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
#include <TestI.h>

DEFINE_TEST("client")

using namespace std;
using namespace Test;

class MyObjectFactory : public Ice::ObjectFactory
{
public:

    virtual Ice::ObjectPtr create(const string& type)
    {
        if(type == "::Test::B")
        {
            return new BI;
        }
        else if(type == "::Test::C")
        {
            return new CI;
        }
        else if(type == "::Test::D")
        {
            return new DI;
        }
        else if(type == "::Test::E")
        {
            return new EI;
        }
        else if(type == "::Test::F")
        {
            return new FI;
        }
        else if(type == "::Test::I")
        {
            return new II;
        }
        else if(type == "::Test::J")
        {
            return new JI;
        }
        else if(type == "::Test::H")
        {
            return new HI;
        }

        assert(false); // Should never be reached
        return 0;
    }

    virtual void destroy()
    {
        // Nothing to do
    }
};

int
run(int, char**, const Ice::CommunicatorPtr& communicator)
{
    Ice::ObjectFactoryPtr factory = new MyObjectFactory;
    communicator->addObjectFactory(factory, "::Test::B");
    communicator->addObjectFactory(factory, "::Test::C");
    communicator->addObjectFactory(factory, "::Test::D");
    communicator->addObjectFactory(factory, "::Test::E");
    communicator->addObjectFactory(factory, "::Test::F");
    communicator->addObjectFactory(factory, "::Test::I");
    communicator->addObjectFactory(factory, "::Test::J");
    communicator->addObjectFactory(factory, "::Test::H");

    InitialPrx allTests(const Ice::CommunicatorPtr&, bool);
    InitialPrx initial = allTests(communicator, false);
    initial->shutdown();
    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    int status;
    Ice::CommunicatorPtr communicator;

    try
    {
        communicator = Ice::initialize(argc, argv);
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

    return status;
}
