// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.dispatcher;

public class Client extends test.Util.Application
{
    public int run(String[] args)
    {
        AllTests.allTests(communicator(), getWriter(), _dispatcher);
        return 0;
    }

    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        assert(_dispatcher == null);
        _dispatcher = new Dispatcher();
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.dispatcher");
        initData.dispatcher = _dispatcher;
        return initData;
    }

    Dispatcher getDispatcher()
    {
        return _dispatcher;
    }

    public static void main(String[] args)
    {
        Client app = new Client();
        int result = app.main("Client", args);
        app.getDispatcher().terminate();
        System.gc();
        System.exit(result);
    }

    //
    // The Dispatcher class uses a static "_instance" member in other language
    // mappings. In Java, we avoid the use of static members because we need to
    // maintain support for Android (in which the client and server run in the
    // same process).
    //
    private Dispatcher _dispatcher;
}
