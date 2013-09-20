// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef SESSION_FACTORY_I_H
#define SESSION_FACTORY_I_H

#include <Ice/Ice.h>
#include <Session.h>
#include <ReapTask.h>

class SessionFactoryI : public Demo::SessionFactory
{
public:

    SessionFactoryI(const ReapTaskPtr&);

    virtual Demo::SessionPrx create(const std::string&, const Ice::Current&);
    virtual void shutdown(const Ice::Current&);

private:

    const ReapTaskPtr _reaper;
};

#endif
