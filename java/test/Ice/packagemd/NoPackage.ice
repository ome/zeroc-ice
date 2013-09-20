// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["java:package:test.Ice.packagemd"]]
module Test1
{
class C1
{
    int i;
};

class C2 extends C1
{
    long l;
};

exception E1
{
    int i;
};

exception E2 extends E1
{
    long l;
};

exception notify /* Test keyword escape. */
{
    int i;
};
};
