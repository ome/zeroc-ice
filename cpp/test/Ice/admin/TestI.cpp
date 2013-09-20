// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <TestI.h>
#include <Ice/Ice.h>

using namespace std;

RemoteCommunicatorI::RemoteCommunicatorI(const Ice::CommunicatorPtr& communicator) :
    _communicator(communicator), _called(false)
{
}

Ice::ObjectPrx
RemoteCommunicatorI::getAdmin(const Ice::Current&)
{
    return _communicator->getAdmin();
}

Ice::PropertyDict
RemoteCommunicatorI::getChanges(const Ice::Current&)
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);

    //
    // The client calls PropertiesAdmin::setProperties() and then invokes
    // this operation. Since setProperties() is implemented using AMD, the
    // client might receive its reply and then call getChanges() before our
    // updated() method is called. We block here to ensure that updated()
    // gets called before we return the most recent set of changes.
    //
    while(!_called)
    {
        wait();
    }

    _called = false;

    return _changes;
}

void
RemoteCommunicatorI::shutdown(const Ice::Current&)
{
    _communicator->shutdown();
}

void
RemoteCommunicatorI::waitForShutdown(const Ice::Current&)
{
    //
    // Note that we are executing in a thread of the *main* communicator,
    // not the one that is being shut down.
    //
    _communicator->waitForShutdown();
}

void
RemoteCommunicatorI::destroy(const Ice::Current&)
{
    _communicator->destroy();
}

void
RemoteCommunicatorI::updated(const Ice::PropertyDict& changes)
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);

    _changes = changes;
    _called = true;
    notify();
}

Test::RemoteCommunicatorPrx
RemoteCommunicatorFactoryI::createCommunicator(const Ice::PropertyDict& props, const Ice::Current& current)
{
    //
    // Prepare the property set using the given properties.
    //
    Ice::InitializationData init;
    init.properties = Ice::createProperties();
    for(Ice::PropertyDict::const_iterator p = props.begin(); p != props.end(); ++p)
    {
        init.properties->setProperty(p->first, p->second);
    }

    //
    // Initialize a new communicator.
    //
    Ice::CommunicatorPtr communicator = Ice::initialize(init);

    //
    // Install a custom admin facet.
    //
    communicator->addAdminFacet(new TestFacetI, "TestFacet");

    //
    // The RemoteCommunicator servant also implements PropertiesAdminUpdateCallback.
    // Set the callback on the admin facet.
    //
    RemoteCommunicatorIPtr servant = new RemoteCommunicatorI(communicator);
    Ice::ObjectPtr propFacet = communicator->findAdminFacet("Properties");
    if(propFacet)
    {
        Ice::NativePropertiesAdminPtr admin = Ice::NativePropertiesAdminPtr::dynamicCast(propFacet);
        assert(admin);
        admin->addUpdateCallback(servant);
    }

    Ice::ObjectPrx proxy = current.adapter->addWithUUID(servant);
    return Test::RemoteCommunicatorPrx::uncheckedCast(proxy);
}

void
RemoteCommunicatorFactoryI::shutdown(const Ice::Current& current)
{
    current.adapter->getCommunicator()->shutdown();
}
