// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Freeze.MapInternal;

import Freeze.Catalog;
import Freeze.CatalogIndexList;
import Freeze.Connection;
import Freeze.ConnectionI;
import Freeze.DatabaseException;
import Freeze.DeadlockException;
import Freeze.IndexNotFoundException;
import Freeze.LinkedList;
import Freeze.Map;
import Freeze.MapDb;
import Freeze.MapIndex;
import Freeze.NavigableMap;
import Freeze.Transaction;
import Freeze.Util;

public abstract class MapI<K, V> extends java.util.AbstractMap<K, V>
    implements Map<K, V>, KeyCodec<K>, IteratorModel<K, V>
{
    public abstract byte[] encodeValue(V o, Ice.Communicator communicator, Ice.EncodingVersion encoding);
    public abstract V decodeValue(byte[] b, Ice.Communicator communicator, Ice.EncodingVersion encoding);

    protected
    MapI(Connection connection, String dbName, String key, String value, boolean createDb,
         java.util.Comparator<K> comparator)
    {
        _connection = (ConnectionI)connection;
        _dbName = dbName;
        _comparator = (comparator == null) ? null : new Comparator(comparator);

        _trace = new TraceLevels(_connection, dbName);

        init(null, dbName, key, value, createDb);
    }

    protected
    MapI(Connection connection, String dbName, java.util.Comparator<K> comparator)
    {
        _connection = (ConnectionI)connection;
        _dbName = dbName;
        _comparator = (comparator == null) ? null : new Comparator(comparator);

        _trace = new TraceLevels(_connection, dbName);
    }

    protected static <K, V> void
    recreate(MapI<K, V> map, String dbName, String key, String value, MapIndex[] indices)
    {
        ConnectionI connection = map._connection;
        TraceLevels trace = map._trace;

        if(dbName.equals(Util.catalogName()) || dbName.equals(Util.catalogIndexListName()))
        {
            throw new DatabaseException(trace.errorPrefix + "You cannot recreate the \"" + dbName + "\" database");
        }

        if(trace.level >= 1)
        {
            trace.logger.trace("Freeze.MapInternal.MapI", "Recreating \"" + dbName + "\"");
        }

        Transaction tx = connection.currentTransaction();
        boolean ownTx = (tx == null);

        com.sleepycat.db.DatabaseEntry keyEntry = new com.sleepycat.db.DatabaseEntry();
        com.sleepycat.db.DatabaseEntry valueEntry = new com.sleepycat.db.DatabaseEntry();

        com.sleepycat.db.Database oldDb = null;
        MapDb newDb = null;

        for(;;)
        {
            try
            {
                if(ownTx)
                {
                    tx = null;
                    tx = connection.beginTransaction();
                }

                com.sleepycat.db.Transaction txn = connection.dbTxn();

                if(trace.level >= 2)
                {
                    trace.logger.trace("Freeze.MapInternal.MapI", "Removing all existing indices for \"" + dbName + "\"");
                }

                CatalogIndexList catalogIndexList = new CatalogIndexList(connection, Util.catalogIndexListName(), true);
                String[] oldIndices = catalogIndexList.remove(dbName);

                if(oldIndices != null)
                {
                    for(String oldIndex : oldIndices)
                    {
                        try
                        {
                            connection.removeMapIndex(dbName, oldIndex);
                        }
                        catch(IndexNotFoundException e)
                        {
                            //
                            // Ignored
                            //
                        }
                    }
                }

                //
                // Rename existing database
                //
                String oldDbName = dbName + ".old-" + java.util.UUID.randomUUID().toString();

                if(trace.level >= 2)
                {
                    trace.logger.trace("Freeze.MapInternal.MapI", "Renaming \"" + dbName + "\" to \"" + oldDbName + "\"");
                }

                connection.dbEnv().getEnv().renameDatabase(txn, dbName, null, oldDbName);

                com.sleepycat.db.DatabaseConfig oldDbConfig = new com.sleepycat.db.DatabaseConfig();
                oldDbConfig.setType(com.sleepycat.db.DatabaseType.BTREE);

                oldDb = connection.dbEnv().getEnv().openDatabase(txn, oldDbName, null, oldDbConfig);

                newDb = new MapDb(connection, dbName, key, value, map._comparator, indices, true);
                map.init(newDb, indices);

                if(trace.level >= 2)
                {
                    trace.logger.trace("Freeze.MapInternal.MapI", "Writing contents of \"" + oldDbName + "\" to fresh \"" +
                                       dbName + "\"");
                }

                //
                // Now simply write all of oldDb into newDb
                //
                com.sleepycat.db.Cursor dbc = null;
                try
                {
                    dbc = oldDb.openCursor(txn, null);

                    while(dbc.getNext(keyEntry, valueEntry, null) == com.sleepycat.db.OperationStatus.SUCCESS)
                    {
                        newDb.db().put(txn, keyEntry, valueEntry);
                    }
                }
                finally
                {
                    if(dbc != null)
                    {
                        dbc.close();
                    }
                }

                if(trace.level >= 2)
                {
                    trace.logger.trace("Freeze.MapInternal.MapI", "Transfer complete; removing \"" + oldDbName + "\"");
                }
                connection.dbEnv().getEnv().removeDatabase(txn, oldDbName, null);

                if(ownTx)
                {
                    try
                    {
                        tx.commit();
                    }
                    finally
                    {
                        tx = null;
                    }
                }

                break; // for (;;)
            }
            catch(com.sleepycat.db.DeadlockException dx)
            {
                if(ownTx)
                {
                    if(trace.deadlockWarning)
                    {
                        trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.recreate on Db \"" + dbName + "\"; retrying ...");
                    }

                    //
                    // Ignored, try again
                    //
                }
                else
                {
                    throw new DeadlockException(trace.errorPrefix + "Map.recreate: " + dx.getMessage(), tx, dx);
                }
            }
            catch(com.sleepycat.db.DatabaseException dx)
            {
                throw new DatabaseException(trace.errorPrefix + "Map.recreate: " + dx.getMessage(), dx);
            }
            catch(java.io.FileNotFoundException fne)
            {
                throw new DatabaseException(trace.errorPrefix + "Map.recreate: " + fne.getMessage(), fne);
            }
            finally
            {
                if(ownTx && tx != null)
                {
                    try
                    {
                        tx.rollback();
                    }
                    catch(DatabaseException de)
                    {
                    }
                }

                try
                {
                    if(newDb != null)
                    {
                        newDb.close();
                    }

                    if(oldDb != null)
                    {
                        try
                        {
                            oldDb.close();
                        }
                        catch(com.sleepycat.db.DatabaseException dx)
                        {
                            throw new DatabaseException(trace.errorPrefix + "Map.recreate: " + dx.getMessage(), dx);
                        }
                    }
                }
                finally
                {
                    newDb = null;
                    oldDb = null;
                }
            }
        }
    }

    protected void
    init(MapIndex[] indices, String dbName, String key, String value, boolean createDb)
    {
        init(_connection.dbEnv().getSharedMapDb(dbName, key, value, _comparator, indices, createDb), indices);
    }

    protected void
    init(MapDb db, MapIndex[] indices)
    {
        _db = db;
        _token = _connection.registerMap(this);

        if(indices != null)
        {
            for(MapIndex index : indices)
            {
                _indexMap.put(index.name(), index);
            }
        }
    }

    //
    // Freeze.Map methods
    //

    public void
    fastPut(K key, V value)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(k);
        putImpl(dbKey, value);
    }

    public boolean
    fastRemove(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(k);
        return removeImpl(dbKey);
    }

    public void
    close()
    {
        if(_db != null)
        {
            try
            {
                closeAllIterators();
            }
            finally
            {
                _db = null;
                _connection.unregisterMap(_token);
                _token = null;
            }
        }
    }

    public int
    closeAllIterators()
    {
        return closeAllIteratorsExcept(null);
    }

    //
    // Close this map and destroy the underlying Berkeley DB database
    //
    public void
    destroy()
    {
        if(_db == null)
        {
            throw new DatabaseException(_trace.errorPrefix + "This map is closed");
        }

        if(_dbName.equals(Util.catalogName()) || _dbName.equals(Util.catalogIndexListName()))
        {
            throw new DatabaseException(_trace.errorPrefix + "You cannot destroy the \"" + _dbName + "\" database");
        }

        if(_connection.currentTransaction() != null)
        {
            throw new DatabaseException(
                _trace.errorPrefix + "You cannot destroy a database within an active transaction");
        }

        if(_trace.level >= 1)
        {
            _trace.logger.trace("Freeze.MapInternal.MapI", "destroying \"" + _dbName + "\"");
        }

        closeDb();

        for(;;)
        {
            Transaction tx = null;
            try
            {
                tx = _connection.beginTransaction();
                com.sleepycat.db.Transaction txn = _connection.dbTxn();

                Catalog catalog = new Catalog(_connection, Util.catalogName(), true);
                catalog.remove(_dbName);

                CatalogIndexList catalogIndexList =
                    new CatalogIndexList(_connection, Util.catalogIndexListName(), true);
                catalogIndexList.remove(_dbName);

                _connection.dbEnv().getEnv().removeDatabase(txn, _dbName, null);

                //
                // Remove all indices
                //
                for(String index : _indexMap.keySet())
                {
                    _connection.removeMapIndex(_dbName, index);
                }

                tx.commit();

                break; // for(;;)
            }
            catch(java.io.FileNotFoundException dx)
            {
                try
                {
                    tx.rollback();
                }
                catch(DatabaseException e)
                {
                }

                throw new DatabaseException(_trace.errorPrefix + "file not found", dx);
            }
            catch(com.sleepycat.db.DeadlockException dx)
            {
                if(_trace.deadlockWarning)
                {
                    _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.destroy on Db \"" + _dbName +
                                          "\"; retrying...");
                }

                //
                // Ignored, try again
                //
            }
            catch(com.sleepycat.db.DatabaseException dx)
            {
                try
                {
                    tx.rollback();
                }
                catch(DatabaseException e)
                {
                }

                throw new DatabaseException(_trace.errorPrefix + dx.getMessage(), dx);
            }
            catch(RuntimeException rx)
            {
                try
                {
                    tx.rollback();
                }
                catch(DatabaseException e)
                {
                }

                throw rx;
            }
        }
    }

    public Connection
    getConnection()
    {
        return _connection;
    }

    public void
    closeDb()
    {
        close();
        _connection.dbEnv().removeSharedMapDb(_dbName);
    }

    //
    // NavigableMap methods
    //

    public java.util.Map.Entry<K, V>
    firstEntry()
    {
        return entrySearch(Search.Type.FIRST, null, true);
    }

    public java.util.Map.Entry<K, V>
    lastEntry()
    {
        return entrySearch(Search.Type.LAST, null, true);
    }

    public java.util.Map.Entry<K, V>
    ceilingEntry(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        return entrySearch(Search.Type.CEILING, k, true);
    }

    public java.util.Map.Entry<K, V>
    floorEntry(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        return entrySearch(Search.Type.FLOOR, k, true);
    }

    public java.util.Map.Entry<K, V>
    higherEntry(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        return entrySearch(Search.Type.HIGHER, k, true);
    }

    public java.util.Map.Entry<K, V>
    lowerEntry(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        return entrySearch(Search.Type.LOWER, k, true);
    }

    public K
    ceilingKey(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        java.util.Map.Entry<K, V> e = entrySearch(Search.Type.CEILING, k, false);
        return e != null ? e.getKey() : null;
    }

    public K
    floorKey(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        java.util.Map.Entry<K, V> e = entrySearch(Search.Type.FLOOR, k, false);
        return e != null ? e.getKey() : null;
    }

    public K
    higherKey(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        java.util.Map.Entry<K, V> e = entrySearch(Search.Type.HIGHER, k, false);
        return e != null ? e.getKey() : null;
    }

    public K
    lowerKey(K key)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        java.util.Map.Entry<K, V> e = entrySearch(Search.Type.LOWER, k, false);
        return e != null ? e.getKey() : null;
    }

    public java.util.Set<K>
    descendingKeySet()
    {
        return descendingMap().keySet();
    }

    public NavigableMap<K, V>
    descendingMap()
    {
        if(_comparator == null)
        {
            throw new UnsupportedOperationException("A comparator is required");
        }

        if(_descendingMap == null)
        {
            _descendingMap = new SubMap<K, V>(this, null, false, null, false, false);
        }

        return _descendingMap;
    }

    public NavigableMap<K, V>
    headMap(K toKey, boolean inclusive)
    {
        if(toKey == null)
        {
            throw new NullPointerException();
        }

        if(_comparator == null)
        {
            throw new UnsupportedOperationException("A comparator is required");
        }

        return new SubMap<K, V>(this, null, false, toKey, inclusive, true);
    }

    public NavigableMap<K, V>
    subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive)
    {
        if(fromKey == null || toKey == null)
        {
            throw new NullPointerException();
        }

        if(_comparator == null)
        {
            throw new UnsupportedOperationException("A comparator is required");
        }

        return new SubMap<K, V>(this, fromKey, fromInclusive, toKey, toInclusive, true);
    }

    public NavigableMap<K, V>
    tailMap(K fromKey, boolean inclusive)
    {
        if(fromKey == null)
        {
            throw new NullPointerException();
        }

        if(_comparator == null)
        {
            throw new UnsupportedOperationException("A comparator is required");
        }

        return new SubMap<K, V>(this, fromKey, inclusive, null, false, true);
    }

    public java.util.Map.Entry<K, V>
    pollFirstEntry()
    {
        EntryI<K, V> e = entrySearch(Search.Type.FIRST, null, true);
        if(e != null)
        {
            removeImpl(e.getDbKey());
        }
        return e;
    }

    public java.util.Map.Entry<K, V>
    pollLastEntry()
    {
        EntryI<K, V> e = entrySearch(Search.Type.LAST, null, true);
        if(e != null)
        {
            removeImpl(e.getDbKey());
        }
        return e;
    }

    //
    // SortedMap methods
    //

    public java.util.Comparator<? super K>
    comparator()
    {
        if(_comparator == null)
        {
            return null;
        }
        else
        {
            //
            // Return's the user's comparator, not the DB comparator.
            //
            return _comparator.comparator();
        }
    }

    public K
    firstKey()
    {
        EntryI<K, V> e = entrySearch(Search.Type.FIRST, null, false);
        if(e == null)
        {
            throw new java.util.NoSuchElementException();
        }
        return e.getKey();
    }

    public K
    lastKey()
    {
        EntryI<K, V> e = entrySearch(Search.Type.LAST, null, false);
        if(e == null)
        {
            throw new java.util.NoSuchElementException();
        }
        return e.getKey();
    }

    public java.util.SortedMap<K, V>
    headMap(K toKey)
    {
        return headMap(toKey, false);
    }

    public java.util.SortedMap<K, V>
    tailMap(K fromKey)
    {
        return tailMap(fromKey, true);
    }

    public java.util.SortedMap<K, V>
    subMap(K fromKey, K toKey)
    {
        return subMap(fromKey, true, toKey, false);
    }

    //
    // Map methods
    //

    public int
    size()
    {
        if(_db == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + _dbName + "\" is closed";
            throw ex;
        }

        for(;;)
        {
            
            try
            {
                com.sleepycat.db.BtreeStats s =
                    (com.sleepycat.db.BtreeStats)_db.db().getStats(_connection.dbTxn(), null);
                return s.getNumKeys();
            }
            catch(com.sleepycat.db.DeadlockException e)
            {
                if(_connection.dbTxn() != null)
                {
                    throw new DeadlockException(_trace.errorPrefix + "Db.getStats: " + e.getMessage(),
                                                _connection.currentTransaction(), e);
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.size while " + "reading Db \"" +
                                              _dbName + "\"; retrying...");
                    }
                    //
                    // Try again
                    //
                }
            }
            catch(com.sleepycat.db.DatabaseException e)
            {
                throw new DatabaseException(_trace.errorPrefix + "Db.getStats: " + e.getMessage(), e);
            }
        }
    }

    public boolean
    containsValue(Object value)
    {
        for(;;)
        {
            Map.EntryIterator<java.util.Map.Entry<K, V>> p = null;
            try
            {
                p = (Map.EntryIterator<java.util.Map.Entry<K, V>>)entrySet().iterator();

                if(value == null)
                {
                    while(p.hasNext())
                    {
                        Entry e = (Entry)p.next();
                        if(e.getValue() == null)
                        {
                            return true;
                        }
                    }
                }
                else
                {
                    while(p.hasNext())
                    {
                        Entry e = (Entry)p.next();
                        if(value.equals(e.getValue()))
                        {
                            return true;
                        }
                    }
                }
                return false;
            }
            catch(DeadlockException e)
            {
                if(_connection.dbTxn() != null)
                {
                    throw e;
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.containsValue while " + 
                                              "iterating over Db \"" + _dbName  + "\"; retrying...");
                    }

                    //
                    // Try again
                    //
                }
            }
            finally
            {
                if(p != null)
                {
                    p.close();
                }
            }
        }
    }

    public boolean
    containsKey(Object o)
    {
        @SuppressWarnings("unchecked")
        K key = (K)o;

        if(_db == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + _dbName + "\" is closed";
            throw ex;
        }

        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());

        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(k);
        com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry();
        dbValue.setPartial(true);

        if(_trace.level >= 2)
        {
            _trace.logger.trace("Freeze.MapInternal.MapI", "checking key in Db \"" + _dbName + "\"");
        }

        for(;;)
        {
            try
            {
                return _db.db().get(_connection.dbTxn(), dbKey, dbValue, null) ==
                    com.sleepycat.db.OperationStatus.SUCCESS;
            }
            catch(com.sleepycat.db.DeadlockException e)
            {
                if(_connection.dbTxn() != null)
                {
                    throw new DeadlockException(_trace.errorPrefix + "Db.get: " + e.getMessage(),
                                                _connection.currentTransaction(), e);
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.containsKey while " +
                                              "reading Db \"" + _dbName + "\"; retrying...");
                    }
                    //
                    // Try again
                    //
                }
            }
            catch(com.sleepycat.db.DatabaseException e)
            {
                throw new DatabaseException(_trace.errorPrefix + "Db.get: " + e.getMessage(), e);
            }
        }
    }

    public V
    get(Object o)
    {
        @SuppressWarnings("unchecked")
        K key = (K)o;

        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(k);
        byte[] v = getImpl(dbKey);
        if(v == null)
        {
            return null;
        }
        else
        {
            return decodeValue(v, _connection.getCommunicator(), _connection.getEncoding());
        }
    }

    public V
    put(K key, V value)
    {
        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(k);
        byte[] v = getImpl(dbKey);
        V old = null;
        if(v != null)
        {
            old = decodeValue(v, _connection.getCommunicator(), _connection.getEncoding());
        }
        putImpl(dbKey, value);
        return old;
    }

    public V
    remove(Object o)
    {
        @SuppressWarnings("unchecked")
        K key = (K)o;

        byte[] k = encodeKey(key, _connection.getCommunicator(), _connection.getEncoding());
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(k);
        byte[] v = getImpl(dbKey);

        if(v != null && removeImpl(dbKey))
        {
            return decodeValue(v, _connection.getCommunicator(), _connection.getEncoding());
        }
        else
        {
            return null;
        }
    }

    public void
    clear()
    {
        if(_db == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + _dbName + "\" is closed";
            throw ex;
        }

        com.sleepycat.db.Transaction txn = _connection.dbTxn();
        if(txn == null)
        {
            closeAllIterators();
        }

        com.sleepycat.db.DatabaseEntry keyEntry = new com.sleepycat.db.DatabaseEntry();
        keyEntry.setPartial(true);

        com.sleepycat.db.DatabaseEntry valueEntry = new com.sleepycat.db.DatabaseEntry();
        valueEntry.setPartial(true);
        
        for(;;)
        {
            try
            {
                com.sleepycat.db.Cursor dbc = null;
                Transaction tx = null;
                try
                {
                    if(txn == null)
                    {
                        tx = _connection.beginTransaction();
                        txn = _connection.dbTxn();
                    }

                    dbc = _db.db().openCursor(txn, null);
                    while(dbc.getNext(keyEntry, valueEntry, null) == com.sleepycat.db.OperationStatus.SUCCESS)
                    {
                        dbc.delete();
                    }
                    break;
                }
                finally
                {
                    try
                    {
                        if(dbc != null)
                        {
                            dbc.close();
                        }
                    }
                    finally 
                    {
                        if(tx != null)
                        {
                            tx.commit();
                        }
                    }
                }
            }
            catch(com.sleepycat.db.DeadlockException e)
            {
                if(txn != null)
                {
                    throw new DeadlockException(_trace.errorPrefix + "Db.truncate: " + e.getMessage(),
                                                _connection.currentTransaction(), e);
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.clear on Db \"" + _dbName +
                                              "\"; retrying...");
                    }

                    //
                    // Try again
                    //
                }
            }
            catch(com.sleepycat.db.DatabaseException e)
            {
                throw new DatabaseException(_trace.errorPrefix + "Db.truncate: " + e.getMessage(), e);
            }
        }
    }

    public java.util.Set<java.util.Map.Entry<K, V>>
    entrySet()
    {
        if(_entrySet == null)
        {
            _entrySet = new java.util.AbstractSet<java.util.Map.Entry<K, V>>()
            {
                public java.util.Iterator<java.util.Map.Entry<K, V>>
                iterator()
                {
                    return new IteratorI<K, V>(MapI.this, MapI.this);
                }

                public boolean
                contains(Object o)
                {
                    if(!(o instanceof Entry))
                    {
                        return false;
                    }
                    @SuppressWarnings("unchecked")
                    EntryI<K, V> entry = (EntryI<K, V>)o;
                    V value = entry.getValue();

                    byte[] v = getImpl(entry.getDbKey());
                    return v != null && valEquals(decodeValue(v, _connection.getCommunicator(),
                                                              _connection.getEncoding()), value);
                }

                public boolean
                remove(Object o)
                {
                    if(!(o instanceof Entry))
                    {
                        return false;
                    }
                    @SuppressWarnings("unchecked")
                    EntryI<K, V> entry = (EntryI<K, V>)o;
                    V value = entry.getValue();

                    byte[] v = getImpl(entry.getDbKey());
                    if(v != null && valEquals(decodeValue(v, _connection.getCommunicator(), _connection.getEncoding()),
                                              value))
                    {
                        return removeImpl(entry.getDbKey());
                    }
                    return false;
                }

                public int
                size()
                {
                    return MapI.this.size();
                }

                public void
                clear()
                {
                    MapI.this.clear();
                }
            };
        }

        return _entrySet;
    }

    //
    // IteratorModel methods
    //

    public String
    dbName()
    {
        return _dbName;
    }

    public TraceLevels
    traceLevels()
    {
        return _trace;
    }

    public com.sleepycat.db.Cursor
    openCursor()
        throws com.sleepycat.db.DatabaseException
    {
        return _db.db().openCursor(_connection.dbTxn(), null);
    }

    public EntryI<K, V>
    firstEntry(com.sleepycat.db.Cursor cursor)
        throws com.sleepycat.db.DatabaseException
    {
        return firstEntry(cursor, null, false, null, false);
    }

    public EntryI<K, V>
    nextEntry(com.sleepycat.db.Cursor cursor)
        throws com.sleepycat.db.DatabaseException
    {
        return nextEntry(cursor, null, false);
    }

    com.sleepycat.db.Database
    db()
    {
        return _db.db();
    }

    ConnectionI
    connection()
    {
        return _connection;
    }

    int
    closeAllIteratorsExcept(Map.EntryIterator<java.util.Map.Entry<K, V>> except)
    {
        int count = 0;

        java.util.Iterator<IteratorI> p = _iteratorList.iterator();

        while(p.hasNext())
        {
            IteratorI i = p.next();
            if(i != except)
            {
                i.close();
                ++count;
            }
        }

        return count;
    }

    Object
    addIterator(IteratorI i)
    {
        _iteratorList.addFirst(i);
        java.util.Iterator<IteratorI> p = _iteratorList.iterator();
        p.next();
        return p;
    }

    void
    removeIterator(Object token)
    {
        @SuppressWarnings("unchecked")
        java.util.Iterator<IteratorI> i = (java.util.Iterator<IteratorI>)token;

        i.remove();
    }

    //
    // Convenience method for use in this class.
    //
    private EntryI<K, V>
    entrySearch(Search.Type type, byte[] key, boolean includeValue)
    {
        return entrySearch(type, key, includeValue, null);
    }

    //
    // Also used by SubMap.
    //
    EntryI<K, V>
    entrySearch(Search.Type type, byte[] key, boolean includeValue, Search.KeyValidator validator)
    {
        if(type != Search.Type.FIRST && type != Search.Type.LAST && key == null)
        {
            throw new NullPointerException();
        }

        if(_db.db() == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + dbName() + "\" is closed";
            throw ex;
        }

        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry(key);
        com.sleepycat.db.DatabaseEntry dbValue = includeValue ? new com.sleepycat.db.DatabaseEntry() : null;

        if(Search.search(type, _connection, _dbName, _db.db(), dbKey, dbValue, _comparator, validator, _trace))
        {
            return new EntryI<K, V>(this, null, dbKey, dbValue != null ? dbValue.getData() : null, null);
        }

        return null;
    }

    //
    // For ascending maps.
    //
    EntryI<K, V>
    firstEntry(com.sleepycat.db.Cursor cursor, K fromKey, boolean fromInclusive, K toKey, boolean toInclusive)
        throws com.sleepycat.db.DatabaseException
    {
        if(fromKey != null)
        {
            com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry();
            com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry();

            byte[] k = encodeKey(fromKey, _connection.getCommunicator(), _connection.getEncoding());
            dbKey.setData(k);
            dbKey.setReuseBuffer(false);

            com.sleepycat.db.OperationStatus status = cursor.getSearchKeyRange(dbKey, dbValue, null);

            if(status == com.sleepycat.db.OperationStatus.SUCCESS && !fromInclusive)
            {
                int cmp = _comparator.compare(dbKey.getData(), k);
                assert(cmp >= 0);
                if(cmp == 0)
                {
                    status = cursor.getNextNoDup(dbKey, dbValue, null);
                }
            }

            if(status == com.sleepycat.db.OperationStatus.SUCCESS)
            {
                return newEntry(dbKey, dbValue, fromKey, fromInclusive, toKey, toInclusive);
            }

            return null;
        }
        else
        {
            return nextEntry(cursor, toKey, toInclusive);
        }
    }

    //
    // For ascending maps.
    //
    EntryI<K, V>
    nextEntry(com.sleepycat.db.Cursor cursor, K toKey, boolean toInclusive)
        throws com.sleepycat.db.DatabaseException
    {
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry();
        com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry();

        if(cursor.getNext(dbKey, dbValue, null) == com.sleepycat.db.OperationStatus.SUCCESS)
        {
            return newEntry(dbKey, dbValue, null, false, toKey, toInclusive);
        }

        return null;
    }

    //
    // For descending maps.
    //
    EntryI<K, V>
    lastEntry(com.sleepycat.db.Cursor cursor, K fromKey, boolean fromInclusive, K toKey, boolean toInclusive)
        throws com.sleepycat.db.DatabaseException
    {
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry();
        com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry();
        com.sleepycat.db.OperationStatus status = null;

        if(fromKey != null)
        {
            byte[] k = encodeKey(fromKey, _connection.getCommunicator(), _connection.getEncoding());
            dbKey.setData(k);
            dbKey.setReuseBuffer(false);

            status = cursor.getSearchKeyRange(dbKey, dbValue, null);

            if(status == com.sleepycat.db.OperationStatus.SUCCESS && !fromInclusive)
            {
                int cmp = _comparator.compare(dbKey.getData(), k);
                assert(cmp >= 0);
                if(cmp == 0)
                {
                    status = cursor.getPrevNoDup(dbKey, dbValue, null);
                }
            }
        }
        else
        {
            status = cursor.getLast(dbKey, dbValue, null);
        }

        if(status == com.sleepycat.db.OperationStatus.SUCCESS)
        {
            return newEntry(dbKey, dbValue, toKey, toInclusive, fromKey, fromInclusive);
        }

        return null;
    }

    //
    // For descending maps.
    //
    EntryI<K, V>
    previousEntry(com.sleepycat.db.Cursor cursor, K toKey, boolean toInclusive)
        throws com.sleepycat.db.DatabaseException
    {
        com.sleepycat.db.DatabaseEntry dbKey = new com.sleepycat.db.DatabaseEntry();
        com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry();

        if(cursor.getPrev(dbKey, dbValue, null) == com.sleepycat.db.OperationStatus.SUCCESS)
        {
            return newEntry(dbKey, dbValue, toKey, toInclusive, null, false);
        }

        return null;
    }

    void
    putImpl(com.sleepycat.db.DatabaseEntry dbKey, V value)
    {
        if(_db == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + _dbName + "\" is closed";
            throw ex;
        }

        byte[] v = encodeValue(value, _connection.getCommunicator(), _connection.getEncoding());
        com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry(v);

        if(_trace.level >= 2)
        {
            _trace.logger.trace("Freeze.MapInternal.MapI", "writing value in Db \"" + _dbName + "\"");
        }

        com.sleepycat.db.Transaction txn = _connection.dbTxn();
        if(txn == null)
        {
            closeAllIterators();
        }

        for(;;)
        {
            try
            {
                _db.db().put(txn, dbKey, dbValue);
                break;
            }
            catch(com.sleepycat.db.DeadlockException e)
            {
                if(txn != null)
                {
                    throw new DeadlockException(_trace.errorPrefix + "Db.put: " + e.getMessage(),
                                                _connection.currentTransaction(), e);
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.putImpl while " +
                                              "writing into Db \"" + _dbName + "\"; retrying...");
                    }

                    //
                    // Try again
                    //
                }
            }
            catch(com.sleepycat.db.DatabaseException e)
            {
                throw new DatabaseException(_trace.errorPrefix + "Db.put: " + e.getMessage(), e);
            }
        }
    }

    boolean
    removeImpl(com.sleepycat.db.DatabaseEntry dbKey)
    {
        if(_db == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + _dbName + "\" is closed";
            throw ex;
        }

        if(_trace.level >= 2)
        {
            _trace.logger.trace("Freeze.MapInternal.MapI", "deleting value from Db \"" + _dbName + "\"");
        }

        com.sleepycat.db.Transaction txn = _connection.dbTxn();
        if(txn == null)
        {
            closeAllIterators();
        }

        for(;;)
        {
            try
            {
                com.sleepycat.db.OperationStatus rc = _db.db().delete(txn, dbKey);
                return (rc == com.sleepycat.db.OperationStatus.SUCCESS);
            }
            catch(com.sleepycat.db.DeadlockException e)
            {
                if(txn != null)
                {
                    throw new DeadlockException(_trace.errorPrefix + "Db.del: " + e.getMessage(),
                                                _connection.currentTransaction(), e);
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.removeImpl while " +
                                              "writing into Db \"" + _dbName + "\"; retrying...");
                    }

                    //
                    // Try again
                    //
                }
            }
            catch(com.sleepycat.db.DatabaseException e)
            {
                throw new DatabaseException(_trace.errorPrefix + "Db.del: " + e.getMessage(), e);
            }
        }
    }

    private byte[]
    getImpl(com.sleepycat.db.DatabaseEntry dbKey)
    {
        if(_db == null)
        {
            DatabaseException ex = new DatabaseException();
            ex.message = _trace.errorPrefix + "\"" + _dbName + "\" is closed";
            throw ex;
        }

        com.sleepycat.db.DatabaseEntry dbValue = new com.sleepycat.db.DatabaseEntry();

        if(_trace.level >= 2)
        {
            _trace.logger.trace("Freeze.MapInternal.MapI", "reading value from Db \"" + _dbName + "\"");
        }

        for(;;)
        {
            try
            {
                com.sleepycat.db.OperationStatus rc = _db.db().get(_connection.dbTxn(), dbKey, dbValue, null);
                if(rc == com.sleepycat.db.OperationStatus.SUCCESS)
                {
                    return dbValue.getData();
                }
                else
                {
                    return null;
                }
            }
            catch(com.sleepycat.db.DeadlockException e)
            {
                if(_connection.dbTxn() != null)
                {
                    throw new DeadlockException(_trace.errorPrefix + "Db.get: " + e.getMessage(),
                                                _connection.currentTransaction(), e);
                }
                else
                {
                    if(_trace.deadlockWarning)
                    {
                        _trace.logger.warning("Deadlock in Freeze.MapInternal.MapI.getImpl while " +
                                              "reading Db \"" + _dbName + "\"; retrying...");
                    }

                    //
                    // Try again
                    //
                }
            }
            catch(com.sleepycat.db.DatabaseException e)
            {
                throw new DatabaseException(_trace.errorPrefix + "Db.get: " + e.getMessage(), e);
            }
        }
    }

    private EntryI<K, V>
    newEntry(com.sleepycat.db.DatabaseEntry dbKey, com.sleepycat.db.DatabaseEntry dbValue, K fromKey,
             boolean fromInclusive, K toKey, boolean toInclusive)
    {
        K key = null;
        if(fromKey != null || toKey != null)
        {
            key = decodeKey(dbKey.getData(), _connection.getCommunicator(), _connection.getEncoding());
            if(!checkRange(key, fromKey, fromInclusive, toKey, toInclusive))
            {
                return null;
            }
        }

        return new EntryI<K, V>(this, key, dbKey, dbValue.getData(), null);
    }

    private boolean
    checkRange(K key, K fromKey, boolean fromInclusive, K toKey, boolean toInclusive)
    {
        if(fromKey != null)
        {
            int cmp = _comparator.comparator().compare(key, fromKey);
            if((fromInclusive && cmp < 0) || (!fromInclusive && cmp <= 0))
            {
                return false;
            }
        }
        if(toKey != null)
        {
            int cmp = _comparator.comparator().compare(key, toKey);
            if((toInclusive && cmp > 0) || (!toInclusive && cmp >= 0))
            {
                return false;
            }
        }
        return true;
    }

    private static boolean
    valEquals(Object v1, Object v2)
    {
        return (v1 == null ? v2 == null : v1.equals(v2));
    }

    private class Comparator implements java.util.Comparator<byte[]>
    {
        Comparator(java.util.Comparator<K> comparator)
        {
            _comparator = comparator;
        }

        public java.util.Comparator<K>
        comparator()
        {
            return _comparator;
        }

        public int
        compare(byte[] d1, byte[] d2)
        {
            Ice.Communicator communicator = _connection.getCommunicator();
            Ice.EncodingVersion encoding = _connection.getEncoding();
            return _comparator.compare(decodeKey(d1, communicator, encoding), decodeKey(d2, communicator, encoding));
        }

        //
        // The user-supplied comparator
        //
        private final java.util.Comparator<K> _comparator;
    }

    public static class Patcher implements IceInternal.Patcher
    {
        public
        Patcher(String type)
        {
            this.type = type;
        }

        public void
        patch(Ice.Object v)
        {
            value = v;
        }

        public String
        type()
        {
            return this.type;
        }

        public Ice.Object
        value()
        {
            return this.value;
        }

        public String type;
        public Ice.Object value;
    }

    private final ConnectionI _connection;
    private final Comparator _comparator;
    private final String _dbName;

    private final TraceLevels _trace;
    private java.util.Iterator _token;
    private MapDb _db;

    private java.util.Set<java.util.Map.Entry<K, V>> _entrySet;
    private NavigableMap<K, V> _descendingMap;
    private LinkedList<IteratorI> _iteratorList = new LinkedList<IteratorI>();
    private java.util.Map<String, MapIndex> _indexMap = new java.util.HashMap<String, MapIndex>();
}
