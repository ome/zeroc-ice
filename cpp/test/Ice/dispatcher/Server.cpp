// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestI.h>
#include <TestCommon.h>
#include <Dispatcher.h>

DEFINE_TEST("server")

using namespace std;

int
run(int, char**, const Ice::CommunicatorPtr& communicator)
{
    communicator->getProperties()->setProperty("TestAdapter.Endpoints", "default -p 12010");
    communicator->getProperties()->setProperty("ControllerAdapter.Endpoints", "tcp -p 12011");
    communicator->getProperties()->setProperty("ControllerAdapter.ThreadPool.Size", "1");

    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("TestAdapter");
    Ice::ObjectAdapterPtr adapter2 = communicator->createObjectAdapter("ControllerAdapter");

    TestIntfControllerIPtr testController = new TestIntfControllerI(adapter);
    
    adapter->add(new TestIntfI(), communicator->stringToIdentity("test"));
    adapter->activate();
    
    adapter2->add(testController, communicator->stringToIdentity("testController"));
    adapter2->activate();

    TEST_READY

    communicator->waitForShutdown();
    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    int status;
    Ice::CommunicatorPtr communicator;

    try
    {
        Ice::InitializationData initData;
        initData.properties = Ice::createProperties(argc, argv);
#ifdef ICE_CPP11
        Ice::DispatcherPtr dispatcher = new Dispatcher();
        initData.dispatcher = Ice::newDispatcher(
            [=](const Ice::DispatcherCallPtr& call, const Ice::ConnectionPtr& conn)
                {
                    dispatcher->dispatch(call, conn);
                });
#else
        initData.dispatcher = new Dispatcher();
#endif
        communicator = Ice::initialize(argc, argv, initData);
        status = run(argc, argv, communicator);
    }
    catch(const Ice::Exception& ex)
    {
        cerr << ex << endl;
        status = EXIT_FAILURE;
    }

    if(communicator)
    {
        try
        {
            communicator->destroy();
        }
        catch(const Ice::Exception& ex)
        {
            cerr << ex << endl;
            status = EXIT_FAILURE;
        }
    }

    Dispatcher::terminate();
    return status;
}
