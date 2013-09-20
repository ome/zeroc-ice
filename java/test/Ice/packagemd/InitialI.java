// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.packagemd;

import test.Ice.packagemd.Test._InitialDisp;
import test.Ice.packagemd.Test1.C1;
import test.Ice.packagemd.Test1.C2;
import test.Ice.packagemd.Test1.E1;
import test.Ice.packagemd.Test1.E2;
import test.Ice.packagemd.Test1._notify;

public final class InitialI extends _InitialDisp
{
    public Ice.Object
    getTest1C2AsObject(Ice.Current __current)
    {
        return new C2();
    }

    public C1
    getTest1C2AsC1(Ice.Current __current)
    {
        return new C2();
    }

    public C2
    getTest1C2AsC2(Ice.Current __current)
    {
        return new C2();
    }

    public void
    throwTest1E2AsE1(Ice.Current __current)
        throws E1
    {
        throw new E2();
    }

    public void
    throwTest1E2AsE2(Ice.Current __current)
        throws E2
    {
        throw new E2();
    }

    public void
    throwTest1Notify(Ice.Current __current)
        throws _notify
    {
        throw new _notify();
    }

    public Ice.Object
    getTest2C2AsObject(Ice.Current __current)
    {
        return new test.Ice.packagemd.testpkg.Test2.C2();
    }

    public test.Ice.packagemd.testpkg.Test2.C1
    getTest2C2AsC1(Ice.Current __current)
    {
        return new test.Ice.packagemd.testpkg.Test2.C2();
    }

    public test.Ice.packagemd.testpkg.Test2.C2
    getTest2C2AsC2(Ice.Current __current)
    {
        return new test.Ice.packagemd.testpkg.Test2.C2();
    }

    public void
    throwTest2E2AsE1(Ice.Current __current)
        throws test.Ice.packagemd.testpkg.Test2.E1
    {
        throw new test.Ice.packagemd.testpkg.Test2.E2();
    }

    public void
    throwTest2E2AsE2(Ice.Current __current)
        throws test.Ice.packagemd.testpkg.Test2.E2
    {
        throw new test.Ice.packagemd.testpkg.Test2.E2();
    }

    public Ice.Object
    getTest3C2AsObject(Ice.Current __current)
    {
        return new test.Ice.packagemd.testpkg.Test3.C2();
    }

    public test.Ice.packagemd.testpkg.Test3.C1
    getTest3C2AsC1(Ice.Current __current)
    {
        return new test.Ice.packagemd.testpkg.Test3.C2();
    }

    public test.Ice.packagemd.testpkg.Test3.C2
    getTest3C2AsC2(Ice.Current __current)
    {
        return new test.Ice.packagemd.testpkg.Test3.C2();
    }

    public void
    throwTest3E2AsE1(Ice.Current __current)
        throws test.Ice.packagemd.testpkg.Test3.E1
    {
        throw new test.Ice.packagemd.testpkg.Test3.E2();
    }

    public void
    throwTest3E2AsE2(Ice.Current __current)
        throws test.Ice.packagemd.testpkg.Test3.E2
    {
        throw new test.Ice.packagemd.testpkg.Test3.E2();
    }

    public void
    shutdown(Ice.Current __current)
    {
        __current.adapter.getCommunicator().shutdown();
    }
}
