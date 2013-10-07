// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.metrics;

class ObserverI implements Ice.Instrumentation.Observer
{
    synchronized public void 
    reset()
    {
        total = 0;
        current = 0;
        failedCount = 0;
    }

    synchronized public void 
    attach()
    {
        ++total;
        ++current;
    }
    synchronized public void 
    detach()
    {
        --current;
    }
    synchronized public void 
    failed(String s)
    {
        ++failedCount;
    }
    
    synchronized int 
    getTotal()
    {
        return total;
    }

    synchronized int 
    getCurrent()
    {
        return current;
    }

    synchronized int 
    getFailedCount()
    {
        return failedCount;
    }

    int total;
    int current;
    int failedCount;
};
