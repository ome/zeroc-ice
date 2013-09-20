// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.adapterDeactivation;

public class Collocated extends test.Util.Application
{
    public int
    run(String[] args)
    {
        Ice.ObjectAdapter adapter = communicator().createObjectAdapter("TestAdapter");
        Ice.ServantLocator locator = new ServantLocatorI();
        adapter.addServantLocator(locator, "");

        AllTests.allTests(communicator(), getWriter());

        adapter.waitForDeactivate();
        return 0;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.adapterDeactivation");
        initData.properties.setProperty("TestAdapter.Endpoints", "default -p 12010");
        return initData;
    }

    public static void
    main(String[] args)
    {
        Collocated app = new Collocated();
        int result = app.main("Collocated", args);
        System.exit(result);
    }
}
