// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.exceptions;

import java.io.PrintWriter;

import test.Ice.exceptions.Test.A;
import test.Ice.exceptions.Test.AMI_Thrower_throwAasA;
import test.Ice.exceptions.Test.AMI_Thrower_throwAorDasAorD;
import test.Ice.exceptions.Test.AMI_Thrower_throwAssertException;
import test.Ice.exceptions.Test.AMI_Thrower_throwBasA;
import test.Ice.exceptions.Test.AMI_Thrower_throwBasB;
import test.Ice.exceptions.Test.AMI_Thrower_throwCasA;
import test.Ice.exceptions.Test.AMI_Thrower_throwCasB;
import test.Ice.exceptions.Test.AMI_Thrower_throwCasC;
import test.Ice.exceptions.Test.AMI_Thrower_throwLocalException;
import test.Ice.exceptions.Test.AMI_Thrower_throwLocalExceptionIdempotent;
import test.Ice.exceptions.Test.AMI_Thrower_throwNonIceException;
import test.Ice.exceptions.Test.AMI_Thrower_throwUndeclaredA;
import test.Ice.exceptions.Test.AMI_Thrower_throwUndeclaredB;
import test.Ice.exceptions.Test.AMI_Thrower_throwUndeclaredC;
import test.Ice.exceptions.Test.AMI_WrongOperation_noSuchOperation;
import test.Ice.exceptions.Test.B;
import test.Ice.exceptions.Test.C;
import test.Ice.exceptions.Test.D;
import test.Ice.exceptions.Test.ThrowerPrx;
import test.Ice.exceptions.Test.ThrowerPrxHelper;
import test.Ice.exceptions.Test.WrongOperationPrx;
import test.Ice.exceptions.Test.WrongOperationPrxHelper;
import test.Ice.exceptions.Test.Callback_Thrower_throwAasA;
import test.Ice.exceptions.Test.Callback_Thrower_throwAorDasAorD;
import test.Ice.exceptions.Test.Callback_Thrower_throwAssertException;
import test.Ice.exceptions.Test.Callback_Thrower_throwBasA;
import test.Ice.exceptions.Test.Callback_Thrower_throwBasB;
import test.Ice.exceptions.Test.Callback_Thrower_throwCasA;
import test.Ice.exceptions.Test.Callback_Thrower_throwCasB;
import test.Ice.exceptions.Test.Callback_Thrower_throwCasC;
import test.Ice.exceptions.Test.Callback_Thrower_throwLocalException;
import test.Ice.exceptions.Test.Callback_Thrower_throwLocalExceptionIdempotent;
import test.Ice.exceptions.Test.Callback_Thrower_throwNonIceException;
import test.Ice.exceptions.Test.Callback_Thrower_throwUndeclaredA;
import test.Ice.exceptions.Test.Callback_Thrower_throwUndeclaredB;
import test.Ice.exceptions.Test.Callback_Thrower_throwUndeclaredC;
import test.Ice.exceptions.Test.Callback_WrongOperation_noSuchOperation;

public class AllTests
{
    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    private static class Callback
    {
        Callback()
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

    private static class AMI_Thrower_throwAasAI extends AMI_Thrower_throwAasA
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(A ex)
            {
                test(ex.aMem == 1);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwAasAObjectNotExistI extends AMI_Thrower_throwAasA
    {
        AMI_Thrower_throwAasAObjectNotExistI(Ice.Communicator communicator)
        {
            _communicator = communicator;
        }

        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.ObjectNotExistException ex)
            {
                Ice.Identity id = _communicator.stringToIdentity("does not exist");
                test(ex.id.equals(id));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
        private Ice.Communicator _communicator;
    }

    private static class AMI_Thrower_throwAasAFacetNotExistI extends AMI_Thrower_throwAasA
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.FacetNotExistException ex)
            {
                test(ex.facet.equals("no such facet"));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwAorDasAorDI extends AMI_Thrower_throwAorDasAorD
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(A ex)
            {
                test(ex.aMem == 1);
            }
            catch(D ex)
            {
                test(ex.dMem == -1);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwBasAI extends AMI_Thrower_throwBasA
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(B ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwCasAI extends AMI_Thrower_throwCasA
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(C ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
                test(ex.cMem == 3);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwBasBI extends AMI_Thrower_throwBasB
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(B ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwCasBI extends AMI_Thrower_throwCasB
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(C ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
                test(ex.cMem == 3);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwCasCI extends AMI_Thrower_throwCasC
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void ice_exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(C ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
                test(ex.cMem == 3);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwUndeclaredAI extends AMI_Thrower_throwUndeclaredA
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwUndeclaredBI extends AMI_Thrower_throwUndeclaredB
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwUndeclaredCI extends AMI_Thrower_throwUndeclaredC
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwLocalExceptionI extends AMI_Thrower_throwLocalException
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownLocalException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwNonIceExceptionI extends AMI_Thrower_throwNonIceException
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_Thrower_throwAssertExceptionI extends AMI_Thrower_throwAssertException
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.ConnectionLostException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class AMI_WrongOperation_noSuchOperationI extends AMI_WrongOperation_noSuchOperation
    {
        @Override
        public void ice_response()
        {
            test(false);
        }

        @Override
        public void ice_exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.OperationNotExistException ex)
            {
                test(ex.operation.equals("noSuchOperation"));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwAasAI extends Callback_Thrower_throwAasA
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(A ex)
            {
                test(ex.aMem == 1);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwAasAObjectNotExistI extends Callback_Thrower_throwAasA
    {
        Callback_Thrower_throwAasAObjectNotExistI(Ice.Communicator communicator)
        {
            _communicator = communicator;
        }

        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.ObjectNotExistException ex)
            {
                Ice.Identity id = _communicator.stringToIdentity("does not exist");
                test(ex.id.equals(id));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
        private Ice.Communicator _communicator;
    }

    private static class Callback_Thrower_throwAasAFacetNotExistI extends Callback_Thrower_throwAasA
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.FacetNotExistException ex)
            {
                test(ex.facet.equals("no such facet"));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwAorDasAorDI extends Callback_Thrower_throwAorDasAorD
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(A ex)
            {
                test(ex.aMem == 1);
            }
            catch(D ex)
            {
                test(ex.dMem == -1);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwBasAI extends Callback_Thrower_throwBasA
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(B ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwCasAI extends Callback_Thrower_throwCasA
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(C ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
                test(ex.cMem == 3);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwBasBI extends Callback_Thrower_throwBasB
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(B ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwCasBI extends Callback_Thrower_throwCasB
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(C ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
                test(ex.cMem == 3);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwCasCI extends Callback_Thrower_throwCasC
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            exc.printStackTrace();
            test(false);
        }

        @Override
        public void exception(Ice.UserException exc)
        {
            try
            {
                throw exc;
            }
            catch(C ex)
            {
                test(ex.aMem == 1);
                test(ex.bMem == 2);
                test(ex.cMem == 3);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwUndeclaredAI extends Callback_Thrower_throwUndeclaredA
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwUndeclaredBI extends Callback_Thrower_throwUndeclaredB
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwUndeclaredCI extends Callback_Thrower_throwUndeclaredC
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwLocalExceptionI extends Callback_Thrower_throwLocalException
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownLocalException ex)
            {
            }
            catch(Ice.OperationNotExistException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwNonIceExceptionI extends Callback_Thrower_throwNonIceException
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.UnknownException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_Thrower_throwAssertExceptionI extends Callback_Thrower_throwAssertException
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.ConnectionLostException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    private static class Callback_WrongOperation_noSuchOperationI extends Callback_WrongOperation_noSuchOperation
    {
        @Override
        public void response()
        {
            test(false);
        }

        @Override
        public void exception(Ice.LocalException exc)
        {
            try
            {
                throw exc;
            }
            catch(Ice.OperationNotExistException ex)
            {
                test(ex.operation.equals("noSuchOperation"));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            callback.called();
        }

        public void check()
        {
            callback.check();
        }

        private Callback callback = new Callback();
    }

    public static ThrowerPrx
    allTests(Ice.Communicator communicator, boolean collocated, PrintWriter out)
    {
        {
            out.print("testing object adapter registration exceptions... ");
            Ice.ObjectAdapter first;
            try
            {
                first = communicator.createObjectAdapter("TestAdapter0");
            }
            catch(Ice.InitializationException ex)
            {
                // Expected
            }

            communicator.getProperties().setProperty("TestAdapter0.Endpoints", "default");
            first = communicator.createObjectAdapter("TestAdapter0");
            try
            {
                Ice.ObjectAdapter second = communicator.createObjectAdapter("TestAdapter0");
                test(false);
            }
            catch(Ice.AlreadyRegisteredException ex)
            {
                // Expected
            }

            try
            {
                Ice.ObjectAdapter second =
                    communicator.createObjectAdapterWithEndpoints("TestAdapter0", "ssl -h foo -p 12011");
                test(false);
            }
            catch(Ice.AlreadyRegisteredException ex)
            {
                // Expected
            }
            first.deactivate();
            out.println("ok");
        }

        {
            out.print("testing servant registration exceptions... ");
            communicator.getProperties().setProperty("TestAdapter1.Endpoints", "default");
            Ice.ObjectAdapter adapter = communicator.createObjectAdapter("TestAdapter1");
            Ice.Object obj = new EmptyI();
            adapter.add(obj, communicator.stringToIdentity("x"));
            try
            {
                adapter.add(obj, communicator.stringToIdentity("x"));
                test(false);
            }
            catch(Ice.AlreadyRegisteredException ex)
            {
            }

            adapter.remove(communicator.stringToIdentity("x"));
            try
            {
                adapter.remove(communicator.stringToIdentity("x"));
                test(false);
            }
            catch(Ice.NotRegisteredException ex)
            {
            }
            adapter.deactivate();
            out.println("ok");
        }

        {
            out.print("testing servant locator registration exceptions... ");
            communicator.getProperties().setProperty("TestAdapter2.Endpoints", "default");
            Ice.ObjectAdapter adapter = communicator.createObjectAdapter("TestAdapter2");
            Ice.ServantLocator loc = new ServantLocatorI();
            adapter.addServantLocator(loc, "x");
            try
            {
                adapter.addServantLocator(loc, "x");
                test(false);
            }
            catch(Ice.AlreadyRegisteredException ex)
            {
            }

            adapter.deactivate();
            out.println("ok");
        }

        {
            out.print("testing object factory registration exception... ");
            Ice.ObjectFactory of = new ObjectFactoryI();
            communicator.addObjectFactory(of, "::x");
            try
            {
                communicator.addObjectFactory(of, "::x");
                test(false);
            }
            catch(Ice.AlreadyRegisteredException ex)
            {
            }
            out.println("ok");
        }

        out.print("testing stringToProxy... ");
        out.flush();
        String ref = "thrower:default -p 12010";
        Ice.ObjectPrx base = communicator.stringToProxy(ref);
        test(base != null);
        out.println("ok");

        out.print("testing checked cast... ");
        out.flush();
        ThrowerPrx thrower = ThrowerPrxHelper.checkedCast(base);
        test(thrower != null);
        test(thrower.equals(base));
        out.println("ok");

        out.print("catching exact types... ");
        out.flush();

        try
        {
            thrower.throwAasA(1);
            test(false);
        }
        catch(A ex)
        {
            test(ex.aMem == 1);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwAorDasAorD(1);
            test(false);
        }
        catch(A ex)
        {
            test(ex.aMem == 1);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwAorDasAorD(-1);
            test(false);
        }
        catch(D ex)
        {
            test(ex.dMem == -1);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwBasB(1, 2);
            test(false);
        }
        catch(B ex)
        {
            test(ex.aMem == 1);
            test(ex.bMem == 2);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwCasC(1, 2, 3);
            test(false);
        }
        catch(C ex)
        {
            test(ex.aMem == 1);
            test(ex.bMem == 2);
            test(ex.cMem == 3);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        out.println("ok");

        out.print("catching base types... ");
        out.flush();

        try
        {
            thrower.throwBasB(1, 2);
            test(false);
        }
        catch(A ex)
        {
            test(ex.aMem == 1);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwCasC(1, 2, 3);
            test(false);
        }
        catch(B ex)
        {
            test(ex.aMem == 1);
            test(ex.bMem == 2);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        out.println("ok");

        out.print("catching derived types... ");
        out.flush();

        try
        {
            thrower.throwBasA(1, 2);
            test(false);
        }
        catch(B ex)
        {
            test(ex.aMem == 1);
            test(ex.bMem == 2);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwCasA(1, 2, 3);
            test(false);
        }
        catch(C ex)
        {
            test(ex.aMem == 1);
            test(ex.bMem == 2);
            test(ex.cMem == 3);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwCasB(1, 2, 3);
            test(false);
        }
        catch(C ex)
        {
            test(ex.aMem == 1);
            test(ex.bMem == 2);
            test(ex.cMem == 3);
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        out.println("ok");

        if(thrower.supportsUndeclaredExceptions())
        {
            test(!collocated);

            out.print("catching unknown user exception... ");
            out.flush();

            try
            {
                thrower.throwUndeclaredA(1);
                test(false);
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }

            try
            {
                thrower.throwUndeclaredB(1, 2);
                test(false);
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }

            try
            {
                thrower.throwUndeclaredC(1, 2, 3);
                test(false);
            }
            catch(Ice.UnknownUserException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }

            out.println("ok");
        }

        if(thrower.supportsAssertException())
        {
            out.print("testing assert in the server... ");
            out.flush();

            try
            {
                thrower.throwAssertException();
                test(false);
            }
            catch(Ice.ConnectionLostException ex)
            {
                test(!collocated);
            }
            catch(Ice.UnknownException ex)
            {
                test(collocated);
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }

            out.println("ok");
        }

        out.print("testing memory limit marshal exception...");
        out.flush();
        {
            try
            {
                thrower.throwMemoryLimitException(null);
                test(collocated);
            }
            catch(Ice.UnknownLocalException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }

            try
            {
                thrower.throwMemoryLimitException(new byte[20 * 1024]); // 20KB
                test(collocated);
            }
            catch(Ice.MemoryLimitException ex)
            {
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
            
            if(!collocated)
            {
                try
                {
                    thrower.end_throwMemoryLimitException(
                        thrower.begin_throwMemoryLimitException(new byte[20 * 1024])); // 20KB
                    test(false);
                }
                catch(Ice.MemoryLimitException ex)
                {
                }
                catch(Throwable ex)
                {
                    ex.printStackTrace();
                    test(false);
                }
            }
        }
        out.println("ok");

        out.print("catching object not exist exception... ");
        out.flush();

        {
            Ice.Identity id = communicator.stringToIdentity("does not exist");
            try
            {
                ThrowerPrx thrower2 = ThrowerPrxHelper.uncheckedCast(thrower.ice_identity(id));
                thrower2.ice_ping();
                test(false);
            }
            catch(Ice.ObjectNotExistException ex)
            {
                test(ex.id.equals(id));
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }
        }

        out.println("ok");

        out.print("catching facet not exist exception... ");
        out.flush();

        try
        {
            ThrowerPrx thrower2 = ThrowerPrxHelper.uncheckedCast(thrower, "no such facet");
            try
            {
                thrower2.ice_ping();
                test(false);
            }
            catch(Ice.FacetNotExistException ex)
            {
                test(ex.facet.equals("no such facet"));
            }
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        out.println("ok");

        out.print("catching operation not exist exception... ");
        out.flush();

        try
        {
            WrongOperationPrx thrower2 = WrongOperationPrxHelper.uncheckedCast(thrower);
            thrower2.noSuchOperation();
            test(false);
        }
        catch(Ice.OperationNotExistException ex)
        {
            test(ex.operation.equals("noSuchOperation"));
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        out.println("ok");

        out.print("catching unknown local exception... ");
        out.flush();

        try
        {
            thrower.throwLocalException();
            test(false);
        }
        catch(Ice.UnknownLocalException ex)
        {
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        try
        {
            thrower.throwLocalExceptionIdempotent();
            test(false);
        }
        catch(Ice.UnknownLocalException ex)
        {
        }
        catch(Ice.OperationNotExistException ex)
        {
        }
        catch(Throwable ex)
        {
            ex.printStackTrace();
            test(false);
        }

        out.println("ok");

        out.print("catching unknown non-Ice exception... ");
        out.flush();

        try
        {
            thrower.throwNonIceException();
            test(false);
        }
        catch(Ice.UnknownException ex)
        {
        }
        catch(Throwable ex)
        {
            out.println(ex);
            test(false);
        }

        out.println("ok");

        out.print("testing asynchronous exceptions... ");
        out.flush();

        try
        {
            thrower.throwAfterResponse();
        }
        catch(Ice.LocalException ex)
        {
            test(false);
        }
        catch(Throwable ex)
        {
            out.println(ex);
            test(false);
        }

        try
        {
            thrower.throwAfterException();
            test(false);
        }
        catch(A ex)
        {
        }
        catch(Ice.LocalException ex)
        {
            test(false);
        }
        catch(Throwable ex)
        {
            out.println(ex);
            test(false);
        }

        out.println("ok");

        if(!collocated)
        {
            out.print("catching exact types with AMI... ");
            out.flush();

            {
                AMI_Thrower_throwAasAI cb = new AMI_Thrower_throwAasAI();
                thrower.throwAasA_async(cb, 1);
                cb.check();
                // Let's check if we can reuse the same callback object for another call.
                thrower.throwAasA_async(cb, 1);
                cb.check();
            }

            {
                AMI_Thrower_throwAorDasAorDI cb = new AMI_Thrower_throwAorDasAorDI();
                thrower.throwAorDasAorD_async(cb, 1);
                cb.check();
            }

            {
                AMI_Thrower_throwAorDasAorDI cb = new AMI_Thrower_throwAorDasAorDI();
                thrower.throwAorDasAorD_async(cb, -1);
                cb.check();
            }

            {
                AMI_Thrower_throwBasBI cb = new AMI_Thrower_throwBasBI();
                thrower.throwBasB_async(cb, 1, 2);
                cb.check();
            }

            {
                AMI_Thrower_throwCasCI cb = new AMI_Thrower_throwCasCI();
                thrower.throwCasC_async(cb, 1, 2, 3);
                cb.check();
                // Let's check if we can reuse the same callback object for another call.
                thrower.throwCasC_async(cb, 1, 2, 3);
                cb.check();
            }

            out.println("ok");

            out.print("catching derived types with AMI... ");
            out.flush();

            {
                AMI_Thrower_throwBasAI cb = new AMI_Thrower_throwBasAI();
                thrower.throwBasA_async(cb, 1, 2);
                cb.check();
            }

            {
                AMI_Thrower_throwCasAI cb = new AMI_Thrower_throwCasAI();
                thrower.throwCasA_async(cb, 1, 2, 3);
                cb.check();
            }

            {
                AMI_Thrower_throwCasBI cb = new AMI_Thrower_throwCasBI();
                thrower.throwCasB_async(cb, 1, 2, 3);
                cb.check();
            }

            out.println("ok");

            if(thrower.supportsUndeclaredExceptions())
            {
                out.print("catching unknown user exception with AMI... ");
                out.flush();

                {
                    AMI_Thrower_throwUndeclaredAI cb = new AMI_Thrower_throwUndeclaredAI();
                    thrower.throwUndeclaredA_async(cb, 1);
                    cb.check();
                }

                {
                    AMI_Thrower_throwUndeclaredBI cb = new AMI_Thrower_throwUndeclaredBI();
                    thrower.throwUndeclaredB_async(cb, 1, 2);
                    cb.check();
                }

                {
                    AMI_Thrower_throwUndeclaredCI cb = new AMI_Thrower_throwUndeclaredCI();
                    thrower.throwUndeclaredC_async(cb, 1, 2, 3);
                    cb.check();
                }

                out.println("ok");
            }

            if(thrower.supportsAssertException())
            {
                out.print("testing assert in the server with AMI... ");
                out.flush();

                AMI_Thrower_throwAssertExceptionI cb = new AMI_Thrower_throwAssertExceptionI();
                thrower.throwAssertException_async(cb);
                cb.check();

                out.println("ok");
            }

            out.print("catching object not exist exception with AMI... ");
            out.flush();

            {
                Ice.Identity id = communicator.stringToIdentity("does not exist");
                ThrowerPrx thrower2 = ThrowerPrxHelper.uncheckedCast(thrower.ice_identity(id));
                AMI_Thrower_throwAasAObjectNotExistI cb = new AMI_Thrower_throwAasAObjectNotExistI(communicator);
                thrower2.throwAasA_async(cb, 1);
                cb.check();
            }

            out.println("ok");

            out.print("catching facet not exist exception with AMI... ");
            out.flush();

            try
            {
                ThrowerPrx thrower2 = ThrowerPrxHelper.uncheckedCast(thrower, "no such facet");
                {
                    AMI_Thrower_throwAasAFacetNotExistI cb = new AMI_Thrower_throwAasAFacetNotExistI();
                    thrower2.throwAasA_async(cb, 1);
                    cb.check();
                }
            }
            catch(Throwable ex)
            {
                ex.printStackTrace();
                test(false);
            }

            out.println("ok");

            out.print("catching operation not exist exception with AMI... ");
            out.flush();

            {
                AMI_WrongOperation_noSuchOperationI cb = new AMI_WrongOperation_noSuchOperationI();
                WrongOperationPrx thrower2 = WrongOperationPrxHelper.uncheckedCast(thrower);
                thrower2.noSuchOperation_async(cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching unknown local exception with AMI... ");
            out.flush();

            {
                AMI_Thrower_throwLocalExceptionI cb = new AMI_Thrower_throwLocalExceptionI();
                thrower.throwLocalException_async(cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching unknown non-Ice exception with AMI... ");
            out.flush();

            {
                AMI_Thrower_throwNonIceExceptionI cb = new AMI_Thrower_throwNonIceExceptionI();
                thrower.throwNonIceException_async(cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching exact types with new AMI mapping... ");
            out.flush();

            {
                Callback_Thrower_throwAasAI cb = new Callback_Thrower_throwAasAI();
                thrower.begin_throwAasA(1, cb);
                cb.check();
            }

            {
                Callback_Thrower_throwAorDasAorDI cb = new Callback_Thrower_throwAorDasAorDI();
                thrower.begin_throwAorDasAorD(1, cb);
                cb.check();
            }

            {
                Callback_Thrower_throwAorDasAorDI cb = new Callback_Thrower_throwAorDasAorDI();
                thrower.begin_throwAorDasAorD(-1, cb);
                cb.check();
            }

            {
                Callback_Thrower_throwBasBI cb = new Callback_Thrower_throwBasBI();
                thrower.begin_throwBasB(1, 2, cb);
                cb.check();
            }

            {
                Callback_Thrower_throwCasCI cb = new Callback_Thrower_throwCasCI();
                thrower.begin_throwCasC(1, 2, 3, cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching derived types with new AMI mapping... ");
            out.flush();

            {
                Callback_Thrower_throwBasAI cb = new Callback_Thrower_throwBasAI();
                thrower.begin_throwBasA(1, 2, cb);
                cb.check();
            }

            {
                Callback_Thrower_throwCasAI cb = new Callback_Thrower_throwCasAI();
                thrower.begin_throwCasA(1, 2, 3, cb);
                cb.check();
            }

            {
                Callback_Thrower_throwCasBI cb = new Callback_Thrower_throwCasBI();
                thrower.begin_throwCasB(1, 2, 3, cb);
                cb.check();
            }

            out.println("ok");

            if(thrower.supportsUndeclaredExceptions())
            {
                out.print("catching unknown user exception with new AMI mapping... ");
                out.flush();

                {
                    Callback_Thrower_throwUndeclaredAI cb = new Callback_Thrower_throwUndeclaredAI();
                    thrower.begin_throwUndeclaredA(1, cb);
                    cb.check();
                }

                {
                    Callback_Thrower_throwUndeclaredBI cb = new Callback_Thrower_throwUndeclaredBI();
                    thrower.begin_throwUndeclaredB(1, 2, cb);
                    cb.check();
                }

                {
                    Callback_Thrower_throwUndeclaredCI cb = new Callback_Thrower_throwUndeclaredCI();
                    thrower.begin_throwUndeclaredC(1, 2, 3, cb);
                    cb.check();
                }

                out.println("ok");
            }

            out.print("catching object not exist exception with new AMI mapping... ");
            out.flush();

            {
                Ice.Identity id = communicator.stringToIdentity("does not exist");
                ThrowerPrx thrower2 = ThrowerPrxHelper.uncheckedCast(thrower.ice_identity(id));
                AMI_Thrower_throwAasAObjectNotExistI cb = new AMI_Thrower_throwAasAObjectNotExistI(communicator);
                thrower2.begin_throwAasA(1, cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching facet not exist exception with new AMI mapping... ");
            out.flush();

            {
                ThrowerPrx thrower2 = ThrowerPrxHelper.uncheckedCast(thrower, "no such facet");
                Callback_Thrower_throwAasAFacetNotExistI cb = new Callback_Thrower_throwAasAFacetNotExistI();
                thrower2.begin_throwAasA(1, cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching operation not exist exception with new AMI mapping... ");
            out.flush();

            {
                Callback_WrongOperation_noSuchOperationI cb = new Callback_WrongOperation_noSuchOperationI();
                WrongOperationPrx thrower2 = WrongOperationPrxHelper.uncheckedCast(thrower);
                thrower2.begin_noSuchOperation(cb);
                cb.check();
            }

            out.println("ok");

            out.print("catching unknown local exception with new AMI mapping... ");
            out.flush();

            {
                Callback_Thrower_throwLocalExceptionI cb = new Callback_Thrower_throwLocalExceptionI();
                thrower.begin_throwLocalException(cb);
                cb.check();
            }

            {
                final Callback_Thrower_throwLocalExceptionI cb = new Callback_Thrower_throwLocalExceptionI();
                thrower.begin_throwLocalExceptionIdempotent(new Callback_Thrower_throwLocalExceptionIdempotent()
                    {
                        @Override
                        public void response()
                        {
                            cb.response();
                        }

                        @Override
                        public void exception(Ice.LocalException exc)
                        {
                            cb.exception(exc);
                        }
                    });
                cb.check();
            }

            out.println("ok");

            out.print("catching unknown non-Ice exception with new AMI mapping... ");
            out.flush();

            {
                Callback_Thrower_throwNonIceExceptionI cb = new Callback_Thrower_throwNonIceExceptionI();
                thrower.begin_throwNonIceException(cb);
                cb.check();
            }

            out.println("ok");
        }

        return thrower;
    }
}
