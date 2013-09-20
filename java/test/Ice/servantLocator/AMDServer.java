// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.servantLocator;

public class AMDServer extends test.Util.Application
{
    public int run(String[] args)
    {

        Ice.ObjectAdapter adapter = communicator().createObjectAdapter("TestAdapter");
        adapter.addServantLocator(new AMDServantLocatorI("category"), "category");
        adapter.addServantLocator(new AMDServantLocatorI(""), "");
        adapter.add(new AMDTestI(), communicator().stringToIdentity("asm"));
        adapter.add(new AMDTestActivationI(), communicator().stringToIdentity("test/activation"));
        adapter.activate();
        return WAIT;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.servantLocator.AMD");
        initData.properties.setProperty("TestAdapter.Endpoints", "default -p 12010");
        initData.properties.setProperty("Ice.Warn.Dispatch", "0");

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
