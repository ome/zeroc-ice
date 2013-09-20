// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceGrid/AdminCallbackRouter.h>

using namespace Ice;
using namespace std;

void
IceGrid::AdminCallbackRouter::invokeResponse(bool ok, const std::pair<const Byte*, const Byte*>& outParams,
                                             const InvokeCookiePtr& cookie)
{
    cookie->cb()->ice_response(ok, outParams);
}

void
IceGrid::AdminCallbackRouter::invokeException(const Ice::Exception&, const InvokeCookiePtr& cookie)
{
    // Callback object is unreachable.
    cookie->cb()->ice_exception(ObjectNotExistException(__FILE__, __LINE__));
}

void
IceGrid::AdminCallbackRouter::addMapping(const string& category, const ConnectionPtr& con)
{
    IceUtil::Mutex::Lock sync(_mutex);

#ifdef NDEBUG
    _categoryToConnection.insert(map<string, ConnectionPtr>::value_type(category, con));
#else
    bool inserted =
        _categoryToConnection.insert(map<string, ConnectionPtr>::value_type(category, con)).second;
    assert(inserted == true);
#endif
}

void
IceGrid::AdminCallbackRouter::removeMapping(const string& category)
{
    IceUtil::Mutex::Lock sync(_mutex);

#ifndef NDEBUG
    size_t one =
#endif
        _categoryToConnection.erase(category);

    assert(one == 1);
}


void
IceGrid::AdminCallbackRouter::ice_invoke_async(const AMD_Object_ice_invokePtr& cb, 
                                               const pair<const Byte*, const Byte*>& inParams,
                                               const Current& current)
{
    ConnectionPtr con;

    {
        IceUtil::Mutex::Lock sync(_mutex);
        map<string, ConnectionPtr>::iterator p = _categoryToConnection.find(current.id.category);
        if(p == _categoryToConnection.end())
        {
            throw ObjectNotExistException(__FILE__, __LINE__);
        }
        con = p->second;
    }

  
    ObjectPrx target = con->createProxy(current.id)->ice_facet(current.facet);
    
        
    //
    // Call with AMI
    //
    target->begin_ice_invoke(current.operation, current.mode, inParams, current.ctx, 
                             newCallback_Object_ice_invoke(
                                            this, 
                                            &AdminCallbackRouter::invokeResponse, 
                                            &AdminCallbackRouter::invokeException),
                             new InvokeCookie(cb));
}

