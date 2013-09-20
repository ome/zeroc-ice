// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceGrid/Topics.h>
#include <IceGrid/DescriptorHelper.h>

using namespace std;
using namespace IceGrid;

namespace
{

//
// Encodings supported by the observers. We create one topic per
// encoding version and subscribe the observer to the appropriate
// topic depending on its encoding.
//
Ice::EncodingVersion encodings[] = {
    { 1, 0 },
    { 1, 1 }
};

}

ObserverTopic::ObserverTopic(const IceStorm::TopicManagerPrx& topicManager, const string& name) :
    _logger(topicManager->ice_getCommunicator()->getLogger()),
    _serial(0)
{
    for(int i = 0; i < static_cast<int>(sizeof(encodings) / sizeof(Ice::EncodingVersion)); ++i)
    {
        ostringstream os;
        os << name << "-" << Ice::encodingVersionToString(encodings[i]);
        IceStorm::TopicPrx t;
        try
        {
            t = topicManager->create(os.str());
        }
        catch(const IceStorm::TopicExists&)
        {
            t = topicManager->retrieve(os.str());
        }

        //
        // NOTE: collocation optimization needs to be turned on for the
        // topic because the subscribe() method is given a fixed proxy
        // which can't be marshalled.
        //
        _topics[encodings[i]] = t->ice_collocationOptimized(true);
        _basePublishers.push_back(
            t->getPublisher()->ice_collocationOptimized(false)->ice_encodingVersion(encodings[i]));
    }
}

ObserverTopic::~ObserverTopic()
{
}

int
ObserverTopic::subscribe(const Ice::ObjectPrx& obsv, const string& name)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }

    assert(obsv);
    try
    {
        IceStorm::QoS qos;
        qos["reliability"] = "ordered";
        Ice::EncodingVersion v = IceInternal::getCompatibleEncoding(obsv->ice_getEncodingVersion());
        map<Ice::EncodingVersion, IceStorm::TopicPrx>::const_iterator p = _topics.find(v);
        if(p == _topics.end())
        {
            Ice::Warning out(_logger);
            out << "unsupported encoding version for observer `" << obsv << "'";
            return -1;
        }
        initObserver(p->second->subscribeAndGetPublisher(qos, obsv->ice_twoway()));
    }
    catch(const IceStorm::AlreadySubscribed&)
    {
        throw ObserverAlreadyRegisteredException(obsv->ice_getIdentity());
    }

    if(!name.empty())
    {
        assert(_syncSubscribers.find(name) == _syncSubscribers.end());
        _syncSubscribers.insert(name);
        addExpectedUpdate(_serial, name);
        return _serial;
    }
    return -1;
}

void
ObserverTopic::unsubscribe(const Ice::ObjectPrx& observer, const string& name)
{
    Lock sync(*this);
    Ice::EncodingVersion v = IceInternal::getCompatibleEncoding(observer->ice_getEncodingVersion());
    map<Ice::EncodingVersion, IceStorm::TopicPrx>::const_iterator p = _topics.find(v);
    if(p == _topics.end())
    {
        return;
    }
    p->second->unsubscribe(observer);

    assert(observer);

    if(!name.empty())
    {
        assert(_syncSubscribers.find(name) != _syncSubscribers.end());
        _syncSubscribers.erase(name);

        map<int, set<string> >::iterator p = _waitForUpdates.begin();
        bool notifyMonitor = false;
        while(p != _waitForUpdates.end())
        {
            p->second.erase(name);
            if(p->second.empty())
            {
                _waitForUpdates.erase(p++);
                notifyMonitor = true;
            }
            else
            {
                ++p;
            }
        }
    
        if(notifyMonitor)
        {
            notifyAll();
        }
    }
}

void
ObserverTopic::destroy()
{
    Lock sync(*this);
    _topics.clear();
    notifyAll();
}

void
ObserverTopic::receivedUpdate(const string& name, int serial, const string& failure)
{
    Lock sync(*this);
    map<int, set<string> >::iterator p = _waitForUpdates.find(serial);
    if(p != _waitForUpdates.end())
    {
        p->second.erase(name);
        
        if(!failure.empty())
        {
            map<int, map<string, string> >::iterator q = _updateFailures.find(serial);
            if(q == _updateFailures.end())
            {
                q = _updateFailures.insert(make_pair(serial, map<string ,string>())).first;
            }
            q->second.insert(make_pair(name, failure));
        }

        if(p->second.empty())
        {
            _waitForUpdates.erase(p);
        }

        notifyAll();
    }
}

void
ObserverTopic::waitForSyncedSubscribers(int serial, const string& name)
{
    Lock sync(*this);
    waitForSyncedSubscribersNoSync(serial, name);
}

void
ObserverTopic::addExpectedUpdate(int serial, const string& name)
{
    if(_syncSubscribers.empty() && name.empty())
    {
        return;
    }

    // Must be called with the lock held.
    if(name.empty())
    {
        assert(_waitForUpdates[serial].empty());
        _waitForUpdates[serial] = _syncSubscribers;
    }
    else
    {
        _waitForUpdates[serial].insert(name);
    }
}

void
ObserverTopic::waitForSyncedSubscribersNoSync(int serial, const string& name)
{
    if(serial < 0)
    {
        return;
    }

    //
    // Wait until all the updates are received or the service shutdown.
    //
    while(!_topics.empty())
    {
        map<int, set<string> >::const_iterator p = _waitForUpdates.find(serial);
        if(p == _waitForUpdates.end())
        {
            map<int, map<string, string> >::iterator q = _updateFailures.find(serial);
            if(q != _updateFailures.end())
            {
                map<string, string> failures = q->second;
                _updateFailures.erase(q);               
                ostringstream os;
                for(map<string, string>::const_iterator r = failures.begin(); r != failures.end(); ++r)
                {
                    os << "replication failed on replica `" << r->first << "':\n" << r->second << "\n";
                }

                Ice::Error err(_logger);
                err << os.str();
            }
            return;
        }
        else
        {
            if(!name.empty() && p->second.find(name) == p->second.end())
            {
                return;
            }
            wait();
        }
    }
}

void
ObserverTopic::updateSerial(int serial)
{
    assert(_serial + 1 == serial);
    _serial = serial;
}

Ice::Context
ObserverTopic::getContext(int serial) const
{
    ostringstream os;
    os << serial;

    Ice::Context context;
    context["serial"] = os.str();
    return context;
}

RegistryObserverTopic::RegistryObserverTopic(const IceStorm::TopicManagerPrx& topicManager) : 
    ObserverTopic(topicManager, "RegistryObserver")
{
    _publishers = getPublishers<RegistryObserverPrx>();
}

void
RegistryObserverTopic::registryUp(const RegistryInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return;
    }
    updateSerial(_serial + 1);
    _registries.insert(make_pair(info.name, info));
    try
    {
        for(vector<RegistryObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->registryUp(info);
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `registryUp' update:\n" << ex;    
    }
}

void 
RegistryObserverTopic::registryDown(const string& name)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return;
    }

    if(_registries.find(name) == _registries.end())
    {
        return;
    }

    updateSerial(_serial + 1);
    _registries.erase(name);
    try
    {
        for(vector<RegistryObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->registryDown(name);
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `registryDown' update:\n" << ex;    
    }
}

void
RegistryObserverTopic::initObserver(const Ice::ObjectPrx& obsv)
{
    RegistryObserverPrx observer = RegistryObserverPrx::uncheckedCast(obsv);
    RegistryInfoSeq registries;
    registries.reserve(_registries.size());
    for(map<string, RegistryInfo>::const_iterator p = _registries.begin(); p != _registries.end(); ++p)
    {
        registries.push_back(p->second);
    }
    observer->registryInit(registries, getContext(_serial));
}

NodeObserverTopic::NodeObserverTopic(const IceStorm::TopicManagerPrx& topicManager, 
                                     const Ice::ObjectAdapterPtr& adapter) : 
    ObserverTopic(topicManager, "NodeObserver")
{
    _publishers = getPublishers<NodeObserverPrx>();
    try
    {
        const_cast<NodeObserverPrx&>(_externalPublisher) = NodeObserverPrx::uncheckedCast(adapter->addWithUUID(this));
    }
    catch(const Ice::LocalException&)
    {
    }
}

void
NodeObserverTopic::nodeInit(const NodeDynamicInfoSeq&, const Ice::Current&)
{
    assert(false);
}

void
NodeObserverTopic::nodeUp(const NodeDynamicInfo& info, const Ice::Current&)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return;
    }
    updateSerial(_serial + 1);
    _nodes.insert(make_pair(info.info.name, info));
    try
    {
        for(vector<NodeObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->nodeUp(info);
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing 'nodeUp' update:\n" << ex;    
    }
}

void 
NodeObserverTopic::nodeDown(const string& /*name*/, const Ice::Current&)
{
    assert(false);
}

void 
NodeObserverTopic::updateServer(const string& node, const ServerDynamicInfo& server, const Ice::Current&)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return;
    }

    if(_nodes.find(node) == _nodes.end())
    {
        //
        // If the node isn't known anymore, we ignore the update.
        //
        return;
    }
    
    updateSerial(_serial + 1);

    ServerDynamicInfoSeq& servers = _nodes[node].servers;
    ServerDynamicInfoSeq::iterator p = servers.begin();
    while(p != servers.end())
    {
        if(p->id == server.id)
        {
            if(server.state == Destroyed || (server.state == Inactive && server.enabled))
            {
                servers.erase(p);
            }
            else
            {
                *p = server;
            }
            break;
        }
        ++p;
    }
    if(server.state != Destroyed && (server.state != Inactive || !server.enabled) && p == servers.end())
    {
        servers.push_back(server);
    }

    try
    {
        for(vector<NodeObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->updateServer(node, server);
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `updateServer' update:\n" << ex;    
    }
}

void 
NodeObserverTopic::updateAdapter(const string& node, const AdapterDynamicInfo& adapter, const Ice::Current&)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return;
    }

    if(_nodes.find(node) == _nodes.end())
    {
        //
        // If the node isn't known anymore, we ignore the update.
        //
        return;
    }

    updateSerial(_serial + 1);

    AdapterDynamicInfoSeq& adapters = _nodes[node].adapters;
    AdapterDynamicInfoSeq::iterator p = adapters.begin();
    while(p != adapters.end())
    {
        if(p->id == adapter.id)
        {
            if(adapter.proxy)
            {
                *p = adapter;
            }
            else
            {
                adapters.erase(p);
            }
            break;
        }
        ++p;
    }
    if(adapter.proxy && p == adapters.end())
    {
        adapters.push_back(adapter);
    }
    
    try
    {
        for(vector<NodeObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->updateAdapter(node, adapter);
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `updateAdapter' update:\n" << ex;    
    }
}

void 
NodeObserverTopic::nodeDown(const string& name)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return;
    }

    updateSerial(_serial + 1);

    if(_nodes.find(name) != _nodes.end())
    {
        _nodes.erase(name);
        try
        {
            for(vector<NodeObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
            {
                (*p)->nodeDown(name);
            }
        }
        catch(const Ice::LocalException& ex)
        {
            Ice::Warning out(_logger);
            out << "unexpected exception while publishing `nodeDown' update:\n" << ex;    
        }
    }
}

void
NodeObserverTopic::initObserver(const Ice::ObjectPrx& obsv)
{
    NodeObserverPrx observer = NodeObserverPrx::uncheckedCast(obsv);
    NodeDynamicInfoSeq nodes;
    nodes.reserve(_nodes.size());
    for(map<string, NodeDynamicInfo>::const_iterator p = _nodes.begin(); p != _nodes.end(); ++p)
    {
        nodes.push_back(p->second);
    }
    observer->nodeInit(nodes, getContext(_serial));
}

ApplicationObserverTopic::ApplicationObserverTopic(const IceStorm::TopicManagerPrx& topicManager,
                                                   const map<string, ApplicationInfo>& applications) :
    ObserverTopic(topicManager, "ApplicationObserver"),
    _applications(applications)
{
    _publishers = getPublishers<ApplicationObserverPrx>();
}

int
ApplicationObserverTopic::applicationInit(int serial, const ApplicationInfoSeq& apps)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(serial);
    _applications.clear();
    for(ApplicationInfoSeq::const_iterator p = apps.begin(); p != apps.end(); ++p)
    {
        _applications.insert(make_pair(p->descriptor.name, *p));
    }
    try
    {
        for(vector<ApplicationObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->applicationInit(serial, apps, getContext(serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `applicationInit' update:\n" << ex;    
    }
    addExpectedUpdate(serial);
    return serial;
}

int 
ApplicationObserverTopic::applicationAdded(int serial, const ApplicationInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }

    updateSerial(serial);
    _applications.insert(make_pair(info.descriptor.name, info));
    try
    {
        for(vector<ApplicationObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->applicationAdded(serial, info, getContext(serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `applicationAdded' update:\n" << ex;    
    }
    addExpectedUpdate(serial);
    return serial;
}

int 
ApplicationObserverTopic::applicationRemoved(int serial, const string& name)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(serial);
    _applications.erase(name);
    try
    {
        for(vector<ApplicationObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->applicationRemoved(serial, name, getContext(serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `applicationRemoved' update:\n" << ex;    
    }
    addExpectedUpdate(serial);
    return serial;
}

int 
ApplicationObserverTopic::applicationUpdated(int serial, const ApplicationUpdateInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }

    updateSerial(serial);
    try
    {
        map<string, ApplicationInfo>::iterator p = _applications.find(info.descriptor.name);
        if(p != _applications.end())
        {
            ApplicationHelper helper(_publishers[0]->ice_getCommunicator(), p->second.descriptor);
            p->second.descriptor = helper.update(info.descriptor);
            p->second.updateTime = info.updateTime;
            p->second.updateUser = info.updateUser;
            p->second.revision = info.revision;
        }
    }
    catch(const DeploymentException& ex)
    {
        Ice::Error out(_logger);
        out << "unexpected exception while instantiating application `" << info.descriptor.name << "':\n" << ex.reason;
        assert(false);
    }
    catch(const std::string& msg)
    {
        Ice::Error out(_logger);
        out << "unexpected exception while instantiating application `" << info.descriptor.name << "':\n" << msg;
        assert(false);
    }
    catch(const char* msg)
    {
        Ice::Error out(_logger);
        out << "unexpected exception while instantiating application `" << info.descriptor.name << "':\n" << msg;
        assert(false);
    }
    catch(...)
    {
        Ice::Error out(_logger);
        out << "unexpected exception while instantiating application `" << info.descriptor.name << "'";
        assert(false);
    }
    try
    {
        for(vector<ApplicationObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->applicationUpdated(serial, info, getContext(serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `applicationUpdated' update:\n" << ex;    
    }
    addExpectedUpdate(serial);
    return serial;
}

void 
ApplicationObserverTopic::initObserver(const Ice::ObjectPrx& obsv)
{
    ApplicationObserverPrx observer = ApplicationObserverPrx::uncheckedCast(obsv);
    ApplicationInfoSeq applications;
    for(map<string, ApplicationInfo>::const_iterator p = _applications.begin(); p != _applications.end(); ++p)
    {
        applications.push_back(p->second);
    }
    observer->applicationInit(_serial, applications, getContext(_serial));
}

AdapterObserverTopic::AdapterObserverTopic(const IceStorm::TopicManagerPrx& topicManager,
                                           const map<string, AdapterInfo>& adapters) :
    ObserverTopic(topicManager, "AdapterObserver"),
    _adapters(adapters)
{
    _publishers = getPublishers<AdapterObserverPrx>();
}

int 
AdapterObserverTopic::adapterInit(const AdapterInfoSeq& adpts)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _adapters.clear();
    for(AdapterInfoSeq::const_iterator q = adpts.begin(); q != adpts.end(); ++q)
    {
        _adapters.insert(make_pair(q->id, *q));
    }
    try
    {
        for(vector<AdapterObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->adapterInit(adpts, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `adapterInit' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int 
AdapterObserverTopic::adapterAdded(const AdapterInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _adapters.insert(make_pair(info.id, info));
    try
    {
        for(vector<AdapterObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->adapterAdded(info, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `adapterAdded' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int 
AdapterObserverTopic::adapterUpdated(const AdapterInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _adapters[info.id] = info;
    try
    {
        for(vector<AdapterObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->adapterUpdated(info, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `adapterUpdated' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int
AdapterObserverTopic::adapterRemoved(const string& id)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _adapters.erase(id);
    try
    {
        for(vector<AdapterObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->adapterRemoved(id, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `adapterRemoved' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

void 
AdapterObserverTopic::initObserver(const Ice::ObjectPrx& obsv)
{
    AdapterObserverPrx observer = AdapterObserverPrx::uncheckedCast(obsv);
    AdapterInfoSeq adapters;
    for(map<string, AdapterInfo>::const_iterator p = _adapters.begin(); p != _adapters.end(); ++p)
    {
        adapters.push_back(p->second);
    }   
    observer->adapterInit(adapters, getContext(_serial));
}

ObjectObserverTopic::ObjectObserverTopic(const IceStorm::TopicManagerPrx& topicManager,
                                         const map<Ice::Identity, ObjectInfo>& objects) :
    ObserverTopic(topicManager, "ObjectObserver"),
    _objects(objects)
{
    _publishers = getPublishers<ObjectObserverPrx>();
}

int 
ObjectObserverTopic::objectInit(const ObjectInfoSeq& objects)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _objects.clear();
    for(ObjectInfoSeq::const_iterator r = objects.begin(); r != objects.end(); ++r)
    {
        _objects.insert(make_pair(r->proxy->ice_getIdentity(), *r));
    }
    try
    {
        for(vector<ObjectObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->objectInit(objects, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `objectInit' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int 
ObjectObserverTopic::objectAdded(const ObjectInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _objects.insert(make_pair(info.proxy->ice_getIdentity(), info));
    try
    {
        for(vector<ObjectObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->objectAdded(info, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `objectAdded' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int 
ObjectObserverTopic::objectUpdated(const ObjectInfo& info)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _objects[info.proxy->ice_getIdentity()] = info;
    try
    {
        for(vector<ObjectObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->objectUpdated(info, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `objectUpdated' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int
ObjectObserverTopic::objectRemoved(const Ice::Identity& id)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);
    _objects.erase(id);
    try
    {
        for(vector<ObjectObserverPrx>::const_iterator p = _publishers.begin(); p != _publishers.end(); ++p)
        {
            (*p)->objectRemoved(id, getContext(_serial));
        }
    }
    catch(const Ice::LocalException& ex)
    {
        Ice::Warning out(_logger);
        out << "unexpected exception while publishing `objectRemoved' update:\n" << ex;    
    }
    addExpectedUpdate(_serial);
    return _serial;
}

int
ObjectObserverTopic::objectsAddedOrUpdated(const ObjectInfoSeq& infos)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);

    for(ObjectInfoSeq::const_iterator p = infos.begin(); p != infos.end(); ++p)
    {
        map<Ice::Identity, ObjectInfo>::iterator q = _objects.find(p->proxy->ice_getIdentity());
        if(q != _objects.end())
        {
            q->second = *p;
            try
            {
                for(vector<ObjectObserverPrx>::const_iterator q = _publishers.begin(); q != _publishers.end(); ++q)
                {
                    (*q)->objectUpdated(*p, getContext(_serial));
                }
            }
            catch(const Ice::LocalException& ex)
            {
                Ice::Warning out(_logger);
                out << "unexpected exception while publishing `objectUpdated' update:\n" << ex;    
            }
        }
        else
        {
            _objects.insert(make_pair(p->proxy->ice_getIdentity(), *p));
            try
            {
                for(vector<ObjectObserverPrx>::const_iterator q = _publishers.begin(); q != _publishers.end(); ++q)
                {
                    (*q)->objectAdded(*p, getContext(_serial));
                }
            }
            catch(const Ice::LocalException& ex)
            {
                Ice::Warning out(_logger);
                out << "unexpected exception while publishing `objectAdded' update:\n" << ex;    
            }
        }
    }

    //
    // We don't wait for the update to be received by the replicas
    // here. This operation is called by ReplicaSessionI.
    // 
    addExpectedUpdate(_serial);
    //waitForSyncedSubscribersNoSync(_serial);
    return _serial;
}

int
ObjectObserverTopic::objectsRemoved(const ObjectInfoSeq& infos)
{
    Lock sync(*this);
    if(_topics.empty())
    {
        return -1;
    }
    updateSerial(_serial + 1);

    for(ObjectInfoSeq::const_iterator p = infos.begin(); p != infos.end(); ++p)
    {
        _objects.erase(p->proxy->ice_getIdentity());
        try
        {
            for(vector<ObjectObserverPrx>::const_iterator q = _publishers.begin(); q != _publishers.end(); ++q)
            {
                (*q)->objectRemoved(p->proxy->ice_getIdentity(), getContext(_serial));
            }
        }
        catch(const Ice::LocalException& ex)
        {
            Ice::Warning out(_logger);
            out << "unexpected exception while publishing `objectUpdated' update:\n" << ex;    
        }
    }

    //
    // We don't need to wait for the update to be received by the
    // replicas here. This operation is only called internaly by 
    // IceGrid.
    // 
    addExpectedUpdate(_serial);
    //waitForSyncedSubscribersNoSync(_serial);
    return _serial;
}

void 
ObjectObserverTopic::initObserver(const Ice::ObjectPrx& obsv)
{
    ObjectObserverPrx observer = ObjectObserverPrx::uncheckedCast(obsv);
    ObjectInfoSeq objects;
    for(map<Ice::Identity, ObjectInfo>::const_iterator p = _objects.begin(); p != _objects.end(); ++p)
    {
        objects.push_back(p->second);
    }
    observer->objectInit(objects, getContext(_serial));
}
