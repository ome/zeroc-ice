// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

using System;
using System.Collections.Generic;
using System.Diagnostics;

#if SILVERLIGHT
using System.Windows.Controls;
#endif

public class AllTests : TestCommon.TestApp
{
#if SILVERLIGHT
    override
    public void run(Ice.Communicator communicator)
#else
    public static Test.MyClassPrx allTests(Ice.Communicator communicator)
#endif
    {
        Write("testing stringToProxy... ");
        Flush();
        string rf = "test:default -p 12010";
        Ice.ObjectPrx baseProxy = communicator.stringToProxy(rf);
        test(baseProxy != null);

        Ice.ObjectPrx b1 = communicator.stringToProxy("test");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getAdapterId().Length == 0 && b1.ice_getFacet().Length == 0);
        b1 = communicator.stringToProxy("test ");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        b1 = communicator.stringToProxy(" test ");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        b1 = communicator.stringToProxy(" test");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        b1 = communicator.stringToProxy("'test -f facet'");
        test(b1.ice_getIdentity().name.Equals("test -f facet") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        try
        {
            b1 = communicator.stringToProxy("\"test -f facet'");
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        b1 = communicator.stringToProxy("\"test -f facet\"");
        test(b1.ice_getIdentity().name.Equals("test -f facet") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        b1 = communicator.stringToProxy("\"test -f facet@test\"");
        test(b1.ice_getIdentity().name.Equals("test -f facet@test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        b1 = communicator.stringToProxy("\"test -f facet@test @test\"");
        test(b1.ice_getIdentity().name.Equals("test -f facet@test @test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Length == 0);
        try
        {
            b1 = communicator.stringToProxy("test test");
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        b1 = communicator.stringToProxy("test\\040test");
        test(b1.ice_getIdentity().name.Equals("test test") && b1.ice_getIdentity().category.Length == 0);
        try
        {
            b1 = communicator.stringToProxy("test\\777");
            test(false);
        }
        catch(Ice.IdentityParseException)
        {
        }
        b1 = communicator.stringToProxy("test\\40test");
        test(b1.ice_getIdentity().name.Equals("test test"));

        // Test some octal and hex corner cases.
        b1 = communicator.stringToProxy("test\\4test");
        test(b1.ice_getIdentity().name.Equals("test\u0004test"));
        b1 = communicator.stringToProxy("test\\04test");
        test(b1.ice_getIdentity().name.Equals("test\u0004test"));
        b1 = communicator.stringToProxy("test\\004test");
        test(b1.ice_getIdentity().name.Equals("test\u0004test"));
        b1 = communicator.stringToProxy("test\\1114test");
        test(b1.ice_getIdentity().name.Equals("test\u00494test"));

        b1 = communicator.stringToProxy("test\\b\\f\\n\\r\\t\\'\\\"\\\\test");
        test(b1.ice_getIdentity().name.Equals("test\b\f\n\r\t\'\"\\test") && b1.ice_getIdentity().category.Length == 0);

        b1 = communicator.stringToProxy("category/test");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category") &&
             b1.ice_getAdapterId().Length == 0);

        b1 = communicator.stringToProxy("");
        test(b1 == null);
        b1 = communicator.stringToProxy("\"\"");
        test(b1 == null);
        try
        {
            b1 = communicator.stringToProxy("\"\" test"); // Invalid trailing characters.
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        try
        {
            b1 = communicator.stringToProxy("test:"); // Missing endpoint.
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        b1 = communicator.stringToProxy("test@adapter");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getAdapterId().Equals("adapter"));
        try
        {
            b1 = communicator.stringToProxy("id@adapter test");
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        b1 = communicator.stringToProxy("category/test@adapter");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category") &&
             b1.ice_getAdapterId().Equals("adapter"));
        b1 = communicator.stringToProxy("category/test@adapter:tcp");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category") &&
             b1.ice_getAdapterId().Equals("adapter:tcp"));
        b1 = communicator.stringToProxy("'category 1/test'@adapter");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category 1") &&
             b1.ice_getAdapterId().Equals("adapter"));
        b1 = communicator.stringToProxy("'category/test 1'@adapter");
        test(b1.ice_getIdentity().name.Equals("test 1") && b1.ice_getIdentity().category.Equals("category") &&
             b1.ice_getAdapterId().Equals("adapter"));
        b1 = communicator.stringToProxy("'category/test'@'adapter 1'");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category") &&
             b1.ice_getAdapterId().Equals("adapter 1"));
        b1 = communicator.stringToProxy("\"category \\/test@foo/test\"@adapter");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category /test@foo") &&
             b1.ice_getAdapterId().Equals("adapter"));
        b1 = communicator.stringToProxy("\"category \\/test@foo/test\"@\"adapter:tcp\"");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Equals("category /test@foo") &&
             b1.ice_getAdapterId().Equals("adapter:tcp"));

        b1 = communicator.stringToProxy("id -f facet");
        test(b1.ice_getIdentity().name.Equals("id") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet"));
        b1 = communicator.stringToProxy("id -f 'facet x'");
        test(b1.ice_getIdentity().name.Equals("id") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet x"));
        b1 = communicator.stringToProxy("id -f \"facet x\"");
        test(b1.ice_getIdentity().name.Equals("id") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet x"));
        try
        {
            b1 = communicator.stringToProxy("id -f \"facet x");
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        try
        {
            b1 = communicator.stringToProxy("id -f \'facet x");
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        b1 = communicator.stringToProxy("test -f facet:tcp");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet") && b1.ice_getAdapterId().Length == 0);
        b1 = communicator.stringToProxy("test -f \"facet:tcp\"");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet:tcp") && b1.ice_getAdapterId().Length == 0);
        b1 = communicator.stringToProxy("test -f facet@test");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet") && b1.ice_getAdapterId().Equals("test"));
        b1 = communicator.stringToProxy("test -f 'facet@test'");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet@test") && b1.ice_getAdapterId().Length == 0);
        b1 = communicator.stringToProxy("test -f 'facet@test'@test");
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getFacet().Equals("facet@test") && b1.ice_getAdapterId().Equals("test"));
        try
        {
            b1 = communicator.stringToProxy("test -f facet@test @test");
            test(false);
        }
        catch(Ice.ProxyParseException)
        {
        }
        b1 = communicator.stringToProxy("test");
        test(b1.ice_isTwoway());
        b1 = communicator.stringToProxy("test -t");
        test(b1.ice_isTwoway());
        b1 = communicator.stringToProxy("test -o");
        test(b1.ice_isOneway());
        b1 = communicator.stringToProxy("test -O");
        test(b1.ice_isBatchOneway());
        b1 = communicator.stringToProxy("test -d");
        test(b1.ice_isDatagram());
        b1 = communicator.stringToProxy("test -D");
        test(b1.ice_isBatchDatagram());
        b1 = communicator.stringToProxy("test");
        test(!b1.ice_isSecure());
        b1 = communicator.stringToProxy("test -s");
        test(b1.ice_isSecure());

        test(b1.ice_getEncodingVersion().Equals(Ice.Util.currentEncoding));

        b1 = communicator.stringToProxy("test -e 1.0");
        test(b1.ice_getEncodingVersion().major == 1 && b1.ice_getEncodingVersion().minor == 0);

        b1 = communicator.stringToProxy("test -e 6.5");
        test(b1.ice_getEncodingVersion().major == 6 && b1.ice_getEncodingVersion().minor == 5);

        b1 = communicator.stringToProxy("test -p 1.0 -e 1.0");
        test(b1.ToString().Equals("test -t -e 1.0"));
        
        b1 = communicator.stringToProxy("test -p 6.5 -e 1.0");
        test(b1.ToString().Equals("test -t -p 6.5 -e 1.0"));

        try
        {
            b1 = communicator.stringToProxy("test:tcp@adapterId");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }
        // This is an unknown endpoint warning, not a parse exception.
        //
        //try
        //{
        //   b1 = communicator.stringToProxy("test -f the:facet:tcp");
        //   test(false);
        //}
        //catch(Ice.EndpointParseException)
        //{
        //}
        try
        {
            b1 = communicator.stringToProxy("test::tcp");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }
        WriteLine("ok");

        Write("testing propertyToProxy... ");
        Flush();
        Ice.Properties prop = communicator.getProperties();
        String propertyPrefix = "Foo.Proxy";
        prop.setProperty(propertyPrefix, "test:default -p 12010");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getIdentity().name.Equals("test") && b1.ice_getIdentity().category.Length == 0 &&
             b1.ice_getAdapterId().Length == 0 && b1.ice_getFacet().Length == 0);

        String property;

        property = propertyPrefix + ".Locator";
        test(b1.ice_getLocator() == null);
        prop.setProperty(property, "locator:default -p 10000");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getLocator() != null && b1.ice_getLocator().ice_getIdentity().name.Equals("locator"));
        try
        {
                prop.setProperty(property, "");
        }
        catch(Exception ex)
        {
                System.Console.WriteLine(ex.ToString());
        }
        property = propertyPrefix + ".LocatorCacheTimeout";
        test(b1.ice_getLocatorCacheTimeout() == -1);
        prop.setProperty(property, "1");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getLocatorCacheTimeout() == 1);
        prop.setProperty(property, "");

        // Now retest with an indirect proxy.
        prop.setProperty(propertyPrefix, "test");
        property = propertyPrefix + ".Locator";
        prop.setProperty(property, "locator:default -p 10000");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getLocator() != null && b1.ice_getLocator().ice_getIdentity().name.Equals("locator"));
        prop.setProperty(property, "");

        property = propertyPrefix + ".LocatorCacheTimeout";
        test(b1.ice_getLocatorCacheTimeout() == -1);
        prop.setProperty(property, "1");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getLocatorCacheTimeout() == 1);
        prop.setProperty(property, "");

        // This cannot be tested so easily because the property is cached
        // on communicator initialization.
        //
        //prop.setProperty("Ice.Default.LocatorCacheTimeout", "60");
        //b1 = communicator.propertyToProxy(propertyPrefix);
        //test(b1.ice_getLocatorCacheTimeout() == 60);
        //prop.setProperty("Ice.Default.LocatorCacheTimeout", "");

        prop.setProperty(propertyPrefix, "test:default -p 12010");

        property = propertyPrefix + ".Router";
        test(b1.ice_getRouter() == null);
        prop.setProperty(property, "router:default -p 10000");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getRouter() != null && b1.ice_getRouter().ice_getIdentity().name.Equals("router"));
        prop.setProperty(property, "");

        property = propertyPrefix + ".PreferSecure";
        test(!b1.ice_isPreferSecure());
        prop.setProperty(property, "1");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_isPreferSecure());
        prop.setProperty(property, "");

        property = propertyPrefix + ".ConnectionCached";
        test(b1.ice_isConnectionCached());
        prop.setProperty(property, "0");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(!b1.ice_isConnectionCached());
        prop.setProperty(property, "");

        property = propertyPrefix + ".EndpointSelection";
        test(b1.ice_getEndpointSelection() == Ice.EndpointSelectionType.Random);
        prop.setProperty(property, "Random");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getEndpointSelection() == Ice.EndpointSelectionType.Random);
        prop.setProperty(property, "Ordered");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getEndpointSelection() == Ice.EndpointSelectionType.Ordered);
        prop.setProperty(property, "");

        property = propertyPrefix + ".CollocationOptimized";
        test(b1.ice_isCollocationOptimized());
        prop.setProperty(property, "0");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(!b1.ice_isCollocationOptimized());
        prop.setProperty(property, "");

        WriteLine("ok");

        Write("testing proxyToProperty... ");
        Flush();

        b1 = communicator.stringToProxy("test");
        b1 = b1.ice_collocationOptimized(true);
        b1 = b1.ice_connectionCached(true);
        b1 = b1.ice_preferSecure(false);
        b1 = b1.ice_endpointSelection(Ice.EndpointSelectionType.Ordered);
        b1 = b1.ice_locatorCacheTimeout(100);
        b1 = b1.ice_encodingVersion(new Ice.EncodingVersion(1, 0));

        Ice.ObjectPrx router = communicator.stringToProxy("router");
        router = router.ice_collocationOptimized(false);
        router = router.ice_connectionCached(true);
        router = router.ice_preferSecure(true);
        router = router.ice_endpointSelection(Ice.EndpointSelectionType.Random);
        router = router.ice_locatorCacheTimeout(200);

        Ice.ObjectPrx locator = communicator.stringToProxy("locator");
        locator = locator.ice_collocationOptimized(true);
        locator = locator.ice_connectionCached(false);
        locator = locator.ice_preferSecure(true);
        locator = locator.ice_endpointSelection(Ice.EndpointSelectionType.Random);
        locator = locator.ice_locatorCacheTimeout(300);

        locator = locator.ice_router(Ice.RouterPrxHelper.uncheckedCast(router));
        b1 = b1.ice_locator(Ice.LocatorPrxHelper.uncheckedCast(locator));

        Dictionary<string, string> proxyProps = communicator.proxyToProperty(b1, "Test");
        test(proxyProps.Count == 18);

        test(proxyProps["Test"].Equals("test -t -e 1.0"));
        test(proxyProps["Test.CollocationOptimized"].Equals("1"));
        test(proxyProps["Test.ConnectionCached"].Equals("1"));
        test(proxyProps["Test.PreferSecure"].Equals("0"));
        test(proxyProps["Test.EndpointSelection"].Equals("Ordered"));
        test(proxyProps["Test.LocatorCacheTimeout"].Equals("100"));

        test(proxyProps["Test.Locator"].Equals(
                 "locator -t -e " + Ice.Util.encodingVersionToString(Ice.Util.currentEncoding)));
        test(proxyProps["Test.Locator.CollocationOptimized"].Equals("1"));
        test(proxyProps["Test.Locator.ConnectionCached"].Equals("0"));
        test(proxyProps["Test.Locator.PreferSecure"].Equals("1"));
        test(proxyProps["Test.Locator.EndpointSelection"].Equals("Random"));
        test(proxyProps["Test.Locator.LocatorCacheTimeout"].Equals("300"));
                                                        
        test(proxyProps["Test.Locator.Router"].Equals(
                 "router -t -e " + Ice.Util.encodingVersionToString(Ice.Util.currentEncoding)));
        test(proxyProps["Test.Locator.Router.CollocationOptimized"].Equals("0"));
        test(proxyProps["Test.Locator.Router.ConnectionCached"].Equals("1"));
        test(proxyProps["Test.Locator.Router.PreferSecure"].Equals("1"));
        test(proxyProps["Test.Locator.Router.EndpointSelection"].Equals("Random"));
        test(proxyProps["Test.Locator.Router.LocatorCacheTimeout"].Equals("200"));
                                                          
        WriteLine("ok");

        Write("testing ice_getCommunicator... ");
        Flush();
        test(baseProxy.ice_getCommunicator() == communicator);
        WriteLine("ok");

        Write("testing proxy methods... ");
        test(communicator.identityToString(
                 baseProxy.ice_identity(communicator.stringToIdentity("other")).ice_getIdentity()).Equals("other"));
        test(baseProxy.ice_facet("facet").ice_getFacet().Equals("facet"));
        test(baseProxy.ice_adapterId("id").ice_getAdapterId().Equals("id"));
        test(baseProxy.ice_twoway().ice_isTwoway());
        test(baseProxy.ice_oneway().ice_isOneway());
        test(baseProxy.ice_batchOneway().ice_isBatchOneway());
        test(baseProxy.ice_datagram().ice_isDatagram());
        test(baseProxy.ice_batchDatagram().ice_isBatchDatagram());
        test(baseProxy.ice_secure(true).ice_isSecure());
        test(!baseProxy.ice_secure(false).ice_isSecure());
        test(baseProxy.ice_collocationOptimized(true).ice_isCollocationOptimized());
        test(!baseProxy.ice_collocationOptimized(false).ice_isCollocationOptimized());
        test(baseProxy.ice_preferSecure(true).ice_isPreferSecure());
        test(!baseProxy.ice_preferSecure(false).ice_isPreferSecure());
        WriteLine("ok");

        Write("testing proxy comparison... ");
        Flush();

        test(communicator.stringToProxy("foo").Equals(communicator.stringToProxy("foo")));
        test(!communicator.stringToProxy("foo").Equals(communicator.stringToProxy("foo2")));

        Ice.ObjectPrx compObj = communicator.stringToProxy("foo");

        test(compObj.ice_facet("facet").Equals(compObj.ice_facet("facet")));
        test(!compObj.ice_facet("facet").Equals(compObj.ice_facet("facet1")));

        test(compObj.ice_oneway().Equals(compObj.ice_oneway()));
        test(!compObj.ice_oneway().Equals(compObj.ice_twoway()));

        test(compObj.ice_secure(true).Equals(compObj.ice_secure(true)));
        test(!compObj.ice_secure(false).Equals(compObj.ice_secure(true)));

        test(compObj.ice_collocationOptimized(true).Equals(compObj.ice_collocationOptimized(true)));
        test(!compObj.ice_collocationOptimized(false).Equals(compObj.ice_collocationOptimized(true)));

        test(compObj.ice_connectionCached(true).Equals(compObj.ice_connectionCached(true)));
        test(!compObj.ice_connectionCached(false).Equals(compObj.ice_connectionCached(true)));

        test(compObj.ice_endpointSelection(Ice.EndpointSelectionType.Random).Equals(
                 compObj.ice_endpointSelection(Ice.EndpointSelectionType.Random)));
        test(!compObj.ice_endpointSelection(Ice.EndpointSelectionType.Random).Equals(
                 compObj.ice_endpointSelection(Ice.EndpointSelectionType.Ordered)));

        test(compObj.ice_connectionId("id2").Equals(compObj.ice_connectionId("id2")));
        test(!compObj.ice_connectionId("id1").Equals(compObj.ice_connectionId("id2")));
        test(compObj.ice_connectionId("id1").ice_getConnectionId().Equals("id1"));
        test(compObj.ice_connectionId("id2").ice_getConnectionId().Equals("id2"));

        test(compObj.ice_compress(true).Equals(compObj.ice_compress(true)));
        test(!compObj.ice_compress(false).Equals(compObj.ice_compress(true)));

        test(compObj.ice_timeout(20).Equals(compObj.ice_timeout(20)));
        test(!compObj.ice_timeout(10).Equals(compObj.ice_timeout(20)));

        Ice.LocatorPrx loc1 = Ice.LocatorPrxHelper.uncheckedCast(communicator.stringToProxy("loc1:default -p 10000"));
        Ice.LocatorPrx loc2 = Ice.LocatorPrxHelper.uncheckedCast(communicator.stringToProxy("loc2:default -p 10000"));
        test(compObj.ice_locator(null).Equals(compObj.ice_locator(null)));
        test(compObj.ice_locator(loc1).Equals(compObj.ice_locator(loc1)));
        test(!compObj.ice_locator(loc1).Equals(compObj.ice_locator(null)));
        test(!compObj.ice_locator(null).Equals(compObj.ice_locator(loc2)));
        test(!compObj.ice_locator(loc1).Equals(compObj.ice_locator(loc2)));

        Ice.RouterPrx rtr1 = Ice.RouterPrxHelper.uncheckedCast(communicator.stringToProxy("rtr1:default -p 10000"));
        Ice.RouterPrx rtr2 = Ice.RouterPrxHelper.uncheckedCast(communicator.stringToProxy("rtr2:default -p 10000"));
        test(compObj.ice_router(null).Equals(compObj.ice_router(null)));
        test(compObj.ice_router(rtr1).Equals(compObj.ice_router(rtr1)));
        test(!compObj.ice_router(rtr1).Equals(compObj.ice_router(null)));
        test(!compObj.ice_router(null).Equals(compObj.ice_router(rtr2)));
        test(!compObj.ice_router(rtr1).Equals(compObj.ice_router(rtr2)));

        Dictionary<string, string> ctx1 = new Dictionary<string, string>();
        ctx1["ctx1"] = "v1";
        Dictionary<string, string> ctx2 = new Dictionary<string, string>();
        ctx2["ctx2"] = "v2";
        test(compObj.ice_context(null).Equals(compObj.ice_context(null)));
        test(compObj.ice_context(ctx1).Equals(compObj.ice_context(ctx1)));
        test(!compObj.ice_context(ctx1).Equals(compObj.ice_context(null)));
        test(!compObj.ice_context(null).Equals(compObj.ice_context(ctx2)));
        test(!compObj.ice_context(ctx1).Equals(compObj.ice_context(ctx2)));

        test(compObj.ice_preferSecure(true).Equals(compObj.ice_preferSecure(true)));
        test(!compObj.ice_preferSecure(true).Equals(compObj.ice_preferSecure(false)));

        Ice.ObjectPrx compObj1 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10000");
        Ice.ObjectPrx compObj2 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10001");
        test(!compObj1.Equals(compObj2));

        compObj1 = communicator.stringToProxy("foo@MyAdapter1");
        compObj2 = communicator.stringToProxy("foo@MyAdapter2");
        test(!compObj1.Equals(compObj2));

        test(compObj1.ice_locatorCacheTimeout(20).Equals(compObj1.ice_locatorCacheTimeout(20)));
        test(!compObj1.ice_locatorCacheTimeout(10).Equals(compObj1.ice_locatorCacheTimeout(20)));

        compObj1 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 1000");
        compObj2 = communicator.stringToProxy("foo@MyAdapter1");
        test(!compObj1.Equals(compObj2));

        Ice.Endpoint[] endpts1 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10000").ice_getEndpoints();
        Ice.Endpoint[] endpts2 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10001").ice_getEndpoints();
        test(!endpts1[0].Equals(endpts2[0]));
        test(endpts1[0].Equals(communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10000").ice_getEndpoints()[0]));

        //
        // TODO: Ideally we should also test comparison of fixed proxies.
        //
        WriteLine("ok");

        Write("testing checked cast... ");
        Flush();
        Test.MyClassPrx cl = Test.MyClassPrxHelper.checkedCast(baseProxy);
        test(cl != null);
        Test.MyDerivedClassPrx derived = Test.MyDerivedClassPrxHelper.checkedCast(cl);
        test(derived != null);
        test(cl.Equals(baseProxy));
        test(derived.Equals(baseProxy));
        test(cl.Equals(derived));
        WriteLine("ok");

        Write("testing checked cast with context... ");
        Flush();

        Dictionary<string, string> c = cl.getContext();
        test(c == null || c.Count == 0);

        c = new Dictionary<string, string>();
        c["one"] = "hello";
        c["two"] = "world";
        cl = Test.MyClassPrxHelper.checkedCast(baseProxy, c);
        Dictionary<string, string> c2 = cl.getContext();
        test(Ice.CollectionComparer.Equals(c, c2));
        WriteLine("ok");

        Write("testing encoding versioning... ");
        Flush();
        string ref20 = "test -e 2.0:default -p 12010";
        Test.MyClassPrx cl20 = Test.MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref20));
        try 
        {
            cl20.ice_collocationOptimized(false).ice_ping();
            test(false);
        }
        catch(Ice.UnsupportedEncodingException)
        {
            // Server 2.0 endpoint doesn't support 1.1 version.
        }

        string ref10 = "test -e 1.0:default -p 12010";
        Test.MyClassPrx cl10 = Test.MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref10));
        cl10.ice_ping();
        cl10.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();
        cl.ice_collocationOptimized(false).ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();

        // 1.3 isn't supported but since a 1.3 proxy supports 1.1, the
        // call will use the 1.1 encoding
        string ref13 = "test -e 1.3:default -p 12010";
        Test.MyClassPrx cl13 = Test.MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref13));
        cl13.ice_ping();
        try
        {
            cl13.end_ice_ping(cl13.begin_ice_ping());
        }
        catch(Ice.CollocationOptimizationException)
        {
        }

        try
        {
            // Send request with bogus 1.2 encoding.
            Ice.EncodingVersion version = new Ice.EncodingVersion(1, 2);
            Ice.OutputStream os = Ice.Util.createOutputStream(communicator);
            os.startEncapsulation();
            os.endEncapsulation();
            byte[] inEncaps = os.finished();
            inEncaps[4] = version.major;
            inEncaps[5] = version.minor;
            byte[] outEncaps;
            cl.ice_collocationOptimized(false).ice_invoke("ice_ping", Ice.OperationMode.Normal, inEncaps,
                                                          out outEncaps);
            test(false);
        }
        catch(Ice.UnknownLocalException ex)
        {
            // The server thrown an UnsupportedEncodingException
            test(ex.unknown.IndexOf("UnsupportedEncodingException") > 0);
        }

        try
        {
            // Send request with bogus 2.0 encoding.
            Ice.EncodingVersion version = new Ice.EncodingVersion(2, 0);
            Ice.OutputStream os = Ice.Util.createOutputStream(communicator);
            os.startEncapsulation();
            os.endEncapsulation();
            byte[] inEncaps = os.finished();
            inEncaps[4] = version.major;
            inEncaps[5] = version.minor;
            byte[] outEncaps;
            cl.ice_collocationOptimized(false).ice_invoke("ice_ping", Ice.OperationMode.Normal, inEncaps, 
                                                          out outEncaps);
            test(false);
        }
        catch(Ice.UnknownLocalException ex)
        {
            // The server thrown an UnsupportedEncodingException
            test(ex.unknown.IndexOf("UnsupportedEncodingException") > 0);
        }

        WriteLine("ok");

        Write("testing protocol versioning... ");
        Flush();
        ref20 = "test -p 2.0:default -p 12010";
        cl20 = Test.MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref20));
        try 
        {
            cl20.ice_collocationOptimized(false).ice_ping();
            test(false);
        }
        catch(Ice.UnsupportedProtocolException)
        {
            // Server 2.0 proxy doesn't support 1.0 version.
        }

        ref10 = "test -p 1.0:default -p 12010";
        cl10 = Test.MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref10));
        cl10.ice_ping();

        // 1.3 isn't supported but since a 1.3 proxy supports 1.1, the
        // call will use the 1.1 protocol
        ref13 = "test -p 1.3:default -p 12010";
        cl13 = Test.MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref13));
        cl13.ice_ping();
        try
        {
            cl13.end_ice_ping(cl13.begin_ice_ping());
        }
        catch(Ice.CollocationOptimizationException)
        {
        }
        WriteLine("ok");

        Write("testing opaque endpoints... ");
        Flush();

        try
        {
            // Invalid -x option
            communicator.stringToProxy("id:opaque -t 99 -v abc -x abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Missing -t and -v
            communicator.stringToProxy("id:opaque");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Repeated -t
            communicator.stringToProxy("id:opaque -t 1 -t 1 -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Repeated -v
            communicator.stringToProxy("id:opaque -t 1 -v abc -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Missing -t
            communicator.stringToProxy("id:opaque -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Missing -v
            communicator.stringToProxy("id:opaque -t 1");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Missing arg for -t
            communicator.stringToProxy("id:opaque -t -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Missing arg for -v
            communicator.stringToProxy("id:opaque -t 1 -v");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Not a number for -t
            communicator.stringToProxy("id:opaque -t x -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // < 0 for -t
            communicator.stringToProxy("id:opaque -t -1 -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        try
        {
            // Invalid char for -v
            communicator.stringToProxy("id:opaque -t 99 -v x?c");
            test(false);
        }
        catch(Ice.EndpointParseException)
        {
        }

        // Legal TCP endpoint expressed as opaque endpoint
        Ice.ObjectPrx p1 = communicator.stringToProxy("test -e 1.1:opaque -t 1 -e 1.0 -v CTEyNy4wLjAuMeouAAAQJwAAAA==");
        string pstr = communicator.proxyToString(p1);
        test(pstr.Equals("test -t -e 1.1:tcp -h 127.0.0.1 -p 12010 -t 10000"));

        // Opaque endpoint encoded with 1.1 encoding.
        Ice.ObjectPrx p2 = communicator.stringToProxy("test -e 1.1:opaque -e 1.1 -t 1 -v CTEyNy4wLjAuMeouAAAQJwAAAA==");
        test(communicator.proxyToString(p2).Equals("test -t -e 1.1:tcp -h 127.0.0.1 -p 12010 -t 10000"));
        
        if(communicator.getProperties().getPropertyAsInt("Ice.IPv6") == 0)
        {
            // Working?
            bool ssl = communicator.getProperties().getProperty("Ice.Default.Protocol").Equals("ssl");
            if(!ssl)
            {
                p1.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();
            }

            // Two legal TCP endpoints expressed as opaque endpoints
            p1 = communicator.stringToProxy("test -e 1.0:opaque -e 1.0 -t 1 -v CTEyNy4wLjAuMeouAAAQJwAAAA==:opaque -e 1.0 -t 1 -v CTEyNy4wLjAuMusuAAAQJwAAAA==");
            pstr = communicator.proxyToString(p1);
            test(pstr.Equals("test -t -e 1.0:tcp -h 127.0.0.1 -p 12010 -t 10000:tcp -h 127.0.0.2 -p 12011 -t 10000"));

            // Test that an SSL endpoint and a nonsense endpoint get written back out as an opaque endpoint.
            p1 = communicator.stringToProxy("test -e 1.0:opaque -e 1.0 -t 2 -v CTEyNy4wLjAuMREnAAD/////AA==:opaque -e 1.0 -t 99 -v abch");
            pstr = communicator.proxyToString(p1);
            if(!ssl)
            {
                test(pstr.Equals("test -t -e 1.0:opaque -t 2 -e 1.0 -v CTEyNy4wLjAuMREnAAD/////AA==:opaque -t 99 -e 1.0 -v abch"));
            }
            else
            {
                test(pstr.Equals("test -t -e 1.0:ssl -h 127.0.0.1 -p 10001:opaque -t 99 -e 1.0 -v abch"));
            }
        }

        WriteLine("ok");
#if SILVERLIGHT
        cl.shutdown();
#else
        return cl;
#endif
    }
}
