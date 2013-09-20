// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

module Test
{

exception CallbackException
{
    double someValue;
    string someString;
};

interface CallbackReceiver
{
    void callback();

    void callbackEx()
        throws CallbackException;
};

interface Callback
{
    void initiateCallback(CallbackReceiver* proxy);

    void initiateCallbackEx(CallbackReceiver* proxy)
        throws CallbackException;

    void shutdown();
};

};

