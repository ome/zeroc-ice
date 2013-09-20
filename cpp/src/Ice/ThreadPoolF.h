// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_THREAD_POOL_F_H
#define ICE_THREAD_POOL_F_H

#include <IceUtil/Shared.h>

#include <Ice/Handle.h>

namespace IceInternal
{

class ThreadPool;
ICE_API IceUtil::Shared* upCast(ThreadPool*);
typedef Handle<ThreadPool> ThreadPoolPtr;

class ThreadPoolWorkItem;
ICE_API IceUtil::Shared* upCast(ThreadPoolWorkItem*);
typedef Handle<ThreadPoolWorkItem> ThreadPoolWorkItemPtr;

class ThreadPoolCurrent;

}

#endif
