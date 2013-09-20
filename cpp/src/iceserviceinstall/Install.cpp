// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceUtil/Options.h>
#include <ServiceInstaller.h>

using namespace std;
using namespace Ice;

class Install : public Application
{
public:
    virtual int run(int, char*[]);

    Install();

    bool pauseEnabled() const;
    bool debug() const;
    bool pause() const;

private:

    void usage() const;

    bool _debug;
    bool _pauseEnabled;
    bool _pause;
};

int
wmain(int argc, wchar_t* argv[])
{
    Install app;
    InitializationData id;
    id.properties = Ice::createProperties();
    id.properties->setProperty("Ice.Plugin.IceSSL", "IceSSL:createIceSSL");
    int status = app.main(argc, argv, id);

    if(app.pauseEnabled() && (app.pause() || app.debug() || status != 0))
    {
        system("pause");
    }

    return status;
}

int
Install::run(int argc, char* argv[])
{
    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");
    opts.addOpt("u", "uninstall");
    opts.addOpt("n", "nopause");

    vector<string> propNames = IceServiceInstaller::getPropertyNames();

    for(size_t i = 0; i < propNames.size(); ++i)
    {
        opts.addOpt("", propNames[i], IceUtilInternal::Options::NeedArg);
    }

    vector<string> commands;
    try
    {
        commands = opts.parse(argc, (const char**)argv);
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        cerr << "Error:" << e.reason << endl;
        usage();
        return EXIT_FAILURE;
    }

    _pauseEnabled = !opts.isSet("nopause");

    if(opts.isSet("help"))
    {
        usage();
        _pause = true;
        return EXIT_SUCCESS;
    }
    if(opts.isSet("version"))
    {
        cout << ICE_STRING_VERSION << endl;
        _pause = true;
        return EXIT_SUCCESS;
    }

    if(commands.size() != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    int serviceType = -1;
    for(int j = 0; j < IceServiceInstaller::serviceCount; ++j)
    {
        if(commands[0] == IceServiceInstaller::serviceTypeToLowerString(j))
        {
            serviceType = j;
            break; // for
        }
    }

    if(serviceType == -1)
    {
        cerr << "Invalid service " << commands[0] << endl;
        return EXIT_FAILURE;
    }

    string configFile = commands[1];

    try
    {
        IceServiceInstaller installer(serviceType, configFile, communicator());

        if(opts.isSet("uninstall"))
        {
            installer.uninstall();
        }
        else
        {
            PropertiesPtr properties = communicator()->getProperties();

            for(size_t j = 0; j < propNames.size(); ++j)
            {
                if(opts.isSet(propNames[j]))
                {
                    properties->setProperty(propNames[j], opts.optArg(propNames[j]));
                }
            }

            _debug = properties->getPropertyAsInt("Debug") != 0;

            installer.install(properties);
        }
    }
    catch(const string& msg)
    {
        cerr << "Error: " << msg << endl;
        return EXIT_FAILURE;
    }
    catch(const Ice::Exception& ex)
    {
        cerr << "Error: " << ex << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

Install::Install() :
    _pauseEnabled(true),
    _debug(false),
    _pause(false)
{
}

bool
Install::pauseEnabled() const
{
    return _pauseEnabled;
}

bool
Install::debug() const
{
    return _debug;
}

bool
Install::pause() const
{
    return _pause;
}

void
Install::usage() const
{
    cerr << "Usage: " << appName()
         << " [options] service config-file [property] [property]\n";
    cerr <<
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-n, --nopause        Do not call pause after displaying a message.\n"
        "-v, --version        Display the Ice version.\n"
        "-u, --uninstall      Uninstall the Windows service.\n"
        "\n"
        "service must be icegridregistry, icegridnode or glacier2router.\n"
        "\n"
        "config-file          Path to the Ice configuration file for this service.\n"
        "                     If the path starts with HKLM\\ the configuration will be\n"
        "                     read from the corresponding Windows registry keyword in\n"
        "                     HKEY_LOCAL_MACHINE.\n"
        "\n"
        "Valid properties:\n"
        "ImagePath            Full path to <service>.exe. The default value is\n"
        "                     <directory of " << appName() << ">\\<service>.exe\n"
        "DisplayName          Display name of the service.\n"
        "Description          Description of the service.\n"
        "AutoStart            If non-zero, the service is started automatically when\n"
        "                     the computer starts up. The default value is 1.\n"
        "ObjectName           Account used to run the service. Defaults to\n"
        "                     NT Authority\\LocalService.\n"
        "Password             Password for ObjectName.\n"
        "DependOnRegistry     If non-zero, the service depends on the IceGrid registry\n"
        "                     service (the IceGrid registry service name is computed\n"
        "                     using Ice.Default.Locator in <config-file>).\n"
        "EventLog             The name of the EventLog used by this service;\n"
        "                     the default is Application.\n"
        ;
}
