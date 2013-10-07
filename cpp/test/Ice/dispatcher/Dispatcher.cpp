// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Dispatcher.h>
#include <TestCommon.h>

Dispatcher* Dispatcher::_instance = 0;

Dispatcher::Dispatcher()
{
    _instance = this;
    _terminated = false;
    __setNoDelete(true);
    start();
    __setNoDelete(false);
}

void
Dispatcher::dispatch(const Ice::DispatcherCallPtr& call, const Ice::ConnectionPtr&)
{
    Lock sync(*this);
    _calls.push_back(call);
    if(_calls.size() == 1)
    {
        notify();
    }
}

void
Dispatcher::terminate()
{
    {
        Lock sync(*_instance);
        _instance->_terminated = true;
        _instance->notify();
    }

    _instance->getThreadControl().join();
    _instance = 0;
}

bool
Dispatcher::isDispatcherThread()
{
    return IceUtil::ThreadControl() == _instance->getThreadControl();
}

void
Dispatcher::run()
{
    while(true)
    {
        Ice::DispatcherCallPtr call;
        {
            Lock sync(*this);
            
            while(!_terminated && _calls.empty())
            {               
                wait();
            }
            
            if(!_calls.empty())
            {
                call = _calls.front();
                _calls.pop_front();
            }
            else if(_terminated)
            {
                // Terminate only once all calls are dispatched.
                return;
            }
        }
        
        
        if(call)
        {
            try
            {
                call->run();
            }
            catch(...)
            {
                // Exceptions should never propagate here.
                test(false);
            }
        }
    }
}
