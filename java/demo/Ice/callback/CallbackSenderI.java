// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

import Demo.*;

public final class CallbackSenderI extends _CallbackSenderDisp
{
    public void
    initiateCallback(CallbackReceiverPrx proxy, Ice.Current current)
    {
        System.out.println("initiating callback");
        try
        {
            proxy.callback();
        }
        catch(Ice.LocalException ex)
        {
            ex.printStackTrace();
        }
    }

    public void
    shutdown(Ice.Current current)
    {
        System.out.println("Shutting down...");
        try
        {
            current.adapter.getCommunicator().shutdown();
        }
        catch(Ice.LocalException ex)
        {
            ex.printStackTrace();
        }
    }
}
