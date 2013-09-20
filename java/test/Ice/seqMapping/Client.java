// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.seqMapping;

import test.Ice.seqMapping.Test.*;

public class Client extends test.Util.Application
{
    public int
    run(String[] args)
    {
        java.io.PrintWriter out = getWriter();

        MyClassPrx myClass = AllTests.allTests(communicator(), false, out);

        out.print("shutting down server... ");
        out.flush();
        myClass.shutdown();
        out.println("ok");

        return 0;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.seqMapping");
        return initData;
    }

    public static void main(String[] args)
    {
        Client c = new Client();
        int status = c.main("Client", args);

        System.gc();
        System.exit(status);
    }
}
