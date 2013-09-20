// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Freeze/ObjectStore.h>
#include <Freeze/EvictorI.h>
#include <Freeze/BackgroundSaveEvictorI.h>
#include <Freeze/Util.h>
#include <Freeze/Catalog.h>
#include <Freeze/TransactionI.h>
#include <Freeze/IndexI.h>

#include <Ice/StringConverter.h>

using namespace std;
using namespace Ice;
using namespace Freeze;

Freeze::ObjectStoreBase::ObjectStoreBase(const string& facet, const string& facetType,
                                         bool createDb,  EvictorIBase* evictor,  
                                         const vector<IndexPtr>& indices,
                                         bool populateEmptyIndices) :
    _facet(facet),
    _evictor(evictor),
    _indices(indices),
    _communicator(evictor->communicator()),
    _encoding(evictor->encoding()),
    _keepStats(false)
{
    if(facet == "")
    {
        _dbName = EvictorIBase::defaultDb;
    }
    else
    {
        _dbName = facet;
    }

    if(!facetType.empty())
    {
        //
        // Create a sample servant with this type
        //
        ObjectFactoryPtr factory = _communicator->findObjectFactory(facetType);
        if(factory == 0)
        {
            throw DatabaseException(__FILE__, __LINE__, "No object factory registered for type-id '" + facetType + "'");
        }
        
        _sampleServant = factory->create(facetType);
    }

    ConnectionPtr catalogConnection = createConnection(_communicator, evictor->dbEnv()->getEnvName());
    Catalog catalog(catalogConnection, catalogName());
    
    Catalog::iterator p = catalog.find(evictor->filename());
    if(p != catalog.end())
    {
        if(p->second.evictor)
        {
            //
            // empty means the value is ::Freeze::ObjectRecord
            //
            _keepStats = p->second.value.empty();
        }
        else
        {
            DatabaseException ex(__FILE__, __LINE__);
            ex.message = evictor->filename() + " is not an evictor database";
            throw ex;
        }
    }

    DbEnv* dbEnv = evictor->dbEnv()->getEnv();

    try
    {
        _db.reset(new Db(dbEnv, 0));

        Ice::PropertiesPtr properties = evictor->communicator()->getProperties();
        string propPrefix = "Freeze.Evictor." + evictor->filename() + ".";

        int btreeMinKey = properties->getPropertyAsInt(propPrefix + _dbName + ".BtreeMinKey");
        if(btreeMinKey > 2)
        {
            if(evictor->trace() >= 1)
            {
                Trace out(evictor->communicator()->getLogger(), "Freeze.Evictor");
                out << "Setting \"" << evictor->filename() + "." + _dbName << "\"'s btree minkey to " << btreeMinKey;
            }

            _db->set_bt_minkey(btreeMinKey);
        }
        
        bool checksum = properties->getPropertyAsInt(propPrefix + "Checksum") > 0;
        if(checksum)
        {
            if(evictor->trace() >= 1)
            {
                Trace out(evictor->communicator()->getLogger(), "Freeze.Evictor");
                out << "Turning checksum on for \"" << evictor->filename() << "\"";
            }

            _db->set_flags(DB_CHKSUM);
        }
        
        int pageSize = properties->getPropertyAsInt(propPrefix + "PageSize");
        if(pageSize > 0)
        {
            if(evictor->trace() >= 1)
            {
                Trace out(evictor->communicator()->getLogger(), "Freeze.Evictor");
                out << "Setting \"" << evictor->filename() << "\"'s pagesize to " << pageSize;
            }

            _db->set_pagesize(pageSize);
        }
        

        TransactionPtr tx = catalogConnection->beginTransaction();
        DbTxn* txn = getTxn(tx);

        u_int32_t flags = DB_THREAD;
        if(createDb)
        {
            flags |= DB_CREATE;
        }

        //
        // We keep _dbName as a native string here, while it might have
        // been better to convert it to UTF-8, changing this isn't
        // possible without potentially breaking backward compatibility
        // with deployed databases.
        //
        _db->open(txn, Ice::nativeToUTF8(evictor->communicator(), evictor->filename()).c_str(), _dbName.c_str(),
                  DB_BTREE, flags, FREEZE_DB_MODE);

        for(size_t i = 0; i < _indices.size(); ++i)
        {
            _indices[i]->_impl->associate(this, txn, createDb, populateEmptyIndices);
        }
        
        if(p == catalog.end())
        {
            CatalogData catalogData;
            catalogData.evictor = true;
            catalogData.key = "Ice::Identity";
            catalogData.value = "Object";
            catalog.put(Catalog::value_type(evictor->filename(), catalogData));
        }

        tx->commit();
    }
    catch(const DbException& dx)
    {
        TransactionPtr tx = catalogConnection->currentTransaction();
        if(tx != 0)
        {
            try
            {
                tx->rollback();
            }
            catch(...)
            {
            }
        }

        if(dx.get_errno() == ENOENT)
        {
            NotFoundException ex(__FILE__, __LINE__);
            ex.message = dx.what();
            throw ex;
        }
        else
        {
            DatabaseException ex(__FILE__, __LINE__);
            ex.message = dx.what();
            throw ex;
        }
    }
    catch(...)
    {
        TransactionPtr tx = catalogConnection->currentTransaction();
        if(tx != 0)
        {
            try
            {
                tx->rollback();
            }
            catch(...)
            {
            }
        }
        throw;
    }
}

Freeze::ObjectStoreBase::~ObjectStoreBase()
{
    try
    {
        _db->close(0);
        
        for(size_t i = 0; i < _indices.size(); ++i)
        {
            _indices[i]->_impl->close();
        }
        _indices.clear();
    }
    catch(const DbException& dx)
    {
        Ice::Error error(_communicator->getLogger());
        error << "Freeze: closing ObjectStore " << _dbName << " raised DbException: " << dx.what();
    }
}
    
bool
Freeze::ObjectStoreBase::dbHasObject(const Identity& ident, const TransactionIPtr& transaction) const
{
    DbTxn* tx = 0;
    if(transaction != 0)
    {
        tx = transaction->dbTxn();
        if(tx == 0)
        {
            throw DatabaseException(__FILE__, __LINE__, "inactive transaction");
        }
    }

    Key key;    
    marshal(ident, key, _communicator, _encoding);
    Dbt dbKey;
    initializeInDbt(key, dbKey);
    
    //
    // Keep 0 length since we're not interested in the data
    //
    Dbt dbValue;
    dbValue.set_flags(DB_DBT_USERMEM | DB_DBT_PARTIAL);

    for(;;)
    {
        try
        {
            int err = _db->get(tx, &dbKey, &dbValue, 0);
            
            if(err == 0)
            {
                return true;
            }
            else if(err == DB_NOTFOUND)
            {
                return false;
            }
            else
            {
                assert(0);
                throw DatabaseException(__FILE__, __LINE__);
            }
        }
        catch(const DbDeadlockException& dx)
        {
            if(_evictor->deadlockWarning())
            {
                Warning out(_communicator->getLogger());
                out << "Deadlock in Freeze::ObjectStoreBase::dbHasObject while searching \"" 
                    << _evictor->filename() + "/" + _dbName << "\"; retrying ...";
            }

            if(tx != 0)
            {
                throw DeadlockException(__FILE__, __LINE__, dx.what(), transaction);
            }
            // Else, try again
        }
        catch(const DbException& dx)
        {
            DatabaseException ex(__FILE__, __LINE__);
            ex.message = dx.what();
            throw ex;
        }
    }

}

void
Freeze::ObjectStoreBase::save(Key& key, Value& value, Byte status, DbTxn* tx)
{
    switch(status)
    {
        case created:
        case modified:
        {
            Dbt dbKey;
            Dbt dbValue;
            initializeInDbt(key, dbKey);
            initializeInDbt(value, dbValue);
            u_int32_t flags = (status == created) ? DB_NOOVERWRITE : 0;
            int err = _db->put(tx, &dbKey, &dbValue, flags);
            if(err != 0)
            {
                throw DatabaseException(__FILE__, __LINE__);
            }
            break;
        }

        case destroyed:
        {
            Dbt dbKey;
            initializeInDbt(key, dbKey);
            int err = _db->del(tx, &dbKey, 0);
            if(err != 0)
            {
                throw DatabaseException(__FILE__, __LINE__);
            }
            break;
        }   
        default:
        {
            assert(0);
        }
    }
}

void 
Freeze::ObjectStoreBase::marshal(const Identity& ident, 
                                 Key& bytes, 
                                 const CommunicatorPtr& communicator, 
                                 const EncodingVersion& encoding)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get(), encoding, true);
    stream.write(ident);
    vector<Byte>(stream.b.begin(), stream.b.end()).swap(bytes);
}
    
void 
Freeze::ObjectStoreBase::unmarshal(Identity& ident, 
                                   const Key& bytes, 
                                   const CommunicatorPtr& communicator, 
                                   const EncodingVersion& encoding)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get(), encoding, &bytes[0], &bytes[0] + bytes.size());
    stream.read(ident);
}

void
Freeze::ObjectStoreBase::marshal(const ObjectRecord& v, 
                                 Value& bytes, 
                                 const CommunicatorPtr& communicator,
                                 const EncodingVersion& encoding,
                                 bool keepStats)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get(), encoding, true);
    stream.startWriteEncaps();
    if(keepStats)
    {
        stream.write(v);
    }
    else
    {
        stream.write(v.servant);
    }

    stream.writePendingObjects();
    stream.endWriteEncaps();
    vector<Byte>(stream.b.begin(), stream.b.end()).swap(bytes);
}

void
Freeze::ObjectStoreBase::unmarshal(ObjectRecord& v,
                                   const Value& bytes,
                                   const CommunicatorPtr& communicator,
                                   const EncodingVersion& encoding,
                                   bool keepStats)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get(), encoding, &bytes[0], &bytes[0] + bytes.size());
    stream.sliceObjects(false);
    stream.startReadEncaps();
    
    if(keepStats)
    {
        stream.read(v);
    }
    else
    {
        stream.read(v.servant);
    }
    
    stream.readPendingObjects();
    stream.endReadEncaps();
}

bool
Freeze::ObjectStoreBase::load(const Identity& ident, const TransactionIPtr& transaction, ObjectRecord& rec)
{
    if(transaction == 0)
    {
        throw DatabaseException(__FILE__, __LINE__, "no active transaction");
    }

    DbTxn* txn = transaction->dbTxn();
    
    if(txn == 0)
    {
        throw DatabaseException(__FILE__, __LINE__, "inactive transaction");
    }

    Key key;
    marshal(ident, key, _communicator, _encoding);

    Dbt dbKey;
    initializeInDbt(key, dbKey);

    const size_t defaultValueSize = 4096;
    Value value(defaultValueSize);

    Dbt dbValue;
    initializeOutDbt(value, dbValue);

    for(;;)
    {
        try
        {
            int rs =_db->get(txn, &dbKey, &dbValue, 0);
            if(rs == DB_NOTFOUND)
            {
                return false;
            }
            else if(rs != 0)
            {
                assert(0);
                throw DatabaseException(__FILE__, __LINE__);
            }
            break; // for(;;)
        }
        catch(const DbDeadlockException& dx)
        {
            if(_evictor->deadlockWarning())
            {
                Warning out(_communicator->getLogger());
                out << "Deadlock in Freeze::ObjectStoreBase::load while searching \"" 
                    << _evictor->filename() + "/" + _dbName << "\"";
            }
            throw DeadlockException(__FILE__, __LINE__, dx.what(), transaction);
        }
        catch(const DbException& dx)
        {
            handleDbException(dx, value, dbValue, __FILE__, __LINE__);
        }
    }
    
    unmarshal(rec, value, _communicator, _encoding, _keepStats);
    _evictor->initialize(ident, _facet, rec.servant);
    return true;
}

void
Freeze::ObjectStoreBase::update(const Identity& ident, const ObjectRecord& rec, const TransactionIPtr& transaction)
{
    if(transaction == 0)
    {
        throw DatabaseException(__FILE__, __LINE__, "no active transaction");
    }

    DbTxn* txn = transaction->dbTxn();
    
    if(txn == 0)
    {
        throw DatabaseException(__FILE__, __LINE__, "inactive transaction");
    }

    Key key;
    marshal(ident, key, _communicator, _encoding);

    Value value;
    marshal(rec, value, _communicator, _encoding, _keepStats);

    Dbt dbKey;
    Dbt dbValue;
    initializeInDbt(key, dbKey);
    initializeInDbt(value, dbValue);
    u_int32_t flags = 0;

    try
    {
        _db->put(txn, &dbKey, &dbValue, flags);
    }
    catch(const DbDeadlockException& dx)
    {
        if(_evictor->deadlockWarning())
        {
            Warning out(_communicator->getLogger());
            out << "Deadlock in Freeze::ObjectStoreBase::update while updating \"" 
                << _evictor->filename() + "/" + _dbName << "\"";
        }
        throw DeadlockException(__FILE__, __LINE__, dx.what(), transaction);
    }
    catch(const DbException& dx)
    {
        handleDbException(dx, __FILE__, __LINE__);
    }
}

bool
Freeze::ObjectStoreBase::insert(const Identity& ident, const ObjectRecord& rec, const TransactionIPtr& transaction)
{
    DbTxn* tx = 0;
    if(transaction != 0)
    {
        tx = transaction->dbTxn();
        if(tx == 0)
        {
            throw DatabaseException(__FILE__, __LINE__, "inactive transaction");
        }
    }

    Key key;
    marshal(ident, key, _communicator, _encoding);

    Value value;
    marshal(rec, value, _communicator, _encoding, _keepStats);

    Dbt dbKey;
    Dbt dbValue;
    initializeInDbt(key, dbKey);
    initializeInDbt(value, dbValue);
    u_int32_t flags = DB_NOOVERWRITE;
    if(tx == 0)
    {
        flags |= DB_AUTO_COMMIT;
    }

    for(;;)
    {
        try
        {
            return  _db->put(tx, &dbKey, &dbValue, flags) == 0;
        }
        catch(const DbDeadlockException& dx)
        {
            if(_evictor->deadlockWarning())
            {
                Warning out(_communicator->getLogger());
                out << "Deadlock in Freeze::ObjectStoreBase::insert while updating \"" 
                    << _evictor->filename() + "/" + _dbName << "\"";
            }
            if(tx != 0)
            {
                throw DeadlockException(__FILE__, __LINE__, dx.what(), transaction);
            }
            //
            // Otherwise, try again
            //
        }
        catch(const DbException& dx)
        {
            handleDbException(dx, __FILE__, __LINE__);
        }
    }
}

bool
Freeze::ObjectStoreBase::remove(const Identity& ident, const TransactionIPtr& transaction)
{
    DbTxn* tx = 0;
    if(transaction != 0)
    {
        tx = transaction->dbTxn();
        if(tx == 0)
        {
            throw DatabaseException(__FILE__, __LINE__, "inactive transaction");
        }
    }

    Key key;
    marshal(ident, key, _communicator, _encoding);
   
    Dbt dbKey;
    initializeInDbt(key, dbKey);

    for(;;)
    {
        try
        {
            return _db->del(tx, &dbKey, tx != 0 ? 0 : DB_AUTO_COMMIT) == 0;
        }
        catch(const DbDeadlockException& dx)
        {
            if(_evictor->deadlockWarning())
            {
                Warning out(_communicator->getLogger());
                out << "Deadlock in Freeze::ObjectStoreBase::remove while updating \"" 
                    << _evictor->filename() + "/" + _dbName << "\"";
            }
            if(tx != 0)
            {
                throw DeadlockException(__FILE__, __LINE__, dx.what(), transaction);
            }
            //
            // Otherwise, try again
            //
        }
        catch(const DbException& dx)
        {
            handleDbException(dx, __FILE__, __LINE__);
        }
    }
}


const string&
Freeze::ObjectStoreBase::dbName() const
{
    return _dbName;
}

//
// Non transactional load
//
bool
Freeze::ObjectStoreBase::loadImpl(const Identity& ident, ObjectRecord& rec)
{
    Key key;
    marshal(ident, key, _communicator, _encoding);

    Dbt dbKey;
    initializeInDbt(key, dbKey);

    const size_t defaultValueSize = 4096;
    Value value(defaultValueSize);

    Dbt dbValue;
    initializeOutDbt(value, dbValue);

    for(;;)
    {
        try
        {
            int rs = _db->get(0, &dbKey, &dbValue, 0);
            if(rs == DB_NOTFOUND)
            {
                return false;
            }
            else if(rs != 0)
            {
                assert(0);
                throw DatabaseException(__FILE__, __LINE__);
            }
            break; // for(;;)
        }
        catch(const DbDeadlockException&)
        {
            if(_evictor->deadlockWarning())
            {
                Warning out(_communicator->getLogger());
                out << "Deadlock in Freeze::ObjectStoreBase::load while searching \"" 
                    << _evictor->filename() + "/" + _dbName << "\"; retrying ...";
            }
            //
            // Ignored, try again
            //
        }
        catch(const DbException& dx)
        {
            handleDbException(dx, value, dbValue, __FILE__, __LINE__);
        }
    }
    
    unmarshal(rec, value, _communicator, _encoding, _keepStats);
    _evictor->initialize(ident, _facet, rec.servant);
    return true;
}
