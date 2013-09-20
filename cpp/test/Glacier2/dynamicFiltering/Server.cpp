// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Application.h>
#include <Ice/Locator.h>
#include <Glacier2/PermissionsVerifier.h>
#include <TestControllerI.h>
#include <SessionI.h>
#include <BackendI.h>

using namespace std;
using namespace Ice;
using namespace Test;

//
// Dummy ServerLocatorRegistry, ServerLocator and ServantLocator. For
// simplicity, we essentially 'alias' all possible requests to a single
// object adapter and a single servant.
//
class ServerLocatorRegistry : virtual public LocatorRegistry
{
public:

    virtual void 
    setAdapterDirectProxy_async(const AMD_LocatorRegistry_setAdapterDirectProxyPtr& cb, const string&, 
                                const ObjectPrx&, const Current&)
    {
        cb->ice_response();
    }

    virtual void
    setReplicatedAdapterDirectProxy_async(const AMD_LocatorRegistry_setReplicatedAdapterDirectProxyPtr& cb,
                                          const string&, const string&, const ObjectPrx&, const Current&)
    {
        cb->ice_response();
    }

    virtual void
    setServerProcessProxy_async(const AMD_LocatorRegistry_setServerProcessProxyPtr& cb,
                                const string&, const ProcessPrx&, const Current&)
    {
        cb->ice_response();
    }
};

class ServerLocatorI : virtual public Locator
{
public:
    ServerLocatorI(BackendPtr backend, ObjectAdapterPtr adapter) :
        _backend(backend),
        _adapter(adapter)
    {
        _registryPrx = LocatorRegistryPrx::uncheckedCast(adapter->add(new ServerLocatorRegistry, 
                                                        _adapter->getCommunicator()->stringToIdentity("registry")));
    }

    virtual void
    findObjectById_async(const AMD_Locator_findObjectByIdPtr& cb, const Identity& id, const Current&) const 
    { 
        cb->ice_response(_adapter->createProxy(id));
    }    

    virtual void
    findAdapterById_async(const AMD_Locator_findAdapterByIdPtr& cb, const string&, const Current&) const 
    {
       cb->ice_response(_adapter->createDirectProxy(_adapter->getCommunicator()->stringToIdentity("dummy")));   
    }

    virtual LocatorRegistryPrx 
    getRegistry(const Current&) const 
    { 
        return _registryPrx;
    }

private:
    BackendPtr _backend;
    ObjectAdapterPtr _adapter;
    LocatorRegistryPrx _registryPrx;
};

class ServantLocatorI : virtual public ServantLocator
{
public:

    ServantLocatorI(const BackendPtr& backend) :
        _backend(backend)
    {
    }
        
    virtual ObjectPtr locate(const Current&, LocalObjectPtr&)
    {
        return _backend;
    }

    virtual void finished(const Current&, const ObjectPtr&, const LocalObjectPtr&)
    {
    }

    virtual void deactivate(const string&)
    {
    }

private:

    BackendPtr _backend;
};

class SessionControlServer : public Application
{
public:

    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
    SessionControlServer app;
    return app.main(argc, argv);
}

int
SessionControlServer::run(int, char*[])
{
    //
    // The server requires 3 separate server endpoints. One for the test
    // controller that will coordinate the tests and the required
    // configurations across the client and the router, an adapter for
    // the session manager for the router to communicate with and
    // finally, an adapter for the dummy backend server that the client
    // will ultimately attempt to make calls on. The backend uses a
    // servant locator that responds to each lookup with the same
    // servant, allowing us to use any reference as long as the client
    // expects to use a proxy for the correct type of object.
    //
    communicator()->getProperties()->setProperty("TestControllerAdapter.Endpoints", "tcp -p 12013");
    ObjectAdapterPtr controllerAdapter = communicator()->createObjectAdapter("TestControllerAdapter");
    TestControllerIPtr controller = new TestControllerI;
    controllerAdapter->add(controller, communicator()->stringToIdentity("testController"));
    controllerAdapter->activate();

    communicator()->getProperties()->setProperty("SessionControlAdapter.Endpoints", "tcp -p 12010");
    ObjectAdapterPtr adapter = communicator()->createObjectAdapter("SessionControlAdapter");
    adapter->add(new SessionManagerI(controller), communicator()->stringToIdentity("SessionManager"));
    adapter->activate();

    BackendPtr backend = new BackendI;
    communicator()->getProperties()->setProperty("BackendAdapter.Endpoints", "default -p 12012");
    ObjectAdapterPtr backendAdapter = communicator()->createObjectAdapter("BackendAdapter");
    backendAdapter->addServantLocator(new ServantLocatorI(backend), "");
    backendAdapter->activate();

    Ice::LocatorPtr locator = new ServerLocatorI(backend, backendAdapter);
    backendAdapter->add(locator, communicator()->stringToIdentity("locator"));

    communicator()->waitForShutdown();
    return EXIT_SUCCESS;
}
