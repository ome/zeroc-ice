// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_GRID_REGISTRYI_H
#define ICE_GRID_REGISTRYI_H

#include <IceUtil/Timer.h>
#include <IceGrid/Registry.h>
#include <IceGrid/Query.h>
#include <IceGrid/Locator.h>
#include <IceGrid/Internal.h>
#include <IceGrid/PlatformInfo.h>
#include <IceGrid/ReplicaSessionManager.h>
#include <Glacier2/PermissionsVerifierF.h>
#include <IceStorm/Service.h>

namespace IceGrid
{

class Database;
typedef IceUtil::Handle<Database> DatabasePtr;

class WellKnownObjectsManager;
typedef IceUtil::Handle<WellKnownObjectsManager> WellKnownObjectsManagerPtr;

class TraceLevels;
typedef IceUtil::Handle<TraceLevels> TraceLevelsPtr;

class ReapThread;
typedef IceUtil::Handle<ReapThread> ReapThreadPtr;    

class SessionServantManager;
typedef IceUtil::Handle<SessionServantManager> SessionServantManagerPtr;    

class ClientSessionFactory;
typedef IceUtil::Handle<ClientSessionFactory> ClientSessionFactoryPtr;    

class AdminSessionFactory;
typedef IceUtil::Handle<AdminSessionFactory> AdminSessionFactoryPtr;    

std::string getInstanceName(const Ice::CommunicatorPtr&);

class RegistryI : public Registry
{
public:

    RegistryI(const Ice::CommunicatorPtr&, const TraceLevelsPtr&, bool, bool, const std::string&);
    ~RegistryI();

    bool start();
    bool startImpl();
    void stop();

    virtual SessionPrx createSession(const std::string&, const std::string&, const Ice::Current&);
    virtual AdminSessionPrx createAdminSession(const std::string&, const std::string&, const Ice::Current&);

    virtual SessionPrx createSessionFromSecureConnection(const Ice::Current&);
    virtual AdminSessionPrx createAdminSessionFromSecureConnection(const Ice::Current&);

    virtual int getSessionTimeout(const Ice::Current& = Ice::Current()) const;
    
    std::string getName() const;
    RegistryInfo getInfo() const;

    void waitForShutdown();
    virtual void shutdown();
    
    std::string getServerAdminCategory() const { return _instanceName + "-RegistryRouter"; }

    Ice::ObjectPrx createAdminCallbackProxy(const Ice::Identity&) const;

private:

    Ice::LocatorRegistryPrx setupLocatorRegistry(const Ice::ObjectAdapterPtr&); 
    LocatorPrx setupLocator(const Ice::ObjectAdapterPtr&, const Ice::ObjectAdapterPtr&, const Ice::LocatorRegistryPrx&,
                            const RegistryPrx&, const QueryPrx&); 
    QueryPrx setupQuery(const Ice::ObjectAdapterPtr&);
    RegistryPrx setupRegistry(const Ice::ObjectAdapterPtr&);
    InternalRegistryPrx setupInternalRegistry(const Ice::ObjectAdapterPtr&);
    void setupNullPermissionsVerifier(const Ice::ObjectAdapterPtr&);
    bool setupUserAccountMapper(const Ice::ObjectAdapterPtr&);
    Ice::ObjectAdapterPtr setupClientSessionFactory(const Ice::ObjectAdapterPtr&, const LocatorPrx&);
    Ice::ObjectAdapterPtr setupAdminSessionFactory(const Ice::ObjectAdapterPtr&, const Ice::ObjectPtr&, 
                                                   const LocatorPrx&);

    Glacier2::PermissionsVerifierPrx getPermissionsVerifier(const Ice::ObjectAdapterPtr&, const LocatorPrx&,
                                                            const std::string&, const std::string&);

    Glacier2::SSLPermissionsVerifierPrx getSSLPermissionsVerifier(const LocatorPrx&, const std::string&);
    Glacier2::SSLInfo getSSLInfo(const Ice::ConnectionPtr&, std::string&);

    NodePrxSeq registerReplicas(const InternalRegistryPrx&, const NodePrxSeq&);
    void registerNodes(const InternalRegistryPrx&, const NodePrxSeq&);
    
    const Ice::CommunicatorPtr _communicator;
    const TraceLevelsPtr _traceLevels;
    const bool _nowarn;
    const bool _readonly;
    const std::string _initFromReplica;

    DatabasePtr _database;
    Ice::ObjectAdapterPtr _clientAdapter;
    Ice::ObjectAdapterPtr _serverAdapter;
    WellKnownObjectsManagerPtr _wellKnownObjects;
    std::string _instanceName;
    bool _master;
    std::string _replicaName;
    ReapThreadPtr _reaper;
    IceUtil::TimerPtr _timer;
    SessionServantManagerPtr _servantManager;
    int _sessionTimeout;
    ReplicaSessionManager _session;
    mutable PlatformInfo _platform;

    Glacier2::PermissionsVerifierPrx _nullPermissionsVerifier;
    Glacier2::SSLPermissionsVerifierPrx _nullSSLPermissionsVerifier;

    ClientSessionFactoryPtr _clientSessionFactory;
    Glacier2::PermissionsVerifierPrx _clientVerifier;
    Glacier2::SSLPermissionsVerifierPrx _sslClientVerifier;

    AdminSessionFactoryPtr _adminSessionFactory;
    Glacier2::PermissionsVerifierPrx _adminVerifier;
    Glacier2::SSLPermissionsVerifierPrx _sslAdminVerifier;

    IceStormInternal::ServicePtr _iceStorm;
};
typedef IceUtil::Handle<RegistryI> RegistryIPtr;

}

#endif
