// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceSSL;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

class Instance
{
    Instance(Ice.Communicator communicator)
    {
        _logger = communicator.getLogger();
        _facade = IceInternal.Util.getProtocolPluginFacade(communicator);
        _securityTraceLevel = communicator.getProperties().getPropertyAsIntWithDefault("IceSSL.Trace.Security", 0);
        _securityTraceCategory = "Security";
        _trustManager = new TrustManager(communicator);

        //
        // Register the endpoint factory. We have to do this now, rather than
        // in initialize, because the communicator may need to interpret
        // proxies before the plug-in is fully initialized.
        //
        _facade.addEndpointFactory(new EndpointFactoryI(this));
    }

    void
    initialize()
    {
        if(_initialized)
        {
            return;
        }

        final String prefix = "IceSSL.";
        Ice.Properties properties = communicator().getProperties();

        //
        // Parse the cipher list.
        //
        String ciphers = properties.getProperty(prefix + "Ciphers");
        if(ciphers.length() > 0)
        {
            parseCiphers(ciphers);
        }

        //
        // Select protocols.
        //
        String[] protocols = properties.getPropertyAsList(prefix + "Protocols");
        if(protocols.length != 0)
        {
            java.util.ArrayList<String> l = new java.util.ArrayList<String>();
            for(String prot : protocols)
            {
                String s = prot.toLowerCase();
                if(s.equals("ssl3") || s.equals("sslv3"))
                {
                    l.add("SSLv3");
                }
                else if(s.equals("tls") || s.equals("tls1") || s.equals("tlsv1") || s.equals("tls1_0") ||
                        s.equals("tlsv1_0"))
                {
                    l.add("TLSv1");
                }
                else if(s.equals("tls1_1") || s.equals("tlsv1_1"))
                {
                    l.add("TLSv1.1");
                }
                else if(s.equals("tls1_2") || s.equals("tlsv1_2"))
                {
                    l.add("TLSv1.2");
                }
                else
                {
                    Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                    e.reason = "IceSSL: unrecognized protocol `" + prot + "'";
                    throw e;
                }
            }
            _protocols = new String[l.size()];
            l.toArray(_protocols);
        }

        //
        // CheckCertName determines whether we compare the name in a peer's
        // certificate against its hostname.
        //
        _checkCertName = properties.getPropertyAsIntWithDefault(prefix + "CheckCertName", 0) > 0;

        //
        // VerifyDepthMax establishes the maximum length of a peer's certificate
        // chain, including the peer's certificate. A value of 0 means there is
        // no maximum.
        //
        _verifyDepthMax = properties.getPropertyAsIntWithDefault(prefix + "VerifyDepthMax", 2);

        //
        // VerifyPeer determines whether certificate validation failures abort a connection.
        //
        _verifyPeer = communicator().getProperties().getPropertyAsIntWithDefault("IceSSL.VerifyPeer", 2);

        //
        // Check for a certificate verifier.
        //
        final String certVerifierClass = properties.getProperty(prefix + "CertVerifier");
        if(certVerifierClass.length() > 0)
        {
            if(_verifier != null)
            {
                Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                e.reason = "IceSSL: certificate verifier already installed";
                throw e;
            }

            Class<?> cls = null;
            try
            {
                cls = _facade.findClass(certVerifierClass);
            }
            catch(Throwable ex)
            {
                throw new Ice.PluginInitializationException(
                    "IceSSL: unable to load certificate verifier class " + certVerifierClass, ex);
            }

            try
            {
                _verifier = (CertificateVerifier)cls.newInstance();
            }
            catch(Throwable ex)
            {
                throw new Ice.PluginInitializationException(
                    "IceSSL: unable to instantiate certificate verifier class " + certVerifierClass, ex);
            }
        }

        //
        // Check for a password callback.
        //
        final String passwordCallbackClass = properties.getProperty(prefix + "PasswordCallback");
        if(passwordCallbackClass.length() > 0)
        {
            if(_passwordCallback != null)
            {
                Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                e.reason = "IceSSL: password callback already installed";
                throw e;
            }

            Class<?> cls = null;
            try
            {
                cls = _facade.findClass(passwordCallbackClass);
            }
            catch(Throwable ex)
            {
                throw new Ice.PluginInitializationException(
                    "IceSSL: unable to load password callback class " + passwordCallbackClass, ex);
            }

            try
            {
                _passwordCallback = (PasswordCallback)cls.newInstance();
            }
            catch(Throwable ex)
            {
                throw new Ice.PluginInitializationException(
                    "IceSSL: unable to instantiate password callback class " + passwordCallbackClass, ex);
            }
        }

        //
        // If the user doesn't supply an SSLContext, we need to create one based
        // on property settings.
        //
        if(_context == null)
        {
            try
            {
                //
                // Check for a default directory. We look in this directory for
                // files mentioned in the configuration.
                //
                _defaultDir = properties.getProperty(prefix + "DefaultDir");

                //
                // We need a SecureRandom object.
                //
                // NOTE: The JDK recommends obtaining a SecureRandom object like this:
                //
                // java.security.SecureRandom rand = java.security.SecureRandom.getInstance("SHA1PRNG");
                //
                // However, there is a bug (6202721) which causes it to always use /dev/random,
                // which can lead to long delays at program startup. The workaround is to use
                // the default constructor.
                //
                java.security.SecureRandom rand = new java.security.SecureRandom();

                //
                // Check for seed data for the random number generator.
                //
                final String seedFiles = properties.getProperty(prefix + "Random");
                if(seedFiles.length() > 0)
                {
                    final String[] arr = seedFiles.split(java.io.File.pathSeparator);
                    for(String file : arr)
                    {
                        try
                        {
                            java.io.InputStream seedStream = openResource(file);
                            if(seedStream == null)
                            {
                                Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                                e.reason = "IceSSL: random seed file not found:\n" + file;
                                throw e;
                            }

                            _seeds.add(seedStream);
                        }
                        catch(java.io.IOException ex)
                        {
                            throw new Ice.PluginInitializationException(
                                "IceSSL: unable to access random seed file:\n" + file, ex);
                        }
                    }
                }

                if(!_seeds.isEmpty())
                {
                    byte[] seed = null;
                    int start = 0;
                    for(InputStream in : _seeds)
                    {
                        try
                        {
                            int num = in.available();
                            if(seed == null)
                            {
                                seed = new byte[num];
                            }
                            else
                            {
                                byte[] tmp = new byte[seed.length + num];
                                System.arraycopy(seed, 0, tmp, 0, seed.length);
                                start = seed.length;
                                seed = tmp;
                            }
                            in.read(seed, start, num);
                        }
                        catch(java.io.IOException ex)
                        {
                            throw new Ice.PluginInitializationException("IceSSL: error while reading random seed", ex);
                        }
                        finally
                        {
                            try
                            {
                                in.close();
                            }
                            catch(java.io.IOException e)
                            {
                                // Ignore.
                            }
                        }
                    }
                    rand.setSeed(seed);
                }
                _seeds.clear();

                //
                // We call nextInt() in order to force the object to perform any time-consuming
                // initialization tasks now.
                //
                rand.nextInt();

                //
                // The keystore holds private keys and associated certificates.
                //
                String keystorePath = properties.getProperty(prefix + "Keystore");

                //
                // The password for the keys.
                //
                String password = properties.getProperty(prefix + "Password");

                //
                // The password for the keystore.
                //
                String keystorePassword = properties.getProperty(prefix + "KeystorePassword");

                //
                // The default keystore type is usually "JKS", but the legal values are determined
                // by the JVM implementation. Other possibilities include "PKCS12" and "BKS".
                //
                final String defaultType = java.security.KeyStore.getDefaultType();
                final String keystoreType = properties.getPropertyWithDefault(prefix + "KeystoreType", defaultType);

                //
                // The alias of the key to use in authentication.
                //
                final String alias = properties.getProperty(prefix + "Alias");

                //
                // The truststore holds the certificates of trusted CAs.
                //
                String truststorePath = properties.getProperty(prefix + "Truststore");

                //
                // The password for the truststore.
                //
                String truststorePassword = properties.getProperty(prefix + "TruststorePassword");

                //
                // The default truststore type is usually "JKS", but the legal values are determined
                // by the JVM implementation. Other possibilities include "PKCS12" and "BKS".
                //
                final String truststoreType =
                    properties.getPropertyWithDefault(prefix + "TruststoreType",
                                                      java.security.KeyStore.getDefaultType());

                //
                // Collect the key managers.
                //
                javax.net.ssl.KeyManager[] keyManagers = null;
                java.security.KeyStore keys = null;
                if(_keystoreStream != null || keystorePath.length() > 0)
                {
                    java.io.InputStream keystoreStream = null;
                    try
                    {
                        if(_keystoreStream != null)
                        {
                            keystoreStream = _keystoreStream;
                        }
                        else
                        {
                            keystoreStream = openResource(keystorePath);
                            if(keystoreStream == null)
                            {
                                Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                                e.reason = "IceSSL: keystore not found:\n" + keystorePath;
                                throw e;
                            }
                        }

                        keys = java.security.KeyStore.getInstance(keystoreType);
                        char[] passwordChars = null;
                        if(keystorePassword.length() > 0)
                        {
                            passwordChars = keystorePassword.toCharArray();
                        }
                        else if(_passwordCallback != null)
                        {
                            passwordChars = _passwordCallback.getKeystorePassword();
                        }
                        else if(keystoreType.equals("BKS"))
                        {
                            // Bouncy Castle does not permit null passwords.
                            passwordChars = new char[0];
                        }

                        keys.load(keystoreStream, passwordChars);

                        if(passwordChars != null)
                        {
                            java.util.Arrays.fill(passwordChars, '\0');
                        }
                        keystorePassword = null;
                    }
                    catch(java.io.IOException ex)
                    {
                        throw new Ice.PluginInitializationException(
                            "IceSSL: unable to load keystore:\n" + keystorePath, ex);
                    }
                    finally
                    {
                        if(keystoreStream != null)
                        {
                            try
                            {
                                keystoreStream.close();
                            }
                            catch(java.io.IOException e)
                            {
                                // Ignore.
                            }
                        }
                    }

                    String algorithm = javax.net.ssl.KeyManagerFactory.getDefaultAlgorithm();
                    javax.net.ssl.KeyManagerFactory kmf = javax.net.ssl.KeyManagerFactory.getInstance(algorithm);
                    char[] passwordChars = new char[0]; // This password cannot be null.
                    if(password.length() > 0)
                    {
                        passwordChars = password.toCharArray();
                    }
                    else if(_passwordCallback != null)
                    {
                        passwordChars = _passwordCallback.getPassword(alias);
                    }
                    kmf.init(keys, passwordChars);
                    if(passwordChars.length > 0)
                    {
                        java.util.Arrays.fill(passwordChars, '\0');
                    }
                    password = null;
                    keyManagers = kmf.getKeyManagers();

                    //
                    // If the user selected a specific alias, we need to wrap the key managers
                    // in order to return the desired alias.
                    //
                    if(alias.length() > 0)
                    {
                        if(!keys.isKeyEntry(alias))
                        {
                            Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                            e.reason = "IceSSL: keystore does not contain an entry with alias `" + alias + "'";
                            throw e;
                        }

                        for(int i = 0; i < keyManagers.length; ++i)
                        {
                            keyManagers[i] = new X509KeyManagerI((javax.net.ssl.X509KeyManager)keyManagers[i], alias);
                        }
                    }
                }

                //
                // Load the truststore.
                //
                java.security.KeyStore ts = null;
                if(_truststoreStream != null || truststorePath.length() > 0)
                {
                    //
                    // If the trust store and the key store are the same input
                    // stream or file, don't create another key store.
                    //
                    if((_truststoreStream != null && _truststoreStream == _keystoreStream) ||
                       (truststorePath.length() > 0 && truststorePath.equals(keystorePath)))
                    {
                        assert keys != null;
                        ts = keys;
                    }
                    else
                    {
                        java.io.InputStream truststoreStream = null;
                        try
                        {
                            if(_truststoreStream != null)
                            {
                                truststoreStream = _truststoreStream;
                            }
                            else
                            {
                                truststoreStream = openResource(truststorePath);
                                if(truststoreStream == null)
                                {
                                    Ice.PluginInitializationException e = new Ice.PluginInitializationException();
                                    e.reason = "IceSSL: truststore not found:\n" + truststorePath;
                                    throw e;
                                }
                            }

                            ts = java.security.KeyStore.getInstance(truststoreType);

                            char[] passwordChars = null;
                            if(truststorePassword.length() > 0)
                            {
                                passwordChars = truststorePassword.toCharArray();
                            }
                            else if(_passwordCallback != null)
                            {
                                passwordChars = _passwordCallback.getTruststorePassword();
                            }
                            else if(truststoreType.equals("BKS"))
                            {
                                // Bouncy Castle does not permit null passwords.
                                passwordChars = new char[0];
                            }

                            ts.load(truststoreStream, passwordChars);

                            if(passwordChars != null)
                            {
                                java.util.Arrays.fill(passwordChars, '\0');
                            }
                            truststorePassword = null;
                        }
                        catch(java.io.IOException ex)
                        {
                            throw new Ice.PluginInitializationException(
                                "IceSSL: unable to load truststore:\n" + truststorePath, ex);
                        }
                        finally
                        {
                            if(truststoreStream != null)
                            {
                                try
                                {
                                    truststoreStream.close();
                                }
                                catch(java.io.IOException e)
                                {
                                    // Ignore.
                                }
                            }
                        }
                    }
                }
                else
                {
                    ts = keys;
                }

                //
                // Collect the trust managers.
                //
                javax.net.ssl.TrustManager[] trustManagers = null;
                {
                    String algorithm = javax.net.ssl.TrustManagerFactory.getDefaultAlgorithm();
                    javax.net.ssl.TrustManagerFactory tmf = javax.net.ssl.TrustManagerFactory.getInstance(algorithm);
                    tmf.init(ts);
                    trustManagers = tmf.getTrustManagers();
                    assert(trustManagers != null);
                }

                //
                // Wrap each trust manager.
                //
                for(int i = 0; i < trustManagers.length; ++i)
                {
                    trustManagers[i] = new X509TrustManagerI(this, (javax.net.ssl.X509TrustManager)trustManagers[i]);
                }

                //
                // Initialize the SSL context.
                //
                _context = javax.net.ssl.SSLContext.getInstance("TLS");
                _context.init(keyManagers, trustManagers, rand);
            }
            catch(java.security.GeneralSecurityException ex)
            {
                throw new Ice.PluginInitializationException("IceSSL: unable to initialize context", ex);
            }
        }

        //
        // Clear cached input streams.
        //
        _seeds.clear();
        _keystoreStream = null;
        _truststoreStream = null;

        _initialized = true;
    }

    void
    context(javax.net.ssl.SSLContext context)
    {
        if(_initialized)
        {
            Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
            ex.reason = "IceSSL: plug-in is already initialized";
            throw ex;
        }

        _context = context;
    }

    javax.net.ssl.SSLContext
    context()
    {
        return _context;
    }

    void
    setCertificateVerifier(CertificateVerifier verifier)
    {
        _verifier = verifier;
    }

    CertificateVerifier
    getCertificateVerifier()
    {
        return _verifier;
    }

    void
    setPasswordCallback(PasswordCallback callback)
    {
        _passwordCallback = callback;
    }

    PasswordCallback
    getPasswordCallback()
    {
        return _passwordCallback;
    }

    void
    setKeystoreStream(java.io.InputStream stream)
    {
        if(_initialized)
        {
            Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
            ex.reason = "IceSSL: plugin is already initialized";
            throw ex;
        }

        _keystoreStream = stream;
    }

    void
    setTruststoreStream(java.io.InputStream stream)
    {
        if(_initialized)
        {
            Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
            ex.reason = "IceSSL: plugin is already initialized";
            throw ex;
        }

        _truststoreStream = stream;
    }

    void
    addSeedStream(java.io.InputStream stream)
    {
        _seeds.add(stream);
    }

    Ice.Communicator
    communicator()
    {
        return _facade.getCommunicator();
    }

    IceInternal.EndpointHostResolver
    endpointHostResolver()
    {
        return _facade.getEndpointHostResolver();
    }

    int
    protocolSupport()
    {
        return _facade.getProtocolSupport();
    }

    boolean
    preferIPv6()
    {
        return _facade.getPreferIPv6();
    }

    Ice.EncodingVersion
    defaultEncoding()
    {
        return _facade.getDefaultEncoding();
    }

    String
    defaultHost()
    {
        return _facade.getDefaultHost();
    }

    int
    networkTraceLevel()
    {
        return _facade.getNetworkTraceLevel();
    }

    String
    networkTraceCategory()
    {
        return _facade.getNetworkTraceCategory();
    }

    int
    securityTraceLevel()
    {
        return _securityTraceLevel;
    }

    String
    securityTraceCategory()
    {
        return _securityTraceCategory;
    }

    boolean
    initialized()
    {
        return _initialized;
    }

    javax.net.ssl.SSLEngine
    createSSLEngine(boolean incoming, java.net.InetSocketAddress peerAddr)
    {
        javax.net.ssl.SSLEngine engine;
        if(peerAddr != null)
        {
            engine = _context.createSSLEngine(peerAddr.getAddress().getHostAddress(), peerAddr.getPort());
        }
        else
        {
            engine = _context.createSSLEngine();
        }
        engine.setUseClientMode(!incoming);

        String[] cipherSuites = filterCiphers(engine.getSupportedCipherSuites(), engine.getEnabledCipherSuites());
        try
        {
            engine.setEnabledCipherSuites(cipherSuites);
        }
        catch(IllegalArgumentException ex)
        {
            throw new Ice.SecurityException("IceSSL: invalid ciphersuite", ex);
        }

        if(_securityTraceLevel >= 1)
        {
            StringBuilder s = new StringBuilder(128);
            s.append("enabling SSL ciphersuites:");
            for(String suite : cipherSuites)
            {
                s.append("\n  ");
                s.append(suite);
            }
            _logger.trace(_securityTraceCategory, s.toString());
        }

        if(_protocols != null)
        {
            try
            {
                engine.setEnabledProtocols(_protocols);
            }
            catch(IllegalArgumentException ex)
            {
                throw new Ice.SecurityException("IceSSL: invalid protocol", ex);
            }
        }

        if(incoming)
        {
            if(_verifyPeer == 0)
            {
                engine.setWantClientAuth(false);
                engine.setNeedClientAuth(false);
            }
            else if(_verifyPeer == 1)
            {
                engine.setWantClientAuth(true);
            }
            else
            {
                engine.setNeedClientAuth(true);
            }
        }

        try
        {
            engine.beginHandshake();
        }
        catch(javax.net.ssl.SSLException ex)
        {
            throw new Ice.SecurityException("IceSSL: handshake error", ex);
        }

        return engine;
    }

    String[]
    filterCiphers(String[] supportedCiphers, String[] defaultCiphers)
    {
        java.util.LinkedList<String> result = new java.util.LinkedList<String>();
        if(_allCiphers)
        {
            for(String cipher : supportedCiphers)
            {
                result.add(cipher);
            }
        }
        else if(!_noCiphers)
        {
            for(String cipher : defaultCiphers)
            {
                result.add(cipher);
            }
        }

        if(_ciphers != null)
        {
            for(CipherExpression ce : _ciphers)
            {
                if(ce.not)
                {
                    java.util.Iterator<String> e = result.iterator();
                    while(e.hasNext())
                    {
                        String cipher = e.next();
                        if(ce.cipher != null)
                        {
                            if(ce.cipher.equals(cipher))
                            {
                                e.remove();
                            }
                        }
                        else
                        {
                            assert(ce.re != null);
                            java.util.regex.Matcher m = ce.re.matcher(cipher);
                            if(m.find())
                            {
                                e.remove();
                            }
                        }
                    }
                }
                else
                {
                    if(ce.cipher != null)
                    {
                        result.add(0, ce.cipher);
                    }
                    else
                    {
                        assert(ce.re != null);
                        for(String cipher : supportedCiphers)
                        {
                            java.util.regex.Matcher m = ce.re.matcher(cipher);
                            if(m.find())
                            {
                                result.add(0, cipher);
                            }
                        }
                    }
                }
            }
        }

        String[] arr = new String[result.size()];
        result.toArray(arr);
        return arr;
    }

    String[]
    protocols()
    {
        return _protocols;
    }

    void
    traceConnection(java.nio.channels.SocketChannel fd, javax.net.ssl.SSLEngine engine, boolean incoming)
    {
        javax.net.ssl.SSLSession session = engine.getSession();
        String msg = "SSL summary for " + (incoming ? "incoming" : "outgoing") + " connection\n" +
            "cipher = " + session.getCipherSuite() + "\n" +
            "protocol = " + session.getProtocol() + "\n" +
            IceInternal.Network.fdToString(fd);
        _logger.trace(_securityTraceCategory, msg);
    }

    void
    verifyPeer(NativeConnectionInfo info, java.nio.channels.SelectableChannel fd, String address)
    {
        //
        // For an outgoing connection, we compare the proxy address (if any) against
        // fields in the server's certificate (if any).
        //
        if(info.nativeCerts != null && info.nativeCerts.length > 0 && address.length() > 0)
        {
            java.security.cert.X509Certificate cert = (java.security.cert.X509Certificate)info.nativeCerts[0];

            //
            // Extract the IP addresses and the DNS names from the subject
            // alternative names.
            //
            java.util.ArrayList<String> ipAddresses = new java.util.ArrayList<String>();
            java.util.ArrayList<String> dnsNames = new java.util.ArrayList<String>();
            try
            {
                java.util.Collection<java.util.List<?> > subjectAltNames = cert.getSubjectAlternativeNames();
                if(subjectAltNames != null)
                {
                    for(java.util.List<?> l : subjectAltNames)
                    {
                        assert(!l.isEmpty());
                        Integer n = (Integer)l.get(0);
                        if(n.intValue() == 7)
                        {
                            ipAddresses.add((String)l.get(1));
                        }
                        else if(n.intValue() == 2)
                        {
                            dnsNames.add(((String)l.get(1)).toLowerCase());
                        }
                    }
                }
            }
            catch(java.security.cert.CertificateParsingException ex)
            {
                assert(false);
            }

            //
            // Compare the peer's address against the common name as well as
            // the dnsName and ipAddress values in the subject alternative name.
            //
            boolean certNameOK = false;
            String dn = "";
            String addrLower = address.toLowerCase();
            {
                javax.security.auth.x500.X500Principal principal = cert.getSubjectX500Principal();
                dn = principal.getName(javax.security.auth.x500.X500Principal.CANONICAL);
                //
                // Canonical format is already in lower case.
                //
                String cn = "cn=" + addrLower;
                int pos = dn.indexOf(cn);
                if(pos >= 0)
                {
                    //
                    // Ensure we match the entire common name.
                    //
                    certNameOK = (pos + cn.length() == dn.length()) || (dn.charAt(pos + cn.length()) == ',');
                }
            }

            //
            // Compare the peer's address against the dnsName and ipAddress
            // values in the subject alternative name.
            //
            if(!certNameOK)
            {
                certNameOK = ipAddresses.contains(addrLower);
            }
            if(!certNameOK)
            {
                certNameOK = dnsNames.contains(addrLower);
            }

            //
            // Log a message if the name comparison fails. If CheckCertName is defined,
            // we also raise an exception to abort the connection. Don't log a message if
            // CheckCertName is not defined and a verifier is present.
            //
            if(!certNameOK && (_checkCertName || (_securityTraceLevel >= 1 && _verifier == null)))
            {
                StringBuilder sb = new StringBuilder(128);
                sb.append("IceSSL: ");
                if(!_checkCertName)
                {
                    sb.append("ignoring ");
                }
                sb.append("certificate validation failure:\npeer certificate does not have `");
                sb.append(address);
                sb.append("' as its commonName or in its subjectAltName extension");
                if(dn.length() > 0)
                {
                    sb.append("\nSubject DN: ");
                    sb.append(dn);
                }
                if(!dnsNames.isEmpty())
                {
                    sb.append("\nDNS names found in certificate: ");
                    for(int j = 0; j < dnsNames.size(); ++j)
                    {
                        if(j > 0)
                        {
                            sb.append(", ");
                        }
                        sb.append(dnsNames.get(j));
                    }
                }
                if(!ipAddresses.isEmpty())
                {
                    sb.append("\nIP addresses found in certificate: ");
                    for(int j = 0; j < ipAddresses.size(); ++j)
                    {
                        if(j > 0)
                        {
                            sb.append(", ");
                        }
                        sb.append(ipAddresses.get(j));
                    }
                }
                if(_securityTraceLevel >= 1)
                {
                    _logger.trace(_securityTraceCategory, sb.toString());
                }
                if(_checkCertName)
                {
                    Ice.SecurityException ex = new Ice.SecurityException();
                    ex.reason = sb.toString();
                    throw ex;
                }
            }
        }

        if(_verifyDepthMax > 0 && info.nativeCerts != null && info.nativeCerts.length > _verifyDepthMax)
        {
            String msg = (info.incoming ? "incoming" : "outgoing") + " connection rejected:\n" +
                "length of peer's certificate chain (" + info.nativeCerts.length + ") exceeds maximum of " +
                _verifyDepthMax + "\n" +
                IceInternal.Network.fdToString(fd);
            if(_securityTraceLevel >= 1)
            {
                _logger.trace(_securityTraceCategory, msg);
            }
            Ice.SecurityException ex = new Ice.SecurityException();
            ex.reason = msg;
            throw ex;
        }

        if(!_trustManager.verify(info))
        {
            String msg = (info.incoming ? "incoming" : "outgoing") + " connection rejected by trust manager\n" +
                IceInternal.Network.fdToString(fd);
            if(_securityTraceLevel >= 1)
            {
                _logger.trace(_securityTraceCategory, msg);
            }
            Ice.SecurityException ex = new Ice.SecurityException();
            ex.reason = msg;
            throw ex;
        }

        if(_verifier != null && !_verifier.verify(info))
        {
            String msg = (info.incoming ? "incoming" : "outgoing") + " connection rejected by certificate verifier\n" +
                IceInternal.Network.fdToString(fd);
            if(_securityTraceLevel >= 1)
            {
                _logger.trace(_securityTraceCategory, msg);
            }
            Ice.SecurityException ex = new Ice.SecurityException();
            ex.reason = msg;
            throw ex;
        }
    }

    void
    trustManagerFailure(boolean incoming, java.security.cert.CertificateException ex)
        throws java.security.cert.CertificateException
    {
        if(_verifyPeer == 0)
        {
            if(_securityTraceLevel >= 1)
            {
                String msg = "ignoring peer verification failure";
                if(_securityTraceLevel > 1)
                {
                    java.io.StringWriter sw = new java.io.StringWriter();
                    java.io.PrintWriter pw = new java.io.PrintWriter(sw);
                    ex.printStackTrace(pw);
                    pw.flush();
                    msg += ":\n" + sw.toString();
                }
                _logger.trace(_securityTraceCategory, msg);
            }
        }
        else
        {
            throw ex;
        }
    }

    private void
    parseCiphers(String ciphers)
    {
        java.util.ArrayList<CipherExpression> cipherList = new java.util.ArrayList<CipherExpression>();
        String[] expr = ciphers.split("[ \t]+");
        for(int i = 0; i < expr.length; ++i)
        {
            if(expr[i].equals("ALL"))
            {
                if(i != 0)
                {
                    Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
                    ex.reason = "IceSSL: `ALL' must be first in cipher list `" + ciphers + "'";
                    throw ex;
                }
                _allCiphers = true;
            }
            else if(expr[i].equals("NONE"))
            {
                if(i != 0)
                {
                    Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
                    ex.reason = "IceSSL: `NONE' must be first in cipher list `" + ciphers + "'";
                    throw ex;
                }
                _noCiphers = true;
            }
            else
            {
                CipherExpression ce = new CipherExpression();
                String exp = expr[i];
                if(exp.charAt(0) == '!')
                {
                    ce.not = true;
                    if(exp.length() > 1)
                    {
                        exp = exp.substring(1);
                    }
                    else
                    {
                        Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
                        ex.reason = "IceSSL: invalid cipher expression `" + exp + "'";
                        throw ex;
                    }
                }

                if(exp.charAt(0) == '(')
                {
                    if(!exp.endsWith(")"))
                    {
                        Ice.PluginInitializationException ex = new Ice.PluginInitializationException();
                        ex.reason = "IceSSL: invalid cipher expression `" + exp + "'";
                        throw ex;
                    }

                    try
                    {
                        ce.re = java.util.regex.Pattern.compile(exp.substring(1, exp.length() - 2));
                    }
                    catch(java.util.regex.PatternSyntaxException ex)
                    {
                        throw new Ice.PluginInitializationException(
                            "IceSSL: invalid cipher expression `" + exp + "'", ex);
                    }
                }
                else
                {
                    ce.cipher = exp;
                }

                cipherList.add(ce);
            }
        }
        _ciphers = new CipherExpression[cipherList.size()];
        cipherList.toArray(_ciphers);
    }

    private java.io.InputStream
    openResource(String path)
        throws java.io.IOException
    {
        //
        // This method wraps a call to IceInternal.Util.openResource. If the first call fails and
        // IceSSL.DefaultDir is defined, prepend the default directory and try again.
        //
        java.io.InputStream stream = IceInternal.Util.openResource(getClass().getClassLoader(), path);
        if(stream == null && _defaultDir.length() > 0)
        {
            stream = IceInternal.Util.openResource(getClass().getClassLoader(),
                                                   _defaultDir + java.io.File.separator + path);
        }

        if(stream != null)
        {
            stream = new java.io.BufferedInputStream(stream);
        }

        return stream;
    }

    private static class CipherExpression
    {
        boolean not;
        String cipher;
        java.util.regex.Pattern re;
    }

    private Ice.Logger _logger;
    private IceInternal.ProtocolPluginFacade _facade;
    private int _securityTraceLevel;
    private String _securityTraceCategory;
    private boolean _initialized;
    private javax.net.ssl.SSLContext _context;
    private String _defaultDir;
    private CipherExpression[] _ciphers;
    private boolean _allCiphers;
    private boolean _noCiphers;
    private String[] _protocols;
    private boolean _checkCertName;
    private int _verifyDepthMax;
    private int _verifyPeer;
    private CertificateVerifier _verifier;
    private PasswordCallback _passwordCallback;
    private TrustManager _trustManager;

    private InputStream _keystoreStream;
    private InputStream _truststoreStream;
    private List<InputStream> _seeds = new ArrayList<InputStream>();
}
