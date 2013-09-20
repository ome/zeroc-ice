// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Glacier2.router;

public class Server extends test.Util.Application
{
    public int
    run(String[] args)
    {
        communicator().getProperties().setProperty("CallbackAdapter.Endpoints", "tcp -p 12010");
        Ice.ObjectAdapter adapter = communicator().createObjectAdapter("CallbackAdapter");
        adapter.add(new CallbackI(),
                    communicator().stringToIdentity("c1/callback")); // The test allows "c1" as category.
        adapter.add(new CallbackI(),
                    communicator().stringToIdentity("c2/callback")); // The test allows "c2" as category.
        adapter.add(new CallbackI(),
                    communicator().stringToIdentity("c3/callback")); // The test rejects "c3" as category.
        adapter.add(new CallbackI(),
                    communicator().stringToIdentity("_userid/callback")); // The test allows the prefixed userid.
        adapter.activate();
        communicator().waitForShutdown();
        return 0;
    }
    
    
    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Glacier2.router");

        return initData;
    }

    public static void
    main(String[] args)
    {
        Server c = new Server();
        int status = c.main("Server", args);
        
        System.gc();
        System.exit(status);
    }
}
