// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Application.h>
#include <ServantLocatorI.h>
#include <TestCommon.h>
#include <TestAMDI.h>

using namespace std;
using namespace Ice;

class ServantLocatorAMDI : public Test::ServantLocatorI
{
public:

    ServantLocatorAMDI(const string& category) : Test::ServantLocatorI(category)
    {
    }

protected:

    virtual Ice::ObjectPtr
    newServantAndCookie(Ice::LocalObjectPtr& cookie) const
    {
        cookie = new CookieI();
        return new TestAMDI();
    }

    virtual void
    checkCookie(const Ice::LocalObjectPtr& cookie) const
    {
        Test::CookiePtr co = Test::CookiePtr::dynamicCast(cookie);
        test(co);
        test(co->message() == "blahblah");
    }

    virtual void
    throwTestIntfUserException() const
    {
        throw Test::TestIntfUserException();
    }
};

class TestActivationI : public Test::TestActivation
{
public:

    void activateServantLocator(bool activate, const Ice::Current& current)
    {
        if(activate)
        {
            current.adapter->addServantLocator(new ServantLocatorAMDI(""), "");
            current.adapter->addServantLocator(new ServantLocatorAMDI("category"), "category");
        }
        else
        {
            ServantLocatorPtr locator = current.adapter->removeServantLocator("");
            locator->deactivate("");
            locator = current.adapter->removeServantLocator("category");
            locator->deactivate("category");
        }
    }
};

class TestServer : public Application
{
public:

    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
    TestServer app;
    return app.main(argc, argv);
}

int
TestServer::run(int, char**)
{
    communicator()->getProperties()->setProperty("TestAdapter.Endpoints", "default -p 12010:udp");
    communicator()->getProperties()->setProperty("Ice.Warn.Dispatch", "0");

    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("TestAdapter");
    
    adapter->addServantLocator(new ServantLocatorAMDI(""), "");
    adapter->addServantLocator(new ServantLocatorAMDI("category"), "category");
    adapter->add(new TestAMDI, communicator()->stringToIdentity("asm"));
    adapter->add(new TestActivationI, communicator()->stringToIdentity("test/activation"));
    adapter->activate();
    adapter->waitForDeactivate();
    return EXIT_SUCCESS;
}
