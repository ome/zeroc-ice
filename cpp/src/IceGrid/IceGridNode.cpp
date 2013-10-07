// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/UUID.h>
#include <IceUtil/Timer.h>
#include <IceUtil/StringUtil.h>
#include <IceUtil/FileUtil.h>
#include <Ice/Ice.h>
#include <Ice/Locator.h>
#include <Ice/Service.h>
#include <IceGrid/Activator.h>
#include <IceGrid/NodeServerAdminRouter.h>
#include <IceGrid/RegistryI.h>
#include <IceGrid/FileUserAccountMapperI.h>
#include <IceGrid/NodeI.h>
#include <IceGrid/NodeSessionManager.h>
#include <IceGrid/TraceLevels.h>
#include <IceGrid/DescriptorParser.h>
#include <IceGrid/Util.h>
#include <IcePatch2/Util.h>

#ifdef _WIN32
#   include <direct.h>
#   include <sys/types.h>
#   include <winsock2.h>
#endif

using namespace std;
using namespace Ice;
using namespace IceGrid;

namespace
{

class ProcessI : public Process
{
public:
    
    ProcessI(const ActivatorPtr&, const ProcessPtr&);

    virtual void shutdown(const Current&);
    virtual void writeMessage(const std::string&, Int, const Current&);
    
private:
    
    ActivatorPtr _activator;
    ProcessPtr _origProcess;
};


class NodeService : public Service
{
public:

    NodeService();
    ~NodeService();

    virtual bool shutdown();

protected:

    virtual bool start(int, char*[], int&);
    bool startImpl(int, char*[], int&);
    virtual void waitForShutdown();
    virtual bool stop();
    virtual CommunicatorPtr initializeCommunicator(int&, char*[], const InitializationData&);

private:

    void usage(const std::string&);

    ActivatorPtr _activator;
    IceUtil::TimerPtr _timer;
    RegistryIPtr _registry;
    NodeIPtr _node;
    IceUtil::UniquePtr<NodeSessionManager> _sessions;
    Ice::ObjectAdapterPtr _adapter;
};

class CollocatedRegistry : public RegistryI
{
public:

    CollocatedRegistry(const CommunicatorPtr&, const ActivatorPtr&, bool, bool, const std::string&);
    virtual void shutdown();

private:

    ActivatorPtr _activator;
};


class DefaultServantLocator : public Ice::ServantLocator
{
public:

    DefaultServantLocator(const ObjectPtr& servant) :
        _servant(servant)
    {
    }

    virtual ObjectPtr locate(const Current&, LocalObjectPtr&)
    {
        return _servant;
    }

    virtual void finished(const Current&, const ObjectPtr&, const LocalObjectPtr&)
    {
    }

    virtual void deactivate(const string&)
    {
    }

private:
    ObjectPtr _servant;
};

#ifdef _WIN32
void
setNoIndexingAttribute(const string& pa)
{
    wstring path = IceUtil::stringToWstring(pa);
    DWORD attrs = GetFileAttributesW(path.c_str());
    if(attrs == INVALID_FILE_ATTRIBUTES)
    {
        FileException ex(__FILE__, __LINE__);
        ex.path = pa;
        ex.error = IceInternal::getSystemErrno();
        throw ex;
    }
    if(!SetFileAttributesW(path.c_str(), attrs | FILE_ATTRIBUTE_NOT_CONTENT_INDEXED))
    {
        FileException ex(__FILE__, __LINE__);
        ex.path = pa;
        ex.error = IceInternal::getSystemErrno();
        throw ex;
    }
}
#endif

} 


CollocatedRegistry::CollocatedRegistry(const CommunicatorPtr& com, 
                                       const ActivatorPtr& activator, 
                                       bool nowarn,
                                       bool readonly,
                                       const string& initFromReplica) :
    RegistryI(com, new TraceLevels(com, "IceGrid.Registry"), nowarn, readonly, initFromReplica), 
    _activator(activator)
{
}

void
CollocatedRegistry::shutdown()
{
    _activator->shutdown();
}

ProcessI::ProcessI(const ActivatorPtr& activator, const ProcessPtr& origProcess) : 
    _activator(activator),
    _origProcess(origProcess)
{
}

void
ProcessI::shutdown(const Current&)
{
    _activator->shutdown();
}

void
ProcessI::writeMessage(const string& message, Int fd, const Current& current)
{
    _origProcess->writeMessage(message, fd, current);
}

NodeService::NodeService()
{
}

NodeService::~NodeService()
{
}


bool
NodeService::shutdown()
{
    assert(_activator);
    _activator->shutdown();
    if(_sessions.get())
    {
        _sessions->terminate(); // Unblock the main thread if it's blocked on waitForCreate()
    }
    return true;
}

bool
NodeService::start(int argc, char* argv[], int& status)
{
    try
    {
        if(!startImpl(argc, argv, status))
        {
            stop();
            return false;
        }
    }
    catch(...)
    {
        stop();
        throw;
    }
    return true;
}

bool
NodeService::startImpl(int argc, char* argv[], int& status)
{
    bool nowarn = false;
    bool readonly = false;
    string initFromReplica;
    string desc;
    vector<string> targets;


    for(int i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            usage(argv[0]);
            status = EXIT_SUCCESS;
            return false;
        }
        else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            print(ICE_STRING_VERSION);
            status = EXIT_SUCCESS;
            return false;
        }
        else if(strcmp(argv[i], "--nowarn") == 0)
        {
            nowarn = true;
        }
        else if(strcmp(argv[i], "--readonly") == 0)
        {
            readonly = true;
        }
        else if(strcmp(argv[i], "--initdb-from-replica") == 0)
        {
            if(i + 1 >= argc)
            {
                error("missing replica argument for option `" + string(argv[i]) + "'");
                usage(argv[0]);
                return false;
            }

            initFromReplica = argv[++i];
        } 
        else if(strcmp(argv[i], "--deploy") == 0)
        {
            if(i + 1 >= argc)
            {
                error("missing descriptor argument for option `" + string(argv[i]) + "'");
                usage(argv[0]);
                return false;
            }

            desc = argv[++i];

            while(i + 1 < argc && argv[++i][0] != '-')
            {
                targets.push_back(argv[i]);
            }
        }
        else
        {
            error("invalid option: `" + string(argv[i]) + "'");
            usage(argv[0]);
            return false;
        }
    }

    PropertiesPtr properties = communicator()->getProperties();

    //
    // Disable server idle time. Otherwise, the adapter would be
    // shutdown prematurely and the deactivation would fail.
    // Deactivation of the node relies on the object adapter
    // to be active since it needs to terminate servers.
    //
    // TODO: implement Ice.ServerIdleTime in the activator
    // termination listener instead?
    //
    properties->setProperty("Ice.ServerIdleTime", "0");

    //
    // Warn the user that setting Ice.ThreadPool.Server isn't useful.
    //
    if(!nowarn && properties->getPropertyAsIntWithDefault("Ice.ThreadPool.Server.Size", 0) > 0)
    {
        Warning out(communicator()->getLogger());
        out << "setting `Ice.ThreadPool.Server.Size' is not useful, ";
        out << "you should set individual adapter thread pools instead.";
    }
    
    setupThreadPool(properties, "IceGrid.Node.ThreadPool", 1, 100);

    //
    // Create the activator.
    //
    TraceLevelsPtr traceLevels = new TraceLevels(communicator(), "IceGrid.Node");
    _activator = new Activator(traceLevels);

    //
    // Collocate the IceGrid registry if we need to.
    //
    if(properties->getPropertyAsInt("IceGrid.Node.CollocateRegistry") > 0)
    {
        _registry = new CollocatedRegistry(communicator(), _activator, nowarn, readonly, initFromReplica);
        if(!_registry->start())
        {
            return false;
        }

        //
        // Set the default locator property to point to the collocated
        // locator (this property is passed by the activator to each
        // activated server). The default locator is also needed by
        // the node session manager.
        //
        if(properties->getProperty("Ice.Default.Locator").empty())
        {
            Identity locatorId;
            locatorId.category = properties->getPropertyWithDefault("IceGrid.InstanceName", "IceGrid");
            locatorId.name = "Locator";
            string endpoints = properties->getProperty("IceGrid.Registry.Client.Endpoints");
            string locPrx = "\"" + communicator()->identityToString(locatorId) + "\" :" + endpoints;
            communicator()->setDefaultLocator(Ice::LocatorPrx::uncheckedCast(communicator()->stringToProxy(locPrx)));
            properties->setProperty("Ice.Default.Locator", locPrx);
        }
    }
    else if(properties->getProperty("Ice.Default.Locator").empty())
    {
        error("property `Ice.Default.Locator' is not set");
        return false;
    }

    //
    // Initialize the database environment (first setup the directory structure if needed).
    //
    string dataPath = properties->getProperty("IceGrid.Node.Data");
    string dbPath;
    if(dataPath.empty())
    {
        error("property `IceGrid.Node.Data' is not set");
        return false;
    }
    else
    {
        if(!IceUtilInternal::directoryExists(dataPath))
        {
            FileException ex(__FILE__, __LINE__);
            ex.path = dataPath;
            ex.error = IceInternal::getSystemErrno();
      
            ServiceError err(this);
            err << "property `IceGrid.Node.Data' is set to an invalid path:\n" << ex;
            return false;
        }

        //
        // Creates subdirectories.
        //
        if(dataPath[dataPath.length() - 1] != '/')
        {
            dataPath += "/"; 
        }

        IcePatch2::createDirectory(dataPath + "servers");
        IcePatch2::createDirectory(dataPath + "tmp");
        IcePatch2::createDirectory(dataPath + "distrib");

#ifdef _WIN32
        //
        // Make sure these directories are not indexed by the Windows
        // indexing service (which can cause random "Access Denied"
        // errors if indexing runs at the same time as the node is
        // creating/deleting files).
        //
        try
        {
            setNoIndexingAttribute(dataPath + "servers");
            setNoIndexingAttribute(dataPath + "tmp");
            setNoIndexingAttribute(dataPath + "distrib");
        }
        catch(const FileException& ex)
        {
            if(!nowarn)
            {
                Warning out(communicator()->getLogger());
                out << "couldn't disable file indexing:\n" << ex;
            }
        }
#endif
    }

    //
    // Check that required properties are set and valid.
    //
    if(properties->getProperty("IceGrid.Node.Endpoints").empty())
    {
        error("property `IceGrid.Node.Endpoints' is not set");
        return false;
    }

    string name = properties->getProperty("IceGrid.Node.Name");
    if(name.empty())
    {
        error("property `IceGrid.Node.Name' is not set");
        return false;
    }

    //
    // Setup the Freeze database environment home directory. The name of the database
    // environment for the IceGrid node is the name of the node.
    //
    properties->setProperty("Freeze.DbEnv." + name + ".DbHome", dbPath);

    //
    // Create the node object adapter.
    //
    _adapter = communicator()->createObjectAdapter("IceGrid.Node");

    //
    // Setup the user account mapper if configured.
    //
    string mapperProperty = "IceGrid.Node.UserAccountMapper";
    string mapperPropertyValue = properties->getProperty(mapperProperty);
    UserAccountMapperPrx mapper;
    if(!mapperPropertyValue.empty())
    {
        try
        {
            mapper = UserAccountMapperPrx::uncheckedCast(communicator()->propertyToProxy(mapperProperty));
        }
        catch(const std::exception& ex)
        {
            ServiceError err(this);
            err << "user account mapper `" << mapperProperty << "' is invalid:\n" << ex;
            return false;
        }
    }
    else
    {
        string userAccountFileProperty = properties->getProperty("IceGrid.Node.UserAccounts");
        if(!userAccountFileProperty.empty())
        {
            try
            {
                Ice::ObjectPrx object = _adapter->addWithUUID(new FileUserAccountMapperI(userAccountFileProperty));
                object = object->ice_collocationOptimized(true);
                mapper = UserAccountMapperPrx::uncheckedCast(object);
            }
            catch(const std::string& msg)
            {
                error(msg);
                return false;
            }
        }
    }

    //
    // Create a new timer to handle server activation/deactivation timeouts.
    //
    _timer = new IceUtil::Timer();

    //
    // The IceGrid instance name.
    //
    const string instanceName = communicator()->getDefaultLocator()->ice_getIdentity().category;

    _sessions.reset(new NodeSessionManager(communicator()));

    //
    // Create the server factory. The server factory creates persistent objects
    // for the server and server adapter. It also takes care of installing the
    // evictors and object factories necessary to store these objects.
    //
    Identity id = communicator()->stringToIdentity(instanceName + "/Node-" + name);
    NodePrx nodeProxy = NodePrx::uncheckedCast(_adapter->createProxy(id));
    _node = new NodeI(_adapter, *_sessions, _activator, _timer, traceLevels, nodeProxy, name, mapper);
    _adapter->add(_node, nodeProxy->ice_getIdentity());

    _adapter->addServantLocator(new DefaultServantLocator(new NodeServerAdminRouter(_node)), 
                                _node->getServerAdminCategory());

    //
    // Start the platform info thread if needed.
    //
    _node->getPlatformInfo().start();

    //
    // Ensures that the locator is reachable.
    // 
    if(!nowarn)
    {
        try
        {
            communicator()->getDefaultLocator()->ice_timeout(1000)->ice_ping();
        }
        catch(const Ice::LocalException& ex)
        {
            Warning out(communicator()->getLogger());
            out << "couldn't reach the IceGrid registry (this is expected ";
            out << "if it's down, otherwise please check the value of the ";
            out << "Ice.Default.Locator property):\n" << ex;
        }
    }

    //
    // Create the node sessions with the registries.
    //
    _sessions->create(_node);

    //
    // In some tests, we deploy icegridnodes using IceGrid:
    //
    if(properties->getProperty("Ice.Admin.Endpoints") != "")
    {
        //
        // Replace Process facet and create Admin object
        //
        try
        {
            ProcessPtr origProcess = ProcessPtr::dynamicCast(communicator()->removeAdminFacet("Process"));
            communicator()->addAdminFacet(new ProcessI(_activator, origProcess), "Process");
            communicator()->getAdmin();
        }
        catch(const Ice::NotRegisteredException&)
        {
            //
            // Some plug-in removed the Process facet, so we don't replace it.
            // (unlikely error though)
            // 
        }
    }

    //
    // Start the activator.
    //
    _activator->start();

    //
    // Activate the adapter.
    //
    _adapter->activate();

    //
    // Notify the node session manager that the node can start
    // accepting incoming connections.
    //
    _sessions->activate();

    string bundleName = properties->getProperty("IceGrid.Node.PrintServersReady");
    if(!bundleName.empty() || !desc.empty())
    {
        enableInterrupt();
        if(!_sessions->waitForCreate())
        {
            //
            // Create was interrupted, return true as if the service was
            // correctly initiliazed to make sure it's properly stopped.
            //
            return true;
        }
        disableInterrupt();
    }

    //
    // Deploy application if a descriptor is passed as a command-line option.
    //
    if(!desc.empty())
    {
        try
        {
            Ice::Identity regId;
            regId.category = instanceName;
            regId.name = "Registry";
            
            RegistryPrx registry = RegistryPrx::checkedCast(communicator()->getDefaultLocator()->findObjectById(regId));
            if(!registry)
            {
                throw "invalid registry";
            }
        
            registry = registry->ice_preferSecure(true); // Use SSL if available.
            
            IceGrid::AdminSessionPrx session;
            if(communicator()->getProperties()->getPropertyAsInt("IceGridAdmin.AuthenticateUsingSSL"))
            {
                session = registry->createAdminSessionFromSecureConnection();
            }
            else
            {
                string id = communicator()->getProperties()->getProperty("IceGridAdmin.Username");
                string password = communicator()->getProperties()->getProperty("IceGridAdmin.Password");
                while(id.empty())
                {
                    cout << "user id: " << flush;
                    getline(cin, id);
                    id = IceUtilInternal::trim(id);
                }
                
                if(password.empty())
                {
                    cout << "password: " << flush;
                    getline(cin, password);
                    password = IceUtilInternal::trim(password);
                }
                
                session = registry->createAdminSession(id, password);
            }
            assert(session);

            AdminPrx admin = session->getAdmin();
            map<string, string> vars;
            ApplicationDescriptor app = DescriptorParser::parseDescriptor(desc, targets, vars, communicator(), admin);

            try
            {
                admin->syncApplication(app);
            }
            catch(const ApplicationNotExistException&)
            {
                admin->addApplication(app);
            }
        }
        catch(const DeploymentException& ex)
        {
            ServiceWarning warn(this);
            warn << "failed to deploy application `" << desc << "':\n" << ex;
        }
        catch(const AccessDeniedException& ex)
        {
            ServiceWarning warn(this);
            warn << "failed to deploy application `" << desc << "':\n" 
                 << "registry database is locked by `" << ex.lockUserId << "'";
        }
        catch(const std::exception& ex)
        {
            ServiceWarning warn(this);
            warn << "failed to deploy application `" << desc << "':\n" << ex;
        }
        catch(const string& reason)
        {
            ServiceWarning warn(this);
            warn << "failed to deploy application `" << desc << "':\n" << reason;
        }
    }

    if(!bundleName.empty())
    {
        print(bundleName + " ready");
    }

    return true;
}

void
NodeService::waitForShutdown()
{
    //
    // Wait for the activator shutdown. Once the run method returns
    // all the servers have been deactivated.
    //
    enableInterrupt();
    _activator->waitForShutdown();
    disableInterrupt();
}

bool
NodeService::stop()
{
    if(_activator)
    {
        try
        {
            _activator->shutdown();
            _activator->destroy();
        }
        catch(...)
        {
            assert(false);
        }
        _activator = 0;
    }

    if(_timer)
    {
        //
        // The timer must be destroyed after the activator and before the
        // communicator is shutdown.
        //
        try
        {
            _timer->destroy();
        }
        catch(...)
        {
            assert(false);
        }
        _timer = 0;
    }

    //
    // Deactivate the node object adapter.
    //
    if(_adapter)
    {
        try
        {
            _adapter->deactivate();
            _adapter = 0;
        }
        catch(const std::exception& ex)
        {
            ServiceWarning warn(this);
            warn << "unexpected exception while shutting down node:\n" << ex;
        }
    }

    //
    // Terminate the node sessions with the registries.
    //
    if(_sessions.get())
    {
        _sessions->destroy();
    }

    //
    // Stop the platform info thread.
    //
    if(_node)
    {
        _node->getPlatformInfo().stop();
    }

    //
    // We can now safely shutdown the communicator.
    //
    try
    {
        communicator()->shutdown();
        communicator()->waitForShutdown();
    }
    catch(const std::exception& ex)
    {
        ServiceWarning warn(this);
        warn << "unexpected exception while shutting down node:\n" << ex;
    }

    //
    // Break cylic reference counts.
    //
    if(_node)
    {
        _node->shutdown();
        _node = 0;
    }

    //
    // And shutdown the collocated registry.
    //
    if(_registry)
    {
        _registry->stop();
        _registry = 0;
    }

    return true;
}

CommunicatorPtr
NodeService::initializeCommunicator(int& argc, char* argv[], 
                                    const InitializationData& initializationData)
{
    InitializationData initData = initializationData;
    initData.properties = createProperties(argc, argv, initData.properties);

    //
    // Make sure that IceGridNode doesn't use collocation optimization
    //
    initData.properties->setProperty("Ice.Default.CollocationOptimized", "0");

    //
    // Delay creation of Admin object:
    //
    initData.properties->setProperty("Ice.Admin.DelayCreation", "1");

    //
    // Default backend database plugin is Freeze if none is specified.
    //
    if(initData.properties->getPropertyAsInt("IceGrid.Node.CollocateRegistry") > 0 &&
       initData.properties->getProperty("Ice.Plugin.DB").empty())
    {
        initData.properties->setProperty("Ice.Plugin.DB", "IceGridFreezeDB:createFreezeDB");
    }

    //
    // Setup the client thread pool size.
    //
    setupThreadPool(initData.properties, "Ice.ThreadPool.Client", 1, 100);

    return Service::initializeCommunicator(argc, argv, initData);
}

void
NodeService::usage(const string& appName)
{
    string options =
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.\n"
        "--nowarn             Don't print any security warnings.\n"
        "--readonly           Start the collocated master registry in read-only mode.\n"
        "--initdb-from-replica=<replica>\n"
        "                     Initialize the collocated registry database from the\n"
        "                     given replica.\n"
        "--deploy DESCRIPTOR [TARGET1 [TARGET2 ...]]\n"
        "                     Add or update descriptor in file DESCRIPTOR, with\n"
        "                     optional targets.\n";
#ifndef _WIN32
    options.append(
        "\n"
        "\n"
        "--daemon             Run as a daemon.\n"
        "--noclose            Do not close open file descriptors.\n"
        "--nochdir            Do not change the current working directory.\n"
        "--pidfile FILE       Write process ID into FILE."
    );
#endif
    print("Usage: " + appName + " [options]\n" + options);
}

#ifdef _WIN32

int
wmain(int argc, wchar_t* argv[])

#else

int
main(int argc, char* argv[])

#endif
{
    NodeService svc;
    return svc.main(argc, argv);
}
