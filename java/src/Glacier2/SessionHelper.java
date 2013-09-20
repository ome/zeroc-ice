// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Glacier2;

/**
 * A helper class for using Glacier2 with GUI applications.
 */
public class SessionHelper
{
    private class SessionRefreshThread extends Thread
    {
        SessionRefreshThread(Glacier2.RouterPrx router, long period)
        {
            _router = router;
            _period = period;
            _done = false;
        }

        synchronized public void
        run()
        {
            while(true)
            {
                try
                {
                    _router.begin_refreshSession(new Glacier2.Callback_Router_refreshSession()
                    {
                        public void response()
                        {
                        }

                        public void exception(Ice.LocalException ex)
                        {
                            done();
                            SessionHelper.this.destroy();
                        }

                        public void exception(Ice.UserException ex)
                        {
                            done();
                            SessionHelper.this.destroy();
                        }
                    });
                }
                catch(Ice.CommunicatorDestroyedException ex)
                {
                    //
                    // AMI requests can raise CommunicatorDestroyedException directly.
                    //
                    break;
                }

                if(!_done)
                {
                    try
                    {
                        wait(_period);
                    }
                    catch(InterruptedException ex)
                    {
                    }
                }

                if(_done)
                {
                    break;
                }
            }
        }

        synchronized public void
        done()
        {
            if(!_done)
            {
                _done = true;
                notify();
            }
        }

        private final Glacier2.RouterPrx _router;
        private final long _period;
        private boolean _done = false;
    }

    /**
     * Creates a Glacier2 session.
     *
     * @param callback The callback for notifications about session establishment.
     * @param initData The {@link Ice.InitializationData} for initializing the communicator.
     */
    public SessionHelper(SessionCallback callback, Ice.InitializationData initData)
    {
        _callback = callback;
        _initData = initData;
    }

    /**
     * Destroys the Glacier2 session.
     * 
     * Once the session has been destroyed, {@link SessionCallback.disconnected} is called on
     * the associated callback object.
     */
    public void
    destroy()
    {
        synchronized(this)
        {
            if(_destroy)
            {
                return;
            }
            _destroy = true;
            if(!_connected)
            {
                //
                // In this case a connecting session is being
                // destroyed. The communicator and session will be
                // destroyed when the connection establishment has
                // completed.
                //
                return;
            }
            _session = null;
            _connected = false;

            try
            {
                Runtime.getRuntime().removeShutdownHook(_shutdownHook);
            }
            catch(IllegalStateException ex)
            {
                // Ignore
            }
            catch(SecurityException ex)
            {
                // Ignore
            }
        }

        //
        // Run the destroyInternal in a thread. This is because it
        // destroyInternal makes remote invocations.
        //
        new Thread(new Runnable()
        {
            public void run()
            {
                destroyInternal();
            }
        }).start();
    }

    /**
     * Returns the session's communicator object.
     * @return The communicator.
     */
    synchronized public Ice.Communicator
    communicator()
    {
        return _communicator;
    }

    /**
     * Returns the category to be used in the identities of all of the client's
     * callback objects. Clients must use this category for the router to
     * forward callback requests to the intended client.
     * @return The category.
     * @throws SessionNotExistException No session exists.
     **/
    synchronized public String
    categoryForClient()
        throws SessionNotExistException
    {
        if(_router == null)
        {
            throw new SessionNotExistException();
        }
        
        return _category;
    }

    /**
     * Adds a servant to the callback object adapter's Active Servant Map with a UUID.
     * @param servant The servant to add.
     * @return The proxy for the servant.
     * @throws SessionNotExistException No session exists.
     **/
    synchronized public Ice.ObjectPrx
    addWithUUID(Ice.Object servant)
        throws SessionNotExistException
    {
        if(_router == null)
        {
            throw new SessionNotExistException();
        }
        return internalObjectAdapter().add(servant, new Ice.Identity(java.util.UUID.randomUUID().toString(),
                                                                     _category));
    }
    
    /**
     * Returns the Glacier2 session proxy. If the session hasn't been established yet, 
     * or the session has already been destroyed, throws SessionNotExistException.
     * @return The session proxy, or throws SessionNotExistException if no session exists.
     * @throws SessionNotExistException No session exists.
     */
    synchronized public Glacier2.SessionPrx
    session()
        throws SessionNotExistException
    {
        if(_session == null)
        {
            throw new SessionNotExistException();
        }

        return _session;
    }

    /**
     * Returns true if there is an active session, otherwise returns false.
     * @return <code>true</code>if session exists or false if no session exists. 
     */
    synchronized public boolean
    isConnected()
    {
        return _connected;
    }

    /**
     * Creates an object adapter for callback objects.
     * @return The object adapter.
     * @throws SessionNotExistException No session exists.
     */
    synchronized public Ice.ObjectAdapter
    objectAdapter()
        throws SessionNotExistException
    {
        return internalObjectAdapter();
    }

    //
    // Only call this method when the calling thread owns the lock
    //
    private Ice.ObjectAdapter
    internalObjectAdapter()
        throws SessionNotExistException
    {
        if(_router == null)
        {
            throw new SessionNotExistException();
        }
        if(_adapter == null)
        {
            _adapter = _communicator.createObjectAdapterWithRouter("", _router);
            _adapter.activate();
        }
        return _adapter;
    }

    private interface ConnectStrategy
    {
        Glacier2.SessionPrx
        connect(Glacier2.RouterPrx router)
            throws CannotCreateSessionException, PermissionDeniedException;
    }
    
    /**
     * Connects to the Glacier2 router using the associated SSL credentials.
     *
     * Once the connection is established, {@link SessionCallback#connected} is called on the callback object;
     * upon failure, {@link SessionCallback#exception} is called with the exception.
     *
     * @param context The request context to use when creating the session.
     */
    synchronized protected void
    connect(final java.util.Map<String, String> context)
    {
        connectImpl(new ConnectStrategy()
                            {
                                public SessionPrx connect(RouterPrx router)
                                    throws CannotCreateSessionException, PermissionDeniedException
                                {
                                    return router.createSessionFromSecureConnection(context);
                                }
                            });
    }

    /**
     * Connects a Glacier2 session using user name and password credentials.
     *
     * Once the connection is established, {@link SessionCallback#connected} is called on the callback object;
     * upon failure {@link SessionCallback.exception} is called with the exception. 
     * 
     * @param username The user name.
     * @param password The password.
     * @param context The request context to use when creating the session.
     */
    synchronized protected void
    connect(final String username, final String password, final java.util.Map<String, String> context)
    {
        connectImpl(new ConnectStrategy()
                            {
                                public SessionPrx connect(RouterPrx router)
                                    throws CannotCreateSessionException, PermissionDeniedException
                                {
                                    return router.createSession(username, password, context);
                                }
                            });
    }

    private void
    connected(RouterPrx router, SessionPrx session)
    {
        Ice.Connection conn = router.ice_getCachedConnection();
        long timeout = router.getSessionTimeout();
        String category = router.getCategoryForClient();

        synchronized(this)
        {
            _router = router;

            if(_destroy)
            {
                //
                // Run the destroyInternal in a thread. This is because it
                // destroyInternal makes remote invocations.
                //
                new Thread(new Runnable()
                {
                    public void run()
                    {
                        destroyInternal();
                    }
                }).start();
                return;
            }

            //
            // Cache the category.
            //
            _category = category;

            //
            // Assign the session after _destroy is checked.
            //
            _session = session;
            _connected = true;

            assert _refreshThread == null;
            if(timeout > 0)
            {
                _refreshThread = new SessionRefreshThread(_router, (timeout * 1000)/2);
                _refreshThread.start();
            }

            _shutdownHook = new Thread("Shutdown hook")
            {
                public void run()
                {
                    SessionHelper.this.destroy();
                }
            };

            try
            {
                Runtime.getRuntime().addShutdownHook(_shutdownHook);
            }
            catch(IllegalStateException e)
            {
                //
                // Shutdown in progress, ignored
                //
            }
            catch(SecurityException ex)
            {
                //
                // Ignore. Unsigned applets cannot registered shutdown hooks.
                //
            }
        }

        dispatchCallback(new Runnable()
            {
                public void run()
                {
                    try
                    {
                        _callback.connected(SessionHelper.this);
                    }
                    catch(SessionNotExistException ex)
                    {
                        SessionHelper.this.destroy();
                    }
                }
            }, conn);
    }

    private void
    destroyInternal()
    {
        assert _destroy;
        Glacier2.RouterPrx router = null;
        Ice.Communicator communicator = null;
        SessionRefreshThread refreshThread = null;
        synchronized(this)
        {
            if(_router == null)
            {
                return;
            }

            router = _router;
            _router = null;

            refreshThread = _refreshThread;
            _refreshThread = null;

            communicator = _communicator;
            _communicator = null;
        }

        assert communicator != null;

        try
        {
            router.destroySession();
        }
        catch(Ice.ConnectionLostException e)
        {
            //
            // Expected if another thread invoked on an object from the session concurrently.
            //
        }
        catch(SessionNotExistException e)
        {
            //
            // This can also occur.
            //
        }
        catch(Throwable e)
        {
            //
            // Not expected.
            //
            communicator.getLogger().warning("SessionHelper: unexpected exception when destroying the session:\n" + e);
        }

        if(refreshThread != null)
        {
            refreshThread.done();
            while(true)
            {
                try
                {
                    refreshThread.join();
                    break;
                }
                catch(InterruptedException e)
                {
                }
            }
        }

        try
        {
            communicator.destroy();
        }
        catch(Throwable ex)
        {
        }

        //
        // Notify the callback that the session is gone.
        //
        dispatchCallback(new Runnable()
        {
            public void run()
            {
                _callback.disconnected(SessionHelper.this);
            }
        }, null);
    }
    
    private void
    connectImpl(final ConnectStrategy factory)
    {
        assert !_destroy;

        try
        {
            _communicator = Ice.Util.initialize(_initData);
        }
        catch(final Ice.LocalException ex)
        {
            _destroy = true;
            new Thread(new Runnable()
                {
                    public void run()
                    {
                        dispatchCallback(new Runnable()
                        {
                            public void run()
                            {
                                _callback.connectFailed(SessionHelper.this, ex);
                            }
                        }, null);
                    }
                }).start();
            return;
        }

        new Thread(new Runnable()
        {
            public void run()
            {
                try
                {
                    dispatchCallbackAndWait(new Runnable()
                    {
                        public void run()
                        {
                            _callback.createdCommunicator(SessionHelper.this);
                        }
                    });

                    Glacier2.RouterPrx routerPrx = Glacier2.RouterPrxHelper.uncheckedCast(
                        _communicator.getDefaultRouter());
                    Glacier2.SessionPrx session = factory.connect(routerPrx);
                    connected(routerPrx, session);
                }
                catch(final Exception ex)
                {
                    try
                    {
                        _communicator.destroy();
                        _communicator = null;
                    }
                    catch(Throwable ex1)
                    {
                    }

                    dispatchCallback(new Runnable()
                    {
                        public void run()
                        {
                            _callback.connectFailed(SessionHelper.this, ex);
                        }
                    }, null);
                }
            }
        }).start();
    }

    private void
    dispatchCallback(Runnable runnable, Ice.Connection conn)
    {
        if(_initData.dispatcher != null)
        {
            _initData.dispatcher.dispatch(runnable, conn);
        }
        else
        {
            runnable.run();
        }
    }

    private void
    dispatchCallbackAndWait(final Runnable runnable)
    {
        if(_initData.dispatcher != null)
        {
            final java.util.concurrent.Semaphore sem = new java.util.concurrent.Semaphore(0);
            _initData.dispatcher.dispatch(
                new Runnable()
                {
                    public void 
                    run()
                    {
                        runnable.run();
                        sem.release();
                    }
                }, null);
            sem.acquireUninterruptibly();
        }
        else
        {
            runnable.run();
        }
    }

    private final Ice.InitializationData _initData;
    private Ice.Communicator _communicator;
    private Ice.ObjectAdapter _adapter;
    private Glacier2.RouterPrx _router;
    private Glacier2.SessionPrx _session;
    private String _category;

    private SessionRefreshThread _refreshThread;
    private final SessionCallback _callback;
    private boolean _destroy = false;
    private boolean _connected = false;
    private Thread _shutdownHook;
}
