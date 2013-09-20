// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEGRID_TOPICS_H
#define ICEGRID_TOPICS_H

#include <IceUtil/Mutex.h>
#include <IceStorm/IceStorm.h>
#include <IceGrid/Internal.h>
#include <IceGrid/Observer.h>
#include <set>

namespace IceGrid
{

class ObserverTopic : public IceUtil::Monitor<IceUtil::Mutex>, virtual public Ice::Object
{
public:

    ObserverTopic(const IceStorm::TopicManagerPrx&, const std::string&);
    virtual ~ObserverTopic();

    int subscribe(const Ice::ObjectPrx&, const std::string& = std::string());
    void unsubscribe(const Ice::ObjectPrx&, const std::string& = std::string());
    void destroy();

    void receivedUpdate(const std::string&, int, const std::string&);

    virtual void initObserver(const Ice::ObjectPrx&) = 0;

    void waitForSyncedSubscribers(int, const std::string& = std::string());

protected:

    void addExpectedUpdate(int, const std::string& = std::string());
    void waitForSyncedSubscribersNoSync(int, const std::string& = std::string());
    void updateSerial(int);
    Ice::Context getContext(int) const;

    template<typename T> std::vector<T> getPublishers() const
    {
        std::vector<T> publishers;
        for(std::vector<Ice::ObjectPrx>::const_iterator p = _basePublishers.begin(); p != _basePublishers.end(); ++p)
        {
            publishers.push_back(T::uncheckedCast(*p));
        }
        return publishers;
    }

    Ice::LoggerPtr _logger;
    std::map<Ice::EncodingVersion, IceStorm::TopicPrx> _topics;
    std::vector<Ice::ObjectPrx> _basePublishers;
    int _serial;

    std::set<std::string> _syncSubscribers;
    std::map<int, std::set<std::string> > _waitForUpdates;
    std::map<int, std::map<std::string, std::string> > _updateFailures;
};
typedef IceUtil::Handle<ObserverTopic> ObserverTopicPtr;

class RegistryObserverTopic : public ObserverTopic
{
public:

    RegistryObserverTopic(const IceStorm::TopicManagerPrx&);

    void registryUp(const RegistryInfo&);
    void registryDown(const std::string&);

    virtual void initObserver(const Ice::ObjectPrx&);

private:

    std::vector<RegistryObserverPrx> _publishers;
    std::map<std::string, RegistryInfo> _registries;
};
typedef IceUtil::Handle<RegistryObserverTopic> RegistryObserverTopicPtr;

class NodeObserverTopic : public ObserverTopic, public NodeObserver
{
public:
    
    NodeObserverTopic(const IceStorm::TopicManagerPrx&, const Ice::ObjectAdapterPtr&);

    virtual void nodeInit(const NodeDynamicInfoSeq&, const Ice::Current&);
    virtual void nodeUp(const NodeDynamicInfo&, const Ice::Current&);
    virtual void nodeDown(const std::string&, const Ice::Current&);
    virtual void updateServer(const std::string&, const ServerDynamicInfo&, const Ice::Current&);
    virtual void updateAdapter(const std::string&, const AdapterDynamicInfo&, const Ice::Current&);

    const NodeObserverPrx& getPublisher() { return _externalPublisher; }

    void nodeDown(const std::string&);
    virtual void initObserver(const Ice::ObjectPrx&);

private:

    const NodeObserverPrx _externalPublisher;
    std::vector<NodeObserverPrx> _publishers;
    std::map<std::string, NodeDynamicInfo> _nodes;
};
typedef IceUtil::Handle<NodeObserverTopic> NodeObserverTopicPtr;

class ApplicationObserverTopic : public ObserverTopic
{
public:

    ApplicationObserverTopic(const IceStorm::TopicManagerPrx&, const std::map<std::string, ApplicationInfo>&);

    int applicationInit(int, const ApplicationInfoSeq&);
    int applicationAdded(int, const ApplicationInfo&);
    int applicationRemoved(int, const std::string&);
    int applicationUpdated(int, const ApplicationUpdateInfo&);

    virtual void initObserver(const Ice::ObjectPrx&);

private:

    std::vector<ApplicationObserverPrx> _publishers;
    std::map<std::string, ApplicationInfo> _applications;
};
typedef IceUtil::Handle<ApplicationObserverTopic> ApplicationObserverTopicPtr;

class AdapterObserverTopic : public ObserverTopic
{
public:

    AdapterObserverTopic(const IceStorm::TopicManagerPrx&, const std::map<std::string, AdapterInfo>&);

    int adapterInit(const AdapterInfoSeq&);
    int adapterAdded(const AdapterInfo&);
    int adapterUpdated(const AdapterInfo&);
    int adapterRemoved(const std::string&);

    virtual void initObserver(const Ice::ObjectPrx&);

private:

    std::vector<AdapterObserverPrx> _publishers;
    std::map<std::string, AdapterInfo> _adapters;
};
typedef IceUtil::Handle<AdapterObserverTopic> AdapterObserverTopicPtr;

class ObjectObserverTopic : public ObserverTopic
{
public:

    ObjectObserverTopic(const IceStorm::TopicManagerPrx&, const std::map<Ice::Identity, ObjectInfo>&);

    int objectInit(const ObjectInfoSeq&);
    int objectAdded(const ObjectInfo&);
    int objectUpdated(const ObjectInfo&);
    int objectRemoved(const Ice::Identity&);

    int objectsAddedOrUpdated(const ObjectInfoSeq&);
    int objectsRemoved(const ObjectInfoSeq&);

    virtual void initObserver(const Ice::ObjectPrx&);

private:

    std::vector<ObjectObserverPrx> _publishers;
    std::map<Ice::Identity, ObjectInfo> _objects;
};
typedef IceUtil::Handle<ObjectObserverTopic> ObjectObserverTopicPtr;

};

#endif
