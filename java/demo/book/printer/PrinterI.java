// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

public class PrinterI extends Demo._PrinterDisp
{
    public void
    printString(String s, Ice.Current current)
    {
        System.out.println(s);
    }
}
