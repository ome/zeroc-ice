// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.slicing.exceptions;

import test.Ice.slicing.exceptions.client.Test.TestIntfPrx;

public class Client extends test.Util.Application
{
    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.slicing.exceptions.client");
        return initData;
    }

    @Override
    public int run(String[] args)
    {
        TestIntfPrx test = AllTests.allTests(communicator(), false, getWriter());
        test.shutdown();
        return 0;
    }

    public static void main(String[] args)
    {
        Client c = new Client();
        int status = c.main("Client", args);

        System.gc();
        System.exit(status);
    }
}
