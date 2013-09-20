// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Glacier2/PermissionsVerifier.h>
#include <IceSSL/Plugin.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;

class ClientPermissionsVerifierI : public Glacier2::PermissionsVerifier
{
public:

    virtual bool
    checkPermissions(const string& userId, const string& passwd, string&, const Ice::Current& current) const
    {
        if(current.ctx.find("throw") != current.ctx.end())
        {
            throw Test::ExtendedPermissionDeniedException("reason");
        }
        return (userId == "client1" && passwd == "test1") || (userId == "client2" && passwd == "test2");
    }
};

class SSLPermissionsVerifierI : public Glacier2::SSLPermissionsVerifier
{
public:

    virtual bool
    authorize(const Glacier2::SSLInfo& info, string&, const Ice::Current& current) const
    {
        if(current.ctx.find("throw") != current.ctx.end())
        {
            throw Test::ExtendedPermissionDeniedException("reason");
        }

        IceSSL::CertificatePtr cert = IceSSL::Certificate::decode(info.certs[0]);
        test(cert->getIssuerDN() == IceSSL::DistinguishedName(
            "emailAddress=info@zeroc.com,CN=ZeroC Test CA,OU=Ice,O=ZeroC\\, Inc.,L=Palm Beach Gardens,"
            "ST=Florida,C=US"));
        test(cert->getSubjectDN() == IceSSL::DistinguishedName(
            "CN=Client,emailAddress=info@zeroc.com,OU=Ice,O=ZeroC\\, Inc.,ST=Florida,C=US"));
        test(cert->checkValidity());

        return true;
    }
};

class Server : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[]);
};

int
Server::run(int, char**)
{
    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("Server");
    if(communicator()->getProperties()->getPropertyAsInt("AddPermissionsVerifiers") > 0)
    {
        adapter->add(new ClientPermissionsVerifierI(), communicator()->stringToIdentity("ClientPermissionsVerifier"));
        adapter->add(new SSLPermissionsVerifierI(), communicator()->stringToIdentity("SSLPermissionsVerifier"));
    }
    adapter->activate();

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
    Server app;
    int rc = app.main(argc, argv);
    return rc;
}
