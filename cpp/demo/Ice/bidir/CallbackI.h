// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef CALLBACK_I_H
#define CALLBACK_I_H

#include <IceUtil/IceUtil.h>
#include <Callback.h>
#include <set>

class CallbackSenderI;
typedef IceUtil::Handle<CallbackSenderI> CallbackSenderIPtr;

class CallbackSenderI : public Demo::CallbackSender, public IceUtil::Monitor<IceUtil::Mutex>
{
public:
    
    CallbackSenderI(const Ice::CommunicatorPtr&);

    void destroy();

    virtual void addClient(const Ice::Identity&, const Ice::Current&);

    void start();
    void run();

private:

    Ice::CommunicatorPtr _communicator;
    bool _destroy;
    std::set<Demo::CallbackReceiverPrx> _clients;

    //
    // We cannot derive CallbackSenderI from IceUtil::Thread, because
    // CallbackSenderI uses IceUtil::GCShared as base, and
    // IceUtil::Thread uses IceUtil::Shared as base. These two base
    // classes are not compatible. Therefore we use this helper class.
    //
    class CallbackSenderThread : public IceUtil::Thread
    {
    public:

        CallbackSenderThread(const CallbackSenderIPtr& callbackSender) :
            _callbackSender(callbackSender)
        {
        }

        virtual void run()
        {
            _callbackSender->run();
        }

    private:

        const CallbackSenderIPtr _callbackSender;
    };

    IceUtil::ThreadPtr _callbackSenderThread;
};

#endif
