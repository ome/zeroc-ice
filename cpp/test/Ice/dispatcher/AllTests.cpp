// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceUtil/Random.h>
#include <TestCommon.h>
#include <Test.h>
#include <Dispatcher.h>

using namespace std;

namespace
{

class Callback : public IceUtil::Shared
{
public:

    Callback() :
        _called(false)
    {
    }

    void check()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(_m);
        while(!_called)
        {
            _m.wait();
        }
        _called = false;
    }

    void
    response()
    {
        test(Dispatcher::isDispatcherThread());
        called();
    }

    void
    exception(const Ice::Exception& ex)
    {
        test(dynamic_cast<const Ice::NoEndpointException*>(&ex));
        test(Dispatcher::isDispatcherThread());
        called();
    }

    void
    payload()
    {
        test(Dispatcher::isDispatcherThread());
    }

    void
    ignoreEx(const Ice::Exception& ex)
    {
        test(dynamic_cast<const Ice::CommunicatorDestroyedException*>(&ex));
    }

    void
    sent(bool sentSynchronously)
    {
        test(sentSynchronously || Dispatcher::isDispatcherThread());
    }

protected:

    void called()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(_m);
        assert(!_called);
        _called = true;
        _m.notify();
    }

private:

    IceUtil::Monitor<IceUtil::Mutex> _m;
    bool _called;
};
typedef IceUtil::Handle<Callback> CallbackPtr;

}

void
allTests(const Ice::CommunicatorPtr& communicator)
{
    string sref = "test:default -p 12010";
    Ice::ObjectPrx obj = communicator->stringToProxy(sref);
    test(obj);

    Test::TestIntfPrx p = Test::TestIntfPrx::uncheckedCast(obj);

    sref = "testController:tcp -p 12011";
    obj = communicator->stringToProxy(sref);
    test(obj);

    Test::TestIntfControllerPrx testController = Test::TestIntfControllerPrx::uncheckedCast(obj);

#ifdef ICE_CPP11
    cout << "testing C++11 dispatcher... " << flush;
#else
    cout << "testing dispatcher... " << flush;
#endif
    {
        p->op();

        CallbackPtr cb = new Callback;
        Test::Callback_TestIntf_opPtr callback = Test::newCallback_TestIntf_op(cb,
                                                                               &Callback::response,
                                                                               &Callback::exception);
        p->begin_op(callback);
        cb->check();

        Test::TestIntfPrx i = p->ice_adapterId("dummy");
        i->begin_op(callback);
        cb->check();

        testController->holdAdapter();

        Test::Callback_TestIntf_opWithPayloadPtr callback2 =
            Test::newCallback_TestIntf_opWithPayload(cb, &Callback::payload, &Callback::ignoreEx, &Callback::sent);

        Ice::ByteSeq seq;
        seq.resize(1024); // Make sure the request doesn't compress too well.
        for(Ice::ByteSeq::iterator q = seq.begin(); q != seq.end(); ++q)
        {
            *q = static_cast<Ice::Byte>(IceUtilInternal::random(255));
        }
        Ice::AsyncResultPtr result;
        while((result = p->begin_opWithPayload(seq, callback2))->sentSynchronously());
        testController->resumeAdapter();
        result->waitForCompleted();
    }
    cout << "ok" << endl;

    p->shutdown();
}
