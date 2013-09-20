// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceSSL/Plugin.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;
using namespace Ice;

class PasswordPromptI : public IceSSL::PasswordPrompt
{
public:

    PasswordPromptI(const string& password) : _password(password), _count(0)
    {
    }

    virtual string getPassword()
    {
        ++_count; 
        return _password;
    }

    int count() const
    {
        return _count;
    }

private:

    string _password;
    int _count;
};
typedef IceUtil::Handle<PasswordPromptI> PasswordPromptIPtr;

class CertificateVerifierI : public IceSSL::CertificateVerifier
{
public:

    CertificateVerifierI()
    {
        reset();
    }

    virtual bool
    verify(const IceSSL::NativeConnectionInfoPtr& info)
    {
        if(info->nativeCerts.size() > 0)
        {
            //
            // Subject alternative name
            //
            {
                vector<pair<int, string> > altNames = info->nativeCerts[0]->getSubjectAlternativeNames();
                vector<string> ipAddresses;
                vector<string> dnsNames;
                for(vector<pair<int, string> >::const_iterator p = altNames.begin(); p != altNames.end(); ++p)
                {
                    if(p->first == 7)
                    {
                        ipAddresses.push_back(p->second);
                    }
                    else if(p->first == 2)
                    {
                        dnsNames.push_back(p->second);
                    }
                }

                test(find(dnsNames.begin(), dnsNames.end(), "server") != dnsNames.end());
                test(find(ipAddresses.begin(), ipAddresses.end(), "127.0.0.1") != ipAddresses.end());
            }

            //
            // Issuer alternative name
            //
            {
                vector<pair<int, string> > altNames = info->nativeCerts[0]->getIssuerAlternativeNames();
                vector<string> ipAddresses;
                vector<string> emailAddresses;
                for(vector<pair<int, string> >::const_iterator p = altNames.begin(); p != altNames.end(); ++p)
                {
                    if(p->first == 7)
                    {
                        ipAddresses.push_back(p->second);
                    }
                    else if(p->first == 1)
                    {
                        emailAddresses.push_back(p->second);
                    }
                }

                test(find(ipAddresses.begin(), ipAddresses.end(), "127.0.0.1") != ipAddresses.end());
                test(find(emailAddresses.begin(), emailAddresses.end(), "issuer@zeroc.com") != emailAddresses.end());
            }
        }

        _hadCert = info->nativeCerts.size() != 0;
        _invoked = true;
        return _returnValue;
    }

    void reset()
    {
        _returnValue = true;
        _invoked = false;
        _hadCert = false;
    }

    void returnValue(bool b)
    {
        _returnValue = b;
    }

    bool invoked() const
    {
        return _invoked;
    }

    bool hadCert() const
    {
        return _hadCert;
    }

private:

    bool _returnValue;
    bool _invoked;
    bool _hadCert;
};
typedef IceUtil::Handle<CertificateVerifierI> CertificateVerifierIPtr;

static PropertiesPtr
createClientProps(const Ice::PropertiesPtr& defaultProperties, const string& defaultDir, const string& defaultHost)
{
    PropertiesPtr result = createProperties();
    result->setProperty("Ice.Plugin.IceSSL", "IceSSL:createIceSSL");
    result->setProperty("IceSSL.DefaultDir", defaultDir);
    if(!defaultProperties->getProperty("Ice.IPv6").empty())
    {
        result->setProperty("Ice.IPv6", defaultProperties->getProperty("Ice.IPv6"));
    }
    if(!defaultHost.empty())
    {
        result->setProperty("Ice.Default.Host", defaultHost);
    }
    return result;
}

static Test::Properties
createServerProps(const Ice::PropertiesPtr& defaultProperties, const string& defaultDir, const string& defaultHost)
{
    Test::Properties result;
    result["Ice.Plugin.IceSSL"] = "IceSSL:createIceSSL";
    result["IceSSL.DefaultDir"] = defaultDir;
    if(!defaultProperties->getProperty("Ice.IPv6").empty())
    {
        result["Ice.IPv6"] = defaultProperties->getProperty("Ice.IPv6");
    }
    if(!defaultHost.empty())
    {
        result["Ice.Default.Host"] = defaultHost;
    }
    return result;
}

void
allTests(const CommunicatorPtr& communicator, const string& testDir)
{
    string factoryRef = "factory:tcp -p 12010";
    ObjectPrx base = communicator->stringToProxy(factoryRef);
    test(base);
    Test::ServerFactoryPrx factory = Test::ServerFactoryPrx::checkedCast(base);

    string defaultHost = communicator->getProperties()->getProperty("Ice.Default.Host");
    string defaultDir = testDir + "/../certs";
    Ice::PropertiesPtr defaultProperties = communicator->getProperties();
#ifdef _WIN32
    string sep = ";";
#else
    string sep = ":";
#endif

    cout << "testing manual initialization... " << flush;
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("Ice.InitPlugins", "0");
        CommunicatorPtr comm = initialize(initData);
        ObjectPrx p = comm->stringToProxy("dummy:ssl -p 9999");
        try
        {
            p->ice_ping();
            test(false);
        }
        catch(const PluginInitializationException&)
        {
            // Expected.
        }
        catch(const LocalException&)
        {
            test(false);
        }
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("Ice.InitPlugins", "0");
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        CommunicatorPtr comm = initialize(initData);
        PluginManagerPtr pm = comm->getPluginManager();
        pm->initializePlugins();
        ObjectPrx obj = comm->stringToProxy(factoryRef);
        test(obj);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(obj);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.Ciphers"] = "ADH";
        d["IceSSL.VerifyPeer"] = "0";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing certificate verification... " << flush;
    {
        //
        // Test IceSSL.VerifyPeer=0. Client does not have a certificate,
        // but it still verifies the server's. The createClientProps
        // function defines IceSSL.DefaultDir, which allows OpenSSL in the
        // client to find the CA certificate. We remove that property here
        // to verify that the connection can still proceed without any
        // CA certificate.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        initData.properties->setProperty("IceSSL.DefaultDir", "");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "0";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->noCert();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        //
        // Validate that we can get the connection info.
        //
        try
        {
            IceSSL::NativeConnectionInfoPtr info = 
                IceSSL::NativeConnectionInfoPtr::dynamicCast(server->ice_getConnection()->getInfo());
            test(info->nativeCerts.size() == 2);
        }
        catch(const Ice::LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        //
        // Test IceSSL.VerifyPeer=1. Client does not have a certificate.
        //
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "1";
        server = fact->createServer(d);
        try
        {
            server->noCert();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        //
        // Test IceSSL.VerifyPeer=2. This should fail because the client
        // does not supply a certificate.
        //
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "2";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
#ifdef _WIN32
        catch(const ConnectionLostException&)
        {
            // Expected.
        }
#endif
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        comm->destroy();

        //
        // Test IceSSL.VerifyPeer=1. Client has a certificate.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "1";
        server = fact->createServer(d);
        try
        {
            IceSSL::CertificatePtr clientCert =
                IceSSL::Certificate::load(defaultDir + "/c_rsa_nopass_ca1_pub.pem");
            server->checkCert(clientCert->getSubjectDN(), clientCert->getIssuerDN());

            //
            // Validate that we can get the connection info. Validate
            // that the certificates have the same DN.
            //
            // Validate some aspects of the Certificate class.
            //
            IceSSL::CertificatePtr serverCert =
                IceSSL::Certificate::load(defaultDir + "/s_rsa_nopass_ca1_pub.pem");
            test(IceSSL::Certificate::decode(serverCert->encode()) == serverCert);
            test(serverCert == serverCert);
            test(serverCert->checkValidity());
            test(!serverCert->checkValidity(IceUtil::Time::seconds(0)));

            IceSSL::CertificatePtr caCert = IceSSL::Certificate::load(defaultDir + "/cacert1.pem");
            test(caCert == caCert);
            test(caCert->checkValidity());
            test(!caCert->checkValidity(IceUtil::Time::seconds(0)));

            test(!serverCert->verify(serverCert->getPublicKey()));
            test(serverCert->verify(caCert->getPublicKey()));
            test(caCert->verify(caCert->getPublicKey()));

            IceSSL::NativeConnectionInfoPtr info = 
                IceSSL::NativeConnectionInfoPtr::dynamicCast(server->ice_getConnection()->getInfo());

            test(info->nativeCerts.size() == 2);

            test(caCert == info->nativeCerts[1]);
            test(serverCert == info->nativeCerts[0]);

            test(serverCert != info->nativeCerts[1]);
            test(caCert != info->nativeCerts[0]);

            test(info->nativeCerts[0]->checkValidity() && info->nativeCerts[1]->checkValidity());
            test(!info->nativeCerts[0]->checkValidity(IceUtil::Time::seconds(0)) &&
                 !info->nativeCerts[1]->checkValidity(IceUtil::Time::seconds(0)));
            test(info->nativeCerts[0]->verify(info->nativeCerts[1]->getPublicKey()));
            test(info->nativeCerts.size() == 2 &&
                 info->nativeCerts[0]->getSubjectDN() == serverCert->getSubjectDN() &&
                 info->nativeCerts[0]->getIssuerDN() == serverCert->getIssuerDN());
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        //
        // Test IceSSL.VerifyPeer=2. Client has a certificate.
        //
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "2";
        server = fact->createServer(d);
        try
        {
            IceSSL::CertificatePtr clientCert =
                IceSSL::Certificate::load(defaultDir + "/c_rsa_nopass_ca1_pub.pem");
            server->checkCert(clientCert->getSubjectDN(), clientCert->getIssuerDN());
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        comm->destroy();

        //
        // Test IceSSL.VerifyPeer=1. This should fail because the client doesn't
        // trust the server's CA. We disable IceSSL.DefaultDir in the client so that
        // OpenSSL can't search for the server's CA certificate.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.DefaultDir", "");
        initData.properties->setProperty("IceSSL.VerifyPeer", "1");
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "0";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
#ifdef _WIN32
        catch(const ConnectionLostException&)
        {
            // Expected.
        }
#endif
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        comm->destroy();

        //
        // Test IceSSL.VerifyPeer=1. This should fail because the server doesn't
        // trust the client's CA. The IceSSL.DefaultDir setting in the client
        // allows OpenSSL to find the server's CA certificate. We have to disable
        // IceSSL.DefaultDir in the server so that it can't find the client's CA
        // certificate.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert2.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca2_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca2_priv.pem");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d.erase("IceSSL.DefaultDir");
        d["IceSSL.CertAuthFile"] = defaultDir + "/cacert1.pem";
        d["IceSSL.CertFile"] = defaultDir + "/s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = defaultDir + "/s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "1";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
#ifdef _WIN32
        catch(const ConnectionLostException&)
        {
            // Expected.
        }
#endif
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);

        comm->destroy();

        //
        // Verify that IceSSL.CheckCertName has no effect in a server.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        comm = initialize(initData);

        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.CheckCertName"] = "1";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();

        //
        // Test IceSSL.CheckCertName. The test certificates for the server contain "127.0.0.1"
        // as the common name or as a subject alternative name, so we only perform this test when
        // the default host is "127.0.0.1".
        //
        if(defaultHost == "127.0.0.1")
        {
            //
            // Test subject alternative name.
            //
            {
                initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
                initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
                initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
                initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
                initData.properties->setProperty("IceSSL.CheckCertName", "1");
                comm = initialize(initData);

                fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
                test(fact);
                d = createServerProps(defaultProperties, defaultDir, defaultHost);
                d["IceSSL.CertAuthFile"] = "cacert1.pem";
                d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
                d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
                server = fact->createServer(d);
                try
                {
                    server->ice_ping();
                }
                catch(const LocalException&)
                {
                    test(false);
                }
                fact->destroyServer(server);
                comm->destroy();
            }
            //
            // Test common name.
            //
            {
                initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
                initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
                initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
                initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
                initData.properties->setProperty("IceSSL.CheckCertName", "1");
                comm = initialize(initData);

                fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
                test(fact);
                d = createServerProps(defaultProperties, defaultDir, defaultHost);
                d["IceSSL.CertAuthFile"] = "cacert1.pem";
                d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_cn1_pub.pem";
                d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_cn1_priv.pem";
                server = fact->createServer(d);
                try
                {
                    server->ice_ping();
                }
                catch(const LocalException&)
                {
                    test(false);
                }
                fact->destroyServer(server);
                comm->destroy();
            }
            //
            // Test common name again. The certificate used in this test has "127.0.0.11" as its
            // common name, therefore the address "127.0.0.1" must NOT match.
            //
            {
                initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
                initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
                initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
                initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
                initData.properties->setProperty("IceSSL.CheckCertName", "1");
                comm = initialize(initData);

                fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
                test(fact);
                d = createServerProps(defaultProperties, defaultDir, defaultHost);
                d["IceSSL.CertAuthFile"] = "cacert1.pem";
                d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_cn2_pub.pem";
                d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_cn2_priv.pem";
                server = fact->createServer(d);
                try
                {
                    server->ice_ping();
                    test(false);
                }
                catch(const LocalException&)
                {
                    // Expected.
                }
                fact->destroyServer(server);
                comm->destroy();
            }
        }
    }
    cout << "ok" << endl;

    cout << "testing custom certificate verifier... " << flush;
    {
        //
        // ADH is allowed but will not have a certificate.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        CommunicatorPtr comm = initialize(initData);
        IceSSL::PluginPtr plugin = IceSSL::PluginPtr::dynamicCast(comm->getPluginManager()->getPlugin("IceSSL"));
        test(plugin);
        CertificateVerifierIPtr verifier = new CertificateVerifierI;
        plugin->setCertificateVerifier(verifier);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.Ciphers"] = "ADH";
        d["IceSSL.VerifyPeer"] = "0";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            string cipherSub = "ADH-";
            server->checkCipher(cipherSub);
            IceSSL::NativeConnectionInfoPtr info = 
                IceSSL::NativeConnectionInfoPtr::dynamicCast(server->ice_getConnection()->getInfo());
            test(info->cipher.compare(0, cipherSub.size(), cipherSub) == 0);
        }
        catch(const LocalException&)
        {
            test(false);
        }
        test(verifier->invoked());
        test(!verifier->hadCert());

        //
        // Have the verifier return false. Close the connection explicitly
        // to force a new connection to be established.
        //
        verifier->reset();
        verifier->returnValue(false);
        server->ice_getConnection()->close(false);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const SecurityException&)
        {
            // Expected.
        }
        catch(const LocalException&)
        {
            test(false);
        }
        test(verifier->invoked());
        test(!verifier->hadCert());

        fact->destroyServer(server);
        comm->destroy();
    }
    {
        //
        // Verify that a server certificate is present.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        CommunicatorPtr comm = initialize(initData);
        IceSSL::PluginPtr plugin = IceSSL::PluginPtr::dynamicCast(comm->getPluginManager()->getPlugin("IceSSL"));
        test(plugin);
        CertificateVerifierIPtr verifier = new CertificateVerifierI;
        plugin->setCertificateVerifier(verifier);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.VerifyPeer"] = "2";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        test(verifier->invoked());
        test(verifier->hadCert());
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing protocols... " << flush;
    {
        //
        // This should fail because the client and server have no protocol
        // in common.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");
        initData.properties->setProperty("IceSSL.Protocols", "ssl3");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.Ciphers"] = "ADH";
        d["IceSSL.VerifyPeer"] = "0";
        d["IceSSL.Protocols"] = "tls1";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected on some platforms.
        }
        catch(const ConnectionLostException&)
        {
            // Expected on some platforms.
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();

        //
        // This should succeed.
        //
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.Ciphers"] = "ADH";
        d["IceSSL.VerifyPeer"] = "0";
        d["IceSSL.Protocols"] = "tls1, ssl3";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing expired certificates... " << flush;
    {
        //
        // This should fail because the server's certificate is expired.
        //
        {
            IceSSL::CertificatePtr cert =
                IceSSL::Certificate::load(defaultDir + "/s_rsa_nopass_ca1_exp_pub.pem");
            test(!cert->checkValidity());
        }

        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_exp_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_exp_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
#ifdef _WIN32
        catch(const ConnectionLostException&)
        {
            // Expected.
        }
#endif
        catch(const LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();

        //
        // This should fail because the client's certificate is expired.
        //
        {
            IceSSL::CertificatePtr cert =
                IceSSL::Certificate::load(defaultDir + "/c_rsa_nopass_ca1_exp_pub.pem");
            test(!cert->checkValidity());
        }
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_exp_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_exp_priv.pem");
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
#ifdef _WIN32
        catch(const ConnectionLostException&)
        {
            // Expected.
        }
#endif
        catch(const LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing CA certificate directory... " << flush;
    {
        //
        // Don't specify CertAuthFile explicitly; we let OpenSSL find the CA
        // certificate in the default directory.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing password prompt... " << flush;
    {
        //
        // Use the correct password.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_pass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_pass_ca1_priv.pem");
        initData.properties->setProperty("Ice.InitPlugins", "0");
        CommunicatorPtr comm = initialize(initData);
        PluginManagerPtr pm = comm->getPluginManager();
        IceSSL::PluginPtr plugin = IceSSL::PluginPtr::dynamicCast(pm->getPlugin("IceSSL"));
        test(plugin);
        PasswordPromptIPtr prompt = new PasswordPromptI("client");
        plugin->setPasswordPrompt(prompt);
        pm->initializePlugins();
        test(prompt->count() == 1);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();

        //
        // Use an incorrect password and check that retries are attempted.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_pass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_pass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.PasswordRetryMax", "4");
        initData.properties->setProperty("Ice.InitPlugins", "0");
        comm = initialize(initData);
        pm = comm->getPluginManager();
        plugin = IceSSL::PluginPtr::dynamicCast(pm->getPlugin("IceSSL"));
        test(plugin);
        prompt = new PasswordPromptI("invalid");
        plugin->setPasswordPrompt(prompt);
        try
        {
            pm->initializePlugins();
        }
        catch(const PluginInitializationException&)
        {
            // Expected.
        }
        catch(const LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        test(prompt->count() == 4);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing ciphers... " << flush;
    {
        //
        // The server has a certificate but the client doesn't. They should
        // negotiate to use ADH since we explicitly enable it.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.Ciphers"] = "RSA:ADH";
        d["IceSSL.VerifyPeer"] = "1";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            string cipherSub = "ADH-";
            server->checkCipher(cipherSub);
            IceSSL::NativeConnectionInfoPtr info = 
                IceSSL::NativeConnectionInfoPtr::dynamicCast(server->ice_getConnection()->getInfo());
            test(info->cipher.compare(0, cipherSub.size(), cipherSub) == 0);
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    
    {
        //
        // Configure a server with RSA and DSA certificates.
        //
        // First try a client with a DSA certificate.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_dsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_dsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.Ciphers", "DEFAULT:DSS");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem" + sep + "s_dsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem" + sep + "s_dsa_nopass_ca1_priv.pem";
        d["IceSSL.Ciphers"] = "DEFAULT:DSS";
        d["IceSSL.VerifyPeer"] = "1";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();

        //
        // Next try a client with an RSA certificate.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem" + sep + "s_dsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem" + sep + "s_dsa_nopass_ca1_priv.pem";
        d["IceSSL.Ciphers"] = "DEFAULT:DSS";
        d["IceSSL.VerifyPeer"] = "1";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();

        //
        // Next try a client with ADH. This should fail.
        //
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        comm = initialize(initData);
        fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem" + sep + "s_dsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem" + sep + "s_dsa_nopass_ca1_priv.pem";
        d["IceSSL.Ciphers"] = "DEFAULT:DSS";
        d["IceSSL.VerifyPeer"] = "1";
        server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        //
        // Configure a server with RSA and a client with DSA. This should fail.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_dsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_dsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.Ciphers", "DSS");
        CommunicatorPtr comm = initialize(initData);
        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const ProtocolException&)
        {
            // Expected.
        }
#ifdef _WIN32
        catch(const ConnectionLostException&)
        {
            // Expected.
        }
#endif
        catch(const LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing IceSSL.TrustOnly... " << flush;
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "C=US, ST=Florida, O=ZeroC\\, Inc.,"
                                         "OU=Ice, emailAddress=info@zeroc.com, CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "!C=US, ST=Florida, O=ZeroC\\, Inc.,"
                                         "OU=Ice, emailAddress=info@zeroc.com, CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "C=US, ST=Florida, O=\"ZeroC, Inc.\","
                                         "OU=Ice, emailAddress=info@zeroc.com, CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");

        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com,"
                                "CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "!C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com, CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "!CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");

        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "!CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "CN=Client");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "CN=Server";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "C=Canada,CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "!C=Canada,CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "C=Canada;CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "!C=Canada;!CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "!CN=Server1"); // Should not match "Server"
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "!CN=Client1"; // Should not match "Client"
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        //
        // Test rejection when client does not supply a certificate.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        CommunicatorPtr comm = initialize(initData);
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.TrustOnly"] = "C=US, ST=Florida, O=ZeroC\\, Inc.,OU=Ice, emailAddress=info@zeroc.com, CN=Client";
        d["IceSSL.Ciphers"] = "ADH";
        d["IceSSL.VerifyPeer"] = "0";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        //
        // Test rejection when client does not supply a certificate.
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        CommunicatorPtr comm = initialize(initData);
        initData.properties->setProperty("IceSSL.Ciphers", "ADH");
        initData.properties->setProperty("IceSSL.VerifyPeer", "0");

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.TrustOnly"] = "!C=US, ST=Florida, O=ZeroC\\, Inc.,OU=Ice, emailAddress=info@zeroc.com, CN=Client";
        d["IceSSL.Ciphers"] = "ADH";
        d["IceSSL.VerifyPeer"] = "0";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        //
        // Rejection takes precedence (client).
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly", "ST=Florida;!CN=Server;C=US");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        //
        // Rejection takes precedence (server).
        //
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly"] = "C=US;!CN=Client;ST=Florida";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing IceSSL.TrustOnly.Client... " << flush;
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly.Client", "C=US, ST=Florida, O=ZeroC\\, Inc.,"
                                         "OU=Ice, emailAddress=info@zeroc.com, CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        // Should have no effect.
        d["IceSSL.TrustOnly.Client"] = "C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com,"
                                "CN=Server";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly.Client", "!C=US, ST=Florida, O=ZeroC\\, Inc.,"
                                         "OU=Ice, emailAddress=info@zeroc.com, CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        // Should have no effect.
        d["IceSSL.TrustOnly.Client"] = "!CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly.Client", "CN=Client");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        initData.properties->setProperty("IceSSL.TrustOnly.Client", "!CN=Client");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing IceSSL.TrustOnly.Server... " << flush;
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        // Should have no effect.
        initData.properties->setProperty("IceSSL.TrustOnly.Server", "C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice,"
                                         "emailAddress=info@zeroc.com,CN=Client");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server"] = "C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com,"
                                         "CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server"] =
            "!C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com, CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        // Should have no effect.
        initData.properties->setProperty("IceSSL.TrustOnly.Server", "!CN=Server");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server"] = "CN=Server";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server"] = "!CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    cout << "testing IceSSL.TrustOnly.Server.<AdapterName>... " << flush;
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server"] = "CN=bogus";
        d["IceSSL.TrustOnly.Server.ServerAdapter"] =
            "C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com,CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server.ServerAdapter"] =
            "!C=US, ST=Florida, O=ZeroC\\, Inc., OU=Ice, emailAddress=info@zeroc.com, CN=Client";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server.ServerAdapter"] = "CN=bogus";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
            test(false);
        }
        catch(const LocalException&)
        {
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    {
        InitializationData initData;
        initData.properties = createClientProps(defaultProperties, defaultDir, defaultHost);
        initData.properties->setProperty("IceSSL.CertAuthFile", "cacert1.pem");
        initData.properties->setProperty("IceSSL.CertFile", "c_rsa_nopass_ca1_pub.pem");
        initData.properties->setProperty("IceSSL.KeyFile", "c_rsa_nopass_ca1_priv.pem");
        CommunicatorPtr comm = initialize(initData);

        Test::ServerFactoryPrx fact = Test::ServerFactoryPrx::checkedCast(comm->stringToProxy(factoryRef));
        test(fact);
        Test::Properties d = createServerProps(defaultProperties, defaultDir, defaultHost);
        d["IceSSL.CertAuthFile"] = "cacert1.pem";
        d["IceSSL.CertFile"] = "s_rsa_nopass_ca1_pub.pem";
        d["IceSSL.KeyFile"] = "s_rsa_nopass_ca1_priv.pem";
        d["IceSSL.TrustOnly.Server.ServerAdapter"] = "!CN=bogus";
        Test::ServerPrx server = fact->createServer(d);
        try
        {
            server->ice_ping();
        }
        catch(const LocalException&)
        {
            test(false);
        }
        fact->destroyServer(server);
        comm->destroy();
    }
    cout << "ok" << endl;

    factory->shutdown();
}
