// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

#include <TestAMD.ice>

module Test
{

exception UnknownDerived extends Base
{
    string ud;
};

exception UnknownIntermediate extends Base
{
   string ui;
};

exception UnknownMostDerived1 extends KnownIntermediate
{
   string umd1;
};

exception UnknownMostDerived2 extends UnknownIntermediate
{
   string umd2;
};

};
