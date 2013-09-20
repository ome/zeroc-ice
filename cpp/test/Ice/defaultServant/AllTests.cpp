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

using namespace std;
using namespace Test;

void
allTests(const Ice::CommunicatorPtr& communicator)
{
    Ice::ObjectAdapterPtr oa = communicator->createObjectAdapterWithEndpoints("MyOA", "tcp -h localhost");
    oa->activate();

    Ice::ObjectPtr servant = new MyObjectI();

    //
    // Register default servant with category "foo"
    //
    oa->addDefaultServant(servant, "foo");

    //
    // Start test
    //
    cout << "testing single category... " << flush;

    Ice::ObjectPtr r = oa->findDefaultServant("foo");
    test(r == servant);

    r = oa->findDefaultServant("bar");
    test(r == 0);

    Ice::Identity identity;
    identity.category = "foo";

    string names[] = { "foo", "bar", "x", "y", "abcdefg" };

    int idx;

    for(idx = 0; idx < 5; ++idx)
    {
        identity.name = names[idx];
        MyObjectPrx prx = MyObjectPrx::uncheckedCast(oa->createProxy(identity));
        prx->ice_ping();
        test(prx->getName() == names[idx]);
    }

    identity.name = "ObjectNotExist";
    MyObjectPrx prx = MyObjectPrx::uncheckedCast(oa->createProxy(identity));
    try
    {
        prx->ice_ping();
        test(false);
    }
    catch(const Ice::ObjectNotExistException&)
    {
        // Expected
    }

    try
    {
        prx->getName();
        test(false);
    }
    catch(const Ice::ObjectNotExistException&)
    {
        // Expected
    }

    identity.name = "FacetNotExist";
    prx = MyObjectPrx::uncheckedCast(oa->createProxy(identity));
    try
    {
        prx->ice_ping();
        test(false);
    }
    catch(const Ice::FacetNotExistException&)
    {
        // Expected
    }

    try
    {
        prx->getName();
        test(false);
    }
    catch(const Ice::FacetNotExistException&)
    {
        // Expected
    }

    identity.category = "bar";
    for(idx = 0; idx < 5; idx++)
    {
        identity.name = names[idx];
        prx = MyObjectPrx::uncheckedCast(oa->createProxy(identity));

        try
        {
            prx->ice_ping();
            test(false);
        }
        catch(const Ice::ObjectNotExistException&)
        {
            // Expected
        }

        try
        {
            prx->getName();
            test(false);
        }
        catch(const Ice::ObjectNotExistException&)
        {
            // Expected
        }
    }

    oa->removeDefaultServant("foo");
    identity.category = "foo";
    prx = MyObjectPrx::uncheckedCast(oa->createProxy(identity));
    try
    {
        prx->ice_ping();
    }
    catch(const Ice::ObjectNotExistException&)
    {
        // Expected
    }

    cout << "ok" << endl;

    cout << "testing default category... " << flush;

    oa->addDefaultServant(servant, "");

    r = oa->findDefaultServant("bar");
    test(r == 0);

    r = oa->findDefaultServant("");
    test(r == servant);

    for(idx = 0; idx < 5; ++idx)
    {
        identity.name = names[idx];
        prx = MyObjectPrx::uncheckedCast(oa->createProxy(identity));
        prx->ice_ping();
        test(prx->getName() == names[idx]);
    }

    cout << "ok" << endl;
}
