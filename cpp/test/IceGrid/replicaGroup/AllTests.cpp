// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Ice/BuiltinSequences.h>
#include <IceGrid/Query.h>
#include <IceGrid/Registry.h>
#include <IceGrid/Admin.h>
#include <IceUtil/Thread.h>
#include <TestCommon.h>
#include <Test.h>
#include <set>

using namespace std;
using namespace Test;
using namespace IceGrid;

class SessionKeepAliveThread : public IceUtil::Thread, public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    SessionKeepAliveThread(const IceGrid::AdminSessionPrx& session, long timeout) :
        _session(session),
        _timeout(IceUtil::Time::seconds(timeout)),
        _destroy(false)
    {
    }

    virtual void
    run()
    {
        Lock sync(*this);
        while(!_destroy)
        {
            timedWait(_timeout);
            if(_destroy)
            {
                break;
            }
            try
            {
                _session->keepAlive();
            }
            catch(const Ice::Exception&)
            {
                break;
            }
        }
    }

    void
    destroy()
    {
        Lock sync(*this);
        _destroy = true;
        notify();
    }

private:

    IceGrid::AdminSessionPrx _session;
    const IceUtil::Time _timeout;
    bool _destroy;
};

typedef IceUtil::Handle<SessionKeepAliveThread> SessionKeepAliveThreadPtr;

void
instantiateServer(const AdminPrx& admin, const string& templ, const string& node, const map<string, string>& params,
                  const string& application = string("Test"))
{
    ServerInstanceDescriptor desc;
    desc._cpp_template = templ;
    desc.parameterValues = params;
    NodeUpdateDescriptor nodeUpdate;
    nodeUpdate.name = node;
    nodeUpdate.serverInstances.push_back(desc);
    ApplicationUpdateDescriptor update;
    update.name = application;
    update.nodes.push_back(nodeUpdate);
    try
    {
        admin->updateApplication(update);
    }
    catch(const DeploymentException& ex)
    {
        cerr << ex.reason << endl;
        test(false);
    }
    catch(const Ice::LocalException& ex)
    {
        cerr << ex << endl;
        test(false);
    }

    assert(params.find("id") != params.end());
    try
    {
        admin->startServer(params.find("id")->second);
    }
    catch(const NodeUnreachableException&)
    {
    }
    catch(const Ice::Exception&)
    {
        test(false);
    }
}

void
removeServer(const AdminPrx& admin, const string& id)
{
    try
    {
        admin->enableServer(id, false); // Makes sure the server isn't activated on-demand after the stop.
        admin->stopServer(id);
    }
    catch(const ServerStopException&)
    {
    }
    catch(const NodeUnreachableException&)
    {
    }
    catch(const Ice::UserException& ex)
    {
        cerr << ex << endl;
        test(false);
    }

    ServerInfo info = admin->getServerInfo(id);

    NodeUpdateDescriptor nodeUpdate;
    nodeUpdate.name = info.node;
    nodeUpdate.removeServers.push_back(id);
    ApplicationUpdateDescriptor update;
    update.name = info.application;
    update.nodes.push_back(nodeUpdate);
    try
    {
        admin->updateApplication(update);
    }
    catch(DeploymentException& ex)
    {
        cerr << ex.reason << endl;
        test(false);
    }
}

void
allTests(const Ice::CommunicatorPtr& comm)
{
    RegistryPrx registry = IceGrid::RegistryPrx::checkedCast(comm->stringToProxy("IceGrid/Registry"));
    test(registry);
    AdminSessionPrx session = registry->createAdminSession("foo", "bar");

    SessionKeepAliveThreadPtr keepAlive = new SessionKeepAliveThread(session, registry->getSessionTimeout()/2);
    keepAlive->start();

    AdminPrx admin = session->getAdmin();
    test(admin);

    set<string> serverReplicaIds;
    serverReplicaIds.insert("Server1.ReplicatedAdapter");
    serverReplicaIds.insert("Server2.ReplicatedAdapter");
    serverReplicaIds.insert("Server3.ReplicatedAdapter");
    set<string> svcReplicaIds;
    svcReplicaIds.insert("IceBox1.Service1.Service1");
    svcReplicaIds.insert("IceBox1.Service2.Service2");
    svcReplicaIds.insert("IceBox1.Service3.Service3");

    cout << "testing Query::findAllReplicas... " << flush;
    {
        map<string, string> params;
        params["replicaGroup"] = "RoundRobin";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        instantiateServer(admin, "Server", "localnode", params);

        QueryPrx query = IceGrid::QueryPrx::checkedCast(comm->stringToProxy("IceGrid/Query"));
        test(query);
        
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("dummy@RoundRobin"));
        Ice::ObjectProxySeq objs = query->findAllReplicas(obj);
        test(objs.size() == 3);
        test(serverReplicaIds.find(objs[0]->ice_getAdapterId()) != serverReplicaIds.end());
        test(serverReplicaIds.find(objs[1]->ice_getAdapterId()) != serverReplicaIds.end());
        test(serverReplicaIds.find(objs[2]->ice_getAdapterId()) != serverReplicaIds.end());

        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("RoundRobin"));
        objs = query->findAllReplicas(obj);
        test(objs.size() == 3);
        test(serverReplicaIds.find(objs[0]->ice_getAdapterId()) != serverReplicaIds.end());
        test(serverReplicaIds.find(objs[1]->ice_getAdapterId()) != serverReplicaIds.end());
        test(serverReplicaIds.find(objs[2]->ice_getAdapterId()) != serverReplicaIds.end());
        
        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("dummy@dummy"));
        objs = query->findAllReplicas(obj);
        test(objs.empty());

        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("dummy@Server1.ReplicatedAdapter"));
        objs = query->findAllReplicas(obj);
        test(objs.empty());

        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("dummy:tcp"));
        objs = query->findAllReplicas(obj);
        test(objs.empty());

        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("dummy@Ordered"));
        objs = query->findAllReplicas(obj);
        test(objs.empty());
        
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");
    }
    cout << "ok" << endl;

    cout << "testing replication with round-robin load balancing... " << flush;
    {
        map<string, string> params;
        params["replicaGroup"] = "RoundRobin";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        instantiateServer(admin, "Server", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("RoundRobin"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(0));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        try
        {
            test(obj->getReplicaIdAndShutdown() == "Server1.ReplicatedAdapter");
            test(obj->getReplicaIdAndShutdown() == "Server2.ReplicatedAdapter");
            test(obj->getReplicaIdAndShutdown() == "Server3.ReplicatedAdapter");        

            admin->enableServer("Server1", false);
            admin->enableServer("Server2", false);
            admin->enableServer("Server3", false);

            try
            {
                obj->getReplicaId();
                test(false);
            }
            catch(const Ice::NoEndpointException&)
            {
            }

            admin->enableServer("Server1", true);
            admin->enableServer("Server2", true);
            admin->enableServer("Server3", true);

            set<string> adapterIds;
            string previousId;
            while(adapterIds.size() != 3)
            {
                string id = obj->getReplicaId();
                adapterIds.insert(id);

                if(adapterIds.size() == 1)
                {
                    previousId = id;
                }
                else
                {
                    test(previousId != id);
                    previousId = id;
                }
            }
            
            int i;
            for(i = 0; i < 3; i++)
            {
                if(obj->getReplicaId() == "Server3.ReplicatedAdapter")
                {
                    break;
                }
            }
            test(i != 3);

            test(obj->getReplicaId() == "Server1.ReplicatedAdapter");
            test(obj->getReplicaId() == "Server2.ReplicatedAdapter");
            test(obj->getReplicaId() == "Server3.ReplicatedAdapter");

            test(obj->getReplicaIdAndShutdown() == "Server1.ReplicatedAdapter");
            test(obj->getReplicaIdAndShutdown() == "Server2.ReplicatedAdapter");
            test(obj->getReplicaIdAndShutdown() == "Server3.ReplicatedAdapter");
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }

        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");
    }
    {
        map<string, string> params;
        params["replicaGroup"] = "RoundRobin";
        params["id"] = "IceBox1";
        instantiateServer(admin, "IceBox", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("RoundRobin"));
        try
        {
            test(obj->getReplicaIdAndShutdown() == "IceBox1.Service1.Service1");
            test(obj->getReplicaIdAndShutdown() == "IceBox1.Service2.Service2");
            test(obj->getReplicaIdAndShutdown() == "IceBox1.Service3.Service3");
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        removeServer(admin, "IceBox1");
    }
    cout << "ok" << endl;

    cout << "testing replication with ordered load balancing... " << flush;
    {
        map<string, string> params;
        params["replicaGroup"] = "Ordered";
        params["id"] = "Server1";
        params["priority"] = "3";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        params["priority"] = "1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        params["priority"] = "2";
        instantiateServer(admin, "Server", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Ordered"));
        try
        {
            test(obj->getReplicaIdAndShutdown() == "Server2.ReplicatedAdapter");
            admin->enableServer("Server2", false);
            test(obj->getReplicaIdAndShutdown() == "Server3.ReplicatedAdapter");
            admin->enableServer("Server3", false);
            test(obj->getReplicaIdAndShutdown() == "Server1.ReplicatedAdapter");
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");
    }
    {
        map<string, string> params;
        params["replicaGroup"] = "Ordered";
        params["id"] = "IceBox1";
        instantiateServer(admin, "IceBox", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Ordered"));
        try
        {
            test(obj->getReplicaIdAndShutdown() == "IceBox1.Service3.Service3");
            test(obj->getReplicaIdAndShutdown() == "IceBox1.Service2.Service2");
            test(obj->getReplicaIdAndShutdown() == "IceBox1.Service1.Service1");
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        removeServer(admin, "IceBox1");
    }
    cout << "ok" << endl;

    cout << "testing replication with random load balancing... " << flush;
    {
        map<string, string> params;
        params["replicaGroup"] = "Random";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        instantiateServer(admin, "Server", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Random"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(0));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        set<string> replicaIds = serverReplicaIds;
        while(!replicaIds.empty())
        {
            try
            {
                replicaIds.erase(obj->getReplicaId());
            }
            catch(const Ice::LocalException& ex)
            {
                cerr << ex << endl;
                test(false);
            }
        }
        
        admin->stopServer("Server1");
        admin->stopServer("Server2");
        admin->stopServer("Server3");

        admin->enableServer("Server1", false);
        admin->enableServer("Server2", false);
        admin->enableServer("Server3", false);

        try
        {
            obj->getReplicaId();
            test(false);
        }
        catch(const Ice::NoEndpointException&)
        {
        }
        
        admin->enableServer("Server1", true);
        admin->enableServer("Server2", true);
        admin->enableServer("Server3", true);

        replicaIds = serverReplicaIds;
        while(!replicaIds.empty())
        {
            try
            {
                replicaIds.erase(obj->getReplicaIdAndShutdown());
            }
            catch(const Ice::LocalException& ex)
            {
                cerr << ex << endl;
                test(false);
            }
        }

        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");
    }
    {
        map<string, string> params;
        params["replicaGroup"] = "Random";
        params["id"] = "IceBox1";
        instantiateServer(admin, "IceBox", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Random"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(0));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        set<string> replicaIds = svcReplicaIds;
        while(!replicaIds.empty())
        {
            try
            {
                replicaIds.erase(obj->getReplicaId());
            }
            catch(const Ice::ConnectionRefusedException&)
            {
            }
            catch(const Ice::LocalException& ex)
            {
                cerr << ex << endl;
                test(false);
            }
        }
        removeServer(admin, "IceBox1");
    }
    cout << "ok" << endl;

    cout << "testing replication with adaptive load balancing... " << flush;
    {
        map<string, string> params;
        params["replicaGroup"] = "Adaptive";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        instantiateServer(admin, "Server", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Adaptive"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(0));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        set<string> replicaIds = serverReplicaIds;
        while(!replicaIds.empty())
        {
            try
            {
                replicaIds.erase(obj->getReplicaId());
            }
            catch(const Ice::LocalException& ex)
            {
                cerr << ex << endl;
                test(false);
            }
        }
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");
    }
    {
        map<string, string> params;
        params["replicaGroup"] = "Adaptive";
        params["id"] = "IceBox1";
        instantiateServer(admin, "IceBox", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Adaptive"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(0));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        set<string> replicaIds = svcReplicaIds;
        while(!replicaIds.empty())
        {
            try
            {
                replicaIds.erase(obj->getReplicaId());
            }
            catch(const Ice::ConnectionRefusedException&)
            {
            }
            catch(const Ice::LocalException& ex)
            {
                cerr << ex << endl;
                test(false);
            }
        }
        removeServer(admin, "IceBox1");
    }
    cout << "ok" << endl;

    cout << "testing load balancing n-replicas..." << flush;
    {
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("RoundRobin-2"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(-1));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        try
        {
            obj->ice_ping();
            test(false);
        }
        catch(const Ice::NoEndpointException&)
        {
        }

        map<string, string> params;
        params["replicaGroup"] = "RoundRobin-2";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        instantiateServer(admin, "Server", "localnode", params);
        try
        {
            set<string> replicaIds;
            set<string> expected;
            replicaIds.insert("Server1.ReplicatedAdapter");
            replicaIds.insert("Server2.ReplicatedAdapter");
            expected = replicaIds;
            while(!replicaIds.empty())
            {
                string replicaId = obj->getReplicaId();
                test(expected.find(replicaId) != expected.end());
                replicaIds.erase(replicaId);
            }
            obj->ice_locatorCacheTimeout(0)->ice_ping();
            replicaIds.insert("Server2.ReplicatedAdapter");
            replicaIds.insert("Server3.ReplicatedAdapter");
            expected = replicaIds;
            while(!replicaIds.empty())
            {
                string replicaId = obj->getReplicaId();
                test(expected.find(replicaId) != expected.end());
                replicaIds.erase(replicaId);
            }
            obj->ice_locatorCacheTimeout(0)->ice_ping();
            replicaIds.insert("Server3.ReplicatedAdapter");
            replicaIds.insert("Server1.ReplicatedAdapter");
            expected = replicaIds;
            while(!replicaIds.empty())
            {
                string replicaId = obj->getReplicaId();
                test(expected.find(replicaId) != expected.end());
                replicaIds.erase(replicaId);
            }

            admin->stopServer("Server1");
            admin->stopServer("Server2");
            admin->stopServer("Server3");

            obj->ice_locatorCacheTimeout(0)->ice_ping();
            int nRetry = 500; 
            while(replicaIds.size() != 2 && --nRetry > 0)
            {
                replicaIds.insert(obj->getReplicaId());
            }
            test(replicaIds.size() == 2);
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");

    }
    {
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("RoundRobin-All"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(-1));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        try
        {
            obj->ice_ping();
            test(false);
        }
        catch(const Ice::NoEndpointException&)
        {
        }

        map<string, string> params;
        params["replicaGroup"] = "RoundRobin-All";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        params["id"] = "Server3";
        instantiateServer(admin, "Server", "localnode", params);
        try
        {
            set<string> replicaIds;
            set<string> expected;
            replicaIds.insert("Server1.ReplicatedAdapter");
            replicaIds.insert("Server2.ReplicatedAdapter");
            replicaIds.insert("Server3.ReplicatedAdapter");
            expected = replicaIds;
            while(!replicaIds.empty())
            {
                string replicaId = obj->getReplicaId();
                test(expected.find(replicaId) != expected.end());
                replicaIds.erase(replicaId);
            }
            obj->ice_locatorCacheTimeout(0)->ice_ping();
            replicaIds.insert("Server1.ReplicatedAdapter");
            replicaIds.insert("Server2.ReplicatedAdapter");
            replicaIds.insert("Server3.ReplicatedAdapter");
            expected = replicaIds;
            while(!replicaIds.empty())
            {
                string replicaId = obj->getReplicaId();
                test(expected.find(replicaId) != expected.end());
                replicaIds.erase(replicaId);
            }
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");
        removeServer(admin, "Server3");

    }
    cout << "ok" << endl;

    cout << "testing replication with inactive nodes... " << flush;
    {
        map<string, string> params;

        params["replicaGroup"] = "Random";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "inactivenode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Random"));
        test(obj->getReplicaId() == "Server2.ReplicatedAdapter");

        //
        // Also make sure that findObjectByTypeOnLeastLoadedNode still work.
        //
        QueryPrx query = IceGrid::QueryPrx::checkedCast(comm->stringToProxy("IceGrid/Query"));
        obj = TestIntfPrx::uncheckedCast(query->findObjectByTypeOnLeastLoadedNode("::Test::TestIntf", LoadSample1));
        test(obj->getReplicaId() == "Server2.ReplicatedAdapter");
        
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");

        params["replicaGroup"] = "RoundRobin";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "inactivenode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("RoundRobin"));
        test(obj->getReplicaId() == "Server2.ReplicatedAdapter");
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");

        params["replicaGroup"] = "Adaptive";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "inactivenode", params);
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params);
        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Adaptive"));
        test(obj->getReplicaId() == "Server2.ReplicatedAdapter");
        removeServer(admin, "Server1");
        removeServer(admin, "Server2");

        params["replicaGroup"] = "Random";
        params["id"] = "IceBox1";
        instantiateServer(admin, "IceBox", "localnode", params);
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "inactivenode", params);
        obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Random"));
        test(svcReplicaIds.find(obj->getReplicaId()) != svcReplicaIds.end());
        removeServer(admin, "IceBox1");
        removeServer(admin, "Server1");
    };
    cout << "ok" << endl;

    cout << "testing replica group from different applications... " << flush;
    {
        map<string, string> params;
        params["replicaGroup"] = "Random";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);

        ApplicationUpdateDescriptor update;
        update.name = "Test";
        update.removeReplicaGroups.push_back("Random");
        try
        {
            admin->updateApplication(update);
            test(false);
        }
        catch(const DeploymentException&)
        {
            // The Random replica goup is used by Server1!
        }

        //
        // Add an application Test1 without replica groups and a
        // server that uses the Random replica group.
        //
        ApplicationInfo app = admin->getApplicationInfo("Test");
        app.descriptor.name = "Test1";
        app.descriptor.replicaGroups.clear();
        app.descriptor.nodes.clear();
        try
        {
            admin->addApplication(app.descriptor);
        }
        catch(const DeploymentException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        params["id"] = "Server2";
        instantiateServer(admin, "Server", "localnode", params, "Test1");

        try
        {
            admin->removeApplication("Test");
            test(false);
        }
        catch(const DeploymentException&)
        {
            // Test has a replica group referenced by the Test1 application.
        }

        TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy("Random"));
        obj = TestIntfPrx::uncheckedCast(obj->ice_locatorCacheTimeout(0));
        obj = TestIntfPrx::uncheckedCast(obj->ice_connectionCached(false));
        set<string> replicaIds;
        replicaIds.insert("Server1.ReplicatedAdapter");
        replicaIds.insert("Server2.ReplicatedAdapter");
        while(!replicaIds.empty())
        {
            try
            {
                replicaIds.erase(obj->getReplicaId());
            }
            catch(const Ice::LocalException& ex)
            {
                cerr << ex << endl;
                test(false);
            }
        }
        
        removeServer(admin, "Server2");
        removeServer(admin, "Server1");

        ReplicaGroupDescriptor replicaGroup;
        replicaGroup.id = "ReplicatedAdapterFromTest1";
        replicaGroup.loadBalancing = new RandomLoadBalancingPolicy();
        replicaGroup.loadBalancing->nReplicas = "0";
        update = ApplicationUpdateDescriptor();
        update.name = "Test1";
        update.replicaGroups.push_back(replicaGroup);

        try
        {
            admin->updateApplication(update);
        }
        catch(const DeploymentException& ex)
        {
            cerr << ex.reason << endl;
            test(false);
        }

        params["replicaGroup"] = "ReplicatedAdapterFromTest1";
        params["id"] = "Server1";
        instantiateServer(admin, "Server", "localnode", params);

        try
        {
            admin->removeApplication("Test1");
            test(false);
        }
        catch(const DeploymentException&)
        {
            // ReplicatedAdapterFromTest1 used by server from Test
        }

        update = ApplicationUpdateDescriptor();
        update.name = "Test1";
        update.removeReplicaGroups.push_back("ReplicatedAdapterFromTest1");
        try
        {
            admin->updateApplication(update);
            test(false);
        }
        catch(const DeploymentException&)
        {
            // ReplicatedAdapterFromTest1 used by server from Test
        }

        removeServer(admin, "Server1");

        try
        {
            admin->updateApplication(update);
        }
        catch(const DeploymentException& ex)
        {
            cerr << ex << endl;
            test(false);
        }

        admin->removeApplication("Test1");
    };
    cout << "ok" << endl;

    cout << "testing replica group with different server encoding support... " << flush;
    {
        vector<string> loadBalancings;
        loadBalancings.push_back("Random");
        loadBalancings.push_back("RoundRobin");
        loadBalancings.push_back("RoundRobin-All");
        for(vector<string>::const_iterator p = loadBalancings.begin(); p != loadBalancings.end(); ++p)
        {
            map<string, string> params;
            params["replicaGroup"] = *p;
            params["id"] = "Server1";
            params["encoding"] = "1.0";
            instantiateServer(admin, "Server", "localnode", params);
            params["id"] = "Server2";
            params["encoding"] = "1.1";
            instantiateServer(admin, "Server", "localnode", params);
            params["id"] = "Server3";
            params["encoding"] = "1.0";
            instantiateServer(admin, "Server", "localnode", params);
            
            TestIntfPrx obj = TestIntfPrx::uncheckedCast(comm->stringToProxy(*p));
            obj = obj->ice_locatorCacheTimeout(0);
            obj = obj->ice_connectionCached(false);
            
            for(int i = 0; i < 30; ++i)
            {
                test(obj->getReplicaId() == "Server2.ReplicatedAdapter");
            }
            
            obj = obj->ice_encodingVersion(Ice::Encoding_1_0);
            set<string> replicaIds = serverReplicaIds;
            while(!replicaIds.empty())
            {
                try
                {
                    replicaIds.erase(obj->getReplicaId());
                }
                catch(const Ice::LocalException& ex)
                {
                    cerr << ex << endl;
                    test(false);
                }
            }
            
            removeServer(admin, "Server1");
            removeServer(admin, "Server2");
            removeServer(admin, "Server3");
        }
    };
    cout << "ok" << endl;

    keepAlive->destroy();
    keepAlive->getThreadControl().join();
    keepAlive = 0;

    session->destroy();
}
