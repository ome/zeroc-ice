// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Ice/Locator.h>
#include <TestI.h>

using namespace Test;

ServerManagerI::ServerManagerI(const ServerLocatorRegistryPtr& registry,
                               const Ice::InitializationData& initData) :
    _registry(registry), _initData(initData), _nextPort(12011)
{
    _initData.properties->setProperty("TestAdapter.AdapterId", "TestAdapter");
    _initData.properties->setProperty("TestAdapter.ReplicaGroupId", "ReplicatedAdapter");    
    _initData.properties->setProperty("TestAdapter2.AdapterId", "TestAdapter2");
    _initData.properties->setProperty("Ice.PrintAdapterReady", "0");
}

void
ServerManagerI::startServer(const Ice::Current&)
{
    for(::std::vector<Ice::CommunicatorPtr>::const_iterator i = _communicators.begin(); i != _communicators.end(); ++i)
    {
        (*i)->waitForShutdown();
        (*i)->destroy();
    }
    _communicators.clear();

    //
    // Simulate a server: create a new communicator and object
    // adapter. The object adapter is started on a system allocated
    // port. The configuration used here contains the Ice.Locator
    // configuration variable. The new object adapter will register
    // its endpoints with the locator and create references containing
    // the adapter id instead of the endpoints.
    //
    Ice::CommunicatorPtr serverCommunicator = Ice::initialize(_initData);
    _communicators.push_back(serverCommunicator);

    //
    // Use fixed port to ensure that OA re-activation doesn't re-use previous port from
    // another OA (e.g.: TestAdapter2 is re-activated using port of TestAdapter).
    //
    {
        std::ostringstream os;
        os << "default -p " << _nextPort++;
        serverCommunicator->getProperties()->setProperty("TestAdapter.Endpoints", os.str());
    }
    {
        std::ostringstream os;
        os << "default -p " << _nextPort++;
        serverCommunicator->getProperties()->setProperty("TestAdapter2.Endpoints", os.str());
    }

    Ice::ObjectAdapterPtr adapter = serverCommunicator->createObjectAdapter("TestAdapter");
    Ice::ObjectAdapterPtr adapter2 = serverCommunicator->createObjectAdapter("TestAdapter2");

    Ice::ObjectPrx locator = serverCommunicator->stringToProxy("locator:default -p 12010");
    adapter->setLocator(Ice::LocatorPrx::uncheckedCast(locator));
    adapter2->setLocator(Ice::LocatorPrx::uncheckedCast(locator));

    Ice::ObjectPtr object = new TestI(adapter, adapter2, _registry);
    _registry->addObject(adapter->add(object, serverCommunicator->stringToIdentity("test")));
    _registry->addObject(adapter->add(object, serverCommunicator->stringToIdentity("test2")));
    adapter->add(object, serverCommunicator->stringToIdentity("test3"));

    adapter->activate();
    adapter2->activate();
}

void
ServerManagerI::shutdown(const Ice::Current& current)
{
    for(::std::vector<Ice::CommunicatorPtr>::const_iterator i = _communicators.begin(); i != _communicators.end(); ++i)
    {
        (*i)->destroy();
    }
    current.adapter->getCommunicator()->shutdown();
}


TestI::TestI(const Ice::ObjectAdapterPtr& adapter, 
             const Ice::ObjectAdapterPtr& adapter2, 
             const ServerLocatorRegistryPtr& registry) :
    _adapter1(adapter), _adapter2(adapter2), _registry(registry)
{
    _registry->addObject(_adapter1->add(new HelloI(), _adapter1->getCommunicator()->stringToIdentity("hello")));
}

void
TestI::shutdown(const Ice::Current&)
{
    _adapter1->getCommunicator()->shutdown();
}

HelloPrx
TestI::getHello(const Ice::Current&)
{
    return HelloPrx::uncheckedCast(_adapter1->createIndirectProxy(
                                        _adapter1->getCommunicator()->stringToIdentity("hello")));
}

HelloPrx
TestI::getReplicatedHello(const Ice::Current&)
{
    return HelloPrx::uncheckedCast(_adapter1->createProxy(_adapter1->getCommunicator()->stringToIdentity("hello")));
}

void
TestI::migrateHello(const Ice::Current&)
{
    const Ice::Identity id = _adapter1->getCommunicator()->stringToIdentity("hello");
    try
    {
        _registry->addObject(_adapter2->add(_adapter1->remove(id), id));
    }
    catch(Ice::NotRegisteredException&)
    {
        _registry->addObject(_adapter1->add(_adapter2->remove(id), id));
    }
}

void
HelloI::sayHello(const Ice::Current&)
{
}
