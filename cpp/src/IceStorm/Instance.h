// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef INSTANCE_H
#define INSTANCE_H


#include <Ice/CommunicatorF.h>
#include <Ice/ObjectAdapterF.h>
#include <Ice/PropertiesF.h>
#include <IceUtil/Time.h>
#include <IceStorm/Election.h>
#include <IceStorm/Instrumentation.h>

namespace IceUtil
{

class Timer;
typedef IceUtil::Handle<Timer> TimerPtr;

}

namespace IceStormElection
{

class Observers;
typedef IceUtil::Handle<Observers> ObserversPtr;

class NodeI;
typedef IceUtil::Handle<NodeI> NodeIPtr;

}

namespace IceStorm
{

class TraceLevels;
typedef IceUtil::Handle<TraceLevels> TraceLevelsPtr;

class ConnectionPool;
typedef IceUtil::Handle<ConnectionPool> ConnectionPoolPtr;

class Instance : public IceUtil::Shared
{
public:

    Instance(const std::string&, const std::string&, const Ice::CommunicatorPtr&, const ConnectionPoolPtr&, 
             const Ice::ObjectAdapterPtr&, const Ice::ObjectAdapterPtr&, const Ice::ObjectAdapterPtr& = 0,
             const IceStormElection::NodePrx& = 0);
    ~Instance();

    void setNode(const IceStormElection::NodeIPtr&);

    std::string instanceName() const;
    std::string serviceName() const;
    Ice::CommunicatorPtr communicator() const;
    Ice::PropertiesPtr properties() const;
    Ice::ObjectAdapterPtr publishAdapter() const;
    Ice::ObjectAdapterPtr topicAdapter() const;
    Ice::ObjectAdapterPtr nodeAdapter() const;
    IceStormElection::ObserversPtr observers() const;
    IceStormElection::NodeIPtr node() const;
    IceStormElection::NodePrx nodeProxy() const;
    TraceLevelsPtr traceLevels() const;
    IceUtil::TimerPtr batchFlusher() const;
    IceUtil::TimerPtr timer() const;
    Ice::ObjectPrx topicReplicaProxy() const;
    Ice::ObjectPrx publisherReplicaProxy() const;
    ConnectionPoolPtr connectionPool() const;
    IceStorm::Instrumentation::TopicManagerObserverPtr observer() const;

    IceUtil::Time discardInterval() const;
    IceUtil::Time flushInterval() const;
    int sendTimeout() const;

    void shutdown();
    void destroy();

private:

    const std::string _instanceName;
    const std::string _serviceName;
    const Ice::CommunicatorPtr _communicator;
    const Ice::ObjectAdapterPtr _publishAdapter;
    const Ice::ObjectAdapterPtr _topicAdapter;
    const Ice::ObjectAdapterPtr _nodeAdapter;
    const IceStormElection::NodePrx _nodeProxy;
    const TraceLevelsPtr _traceLevels;
    const IceUtil::Time _discardInterval;
    const IceUtil::Time _flushInterval;
    const int _sendTimeout;
    const Ice::ObjectPrx _topicReplicaProxy;
    const Ice::ObjectPrx _publisherReplicaProxy;
    const ConnectionPoolPtr _connectionPool;
    IceStormElection::NodeIPtr _node;
    IceStormElection::ObserversPtr _observers;
    IceUtil::TimerPtr _batchFlusher;
    IceUtil::TimerPtr _timer;
    IceStorm::Instrumentation::TopicManagerObserverPtr _observer;
};
typedef IceUtil::Handle<Instance> InstancePtr;

} // End namespace IceStorm

#endif
