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
using System.Diagnostics;
using System.Threading;

public class AllTests
{
    private static void test(bool b)
    {
        if(!b)
        {
            throw new System.Exception();
        }
    }

    private class Callback
    {
        internal Callback()
        {
            _called = false;
        }

        public virtual void check()
        {
            _m.Lock();
            try
            {
                while(!_called)
                {
                    _m.Wait();
                }

                _called = false;
            }
            finally
            {
                _m.Unlock();
            }
        }

        public virtual void called()
        {
            _m.Lock();
            try
            {
                Debug.Assert(!_called);
                _called = true;
                _m.Notify();
            }
            finally
            {
                _m.Unlock();
            }
        }

        public virtual bool isCalled()
        {
            _m.Lock();
            try
            {
                return _called;
            }
            finally
            {
                _m.Unlock();
            }
        }

        private bool _called;
        private readonly IceUtilInternal.Monitor _m = new IceUtilInternal.Monitor();
    }

    private class OpAMICallback
    {
        public void response()
        {
            _response.called();
        }

        public void noResponse()
        {
            test(false);
        }

        public void exception(Ice.Exception ex)
        {
            _response.called();
        }

        public void noException(Ice.Exception ex)
        {
            Console.Error.WriteLine(ex);
            test(false);
        }

        public void sent(bool ss)
        {
            _sent.called();
        }

        public bool checkException(bool wait)
        {
            if(wait)
            {
                _response.check();
                return true;
            }
            else
            {
                return _response.isCalled();
            }
        }

        public bool checkResponse(bool wait)
        {
            if(wait)
            {
                _response.check();
                return true;
            }
            else
            {
                return _response.isCalled();
            }
        }

        public void checkResponseAndSent()
        {
            _sent.check();
            _response.check();
        }

        private Callback _response = new Callback();
        private Callback _sent = new Callback();
    }

    private class OpThread
    {
        internal OpThread(BackgroundPrx background)
        {
            _background = BackgroundPrxHelper.uncheckedCast(background.ice_oneway());
            Start();
        }

        public void Join()
        {
            _thread.Join();
        }

        public void Start()
        {
            _thread = new Thread(new ThreadStart(Run));
            _thread.Start();
        }

        public void Run()
        {
            int count = 0;
            while(true)
            {
                lock(this)
                {
                    if(_destroyed)
                    {
                        return;
                    }
                }

                try
                {
                    if(++count == 10) // Don't blast the connection with only oneway's
                    {
                        count = 0;
                        _background.ice_twoway().ice_ping();
                    }
                    _background.begin_op();
                    Thread.Sleep(1);
                }
                catch(Ice.LocalException)
                {
                }
            }
        }

        public void destroy()
        {
            lock(this)
            {
                _destroyed = true;
            }
        }

        private bool _destroyed = false;
        private BackgroundPrx _background = null;
        private Thread _thread;
    }

    public static Test.BackgroundPrx allTests(Ice.Communicator communicator)
    {
        string sref = "background:default -p 12010";
        Ice.ObjectPrx obj = communicator.stringToProxy(sref);
        test(obj != null);

        BackgroundPrx background = BackgroundPrxHelper.uncheckedCast(obj);

        sref = "backgroundController:tcp -p 12011";
        obj = communicator.stringToProxy(sref);
        test(obj != null);

        BackgroundControllerPrx backgroundController = BackgroundControllerPrxHelper.uncheckedCast(obj);

        Configuration configuration = Configuration.getInstance();

        Console.Write("testing connect... ");
        Console.Out.Flush();
        {
            connectTests(configuration, background);
        }
        Console.Out.WriteLine("ok");

        Console.Write("testing initialization... ");
        Console.Out.Flush();
        {
            initializeTests(configuration, background, backgroundController);
        }
        Console.Out.WriteLine("ok");

        Console.Write("testing connection validation... ");
        Console.Out.Flush();
        {
            validationTests(configuration, background, backgroundController);
        }
        Console.Out.WriteLine("ok");

        Console.Write("testing read/write... ");
        Console.Out.Flush();
        {
            readWriteTests(configuration, background, backgroundController);
        }
        Console.Out.WriteLine("ok");

        Console.Write("testing locator... ");
        Console.Out.Flush();
        {
            Ice.LocatorPrx locator;
            obj = communicator.stringToProxy("locator:default -p 12010 -t 500");
            locator = Ice.LocatorPrxHelper.uncheckedCast(obj);
            obj = communicator.stringToProxy("background@Test").ice_locator(locator).ice_oneway();

            backgroundController.pauseCall("findAdapterById");
            try
            {
                obj.ice_ping();
                test(false);
            }
            catch(Ice.TimeoutException)
            {
            }
            backgroundController.resumeCall("findAdapterById");

            obj = communicator.stringToProxy("locator:default -p 12010");
            locator = Ice.LocatorPrxHelper.uncheckedCast(obj);
            obj = obj.ice_locator(locator);
            obj.ice_ping();

            obj = communicator.stringToProxy("background@Test").ice_locator(locator);
            BackgroundPrx bg = BackgroundPrxHelper.uncheckedCast(obj);

            backgroundController.pauseCall("findAdapterById");
            Ice.AsyncResult r1 = bg.begin_op();
            Ice.AsyncResult r2 = bg.begin_op();
            test(!r1.IsCompleted);
            test(!r2.IsCompleted);
            backgroundController.resumeCall("findAdapterById");
            bg.end_op(r1);
            bg.end_op(r2);
            test(r1.IsCompleted);
            test(r2.IsCompleted);
        }
        Console.Out.WriteLine("ok");

        Console.Write("testing router... ");
        Console.Out.Flush();
        {
            Ice.RouterPrx router;

            obj = communicator.stringToProxy("router:default -p 12010 -t 500");
            router = Ice.RouterPrxHelper.uncheckedCast(obj);
            obj = communicator.stringToProxy("background@Test").ice_router(router).ice_oneway();

            backgroundController.pauseCall("getClientProxy");
            try
            {
                obj.ice_ping();
                test(false);
            }
            catch(Ice.TimeoutException)
            {
            }
            backgroundController.resumeCall("getClientProxy");

            obj = communicator.stringToProxy("router:default -p 12010");
            router = Ice.RouterPrxHelper.uncheckedCast(obj);
            obj = communicator.stringToProxy("background@Test").ice_router(router);
            BackgroundPrx bg = BackgroundPrxHelper.uncheckedCast(obj);
            test(bg.ice_getRouter() != null);

            backgroundController.pauseCall("getClientProxy");
            Ice.AsyncResult r1 = bg.begin_op();
            Ice.AsyncResult r2 = bg.begin_op();
            test(!r1.IsCompleted);
            test(!r2.IsCompleted);
            backgroundController.resumeCall("getClientProxy");
            bg.end_op(r1);
            bg.end_op(r2);
            test(r1.IsCompleted);
            test(r2.IsCompleted);
        }
        Console.Out.WriteLine("ok");

        return background;
    }

    private static void connectTests(Configuration configuration, Test.BackgroundPrx background)
    {
        try
        {
            background.op();
        }
        catch(Ice.LocalException ex)
        {
            System.Console.Out.WriteLine(ex);
            test(false);
        }
        background.ice_getConnection().close(false);

        for(int i = 0; i < 4; ++i)
        {
            if(i == 0 || i == 2)
            {
                configuration.connectorsException(new Ice.DNSException());
            }
            else
            {
                configuration.connectException(new Ice.SocketException());
            }
            BackgroundPrx prx = (i == 1 || i == 3) ? background : (BackgroundPrx)background.ice_oneway();

            try
            {
                prx.op();
                test(false);
            }
            catch(Ice.Exception)
            {
            }

            Ice.AsyncResult r = prx.begin_op();
            test(!r.sentSynchronously());
            try
            {
                prx.end_op(r);
                test(false);
            }
            catch(Ice.Exception)
            {
            }
            test(r.IsCompleted);

            OpAMICallback cbEx = new OpAMICallback();
            r = prx.begin_op().whenCompleted(cbEx.exception);
            test(!r.sentSynchronously());
            cbEx.checkException(true);
            test(r.IsCompleted);

            if(i == 0 || i == 2)
            {
                configuration.connectorsException(null);
            }
            else
            {
                configuration.connectException(null);
            }
        }

        OpThread thread1 = new OpThread(background);
        OpThread thread2 = new OpThread(background);

        for(int i = 0; i < 5; i++)
        {
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
                test(false);
            }

            configuration.connectException(new Ice.SocketException());
            background.ice_getCachedConnection().close(true);
            Thread.Sleep(10);
            configuration.connectException(null);
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
            }
        }

        thread1.destroy();
        thread2.destroy();

        thread1.Join();
        thread2.Join();
    }

    private static void initializeTests(Configuration configuration, Test.BackgroundPrx background,
                                        Test.BackgroundControllerPrx ctl)
    {
        try
        {
            background.op();
        }
        catch(Ice.LocalException)
        {
            test(false);
        }
        background.ice_getConnection().close(false);

        for(int i = 0; i < 4; ++i)
        {
            if(i == 0 || i == 2)
            {
                configuration.initializeException(new Ice.SocketException());
            }
            else
            {
                continue;
            }
            BackgroundPrx prx = (i == 1 || i == 3) ? background : (BackgroundPrx)background.ice_oneway();

            try
            {
                prx.op();
                test(false);
            }
            catch(Ice.SocketException)
            {
            }

            Ice.AsyncResult r = prx.begin_op();
            test(!r.sentSynchronously());
            try
            {
                prx.end_op(r);
                test(false);
            }
            catch(Ice.Exception)
            {
            }
            test(r.IsCompleted);

            OpAMICallback cbEx = new OpAMICallback();
            r = prx.begin_op().whenCompleted(cbEx.exception);
            test(!r.sentSynchronously());
            cbEx.checkException(true);
            test(r.IsCompleted);

            if(i == 0 || i == 2)
            {
                configuration.initializeException(null);
            }
        }

        //
        // Now run the same tests with the server side.
        //

        try
        {
            ctl.initializeException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.initializeException(false);
        }
        catch(Ice.SecurityException)
        {
            ctl.initializeException(false);
        }

        OpThread thread1 = new OpThread(background);
        OpThread thread2 = new OpThread(background);

        for(int i = 0; i < 5; i++)
        {
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
                test(false);
            }

            configuration.initializeException(new Ice.SocketException());
            background.ice_getCachedConnection().close(true);
            Thread.Sleep(10);
            configuration.initializeException(null);
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
            }
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
                test(false);
            }

            background.ice_getCachedConnection().close(true);
            background.ice_ping();

            ctl.initializeException(true);
            background.ice_getCachedConnection().close(true);
            Thread.Sleep(10);
            ctl.initializeException(false);
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
            }
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
                test(false);
            }

            try
            {
                background.ice_getCachedConnection().close(true);
                background.op();
            }
            catch(Ice.LocalException)
            {
                test(false);
            }
        }

        thread1.destroy();
        thread2.destroy();

        thread1.Join();
        thread2.Join();
    }

    private static void validationTests(Configuration configuration, Test.BackgroundPrx background,
                                        Test.BackgroundControllerPrx ctl)
    {
        try
        {
            background.op();
        }
        catch(Ice.LocalException)
        {
            test(false);
        }
        background.ice_getConnection().close(false);

        try
        {
            // Get the read() of connection validation to throw right away.
            configuration.readException(new Ice.SocketException());
            background.op();
            test(false);
        }
        catch(Ice.SocketException)
        {
            configuration.readException(null);
        }

        for(int i = 0; i < 2; ++i)
        {
            configuration.readException(new Ice.SocketException());
            BackgroundPrx prx = i == 0 ? background : (BackgroundPrx)background.ice_oneway();
            Ice.AsyncResult r = prx.begin_op();
            test(!r.sentSynchronously());
            try
            {
                prx.end_op(r);
                test(false);
            }
            catch(Ice.SocketException)
            {
            }
            test(r.IsCompleted);
            configuration.readException(null);
        }

        if(!background.ice_getCommunicator().getProperties().getProperty("Ice.Default.Protocol").Equals("test-ssl"))
        {
            try
            {
                // Get the read() of the connection validation to return "would block"
                configuration.readReady(false);
                background.op();
                configuration.readReady(true);
            }
            catch(Ice.LocalException ex)
            {
                Console.Error.WriteLine(ex);
                test(false);
            }
            background.ice_getConnection().close(false);

            try
            {
                // Get the read() of the connection validation to return "would block" and then throw.
                configuration.readReady(false);
                configuration.readException(new Ice.SocketException());
                background.op();
                test(false);
            }
            catch(Ice.SocketException)
            {
                configuration.readException(null);
                configuration.readReady(true);
            }

            for(int i = 0; i < 2; ++i)
            {
                configuration.readReady(false);
                configuration.readException(new Ice.SocketException());
                Ice.AsyncResult r = background.begin_op();
                test(!r.sentSynchronously());
                try
                {
                    background.end_op(r);
                    test(false);
                }
                catch(Ice.SocketException)
                {
                }
                test(r.IsCompleted);
                configuration.readException(null);
                configuration.readReady(true);
            }
        }

        {
            ctl.holdAdapter(); // Hold to block in connection validation
            Ice.AsyncResult r = background.begin_op();
            Ice.AsyncResult r2 = background.begin_op();
            test(!r.sentSynchronously() && !r2.sentSynchronously());
            test(!r.IsCompleted && !r2.IsCompleted);
            ctl.resumeAdapter();
            background.end_op(r);
            background.end_op(r2);
            test(r.IsCompleted && r2.IsCompleted);
        }

        try
        {
            // Get the write() of connection validation to throw right away.
            ctl.writeException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.writeException(false);
        }

        try
        {
            // Get the write() of the connection validation to return "would block"
            ctl.writeReady(false);
            background.op();
            ctl.writeReady(true);
        }
        catch(Ice.LocalException ex)
        {
            Console.Error.WriteLine(ex);
            test(false);
        }
        background.ice_getConnection().close(false);

        try
        {
            // Get the write() of the connection validation to return "would block" and then throw.
            ctl.writeReady(false);
            ctl.writeException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.writeException(false);
            ctl.writeReady(true);
        }

        byte[] seq = new byte[512 * 1024];

        BackgroundPrx backgroundBatchOneway = BackgroundPrxHelper.uncheckedCast(background.ice_batchOneway());

        //
        // First send small requests to test without auto-flushing.
        //
        backgroundBatchOneway.ice_ping();
        backgroundBatchOneway.ice_getConnection().close(false);
        try
        {
            backgroundBatchOneway.ice_ping();
            test(false);
        }
        catch(Ice.CloseConnectionException)
        {
        }
        ctl.holdAdapter();
        backgroundBatchOneway.op();
        backgroundBatchOneway.op();
        backgroundBatchOneway.op();
        backgroundBatchOneway.op();
        ctl.resumeAdapter();
        backgroundBatchOneway.ice_flushBatchRequests();

        //
        // Send bigger requests to test with auto-flushing.
        //
        backgroundBatchOneway.ice_ping();
        backgroundBatchOneway.ice_getConnection().close(false);
        try
        {
            backgroundBatchOneway.ice_ping();
            test(false);
        }
        catch(Ice.CloseConnectionException)
        {
        }
        ctl.holdAdapter();
        backgroundBatchOneway.opWithPayload(seq);
        backgroundBatchOneway.opWithPayload(seq);
        backgroundBatchOneway.opWithPayload(seq);
        backgroundBatchOneway.opWithPayload(seq);
        ctl.resumeAdapter();
        backgroundBatchOneway.ice_flushBatchRequests();

        //
        // Then try the same thing with async flush.
        //

        backgroundBatchOneway.ice_ping();
        backgroundBatchOneway.ice_getConnection().close(false);
        try
        {
            backgroundBatchOneway.ice_ping();
            test(false);
        }
        catch(Ice.CloseConnectionException)
        {
        }
        ctl.holdAdapter();
        backgroundBatchOneway.op();
        backgroundBatchOneway.op();
        backgroundBatchOneway.op();
        backgroundBatchOneway.op();
        ctl.resumeAdapter();
        backgroundBatchOneway.begin_ice_flushBatchRequests();
        backgroundBatchOneway.ice_getConnection().close(false);

        backgroundBatchOneway.ice_ping();
        backgroundBatchOneway.ice_getConnection().close(false);
        try
        {
            backgroundBatchOneway.ice_ping();
            test(false);
        }
        catch(Ice.CloseConnectionException)
        {
        }
        ctl.holdAdapter();
        backgroundBatchOneway.opWithPayload(seq);
        backgroundBatchOneway.opWithPayload(seq);
        backgroundBatchOneway.opWithPayload(seq);
        backgroundBatchOneway.opWithPayload(seq);
        ctl.resumeAdapter();
        Ice.AsyncResult r3 = backgroundBatchOneway.begin_ice_flushBatchRequests();
        //
        // We can't close the connection before ensuring all the batches have been sent since
        // with auto-flushing the close connection message might be sent once the first call
        // opWithPayload is sent and before the flushBatchRequests (this would therefore result
        // in the flush to report a CloseConnectionException). Instead we flush a second time
        // with the same callback to wait for the first flush to complete.
        //
        //backgroundBatchOneway.ice_getConnection().close(false);
        backgroundBatchOneway.end_ice_flushBatchRequests(r3);
        backgroundBatchOneway.ice_getConnection().close(false);
    }

    private static void readWriteTests(Configuration configuration, Test.BackgroundPrx background,
                                       Test.BackgroundControllerPrx ctl)
    {
        try
        {
            background.op();
        }
        catch(Ice.LocalException ex)
        {
            Console.Error.WriteLine(ex);
            test(false);
        }

        for(int i = 0; i < 2; ++i)
        {
            BackgroundPrx prx = i == 0 ? background : (BackgroundPrx)background.ice_oneway();

            try
            {
                prx.ice_ping();
                configuration.writeException(new Ice.SocketException());
                prx.op();
                test(false);
            }
            catch(Ice.SocketException)
            {
                configuration.writeException(null);
            }

            background.ice_ping();
            configuration.writeException(new Ice.SocketException());
            Ice.AsyncResult r = prx.begin_op();
            test(!r.sentSynchronously());
            try
            {
                prx.end_op(r);
                test(false);
            }
            catch(Ice.SocketException)
            {
            }
            test(r.IsCompleted);
            configuration.writeException(null);
        }

        try
        {
            background.ice_ping();
            configuration.readException(new Ice.SocketException());
            background.op();
            test(false);
        }
        catch(Ice.SocketException)
        {
            configuration.readException(null);
        }

        {
            background.ice_ping();
            configuration.readReady(false); // Required in C# to make sure beginRead() doesn't throw too soon.
            configuration.readException(new Ice.SocketException());
            Ice.AsyncResult r = background.begin_op();
            if(!r.sentSynchronously())
            {
                // The read exception might propagate before the message send is seen as completed on IOCP.
                //test(r.IsCompleted);
            }
            try
            {
                background.end_op(r);
                test(false);
            }
            catch(Ice.SocketException)
            {
            }
            test(r.IsCompleted);
            configuration.readException(null);
            configuration.readReady(true);
        }

        try
        {
            background.ice_ping();
            configuration.writeReady(false);
            background.op();
            configuration.writeReady(true);
        }
        catch(Ice.LocalException)
        {
            test(false);
        }

        try
        {
            background.ice_ping();
            configuration.readReady(false);
            background.op();
            configuration.readReady(true);
        }
        catch(Ice.LocalException)
        {
            test(false);
        }

        try
        {
            background.ice_ping();
            configuration.writeReady(false);
            configuration.writeException(new Ice.SocketException());
            background.op();
            test(false);
        }
        catch(Ice.SocketException)
        {
            configuration.writeReady(true);
            configuration.writeException(null);
        }

        for(int i = 0; i < 2; ++i)
        {
            BackgroundPrx prx = i == 0 ? background : (BackgroundPrx)background.ice_oneway();

            background.ice_ping();
            configuration.writeReady(false);
            configuration.writeException(new Ice.SocketException());
            Ice.AsyncResult r = prx.begin_op();
            test(!r.sentSynchronously());
            try
            {
                prx.end_op(r);
                test(false);
            }
            catch(Ice.SocketException)
            {
            }
            test(r.IsCompleted);
            configuration.writeReady(true);
            configuration.writeException(null);
        }

        try
        {
            background.ice_ping();
            configuration.readReady(false);
            configuration.readException(new Ice.SocketException());
            background.op();
            test(false);
        }
        catch(Ice.SocketException)
        {
            configuration.readException(null);
            configuration.readReady(true);
        }

        {
            background.ice_ping();
            configuration.readReady(false);
            configuration.readException(new Ice.SocketException());
            Ice.AsyncResult r = background.begin_op();
            if(!r.sentSynchronously())
            {
                // The read exception might propagate before the message send is seen as completed on IOCP.
                //test(r.isCompleted());
            }
            try
            {
                background.end_op(r);
                test(false);
            }
            catch(Ice.SocketException)
            {
            }
            test(r.IsCompleted);
            configuration.readReady(true);
            configuration.readException(null);
        }

        {
            background.ice_ping();
            configuration.readReady(false);
            configuration.writeReady(false);
            configuration.readException(new Ice.SocketException());
            Ice.AsyncResult r = background.begin_op();
            // The read exception might propagate before the message send is seen as completed on IOCP.
            //r.waitForSent();
            try
            {
                background.end_op(r);
                test(false);
            }
            catch(Ice.SocketException)
            {
            }
            test(r.IsCompleted);
            configuration.writeReady(true);
            configuration.readReady(true);
            configuration.readException(null);
        }

        background.ice_ping(); // Establish the connection

        BackgroundPrx backgroundOneway = BackgroundPrxHelper.uncheckedCast(background.ice_oneway());
        test(backgroundOneway.ice_getConnection() == background.ice_getConnection());

        ctl.holdAdapter(); // Hold to block in request send.

        byte[] seq = new byte[1024 * 1024];
        (new System.Random()).NextBytes(seq);
        OpAMICallback cbWP = new OpAMICallback();
        while(backgroundOneway.begin_opWithPayload(seq).whenCompleted(cbWP.noResponse,
                                                                      cbWP.noException).sentSynchronously())
        {
        }

        OpAMICallback cb = new OpAMICallback();
        Ice.AsyncResult r1 = background.begin_op().whenCompleted(cb.response, cb.noException).whenSent(cb.sent);
        test(!r1.sentSynchronously() && !r1.isSent());

        OpAMICallback cb2 = new OpAMICallback();
        Ice.AsyncResult r2 = background.begin_op().whenCompleted(cb2.response, cb2.noException).whenSent(cb2.sent);
        test(!r2.sentSynchronously() && !r2.isSent());

        test(!backgroundOneway.begin_opWithPayload(seq).whenCompleted(cbWP.noResponse, 
                                                                      cbWP.noException).sentSynchronously());
        test(!backgroundOneway.begin_opWithPayload(seq).whenCompleted(cbWP.noResponse, 
                                                                      cbWP.noException).sentSynchronously());

        test(!cb.checkResponse(false));
        test(!cb2.checkResponse(false));
        ctl.resumeAdapter();
        cb.checkResponseAndSent();
        cb2.checkResponseAndSent();
        test(r1.isSent() && r1.IsCompleted);
        test(r2.isSent() && r2.IsCompleted);

        try
        {
            background.ice_ping();
            ctl.writeException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.writeException(false);
        }

        try
        {
            background.ice_ping();
            ctl.readException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.readException(false);
        }

        try
        {
            background.ice_ping();
            ctl.writeReady(false);
            background.op();
            ctl.writeReady(true);
        }
        catch(Ice.LocalException)
        {
            test(false);
        }

        try
        {
            background.ice_ping();
            ctl.readReady(false);
            background.op();
            ctl.readReady(true);
        }
        catch(Ice.LocalException)
        {
            test(false);
        }

        try
        {
            background.ice_ping();
            ctl.writeReady(false);
            ctl.writeException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.writeException(false);
            ctl.writeReady(true);
        }

        try
        {
            background.ice_ping();
            ctl.readReady(false);
            ctl.readException(true);
            background.op();
            test(false);
        }
        catch(Ice.ConnectionLostException)
        {
            ctl.readException(false);
            ctl.readReady(true);
        }

        OpThread thread1 = new OpThread(background);
        OpThread thread2 = new OpThread(background);

        for(int i = 0; i < 5; i++)
        {
            try
            {
                background.ice_ping();
            }
            catch(Ice.LocalException)
            {
                test(false);
            }

            Thread.Sleep(10);
            configuration.writeException(new Ice.SocketException());
            try
            {
                background.op();
            }
            catch(Ice.LocalException)
            {
            }
            configuration.writeException(null);

            Thread.Sleep(10);

            background.ice_ping();
            background.ice_getCachedConnection().close(true);
            Thread.Sleep(10);

            background.ice_getCachedConnection().close(true);
        }

        thread1.destroy();
        thread2.destroy();

        thread1.Join();
        thread2.Join();
    }
}
