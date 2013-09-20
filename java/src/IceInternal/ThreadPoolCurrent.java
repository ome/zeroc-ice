// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

public final class ThreadPoolCurrent
{
    ThreadPoolCurrent(Instance instance, ThreadPool threadPool, ThreadPool.EventHandlerThread thread)
    {
        operation = SocketOperation.None;
        stream = new BasicStream(instance, Protocol.currentProtocolEncoding);

        _threadPool = threadPool;
        _thread = thread;
        _ioCompleted = false;
        _leader = false;
    }

    public int operation;
    public BasicStream stream; // A per-thread stream to be used by event handlers for optimization.

    public void
    ioCompleted()
    {
        _threadPool.ioCompleted(this);
    }
    
    final ThreadPool _threadPool;
    final ThreadPool.EventHandlerThread _thread;
    EventHandler _handler;
    boolean _ioCompleted;
    boolean _leader;
}
