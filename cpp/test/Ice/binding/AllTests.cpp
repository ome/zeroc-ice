// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/Random.h>
#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>
#include <set>

#include <functional>

using namespace std;
using namespace Test;

struct RandomNumberGenerator : public std::unary_function<ptrdiff_t, ptrdiff_t>
{
    ptrdiff_t operator()(ptrdiff_t d)
    {
        return IceUtilInternal::random(static_cast<int>(d));
    }
};

class GetAdapterNameCB : public IceUtil::Shared, public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    void
    response(const string& name)
    {
        Lock sync(*this);
        assert(!name.empty());
        _name = name;
        notify();
    }

    void
    exception(const Ice::Exception&)
    {
        test(false);
    }

    virtual string
    getResult()
    {
        Lock sync(*this);
        while(_name.empty())
        {
            wait();
        }
        return _name;
    }

private:

    string _name;
};
typedef IceUtil::Handle<GetAdapterNameCB> GetAdapterNameCBPtr;

string
getAdapterNameWithAMI(const TestIntfPrx& test)
{
    GetAdapterNameCBPtr cb = new GetAdapterNameCB();
    test->begin_getAdapterName(
        newCallback_TestIntf_getAdapterName(cb, &GetAdapterNameCB::response,  &GetAdapterNameCB::exception));
    return cb->getResult();
}

TestIntfPrx
createTestIntfPrx(vector<RemoteObjectAdapterPrx>& adapters)
{
    Ice::EndpointSeq endpoints;
    TestIntfPrx test;
    for(vector<RemoteObjectAdapterPrx>::const_iterator p = adapters.begin(); p != adapters.end(); ++p)
    {
        test = (*p)->getTestIntf();
        Ice::EndpointSeq edpts = test->ice_getEndpoints();
        endpoints.insert(endpoints.end(), edpts.begin(), edpts.end());
    }
    return TestIntfPrx::uncheckedCast(test->ice_endpoints(endpoints));
}

void
deactivate(const RemoteCommunicatorPrx& com, vector<RemoteObjectAdapterPrx>& adapters)
{
    for(vector<RemoteObjectAdapterPrx>::const_iterator p = adapters.begin(); p != adapters.end(); ++p)
    {
        com->deactivateObjectAdapter(*p);
    }
}

void
allTests(const Ice::CommunicatorPtr& communicator)
{
    string ref = "communicator:default -p 12010";
    RemoteCommunicatorPrx com = RemoteCommunicatorPrx::uncheckedCast(communicator->stringToProxy(ref));

    RandomNumberGenerator rng;

    cout << "testing binding with single endpoint... " << flush;
    {
        RemoteObjectAdapterPrx adapter = com->createObjectAdapter("Adapter", "default");

        TestIntfPrx test1 = adapter->getTestIntf();
        TestIntfPrx test2 = adapter->getTestIntf();
        test(test1->ice_getConnection() == test2->ice_getConnection());

        test1->ice_ping();
        test2->ice_ping();
        
        com->deactivateObjectAdapter(adapter);
        
        TestIntfPrx test3 = TestIntfPrx::uncheckedCast(test1);
        test(test3->ice_getConnection() == test1->ice_getConnection());
        test(test3->ice_getConnection() == test2->ice_getConnection());
        
        try
        {
            test3->ice_ping();
            test(false);
        }
        catch(const Ice::ConnectionRefusedException&)
        {
        }
    }
    cout << "ok" << endl;

    cout << "testing binding with multiple endpoints... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("Adapter11", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter12", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter13", "default"));

        //
        // Ensure that when a connection is opened it's reused for new
        // proxies and that all endpoints are eventually tried.
        //
        set<string> names;
        names.insert("Adapter11");
        names.insert("Adapter12");
        names.insert("Adapter13");
        while(!names.empty())
        {
            vector<RemoteObjectAdapterPrx> adpts = adapters;

            TestIntfPrx test1 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test2 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test3 = createTestIntfPrx(adpts);

            test(test1->ice_getConnection() == test2->ice_getConnection());
            test(test2->ice_getConnection() == test3->ice_getConnection());
            
            names.erase(test1->getAdapterName());
            test1->ice_getConnection()->close(false);
        }

        //
        // Ensure that the proxy correctly caches the connection (we
        // always send the request over the same connection.)
        //
        {
            for(vector<RemoteObjectAdapterPrx>::const_iterator p = adapters.begin(); p != adapters.end(); ++p)
            {
                (*p)->getTestIntf()->ice_ping();
            }
            
            TestIntfPrx test = createTestIntfPrx(adapters);
            string name = test->getAdapterName();
            const int nRetry = 10;
            int i;
            for(i = 0; i < nRetry &&  test->getAdapterName() == name; i++);
            test(i == nRetry);

            for(vector<RemoteObjectAdapterPrx>::const_iterator q = adapters.begin(); q != adapters.end(); ++q)
            {
                (*q)->getTestIntf()->ice_getConnection()->close(false);
            }
        }           

        //
        // Deactivate an adapter and ensure that we can still
        // establish the connection to the remaining adapters.
        //
        com->deactivateObjectAdapter(adapters[0]);
        names.insert("Adapter12");
        names.insert("Adapter13");
        while(!names.empty())
        {
            vector<RemoteObjectAdapterPrx> adpts = adapters;

            TestIntfPrx test1 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test2 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test3 = createTestIntfPrx(adpts);
            
            test(test1->ice_getConnection() == test2->ice_getConnection());
            test(test2->ice_getConnection() == test3->ice_getConnection());

            names.erase(test1->getAdapterName());
            test1->ice_getConnection()->close(false);
        }
        
        //
        // Deactivate an adapter and ensure that we can still
        // establish the connection to the remaining adapter.
        //
        com->deactivateObjectAdapter(adapters[2]);      
        TestIntfPrx test = createTestIntfPrx(adapters);
        test(test->getAdapterName() == "Adapter12");    

        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing binding with multiple random endpoints... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("AdapterRandom11", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterRandom12", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterRandom13", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterRandom14", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterRandom15", "default"));

#ifdef _WIN32
        int count = 60;
#else
        int count = 20;
#endif
        int adapterCount = static_cast<int>(adapters.size());
        while(--count > 0)
        {
#ifdef _WIN32
            if(count == 10)
            {
                com->deactivateObjectAdapter(adapters[4]);
                --adapterCount;
            }
            vector<TestIntfPrx> proxies;
            proxies.resize(10);
#else
            if(count < 60 && count % 10 == 0)
            {
                com->deactivateObjectAdapter(adapters[count / 10 - 1]);
                --adapterCount;
            }
            vector<TestIntfPrx> proxies;
            proxies.resize(40);
#endif
            unsigned int i;
            for(i = 0; i < proxies.size(); ++i)
            {
                vector<RemoteObjectAdapterPrx> adpts;
                adpts.resize(IceUtilInternal::random(static_cast<int>(adapters.size())));
                if(adpts.empty())
                {
                    adpts.resize(1);
                }
                for(vector<RemoteObjectAdapterPrx>::iterator p = adpts.begin(); p != adpts.end(); ++p)
                {
                    *p = adapters[IceUtilInternal::random(static_cast<int>(adapters.size()))];
                }
                proxies[i] = createTestIntfPrx(adpts);
            }
            
            for(i = 0; i < proxies.size(); i++)
            {
                proxies[i]->begin_getAdapterName();
            }
            for(i = 0; i < proxies.size(); i++)
            {
                try
                {
                    proxies[i]->ice_ping();
                }
                catch(const Ice::LocalException&)
                {
                }
            }
            set<Ice::ConnectionPtr> connections;
            for(i = 0; i < proxies.size(); i++)
            {
                if(proxies[i]->ice_getCachedConnection())
                {
                    connections.insert(proxies[i]->ice_getCachedConnection());
                }
            }
            test(static_cast<int>(connections.size()) <= adapterCount);

            for(vector<RemoteObjectAdapterPrx>::const_iterator q = adapters.begin(); q != adapters.end(); ++q)
            {
                try
                {
                    (*q)->getTestIntf()->ice_getConnection()->close(false);
                }
                catch(const Ice::LocalException&)
                {
                    // Expected if adapter is down.
                }
            }
        }
    }
    cout << "ok" << endl;

    cout << "testing binding with multiple endpoints and AMI... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("AdapterAMI11", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterAMI12", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterAMI13", "default"));

        //
        // Ensure that when a connection is opened it's reused for new
        // proxies and that all endpoints are eventually tried.
        //
        set<string> names;
        names.insert("AdapterAMI11");
        names.insert("AdapterAMI12");
        names.insert("AdapterAMI13");
        while(!names.empty())
        {
            vector<RemoteObjectAdapterPrx> adpts = adapters;

            TestIntfPrx test1 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test2 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test3 = createTestIntfPrx(adpts);

            test(test1->ice_getConnection() == test2->ice_getConnection());
            test(test2->ice_getConnection() == test3->ice_getConnection());
            
            names.erase(getAdapterNameWithAMI(test1));
            test1->ice_getConnection()->close(false);
        }

        //
        // Ensure that the proxy correctly caches the connection (we
        // always send the request over the same connection.)
        //
        {
            for(vector<RemoteObjectAdapterPrx>::const_iterator p = adapters.begin(); p != adapters.end(); ++p)
            {
                (*p)->getTestIntf()->ice_ping();
            }
            
            TestIntfPrx test = createTestIntfPrx(adapters);
            string name = getAdapterNameWithAMI(test);
            const int nRetry = 10;
            int i;
            for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == name; i++);
            test(i == nRetry);

            for(vector<RemoteObjectAdapterPrx>::const_iterator q = adapters.begin(); q != adapters.end(); ++q)
            {
                (*q)->getTestIntf()->ice_getConnection()->close(false);
            }
        }           

        //
        // Deactivate an adapter and ensure that we can still
        // establish the connection to the remaining adapters.
        //
        com->deactivateObjectAdapter(adapters[0]);
        names.insert("AdapterAMI12");
        names.insert("AdapterAMI13");
        while(!names.empty())
        {
            vector<RemoteObjectAdapterPrx> adpts = adapters;

            TestIntfPrx test1 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test2 = createTestIntfPrx(adpts);
            random_shuffle(adpts.begin(), adpts.end(), rng);
            TestIntfPrx test3 = createTestIntfPrx(adpts);
            
            test(test1->ice_getConnection() == test2->ice_getConnection());
            test(test2->ice_getConnection() == test3->ice_getConnection());

            names.erase(test1->getAdapterName());
            test1->ice_getConnection()->close(false);
        }
        
        //
        // Deactivate an adapter and ensure that we can still
        // establish the connection to the remaining adapter.
        //
        com->deactivateObjectAdapter(adapters[2]);      
        TestIntfPrx test = createTestIntfPrx(adapters);
        test(test->getAdapterName() == "AdapterAMI12"); 

        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing random endpoint selection... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("Adapter21", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter22", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter23", "default"));

        TestIntfPrx test = createTestIntfPrx(adapters);
        test(test->ice_getEndpointSelection() == Ice::Random);

        set<string> names;
        names.insert("Adapter21");
        names.insert("Adapter22");
        names.insert("Adapter23");
        while(!names.empty())
        {
            names.erase(test->getAdapterName());
            test->ice_getConnection()->close(false);
        }

        test = TestIntfPrx::uncheckedCast(test->ice_endpointSelection(Ice::Random));
        test(test->ice_getEndpointSelection() == Ice::Random);

        names.insert("Adapter21");
        names.insert("Adapter22");
        names.insert("Adapter23");
        while(!names.empty())
        {
            names.erase(test->getAdapterName());
            test->ice_getConnection()->close(false);
        }

        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing ordered endpoint selection... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("Adapter31", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter32", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter33", "default"));

        TestIntfPrx test = createTestIntfPrx(adapters);
        test = TestIntfPrx::uncheckedCast(test->ice_endpointSelection(Ice::Ordered));
        test(test->ice_getEndpointSelection() == Ice::Ordered);
        const int nRetry = 5;
        int i;

        //
        // Ensure that endpoints are tried in order by deactiving the adapters
        // one after the other.
        //
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter31"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[0]);
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter32"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[1]);
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter33"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[2]);
        
        try
        {
            test->getAdapterName();
        }
        catch(const Ice::ConnectionRefusedException&)
        {
        }

        Ice::EndpointSeq endpoints = test->ice_getEndpoints();

        adapters.clear();

        //
        // Now, re-activate the adapters with the same endpoints in the opposite
        // order.
        // 
        adapters.push_back(com->createObjectAdapter("Adapter36", endpoints[2]->toString()));
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter36"; i++);
        test(i == nRetry);
        test->ice_getConnection()->close(false);
        adapters.push_back(com->createObjectAdapter("Adapter35", endpoints[1]->toString()));
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter35"; i++);
        test(i == nRetry);
        test->ice_getConnection()->close(false);
        adapters.push_back(com->createObjectAdapter("Adapter34", endpoints[0]->toString()));
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter34"; i++);
        test(i == nRetry);

        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing per request binding with single endpoint... " << flush;
    {
        RemoteObjectAdapterPrx adapter = com->createObjectAdapter("Adapter41", "default");

        TestIntfPrx test1 = TestIntfPrx::uncheckedCast(adapter->getTestIntf()->ice_connectionCached(false));
        TestIntfPrx test2 = TestIntfPrx::uncheckedCast(adapter->getTestIntf()->ice_connectionCached(false));
        test(!test1->ice_isConnectionCached());
        test(!test2->ice_isConnectionCached());
        test(test1->ice_getConnection() == test2->ice_getConnection());

        test1->ice_ping();
        
        com->deactivateObjectAdapter(adapter);
        
        TestIntfPrx test3 = TestIntfPrx::uncheckedCast(test1);
        try
        {
            test(test3->ice_getConnection() == test1->ice_getConnection());
            test(false);
        }
        catch(const Ice::ConnectionRefusedException&)
        {
        }
    }
    cout << "ok" << endl;

    cout << "testing per request binding with multiple endpoints... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("Adapter51", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter52", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter53", "default"));

        TestIntfPrx test = TestIntfPrx::uncheckedCast(createTestIntfPrx(adapters)->ice_connectionCached(false));
        test(!test->ice_isConnectionCached());

        set<string> names;
        names.insert("Adapter51");
        names.insert("Adapter52");
        names.insert("Adapter53");
        while(!names.empty())
        {
            names.erase(test->getAdapterName());
        }

        com->deactivateObjectAdapter(adapters[0]);

        names.insert("Adapter52");
        names.insert("Adapter53");
        while(!names.empty())
        {
            names.erase(test->getAdapterName());
        }

        com->deactivateObjectAdapter(adapters[2]);

        test(test->getAdapterName() == "Adapter52");
        
        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing per request binding with multiple endpoints and AMI... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("AdapterAMI51", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterAMI52", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterAMI53", "default"));

        TestIntfPrx test = TestIntfPrx::uncheckedCast(createTestIntfPrx(adapters)->ice_connectionCached(false));
        test(!test->ice_isConnectionCached());

        set<string> names;
        names.insert("AdapterAMI51");
        names.insert("AdapterAMI52");
        names.insert("AdapterAMI53");
        while(!names.empty())
        {
            names.erase(getAdapterNameWithAMI(test));
        }

        com->deactivateObjectAdapter(adapters[0]);

        names.insert("AdapterAMI52");
        names.insert("AdapterAMI53");
        while(!names.empty())
        {
            names.erase(getAdapterNameWithAMI(test));
        }

        com->deactivateObjectAdapter(adapters[2]);

        test(test->getAdapterName() == "AdapterAMI52");
        
        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing per request binding and ordered endpoint selection... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("Adapter61", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter62", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter63", "default"));

        TestIntfPrx test = createTestIntfPrx(adapters);
        test = TestIntfPrx::uncheckedCast(test->ice_endpointSelection(Ice::Ordered));
        test(test->ice_getEndpointSelection() == Ice::Ordered);
        test = TestIntfPrx::uncheckedCast(test->ice_connectionCached(false));
        test(!test->ice_isConnectionCached());
        const int nRetry = 5;
        int i;

        //
        // Ensure that endpoints are tried in order by deactiving the adapters
        // one after the other.
        //
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter61"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[0]);
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter62"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[1]);
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter63"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[2]);
        
        try
        {
            test->getAdapterName();
        }
        catch(const Ice::ConnectionRefusedException&)
        {
        }

        Ice::EndpointSeq endpoints = test->ice_getEndpoints();

        adapters.clear();

        //
        // Now, re-activate the adapters with the same endpoints in the opposite
        // order.
        // 
        adapters.push_back(com->createObjectAdapter("Adapter66", endpoints[2]->toString()));
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter66"; i++);
        test(i == nRetry);
        adapters.push_back(com->createObjectAdapter("Adapter65", endpoints[1]->toString()));
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter65"; i++);
        test(i == nRetry);
        adapters.push_back(com->createObjectAdapter("Adapter64", endpoints[0]->toString()));
        for(i = 0; i < nRetry && test->getAdapterName() == "Adapter64"; i++);
        test(i == nRetry);

        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing per request binding and ordered endpoint selection and AMI... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("AdapterAMI61", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterAMI62", "default"));
        adapters.push_back(com->createObjectAdapter("AdapterAMI63", "default"));

        TestIntfPrx test = createTestIntfPrx(adapters);
        test = TestIntfPrx::uncheckedCast(test->ice_endpointSelection(Ice::Ordered));
        test(test->ice_getEndpointSelection() == Ice::Ordered);
        test = TestIntfPrx::uncheckedCast(test->ice_connectionCached(false));
        test(!test->ice_isConnectionCached());
        const int nRetry = 5;
        int i;

        //
        // Ensure that endpoints are tried in order by deactiving the adapters
        // one after the other.
        //
        for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == "AdapterAMI61"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[0]);
        for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == "AdapterAMI62"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[1]);
        for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == "AdapterAMI63"; i++);
        test(i == nRetry);
        com->deactivateObjectAdapter(adapters[2]);
        
        try
        {
            test->getAdapterName();
        }
        catch(const Ice::ConnectionRefusedException&)
        {
        }

        Ice::EndpointSeq endpoints = test->ice_getEndpoints();

        adapters.clear();

        //
        // Now, re-activate the adapters with the same endpoints in the opposite
        // order.
        // 
        adapters.push_back(com->createObjectAdapter("AdapterAMI66", endpoints[2]->toString()));
        for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == "AdapterAMI66"; i++);
        test(i == nRetry);
        adapters.push_back(com->createObjectAdapter("AdapterAMI65", endpoints[1]->toString()));
        for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == "AdapterAMI65"; i++);
        test(i == nRetry);
        adapters.push_back(com->createObjectAdapter("AdapterAMI64", endpoints[0]->toString()));
        for(i = 0; i < nRetry && getAdapterNameWithAMI(test) == "AdapterAMI64"; i++);
        test(i == nRetry);

        deactivate(com, adapters);
    }
    cout << "ok" << endl;

    cout << "testing endpoint mode filtering... " << flush;
    {
        vector<RemoteObjectAdapterPrx> adapters;
        adapters.push_back(com->createObjectAdapter("Adapter71", "default"));
        adapters.push_back(com->createObjectAdapter("Adapter72", "udp"));

        TestIntfPrx test = createTestIntfPrx(adapters);
        test(test->getAdapterName() == "Adapter71");
        
        TestIntfPrx testUDP = TestIntfPrx::uncheckedCast(test->ice_datagram());
        test(test->ice_getConnection() != testUDP->ice_getConnection());
        try
        {
            testUDP->getAdapterName();
        }
        catch(const Ice::TwowayOnlyException&)
        {
        }
    }
    cout << "ok" << endl;

    if(!communicator->getProperties()->getProperty("Ice.Plugin.IceSSL").empty())
    {
        cout << "testing unsecure vs. secure endpoints... " << flush;
        {
            vector<RemoteObjectAdapterPrx> adapters;
            adapters.push_back(com->createObjectAdapter("Adapter81", "ssl"));
            adapters.push_back(com->createObjectAdapter("Adapter82", "tcp"));
            
            TestIntfPrx test = createTestIntfPrx(adapters);
            int i;
            for(i = 0; i < 5; i++)
            {
                test(test->getAdapterName() == "Adapter82");
                test->ice_getConnection()->close(false);
            }
            
            TestIntfPrx testSecure = TestIntfPrx::uncheckedCast(test->ice_secure(true));
            test(testSecure->ice_isSecure());
            testSecure = TestIntfPrx::uncheckedCast(test->ice_secure(false));
            test(!testSecure->ice_isSecure());
            testSecure = TestIntfPrx::uncheckedCast(test->ice_secure(true));
            test(testSecure->ice_isSecure());
            test(test->ice_getConnection() != testSecure->ice_getConnection());

            com->deactivateObjectAdapter(adapters[1]);
            
            for(i = 0; i < 5; i++)
            {
                test(test->getAdapterName() == "Adapter81");
                test->ice_getConnection()->close(false);
            }

            com->createObjectAdapter("Adapter83", (test->ice_getEndpoints()[1])->toString()); // Reactive tcp OA.

            for(i = 0; i < 5; i++)
            {
                test(test->getAdapterName() == "Adapter83");
                test->ice_getConnection()->close(false);
            }

            com->deactivateObjectAdapter(adapters[0]);
            try
            {
                testSecure->ice_ping();
                test(false);
            }
            catch(const Ice::ConnectionRefusedException&)
            {
            }

            deactivate(com, adapters);
        }
        cout << "ok" << endl;
    }

    {
        cout << "testing ipv4 & ipv6 connections... " << flush;

        Ice::PropertiesPtr ipv4 = Ice::createProperties();
        ipv4->setProperty("Ice.IPv4", "1");
        ipv4->setProperty("Ice.IPv6", "0");
        ipv4->setProperty("Adapter.Endpoints", "tcp -h localhost");

        Ice::PropertiesPtr ipv6 = Ice::createProperties();
        ipv6->setProperty("Ice.IPv4", "0");
        ipv6->setProperty("Ice.IPv6", "1");
        ipv6->setProperty("Adapter.Endpoints", "tcp -h localhost");

        Ice::PropertiesPtr bothPreferIPv4 = Ice::createProperties();
        bothPreferIPv4->setProperty("Ice.IPv4", "1");
        bothPreferIPv4->setProperty("Ice.IPv6", "1");
        bothPreferIPv4->setProperty("Ice.PreferIPv6Address", "0");
        bothPreferIPv4->setProperty("Adapter.Endpoints", "tcp -h localhost");

        Ice::PropertiesPtr bothPreferIPv6 = Ice::createProperties();
        bothPreferIPv6->setProperty("Ice.IPv4", "1");
        bothPreferIPv6->setProperty("Ice.IPv6", "1");
        bothPreferIPv6->setProperty("Ice.PreferIPv6Address", "1");
        bothPreferIPv6->setProperty("Adapter.Endpoints", "tcp -h localhost");

        vector<Ice::PropertiesPtr> clientProps;
        clientProps.push_back(ipv4);
        clientProps.push_back(ipv6);
        clientProps.push_back(bothPreferIPv4);
        clientProps.push_back(bothPreferIPv6);

        Ice::PropertiesPtr anyipv4 = ipv4->clone();
        anyipv4->setProperty("Adapter.Endpoints", "tcp -p 12012");
        anyipv4->setProperty("Adapter.PublishedEndpoints", "tcp -h 127.0.0.1 -p 12012");

        Ice::PropertiesPtr anyipv6 = ipv6->clone();
        anyipv6->setProperty("Adapter.Endpoints", "tcp -p 12012");
        anyipv6->setProperty("Adapter.PublishedEndpoints", "tcp -h \"::1\" -p 12012");

        Ice::PropertiesPtr anyboth = Ice::createProperties();
        anyboth->setProperty("Ice.IPv4", "1");
        anyboth->setProperty("Ice.IPv6", "1");
        anyboth->setProperty("Adapter.Endpoints", "tcp -p 12012");
        anyboth->setProperty("Adapter.PublishedEndpoints", "tcp -h \"::1\" -p 12012:tcp -h 127.0.0.1 -p 12012");

        Ice::PropertiesPtr localipv4 = ipv4->clone();
        localipv4->setProperty("Adapter.Endpoints", "tcp -h 127.0.0.1");

        Ice::PropertiesPtr localipv6 = ipv6->clone();
        localipv6->setProperty("Adapter.Endpoints", "tcp -h \"::1\"");

        vector<Ice::PropertiesPtr> serverProps = clientProps;
        serverProps.push_back(anyipv4);
        serverProps.push_back(anyipv6);
        serverProps.push_back(anyboth);
        serverProps.push_back(localipv4);
        serverProps.push_back(localipv6);

#if defined(_WIN32) && !defined(ICE_OS_WINRT)
        OSVERSIONINFO ver;
        ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        GetVersionEx(&ver);
        const bool dualStack = ver.dwMajorVersion >= 6; // Windows XP IPv6 doesn't support dual-stack
#else
        const bool dualStack = true;
#endif

        bool ipv6NotSupported = false;
        for(vector<Ice::PropertiesPtr>::const_iterator p = serverProps.begin(); p != serverProps.end(); ++p)
        {
            Ice::InitializationData serverInitData;
            serverInitData.properties = *p;
            Ice::CommunicatorPtr serverCommunicator = Ice::initialize(serverInitData);
            Ice::ObjectAdapterPtr oa;
            try
            {
                oa = serverCommunicator->createObjectAdapter("Adapter");
                oa->activate();
            }
            catch(const Ice::DNSException&)
            {
                serverCommunicator->destroy();
                continue; // IP version not supported.
            }
            catch(const Ice::SocketException&)
            {
                if(*p == ipv6)
                {
                    ipv6NotSupported = true;
                }
                serverCommunicator->destroy();
                continue; // IP version not supported.
            }

            string strPrx = oa->createProxy(serverCommunicator->stringToIdentity("dummy"))->ice_toString();
            for(vector<Ice::PropertiesPtr>::const_iterator q = clientProps.begin(); q != clientProps.end(); ++q)
            {
                Ice::InitializationData clientInitData;
                clientInitData.properties = *q;
                Ice::CommunicatorPtr clientCommunicator = Ice::initialize(clientInitData);
                Ice::ObjectPrx prx = clientCommunicator->stringToProxy(strPrx);
                try
                {
                    prx->ice_ping();
                    test(false);
                }
                catch(const Ice::ObjectNotExistException&)
                {
                    // Expected, no object registered.
                }
                catch(const Ice::DNSException&)
                {
                    // Expected if no IPv4 or IPv6 address is
                    // associated to localhost or if trying to connect
                    // to an any endpoint with the wrong IP version,
                    // e.g.: resolving an IPv4 address when only IPv6
                    // is enabled fails with a DNS exception.
                }
                catch(const Ice::SocketException&)
                {
                    test((*p == ipv4 && *q == ipv6) || (*p == ipv6 && *q == ipv4) ||
                         (*p == bothPreferIPv4 && *q == ipv6) || (*p == bothPreferIPv6 && *q == ipv4) ||
                         (*p == bothPreferIPv6 && *q == ipv6 && ipv6NotSupported) ||
                         (*p == anyipv4 && *q == ipv6) || (*p == anyipv6 && *q == ipv4) ||
                         (*p == anyboth && *q == ipv4 && !dualStack) ||
                         (*p == localipv4 && *q == ipv6) || (*p == localipv6 && *q == ipv4));
                }
                clientCommunicator->destroy();
            }
            serverCommunicator->destroy();
        }

        cout << "ok" << endl;
    }

    com->shutdown();
}
