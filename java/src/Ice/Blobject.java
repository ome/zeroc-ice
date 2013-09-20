// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

/**
 * Base class for dynamic dispatch servants. A server application
 * derives a concrete servant class from <code>Blobject</code> that
 * implements the {@link Blobject#ice_invoke} method.
 **/
public abstract class Blobject extends Ice.ObjectImpl
{
    /**
     * Dispatch an incoming request.
     *
     * @param inEncaps The encoded in-parameters for the operation.
     * @param outEncaps The encoded out-paramaters and return value
     * for the operation. The return value follows any out-parameters.
     * @param current The Current object to pass to the operation.
     * @return If the operation completed successfully, the return value
     * is <code>true</code>. If the operation raises a user exception,
     * the return value is <code>false</code>; in this case, <code>outEncaps</code>
     * must contain the encoded user exception. If the operation raises an
     * Ice run-time exception, it must throw it directly.
     **/
    public abstract boolean
    ice_invoke(byte[] inEncaps, ByteSeqHolder outEncaps, Current current);

    public DispatchStatus
    __dispatch(IceInternal.Incoming in, Current current)
    {
        byte[] inEncaps;
        ByteSeqHolder outEncaps = new ByteSeqHolder();
        inEncaps = in.readParamEncaps();
        boolean ok = ice_invoke(inEncaps, outEncaps, current);
        in.__writeParamEncaps(outEncaps.value, ok);
        if(ok)
        {
            return DispatchStatus.DispatchOK;
        }
        else
        {
            return DispatchStatus.DispatchUserException;
        }
    }
}
