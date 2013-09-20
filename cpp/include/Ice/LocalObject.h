// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_LOCAL_OBJECT_H
#define ICE_LOCAL_OBJECT_H

#include <IceUtil/Shared.h>
#include <Ice/LocalObjectF.h>

namespace IceInternal
{

class BasicStream;

}

namespace Ice
{

class ICE_API LocalObject : virtual public ::IceUtil::Shared
{
public:

    virtual bool operator==(const LocalObject&) const;
    virtual bool operator<(const LocalObject&) const;
    ICE_DEPRECATED_API ::Ice::Int ice_getHash() const
    {
        return internal_getHash();
    }

protected:

    virtual ::Ice::Int internal_getHash() const;
};

}

#endif
