// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.metrics;

class ThreadObserverI extends ObserverI implements Ice.Instrumentation.ThreadObserver
{
    public synchronized void 
    reset()
    {
        super.reset();
        states = 0;
    }

    public synchronized void 
    stateChanged(Ice.Instrumentation.ThreadState o, Ice.Instrumentation.ThreadState n)
    {
        ++states;
    }

    int states;
};

