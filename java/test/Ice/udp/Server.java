// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.udp;

public class Server extends test.Util.Application
{
    public int run(String[] args)
    {
        Ice.Properties properties = communicator().getProperties();

        int port = 12010;
        try
        {
            port += args.length == 1 ? Integer.parseInt(args[0]) : 0;
        }
        catch(NumberFormatException ex)
        {
        }
        properties.setProperty("ControlAdapter.Endpoints", "tcp -p " + port);
        Ice.ObjectAdapter adapter = communicator().createObjectAdapter("ControlAdapter");
        adapter.add(new TestIntfI(), communicator().stringToIdentity("control"));
        adapter.activate();

        if(port == 12010)
        {
            properties.setProperty("TestAdapter.Endpoints", "udp -p 12010");
            Ice.ObjectAdapter adapter2 = communicator().createObjectAdapter("TestAdapter");
            adapter2.add(new TestIntfI(), communicator().stringToIdentity("test"));
            adapter2.activate();
        }

        Ice.ObjectAdapter mcastAdapter = communicator().createObjectAdapter("McastTestAdapter");
        mcastAdapter.add(new TestIntfI(), communicator().stringToIdentity("test"));
        mcastAdapter.activate();

        return WAIT;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.udp");
        initData.properties.setProperty("Ice.Warn.Connections", "0");
        initData.properties.setProperty("Ice.UDP.RcvSize", "16384");
        initData.properties.setProperty("Ice.UDP.SndSize", "16384");

        String endpoint;
        if(initData.properties.getProperty("Ice.IPv6").equals("1"))
        {
            if(System.getProperty("os.name").contains("OS X"))
            {
                endpoint = "udp -h \"ff02::1:1\" -p 12020 --interface \"lo0\"";
            }
            else
            {
                endpoint = "udp -h \"ff01::1:1\" -p 12020";
            }
        }
        else
        {
            endpoint = "udp -h 239.255.1.1 -p 12020";
        }
        initData.properties.setProperty("McastTestAdapter.Endpoints", endpoint);
        return initData;
    }

    public static void main(String[] args)
    {
        Server c = new Server();
        int status = c.main("Server", args);

        System.gc();
        System.exit(status);
    }
}
