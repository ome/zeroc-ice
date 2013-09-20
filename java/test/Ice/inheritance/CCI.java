// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.inheritance;

import test.Ice.inheritance.Test.MA.CAPrx;
import test.Ice.inheritance.Test.MA.CC;
import test.Ice.inheritance.Test.MA.CCPrx;
import test.Ice.inheritance.Test.MB.CBPrx;

public final class CCI extends CC
{
    public
    CCI()
    {
    }

    public CAPrx
    caop(CAPrx p, Ice.Current current)
    {
        return p;
    }

    public CCPrx
    ccop(CCPrx p, Ice.Current current)
    {
        return p;
    }

    public CBPrx
    cbop(CBPrx p, Ice.Current current)
    {
        return p;
    }
}
