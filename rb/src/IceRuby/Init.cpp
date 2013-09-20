// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Communicator.h>
#include <ImplicitContext.h>
#include <Logger.h>
#include <Operation.h>
#include <Properties.h>
#include <Proxy.h>
#include <Slice.h>
#include <Types.h>
#include <Connection.h>
#include <Endpoint.h>

using namespace std;
using namespace IceRuby;

static VALUE iceModule;

extern "C"
{

void
ICE_DECLSPEC_EXPORT Init_IceRuby()
{
    iceModule = rb_define_module("Ice");
    initCommunicator(iceModule);
    initLogger(iceModule);
    initOperation(iceModule);
    initProperties(iceModule);
    initProxy(iceModule);
    initSlice(iceModule);
    initTypes(iceModule);
    initImplicitContext(iceModule);
    initUtil(iceModule);
    initConnection(iceModule);
    initEndpoint(iceModule);
}

}
