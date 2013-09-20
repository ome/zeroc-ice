// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

import Demo.*;

class PrinterI extends Printer
{
    public void
    printBackwards(Ice.Current current)
    {
        char[] arr = message.toCharArray();
        for(int i = 0; i < arr.length / 2; i++)
        {
            char tmp = arr[arr.length - i - 1];
            arr[arr.length - i - 1] = arr[i];
            arr[i] = tmp;
        }
        System.out.println(new String(arr));
    }
}
