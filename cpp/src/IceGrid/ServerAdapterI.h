// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_GRID_SERVER_ADAPTER_I_H
#define ICE_GRID_SERVER_ADAPTER_I_H

#include <IceUtil/Mutex.h>
#include <IceGrid/Internal.h>

namespace IceGrid
{

class NodeI;
typedef IceUtil::Handle<NodeI> NodeIPtr;

class ServerI;

class ServerAdapterI : public Adapter, public IceUtil::Mutex
{
public:
    
    ServerAdapterI(const NodeIPtr&, ServerI*, const std::string&, const AdapterPrx&, const std::string&, bool);
    virtual ~ServerAdapterI();

    virtual void activate_async(const AMD_Adapter_activatePtr& cb, const Ice::Current&);
    virtual Ice::ObjectPrx getDirectProxy(const Ice::Current& = Ice::Current()) const;
    virtual void setDirectProxy(const ::Ice::ObjectPrx&, const ::Ice::Current& = Ice::Current());
    void destroy();
    void updateEnabled();
    void clear();
    void activationFailed(const std::string&);
    void activationCompleted();

    AdapterPrx getProxy() const;

private:

    const NodeIPtr _node;
    const AdapterPrx _this;
    const std::string _serverId;
    const std::string _id;
    const std::string _replicaId;
    ServerI* _server;

    Ice::ObjectPrx _proxy;
    bool _enabled;
    std::vector<AMD_Adapter_activatePtr> _activateCB;
    bool _activateAfterDeactivating;
};
typedef IceUtil::Handle<ServerAdapterI> ServerAdapterIPtr;

}

#endif
