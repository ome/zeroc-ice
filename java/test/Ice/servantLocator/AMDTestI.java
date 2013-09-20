// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.servantLocator;

import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_asyncException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_asyncResponse;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_impossibleException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_intfUserException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_javaException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_localException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_requestFailedException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_shutdown;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_unknownException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_unknownLocalException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_unknownUserException;
import test.Ice.servantLocator.AMD.Test.AMD_TestIntf_unknownExceptionWithServantException;
import test.Ice.servantLocator.AMD.Test.TestImpossibleException;
import test.Ice.servantLocator.AMD.Test.TestIntfUserException;
import test.Ice.servantLocator.AMD.Test._TestIntfDisp;

public final class AMDTestI extends _TestIntfDisp
{
    public void 
    requestFailedException_async(AMD_TestIntf_requestFailedException cb, Ice.Current current)
    {
        cb.ice_response();
    }

    public void 
    unknownUserException_async(AMD_TestIntf_unknownUserException cb, Ice.Current current)
    {
        cb.ice_response();
    }

    public void 
    unknownLocalException_async(AMD_TestIntf_unknownLocalException cb, Ice.Current current)
    {
        cb.ice_response();
    }

    public void 
    unknownException_async(AMD_TestIntf_unknownException cb, Ice.Current current)
    {
        cb.ice_response();
    }

    public void 
    localException_async(AMD_TestIntf_localException cb, Ice.Current current)
    {
        cb.ice_response();
    }

//     public void 
//     userException_async(AMD_TestIntf_userException cb, Ice.Current current)
//     {
//        cb.ice_response();
//     }

    public void 
    javaException_async(AMD_TestIntf_javaException cb, Ice.Current current)
    {
        cb.ice_response();
    }

    public void 
    unknownExceptionWithServantException_async(AMD_TestIntf_unknownExceptionWithServantException cb, 
                                               Ice.Current current)
    {
        cb.ice_exception(new Ice.ObjectNotExistException());
    }

    public void
    impossibleException_async(AMD_TestIntf_impossibleException cb, boolean _throw, Ice.Current current)
    {
        if(_throw)
        {
            cb.ice_exception(new TestImpossibleException());
        }
        else
        {
            //
            // Return a value so we can be sure that the stream position
            // is reset correctly if finished() throws.
            //
            cb.ice_response("Hello");
        }
    }

    public void
    intfUserException_async(AMD_TestIntf_intfUserException cb, boolean _throw, Ice.Current current)
    {
        if(_throw)
        {
            cb.ice_exception(new TestIntfUserException());
        }
        else
        {
            //
            // Return a value so we can be sure that the stream position
            // is reset correctly if finished() throws.
            //
            cb.ice_response("Hello");
        }
    }

    public void
    asyncResponse_async(AMD_TestIntf_asyncResponse cb, Ice.Current current)
    {
        cb.ice_response();
        throw new Ice.ObjectNotExistException();
    }

    public void
    asyncException_async(AMD_TestIntf_asyncException cb, Ice.Current current)
    {
        cb.ice_exception(new TestIntfUserException());
        throw new Ice.ObjectNotExistException();
    }
    
    public void
    shutdown_async(AMD_TestIntf_shutdown cb, Ice.Current current)
    {
        current.adapter.getCommunicator().shutdown();
        cb.ice_response();
    }
}
