// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_REFERENCE_FACTORY_F_H
#define ICE_REFERENCE_FACTORY_F_H

#include <Ice/Handle.h>

namespace IceInternal
{

class ReferenceFactory;
IceUtil::Shared* upCast(ReferenceFactory*);
typedef Handle<ReferenceFactory> ReferenceFactoryPtr;

}

#endif
