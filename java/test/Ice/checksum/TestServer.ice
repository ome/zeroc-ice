// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

#include <Ice/SliceChecksumDict.ice>

[["java:package:test.Ice.checksum.server"]]
module Test
{

interface Checksum
{
    idempotent Ice::SliceChecksumDict getSliceChecksums();
    
    void shutdown();
};

};
