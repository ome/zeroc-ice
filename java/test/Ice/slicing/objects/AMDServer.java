// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.slicing.objects;

public class AMDServer extends test.Util.Application
{
    public int run(String[] args)
    {
        Ice.Communicator communicator = communicator();
        Ice.ObjectAdapter adapter = communicator.createObjectAdapter("TestAdapter");
        Ice.Object object = new AMDTestI();
        adapter.add(object, communicator.stringToIdentity("Test"));
        adapter.activate();
        return WAIT;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.slicing.objects.serverAMD");
        initData.properties.setProperty("Ice.Warn.Dispatch", "0");
        initData.properties.setProperty("TestAdapter.Endpoints", "default -p 12010 -t 2000");
        return initData;
    }

    public static void main(String[] args)
    {
        AMDServer app = new AMDServer();
        int result = app.main("AMDServer", args);
        System.gc();
        System.exit(result);
    }
}
