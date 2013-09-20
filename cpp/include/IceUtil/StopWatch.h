// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_UTIL_STOPWATCH_H
#define ICE_UTIL_STOPWATCH_H

#include <IceUtil/Time.h>

namespace IceUtilInternal
{

class StopWatch
{
public:

    StopWatch() { }

    void start()
    {
        _s = IceUtil::Time::now(IceUtil::Time::Monotonic);
    }
    
    IceUtil::Int64 stop()
    {
        assert(isStarted());
        IceUtil::Int64 d = (IceUtil::Time::now(IceUtil::Time::Monotonic) - _s).toMicroSeconds();
        _s = IceUtil::Time();
        return d;
    }

    bool isStarted() const
    {
        return _s != IceUtil::Time();
    }

    IceUtil::Int64 delay()
    {
        return (IceUtil::Time::now(IceUtil::Time::Monotonic) - _s).toMicroSeconds();
    }

private:

    IceUtil::Time _s;
};

} // End namespace IceUtilInternal

#endif
