// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/DisableWarnings.h>
#include <IceUtil/Options.h>
#include <IceUtil/CtrlCHandler.h>
#include <IceUtil/Thread.h>
#include <IceUtil/StringUtil.h>
#include <IceUtil/UUID.h>
#include <IceUtil/Mutex.h>
#include <IceUtil/MutexPtrLock.h>
#include <Ice/Ice.h>
#include <Ice/SliceChecksums.h>
#include <IceGrid/Parser.h>
#include <IceGrid/FileParserI.h>
#include <IceGrid/Registry.h>
#include <IceGrid/Locator.h>
#include <Glacier2/Router.h>
#include <fstream>

//
// For getPassword()
//
#ifndef _WIN32
#   include <termios.h>
#else
#   include <conio.h>
#endif

using namespace std;
using namespace Ice;
using namespace IceGrid;

class Client;

namespace
{

IceUtil::Mutex* _staticMutex = 0;
Client* _globalClient = 0;

class Init
{
public:

    Init()
    {
        _staticMutex = new IceUtil::Mutex;
    }

    ~Init()
    {
        delete _staticMutex;
        _staticMutex = 0;
    }
};

Init init;

}

class SessionKeepAliveThread : public IceUtil::Thread, public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    SessionKeepAliveThread(const AdminSessionPrx& session, long timeout) :
        IceUtil::Thread("IceGrid admin session keepalive thread"),
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
            catch(const Exception&)
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

    AdminSessionPrx _session;
    const IceUtil::Time _timeout;
    bool _destroy;
};
typedef IceUtil::Handle<SessionKeepAliveThread> SessionKeepAliveThreadPtr;

class ReuseConnectionRouter : public Router
{
public:
    
    ReuseConnectionRouter(const ObjectPrx& proxy) : _clientProxy(proxy)
    {
    }

    virtual ObjectPrx 
    getClientProxy(const Current&) const
    {
        return _clientProxy;
    }

    virtual ObjectPrx 
    getServerProxy(const Current&) const
    {
        return 0;
    }

    virtual void
    addProxy(const ObjectPrx&, const Current&)
    {
    }

    virtual ObjectProxySeq 
    addProxies(const ObjectProxySeq&, const Current&)
    {
        return ObjectProxySeq();
    }
    
private:

    const ObjectPrx _clientProxy;
};

class Client : public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    void usage();
    int main(StringSeq& args);
    int run(StringSeq& args);
    void interrupted();

    CommunicatorPtr communicator() const { return _communicator; }
    const string& appName() const { return _appName; }

    string getPassword(const string&);

private:

    IceUtil::CtrlCHandler _ctrlCHandler;
    CommunicatorPtr _communicator;
    string _appName;
    ParserPtr _parser;
};

static void
interruptCallback(int /*signal*/)
{
    IceUtilInternal::MutexPtrLock<IceUtil::Mutex> lock(_staticMutex);
    if(_globalClient)
    {
        _globalClient->interrupted();
    }
}

#ifdef _WIN32

int
wmain(int argc, wchar_t* argv[])

#else

int
main(int argc, char* argv[])

#endif
{
    Client app;
    StringSeq args = argsToStringSeq(argc, argv);
    return app.main(args);
}

void
Client::usage()
{
    cerr << "Usage: " << appName() << " [options]\n";
    cerr <<     
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.\n"
        "-e COMMANDS          Execute COMMANDS.\n"
        "-d, --debug          Print debug messages.\n"
        "-s, --server         Start icegridadmin as a server (to parse XML files).\n"
        "-u, --username       Login with the given username.\n"
        "-p, --password       Login with the given password.\n"
        "-S, --ssl            Authenticate through SSL.\n"
        "-r, --replica NAME   Connect to the replica NAME.\n"
        ;
}


int
Client::main(StringSeq& args)
{
    int status = EXIT_SUCCESS;

    try
    {
        _appName = args[0];
        InitializationData id;
        id.properties = createProperties(args);
        //
        // We don't want to load DB plug-ins with icegridadmin, as this will
        // cause FileLock issues when run with the same configuration file
        // used by the service.
        //
        id.properties->setProperty("Ice.Plugin.DB", "");
        _communicator = initialize(id);

        {
            IceUtilInternal::MutexPtrLock<IceUtil::Mutex> sync(_staticMutex);
            _globalClient = this;
        }
        _ctrlCHandler.setCallback(interruptCallback);

        try
        {
            status = run(args);
        }
        catch(const CommunicatorDestroyedException&)
        {
            // Expected if the client is interrupted during the initialization.
        }
    }
    catch(const IceUtil::Exception& ex)
    {
        cerr << _appName << ": " << ex << endl;
        status = EXIT_FAILURE;
    }
    catch(const std::exception& ex)
    {
        cerr << _appName << ": std::exception: " << ex.what() << endl;
        status = EXIT_FAILURE;
    }
    catch(const std::string& msg)
    {
        cerr << _appName << ": " << msg << endl;
        status = EXIT_FAILURE;
    }
    catch(const char* msg)
    {
        cerr << _appName << ": " << msg << endl;
        status = EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << _appName << ": unknown exception" << endl;
        status = EXIT_FAILURE;
    }

    if(_communicator)
    {
        try
        {
            _communicator->destroy();
        }
        catch(const CommunicatorDestroyedException&)
        {
        }
        catch(const Exception& ex)
        {
            cerr << ex << endl;
            status = EXIT_FAILURE;
        }
    }

    _ctrlCHandler.setCallback(0);
    {
        IceUtilInternal::MutexPtrLock<IceUtil::Mutex> sync(_staticMutex);
        _globalClient = 0;
    }

    return status;
        
}

void
Client::interrupted()
{
    Lock sync(*this);
    if(_parser) // If there's an interactive parser, notify the parser.
    {
        _parser->interrupt();
    }
    else
    {
        //
        // Otherwise, destroy the communicator.
        //
        assert(_communicator);
        try
        {
            _communicator->destroy();
        }
        catch(const Exception&)
        {
        }
    }
}

int
Client::run(StringSeq& originalArgs)
{
    string commands;
    bool debug;

    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");
    opts.addOpt("e", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("u", "username", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::NoRepeat);
    opts.addOpt("p", "password", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::NoRepeat);
    opts.addOpt("S", "ssl");
    opts.addOpt("d", "debug");
    opts.addOpt("s", "server");
    opts.addOpt("r", "replica", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::NoRepeat);

    vector<string> args;
    try
    {
        args = opts.parse(originalArgs);
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        cerr << e.reason << endl;
        usage();
        return EXIT_FAILURE;
    }
    if(!args.empty())
    {
        cerr << _appName << ": too many arguments" << endl;
        usage();
        return EXIT_FAILURE;
    }

    if(opts.isSet("help"))
    {
        usage();
        return EXIT_SUCCESS;
    }
    if(opts.isSet("version"))
    {
        cout << ICE_STRING_VERSION << endl;
        return EXIT_SUCCESS;
    }

    if(opts.isSet("server"))
    {
        ObjectAdapterPtr adapter = 
            communicator()->createObjectAdapterWithEndpoints("FileParser", "tcp -h localhost");
        adapter->activate();
        ObjectPrx proxy = adapter->add(new FileParserI, communicator()->stringToIdentity("FileParser"));
        cout << proxy << endl;

        communicator()->waitForShutdown();
        return EXIT_SUCCESS;
    }

    if(opts.isSet("e"))
    {
        vector<string> optargs = opts.argVec("e");
        for(vector<string>::const_iterator i = optargs.begin(); i != optargs.end(); ++i)
        {
            commands += *i + ";";
        }
    }
    debug = opts.isSet("debug");

    bool ssl = communicator()->getProperties()->getPropertyAsInt("IceGridAdmin.AuthenticateUsingSSL");
    if(opts.isSet("ssl"))
    {
        ssl = true;
    }

    string id = communicator()->getProperties()->getProperty("IceGridAdmin.Username");
    if(!opts.optArg("username").empty())
    {
        id = opts.optArg("username");
    }
    string password = communicator()->getProperties()->getProperty("IceGridAdmin.Password");
    if(!opts.optArg("password").empty())
    {
        password = opts.optArg("password");
    }

    PropertiesPtr properties = communicator()->getProperties();
    string replica = properties->getProperty("IceGridAdmin.Replica");
    if(!opts.optArg("replica").empty())
    {
        replica = opts.optArg("replica");
    }

    Glacier2::RouterPrx router;
    AdminSessionPrx session;
    SessionKeepAliveThreadPtr keepAlive;
    int status = EXIT_SUCCESS;
    try
    {
        int timeout;
        if(communicator()->getDefaultRouter())
        {
            try
            {
                // Use SSL if available.
                router = Glacier2::RouterPrx::checkedCast(communicator()->getDefaultRouter()->ice_preferSecure(true));
                if(!router)
                {
                    cerr << _appName << ": configured router is not a Glacier2 router" << endl;
                    return EXIT_FAILURE;
                }
            }
            catch(const LocalException& ex)
            {
                cerr << _appName << ": could not contact the default router:" << endl << ex << endl;
                return EXIT_FAILURE;                
            }

            if(ssl)
            {
                session = AdminSessionPrx::uncheckedCast(router->createSessionFromSecureConnection());
                if(!session)
                {
                    cerr << _appName
                         << ": Glacier2 returned a null session, please set the Glacier2.SSLSessionManager property"
                         << endl;
                    return EXIT_FAILURE;
                }
            }
            else
            {
                while(id.empty() && cin.good())
                {
                    cout << "user id: " << flush;
                    getline(cin, id);
                    if(!cin.good())
                    {
                        return EXIT_FAILURE;
                    }
                    id = IceUtilInternal::trim(id);
                }
                
                if(password.empty())
                {
                    password = getPassword("password: ");
#ifndef _WIN32
                    if(!cin.good())
                    {
                        return EXIT_FAILURE;
                    }
#endif
                }
                     
                session = AdminSessionPrx::uncheckedCast(router->createSession(id, password));
                // Zero the password string.
                for(string::iterator p = password.begin(); p != password.end(); ++p)
                {
                    *p = '\0';
                }
                if(!session)
                {
                    cerr << _appName
                         << ": Glacier2 returned a null session, please set the Glacier2.SessionManager property"
                         << endl;
                    return EXIT_FAILURE;
                }
            }
            timeout = static_cast<int>(router->getSessionTimeout());
        }
        else if(communicator()->getDefaultLocator())
        {
            //
            // Create the identity of the registry to connect to.
            //
            Identity registryId;
            registryId.category = communicator()->getDefaultLocator()->ice_getIdentity().category;
            registryId.name = "Registry";
            if(!replica.empty() && replica != "Master")
            {
                registryId.name += "-" + replica;
            }

            //
            // First try to contact the locator. If we can't talk to the locator,
            // no need to go further. Otherwise, we get the proxy of local registry 
            // proxy.
            //
            IceGrid::LocatorPrx locator;
            RegistryPrx localRegistry;
            try
            {
                locator = IceGrid::LocatorPrx::checkedCast(communicator()->getDefaultLocator());
                if(!locator)
                {
                    cerr << _appName << ": configured locator is not an IceGrid locator" << endl;
                    return EXIT_FAILURE;
                }
                localRegistry = locator->getLocalRegistry();
            }
            catch(const LocalException& ex)
            {
                cerr << _appName << ": could not contact the default locator:" << endl << ex << endl;
                return EXIT_FAILURE;                    
            }
            
            IceGrid::RegistryPrx registry;
            if(localRegistry->ice_getIdentity() == registryId)
            {
                registry = localRegistry;
            }
            else
            {
                //
                // The locator local registry isn't the registry we want to connect to.
                //

                try
                {
                    registry = RegistryPrx::checkedCast(locator->findObjectById(registryId));
                    if(!registry)
                    {
                        cerr << _appName << ": could not contact an IceGrid registry" << endl;
                    }
                }
                catch(const ObjectNotFoundException&)
                {
                    cerr << _appName << ": no active registry replica named `" << replica << "'" << endl;
                    return EXIT_FAILURE;            
                }
                catch(const LocalException& ex)
                {
                    if(!replica.empty())
                    {
                        cerr << _appName << ": could not contact the registry replica named `" << replica << "':\n";
                        cerr << ex << endl;
                        return EXIT_FAILURE;            
                    }
                    else
                    {
                        //
                        // If we can't contact the master, use to the local registry.
                        //
                        registry = localRegistry;
                        string name = registry->ice_getIdentity().name;
                        const string prefix("Registry-");
                        string::size_type pos = name.find(prefix);
                        if(pos != string::npos)
                        {
                            name = name.substr(prefix.size());
                        }
                        cerr << _appName << ": warning: could not contact master, using slave `" << name << "'" << endl;
                    }
                }
            }

            //
            // If the registry to use is the locator local registry, we install a default router
            // to ensure we'll use a single connection regardless of the endpoints returned in the
            // proxies of the various session/admin methods (useful if used over an ssh tunnel).
            //
            if(registry->ice_getIdentity() == localRegistry->ice_getIdentity())
            {
                properties->setProperty("CollocInternal.AdapterId", IceUtil::generateUUID());
                ObjectAdapterPtr colloc = communicator()->createObjectAdapter("CollocInternal");
                colloc->setLocator(0);
                ObjectPrx router = colloc->addWithUUID(new ReuseConnectionRouter(locator));
                communicator()->setDefaultRouter(RouterPrx::uncheckedCast(router));
                registry = registry->ice_router(communicator()->getDefaultRouter());
            }

            // Prefer SSL.
            registry = registry->ice_preferSecure(true);

            if(ssl)
            {
                session = registry->createAdminSessionFromSecureConnection();
            }
            else
            {
                while(id.empty() && cin.good())
                {
                    cout << "user id: " << flush;
                    getline(cin, id);
                    if(!cin.good())
                    {
                        return EXIT_FAILURE;
                    }
                    id = IceUtilInternal::trim(id);
                }
                
                if(password.empty())
                {
                    password = getPassword("password: ");
#ifndef _WIN32
                    if(!cin.good())
                    {
                        return EXIT_FAILURE;
                    }
#endif
                }
                    
                session = registry->createAdminSession(id, password);
                // Zero the password string.
                for(string::iterator p = password.begin(); p != password.end(); ++p)
                {
                    *p = '\0';
                }
            }

            timeout = registry->getSessionTimeout();
        }
        else // No default locator or router set.
        {
            cerr << _appName << ": could not contact the registry:" << endl;
            cerr << "no default locator or router configured" << endl;
            return EXIT_FAILURE;            
        }

        if(timeout > 0)
        {
            keepAlive = new SessionKeepAliveThread(session, timeout / 2);
            keepAlive->start();
        }

        AdminPrx admin = session->getAdmin();

        SliceChecksumDict serverChecksums = admin->getSliceChecksums();
        SliceChecksumDict localChecksums = sliceChecksums();

        //
        // The following slice types are only used by the admin CLI.
        //
        localChecksums.erase("::IceGrid::FileParser");
        localChecksums.erase("::IceGrid::ParseException");
                         
        for(SliceChecksumDict::const_iterator q = localChecksums.begin(); q != localChecksums.end(); ++q)
        {
            SliceChecksumDict::const_iterator r = serverChecksums.find(q->first);
            if(r == serverChecksums.end())
            {
                cerr << appName() << ": server is using unknown Slice type `" << q->first << "'" << endl;
            }
            else if(q->second != r->second)
            {
                cerr << appName() << ": server is using a different Slice definition of `" << q->first << "'" << endl;
            }
        }

        {
            Lock sync(*this);
            _parser = Parser::createParser(communicator(), session, admin, commands.empty());
        }    

        if(!commands.empty()) // Commands were given
        {
            int parseStatus = _parser->parse(commands, debug);
            if(parseStatus == EXIT_FAILURE)
            {
                status = EXIT_FAILURE;
            }
        }
        else // No commands, let's use standard input
        {
            _parser->showBanner();
            
            int parseStatus = _parser->parse(stdin, debug);
            if(parseStatus == EXIT_FAILURE)
            {
                status = EXIT_FAILURE;
            }
        }
    }
    catch(const IceGrid::PermissionDeniedException& ex)
    {
        cout << "permission denied:\n" << ex.reason << endl;
        return EXIT_FAILURE;
    }
    catch(const Glacier2::PermissionDeniedException& ex)
    {
        cout << "permission denied:\n" << ex.reason << endl;
        return EXIT_FAILURE;
    }
    catch(const Glacier2::CannotCreateSessionException& ex)
    {
        cout << "session creation failed:\n" << ex.reason << endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        if(keepAlive)
        {
            keepAlive->destroy();
            keepAlive->getThreadControl().join();
        }

        try
        {
            if(router)
            {
                router->destroySession();
            }
            else if(session)
            {
                session->destroy();
            }
        }
        catch(const Exception&)
        {
        }
        throw;
    }

    if(keepAlive)
    {
        keepAlive->destroy();
        keepAlive->getThreadControl().join();
    }

    if(session)
    {
        try
        {
            if(router)
            {
                router->destroySession();
            }
            else
            {
                session->destroy();
            }
        }
        catch(const Exception&)
        {
            // Ignore. If the registry has been shutdown this will cause
            // an exception.
        }
    }

    return status;
}

string
Client::getPassword(const string& prompt)
{
    cout << prompt << flush;
    string password;
#ifndef _WIN32
    struct termios oldConf;
    struct termios newConf;
    tcgetattr(0, &oldConf);
    newConf = oldConf;
    newConf.c_lflag &= (~ECHO);
    tcsetattr(0, TCSANOW, &newConf);
    getline(cin, password);
    tcsetattr(0, TCSANOW, &oldConf);
#else
    char c;
    while((c = _getch()) != '\r')
    {
        password += c;
    }
#endif
    cout << endl;
    return IceUtilInternal::trim(password);
}
