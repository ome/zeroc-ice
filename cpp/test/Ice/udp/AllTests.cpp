// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;
using namespace Ice;
using namespace Test;

class PingReplyI : public PingReply, public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    virtual void
    reply(const Ice::Current&)
    {
        Lock sync(*this);
        ++_replies;
        notify();
    }

    void
    reset()
    {
         _replies = 0;
    }

    bool
    waitReply(int expectedReplies, const IceUtil::Time& timeout)
    {
        Lock sync(*this);
        IceUtil::Time end = IceUtil::Time::now() + timeout;
        while(_replies < expectedReplies)
        {
            IceUtil::Time delay = end - IceUtil::Time::now();
            if(delay > IceUtil::Time::seconds(0))
            {
                timedWait(delay);
            }
            else
            {
                break;
            }
        }
        return _replies == expectedReplies;
    }

private:

    int _replies;
};

typedef IceUtil::Handle<PingReplyI> PingReplyIPtr;

void
allTests(const CommunicatorPtr& communicator)
{
    communicator->getProperties()->setProperty("ReplyAdapter.Endpoints", "udp -p 12030");
    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("ReplyAdapter");
    PingReplyIPtr replyI = new PingReplyI;
    PingReplyPrx reply = PingReplyPrx::uncheckedCast(adapter->addWithUUID(replyI))->ice_datagram();
    adapter->activate();

    cout << "testing udp... " << flush;
    ObjectPrx base = communicator->stringToProxy("test -d:udp -p 12010");
    TestIntfPrx obj = TestIntfPrx::uncheckedCast(base);

    int nRetry = 5;
    bool ret;
    while(nRetry-- > 0)
    {
        replyI->reset();
        obj->ping(reply);
        obj->ping(reply);
        obj->ping(reply);
        ret = replyI->waitReply(3, IceUtil::Time::seconds(2));
        if(ret)
        {
            break; // Success
        }

        // If the 3 datagrams were not received within the 2 seconds, we try again to
        // receive 3 new datagrams using a new object. We give up after 5 retries. 
        replyI = new PingReplyI;
        reply = PingReplyPrx::uncheckedCast(adapter->addWithUUID(replyI))->ice_datagram();
    }
    test(ret);

    if(communicator->getProperties()->getPropertyAsInt("Ice.Override.Compress") == 0)
    {
        //
        // Only run this test if compression is disabled, the test expect fixed message size
        // to be sent over the wire.
        //

        Test::ByteSeq seq;
        try
        {
            seq.resize(1024);
            while(true)
            {
                seq.resize(seq.size() * 2 + 10);
                replyI->reset();
                obj->sendByteSeq(seq, reply);
                replyI->waitReply(1, IceUtil::Time::seconds(10));
            }
        }
        catch(const DatagramLimitException&)
        {
            test(seq.size() > 16384);
        }
        obj->ice_getConnection()->close(false);
        communicator->getProperties()->setProperty("Ice.UDP.SndSize", "64000");
        seq.resize(50000);
        try
        {
            replyI->reset();
            obj->sendByteSeq(seq, reply);
            test(!replyI->waitReply(1, IceUtil::Time::milliSeconds(500)));
        }
        catch(const Ice::LocalException& ex)
        {
            cerr << ex << endl;
            test(false);
        }
    }

    cout << "ok" << endl;

    string endpoint;
    if(communicator->getProperties()->getProperty("Ice.IPv6") == "1")
    {
#if defined(__APPLE__)
        endpoint = "udp -h \"ff02::1:1\" -p 12020 --interface \"lo0\"";
#else
        endpoint = "udp -h \"ff01::1:1\" -p 12020";
#endif
    }
    else
    {
        endpoint = "udp -h 239.255.1.1 -p 12020";
    }
    base = communicator->stringToProxy("test -d:" + endpoint);
    TestIntfPrx objMcast = TestIntfPrx::uncheckedCast(base);
#ifndef ICE_OS_WINRT
    cout << "testing udp multicast... " << flush;

    nRetry = 5;
    while(nRetry-- > 0)
    {
        replyI->reset();
        objMcast->ping(reply);
        ret = replyI->waitReply(5, IceUtil::Time::seconds(2));
        if(ret)
        {
            break; // Success
        }
        replyI = new PingReplyI;
        reply = PingReplyPrx::uncheckedCast(adapter->addWithUUID(replyI))->ice_datagram();
    }
    if(!ret)
    {
        cout << "failed (is a firewall enabled?)" << endl;
    }
    else
    {
        cout << "ok" << endl;
    }
#endif

    cout << "testing udp bi-dir connection... " << flush;    
    obj->ice_getConnection()->setAdapter(adapter);
    objMcast->ice_getConnection()->setAdapter(adapter);
    nRetry = 5;
    while(nRetry-- > 0)
    {
        replyI->reset();
        obj->pingBiDir(reply->ice_getIdentity());
        obj->pingBiDir(reply->ice_getIdentity());
        obj->pingBiDir(reply->ice_getIdentity());
        ret = replyI->waitReply(3, IceUtil::Time::seconds(2));
        if(ret)
        {
            break; // Success
        }

        // If the 3 datagrams were not received within the 2 seconds, we try again to
        // receive 3 new datagrams using a new object. We give up after 5 retries. 
        replyI = new PingReplyI;
        reply = PingReplyPrx::uncheckedCast(adapter->addWithUUID(replyI))->ice_datagram();
    }
    test(ret);
    cout << "ok" << endl;

    //
    // Sending the replies back on the multicast UDP connection doesn't work for most
    // platform (it works for OS X Leopard but not Snow Leopard, doesn't work on SLES,
    // Windows...). For Windows, see UdpTransceiver constructor for the details. So
    // we don't run this test.
    // 
//     cout << "testing udp bi-dir connection... " << flush;    
//     nRetry = 5;
//     while(nRetry-- > 0)
//     {
//         replyI->reset();
//         objMcast->pingBiDir(reply->ice_getIdentity());
//         ret = replyI->waitReply(5, IceUtil::Time::seconds(2));
//         if(ret)
//         {
//             break; // Success
//         }        
//         replyI = new PingReplyI;
//         reply = PingReplyPrx::uncheckedCast(adapter->addWithUUID(replyI))->ice_datagram();
//     }
//     if(!ret)
//     {
//         cout << "failed (is a firewall enabled?)" << endl;
//     }
//     else
//     {
//         cout << "ok" << endl;
//     }
}
