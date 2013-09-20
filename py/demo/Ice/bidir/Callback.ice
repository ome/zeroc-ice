// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

#include <Ice/Identity.ice>

module Demo
{

interface CallbackReceiver
{
    void callback(int num);
};

interface CallbackSender
{
    void addClient(Ice::Identity ident);
};

};
