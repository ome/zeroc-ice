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
#include <IceUtil/FileUtil.h>
#include <IceUtil/ArgVector.h>

using namespace std;

namespace
{

string configPath;

class Client : public Ice::Application
{
public:
    virtual int
    run(int, char*[])
    {
        Ice::PropertiesPtr properties = communicator()->getProperties();
        test(properties->getProperty("Ice.Trace.Network") == "1");
        test(properties->getProperty("Ice.Trace.Protocol") == "1");
        test(properties->getProperty("Config.Path") == configPath);
        test(properties->getProperty("Ice.ProgramName") == "PropertiesClient");
        test(appName() == properties->getProperty("Ice.ProgramName"));
        return EXIT_SUCCESS;
    };
};

}

int
main(int argc, char* argv[])
{
    ifstream in("./config/configPath");
    if(!in)
    {
        test(false);
    }
    
    if(!getline(in, configPath))
    {
        test(false);
    }
    try
    {
        cout << "testing load properties from UTF-8 path... " << flush;
        Ice::PropertiesPtr properties = Ice::createProperties();
        properties->load(configPath);
        test(properties->getProperty("Ice.Trace.Network") == "1");
        test(properties->getProperty("Ice.Trace.Protocol") == "1");       
        test(properties->getProperty("Config.Path") == configPath);
        test(properties->getProperty("Ice.ProgramName") == "PropertiesClient");
        cout << "ok" << endl;
    }
    catch(const Ice::Exception& ex)
    {
        cerr << ex << endl;
        return EXIT_FAILURE;
    }
    
    cout << "testing load properties from UTF-8 path using Ice::Application... " << flush;
    Client c;
    c.main(argc, argv, configPath.c_str());
    cout << "ok" << endl;
    
    try
    {
        //
        // Try to load multiple config files.
        //
        cout << "testing using Ice.Config with multiple config files... " << flush;
        Ice::PropertiesPtr properties;
        Ice::StringSeq args;
        args.push_back("--Ice.Config=config/config.1, config/config.2, config/config.3");
        IceUtilInternal::ArgVector a(args);
        properties = Ice::createProperties(a.argc, a.argv);
        test(properties->getProperty("Config1") == "Config1");
        test(properties->getProperty("Config2") == "Config2");
        test(properties->getProperty("Config3") == "Config3");
        cout << "ok" << endl;
    }
    catch(const Ice::Exception& ex)
    {
        cerr << ex << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
