// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

public final class ProxyFactory
{
    public Ice.ObjectPrx
    stringToProxy(String str)
    {
        Reference ref = _instance.referenceFactory().create(str, null);
        return referenceToProxy(ref);
    }

    public String
    proxyToString(Ice.ObjectPrx proxy)
    {
        if(proxy != null)
        {
            Ice.ObjectPrxHelperBase h = (Ice.ObjectPrxHelperBase)proxy;
            return h.__reference().toString();
        }
        else
        {
            return "";
        }
    }

    public Ice.ObjectPrx
    propertyToProxy(String prefix)
    {
        String proxy = _instance.initializationData().properties.getProperty(prefix);
        Reference ref = _instance.referenceFactory().create(proxy, prefix);
        return referenceToProxy(ref);
    }

    public java.util.Map<String, String>
    proxyToProperty(Ice.ObjectPrx proxy, String prefix)
    {
        if(proxy != null)
        {
            Ice.ObjectPrxHelperBase h = (Ice.ObjectPrxHelperBase)proxy;
            return h.__reference().toProperty(prefix);
        }
        else
        {
            return new java.util.HashMap<String, String>();
        }
    }

    public Ice.ObjectPrx
    streamToProxy(BasicStream s)
    {
        Ice.Identity ident = new Ice.Identity();
        ident.__read(s);

        Reference ref = _instance.referenceFactory().create(ident, s);
        return referenceToProxy(ref);
    }

    public Ice.ObjectPrx
    referenceToProxy(Reference ref)
    {
        if(ref != null)
        {
            Ice.ObjectPrxHelperBase proxy = new Ice.ObjectPrxHelperBase();
            proxy.setup(ref);
            return proxy;
        }
        else
        {
            return null;
        }
    }

    public void
    proxyToStream(Ice.ObjectPrx proxy, BasicStream s)
    {
        if(proxy != null)
        {
            Ice.ObjectPrxHelperBase h = (Ice.ObjectPrxHelperBase)proxy;
            Reference ref = h.__reference();
            ref.getIdentity().__write(s);
            ref.streamWrite(s);
        }
        else
        {
            Ice.Identity ident = new Ice.Identity();
            ident.name = "";
            ident.category = "";
            ident.__write(s);
        }
    }

    public int
    checkRetryAfterException(Ice.LocalException ex, Reference ref, Ice.IntHolder sleepInterval, int cnt)
    {
        TraceLevels traceLevels = _instance.traceLevels();
        Ice.Logger logger = _instance.initializationData().logger;
        
        //
        // We don't retry batch requests because the exception might have caused
        // the all the requests batched with the connection to be aborted and we
        // want the application to be notified.
        //
        if(ref.getMode() == IceInternal.Reference.ModeBatchOneway ||
           ref.getMode() == IceInternal.Reference.ModeBatchDatagram)
        {
            throw ex;
        }

        if(ex instanceof Ice.ObjectNotExistException)
        {
            Ice.ObjectNotExistException one = (Ice.ObjectNotExistException)ex;

            if(ref.getRouterInfo() != null && one.operation.equals("ice_add_proxy"))
            {
                //
                // If we have a router, an ObjectNotExistException with an
                // operation name "ice_add_proxy" indicates to the client
                // that the router isn't aware of the proxy (for example,
                // because it was evicted by the router). In this case, we
                // must *always* retry, so that the missing proxy is added
                // to the router.
                //

                ref.getRouterInfo().clearCache(ref);

                if(traceLevels.retry >= 1)
                {
                    String s = "retrying operation call to add proxy to router\n" + ex.toString();
                    logger.trace(traceLevels.retryCat, s);
                }

                if(sleepInterval != null)
                {
                    sleepInterval.value = 0;
                }
                return cnt; // We must always retry, so we don't look at the retry count.
            }
            else if(ref.isIndirect())
            {
                //
                // We retry ObjectNotExistException if the reference is
                // indirect.
                //

                if(ref.isWellKnown())
                {
                    LocatorInfo li = ref.getLocatorInfo();
                    if(li != null)
                    {
                        li.clearCache(ref);
                    }
                }
            }
            else
            {
                //
                // For all other cases, we don't retry ObjectNotExistException.
                //
                throw ex;
            }
        }
        else if(ex instanceof Ice.RequestFailedException)
        {
            //
            // For all other cases, we don't retry  ObjectNotExistException
            //
            throw ex;
        }

        //
        // There is no point in retrying an operation that resulted in a
        // MarshalException. This must have been raised locally (because
        // if it happened in a server it would result in an
        // UnknownLocalException instead), which means there was a problem
        // in this process that will not change if we try again.
        //
        // The most likely cause for a MarshalException is exceeding the
        // maximum message size, which is represented by the subclass
        // MemoryLimitException. For example, a client can attempt to send
        // a message that exceeds the maximum memory size, or accumulate
        // enough batch requests without flushing that the maximum size is
        // reached.
        //
        // This latter case is especially problematic, because if we were
        // to retry a batch request after a MarshalException, we would in
        // fact silently discard the accumulated requests and allow new
        // batch requests to accumulate. If the subsequent batched
        // requests do not exceed the maximum message size, it appears to
        // the client that all of the batched requests were accepted, when
        // in reality only the last few are actually sent.
        //
        if(ex instanceof Ice.MarshalException)
        {
            throw ex;
        }

        ++cnt;
        assert(cnt > 0);

        int interval;
        if(cnt == (_retryIntervals.length + 1) && ex instanceof Ice.CloseConnectionException)
        {
            //
            // A close connection exception is always retried at least once, even if the retry
            // limit is reached.
            //
            interval = 0;
        }
        else if(cnt > _retryIntervals.length)
        {
            if(traceLevels.retry >= 1)
            {
                String s = "cannot retry operation call because retry limit has been exceeded\n" + ex.toString();
                logger.trace(traceLevels.retryCat, s);
            }
            throw ex;
        }
        else
        {
            interval = _retryIntervals[cnt - 1];
        }

        if(traceLevels.retry >= 1)
        {
            String s = "retrying operation call";
            if(interval > 0)
            {
                s += " in " + interval + "ms";
            }
            s += " because of exception\n" + ex;
            logger.trace(traceLevels.retryCat, s);
        }

        if(sleepInterval != null)
        {
            sleepInterval.value = interval;
        }
        else if(interval > 0)
        {
            //
            // Sleep before retrying.
            //
            try
            {
                Thread.sleep(interval);
            }
            catch(InterruptedException ex1)
            {
            }
        }
        return cnt;
    }

    //
    // Only for use by Instance.
    //
    ProxyFactory(Instance instance)
    {
        _instance = instance;

        String[] arr = _instance.initializationData().properties.getPropertyAsList("Ice.RetryIntervals");

        if(arr.length > 0)
        {
            _retryIntervals = new int[arr.length];

            for(int i = 0; i < arr.length; i++)
            {
                int v;

                try
                {
                    v = Integer.parseInt(arr[i]);
                }
                catch(NumberFormatException ex)
                {
                    v = 0;
                }

                //
                // If -1 is the first value, no retry and wait intervals.
                // 
                if(i == 0 && v == -1)
                {
                    _retryIntervals = new int[0];
                    break;
                }

                _retryIntervals[i] = v > 0 ? v : 0;
            }
        }
        else
        {
            _retryIntervals = new int[1];
            _retryIntervals[0] = 0;
        }
    }

    private Instance _instance;
    private int[] _retryIntervals;
}
