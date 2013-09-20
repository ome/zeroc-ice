// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

public class IncomingAsync extends IncomingBase implements Ice.AMDCallback
{
    public
    IncomingAsync(Incoming in) // Adopts the argument. It must not be used afterwards.
    {
        super(in);
        _retriable = in.isRetriable();

        if(_retriable)
        {
            in.setActive(this);
            _active = true;
        }
    }

    public void
    ice_exception(java.lang.Exception ex)
    {
        //
        // Only call __exception if this incoming is not retriable or if
        // all the interceptors return true and no response has been sent
        // yet.
        //

        if(_retriable)
        {
            try
            {
                if(_interceptorAsyncCallbackList != null)
                {
                    for(Ice.DispatchInterceptorAsyncCallback cb : _interceptorAsyncCallbackList)
                    {
                        if(cb.exception(ex) == false)
                        {
                            return;
                        }
                    }
                }
            }
            catch(java.lang.RuntimeException exc)
            {
                return;
            }
    
            synchronized(this)
            {
                if(!_active)
                {
                    return;
                }
                _active = false;
            }
        }

        if(_connection != null)
        {
            __exception(ex);
        }
        else
        {
            //
            // Response has already been sent.
            //
            if(_instance.initializationData().properties.getPropertyAsIntWithDefault("Ice.Warn.Dispatch", 1) > 0)
            {
                __warning(ex);
            }
        }
    }

    final void
    __deactivate(Incoming in)
    {
        assert _retriable;

        synchronized(this)
        {
            if(!_active)
            {
                //
                // Since _deactivate can only be called on an active object,
                // this means the response has already been sent (see __validateXXX below)
                //
                throw new Ice.ResponseSentException();
            }
            _active = false;
        }

        in.adopt(this);
    }

    final protected void
    __response()
    {
        try
        {
            if(_locator != null && !__servantLocatorFinished())
            {
                return;
            }

            assert(_connection != null);

            if(_response)
            {
                if(_observer != null)
                {
                    _observer.reply(_os.size() - Protocol.headerSize - 4);
                }
                _connection.sendResponse(_os, _compress);
            }
            else
            {
                _connection.sendNoResponse();
            }

            if(_observer != null)
            {
                _observer.detach();
                _observer = null;
            }
            _connection = null;
        }
        catch(Ice.LocalException ex)
        {
            _connection.invokeException(ex, 1);
        }
    }

    final protected void
    __exception(java.lang.Exception exc)
    {
        try
        {
            if(_locator != null && !__servantLocatorFinished())
            {
                return;
            }

            __handleException(exc);
        }
        catch(Ice.LocalException ex)
        {
            _connection.invokeException(ex, 1);
        }
    }

    final protected boolean
    __validateResponse(boolean ok)
    {
        //
        // Only returns true if this incoming is not retriable or if all
        // the interceptors return true and no response has been sent
        // yet. Upon getting a true return value, the caller should send
        // the response.
        //

        if(_retriable)
        {
            try
            {
                if(_interceptorAsyncCallbackList != null)
                {
                    for(Ice.DispatchInterceptorAsyncCallback cb : _interceptorAsyncCallbackList)
                    {
                        if(cb.response(ok) == false)
                        {
                            return false;
                        }
                    }
                }
            }
            catch(java.lang.RuntimeException ex)
            {
                return false;
            }

            synchronized(this)
            {
                if(!_active)
                {
                    return false;
                }
                _active = false;
            }
        }
        return true;
    }

    private final boolean _retriable;
    private boolean _active = false; // only meaningful when _retriable == true
}
