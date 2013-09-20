// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/Random.h>
#include <IceUtil/IceUtil.h>
#include <Ice/Application.h>
#include <Glacier2/Router.h>
#include <TestCommon.h>
#include <CallbackI.h>

using namespace std;
using namespace Ice;
using namespace Test;

static Ice::InitializationData initData;


class CallbackClient : public Application
{
public:

    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
    //
    // We must disable connection warnings, because we attempt to ping
    // the router before session establishment, as well as after
    // session destruction. Both will cause a ConnectionLostException.
    //
    initData.properties = Ice::createProperties(argc, argv);
    initData.properties->setProperty("Ice.Warn.Connections", "0");
    initData.properties->setProperty("Ice.ThreadPool.Client.Serialize", "1");

    CallbackClient app;
    return app.main(argc, argv, initData);
}

int
CallbackClient::run(int, char**)
{
    ObjectPrx routerBase = communicator()->stringToProxy("Glacier2/router:default -p 12347");
    Glacier2::RouterPrx router = Glacier2::RouterPrx::checkedCast(routerBase);
    communicator()->setDefaultRouter(router);

    ObjectPrx base = communicator()->stringToProxy("c/callback:tcp -p 12010");
    Glacier2::SessionPrx session = router->createSession("userid", "abc123");
    base->ice_ping();

    CallbackPrx twoway = CallbackPrx::checkedCast(base);
    CallbackPrx oneway = twoway->ice_oneway();
    CallbackPrx batchOneway = twoway->ice_batchOneway();

    communicator()->getProperties()->setProperty("Ice.PrintAdapterReady", "0");
    ObjectAdapterPtr adapter = communicator()->createObjectAdapterWithRouter("CallbackReceiverAdapter", router);
    adapter->activate();

    string category = router->getCategoryForClient();

    CallbackReceiverI* callbackReceiverImpl = new CallbackReceiverI;
    ObjectPtr callbackReceiver = callbackReceiverImpl;

    Identity callbackReceiverIdent;
    callbackReceiverIdent.name = "callbackReceiver";
    callbackReceiverIdent.category = category;
    CallbackReceiverPrx twowayR = 
        CallbackReceiverPrx::uncheckedCast(adapter->add(callbackReceiver, callbackReceiverIdent));
    CallbackReceiverPrx onewayR = twowayR->ice_oneway();

    {
        cout << "testing client request override... " << flush;
        {
            for(int i = 0; i < 5; i++)
            {
                oneway->initiateCallback(twowayR, 0);
                oneway->initiateCallback(twowayR, 0);
                callbackReceiverImpl->callbackOK(2, 0);
            }
        }

        {
            Ice::Context ctx;
            ctx["_ovrd"] = "test";
            for(int i = 0; i < 5; i++)
            {
                oneway->initiateCallback(twowayR, i, ctx);
                oneway->initiateCallback(twowayR, i, ctx);
                oneway->initiateCallback(twowayR, i, ctx);
                IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(100));
                test(callbackReceiverImpl->callbackOK(1, i) < 3);
            }
        }
        cout << "ok" << endl;
    }

    {
        cout << "testing server request override... " << flush;
        Ice::Context ctx;
        ctx["serverOvrd"] = "test";
        for(int i = 0; i < 5; i++)
        {
            oneway->initiateCallback(onewayR, i, ctx);
            oneway->initiateCallback(onewayR, i, ctx);
            oneway->initiateCallback(onewayR, i, ctx);
            IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(100));
            test(callbackReceiverImpl->callbackOK(1, i) < 3);
        }
        oneway->initiateCallback(twowayR, 0);
        test(callbackReceiverImpl->callbackOK(1, 0) == 0);

        int count = 0;
        int nRetry = 0;
        do
        {
            callbackReceiverImpl->hold();
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallbackWithPayload(onewayR, ctx);
            oneway->initiateCallback(twowayR, 0);
            IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(200 + nRetry * 200));
            callbackReceiverImpl->activate();
            test(callbackReceiverImpl->callbackOK(1, 0) == 0);
            count = callbackReceiverImpl->callbackWithPayloadOK(0);
            callbackReceiverImpl->callbackWithPayloadOK(count);
        }
        while(count == 10 && nRetry++ < 10);
        test(count < 10);

        oneway->initiateCallbackWithPayload(twowayR);
        oneway->initiateCallbackWithPayload(twowayR);
        callbackReceiverImpl->hold();
        oneway->initiateCallbackWithPayload(twowayR);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallbackWithPayload(twowayR);
        IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(1000));
        callbackReceiverImpl->activate();
        test(callbackReceiverImpl->callbackWithPayloadOK(4) == 0);
        
        int remainingCallbacks = callbackReceiverImpl->callbackOK(1, 0);
        //
        // Occasionally, Glacier2 flushes in the middle of our 5
        // callbacks, so we get more than 1 callback
        // (in theory we could get up to 5 total - more than 1 extra is extremely unlikely)
        //
        // The sleep above is also important as we want to have enough
        // time to receive this (these) extra callback(s).
        //
        test(remainingCallbacks <= 4);
        if(remainingCallbacks > 0)
        {
            test(callbackReceiverImpl->callbackOK(remainingCallbacks, 0) == 0);
        }
        
        ctx["_fwd"] = "O";

        oneway->initiateCallbackWithPayload(twowayR);
        callbackReceiverImpl->hold();
        oneway->initiateCallbackWithPayload(twowayR);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallback(onewayR, 0, ctx);
        oneway->initiateCallbackWithPayload(twowayR);
        IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(200));
        callbackReceiverImpl->activate();
        test(callbackReceiverImpl->callbackWithPayloadOK(3) == 0);
        test(callbackReceiverImpl->callbackOK(1, 0) == 0);

        cout << "ok" << endl;
    }

    {
        cout << "shutdown... " << flush;
        twoway->shutdown();

        try
        {
            router->destroySession();
        }
        catch(const Ice::LocalException&)
        {
            test(false);
        }

        communicator()->setDefaultRouter(0);
        ObjectPrx processBase = communicator()->stringToProxy("Glacier2/admin -f Process:tcp -h 127.0.0.1 -p 12348");
        Ice::ProcessPrx process = Ice::ProcessPrx::checkedCast(processBase);
        process->shutdown();
        try
        {
            process->ice_ping();
            test(false);
        }
        catch(const Ice::LocalException&)
        {
            cout << "ok" << endl;
        }
    }
    return EXIT_SUCCESS;
}
