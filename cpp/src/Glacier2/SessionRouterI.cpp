// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Glacier2/PermissionsVerifier.h>
#include <Glacier2/Session.h>
#include <Glacier2/SessionRouterI.h>
#include <Glacier2/FilterManager.h>
#include <Glacier2/RouterI.h>

#include <IceUtil/UUID.h>

#include <IceSSL/IceSSL.h>
#include <Ice/Connection.h>
#include <Ice/Network.h>

using namespace std;
using namespace Ice;
using namespace Glacier2;

namespace Glacier2
{

class SessionControlI : public SessionControl
{
public:

    SessionControlI(const SessionRouterIPtr& sessionRouter, const ConnectionPtr& connection, 
                    const FilterManagerPtr& filterManager) :
        _sessionRouter(sessionRouter),
        _connection(connection),
        _filters(filterManager)
    {
    }

    virtual StringSetPrx
    categories(const Current&)
    {
        return _filters->categoriesPrx();
    }

    virtual StringSetPrx
    adapterIds(const Current&)
    {
        return _filters->adapterIdsPrx();
    }

    virtual IdentitySetPrx
    identities(const Current&)
    {
        return _filters->identitiesPrx(); 
    }

    virtual int
    getSessionTimeout(const Current& current)
    {
        return static_cast<int>(_sessionRouter->getSessionTimeout(current));
    }
    
    virtual void
    destroy(const Current&)
    {
        _sessionRouter->destroySession(_connection);
        _filters->destroy();
    }

private:

    const SessionRouterIPtr _sessionRouter;
    const ConnectionPtr _connection;
    const FilterManagerPtr _filters;
};

class ClientLocator : public ServantLocator
{
public:

    ClientLocator(const SessionRouterIPtr& sessionRouter) :
        _sessionRouter(sessionRouter)
    {
    }
    
    virtual ObjectPtr
    locate(const Current& current, LocalObjectPtr&)
    {
        return _sessionRouter->getClientBlobject(current.con, current.id);
    }

    virtual void
    finished(const Current&, const ObjectPtr&, const LocalObjectPtr&)
    {
    }

    virtual void
    deactivate(const std::string&)
    {
    }

private:

    const SessionRouterIPtr _sessionRouter;
};

class ServerLocator : public ServantLocator
{
public:

    ServerLocator(const SessionRouterIPtr& sessionRouter) :
        _sessionRouter(sessionRouter)
    {
    }
    
    virtual ObjectPtr
    locate(const Current& current, LocalObjectPtr&)
    {
        return _sessionRouter->getServerBlobject(current.id.category);
    }

    virtual void
    finished(const Current&, const ObjectPtr&, const LocalObjectPtr&)
    {
    }

    virtual void
    deactivate(const std::string&)
    {
    }

private:

    const SessionRouterIPtr _sessionRouter;
};

class UserPasswordCreateSession : public CreateSession
{
public:

    UserPasswordCreateSession(const AMD_Router_createSessionPtr& amdCB, const string& user, const string& password, 
                              const Ice::Current& current, const SessionRouterIPtr& sessionRouter) :
        CreateSession(sessionRouter, user, current),
        _amdCB(amdCB), 
        _password(password)
    {
    }
    

    void
    checkPermissionsResponse(bool ok, const string& reason)
    {
        if(ok)
        {
            authorized(_sessionRouter->_sessionManager);
        }
        else
        {
            exception(PermissionDeniedException(reason.empty() ? string("permission denied") : reason));
        }
    }

    void
    checkPermissionsException(const Ice::Exception& ex)
    {
        if(dynamic_cast<const PermissionDeniedException*>(&ex))
        {
            exception(ex);
        }
        else if(dynamic_cast<const CollocationOptimizationException*>(&ex))
        {
            authorizeCollocated();
        }
        else
        {
            unexpectedAuthorizeException(ex);
        }
    }

    virtual void
    authorize()
    {
        assert(_sessionRouter->_verifier);

        Ice::Context ctx = _current.ctx;
        ctx.insert(_context.begin(), _context.end());
        
        _sessionRouter->_verifier->begin_checkPermissions(_user, _password, ctx,
                                                          newCallback_PermissionsVerifier_checkPermissions(this,
                                                                &UserPasswordCreateSession::checkPermissionsResponse,
                                                                &UserPasswordCreateSession::checkPermissionsException));
    }

    virtual void
    authorizeCollocated()
    {
        try
        {
            string reason;
            Ice::Context ctx = _current.ctx;
            ctx.insert(_context.begin(), _context.end());
            if(_sessionRouter->_verifier->checkPermissions(_user, _password, reason, ctx))
            {
                authorized(_sessionRouter->_sessionManager);
            }
            else
            {
                exception(PermissionDeniedException(reason.empty() ? string("permission denied") : reason));
            }
        }
        catch(const Ice::Exception& ex)
        {
            unexpectedAuthorizeException(ex);
        }
    }

    virtual FilterManagerPtr
    createFilterManager()
    {
        return FilterManager::create(_instance, _user, true);
    }

    virtual void
    createSession()
    {
        Ice::Context ctx = _current.ctx;
        ctx.insert(_context.begin(), _context.end());
        _sessionRouter->_sessionManager->begin_create(_user, _control, ctx,
                                                      newCallback_SessionManager_create(
                                                                        static_cast<CreateSession*>(this),
                                                                        &CreateSession::sessionCreated, 
                                                                        &CreateSession::createException));
    }
    
    virtual void
    finished(const SessionPrx& session)
    {
        _amdCB->ice_response(session);
    }

    virtual void
    finished(const Ice::Exception& ex)
    {
        _amdCB->ice_exception(ex);
    }

private:

    const AMD_Router_createSessionPtr _amdCB;
    const string _password;
};

class SSLCreateSession : public CreateSession
{
public:

    SSLCreateSession(const AMD_Router_createSessionFromSecureConnectionPtr& amdCB, const string& user, 
                     const SSLInfo& sslInfo, const Ice::Current& current, const SessionRouterIPtr& sessionRouter) :
        CreateSession(sessionRouter, user, current),
        _amdCB(amdCB), 
        _sslInfo(sslInfo)
    {
    }
    
    void
    authorizeResponse(bool ok, const string& reason)
    {
        if(ok)
        {
            authorized(_sessionRouter->_sslSessionManager);
        }
        else
        {
            exception(PermissionDeniedException(reason.empty() ? string("permission denied") : reason));
        }
    }

    void
    authorizeException(const Ice::Exception& ex)
    {
        if(dynamic_cast<const PermissionDeniedException*>(&ex))
        {
            exception(ex);
        }
        else if(dynamic_cast<const CollocationOptimizationException*>(&ex))
        {
            authorizeCollocated();
        }
        else
        {
            unexpectedAuthorizeException(ex);
        }
    }

    virtual void
    authorize()
    {
        assert(_sessionRouter->_sslVerifier);

        Ice::Context ctx = _current.ctx;
        ctx.insert(_context.begin(), _context.end());
        _sessionRouter->_sslVerifier->begin_authorize(_sslInfo, ctx, 
                                                      newCallback_SSLPermissionsVerifier_authorize(this,
                                                                             &SSLCreateSession::authorizeResponse, 
                                                                             &SSLCreateSession::authorizeException));
    }

    virtual void
    authorizeCollocated()
    {
        try
        {
            string reason;
            Ice::Context ctx = _current.ctx;
            ctx.insert(_context.begin(), _context.end());
            if(_sessionRouter->_sslVerifier->authorize(_sslInfo, reason, ctx))
            {
                authorized(_sessionRouter->_sslSessionManager);
            }
            else
            {
                exception(PermissionDeniedException(reason.empty() ? string("permission denied") : reason));
            }
        }
        catch(const Ice::Exception& ex)
        {
            unexpectedAuthorizeException(ex);
        }
    }

    virtual FilterManagerPtr
    createFilterManager()
    {
        return FilterManager::create(_instance, _user, false);
    }

    virtual void
    createSession()
    {
        Ice::Context ctx = _current.ctx;
        ctx.insert(_context.begin(), _context.end());
        _sessionRouter->_sslSessionManager->begin_create(_sslInfo, _control, ctx,
                                                         newCallback_SSLSessionManager_create(
                                                                        static_cast<CreateSession*>(this),
                                                                        &CreateSession::sessionCreated, 
                                                                        &CreateSession::createException));
    }
    
    virtual void
    finished(const SessionPrx& session)
    {
        _amdCB->ice_response(session);
    }

    virtual void
    finished(const Ice::Exception& ex)
    {
        _amdCB->ice_exception(ex);
    }

private:

    const AMD_Router_createSessionFromSecureConnectionPtr _amdCB;
    const SSLInfo _sslInfo;
};

}

CreateSession::CreateSession(const SessionRouterIPtr& sessionRouter, const string& user, const Ice::Current& current) :
    _instance(sessionRouter->_instance),
    _sessionRouter(sessionRouter),
    _user(user),
    _current(current)
{
    if(_instance->properties()->getPropertyAsInt("Glacier2.AddConnectionContext") > 0)
    {
        _context["_con.type"] = current.con->type();
        {
            Ice::IPConnectionInfoPtr info = Ice::IPConnectionInfoPtr::dynamicCast(current.con->getInfo());
            if(info)
            {
                ostringstream os;
                os << info->remotePort;
                _context["_con.remotePort"] = os.str();
                _context["_con.remoteAddress"] = info->remoteAddress;
                os.str("");
                os << info->localPort;
                _context["_con.localPort"] = os.str();
                _context["_con.localAddress"] = info->localAddress;            }
        }
        {
            IceSSL::ConnectionInfoPtr info = IceSSL::ConnectionInfoPtr::dynamicCast(current.con->getInfo());
            if(info)
            {
                _context["_con.cipher"] = info->cipher;
                if(info->certs.size() > 0)
                {
                    _context["_con.peerCert"] = info->certs[0];
                }
            }
        }
    }
}

void
CreateSession::create()
{
    try
    {
        if(_sessionRouter->startCreateSession(this, _current.con))
        {
            authorize();
        }
    }
    catch(const Ice::Exception& ex)
    {
        finished(ex);
    }
}

void
CreateSession::addPendingCallback(const CreateSessionPtr& callback)
{
    _pendingCallbacks.push_back(callback);
}

void
CreateSession::authorized(bool createSession)
{
    //
    // Create the filter manager now as it's required for the session control object.
    //
    _filterManager = createFilterManager();

    //
    // If we have a session manager configured, we create a client-visible session object,
    // otherwise, we return a null session proxy.
    //
    if(createSession)
    {
        if(_instance->serverObjectAdapter())
        {
            Ice::ObjectPtr obj = new SessionControlI(_sessionRouter, _current.con, _filterManager);
            _control = SessionControlPrx::uncheckedCast(_instance->serverObjectAdapter()->addWithUUID(obj));
        }
        this->createSession();
    }
    else
    {
        sessionCreated(0);
    }
}

void
CreateSession::unexpectedAuthorizeException(const Ice::Exception& ex)
{
    if(_sessionRouter->sessionTraceLevel() >= 1)
    {
        Warning out(_instance->logger());
        out << "exception while verifying permissions:\n" << ex;
    }
    exception(PermissionDeniedException("internal server error"));
}

void
CreateSession::createException(const Ice::Exception& ex)
{
    try
    {
        ex.ice_throw();
    }
    catch(const CannotCreateSessionException& ex)
    {
        exception(ex);
    }
    catch(const Ice::Exception& ex)
    {
        unexpectedCreateSessionException(ex);
    }
}

void
CreateSession::sessionCreated(const SessionPrx& session)
{
    //
    // Create the session router object.
    //
    RouterIPtr router;
    try
    {
        Ice::Identity ident;
        if(_control)
        {
            ident = _control->ice_getIdentity();
        }

        if(_instance->properties()->getPropertyAsInt("Glacier2.AddConnectionContext") == 1 ||
           _instance->properties()->getPropertyAsInt("Glacier2.AddSSLContext") > 0)
        {
            //
            // DEPRECATED: Glacier2.AddSSLContext.
            //
            IceSSL::ConnectionInfoPtr info = IceSSL::ConnectionInfoPtr::dynamicCast(_current.con->getInfo());
            if(info && _instance->properties()->getPropertyAsInt("Glacier2.AddSSLContext") > 0)
            {
                _context["SSL.Active"] = "1";
                _context["SSL.Cipher"] = info->cipher;
                ostringstream os;
                os << info->remotePort;
                _context["SSL.Remote.Port"] = os.str();
                _context["SSL.Remote.Host"] = info->remoteAddress;
                os.str("");
                os << info->localPort;
                _context["SSL.Local.Port"] = os.str();
                _context["SSL.Local.Host"] = info->localAddress;
                if(info->certs.size() > 0)
                {
                    _context["SSL.PeerCert"] = info->certs[0];
                }
            }

            router = new RouterI(_instance, _current.con, _user, session, ident, _filterManager, _context);
        }
        else
        {
            router = new RouterI(_instance, _current.con, _user, session, ident, _filterManager, Ice::Context());
        }
    }
    catch(const Ice::Exception& ex)
    {
        if(session)
        {
            session->begin_destroy();
        }
        unexpectedCreateSessionException(ex);
        return;
    }

    //
    // Notify the router that the creation is finished.
    //
    try
    {    
        _sessionRouter->finishCreateSession(_current.con, router);
        finished(session);
    }
    catch(const Ice::Exception& ex)
    {
        finished(ex);
    }

    for(vector<CreateSessionPtr>::const_iterator p = _pendingCallbacks.begin(); p != _pendingCallbacks.end(); ++p)
    {
        (*p)->create();
    }
}

void
CreateSession::unexpectedCreateSessionException(const Ice::Exception& ex)
{
    if(_sessionRouter->sessionTraceLevel() >= 1)
    {
        Trace out(_instance->logger(), "Glacier2");
        out << "exception while creating session with session manager:\n" << ex;
    }
    exception(CannotCreateSessionException("internal server error"));
}

void
CreateSession::exception(const Ice::Exception& ex)
{
    try
    {    
        _sessionRouter->finishCreateSession(_current.con, 0);
    }
    catch(const Ice::Exception&)
    {
    }
        
    finished(ex);

    if(_control)
    {
        try
        {
            _instance->serverObjectAdapter()->remove(_control->ice_getIdentity());
        }
        catch(const Exception&)
        {
        }
    }

    for(vector<CreateSessionPtr>::const_iterator p = _pendingCallbacks.begin(); p != _pendingCallbacks.end(); ++p)
    {
        (*p)->create();
    }
}

SessionRouterI::SessionRouterI(const InstancePtr& instance,
                               const PermissionsVerifierPrx& verifier,
                               const SessionManagerPrx& sessionManager,
                               const SSLPermissionsVerifierPrx& sslVerifier,
                               const SSLSessionManagerPrx& sslSessionManager) :
    _instance(instance),
    _sessionTraceLevel(_instance->properties()->getPropertyAsInt("Glacier2.Trace.Session")),
    _rejectTraceLevel(_instance->properties()->getPropertyAsInt("Glacier2.Client.Trace.Reject")),
    _verifier(verifier),
    _sessionManager(sessionManager),
    _sslVerifier(sslVerifier),
    _sslSessionManager(sslSessionManager),
    _sessionTimeout(IceUtil::Time::seconds(_instance->properties()->getPropertyAsInt("Glacier2.SessionTimeout"))),
    _sessionThread(_sessionTimeout > IceUtil::Time() ? new SessionThread(this, _sessionTimeout) : 0),
    _routersByConnectionHint(_routersByConnection.end()),
    _routersByCategoryHint(_routersByCategory.end()),
    _sessionPingCallback(newCallback_Object_ice_ping(this, &SessionRouterI::sessionPingException)),
    _sessionDestroyCallback(newCallback_Session_destroy(this, &SessionRouterI::sessionDestroyException)),
    _destroy(false)
{

    //
    // This session router is used directly as servant for the main
    // Glacier2 router Ice object.
    //
    Identity routerId;
    routerId.category = _instance->properties()->getPropertyWithDefault("Glacier2.InstanceName", "Glacier2");
    routerId.name = "router";

    if(_sessionThread)
    {
        __setNoDelete(true);
        try
        {
            _sessionThread->start();
        }
        catch(const IceUtil::Exception&)
        {
            _sessionThread->destroy();
            _sessionThread = 0;
            __setNoDelete(false);
            throw;
        }
        __setNoDelete(false);
    }

    try
    {
        _instance->clientObjectAdapter()->add(this, routerId);
        
        //
        // All other calls on the client object adapter are dispatched to
        // a router servant based on connection information.
        //
        _instance->clientObjectAdapter()->addServantLocator(new ClientLocator(this), "");
        
        //
        // If there is a server object adapter, all calls on this adapter
        // are dispatched to a router servant based on the category field
        // of the identity.
        //
        if(_instance->serverObjectAdapter())
        {
            _instance->serverObjectAdapter()->addServantLocator(new ServerLocator(this), "");
        }
    }
    catch(const Ice::ObjectAdapterDeactivatedException&)
    {
        // Ignore.
    }

    _instance->setSessionRouter(this);
}

SessionRouterI::~SessionRouterI()
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

    assert(_destroy);
    assert(_routersByConnection.empty());
    assert(_routersByCategory.empty());
    assert(_pending.empty());
    assert(!_sessionThread);
}

void
SessionRouterI::destroy()
{
    map<ConnectionPtr, RouterIPtr> routers;
    SessionThreadPtr sessionThread;
    Callback_Session_destroyPtr destroyCallback;
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        
        assert(!_destroy);
        _destroy = true;
        notify();
        
        _routersByConnection.swap(routers);
        _routersByConnectionHint = _routersByConnection.end();
        
        _routersByCategory.clear();
        _routersByCategoryHint = _routersByCategory.end();
        
        sessionThread = _sessionThread;
        _sessionThread = 0;

        swap(destroyCallback, _sessionDestroyCallback); // Break cyclic reference count.
        _sessionPingCallback = 0; // Break cyclic reference count.
    }

    //
    // We destroy the routers outside the thread synchronization, to
    // avoid deadlocks.
    //
    for(map<ConnectionPtr, RouterIPtr>::iterator p = routers.begin(); p != routers.end(); ++p)
    {
        p->second->destroy(destroyCallback);
    }

    if(sessionThread)
    {
        sessionThread->destroy();
        sessionThread->getThreadControl().join();
    }
}

ObjectPrx
SessionRouterI::getClientProxy(const Current& current) const
{
    return getRouter(current.con, current.id)->getClientProxy(current); // Forward to the per-client router.
}

ObjectPrx
SessionRouterI::getServerProxy(const Current& current) const
{
    return getRouter(current.con, current.id)->getServerProxy(current); // Forward to the per-client router.
}

void
SessionRouterI::addProxy(const ObjectPrx& proxy, const Current& current)
{
    ObjectProxySeq seq;
    seq.push_back(proxy);
    addProxies(seq, current);
}

ObjectProxySeq
SessionRouterI::addProxies(const ObjectProxySeq& proxies, const Current& current)
{
    //
    // Forward to the per-client router.
    //
    return getRouter(current.con, current.id)->addProxies(proxies, current);
}

string
SessionRouterI::getCategoryForClient(const Ice::Current& current) const
{
    // Forward to the per-client router.
    if(_instance->serverObjectAdapter())
    {
        return getRouter(current.con, current.id)->getServerProxy(current)->ice_getIdentity().category;
    }
    else
    {
        return "";
    }
}

void
SessionRouterI::createSession_async(const AMD_Router_createSessionPtr& amdCB, const std::string& userId, 
                                              const std::string& password, const Current& current)
{
    if(!_verifier)
    {
        amdCB->ice_exception(PermissionDeniedException("no configured permissions verifier"));
        return;
    }

    CreateSessionPtr session = new UserPasswordCreateSession(amdCB, userId, password, current, this);
    session->create();
}

void
SessionRouterI::createSessionFromSecureConnection_async(
    const AMD_Router_createSessionFromSecureConnectionPtr& amdCB, const Current& current)
{
    if(!_sslVerifier)
    {
        amdCB->ice_exception(PermissionDeniedException("no configured ssl permissions verifier"));
        return;
    }

    string userDN;
    SSLInfo sslinfo;

    //
    // Populate the SSL context information.
    //
    try
    {
        IceSSL::ConnectionInfoPtr info = IceSSL::ConnectionInfoPtr::dynamicCast(current.con->getInfo());
        if(!info)
        {
            amdCB->ice_exception(PermissionDeniedException("not ssl connection"));
            return;
        }
        sslinfo.remotePort = info->remotePort;
        sslinfo.remoteHost = info->remoteAddress;
        sslinfo.localPort = info->localPort;
        sslinfo.localHost = info->localAddress;
        sslinfo.cipher = info->cipher;
        sslinfo.certs = info->certs;
        if(info->certs.size() > 0)
        {
            userDN = IceSSL::Certificate::decode(info->certs[0])->getSubjectDN();
        }
    }
    catch(const IceSSL::CertificateEncodingException&)
    {
        amdCB->ice_exception(PermissionDeniedException("certificate encoding exception"));
        return;
    }
    catch(const Ice::LocalException&)
    {
        amdCB->ice_exception(PermissionDeniedException("connection exception"));
        return;
    }

    CreateSessionPtr session = new SSLCreateSession(amdCB, userDN, sslinfo, current, this);
    session->create();
}

void
SessionRouterI::destroySession(const Current& current)
{
    destroySession(current.con);
}

void
SessionRouterI::refreshSession(const Ice::Current& current)
{
    RouterIPtr router = getRouter(current.con, current.id, false); // getRouter updates the session timestamp.
    if(!router)
    {
        throw SessionNotExistException();
    }

    //
    // Ping the session to ensure it does not timeout.
    //
    assert(_sessionPingCallback);
    SessionPrx session = router->getSession();
    if(session)
    {
        session->begin_ice_ping(_sessionPingCallback, current.con);
    }
}

void
SessionRouterI::destroySession(const ConnectionPtr& connection)
{
    RouterIPtr router;

    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        
        if(_destroy)
        {
            throw ObjectNotExistException(__FILE__, __LINE__);
        }
        
        map<ConnectionPtr, RouterIPtr>::iterator p;    
        
        if(_routersByConnectionHint != _routersByConnection.end() && _routersByConnectionHint->first == connection)
        {
            p = _routersByConnectionHint;
        }
        else
        {
            p = _routersByConnection.find(connection);
        }
        
        if(p == _routersByConnection.end())
        {
            throw SessionNotExistException();
        }
        
        router = p->second;

        _routersByConnection.erase(p++);
        _routersByConnectionHint = p;
        
        if(_instance->serverObjectAdapter())
        {
            string category = router->getServerProxy(Current())->ice_getIdentity().category;
            assert(!category.empty());
            _routersByCategory.erase(category);
            _routersByCategoryHint = _routersByCategory.end();
        }
    }

    //
    // We destroy the router outside the thread synchronization, to
    // avoid deadlocks.
    //
    if(_sessionTraceLevel >= 1)
    {
        Trace out(_instance->logger(), "Glacier2");
        out << "destroying session\n" << router->toString();
    }
    router->destroy(_sessionDestroyCallback);
}

Ice::Long
SessionRouterI::getSessionTimeout(const Ice::Current&) const
{
    return _sessionTimeout.toSeconds();
}

void 
SessionRouterI::updateSessionObservers()
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

    Glacier2::Instrumentation::RouterObserverPtr observer = _instance->getObserver();
    assert(observer);

    for(map<ConnectionPtr, RouterIPtr>::iterator p = _routersByConnection.begin(); p != _routersByConnection.end(); ++p)
    {
        p->second->updateObserver(observer);
    }   
}

RouterIPtr
SessionRouterI::getRouter(const ConnectionPtr& connection, const Ice::Identity& id, bool close) const
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
    return getRouterImpl(connection, id, close);
}

Ice::ObjectPtr
SessionRouterI::getClientBlobject(const ConnectionPtr& connection, const Ice::Identity& id) const
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
    return getRouterImpl(connection, id, true)->getClientBlobject();
}

Ice::ObjectPtr
SessionRouterI::getServerBlobject(const string& category) const
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

    if(_destroy)
    {
        throw ObjectNotExistException(__FILE__, __LINE__);
    }

    map<string, RouterIPtr>& routers = const_cast<map<string, RouterIPtr>&>(_routersByCategory);

    if(_routersByCategoryHint != routers.end() && _routersByCategoryHint->first == category)
    {
        return _routersByCategoryHint->second->getServerBlobject();
    }
    
    map<string, RouterIPtr>::iterator p = routers.find(category);

    if(p != routers.end())
    {
        _routersByCategoryHint = p;
        return p->second->getServerBlobject();
    }
    else
    {
        throw ObjectNotExistException(__FILE__, __LINE__);
    }
}

void
SessionRouterI::expireSessions()
{
    vector<RouterIPtr> routers;
    
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        
        if(_destroy)
        {
            return;
        }
        
        assert(_sessionTimeout > IceUtil::Time());
        IceUtil::Time minTimestamp = IceUtil::Time::now(IceUtil::Time::Monotonic) - _sessionTimeout;
        
        map<ConnectionPtr, RouterIPtr>::iterator p = _routersByConnection.begin();
        
        while(p != _routersByConnection.end())
        {
            if(p->second->getTimestamp() < minTimestamp)
            {
                RouterIPtr router = p->second;
                routers.push_back(router);
                
                _routersByConnection.erase(p++);
                _routersByConnectionHint = p;
                
                if(_instance->serverObjectAdapter())
                {
                    string category = router->getServerProxy(Current())->ice_getIdentity().category;
                    assert(!category.empty());
                    _routersByCategory.erase(category);
                    _routersByCategoryHint = _routersByCategory.end();
                }
            }
            else
            {
                ++p;
            }
        }
    }
    
    //
    // We destroy the expired routers outside the thread
    // synchronization, to avoid deadlocks.
    //
    for(vector<RouterIPtr>::iterator p = routers.begin(); p != routers.end(); ++p)
    {
        if(_sessionTraceLevel >= 1)
        {
            Trace out(_instance->logger(), "Glacier2");
            out << "expiring session\n" << (*p)->toString();
        }
        (*p)->destroy(_sessionDestroyCallback);
    }
}

RouterIPtr
SessionRouterI::getRouterImpl(const ConnectionPtr& connection, const Ice::Identity& id, bool close) const
{
    if(_destroy)
    {
        throw ObjectNotExistException(__FILE__, __LINE__);
    }

    map<ConnectionPtr, RouterIPtr>& routers = const_cast<map<ConnectionPtr, RouterIPtr>&>(_routersByConnection);

    if(_routersByConnectionHint != routers.end() && _routersByConnectionHint->first == connection)
    {
        _routersByConnectionHint->second->updateTimestamp();
        return _routersByConnectionHint->second;
    }
    
    map<ConnectionPtr, RouterIPtr>::iterator p = routers.find(connection);

    if(p != routers.end())
    {
        _routersByConnectionHint = p;
        p->second->updateTimestamp();
        return p->second;
    }
    else if(close)
    {
        if(_rejectTraceLevel >= 1)
        {
            Trace out(_instance->logger(), "Glacier2");
            out << "rejecting request. no session is associated with the connection.\n";
            out << "identity: " << _instance->communicator()->identityToString(id);
        }
        connection->close(true);
        throw ObjectNotExistException(__FILE__, __LINE__);
    }
    return 0;
}

void
SessionRouterI::sessionPingException(const Ice::Exception&, const Ice::ConnectionPtr& con)
{
    destroySession(con);
}

void
SessionRouterI::sessionDestroyException(const Ice::Exception& ex)
{
    if(_sessionTraceLevel > 0)
    {
        Trace out(_instance->logger(), "Glacier2");
        out << "exception while destroying session\n" << ex;
    }
}


bool
SessionRouterI::startCreateSession(const CreateSessionPtr& cb, const ConnectionPtr& connection)
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        
    if(_destroy)
    {
        CannotCreateSessionException exc;
        exc.reason = "router is shutting down";
        throw exc;
    }

    //
    // Check whether a session already exists for the connection.
    //
    {
        map<ConnectionPtr, RouterIPtr>::iterator p;    
        if(_routersByConnectionHint != _routersByConnection.end() &&
           _routersByConnectionHint->first == connection)
        {
            p = _routersByConnectionHint;
        }
        else
        {
            p = _routersByConnection.find(connection);
        }
            
        if(p != _routersByConnection.end())
        {
            CannotCreateSessionException exc;
            exc.reason = "session exists";
            throw exc;
        }
    }

    map<ConnectionPtr, CreateSessionPtr>::iterator p = _pending.find(connection);
    if(p != _pending.end())
    {
        //
        // If some other thread is currently trying to create a
        // session, we wait until this thread is finished.
        //
        p->second->addPendingCallback(cb);
        return false;
    }
    else
    {
        //
        // No session exists yet, so we will try to create one. To
        // avoid that other threads try to create sessions for the
        // same connection, we add our endpoints to _pending.
        //
        _pending.insert(make_pair(connection, cb));
        return true;
    }
}

void
SessionRouterI::finishCreateSession(const ConnectionPtr& connection, const RouterIPtr& router)
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
    
    //
    // Signal other threads that we are done with trying to
    // establish a session for our connection;
    //
    _pending.erase(connection);
    notify();
    
    if(!router)
    {
        return;
    }

    if(_destroy)
    {
        router->destroy(_sessionDestroyCallback);

        CannotCreateSessionException exc;
        exc.reason = "router is shutting down";
        throw exc;
    }
    
    _routersByConnectionHint = _routersByConnection.insert(
        _routersByConnectionHint, pair<const ConnectionPtr, RouterIPtr>(connection, router));
    
    if(_instance->serverObjectAdapter())
    {
        string category = router->getServerProxy()->ice_getIdentity().category;
        assert(!category.empty());
        pair<map<string, RouterIPtr>::iterator, bool> rc = 
            _routersByCategory.insert(pair<const string, RouterIPtr>(category, router));
        assert(rc.second);
        _routersByCategoryHint = rc.first;
    }

    if(_sessionTraceLevel >= 1)
    {
        Trace out(_instance->logger(), "Glacier2");
        out << "created session\n" << router->toString();
    }
}

SessionRouterI::SessionThread::SessionThread(const SessionRouterIPtr& sessionRouter,
                                                       const IceUtil::Time& sessionTimeout) :
    IceUtil::Thread("Glacier2 session thread"),
    _sessionRouter(sessionRouter),
    _sessionTimeout(sessionTimeout)
{
}

SessionRouterI::SessionThread::~SessionThread()
{
    assert(!_sessionRouter);
}

void
SessionRouterI::SessionThread::destroy()
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
    _sessionRouter = 0;
    notify();
}

void
SessionRouterI::SessionThread::run()
{
    while(true)
    {
        SessionRouterIPtr sessionRouter;

        {
            IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

            if(!_sessionRouter)
            {
                return;
            }
            
            assert(_sessionTimeout > IceUtil::Time());
            timedWait(_sessionTimeout / 4);

            if(!_sessionRouter)
            {
                return;
            }

            sessionRouter = _sessionRouter;
        }

        sessionRouter->expireSessions();
    }
}
