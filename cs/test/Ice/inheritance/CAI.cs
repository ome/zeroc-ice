// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

public sealed class CAI : Test.MA.CA
{
    public CAI()
    {
    }
    
    public override Test.MA.CAPrx caop(Test.MA.CAPrx p, Ice.Current current)
    {
        return p;
    }
}
