// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.0
// Generated from file `Communicator.ice'

#include <Ice/Communicator.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/DisableWarnings.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

static const ::std::string __Ice__Communicator__destroy_name = "destroy";

static const ::std::string __Ice__Communicator__shutdown_name = "shutdown";

static const ::std::string __Ice__Communicator__waitForShutdown_name = "waitForShutdown";

static const ::std::string __Ice__Communicator__stringToProxy_name = "stringToProxy";

static const ::std::string __Ice__Communicator__proxyToString_name = "proxyToString";

static const ::std::string __Ice__Communicator__stringToIdentity_name = "stringToIdentity";

static const ::std::string __Ice__Communicator__identityToString_name = "identityToString";

static const ::std::string __Ice__Communicator__createObjectAdapter_name = "createObjectAdapter";

static const ::std::string __Ice__Communicator__createObjectAdapterWithEndpoints_name = "createObjectAdapterWithEndpoints";

static const ::std::string __Ice__Communicator__createObjectAdapterWithRouter_name = "createObjectAdapterWithRouter";

static const ::std::string __Ice__Communicator__addObjectFactory_name = "addObjectFactory";

static const ::std::string __Ice__Communicator__findObjectFactory_name = "findObjectFactory";

static const ::std::string __Ice__Communicator__getDefaultContext_name = "getDefaultContext";

static const ::std::string __Ice__Communicator__setDefaultContext_name = "setDefaultContext";

static const ::std::string __Ice__Communicator__getProperties_name = "getProperties";

static const ::std::string __Ice__Communicator__getLogger_name = "getLogger";

static const ::std::string __Ice__Communicator__getStats_name = "getStats";

static const ::std::string __Ice__Communicator__getDefaultRouter_name = "getDefaultRouter";

static const ::std::string __Ice__Communicator__setDefaultRouter_name = "setDefaultRouter";

static const ::std::string __Ice__Communicator__getDefaultLocator_name = "getDefaultLocator";

static const ::std::string __Ice__Communicator__setDefaultLocator_name = "setDefaultLocator";

static const ::std::string __Ice__Communicator__getPluginManager_name = "getPluginManager";

static const ::std::string __Ice__Communicator__flushBatchRequests_name = "flushBatchRequests";

void
IceInternal::incRef(::Ice::Communicator* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::Ice::Communicator* p)
{
    p->__decRef();
}

bool
Ice::operator==(const ::Ice::Communicator& l, const ::Ice::Communicator& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) == static_cast<const ::Ice::LocalObject&>(r);
}

bool
Ice::operator!=(const ::Ice::Communicator& l, const ::Ice::Communicator& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) != static_cast<const ::Ice::LocalObject&>(r);
}

bool
Ice::operator<(const ::Ice::Communicator& l, const ::Ice::Communicator& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) < static_cast<const ::Ice::LocalObject&>(r);
}

bool
Ice::operator<=(const ::Ice::Communicator& l, const ::Ice::Communicator& r)
{
    return l < r || l == r;
}

bool
Ice::operator>(const ::Ice::Communicator& l, const ::Ice::Communicator& r)
{
    return !(l < r) && !(l == r);
}

bool
Ice::operator>=(const ::Ice::Communicator& l, const ::Ice::Communicator& r)
{
    return !(l < r);
}
