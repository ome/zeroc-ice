// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_GRID_WAIT_QUEUE_H
#define ICE_GRID_WAIT_QUEUE_H

#include <IceUtil/Thread.h>
#include <IceUtil/Monitor.h>

#include <list>

namespace IceGrid
{

class WaitItem : virtual public IceUtil::Shared
{
public:
    
    WaitItem();
    virtual ~WaitItem();

    virtual void expired(bool) = 0;
    
    const IceUtil::Time& getExpirationTime();
    void setExpirationTime(const IceUtil::Time&);

private:

    IceUtil::Time _expiration;
};

typedef IceUtil::Handle<WaitItem> WaitItemPtr;

class WaitQueue : public IceUtil::Thread, public IceUtil::Monitor< IceUtil::Mutex>
{
public:

    WaitQueue();

    virtual void run();
    void destroy();

    void add(const WaitItemPtr&, const IceUtil::Time&);
    bool remove(const WaitItemPtr&);

private:
    
    std::list<WaitItemPtr> _waitQueue;
    bool _destroyed;
};

typedef IceUtil::Handle<WaitQueue> WaitQueuePtr;

}

#endif
