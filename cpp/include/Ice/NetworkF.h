// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_NETWORK_F_H
#define ICE_NETWORK_F_H

#include <IceUtil/Shared.h>

#include <Ice/Handle.h>

namespace IceInternal
{

class NetworkProxy;
ICE_API IceUtil::Shared* upCast(NetworkProxy*);
typedef Handle<NetworkProxy> NetworkProxyPtr;

}

#endif
