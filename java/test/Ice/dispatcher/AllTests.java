// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.dispatcher;

import java.io.PrintWriter;

import test.Ice.dispatcher.Test.TestIntfPrx;
import test.Ice.dispatcher.Test.TestIntfPrxHelper;
import test.Ice.dispatcher.Test.TestIntfControllerPrx;
import test.Ice.dispatcher.Test.TestIntfControllerPrxHelper;
import test.Ice.dispatcher.Test.Callback_TestIntf_op;
import test.Ice.dispatcher.Test.Callback_TestIntf_opWithPayload;

public class AllTests
{
    private static abstract class OpCallback extends Callback_TestIntf_op
    {
        OpCallback()
        {
            _called = false;
        }

        public synchronized void check()
        {
            while(!_called)
            {
                try
                {
                    wait();
                }
                catch(InterruptedException ex)
                {
                }
            }

            _called = false;
        }

        public synchronized void called()
        {
            assert(!_called);
            _called = true;
            notify();
        }

        private boolean _called;
    }

    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    public static void
    allTests(Ice.Communicator communicator, PrintWriter out, final Dispatcher dispatcher)
    {
        String sref = "test:default -p 12010";
        Ice.ObjectPrx obj = communicator.stringToProxy(sref);
        test(obj != null);

        TestIntfPrx p = TestIntfPrxHelper.uncheckedCast(obj);

        sref = "testController:tcp -p 12011";
        obj = communicator.stringToProxy(sref);
        test(obj != null);

        TestIntfControllerPrx testController = TestIntfControllerPrxHelper.uncheckedCast(obj);

        out.print("testing dispatcher... ");
        out.flush();
        {
            p.op();

            OpCallback cb = new OpCallback()
                {
                    public void
                    response()
                    {
                        test(dispatcher.isDispatcherThread());
                        called();
                    }

                    public void
                    exception(Ice.LocalException ex)
                    {
                        ex.printStackTrace();
                        test(false);
                    }
                };
            p.begin_op(cb);
            cb.check();

            TestIntfPrx i = (TestIntfPrx)p.ice_adapterId("dummy");
            cb = new OpCallback()
                {
                    public void
                    response()
                    {
                        test(false);
                    }

                    public void
                    exception(Ice.LocalException ex)
                    {
                        test(ex instanceof Ice.NoEndpointException);
                        test(dispatcher.isDispatcherThread());
                        called();
                    }
                };
            i.begin_op(cb);
            cb.check();

            testController.holdAdapter();
            Callback_TestIntf_opWithPayload callback = new Callback_TestIntf_opWithPayload()
                {
                    public void
                    response()
                    {
                        test(dispatcher.isDispatcherThread());
                    }

                    public void
                    exception(Ice.LocalException ex)
                    {
                        test(ex instanceof Ice.CommunicatorDestroyedException);
                    }

                    public void
                    sent(boolean sentSynchronously)
                    {
                        test(sentSynchronously || dispatcher.isDispatcherThread());
                    }
                };

            byte[] seq = new byte[10 * 1024];
            new java.util.Random().nextBytes(seq); // Make sure the request doesn't compress too well.
            Ice.AsyncResult r;
            while((r = p.begin_opWithPayload(seq, callback)).sentSynchronously());
            testController.resumeAdapter();
            r.waitForCompleted();
        }
        out.println("ok");

        p.shutdown();
    }
}
