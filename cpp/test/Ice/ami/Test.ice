// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

#include <Ice/BuiltinSequences.ice>
#include <Ice/Endpoint.ice>

module Test
{

exception TestIntfException
{
};

interface TestIntf
{
    void op();
    void opWithPayload(Ice::ByteSeq seq);
    int opWithResult();
    void opWithUE()
        throws TestIntfException;    
    void opBatch();
    int opBatchCount();
    bool waitForBatch(int count);
    void close(bool force);
    void shutdown();
};

interface TestIntfController
{
    void holdAdapter();
    void resumeAdapter();
};

};

