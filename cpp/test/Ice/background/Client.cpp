// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>
#include <Configuration.h>

using namespace std;
using namespace Test;

int
run(int, char**, const Ice::CommunicatorPtr& communicator)
{
    BackgroundPrx allTests(const Ice::CommunicatorPtr&);
    BackgroundPrx background = allTests(communicator);
    background->shutdown();
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

        //
        // For this test, we want to disable retries.
        //
        initData.properties->setProperty("Ice.RetryIntervals", "-1");

        //
        // This test kills connections, so we don't want warnings.
        //
        initData.properties->setProperty("Ice.Warn.Connections", "0");

        initData.properties->setProperty("Ice.MessageSizeMax", "50000");

        //
        // Setup the test transport plug-in.
        //
        initData.properties->setProperty("Ice.Plugin.Test", "TestTransport:createTestTransport");
        string defaultProtocol = initData.properties->getPropertyWithDefault("Ice.Default.Protocol", "tcp");
        initData.properties->setProperty("Ice.Default.Protocol", "test-" + defaultProtocol);

        communicator = Ice::initialize(argc, argv, initData);
        status = run(argc, argv, communicator);
    }
    catch(const Ice::Exception& ex)
    {
        cerr << ex << " " << ex.ice_stackTrace() << endl;
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

    return status;
}
