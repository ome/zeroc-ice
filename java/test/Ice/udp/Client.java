// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.udp;

import test.Ice.udp.Test.*;

public class Client extends test.Util.Application
{
    public int run(String[] args)
    {
        AllTests.allTests(communicator());

        int num;
        try 
        {
            num = args.length == 1 ? Integer.parseInt(args[0]) : 0;
        }
        catch(NumberFormatException ex)
        {
            num = 0;
        }
        for(int i = 0; i < num; ++i)
        {
            TestIntfPrxHelper.uncheckedCast(communicator().stringToProxy("control:tcp -p " + (12010 + i))).shutdown();
        }
        return 0;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.udp");
        initData.properties.setProperty("Ice.Warn.Connections", "0");
        initData.properties.setProperty("Ice.UDP.RcvSize", "16384");
        initData.properties.setProperty("Ice.UDP.SndSize", "16384");
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
