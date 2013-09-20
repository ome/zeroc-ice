// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/DisableWarnings.h>
#include <Ice/Ice.h>
#include <TestI.h>
#include <TestCommon.h>
#include <fstream>

using namespace std;

class Server : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[]);
};

int
Server::run(int argc, char* argv[])
{
    Ice::PropertiesPtr properties = communicator()->getProperties();

    Ice::StringSeq args = Ice::argsToStringSeq(argc, argv);
    args = properties->parseCommandLineOptions("Test", args);
    Ice::stringSeqToArgs(args, argc, argv);

    string name = properties->getProperty("Ice.ProgramName");
    Ice::ObjectAdapterPtr adapter;

    if(!properties->getProperty("ReplicatedAdapter").empty())
    {
        adapter = communicator()->createObjectAdapter("ReplicatedAdapter");
        adapter->activate();
    }
    
    adapter = communicator()->createObjectAdapter("Server");
    Ice::ObjectPtr object = new TestI(properties);
    adapter->add(object, communicator()->stringToIdentity(name));
    shutdownOnInterrupt();
    try
    {
        adapter->activate();
    }
    catch(const Ice::ObjectAdapterDeactivatedException&)
    {
    }
    communicator()->waitForShutdown();
    ignoreInterrupt();
    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    //
    // Test if MY_ENV_VARIABLE is set.
    //
    char* value = getenv("MY_ENV_VARIABLE");
    test(value != 0 && string(value) == "12");

    ifstream in("envs");
    if(!in)
    {
        test(false);
    }
    string unicodeVar;
    string varname1;
    string varname2;
    if(!getline(in, unicodeVar) || !getline(in, varname1) || !getline(in, varname2))
    {
        test(false);
    }

#if defined(_WIN32)
    wchar_t* value2 = _wgetenv(L"MY_ENV_UNICODE_VARIABLE");
    test(value2 != 0 && wstring(value2) == IceUtil::stringToWstring(unicodeVar));

    wchar_t* value3 = _wgetenv(IceUtil::stringToWstring(varname1).c_str());
    test(value3 != 0 && wstring(value3) == L"2");

    // Environment variables are case insensitive on Windows.
    wchar_t* value4 = _wgetenv(IceUtil::stringToWstring(varname1).c_str());
    test(value4 != 0 && wstring(value4) == L"2");

    char* value5 = getenv("MY_WINDOWS_COMPOSED_VARIABLE");
    test(value5 != 0 && string(value5) == "BAR;12");

#else
    char* value2 = getenv("MY_ENV_UNICODE_VARIABLE");
    test(value2 !=0 && string(value2) == unicodeVar);

    char* value3 = getenv(varname1.c_str());
    test(value3 != 0 && string(value3) == "1");

    char* value4 = getenv(varname2.c_str());
    test(value4 != 0 && string(value4) == "2");
    
    char* value5 = getenv("MY_UNIX_COMPOSED_VARIABLE");
    test(value5 != 0 && string(value5) == "BAR;12");
#endif

    Server app;
    int rc = app.main(argc, argv);
    return rc;
}
