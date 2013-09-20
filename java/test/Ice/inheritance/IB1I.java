// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.inheritance;

import test.Ice.inheritance.Test.MA.IAPrx;
import test.Ice.inheritance.Test.MB.IB1Prx;
import test.Ice.inheritance.Test.MB._IB1Disp;

public final class IB1I extends _IB1Disp
{
    public
    IB1I()
    {
    }

    public IAPrx
    iaop(IAPrx p, Ice.Current current)
    {
        return p;
    }

    public IB1Prx
    ib1op(IB1Prx p, Ice.Current current)
    {
        return p;
    }
}
