// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.seqMapping;

public class AMDServer extends test.Util.Application
{
    public int
    run(String[] args)
    {
        Ice.ObjectAdapter adapter = communicator().createObjectAdapter("TestAdapter");
        adapter.add(new AMDMyClassI(), communicator().stringToIdentity("test"));
        adapter.activate();

        return WAIT;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.seqMapping.AMD");
        initData.properties.setProperty("TestAdapter.Endpoints", "default -p 12010:udp");
        return initData;
    }

    public static void main(String[] args)
    {
        AMDServer c = new AMDServer();
        int status = c.main("AMDServer", args);

        System.gc();
        System.exit(status);
    }
}
