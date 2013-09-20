// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.facets;

import test.Ice.facets.Test._EDisp;

public final class EI extends _EDisp
{
    public
    EI()
    {
    }

    public String
    callE(Ice.Current current)
    {
        return "E";
    }
}
