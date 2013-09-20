// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Application.h>
#include <BackendI.h>

using namespace std;
using namespace Ice;
using namespace Test;

class ServantLocatorI : virtual public ServantLocator
{
public:

    ServantLocatorI() :
        _backend(new BackendI)
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

class BackendServer : public Application
{
public:

    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
    BackendServer app;
    return app.main(argc, argv);
}

int
BackendServer::run(int, char**)
{
    communicator()->getProperties()->setProperty("BackendAdapter.Endpoints", "tcp -p 12010");
    ObjectAdapterPtr adapter = communicator()->createObjectAdapter("BackendAdapter");
    adapter->addServantLocator(new ServantLocatorI, "");
    adapter->activate();
    communicator()->waitForShutdown();
    return EXIT_SUCCESS;
}
