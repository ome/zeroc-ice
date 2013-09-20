// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

using Demo;

public sealed class CallbackReceiverI : CallbackReceiverDisp_
{
    public override void callback(int num, Ice.Current current)
    {
         System.Console.Out.WriteLine("received callback #" + num);
    }
}
