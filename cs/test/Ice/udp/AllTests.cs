// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

using Test;
using System;
using System.Threading;

public class AllTests
{
    private static void test(bool b)
    {
        if(!b)
        {
            throw new Exception();
        }
    }

    public class PingReplyI : Test.PingReplyDisp_
    {
        public override void reply(Ice.Current current)
        {
            _m.Lock();
            try
            {
                ++_replies;
                _m.Notify();
            }
            finally
            {
                _m.Unlock();
            }
        }

        public void reset()
        {
            _m.Lock();
            try
            {
                 _replies = 0;
            }
            finally
            {
                _m.Unlock();
            }
        }

        public bool waitReply(int expectedReplies, long timeout)
        {
            _m.Lock();
            try
            {
                long end = IceInternal.Time.currentMonotonicTimeMillis() + timeout;
                while(_replies < expectedReplies)
                {
                    int delay = (int)(end - IceInternal.Time.currentMonotonicTimeMillis());
                    if(delay > 0)
                    {
                        _m.TimedWait(delay);
                    }
                    else
                    {
                        break;
                    }
                }
                return _replies == expectedReplies;
            }
            finally
            {
                _m.Unlock();
            }
        }

        private int _replies = 0;
        private readonly IceUtilInternal.Monitor _m = new IceUtilInternal.Monitor();
    }

    public static void allTests(Ice.Communicator communicator)
    {
        communicator.getProperties().setProperty("ReplyAdapter.Endpoints", "udp -p 12030");
        Ice.ObjectAdapter adapter = communicator.createObjectAdapter("ReplyAdapter");
        PingReplyI replyI = new PingReplyI();
        Test.PingReplyPrx reply =
            (Test.PingReplyPrx)Test.PingReplyPrxHelper.uncheckedCast(adapter.addWithUUID(replyI)).ice_datagram();
        adapter.activate();

        Console.Out.Write("testing udp... ");
        Console.Out.Flush();
        Ice.ObjectPrx @base = communicator.stringToProxy("test:udp -p 12010").ice_datagram();
        Test.TestIntfPrx obj = Test.TestIntfPrxHelper.uncheckedCast(@base);

        int nRetry = 5;
        bool ret = false;
        while(nRetry-- > 0)
        {
            replyI.reset();
            obj.ping(reply);
            obj.ping(reply);
            obj.ping(reply);
            ret = replyI.waitReply(3, 2000);
            if(ret)
            {
                break; // Success
            }

            // If the 3 datagrams were not received within the 2 seconds, we try again to
            // receive 3 new datagrams using a new object. We give up after 5 retries.
            replyI = new PingReplyI();
            reply =(Test.PingReplyPrx)Test.PingReplyPrxHelper.uncheckedCast(adapter.addWithUUID(replyI)).ice_datagram();
        }
        test(ret == true);

        if(communicator.getProperties().getPropertyAsInt("Ice.Override.Compress") == 0)
        {
            //
            // Only run this test if compression is disabled, the test expect fixed message size
            // to be sent over the wire.
            //
            byte[] seq = null;
            try
            {
                seq = new byte[1024];
                while(true)
                {
                    seq = new byte[seq.Length * 2 + 10];
                    replyI.reset();
                    obj.sendByteSeq(seq, reply);
                    replyI.waitReply(1, 10000);
                }
            }
            catch(Ice.DatagramLimitException)
            {
                //
                // The server's Ice.UDP.RcvSize property is set to 16384, which means that DatagramLimitException
                // will be throw when try to send a packet bigger than that. However, Mono 2.10 bug in setting Socket
                // options could cause the RcvSize/SndSize to contain an arbitrary value so the test might fail 
                // with smaller message sizes.
                //
                test(seq.Length > 16384 || IceInternal.AssemblyUtil.runtime_ == IceInternal.AssemblyUtil.Runtime.Mono);
            }
            obj.ice_getConnection().close(false);
            communicator.getProperties().setProperty("Ice.UDP.SndSize", "64000");
            seq = new byte[50000];
            try
            {
                replyI.reset();
                obj.sendByteSeq(seq, reply);

                bool b = replyI.waitReply(1, 500);
                //
                // The server's Ice.UDP.RcvSize property is set to 16384, which means this packet
                // should not be delivered. However, Mono 2.10 bug in setting Socket options could 
                // cause the RcvSize/SndSize to contain an arbitrary value so the packet might 
                // be delivered successfully.
                //
                test(!b || IceInternal.AssemblyUtil.runtime_ == IceInternal.AssemblyUtil.Runtime.Mono);
            }
            catch(Ice.DatagramLimitException)
            {
                //
                // Mono 2.10 bug in setting Socket options could cause the RcvSize/SndSize to contain
                // an arbitrary value so the message send might fail if the effetive SndSize is minor 
                // than expected.
                //
                test(IceInternal.AssemblyUtil.runtime_ == IceInternal.AssemblyUtil.Runtime.Mono);
            }
            catch(Ice.LocalException ex)
            {
                Console.Out.WriteLine(ex);
                test(false);
            }
        }

        Console.Out.WriteLine("ok");

        Console.Out.Write("testing udp multicast... ");
        Console.Out.Flush();
        string endpoint;
        if(communicator.getProperties().getProperty("Ice.IPv6").Equals("1"))
        {
            if(IceInternal.AssemblyUtil.osx_)
            {
                endpoint = "udp -h \"ff02::1:1\" -p 12020 --interface \"lo0\"";
            }
            else
            {
                endpoint = "udp -h \"ff01::1:1\" -p 12020";
            }
        }
        else
        {
            endpoint = "udp -h 239.255.1.1 -p 12020";
        }
        @base = communicator.stringToProxy("test -d:" + endpoint);
        TestIntfPrx objMcast = Test.TestIntfPrxHelper.uncheckedCast(@base);

        nRetry = 5;
        while(nRetry-- > 0)
        {
            replyI.reset();
            objMcast.ping(reply);
            ret = replyI.waitReply(5, 5000);
            if(ret)
            {
                break;
            }
            replyI = new PingReplyI();
            reply =(Test.PingReplyPrx)Test.PingReplyPrxHelper.uncheckedCast(adapter.addWithUUID(replyI)).ice_datagram();
        }
        if(!ret)
        {
            Console.Out.WriteLine("failed (is a firewall enabled?)");
        }
        else
        {
            Console.Out.WriteLine("ok");
        }

        Console.Out.Write("testing udp bi-dir connection... ");
        Console.Out.Flush();
        obj.ice_getConnection().setAdapter(adapter);
        objMcast.ice_getConnection().setAdapter(adapter);
        nRetry = 5;
        while(nRetry-- > 0)
        {
            replyI.reset();
            obj.pingBiDir(reply.ice_getIdentity());
            obj.pingBiDir(reply.ice_getIdentity());
            obj.pingBiDir(reply.ice_getIdentity());
            ret = replyI.waitReply(3, 2000);
            if(ret)
            {
                break; // Success
            }
            replyI = new PingReplyI();
            reply = (PingReplyPrx)PingReplyPrxHelper.uncheckedCast(adapter.addWithUUID(replyI)).ice_datagram();
        }
        test(ret);
        Console.Out.WriteLine("ok");

        //
        // Sending the replies back on the multicast UDP connection doesn't work for most
        // platform (it works for OS X Leopard but not Snow Leopard, doesn't work on SLES,
        // Windows...). For Windows, see UdpTransceiver constructor for the details. So
        // we don't run this test.
        //
//         Console.Out.Write("testing udp bi-dir connection... ");
//         nRetry = 5;
//         while(nRetry-- > 0)
//         {
//             replyI.reset();
//             objMcast.pingBiDir(reply.ice_getIdentity());
//             ret = replyI.waitReply(5, 2000);
//             if(ret)
//             {
//                 break; // Success
//             }
//             replyI = new PingReplyI();
//             reply = (PingReplyPrx)PingReplyPrxHelper.uncheckedCast(adapter.addWithUUID(replyI)).ice_datagram();
//         }

//         if(!ret)
//         {
//             Console.Out.WriteLine("failed (is a firewall enabled?)");
//         }
//         else
//         {
//             Console.Out.WriteLine("ok");
//         }
    }
}
