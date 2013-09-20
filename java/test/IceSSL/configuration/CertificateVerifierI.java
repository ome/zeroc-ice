// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.IceSSL.configuration;
import test.IceSSL.configuration.Test.*;

public class CertificateVerifierI implements IceSSL.CertificateVerifier
{
    public
    CertificateVerifierI()
    {
        reset();
    }

    public boolean
    verify(IceSSL.NativeConnectionInfo info)
    {
        if(info.nativeCerts != null)
        {
            try
            {
                java.util.Collection<java.util.List<?> > subjectAltNames =
                    ((java.security.cert.X509Certificate)info.nativeCerts[0]).getSubjectAlternativeNames();
                test(subjectAltNames != null);
                java.util.List<String> ipAddresses = new java.util.ArrayList<String>();
                java.util.List<String> dnsNames = new java.util.ArrayList<String>();
                for(java.util.List<?> l : subjectAltNames)
                {
                    test(!l.isEmpty());
                    Integer n = (Integer)l.get(0);
                    if(n.intValue() == 7)
                    {
                        ipAddresses.add((String)l.get(1));
                    }
                    else if(n.intValue() == 2)
                    {
                        dnsNames.add((String)l.get(1));
                    }
                }

                test(dnsNames.contains("server"));
                test(ipAddresses.contains("127.0.0.1"));
            }
            catch(java.security.cert.CertificateParsingException ex)
            {
                test(false);
            }
        }

        _hadCert = info.nativeCerts != null;
        _invoked = true;
        return _returnValue;
    }

    void
    reset()
    {
        _returnValue = true;
        _invoked = false;
        _hadCert = false;
    }

    void
    returnValue(boolean b)
    {
        _returnValue = b;
    }

    boolean
    invoked()
    {
        return _invoked;
    }

    boolean
    hadCert()
    {
        return _hadCert;
    }

    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    private boolean _returnValue;
    private boolean _invoked;
    private boolean _hadCert;
}
