// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.proxy;
import java.io.PrintWriter;

import test.Ice.proxy.Test.MyClassPrx;
import test.Ice.proxy.Test.MyClassPrxHelper;
import test.Ice.proxy.Test.MyDerivedClassPrx;
import test.Ice.proxy.Test.MyDerivedClassPrxHelper;

public class AllTests
{
    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    public static MyClassPrx
    allTests(Ice.Communicator communicator, PrintWriter out)
    {
        out.print("testing stringToProxy... ");
        out.flush();
        String ref = "test:default -p 12010";
        Ice.ObjectPrx base = communicator.stringToProxy(ref);
        test(base != null);

        Ice.ObjectPrx b1 = communicator.stringToProxy("test");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getAdapterId().length() == 0 && b1.ice_getFacet().length() == 0);
        b1 = communicator.stringToProxy("test ");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        b1 = communicator.stringToProxy(" test ");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        b1 = communicator.stringToProxy(" test");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        b1 = communicator.stringToProxy("'test -f facet'");
        test(b1.ice_getIdentity().name.equals("test -f facet") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        try
        {
            b1 = communicator.stringToProxy("\"test -f facet'");
            test(false);
        }
        catch(Ice.ProxyParseException ex)
        {
        }
        b1 = communicator.stringToProxy("\"test -f facet\"");
        test(b1.ice_getIdentity().name.equals("test -f facet") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        b1 = communicator.stringToProxy("\"test -f facet@test\"");
        test(b1.ice_getIdentity().name.equals("test -f facet@test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        b1 = communicator.stringToProxy("\"test -f facet@test @test\"");
        test(b1.ice_getIdentity().name.equals("test -f facet@test @test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().length() == 0);
        try
        {
            b1 = communicator.stringToProxy("test test");
            test(false);
        }
        catch(Ice.ProxyParseException ex)
        {
        }
        b1 = communicator.stringToProxy("test\\040test");
        test(b1.ice_getIdentity().name.equals("test test") && b1.ice_getIdentity().category.length() == 0);
        try
        {
            b1 = communicator.stringToProxy("test\\777");
            test(false);
        }
        catch(Ice.IdentityParseException ex)
        {
        }
        b1 = communicator.stringToProxy("test\\40test");
        test(b1.ice_getIdentity().name.equals("test test"));

        // Test some octal and hex corner cases.
        b1 = communicator.stringToProxy("test\\4test");
        test(b1.ice_getIdentity().name.equals("test\4test"));
        b1 = communicator.stringToProxy("test\\04test");
        test(b1.ice_getIdentity().name.equals("test\4test"));
        b1 = communicator.stringToProxy("test\\004test");
        test(b1.ice_getIdentity().name.equals("test\4test"));
        b1 = communicator.stringToProxy("test\\1114test");
        test(b1.ice_getIdentity().name.equals("test\1114test"));

        b1 = communicator.stringToProxy("test\\b\\f\\n\\r\\t\\'\\\"\\\\test");
        test(b1.ice_getIdentity().name.equals("test\b\f\n\r\t\'\"\\test") &&
             b1.ice_getIdentity().category.length() == 0);

        b1 = communicator.stringToProxy("category/test");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category") &&
             b1.ice_getAdapterId().length() == 0);

        b1 = communicator.stringToProxy("");
        test(b1 == null);
        b1 = communicator.stringToProxy("\"\"");
        test(b1 == null);
        try
        {
            b1 = communicator.stringToProxy("\"\" test"); // Invalid trailing characters.
            test(false);
        }
        catch(Ice.ProxyParseException ex)
        {
        }
        try
        {
            b1 = communicator.stringToProxy("test:"); // Missing endpoint.
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        b1 = communicator.stringToProxy("test@adapter");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getAdapterId().equals("adapter"));
        try
        {
            b1 = communicator.stringToProxy("id@adapter test");
            test(false);
        }
        catch(Ice.ProxyParseException ex)
        {
        }
        b1 = communicator.stringToProxy("category/test@adapter");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category") &&
             b1.ice_getAdapterId().equals("adapter"));
        b1 = communicator.stringToProxy("category/test@adapter:tcp");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category") &&
             b1.ice_getAdapterId().equals("adapter:tcp"));
        b1 = communicator.stringToProxy("'category 1/test'@adapter");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category 1") &&
             b1.ice_getAdapterId().equals("adapter"));
        b1 = communicator.stringToProxy("'category/test 1'@adapter");
        test(b1.ice_getIdentity().name.equals("test 1") && b1.ice_getIdentity().category.equals("category") &&
             b1.ice_getAdapterId().equals("adapter"));
        b1 = communicator.stringToProxy("'category/test'@'adapter 1'");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category") &&
             b1.ice_getAdapterId().equals("adapter 1"));
        b1 = communicator.stringToProxy("\"category \\/test@foo/test\"@adapter");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category /test@foo") &&
             b1.ice_getAdapterId().equals("adapter"));
        b1 = communicator.stringToProxy("\"category \\/test@foo/test\"@\"adapter:tcp\"");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.equals("category /test@foo") &&
             b1.ice_getAdapterId().equals("adapter:tcp"));

        b1 = communicator.stringToProxy("id -f facet");
        test(b1.ice_getIdentity().name.equals("id") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet"));
        b1 = communicator.stringToProxy("id -f 'facet x'");
        test(b1.ice_getIdentity().name.equals("id") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet x"));
        b1 = communicator.stringToProxy("id -f \"facet x\"");
        test(b1.ice_getIdentity().name.equals("id") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet x"));
        try
        {
            b1 = communicator.stringToProxy("id -f \"facet x");
            test(false);
        }
        catch(Ice.ProxyParseException ex)
        {
        }
        try
        {
            b1 = communicator.stringToProxy("id -f \'facet x");
            test(false);
        }
        catch(Ice.ProxyParseException ex)
        {
        }
        b1 = communicator.stringToProxy("test -f facet:tcp");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet") && b1.ice_getAdapterId().length() == 0);
        b1 = communicator.stringToProxy("test -f \"facet:tcp\"");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet:tcp") && b1.ice_getAdapterId().length() == 0);
        b1 = communicator.stringToProxy("test -f facet@test");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet") && b1.ice_getAdapterId().equals("test"));
        b1 = communicator.stringToProxy("test -f 'facet@test'");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet@test") && b1.ice_getAdapterId().length() == 0);
        b1 = communicator.stringToProxy("test -f 'facet@test'@test");
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getFacet().equals("facet@test") && b1.ice_getAdapterId().equals("test"));
        try
        {
            b1 = communicator.stringToProxy("test -f facet@test @test");
            test(false);
        }
        catch(Ice.ProxyParseException ex)
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

        test(b1.ice_getEncodingVersion().equals(Ice.Util.currentEncoding()));

        b1 = communicator.stringToProxy("test -e 1.0");
        test(b1.ice_getEncodingVersion().major == 1 && b1.ice_getEncodingVersion().minor == 0);

        b1 = communicator.stringToProxy("test -e 6.5");
        test(b1.ice_getEncodingVersion().major == 6 && b1.ice_getEncodingVersion().minor == 5);

        b1 = communicator.stringToProxy("test -p 1.0 -e 1.0");
        test(b1.toString().equals("test -t -e 1.0"));
        
        b1 = communicator.stringToProxy("test -p 6.5 -e 1.0");
        test(b1.toString().equals("test -t -p 6.5 -e 1.0"));

        try
        {
            b1 = communicator.stringToProxy("test:tcp@adapterId");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }
        // This is an unknown endpoint warning, not a parse exception.
        //
        //try
        //{
        //   b1 = communicator.stringToProxy("test -f the:facet:tcp");
        //   test(false);
        //}
        //catch(Ice.EndpointParseException ex)
        //{
        //}
        try
        {
            b1 = communicator.stringToProxy("test::tcp");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }
        out.println("ok");

        out.print("testing propertyToProxy... ");
        out.flush();
        Ice.Properties prop = communicator.getProperties();
        String propertyPrefix = "Foo.Proxy";
        prop.setProperty(propertyPrefix, "test:default -p 12010");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getIdentity().name.equals("test") && b1.ice_getIdentity().category.length() == 0 &&
             b1.ice_getAdapterId().length() == 0 && b1.ice_getFacet().length() == 0);

        String property;

        property = propertyPrefix + ".Locator";
        test(b1.ice_getLocator() == null);
        prop.setProperty(property, "locator:default -p 10000");
        b1 = communicator.propertyToProxy(propertyPrefix);
        test(b1.ice_getLocator() != null && b1.ice_getLocator().ice_getIdentity().name.equals("locator"));
        prop.setProperty(property, "");

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
        test(b1.ice_getLocator() != null && b1.ice_getLocator().ice_getIdentity().name.equals("locator"));
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
        test(b1.ice_getRouter() != null && b1.ice_getRouter().ice_getIdentity().name.equals("router"));
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

        out.println("ok");

        out.print("testing proxyToProperty... ");
        out.flush();

        b1 = communicator.stringToProxy("test");
        b1 = b1.ice_collocationOptimized(true);
        b1 = b1.ice_connectionCached(true);
        b1 = b1.ice_preferSecure(false);
        b1 = b1.ice_endpointSelection(Ice.EndpointSelectionType.Ordered);
        b1 = b1.ice_locatorCacheTimeout(100);
        b1 = b1.ice_encodingVersion(new Ice.EncodingVersion((byte)1, (byte)0));

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

        java.util.Map<String, String> proxyProps = communicator.proxyToProperty(b1, "Test");
        test(proxyProps.size() == 18);

        test(proxyProps.get("Test").equals("test -t -e 1.0"));
        test(proxyProps.get("Test.CollocationOptimized").equals("1"));
        test(proxyProps.get("Test.ConnectionCached").equals("1"));
        test(proxyProps.get("Test.PreferSecure").equals("0"));
        test(proxyProps.get("Test.EndpointSelection").equals("Ordered"));
        test(proxyProps.get("Test.LocatorCacheTimeout").equals("100"));

        test(proxyProps.get("Test.Locator").equals(
                 "locator -t -e " + Ice.Util.encodingVersionToString(Ice.Util.currentEncoding())));
        test(proxyProps.get("Test.Locator.CollocationOptimized").equals("1"));
        test(proxyProps.get("Test.Locator.ConnectionCached").equals("0"));
        test(proxyProps.get("Test.Locator.PreferSecure").equals("1"));
        test(proxyProps.get("Test.Locator.EndpointSelection").equals("Random"));
        test(proxyProps.get("Test.Locator.LocatorCacheTimeout").equals("300"));

        test(proxyProps.get("Test.Locator.Router").equals(
                 "router -t -e " + Ice.Util.encodingVersionToString(Ice.Util.currentEncoding())));
        test(proxyProps.get("Test.Locator.Router.CollocationOptimized").equals("0"));
        test(proxyProps.get("Test.Locator.Router.ConnectionCached").equals("1"));
        test(proxyProps.get("Test.Locator.Router.PreferSecure").equals("1"));
        test(proxyProps.get("Test.Locator.Router.EndpointSelection").equals("Random"));
        test(proxyProps.get("Test.Locator.Router.LocatorCacheTimeout").equals("200"));

        out.println("ok");

        out.print("testing ice_getCommunicator... ");
        out.flush();
        test(base.ice_getCommunicator() == communicator);
        out.println("ok");

        out.print("testing proxy methods... ");
        out.flush();
        test(communicator.identityToString(
                 base.ice_identity(communicator.stringToIdentity("other")).ice_getIdentity()).equals("other"));
        test(base.ice_facet("facet").ice_getFacet().equals("facet"));
        test(base.ice_adapterId("id").ice_getAdapterId().equals("id"));
        test(base.ice_twoway().ice_isTwoway());
        test(base.ice_oneway().ice_isOneway());
        test(base.ice_batchOneway().ice_isBatchOneway());
        test(base.ice_datagram().ice_isDatagram());
        test(base.ice_batchDatagram().ice_isBatchDatagram());
        test(base.ice_secure(true).ice_isSecure());
        test(!base.ice_secure(false).ice_isSecure());
        test(base.ice_collocationOptimized(true).ice_isCollocationOptimized());
        test(!base.ice_collocationOptimized(false).ice_isCollocationOptimized());
        test(base.ice_preferSecure(true).ice_isPreferSecure());
        test(!base.ice_preferSecure(false).ice_isPreferSecure());
        test(base.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_getEncodingVersion().equals(Ice.Util.Encoding_1_0));
        test(base.ice_encodingVersion(Ice.Util.Encoding_1_1).ice_getEncodingVersion().equals(Ice.Util.Encoding_1_1));
        test(!base.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_getEncodingVersion().equals(Ice.Util.Encoding_1_1));
        out.println("ok");

        out.print("testing proxy comparison... ");
        out.flush();

        test(communicator.stringToProxy("foo").equals(communicator.stringToProxy("foo")));
        test(!communicator.stringToProxy("foo").equals(communicator.stringToProxy("foo2")));

        Ice.ObjectPrx compObj = communicator.stringToProxy("foo");

        test(compObj.ice_facet("facet").equals(compObj.ice_facet("facet")));
        test(!compObj.ice_facet("facet").equals(compObj.ice_facet("facet1")));

        test(compObj.ice_oneway().equals(compObj.ice_oneway()));
        test(!compObj.ice_oneway().equals(compObj.ice_twoway()));

        test(compObj.ice_secure(true).equals(compObj.ice_secure(true)));
        test(!compObj.ice_secure(false).equals(compObj.ice_secure(true)));

        test(compObj.ice_collocationOptimized(true).equals(compObj.ice_collocationOptimized(true)));
        test(!compObj.ice_collocationOptimized(false).equals(compObj.ice_collocationOptimized(true)));

        test(compObj.ice_connectionCached(true).equals(compObj.ice_connectionCached(true)));
        test(!compObj.ice_connectionCached(false).equals(compObj.ice_connectionCached(true)));

        test(compObj.ice_endpointSelection(Ice.EndpointSelectionType.Random).equals(
                 compObj.ice_endpointSelection(Ice.EndpointSelectionType.Random)));
        test(!compObj.ice_endpointSelection(Ice.EndpointSelectionType.Random).equals(
                 compObj.ice_endpointSelection(Ice.EndpointSelectionType.Ordered)));

        test(compObj.ice_connectionId("id2").equals(compObj.ice_connectionId("id2")));
        test(!compObj.ice_connectionId("id1").equals(compObj.ice_connectionId("id2")));

        test(compObj.ice_connectionId("id1").ice_getConnectionId().equals("id1"));
        test(compObj.ice_connectionId("id2").ice_getConnectionId().equals("id2"));


        test(compObj.ice_compress(true).equals(compObj.ice_compress(true)));
        test(!compObj.ice_compress(false).equals(compObj.ice_compress(true)));

        test(compObj.ice_timeout(20).equals(compObj.ice_timeout(20)));
        test(!compObj.ice_timeout(10).equals(compObj.ice_timeout(20)));

        Ice.LocatorPrx loc1 = Ice.LocatorPrxHelper.uncheckedCast(communicator.stringToProxy("loc1:default -p 10000"));
        Ice.LocatorPrx loc2 = Ice.LocatorPrxHelper.uncheckedCast(communicator.stringToProxy("loc2:default -p 10000"));
        test(compObj.ice_locator(null).equals(compObj.ice_locator(null)));
        test(compObj.ice_locator(loc1).equals(compObj.ice_locator(loc1)));
        test(!compObj.ice_locator(loc1).equals(compObj.ice_locator(null)));
        test(!compObj.ice_locator(null).equals(compObj.ice_locator(loc2)));
        test(!compObj.ice_locator(loc1).equals(compObj.ice_locator(loc2)));

        Ice.RouterPrx rtr1 = Ice.RouterPrxHelper.uncheckedCast(communicator.stringToProxy("rtr1:default -p 10000"));
        Ice.RouterPrx rtr2 = Ice.RouterPrxHelper.uncheckedCast(communicator.stringToProxy("rtr2:default -p 10000"));
        test(compObj.ice_router(null).equals(compObj.ice_router(null)));
        test(compObj.ice_router(rtr1).equals(compObj.ice_router(rtr1)));
        test(!compObj.ice_router(rtr1).equals(compObj.ice_router(null)));
        test(!compObj.ice_router(null).equals(compObj.ice_router(rtr2)));
        test(!compObj.ice_router(rtr1).equals(compObj.ice_router(rtr2)));

        java.util.Map<String, String> ctx1 = new java.util.HashMap<String, String>();
        ctx1.put("ctx1", "v1");
        java.util.Map<String, String> ctx2 = new java.util.HashMap<String, String>();
        ctx2.put("ctx2", "v2");
        test(compObj.ice_context(null).equals(compObj.ice_context(null)));
        test(compObj.ice_context(ctx1).equals(compObj.ice_context(ctx1)));
        test(!compObj.ice_context(ctx1).equals(compObj.ice_context(null)));
        test(!compObj.ice_context(null).equals(compObj.ice_context(ctx2)));
        test(!compObj.ice_context(ctx1).equals(compObj.ice_context(ctx2)));

        test(compObj.ice_preferSecure(true).equals(compObj.ice_preferSecure(true)));
        test(!compObj.ice_preferSecure(true).equals(compObj.ice_preferSecure(false)));

        Ice.ObjectPrx compObj1 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10000");
        Ice.ObjectPrx compObj2 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10001");
        test(!compObj1.equals(compObj2));

        compObj1 = communicator.stringToProxy("foo@MyAdapter1");
        compObj2 = communicator.stringToProxy("foo@MyAdapter2");
        test(!compObj1.equals(compObj2));

        test(compObj1.ice_locatorCacheTimeout(20).equals(compObj1.ice_locatorCacheTimeout(20)));
        test(!compObj1.ice_locatorCacheTimeout(10).equals(compObj1.ice_locatorCacheTimeout(20)));

        compObj1 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 1000");
        compObj2 = communicator.stringToProxy("foo@MyAdapter1");
        test(!compObj1.equals(compObj2));

        Ice.Endpoint[] endpts1 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10000").ice_getEndpoints();
        Ice.Endpoint[] endpts2 = communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10001").ice_getEndpoints();
        test(!endpts1[0].equals(endpts2[0]));
        test(endpts1[0].equals(communicator.stringToProxy("foo:tcp -h 127.0.0.1 -p 10000").ice_getEndpoints()[0]));

        test(compObj1.ice_encodingVersion(Ice.Util.Encoding_1_0).equals(
                 compObj1.ice_encodingVersion(Ice.Util.Encoding_1_0)));
        test(!compObj1.ice_encodingVersion(Ice.Util.Encoding_1_0).equals(
                 compObj1.ice_encodingVersion(Ice.Util.Encoding_1_1)));

        //
        // TODO: Ideally we should also test comparison of fixed proxies.
        //
        out.println("ok");

        out.print("testing checked cast... ");
        out.flush();
        MyClassPrx cl = MyClassPrxHelper.checkedCast(base);
        test(cl != null);
        MyDerivedClassPrx derived = MyDerivedClassPrxHelper.checkedCast(cl);
        test(derived != null);
        test(cl.equals(base));
        test(derived.equals(base));
        test(cl.equals(derived));
        out.println("ok");

        out.print("testing checked cast with context... ");
        out.flush();

        java.util.Map<String, String> c = cl.getContext();
        test(c == null || c.size() == 0);

        c = new java.util.HashMap<String, String>();
        c.put("one", "hello");
        c.put("two", "world");
        cl = MyClassPrxHelper.checkedCast(base, c);
        java.util.Map<String, String> c2 = cl.getContext();
        test(c.equals(c2));
        out.println("ok");

        out.print("testing encoding versioning... ");
        out.flush();
        String ref20 = "test -e 2.0:default -p 12010";
        MyClassPrx cl20 = MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref20));
        try 
        {
            cl20.ice_collocationOptimized(false).ice_ping();
            test(false);
        }
        catch(Ice.UnsupportedEncodingException ex)
        {
            // Server 2.0 endpoint doesn't support 1.1 version.
        }

        String ref10 = "test -e 1.0:default -p 12010";
        MyClassPrx cl10 = MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref10));
        cl10.ice_ping();
        cl10.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();
        cl.ice_collocationOptimized(false).ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();

        // 1.3 isn't supported but since a 1.3 proxy supports 1.1, the
        // call will use the 1.1 encoding
        String ref13 = "test -e 1.3:default -p 12010";
        MyClassPrx cl13 = MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref13));
        cl13.ice_ping();
        try
        {
            cl13.end_ice_ping(cl13.begin_ice_ping());
        }
        catch(Ice.CollocationOptimizationException ex)
        {
        }

        try
        {
            // Send request with bogus 1.2 encoding.
            Ice.EncodingVersion version = new Ice.EncodingVersion((byte)1, (byte)2);
            Ice.OutputStream os = Ice.Util.createOutputStream(communicator);
            os.startEncapsulation();
            os.endEncapsulation();
            byte[] inEncaps = os.finished();
            inEncaps[4] = version.major;
            inEncaps[5] = version.minor;
            Ice.ByteSeqHolder outEncaps = new Ice.ByteSeqHolder();
            cl.ice_collocationOptimized(false).ice_invoke("ice_ping", Ice.OperationMode.Normal, inEncaps, outEncaps);
            test(false);
        }
        catch(Ice.UnknownLocalException ex)
        {
            // The server thrown an UnsupportedEncodingException
            test(ex.unknown.indexOf("UnsupportedEncodingException") > 0);
        }

        try
        {
            // Send request with bogus 2.0 encoding.
            Ice.EncodingVersion version = new Ice.EncodingVersion((byte)2, (byte)0);
            Ice.OutputStream os = Ice.Util.createOutputStream(communicator);
            os.startEncapsulation();
            os.endEncapsulation();
            byte[] inEncaps = os.finished();
            inEncaps[4] = version.major;
            inEncaps[5] = version.minor;
            Ice.ByteSeqHolder outEncaps = new Ice.ByteSeqHolder();
            cl.ice_collocationOptimized(false).ice_invoke("ice_ping", Ice.OperationMode.Normal, inEncaps, outEncaps);
            test(false);
        }
        catch(Ice.UnknownLocalException ex)
        {
            // The server thrown an UnsupportedEncodingException
            test(ex.unknown.indexOf("UnsupportedEncodingException") > 0);
        }

        out.println("ok");

        out.print("testing protocol versioning... ");
        out.flush();
        ref20 = "test -p 2.0:default -p 12010";
        cl20 = MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref20));
        try 
        {
            cl20.ice_collocationOptimized(false).ice_ping();
            test(false);
        }
        catch(Ice.UnsupportedProtocolException ex)
        {
            // Server 2.0 proxy doesn't support 1.0 version.
        }

        ref10 = "test -p 1.0:default -p 12010";
        cl10 = MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref10));
        cl10.ice_ping();

        // 1.3 isn't supported but since a 1.3 proxy supports 1.1, the
        // call will use the 1.1 protocol
        ref13 = "test -p 1.3:default -p 12010";
        cl13 = MyClassPrxHelper.uncheckedCast(communicator.stringToProxy(ref13));
        cl13.ice_ping();
        try
        {
            cl13.end_ice_ping(cl13.begin_ice_ping());
        }
        catch(Ice.CollocationOptimizationException ex)
        {
        }
        out.println("ok");
        
        out.print("testing opaque endpoints... ");
        out.flush();

        try
        {
            // Invalid -x option
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t 99 -v abc -x abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Missing -t and -v
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Repeated -t
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t 1 -t 1 -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Repeated -v
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t 1 -v abc -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Missing -t
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Missing -v
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t 1");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Missing arg for -t
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Missing arg for -v
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t 1 -v");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Not a number for -t
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t x -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // < 0 for -t
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t -1 -v abc");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        try
        {
            // Invalid char for -v
            Ice.ObjectPrx p = communicator.stringToProxy("id:opaque -t 99 -v x?c");
            test(false);
        }
        catch(Ice.EndpointParseException ex)
        {
        }

        // Legal TCP endpoint expressed as opaque endpoint
        Ice.ObjectPrx p1 = communicator.stringToProxy("test -e 1.1:opaque -e 1.0 -t 1 -v CTEyNy4wLjAuMeouAAAQJwAAAA==");
        String pstr = communicator.proxyToString(p1);
        test(pstr.equals("test -t -e 1.1:tcp -h 127.0.0.1 -p 12010 -t 10000"));

        // Opaque endpoint encoded with 1.1 encoding.
        Ice.ObjectPrx p2 = communicator.stringToProxy("test:opaque -e 1.1 -t 1 -v CTEyNy4wLjAuMeouAAAQJwAAAA==");
        test(communicator.proxyToString(p2).equals("test -t -e 1.1:tcp -h 127.0.0.1 -p 12010 -t 10000"));

        if(communicator.getProperties().getPropertyAsInt("Ice.IPv6") == 0)
        {
            // Working?
            boolean ssl = communicator.getProperties().getProperty("Ice.Default.Protocol").equals("ssl");
            if(!ssl)
            {
                p1.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();
            }

            // Two legal TCP endpoints expressed as opaque endpoints
            p1 = communicator.stringToProxy("test -e 1.0:opaque -e 1.0 -t 1 -v CTEyNy4wLjAuMeouAAAQJwAAAA==:opaque -e 1.0 -t 1 -v CTEyNy4wLjAuMusuAAAQJwAAAA==");
            pstr = communicator.proxyToString(p1);
            test(pstr.equals("test -t -e 1.0:tcp -h 127.0.0.1 -p 12010 -t 10000:tcp -h 127.0.0.2 -p 12011 -t 10000"));

            //
            // Test that an SSL endpoint and a nonsense endpoint get
            // written back out as an opaque endpoint.
            //
            p1 = communicator.stringToProxy("test -e 1.0:opaque -e 1.0 -t 2 -v CTEyNy4wLjAuMREnAAD/////AA==:opaque -t 99 -e 1.0 -v abch");
            pstr = communicator.proxyToString(p1);
            if(!ssl)
            {
                test(pstr.equals("test -t -e 1.0:opaque -t 2 -e 1.0 -v CTEyNy4wLjAuMREnAAD/////AA==:opaque -t 99 -e 1.0 -v abch"));
            }
            else
            {
                test(pstr.equals("test -t -e 1.0:ssl -h 127.0.0.1 -p 10001:opaque -t 99 -e 1.0 -v abch"));
            }

            //
            // Try to invoke on the SSL endpoint to verify that we get a
            // NoEndpointException (or ConnectFailedException when
            // running with SSL).
            //
            try
            {
                p1.ice_encodingVersion(Ice.Util.Encoding_1_0).ice_ping();
                test(false);
            }
            catch(Ice.NoEndpointException ex)
            {
                test(!ssl);
            }
            catch(Ice.ConnectFailedException ex)
            {
                test(ssl);
            }

            //
            // Test that the proxy with an SSL endpoint and a nonsense
            // endpoint (which the server doesn't understand either) can
            // be sent over the wire and returned by the server without
            // losing the opaque endpoints.
            //
            p2 = derived.echo(p1);
            pstr = communicator.proxyToString(p2);
            if(!ssl)
            {
                test(pstr.equals("test -t -e 1.0:opaque -t 2 -e 1.0 -v CTEyNy4wLjAuMREnAAD/////AA==:opaque -t 99 -e 1.0 -v abch"));
            }
            else
            {
                test(pstr.equals("test -t -e 1.0:ssl -h 127.0.0.1 -p 10001:opaque -t 99 -e 1.0 -v abch"));
            }

        }
        out.println("ok");

        return cl;
    }
}
