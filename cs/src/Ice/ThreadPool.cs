// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

namespace IceInternal
{

    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Threading;

    public delegate void ThreadPoolWorkItem();
    public delegate void AsyncCallback(object state);

    internal struct ThreadPoolMessage
    {
        public ThreadPoolMessage(IceUtilInternal.Monitor mutex)
        {
            _mutex = mutex;
            _finish = false;
            _finishWithIO = false;
        }

        public bool startIOScope(ref ThreadPoolCurrent current)
        {
            // This must be called with the handler locked.
            _finishWithIO = current.startMessage();
            return _finishWithIO;
        }
        
        public void finishIOScope(ref ThreadPoolCurrent current)
        {
            if(_finishWithIO)
            {
                // This must be called with the handler locked. 
                current.finishMessage(true);
            }
        }
        
        public void completed(ref ThreadPoolCurrent current)
        {
            //
            // Call finishMessage once IO is completed only if serialization is not enabled.
            // Otherwise, finishMessage will be called when the event handler is done with 
            // the message (it will be called from destroy below).
            //
            Debug.Assert(_finishWithIO);
            if(current.ioCompleted())
            {
                _finishWithIO = false;
                _finish = true;
            }
        }
        
        public void destroy(ref ThreadPoolCurrent current)
        {
            if(_finish)
            {
                //
                // A ThreadPoolMessage instance must be created outside the synchronization
                // of the event handler. We need to lock the event handler here to call 
                // finishMessage.
                //
                _mutex.Lock();
                try
                {
                    current.finishMessage(false);
                    Debug.Assert(!current.completedSynchronously);
                }
                finally
                {
                    _mutex.Unlock();
                }
            }
        }
        
        private IceUtilInternal.Monitor _mutex;
        private bool _finish;
        private bool _finishWithIO;
    }

    public struct ThreadPoolCurrent
    {
        public ThreadPoolCurrent(ThreadPool threadPool, EventHandler handler, int op)
        {
            _threadPool = threadPool;
            _handler = handler;
            operation = op;
            completedSynchronously = false;
        }

        public readonly int operation;
        public bool completedSynchronously;

        public bool ioCompleted()
        {
            return _threadPool.serialize();
        }

        public bool startMessage()
        {
            return _threadPool.startMessage(ref this);
        }

        public void finishMessage(bool fromIOThread)
        {
            _threadPool.finishMessage(ref this, fromIOThread);
        }

        internal readonly ThreadPool _threadPool;
        internal readonly EventHandler _handler;
    }

    public sealed class ThreadPool
    {
        public ThreadPool(Instance instance, string prefix, int timeout)
        {
            _instance = instance;
            _dispatcher = instance.initializationData().dispatcher;
            _destroyed = false;
            _prefix = prefix;
            _threadIndex = 0;
            _inUse = 0;
            _serialize = _instance.initializationData().properties.getPropertyAsInt(_prefix + ".Serialize") > 0;
            _serverIdleTime = timeout;

            Ice.Properties properties = _instance.initializationData().properties;

            string programName = properties.getProperty("Ice.ProgramName");
            if(programName.Length > 0)
            {
                _threadPrefix = programName + "-" + _prefix;
            }
            else
            {
                _threadPrefix = _prefix;
            }

            //
            // We use just one thread as the default. This is the fastest
            // possible setting, still allows one level of nesting, and
            // doesn't require to make the servants thread safe.
            //
            int size = properties.getPropertyAsIntWithDefault(_prefix + ".Size", 1);
            if(size < 1)
            {
                string s = _prefix + ".Size < 1; Size adjusted to 1";
                _instance.initializationData().logger.warning(s);
                size = 1;
            }

            int sizeMax = properties.getPropertyAsIntWithDefault(_prefix + ".SizeMax", size);
            if(sizeMax < size)
            {
                string s = _prefix + ".SizeMax < " + _prefix + ".Size; SizeMax adjusted to Size (" + size + ")";
                _instance.initializationData().logger.warning(s);
                sizeMax = size;
            }

            int sizeWarn = properties.getPropertyAsInt(_prefix + ".SizeWarn");
            if(sizeWarn != 0 && sizeWarn < size)
            {
                string s = _prefix + ".SizeWarn < " + _prefix + ".Size; adjusted SizeWarn to Size (" + size + ")";
                _instance.initializationData().logger.warning(s);
                sizeWarn = size;
            }
            else if(sizeWarn > sizeMax)
            {
                string s = _prefix + ".SizeWarn > " + _prefix + ".SizeMax; adjusted SizeWarn to SizeMax ("
                    + sizeMax + ")";
                _instance.initializationData().logger.warning(s);
                sizeWarn = sizeMax;
            }

            int threadIdleTime = properties.getPropertyAsIntWithDefault(_prefix + ".ThreadIdleTime", 60);
            if(threadIdleTime < 0)
            {
                string s = _prefix + ".ThreadIdleTime < 0; ThreadIdleTime adjusted to 0";
                _instance.initializationData().logger.warning(s);
                threadIdleTime = 0;
            }

            _size = size;
            _sizeMax = sizeMax;
            _sizeWarn = sizeWarn;
            _threadIdleTime = threadIdleTime;

            int stackSize = properties.getPropertyAsInt(_prefix + ".StackSize");
            if(stackSize < 0)
            {
                string s = _prefix + ".StackSize < 0; Size adjusted to OS default";
                _instance.initializationData().logger.warning(s);
                stackSize = 0;
            }
            _stackSize = stackSize;

#if !SILVERLIGHT
            _hasPriority = properties.getProperty(_prefix + ".ThreadPriority").Length > 0;
            _priority = IceInternal.Util.stringToThreadPriority(properties.getProperty(_prefix + ".ThreadPriority"));
            if(!_hasPriority)
            {
                _hasPriority = properties.getProperty("Ice.ThreadPriority").Length > 0;
                _priority = IceInternal.Util.stringToThreadPriority(properties.getProperty("Ice.ThreadPriority"));
            }
#endif
            
            if(_instance.traceLevels().threadPool >= 1)
            {
                string s = "creating " + _prefix + ": Size = " + _size + ", SizeMax = " + _sizeMax + ", SizeWarn = " + 
                           _sizeWarn;
                _instance.initializationData().logger.trace(_instance.traceLevels().threadPoolCat, s);
            }

            _workItems = new Queue<ThreadPoolWorkItem>();
            
            try
            {
                _threads = new List<WorkerThread>();
                for(int i = 0; i < _size; ++i)
                {
                    WorkerThread thread = new WorkerThread(this, _threadPrefix + "-" + _threadIndex++);
                    _threads.Add(thread);
#if !SILVERLIGHT
                    if(_hasPriority)
                    {
                        thread.start(_priority);
                    }
                    else
                    {
                        thread.start(ThreadPriority.Normal);
                    }
#else
                    thread.start();
#endif
                }
            }
            catch(System.Exception ex)
            {
                string s = "cannot create thread for `" + _prefix + "':\n" + ex;
                _instance.initializationData().logger.error(s);

                destroy();
                joinWithAllThreads();
                throw;
            }
        }

        public void updateObservers()
        {
            _m.Lock();
            try
            {
                foreach(WorkerThread t in _threads)
                {
                    t.updateObserver();
                }
            }
            finally
            {
                _m.Unlock();
            }
        }

        public void destroy()
        {
            _m.Lock();
            try
            {
                Debug.Assert(!_destroyed);
                _destroyed = true;
                _m.NotifyAll();
            }
            finally
            {
                _m.Unlock();
            }
        }

        public void initialize(EventHandler handler)
        {
            // Nothing to do.
        }

        public void register(EventHandler handler, int op)
        {
            update(handler, SocketOperation.None, op);
        }

        public void update(EventHandler handler, int remove, int add)
        {
            _m.Lock();
            try
            {
                Debug.Assert(!_destroyed);
                handler._registered = handler._registered & ~remove;
                handler._registered = handler._registered | add;
                if((add & SocketOperation.Read) != 0 && (handler._pending & SocketOperation.Read) == 0)
                {
                    handler._pending |= SocketOperation.Read;
                    executeNonBlocking(delegate()
                                       {
                                           messageCallback(new ThreadPoolCurrent(this, handler, SocketOperation.Read));
                                       });
                }
                else if((add & SocketOperation.Write) != 0 && (handler._pending & SocketOperation.Write) == 0)
                {
                    handler._pending |= SocketOperation.Write;
                    executeNonBlocking(delegate()
                                       {
                                           messageCallback(new ThreadPoolCurrent(this, handler, SocketOperation.Write));
                                       }); 
                }
            }
            finally
            {
                _m.Unlock();
            }
        }

        public void unregister(EventHandler handler, int op)
        {
            update(handler, op, SocketOperation.None);
        }

        public void finish(EventHandler handler)
        {
            _m.Lock();
            try
            {
                Debug.Assert(!_destroyed);
                if(handler._pending == 0)
                {
                    handler._registered = SocketOperation.None;
                    executeNonBlocking(delegate()
                                       {
                                           ThreadPoolCurrent current = 
                                               new ThreadPoolCurrent(this, handler, SocketOperation.None);
                                           handler.finished(ref current);
                                       });
                }
                else
                {
                    handler._finish = true;
                }
            }
            finally
            {
                _m.Unlock();
            }
        }

#if COMPACT
        public void dispatch(Ice.VoidAction call)
#else
        public void dispatch(System.Action call)
#endif
        {
            if(_dispatcher != null)
            {
                try
                {
                    _dispatcher(call, null);
                }
                catch(System.Exception ex)
                {
                    if(_instance.initializationData().properties.getPropertyAsIntWithDefault(
                           "Ice.Warn.Dispatch", 1) > 1)
                    {
                        _instance.initializationData().logger.warning("dispatch exception:\n" + ex);
                    }
                }
            }
            else
            {
                execute(() => { call(); });
            }
        }

        public void
        execute(ThreadPoolWorkItem workItem)
        {
            _m.Lock();
            try
            {
                Debug.Assert(!_destroyed);
                if(_workItems.Count == 0)
                {
                    _m.Notify();
                }
                _workItems.Enqueue(workItem);

                //
                // If this is a dynamic thread pool which can still grow and if all threads are
                // currently busy dispatching or about to dispatch, we spawn a new thread to 
                // execute this new work item right away.
                //
                if(_threads.Count < _sizeMax && 
                   (_inUse + _workItems.Count) > _threads.Count &&
                   !_destroyed)
                {
                    if(_instance.traceLevels().threadPool >= 1)
                    {
                        string s = "growing " + _prefix + ": Size = " + (_threads.Count + 1);
                        _instance.initializationData().logger.trace(_instance.traceLevels().threadPoolCat, s);
                    }
                    
                    try
                    {
                        WorkerThread t = new WorkerThread(this, _threadPrefix + "-" + _threadIndex++);
#if !SILVERLIGHT
                        if(_hasPriority)
                        {
                            t.start(_priority);
                        }
                        else
                        {
                            t.start(ThreadPriority.Normal);
                        }
#else
                        t.start();
#endif
                        _threads.Add(t);
                    }
                    catch(System.Exception ex)
                    {
                        string s = "cannot create thread for `" + _prefix + "':\n" + ex;
                        _instance.initializationData().logger.error(s);
                    }
                }
            }
            finally
            {
                _m.Unlock();
            }
        }

        public void
        executeNonBlocking(ThreadPoolWorkItem workItem)
        {
            _m.Lock();
            try
            {
                Debug.Assert(!_destroyed);
                _instance.asyncIOThread().queue(workItem);
            }
            finally
            {
                _m.Unlock();
            }
        }

        public void joinWithAllThreads()
        {
            //
            // _threads is immutable after destroy() has been called,
            // therefore no synchronization is needed. (Synchronization
            // wouldn't be possible here anyway, because otherwise the
            // other threads would never terminate.)
            //
            Debug.Assert(_destroyed);
            foreach(WorkerThread thread in _threads)
            {
                thread.join();
            }
        }

        public string prefix()
        {
            return _prefix;
        }

        public bool serialize()
        {
            return _serialize;
        }

        private void run(WorkerThread thread)
        {
            ThreadPoolWorkItem workItem = null;
            while(true)
            {
                _m.Lock();
                try
                {
                    if(workItem != null)
                    {
                        Debug.Assert(_inUse > 0);
                        --_inUse;
                        if(_workItems.Count == 0)
                        {
                            thread.setState(Ice.Instrumentation.ThreadState.ThreadStateIdle);
                        }
                    }

                    workItem = null;

                    while(_workItems.Count == 0)
                    {
                        if(_destroyed)
                        {
                            return;
                        }

                        if(_threadIdleTime > 0)
                        {
                            if(!_m.TimedWait(_threadIdleTime * 1000) && _workItems.Count == 0) // If timeout
                            {
                                if(_destroyed)
                                {
                                    return;
                                }
                                else if(_serverIdleTime == 0 || _threads.Count > 1)
                                {
                                    //
                                    // If not the last thread or if server idle time isn't configured,
                                    // we can exit. Unlike C++/Java, there's no need to have a thread 
                                    // always spawned in the thread pool because all the IO is done
                                    // by the .NET thread pool threads. Instead, we'll just spawn a 
                                    // new thread when needed (i.e.: when a new work item is queued).
                                    //
                                    if(_instance.traceLevels().threadPool >= 1)
                                    {
                                        string s = "shrinking " + _prefix + ": Size=" + (_threads.Count - 1);
                                        _instance.initializationData().logger.trace(
                                            _instance.traceLevels().threadPoolCat, s);
                                    }
                                    
                                    _threads.Remove(thread);
                                    _instance.asyncIOThread().queue(delegate()
                                                                    {
                                                                        thread.join();
                                                                    });
                                    return;
                                }
                                else
                                {
                                    Debug.Assert(_serverIdleTime > 0 && _inUse == 0 && _threads.Count == 1);
                                    if(!_m.TimedWait(_serverIdleTime * 1000)  && _workItems.Count == 0)
                                    {
                                        if(!_destroyed)
                                        {
                                            _workItems.Enqueue(delegate()
                                                               {
                                                                   try
                                                                   {
                                                                       _instance.objectAdapterFactory().shutdown();
                                                                   }
                                                                   catch(Ice.CommunicatorDestroyedException)
                                                                   {
                                                                   }
                                                               });
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            _m.Wait();
                        }
                    }

                    Debug.Assert(_workItems.Count > 0);
                    workItem = _workItems.Dequeue();

                    Debug.Assert(_inUse >= 0);
                    ++_inUse;

                    thread.setState(Ice.Instrumentation.ThreadState.ThreadStateInUseForUser);
                    
                    if(_sizeMax > 1 && _inUse == _sizeWarn)
                    {
                        string s = "thread pool `" + _prefix + "' is running low on threads\n"
                            + "Size=" + _size + ", " + "SizeMax=" + _sizeMax + ", " + "SizeWarn=" + _sizeWarn;
                        _instance.initializationData().logger.warning(s);
                    }                    
                }
                finally
                {
                    _m.Unlock();
                }

                try
                {
                    workItem();
                }
                catch(System.Exception ex)
                {
                    string s = "exception in `" + _prefix + "' while calling on work item:\n" + ex + '\n';
                    _instance.initializationData().logger.error(s);
                }
            }
        }
    
        public bool startMessage(ref ThreadPoolCurrent current)
        {
            Debug.Assert((current._handler._pending & current.operation) != 0);
                                     
            if((current._handler._started & current.operation) != 0)
            {
                Debug.Assert((current._handler._ready & current.operation) == 0);
                current._handler._ready |= current.operation;
                current._handler._started &= ~current.operation;
                if(!current._handler.finishAsync(current.operation)) // Returns false if the handler is finished.
                {
                    current._handler._pending &= ~current.operation;
                    if(current._handler._pending == 0 && current._handler._finish)
                    {
                        finish(current._handler);
                    }
                    return false;
                }
            }
            else if((current._handler._ready & current.operation) == 0 && 
                    (current._handler._registered & current.operation) != 0)
            {
                Debug.Assert((current._handler._started & current.operation) == 0);
                bool completed = false;
                if(!current._handler.startAsync(current.operation, getCallback(current.operation), ref completed))
                {
                    current._handler._pending &= ~current.operation;
                    if(current._handler._pending == 0 && current._handler._finish)
                    {
                        finish(current._handler);
                    }
                    return false;
                }
                else
                {
                    current.completedSynchronously = completed;
                    current._handler._started |= current.operation;
                    return false;
                }
            }
                                     
            if((current._handler._registered & current.operation) != 0)
            {
                Debug.Assert((current._handler._ready & current.operation) != 0);
                current._handler._ready &= ~current.operation;
                return true;
            }
            else
            {
                current._handler._pending &= ~current.operation;
                if(current._handler._pending == 0 && current._handler._finish)
                {
                    finish(current._handler);
                }
                return false;
            }
        }

        public void finishMessage(ref ThreadPoolCurrent current, bool fromIOThread)
        {
            if((current._handler._registered & current.operation) != 0)
            {
                if(fromIOThread)
                {
                    Debug.Assert((current._handler._ready & current.operation) == 0);
                    bool completed = false;
                    if(!current._handler.startAsync(current.operation, getCallback(current.operation), ref completed))
                    {
                        current._handler._pending &= ~current.operation;
                    }
                    else
                    {
                        Debug.Assert((current._handler._pending & current.operation) != 0);
                        current.completedSynchronously = completed;
                        current._handler._started |= current.operation;
                    }
                }
                else
                {
                    ThreadPoolCurrent c = current;
                    executeNonBlocking(delegate()
                                       {
                                           messageCallback(c);
                                       });
                }
            }
            else
            {
                current._handler._pending &= ~current.operation;
            }

            if(current._handler._pending == 0 && current._handler._finish)
            {
                // There are no more pending async operations, it's time to call finish.
                finish(current._handler);
            }
        }

        public void asyncReadCallback(object state)
        {
            messageCallback(new ThreadPoolCurrent(this, (EventHandler)state, SocketOperation.Read));
        }
        
        public void asyncWriteCallback(object state)
        {
            messageCallback(new ThreadPoolCurrent(this, (EventHandler)state, SocketOperation.Write));
        }

        public void messageCallback(ThreadPoolCurrent current)
        {
            try
            {
                do
                {
                    current.completedSynchronously = false;
                    current._handler.message(ref current);
                }
                while(current.completedSynchronously);
            }
            catch(System.Exception ex)
            {
                string s = "exception in `" + _prefix + "':\n" + ex + "\nevent handler: " + current._handler.ToString();
                _instance.initializationData().logger.error(s);
            }            
        }

        private AsyncCallback getCallback(int operation)
        {
            switch(operation)
            {
            case SocketOperation.Read:
                return asyncReadCallback;
            case SocketOperation.Write:
                return asyncWriteCallback;
            default:
                Debug.Assert(false);
                return null;
            }
        }

        private Instance _instance;
        private Ice.Dispatcher _dispatcher;
        private bool _destroyed;
        private readonly string _prefix;
        private readonly string _threadPrefix;

        private sealed class WorkerThread
        {
            private ThreadPool _threadPool;
            private Ice.Instrumentation.ThreadObserver _observer;
            private Ice.Instrumentation.ThreadState _state;

            internal WorkerThread(ThreadPool threadPool, string name) : base()
            {
                _threadPool = threadPool;
                _name = name;
                _state = Ice.Instrumentation.ThreadState.ThreadStateIdle;
                updateObserver();
            }

            public void updateObserver()
            {
                // Must be called with the thread pool mutex locked
                Ice.Instrumentation.CommunicatorObserver obsv = _threadPool._instance.initializationData().observer;
                if(obsv != null)
                {
                    _observer = obsv.getThreadObserver(_threadPool._prefix, _name, _state, _observer);
                    if(_observer != null)
                    {
                        _observer.attach();
                    }
                }
            }

            public void
            setState(Ice.Instrumentation.ThreadState s)
            {
                // Must be called with the thread pool mutex locked
                if(_observer != null)
                {
                    if(_state != s)
                    {
                        _observer.stateChanged(_state, s);
                    }
                }
                _state = s;
            }

            public void join()
            {
                _thread.Join();
            }

#if !SILVERLIGHT
            public void start(ThreadPriority priority)
            {
                if(_threadPool._stackSize == 0)
                {
                    _thread = new Thread(new ThreadStart(Run));
                }
                else
                {
                    _thread = new Thread(new ThreadStart(Run), _threadPool._stackSize);
                }
                _thread.IsBackground = true;
                _thread.Name = _name;
                _thread.Priority = priority;
                _thread.Start();
            }
#else
            public void start()
            {
                _thread = new Thread(new ThreadStart(Run));
                _thread.IsBackground = true;
                _thread.Name = _name;
                _thread.Start();
            }
#endif

            public void Run()
            {
                if(_threadPool._instance.initializationData().threadHook != null)
                {
                    try
                    {
                        _threadPool._instance.initializationData().threadHook.start();
                    }
                    catch(System.Exception ex)
                    {
                        string s = "thread hook start() method raised an unexpected exception in `";
                        s += _threadPool._prefix + "' thread " + _thread.Name + ":\n" + ex;
                        _threadPool._instance.initializationData().logger.error(s);
                    }
                }

                try
                {
                    _threadPool.run(this);
                }
                catch(System.Exception ex)
                {
                    string s = "exception in `" + _threadPool._prefix + "' thread " + _thread.Name + ":\n" + ex;
                    _threadPool._instance.initializationData().logger.error(s);
                }
                
                if(_observer != null)
                {
                    _observer.detach();
                }

                if(_threadPool._instance.initializationData().threadHook != null)
                {
                    try
                    {
                        _threadPool._instance.initializationData().threadHook.stop();
                    }
                    catch(System.Exception ex)
                    {
                        string s = "thread hook stop() method raised an unexpected exception in `";
                        s += _threadPool._prefix + "' thread " + _thread.Name + ":\n" + ex;
                        _threadPool._instance.initializationData().logger.error(s);
                    }
                }
            }

            private readonly string _name;
            private Thread _thread;
        }

        private readonly int _size; // Number of threads that are pre-created.
        private readonly int _sizeMax; // Maximum number of threads.
        private readonly int _sizeWarn; // If _inUse reaches _sizeWarn, a "low on threads" warning will be printed.
        private readonly bool _serialize; // True if requests need to be serialized over the connection.
#if !SILVERLIGHT
        private readonly ThreadPriority _priority;
        private readonly bool _hasPriority = false;
#endif
        private readonly int _serverIdleTime;
        private readonly int _threadIdleTime;
        private readonly int _stackSize;

        private List<WorkerThread> _threads; // All threads, running or not.
        private int _threadIndex; // For assigning thread names.
        private int _inUse; // Number of threads that are currently in use.

        private Queue<ThreadPoolWorkItem> _workItems;

        private readonly IceUtilInternal.Monitor _m = new IceUtilInternal.Monitor();
    }

}
