// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef MY_OBJECT_I_H
#define MY_OBJECT_I_H

#include <Test.h>

class MyObjectI : public Test::MyObject
{
public:

    virtual int add(int, int, const Ice::Current&);
    virtual int addWithRetry(int, int, const Ice::Current&);
    virtual int badAdd(int, int, const Ice::Current&);
    virtual int notExistAdd(int, int, const Ice::Current&);
    virtual int badSystemAdd(int, int, const Ice::Current&);
    
    virtual void amdAdd_async(const Test::AMD_MyObject_amdAddPtr&, int, int, const Ice::Current&);
    virtual void amdAddWithRetry_async(const Test::AMD_MyObject_amdAddWithRetryPtr&, int, int, const Ice::Current&);
    virtual void amdBadAdd_async(const Test::AMD_MyObject_amdBadAddPtr&, int, int, const Ice::Current&);
    virtual void amdNotExistAdd_async(const Test::AMD_MyObject_amdNotExistAddPtr&, int, int, const Ice::Current&);
    virtual void amdBadSystemAdd_async(const Test::AMD_MyObject_amdBadSystemAddPtr&, int, int, const Ice::Current&);
};

#endif
