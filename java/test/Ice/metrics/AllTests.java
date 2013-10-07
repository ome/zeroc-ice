// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.metrics;

import java.io.PrintWriter;
import java.util.Map;

import test.Ice.metrics.Test.*;

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

    static IceMX.ConnectionMetrics
    getServerConnectionMetrics(IceMX.MetricsAdminPrx metrics, long expected)
    {
        try
        {
            IceMX.ConnectionMetrics s;
            Ice.LongHolder timestamp = new Ice.LongHolder();
            s = (IceMX.ConnectionMetrics)metrics.getMetricsView("View", timestamp).get("Connection")[0];
            int nRetry = 30;
            while(s.sentBytes != expected && nRetry-- > 0)
            {
                // On some platforms, it's necessary to wait a little before obtaining the server metrics
                // to get an accurate sentBytes metric. The sentBytes metric is updated before the response
                // to the operation is sent and getMetricsView can be dispatched before the metric is really
                // updated.
                try
                {
                    Thread.sleep(100);
                }
                catch(InterruptedException ex)
                {
                }
                s = (IceMX.ConnectionMetrics)metrics.getMetricsView("View", timestamp).get("Connection")[0];
            }
            return s;
        }
        catch(IceMX.UnknownMetricsView ex)
        {
            assert(false);
            return null;
        }
    }

    static class Callback extends Ice.Callback
    {
        public Callback()
        {
            _wait = true;
        }

        synchronized public void completed(Ice.AsyncResult result)
        {
            _wait = false;
            notify();
        }

        synchronized public void waitForResponse()
        {
            while(_wait)
            {
                try
                {
                    wait();
                }
                catch(InterruptedException ex)
                {
                }
            }
            _wait = true;
        }

        private boolean _wait;
    };

    static private Map<String, String>
    getClientProps(Ice.PropertiesAdminPrx p, Map<String, String> orig, String m) 
    {
        Map<String, String> props = p.getPropertiesForPrefix("IceMX.Metrics");
        for(Map.Entry<String, String> e : props.entrySet())
        {
            e.setValue("");
        }
        for(Map.Entry<String, String> e : orig.entrySet())
        {
            props.put(e.getKey(), e.getValue());
        }
        String map = "";
        if(!m.isEmpty())
        {
            map += "Map." + m + '.';
        }
        props.put("IceMX.Metrics.View." + map + "Reject.parent", "Ice\\.Admin");
        props.put("IceMX.Metrics.View." + map + "Accept.endpointPort", "12010");
        props.put("IceMX.Metrics.View." + map + "Reject.identity", ".*/admin|controller");
        return props;
    }

    static private Map<String, String>
    getServerProps(Ice.PropertiesAdminPrx p, Map<String, String> orig , String m)
    {
        Map<String, String> props = p.getPropertiesForPrefix("IceMX.Metrics");
        for(Map.Entry<String, String> e : props.entrySet())
        {
            e.setValue("");
        }
        for(Map.Entry<String, String> e : orig.entrySet())
        {
            props.put(e.getKey(), e.getValue());
        }
        String map = "";
        if(!m.isEmpty())
        {
            map += "Map." + m + '.';
        }
        props.put("IceMX.Metrics.View." + map + "Reject.parent", "Ice\\.Admin|Controller");
        props.put("IceMX.Metrics.View." + map + "Accept.endpointPort", "12010");
        return props;
    }

    static class UpdateCallbackI implements Ice.PropertiesAdminUpdateCallback
    {
        public UpdateCallbackI(Ice.PropertiesAdminPrx serverProps)
        {
            _updated = false;
            _serverProps = serverProps;
        }
        
        public synchronized void
        waitForUpdate()
        {
            while(!_updated)
            {
                try
                {
                    wait();
                }
                catch(InterruptedException ex)
                {
                }
            }
            // Ensure that the previous updates were committed, the setProperties call returns before 
            // notifying the callbacks so to ensure all the update callbacks have be notified we call
            // a second time, this will block until all the notifications from the first update have
            // completed.
            _serverProps.setProperties(new java.util.HashMap<String, String>()); 
            _updated = false;
        }
            
        public synchronized void
        updated(Map<String, String> dict)
        {
            _updated = true;
            notify();
        }
        
        private boolean _updated;
        private Ice.PropertiesAdminPrx _serverProps;
    };
    
    static void
    waitForCurrent(IceMX.MetricsAdminPrx metrics, String viewName, String map, int value)
        throws IceMX.UnknownMetricsView
    {
        while(true)
        {
            Ice.LongHolder timestamp = new Ice.LongHolder();
            Map<String, IceMX.Metrics[]> view = metrics.getMetricsView(viewName, timestamp);
            test(view.containsKey(map));
            boolean ok = true;
            for(IceMX.Metrics m : view.get(map))
            {
                if(m.current != value)
                {
                    ok = false;
                    break;
                }
            }
            if(ok)
            {
                break;
            }
            try
            {
                Thread.sleep(50);
            }
            catch(InterruptedException ex)
            {
            }
        }
    }
    
    static void
    testAttribute(IceMX.MetricsAdminPrx metrics, 
                  Ice.PropertiesAdminPrx props, 
                  UpdateCallbackI update,
                  String map, 
                  String attr,
                  String value,
                  Runnable func, 
                  PrintWriter out)
        throws IceMX.UnknownMetricsView
    {
        Map<String, String> dict = new java.util.HashMap<String, String>();
        dict.put("IceMX.Metrics.View.Map." + map + ".GroupBy", attr);
        if(props.ice_getIdentity().category.equals("client"))
        {
            props.setProperties(getClientProps(props, dict, map));
            update.waitForUpdate();
        }
        else
        {
            props.setProperties(getServerProps(props, dict, map));
            props.setProperties(new java.util.HashMap<String, String>());
        }
        
        func.run();
        Ice.LongHolder timestamp = new Ice.LongHolder();
        Map<String, IceMX.Metrics[]> view = metrics.getMetricsView("View", timestamp);
        if(!view.containsKey(map) || view.get(map).length == 0)
        {
            if(!value.isEmpty())
            {
                out.println("no map `" + map + "' for group by = `" + attr + "'");
                test(false);
            }
        }
        else if(!view.get(map)[0].id.equals(value))
        {
            out.println("invalid attribute value: " + attr + " = " + value + " got " + view.get(map)[0].id);
            test(false);
        }
        
        dict.clear();
        if(props.ice_getIdentity().category.equals("client"))
        {
            props.setProperties(getClientProps(props, dict, map));
            update.waitForUpdate();
        }
        else
        {
            props.setProperties(getServerProps(props, dict, map));
            props.setProperties(new java.util.HashMap<String, String>());
        }
    }
    
    static class Void implements Runnable
    {
        public void run()
        {
        }
    };
    
    static class Connect implements Runnable
    {
        public Connect(Ice.ObjectPrx proxy)
        {
            this.proxy = proxy;
        }
        
        public void run()
        {
            if(proxy.ice_getCachedConnection() != null)
            {
                proxy.ice_getCachedConnection().close(false);
            }

            try
            {
                proxy.ice_ping();
            }
            catch(Ice.LocalException ex)
            {
            }

            if(proxy.ice_getCachedConnection() != null)
            {
                proxy.ice_getCachedConnection().close(false);
            }
        }
        
        final private Ice.ObjectPrx proxy;
    };
    
    static class InvokeOp implements Runnable
    {
        public InvokeOp(MetricsPrx proxy)
        {
            this.proxy = proxy;
        }

        public void run()
        {
            Map<String, String> ctx = new java.util.HashMap<String, String>();
            ctx.put("entry1", "test");
            ctx.put("entry2", "");
            proxy.op(ctx);
        }

        final private MetricsPrx proxy;
    };

    static void
    testAttribute(IceMX.MetricsAdminPrx metrics, 
                  Ice.PropertiesAdminPrx props, 
                  UpdateCallbackI update,
                  String map, 
                  String attr,
                  String value, 
                  PrintWriter out)
        throws IceMX.UnknownMetricsView
    {
        testAttribute(metrics, props, update, map, attr, value, new Void(), out);
    }

    static void
    updateProps(Ice.PropertiesAdminPrx cprops, 
                Ice.PropertiesAdminPrx sprops, 
                UpdateCallbackI callback, 
                Map<String, String> props,
                String map)
    {
        cprops.setProperties(getClientProps(cprops, props, map));
        sprops.setProperties(getServerProps(sprops, props, map));
        callback.waitForUpdate();
    }
    
    static void
    clearView(Ice.PropertiesAdminPrx cprops, Ice.PropertiesAdminPrx sprops, UpdateCallbackI callback)
    {
        Map<String, String> dict;

        dict = cprops.getPropertiesForPrefix("IceMX.Metrics");
        dict.put("IceMX.Metrics.View.Disabled", "1");
        cprops.setProperties(dict);

        dict = sprops.getPropertiesForPrefix("IceMX.Metrics");
        dict.put("IceMX.Metrics.View.Disabled", "1");
        sprops.setProperties(dict);

        callback.waitForUpdate();

        dict = cprops.getPropertiesForPrefix("IceMX.Metrics");
        dict.put("IceMX.Metrics.View.Disabled", "");
        cprops.setProperties(dict);

        dict = sprops.getPropertiesForPrefix("IceMX.Metrics");
        dict.put("IceMX.Metrics.View.Disabled", "");
        sprops.setProperties(dict);

        callback.waitForUpdate();
    }

    static void
    checkFailure(IceMX.MetricsAdminPrx m, String map, String id, String failure, int count, PrintWriter out)
        throws IceMX.UnknownMetricsView
    {
        IceMX.MetricsFailures f = m.getMetricsFailures("View", map, id);
        if(!f.failures.containsKey(failure))
        {
            out.println("couldn't find failure `" + failure + "' for `" + id + "'");
            test(false);
        }
        if(count > 0 && f.failures.get(failure) != count)
        {
            out.print("count for failure `" + failure + "' of `" + id + "' is different from expected: ");
            out.println(count + " != " + f.failures.get(failure));
            test(false);
        }
    }

    static Map<String, IceMX.Metrics>
    toMap(IceMX.Metrics[] mmap)
    {
        Map<String, IceMX.Metrics> m = new java.util.HashMap<String, IceMX.Metrics>();
        for(IceMX.Metrics e : mmap)
        {
            m.put(e.id, e);
        }
        return m;
    }

    static MetricsPrx 
    allTests(Ice.Communicator communicator, PrintWriter out, CommunicatorObserverI obsv)
        throws IceMX.UnknownMetricsView
    {
        MetricsPrx metrics = MetricsPrxHelper.checkedCast(communicator.stringToProxy("metrics:default -p 12010"));
            
        out.print("testing metrics admin facet checkedCast... ");
        out.flush();
        Ice.ObjectPrx admin = communicator.getAdmin().ice_collocationOptimized(false);
        Ice.PropertiesAdminPrx clientProps = Ice.PropertiesAdminPrxHelper.checkedCast(admin, "Properties");
        IceMX.MetricsAdminPrx clientMetrics = IceMX.MetricsAdminPrxHelper.checkedCast(admin, "Metrics");
        test(clientProps != null && clientMetrics != null);

        admin = metrics.getAdmin();
        Ice.PropertiesAdminPrx serverProps = Ice.PropertiesAdminPrxHelper.checkedCast(admin, "Properties");
        IceMX.MetricsAdminPrx serverMetrics = IceMX.MetricsAdminPrxHelper.checkedCast(admin, "Metrics");
        test(serverProps != null && serverMetrics != null);

        UpdateCallbackI update = new UpdateCallbackI(serverProps);
        ((Ice.NativePropertiesAdmin)communicator.findAdminFacet("Properties")).addUpdateCallback(update);

        out.println("ok");

        Map<String, String> props = new java.util.HashMap<String, String>();

        out.print("testing group by none...");
        out.flush();

        props.put("IceMX.Metrics.View.GroupBy", "none");
        updateProps(clientProps, serverProps, update, props, "");
        Ice.LongHolder timestamp = new Ice.LongHolder();
        Map<String, IceMX.Metrics[]> view = clientMetrics.getMetricsView("View", timestamp);
        test(view.get("Connection").length == 1 && view.get("Connection")[0].current == 1 && 
             view.get("Connection")[0].total == 1);
        test(view.get("Thread").length == 1 && view.get("Thread")[0].current == 3 && view.get("Thread")[0].total == 3);
        out.println("ok");

        out.print("testing group by id...");
        out.flush();

        props.put("IceMX.Metrics.View.GroupBy", "id");
        updateProps(clientProps, serverProps, update, props, "");

        metrics.ice_ping();
        metrics.ice_ping();
        metrics.ice_connectionId("Con1").ice_ping();
        metrics.ice_connectionId("Con1").ice_ping();
        metrics.ice_connectionId("Con1").ice_ping();

        view = clientMetrics.getMetricsView("View", timestamp);
        test(view.get("Thread").length == 3);
        test(view.get("Connection").length == 2);
        test(view.get("Invocation").length == 1);

        IceMX.InvocationMetrics invoke = (IceMX.InvocationMetrics)view.get("Invocation")[0];
        test(invoke.id.indexOf("[ice_ping]") > 0 && invoke.current == 0 && invoke.total == 5);
        test(invoke.remotes.length == 2);
        test(invoke.remotes[0].total >= 2 && invoke.remotes[1].total >= 2);
        test((invoke.remotes[0].total + invoke.remotes[1].total) == 5);

        view = serverMetrics.getMetricsView("View", timestamp);
        test(view.get("Thread").length > 3);
        test(view.get("Connection").length == 2);
        test(view.get("Dispatch").length == 1);
        test(view.get("Dispatch")[0].current <= 1 && view.get("Dispatch")[0].total == 5);
        test(view.get("Dispatch")[0].id.indexOf("[ice_ping]") > 0);

        metrics.ice_getConnection().close(false);
        metrics.ice_connectionId("Con1").ice_getConnection().close(false);

        waitForCurrent(clientMetrics, "View", "Connection", 0);
        waitForCurrent(serverMetrics, "View", "Connection", 0);

        clearView(clientProps, serverProps, update);
    
        out.println("ok");

        out.print("testing connection metrics... ");
        out.flush();

        props.put("IceMX.Metrics.View.Map.Connection.GroupBy", "none");
        updateProps(clientProps, serverProps, update, props, "Connection");

        test(clientMetrics.getMetricsView("View", timestamp).get("Connection").length == 0);
        test(serverMetrics.getMetricsView("View", timestamp).get("Connection").length == 0);

        metrics.ice_ping();

        IceMX.ConnectionMetrics cm1, sm1, cm2, sm2;
        cm1 = (IceMX.ConnectionMetrics)clientMetrics.getMetricsView("View", timestamp).get("Connection")[0];
        sm1 = getServerConnectionMetrics(serverMetrics, 25);
        test(cm1.total == 1 && sm1.total == 1);

        metrics.ice_ping();

        cm2 = (IceMX.ConnectionMetrics)clientMetrics.getMetricsView("View", timestamp).get("Connection")[0];
        sm2 = getServerConnectionMetrics(serverMetrics, 50);

        test(cm2.sentBytes - cm1.sentBytes == 45); // 45 for ice_ping request
        test(cm2.receivedBytes - cm1.receivedBytes == 25); // 25 bytes for ice_ping response
        test(sm2.receivedBytes - sm1.receivedBytes == 45);
        test(sm2.sentBytes - sm1.sentBytes == 25);

        cm1 = cm2;
        sm1 = sm2;

        byte[] bs = new byte[0];
        metrics.opByteS(bs);

        cm2 = (IceMX.ConnectionMetrics)clientMetrics.getMetricsView("View", timestamp).get("Connection")[0];
        sm2 = getServerConnectionMetrics(serverMetrics, sm1.sentBytes + cm2.receivedBytes - cm1.receivedBytes);
        long requestSz = cm2.sentBytes - cm1.sentBytes;
        long replySz = cm2.receivedBytes - cm1.receivedBytes;

        cm1 = cm2;
        sm1 = sm2;

        bs = new byte[456];
        metrics.opByteS(bs);

        cm2 = (IceMX.ConnectionMetrics)clientMetrics.getMetricsView("View", timestamp).get("Connection")[0];
        sm2 = getServerConnectionMetrics(serverMetrics, sm1.sentBytes + replySz);

        test(cm2.sentBytes - cm1.sentBytes == requestSz + bs.length + 4); // 4 is for the seq variable size
        test(cm2.receivedBytes - cm1.receivedBytes == replySz);
        test(sm2.receivedBytes - sm1.receivedBytes == requestSz + bs.length + 4);
        test(sm2.sentBytes - sm1.sentBytes == replySz);

        cm1 = cm2;
        sm1 = sm2;

        bs = new byte[1024 * 1024 * 10]; // Try with large amount of data which should be sent in several chunks
        metrics.opByteS(bs);

        cm2 = (IceMX.ConnectionMetrics)clientMetrics.getMetricsView("View", timestamp).get("Connection")[0];
        sm2 = getServerConnectionMetrics(serverMetrics, sm1.sentBytes + replySz);

        test((cm2.sentBytes - cm1.sentBytes) == (requestSz + bs.length + 4)); // 4 is for the seq variable size
        test((cm2.receivedBytes - cm1.receivedBytes) == replySz);
        test((sm2.receivedBytes - sm1.receivedBytes) == (requestSz + bs.length + 4));
        test((sm2.sentBytes - sm1.sentBytes) == replySz);
    
        props.put("IceMX.Metrics.View.Map.Connection.GroupBy", "state");
        updateProps(clientProps, serverProps, update, props, "Connection");

        Map<String, IceMX.Metrics> map = toMap(serverMetrics.getMetricsView("View", timestamp).get("Connection"));

        test(map.get("active").current == 1);

        ControllerPrx controller = ControllerPrxHelper.checkedCast(
            communicator.stringToProxy("controller:default -p 12011"));
        controller.hold();

        map = toMap(clientMetrics.getMetricsView("View", timestamp).get("Connection"));
        test(map.get("active").current == 1);
        map = toMap(serverMetrics.getMetricsView("View", timestamp).get("Connection"));
        test(map.get("holding").current == 1);

        metrics.ice_getConnection().close(false);

        map = toMap(clientMetrics.getMetricsView("View", timestamp).get("Connection"));
        test(map.get("closing").current == 1);
        map = toMap(serverMetrics.getMetricsView("View", timestamp).get("Connection"));
        test(map.get("holding").current == 1);

        controller.resume();

        map = toMap(serverMetrics.getMetricsView("View", timestamp).get("Connection"));
        test(map.get("holding").current == 0);

        props.put("IceMX.Metrics.View.Map.Connection.GroupBy", "none");
        updateProps(clientProps, serverProps, update, props, "Connection");

        metrics.ice_getConnection().close(false);

        metrics.ice_timeout(500).ice_ping();
        controller.hold();
        try
        {
            metrics.ice_timeout(500).ice_ping();
            test(false);
        }
        catch(Ice.TimeoutException ex)
        {
        }
        controller.resume();

        cm1 = (IceMX.ConnectionMetrics)clientMetrics.getMetricsView("View", timestamp).get("Connection")[0];
        while(true)
        {
            sm1 = (IceMX.ConnectionMetrics)serverMetrics.getMetricsView("View", timestamp).get("Connection")[0];
            if(sm1. failures >= 2)
            {
                break;
            }
            try
            {
                Thread.sleep(10);
            }
            catch(InterruptedException ex)
            {
            }
        }

        test(cm1.failures == 2 && sm1.failures >= 1);

        checkFailure(clientMetrics, "Connection", cm1.id, "Ice::TimeoutException", 1, out);
        checkFailure(clientMetrics, "Connection", cm1.id, "Ice::ConnectTimeoutException", 1, out);
        checkFailure(serverMetrics, "Connection", sm1.id, "Ice::ConnectionLostException", 0, out);

        MetricsPrx m = (MetricsPrx)metrics.ice_timeout(500).ice_connectionId("Con1");
        m.ice_ping();

        testAttribute(clientMetrics, clientProps, update, "Connection", "parent", "Communicator", out);
        //testAttribute(clientMetrics, clientProps, update, "Connection", "id", "");
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpoint",
                      "tcp -h 127.0.0.1 -p 12010 -t 500", out);

        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointType", "1", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointIsDatagram", "false", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointIsSecure", "false", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointTimeout", "500", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointCompress", "false", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointHost", "127.0.0.1", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "endpointPort", "12010", out);

        testAttribute(clientMetrics, clientProps, update, "Connection", "incoming", "false", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "adapterName", "", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "connectionId", "Con1", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "localHost", "127.0.0.1", out);
        //testAttribute(clientMetrics, clientProps, update, "Connection", "localPort", "", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "remoteHost", "127.0.0.1", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "remotePort", "12010", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "mcastHost", "", out);
        testAttribute(clientMetrics, clientProps, update, "Connection", "mcastPort", "", out);
    
        m.ice_getConnection().close(false);

        waitForCurrent(clientMetrics, "View", "Connection", 0);
        waitForCurrent(serverMetrics, "View", "Connection", 0);

        out.println("ok");

        out.print("testing connection establishment metrics... ");
        out.flush();

        props.put("IceMX.Metrics.View.Map.ConnectionEstablishment.GroupBy", "id");
        updateProps(clientProps, serverProps, update, props, "ConnectionEstablishment");
        test(clientMetrics.getMetricsView("View", timestamp).get("ConnectionEstablishment").length == 0);

        metrics.ice_ping();
    
        test(clientMetrics.getMetricsView("View", timestamp).get("ConnectionEstablishment").length == 1);
        IceMX.Metrics m1 = clientMetrics.getMetricsView("View", timestamp).get("ConnectionEstablishment")[0];
        test(m1.current == 0 && m1.total == 1 && m1.id.equals("127.0.0.1:12010"));

        metrics.ice_getConnection().close(false);
        controller.hold();
        try
        {
            communicator.stringToProxy("test:tcp -p 12010 -h 127.0.0.1").ice_timeout(10).ice_ping();
            test(false);
        }
        catch(Ice.ConnectTimeoutException ex)
        {
        }
        catch(Ice.LocalException ex)
        {
            test(false);
        }
        controller.resume();
        test(clientMetrics.getMetricsView("View", timestamp).get("ConnectionEstablishment").length == 1);
        m1 = clientMetrics.getMetricsView("View", timestamp).get("ConnectionEstablishment")[0];
        test(m1.id.equals("127.0.0.1:12010") && m1.total == 3 && m1.failures == 2);

        checkFailure(clientMetrics, "ConnectionEstablishment", m1.id, "Ice::ConnectTimeoutException", 2, out);

        Connect c = new Connect(metrics);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "parent", "Communicator", c, out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "id", "127.0.0.1:12010", c, out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpoint",
                      "tcp -h 127.0.0.1 -p 12010", c, out);

        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointType", "1", c, out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointIsDatagram", "false", c, 
                      out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointIsSecure", "false", c, 
                      out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointTimeout", "-1", c, out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointCompress", "false", c, 
                      out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointHost", "127.0.0.1", c, 
                      out);
        testAttribute(clientMetrics, clientProps, update, "ConnectionEstablishment", "endpointPort", "12010", c, 
                      out);

        out.println("ok");

        out.print("testing endpoint lookup metrics... ");
        out.flush();

        props.put("IceMX.Metrics.View.Map.ConnectionEstablishment.GroupBy", "id");
        updateProps(clientProps, serverProps, update, props, "EndpointLookup");
        test(clientMetrics.getMetricsView("View", timestamp).get("EndpointLookup").length == 0);

        Ice.ObjectPrx prx = communicator.stringToProxy("metrics:default -p 12010 -h localhost");
        prx.ice_ping();
    
        test(clientMetrics.getMetricsView("View", timestamp).get("EndpointLookup").length == 1);
        m1 = clientMetrics.getMetricsView("View", timestamp).get("EndpointLookup")[0];
        test(m1.current <= 1 && m1.total == 1 && m1.id.equals("tcp -h localhost -p 12010"));

        prx.ice_getConnection().close(false);

        boolean dnsException = false;
        try
        {
            communicator.stringToProxy("test:tcp -t 500 -p 12010 -h unknownfoo.zeroc.com").ice_ping();
            test(false);
        }
        catch(Ice.DNSException ex)
        {
            dnsException = true;
        }
        catch(Ice.LocalException ex)
        {
            // Some DNS servers don't fail on unknown DNS names.
        }
        test(clientMetrics.getMetricsView("View", timestamp).get("EndpointLookup").length == 2);
        m1 = clientMetrics.getMetricsView("View", timestamp).get("EndpointLookup")[0];
        if(!m1.id.equals("tcp -h unknownfoo.zeroc.com -p 12010 -t 500"))
        {
            m1 = clientMetrics.getMetricsView("View", timestamp).get("EndpointLookup")[1];
        }
        test(m1.id.equals("tcp -h unknownfoo.zeroc.com -p 12010 -t 500") && m1.total == 2 && 
             (!dnsException || m1.failures == 2));
        if(dnsException)
        {
            checkFailure(clientMetrics, "EndpointLookup", m1.id, "Ice::DNSException", 2, out);
        }

        c = new Connect(prx);

        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "parent", "Communicator", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "id", "tcp -h localhost -p 12010", c,
                      out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpoint", 
                      "tcp -h localhost -p 12010", c, out);

        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointType", "1", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointIsDatagram", "false", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointIsSecure", "false", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointTimeout", "-1", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointCompress", "false", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointHost", "localhost", c, out);
        testAttribute(clientMetrics, clientProps, update, "EndpointLookup", "endpointPort", "12010", c, out);

        out.println("ok");

        out.print("testing dispatch metrics... ");
        out.flush();

        props.put("IceMX.Metrics.View.Map.Dispatch.GroupBy", "operation");
        updateProps(clientProps, serverProps, update, props, "Dispatch");
        test(serverMetrics.getMetricsView("View", timestamp).get("Dispatch").length == 0);

        metrics.op();
        try
        {
            metrics.opWithUserException();
            test(false);
        }
        catch(UserEx ex)
        {
        }
        try
        {
            metrics.opWithRequestFailedException();
            test(false);
        }
        catch(Ice.RequestFailedException ex)
        {
        }
        try
        {
            metrics.opWithLocalException();
            test(false);
        }
        catch(Ice.LocalException ex)
        {
        }
        try
        {
            metrics.opWithUnknownException();
            test(false);
        }
        catch(Ice.UnknownException ex)
        {
        }
        try
        {
            metrics.fail();
            test(false);
        }
        catch(Ice.ConnectionLostException ex)
        {
        }

        map = toMap(serverMetrics.getMetricsView("View", timestamp).get("Dispatch"));
        test(map.size() == 6);

        IceMX.DispatchMetrics dm1 = (IceMX.DispatchMetrics)map.get("op");
        test(dm1.current <= 1 && dm1.total == 1 && dm1.failures == 0 && dm1.userException == 0);
        test(dm1.size == 21 && dm1.replySize == 7);

        dm1 = (IceMX.DispatchMetrics)map.get("opWithUserException");
        test(dm1.current <= 1 &dm1.total == 1 && dm1.failures == 0 && dm1.userException == 1);
        test(dm1.size == 38 && dm1.replySize == 23);
        
        dm1 = (IceMX.DispatchMetrics)map.get("opWithLocalException");
        test(dm1.current <= 1 && dm1.total == 1 && dm1.failures == 1 && dm1.userException == 0);
        checkFailure(serverMetrics, "Dispatch", dm1.id, "Ice::SyscallException", 1, out);
        test(dm1.size == 39 && dm1.replySize > 7); // Reply contains the exception stack depending on the OS.

        dm1 = (IceMX.DispatchMetrics)map.get("opWithRequestFailedException");
        test(dm1.current <= 1 && dm1.total == 1 && dm1.failures == 1 && dm1.userException == 0);
        checkFailure(serverMetrics, "Dispatch", dm1.id, "Ice::ObjectNotExistException", 1, out);
        test(dm1.size == 47 && dm1.replySize == 40);

        dm1 = (IceMX.DispatchMetrics)map.get("opWithUnknownException");
        test(dm1.current <= 1 && dm1.total == 1 && dm1.failures == 1 && dm1.userException == 0);
        checkFailure(serverMetrics, "Dispatch", dm1.id, "java.lang.IllegalArgumentException", 1, out);
        test(dm1.size == 41 && dm1.replySize > 7); // Reply contains the exception stack depending on the OS.

        InvokeOp op = new InvokeOp(metrics);

        testAttribute(serverMetrics, serverProps, update, "Dispatch", "parent", "TestAdapter", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "id", "metrics [op]", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpoint", 
                      "tcp -h 127.0.0.1 -p 12010", op, out);
        //testAttribute(serverMetrics, serverProps, update, "Dispatch", "connection", "", op);

        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointType", "1", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointIsDatagram", "false", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointIsSecure", "false", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointTimeout", "-1", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointCompress", "false", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointHost", "127.0.0.1", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "endpointPort", "12010", op, out);

        testAttribute(serverMetrics, serverProps, update, "Dispatch", "incoming", "true", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "adapterName", "TestAdapter", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "connectionId", "", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "localHost", "127.0.0.1", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "localPort", "12010", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "remoteHost", "127.0.0.1", op, out);
        //testAttribute(serverMetrics, serverProps, update, "Dispatch", "remotePort", "12010", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "mcastHost", "", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "mcastPort", "", op, out);

        testAttribute(serverMetrics, serverProps, update, "Dispatch", "operation", "op", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "identity", "metrics", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "facet", "", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "mode", "twoway", op, out);

        testAttribute(serverMetrics, serverProps, update, "Dispatch", "context.entry1", "test", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "context.entry2", "", op, out);
        testAttribute(serverMetrics, serverProps, update, "Dispatch", "context.entry3", "", op, out);

        out.println("ok");

        out.print("testing invocation metrics... ");
        out.flush();

        props.put("IceMX.Metrics.View.Map.Invocation.GroupBy", "operation");
        props.put("IceMX.Metrics.View.Map.Invocation.Map.Remote.GroupBy", "localPort");
        updateProps(clientProps, serverProps, update, props, "Invocation");
        test(serverMetrics.getMetricsView("View", timestamp).get("Invocation").length == 0);

        Callback cb = new Callback();

        metrics.op();
        metrics.end_op(metrics.begin_op());
        metrics.begin_op(cb);
        cb.waitForResponse();

        try
        {
            metrics.opWithUserException();
            test(false);
        }
        catch(UserEx ex)
        {
        }
        try
        {
            metrics.end_opWithUserException(metrics.begin_opWithUserException());
            test(false);
        }
        catch(UserEx ex)
        {
        }
        metrics.begin_opWithUserException(cb);
        cb.waitForResponse();

        try
        {
            metrics.opWithRequestFailedException();
            test(false);
        }
        catch(Ice.RequestFailedException ex)
        {
        }
        try
        {
            metrics.end_opWithRequestFailedException(metrics.begin_opWithRequestFailedException());
            test(false);
        }
        catch(Ice.RequestFailedException ex)
        {
        }
        metrics.begin_opWithRequestFailedException(cb);
        cb.waitForResponse();

        try
        {
            metrics.opWithLocalException();
            test(false);
        }
        catch(Ice.LocalException ex)
        {
        }
        try
        {
            metrics.end_opWithLocalException(metrics.begin_opWithLocalException());
            test(false);
        }
        catch(Ice.LocalException ex)
        {
        }
        metrics.begin_opWithLocalException(cb);
        cb.waitForResponse();

        try
        {
            metrics.opWithUnknownException();
            test(false);
        }
        catch(Ice.UnknownException ex)
        {
        }
        try
        {
            metrics.end_opWithUnknownException(metrics.begin_opWithUnknownException());
            test(false);
        }
        catch(Ice.UnknownException ex)
        {
        }
        metrics.begin_opWithUnknownException(cb);
        cb.waitForResponse();

        try
        {
            metrics.fail();
            test(false);
        }
        catch(Ice.ConnectionLostException ex)
        {
        }
        try
        {
            metrics.end_fail(metrics.begin_fail());
            test(false);
        }
        catch(Ice.ConnectionLostException ex)
        {
        }
        metrics.begin_fail(cb);
        cb.waitForResponse();

        map = toMap(clientMetrics.getMetricsView("View", timestamp).get("Invocation"));
        test(map.size() == 6);

        IceMX.InvocationMetrics im1;
        IceMX.RemoteMetrics rim1;
        im1 = (IceMX.InvocationMetrics)map.get("op");
        test(im1.current <= 1 && im1.total == 3 && im1.failures == 0 && im1.retry == 0 && im1.remotes.length == 1);
        rim1 = (IceMX.RemoteMetrics)im1.remotes[0];
        test(rim1.current == 0 && rim1.total == 3 && rim1.failures == 0);
        test(rim1.size == 63 && rim1.replySize == 21);

        im1 = (IceMX.InvocationMetrics)map.get("opWithUserException");
        test(im1.current == 0 && im1.total == 3 && im1.failures == 0 && im1.retry == 0 && im1.remotes.length == 1);
        rim1 = (IceMX.RemoteMetrics)im1.remotes[0];
        test(rim1.current == 0 && rim1.total == 3 && rim1.failures == 0);
        test(rim1.size == 114 && rim1.replySize == 69);
        test(im1.userException == 3);

        im1 = (IceMX.InvocationMetrics)map.get("opWithLocalException");
        test(im1.current <= 1 && im1.total == 3 && im1.failures == 3 && im1.retry == 0 && im1.remotes.length == 1);
        rim1 = (IceMX.RemoteMetrics)im1.remotes[0];
        test(rim1.current == 0 && rim1.total == 3 && rim1.failures == 0);
        test(rim1.size == 117 && rim1.replySize > 7);
        checkFailure(clientMetrics, "Invocation", im1.id, "Ice::UnknownLocalException", 3, out);

        im1 = (IceMX.InvocationMetrics)map.get("opWithRequestFailedException");
        test(im1.current <= 1 && im1.total == 3 && im1.failures == 3 && im1.retry == 0 && im1.remotes.length == 1);
        rim1 = (IceMX.RemoteMetrics)im1.remotes[0];
        test(rim1.current == 0 && rim1.total == 3 && rim1.failures == 0);
        test(rim1.size == 141 && rim1.replySize == 120);
        checkFailure(clientMetrics, "Invocation", im1.id, "Ice::ObjectNotExistException", 3, out);

        im1 = (IceMX.InvocationMetrics)map.get("opWithUnknownException");
        test(im1.current <= 1 && im1.total == 3 && im1.failures == 3 && im1.retry == 0 && im1.remotes.length == 1);
        rim1 = (IceMX.RemoteMetrics)im1.remotes[0];
        test(rim1.current == 0 && rim1.total == 3 && rim1.failures == 0);
        test(rim1.size == 123 && rim1.replySize > 7);
        checkFailure(clientMetrics, "Invocation", im1.id, "Ice::UnknownException", 3, out);

        im1 = (IceMX.InvocationMetrics)map.get("fail");
        test(im1.current <= 1 && im1.total == 3 && im1.failures == 3 && im1.retry == 3 && im1.remotes.length == 6);
        test(im1.remotes[0].current == 0 && im1.remotes[0].total == 1 && im1.remotes[0].failures == 1);
        test(im1.remotes[1].current == 0 && im1.remotes[1].total == 1 && im1.remotes[1].failures == 1);
        test(im1.remotes[2].current == 0 && im1.remotes[2].total == 1 && im1.remotes[2].failures == 1);
        test(im1.remotes[3].current == 0 && im1.remotes[3].total == 1 && im1.remotes[3].failures == 1);
        test(im1.remotes[4].current == 0 && im1.remotes[4].total == 1 && im1.remotes[4].failures == 1);
        test(im1.remotes[5].current == 0 && im1.remotes[5].total == 1 && im1.remotes[5].failures == 1);
        checkFailure(clientMetrics, "Invocation", im1.id, "Ice::ConnectionLostException", 3, out);

        testAttribute(clientMetrics, clientProps, update, "Invocation", "parent", "Communicator", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "id", "metrics -t -e 1.1 [op]", op, out);

        testAttribute(clientMetrics, clientProps, update, "Invocation", "operation", "op", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "identity", "metrics", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "facet", "", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "encoding", "1.1", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "mode", "twoway", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "proxy",
                      "metrics -t -e 1.1:tcp -h 127.0.0.1 -p 12010", op, out);

        testAttribute(clientMetrics, clientProps, update, "Invocation", "context.entry1", "test", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "context.entry2", "", op, out);
        testAttribute(clientMetrics, clientProps, update, "Invocation", "context.entry3", "", op, out);

        out.println("ok");
        
        out.print("testing metrics view enable/disable...");
        out.flush();

        Ice.StringSeqHolder disabledViews = new Ice.StringSeqHolder();
        props.put("IceMX.Metrics.View.GroupBy", "none");
        props.put("IceMX.Metrics.View.Disabled", "0");
        updateProps(clientProps, serverProps, update, props, "Thread");
        test(clientMetrics.getMetricsView("View", timestamp).get("Thread").length != 0);
        test(clientMetrics.getMetricsViewNames(disabledViews).length == 1 && disabledViews.value.length == 0);

        props.put("IceMX.Metrics.View.Disabled", "1");
        updateProps(clientProps, serverProps, update, props, "Thread");
        test(clientMetrics.getMetricsView("View", timestamp).get("Thread") == null);
        test(clientMetrics.getMetricsViewNames(disabledViews).length == 0 && disabledViews.value.length == 1);

        clientMetrics.enableMetricsView("View");
        test(clientMetrics.getMetricsView("View", timestamp).get("Thread").length != 0);
        test(clientMetrics.getMetricsViewNames(disabledViews).length == 1 && disabledViews.value.length == 0);

        clientMetrics.disableMetricsView("View");
        test(clientMetrics.getMetricsView("View", timestamp).get("Thread") == null);
        test(clientMetrics.getMetricsViewNames(disabledViews).length == 0 && disabledViews.value.length == 1);

        try
        {
            clientMetrics.enableMetricsView("UnknownView");
        }
        catch(IceMX.UnknownMetricsView ex)
        {
        }

        out.println("ok");

        out.print("testing instrumentation observer delegate... ");
        out.flush();

        test(obsv.threadObserver.getTotal() > 0);
        test(obsv.connectionObserver.getTotal() > 0);
        test(obsv.connectionEstablishmentObserver.getTotal() > 0);
        test(obsv.endpointLookupObserver.getTotal() > 0);
        test(obsv.dispatchObserver.getTotal() > 0);
        test(obsv.invocationObserver.getTotal() > 0);
        test(obsv.invocationObserver.remoteObserver.getTotal() > 0);

        test(obsv.threadObserver.getCurrent() > 0);
        test(obsv.connectionObserver.getCurrent() > 0);
        test(obsv.connectionEstablishmentObserver.getCurrent() == 0);
        test(obsv.endpointLookupObserver.getCurrent() == 0);
        test(obsv.dispatchObserver.getCurrent() == 0);
        test(obsv.invocationObserver.getCurrent() == 0);
        test(obsv.invocationObserver.remoteObserver.getCurrent() == 0);

        test(obsv.threadObserver.getFailedCount() == 0);
        test(obsv.connectionObserver.getFailedCount() > 0);
        test(obsv.connectionEstablishmentObserver.getFailedCount() > 0);
        test(obsv.endpointLookupObserver.getFailedCount() > 0);
        //test(obsv.dispatchObserver.getFailedCount() > 0);
        test(obsv.invocationObserver.getFailedCount() > 0);
        test(obsv.invocationObserver.remoteObserver.getFailedCount() > 0);

        test(obsv.threadObserver.states > 0);
        test(obsv.connectionObserver.received > 0 && obsv.connectionObserver.sent > 0);
        //test(obsv.dispatchObserver.userExceptionCount > 0);
        test(obsv.invocationObserver.userExceptionCount > 0 && obsv.invocationObserver.retriedCount > 0);
        test(obsv.invocationObserver.remoteObserver.replySize > 0);

        out.println("ok");

        return metrics;
    }
}
