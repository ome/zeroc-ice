// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_SERVANT_MANAGER_F_H
#define ICE_SERVANT_MANAGER_F_H

#include <IceUtil/Shared.h>

#include <Ice/Handle.h>

namespace IceInternal
{

class ServantManager;
ICE_API IceUtil::Shared* upCast(ServantManager*);
typedef Handle<ServantManager> ServantManagerPtr;

}

#endif
