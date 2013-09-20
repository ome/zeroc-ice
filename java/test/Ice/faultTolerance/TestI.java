// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.faultTolerance;

import test.Ice.faultTolerance.Test._TestIntfDisp;

public final class TestI extends _TestIntfDisp
{
    public
    TestI(int port)
    {
        _pseudoPid = port; // We use the port number instead of the process ID in Java.
    }

    public void
    shutdown(Ice.Current current)
    {
        current.adapter.getCommunicator().shutdown();
    }

    public void
    abort(Ice.Current current)
    {
        Runtime.getRuntime().halt(0);
    }

    public void
    idempotentAbort(Ice.Current current)
    {
        Runtime.getRuntime().halt(0);
    }

    public int
    pid(Ice.Current current)
    {
        return _pseudoPid;
    }

    private int _pseudoPid;
}
