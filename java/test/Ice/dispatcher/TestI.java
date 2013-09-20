// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.dispatcher;

import test.Ice.dispatcher.Test._TestIntfDisp;

public class TestI extends _TestIntfDisp
{
    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    TestI(Dispatcher dispatcher)
    {
        _dispatcher = dispatcher;
    }

    public void
    op(Ice.Current current)
    {
        test(_dispatcher.isDispatcherThread());
    }

    public void
    opWithPayload(byte[] seq, Ice.Current current)
    {
        test(_dispatcher.isDispatcherThread());
    }

    public void
    shutdown(Ice.Current current)
    {
        current.adapter.getCommunicator().shutdown();
    }

    private Dispatcher _dispatcher;
}
