// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.threadPoolPriority;

public class Server extends test.Util.Application
{
    public int run(String[] args)
    {
        communicator().getProperties().setProperty("TestAdapter.Endpoints", "default -p 12010 -t 10000:udp");
        Ice.ObjectAdapter adapter = communicator().createObjectAdapter("TestAdapter");
        adapter.add(new PriorityI(), communicator().stringToIdentity("test"));
        adapter.activate();

        communicator().waitForShutdown();
        return 0;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.ThreadPool.Server.ThreadPriority", "10");
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
