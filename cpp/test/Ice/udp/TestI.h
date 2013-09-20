// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef TEST_I_H
#define TEST_I_H

#include <Test.h>

class TestIntfI : public Test::TestIntf
{
public:

    virtual void ping(const Test::PingReplyPrx&, const Ice::Current&);
    virtual void sendByteSeq(const Test::ByteSeq&, const Test::PingReplyPrx&, const Ice::Current&);
    virtual void pingBiDir(const Ice::Identity&, const Ice::Current&);
    virtual void shutdown(const Ice::Current&);
};

#endif
