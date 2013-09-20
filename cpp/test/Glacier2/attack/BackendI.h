// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef BACKEND_I_H
#define BACKEND_I_H

#include <Backend.h>

class BackendI : public Test::Backend
{
public:

    virtual void shutdown(const Ice::Current&);
};

#endif
