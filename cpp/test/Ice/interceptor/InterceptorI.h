// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef INTERCEPTOR_I_H
#define INTERCEPTOR_I_H

#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>

class InterceptorI : public Ice::DispatchInterceptor
{
public:

    InterceptorI(const Ice::ObjectPtr&);
    
    virtual Ice::DispatchStatus dispatch(Ice::Request& request);
    
    Ice::DispatchStatus getLastStatus() const;
    const std::string& getLastOperation() const;
    
    virtual void clear();

protected:
    const Ice::ObjectPtr _servant;
    std::string _lastOperation;
    Ice::DispatchStatus _lastStatus;
};

typedef IceUtil::Handle<InterceptorI> InterceptorIPtr;

#endif
