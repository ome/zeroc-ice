// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#if !SILVERLIGHT

namespace Ice
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Reflection;
    using System.Runtime.InteropServices;
    using System.Threading;

    internal static class NativeMethods
    {
#if !COMPACT && !UNITY
        //
        // Technically it's not necessary to wrap DllImport in conditional compilation because
        // the binding occurs at run time and it will never be executed on Mono. However, it
        // causes problems for the Compact Framework.
        //
        [DllImport("kernel32.dll")]
        [return: MarshalAsAttribute(UnmanagedType.Bool)] 
        internal static extern bool 
        SetConsoleCtrlHandler(CtrlCEventHandler eh, [MarshalAsAttribute(UnmanagedType.Bool)]bool add);
#endif
    }

    /// <summary>
    /// The signal policy for Ice.Application signal handling.
    /// </summary>
    public enum SignalPolicy
    {
        /// <summary>
        /// If a signal is received, Ice.Application reacts to the signal
        /// by calling Communicator.destroy or Communicator.shutdown,
        /// or by calling a custom shutdown hook installed by the application.
        /// </summary>
        HandleSignals,

        /// <summary>
        /// Any signal that is received is not intercepted and takes the default action.
        /// </summary>
        NoSignalHandling
    }

    /// <summary>
    /// Utility base class that makes it easy to correctly initialize and finalize
    /// the Ice run time, as well as handle signals. Unless the application specifies
    /// a logger, Application installs a per-process logger that logs to the standard
    /// error output.
    /// Applications must create a derived class that implements the run method.
    /// A program can contain only one instance of this class.
    /// </summary>
    public abstract class Application
    {
        /// <summary>
        /// Called once the communicator has been initialized. The derived class must
        /// implement run, which is the application's starting method.
        /// </summary>
        /// <param name="args">The argument vector for the application. Application
        /// scans the argument vector passed to main for options that are
        /// specific to the Ice run time and removes them; therefore, the vector passed
        /// to run is free from Ice-related options and contains only options
        /// and arguments that are application-specific.</param>
        /// <returns>The run method should return zero for successful termination, and
        /// non-zero otherwise. Application.main returns the value returned by run.</returns>
        public abstract int run(string[] args);

        /// <summary>
        /// Override this method to provide a custom application interrupt
        /// hook. You must call callbackOnInterrupt for this method
        /// to be called. Note that the interruptCallback can be called
        /// concurrently with any other thread (including main) in your
        /// application--take appropriate concurrency precautions.
        /// </summary>
        /// <param name="sig">The cause of the interrupt.</param>
        public virtual void interruptCallback(int sig)
        {
        }

        /// <summary>
        /// Initializes an instance that calls Communicator.shutdown if a signal is received.
        /// </summary>
        public Application()
        {
        }

        /// <summary>
        /// Initializes an instance that handles signals according to the signal policy.
        /// </summary>
        /// <param name="signalPolicy">Determines how to respond to signals.</param>
        public Application(SignalPolicy signalPolicy)
        {
            signalPolicy__ = signalPolicy;
        }

        /// <summary>
        /// The application must call main after it has
        /// instantiated the derived class. main creates
        /// a communicator, establishes the specified signal policy, and,
        /// once run returns, destroys the communicator.
        /// The method prints an error message for any exception that propagates
        /// out of run and ensures that the communicator is
        /// destroyed correctly even if run completes abnormally.
        /// </summary>
        /// <param name="args">The arguments for the application (as passed to Main(string[])
        /// by the operating system.</param>
        /// <returns>The value returned by run. If run terminates with an exception,
        /// the return value is non-zero.</returns>
        public int main(string[] args)
        {
            return main(args, new InitializationData());
        }

        /// <summary>
        /// The application must call main after it has
        /// instantiated the derived class. main creates
        /// a communicator, establishes the specified signal policy, and,
        /// once run returns, destroys the communicator.
        /// The method prints an error message for any exception that propagates
        /// out of run and ensures that the communicator is
        /// destroyed correctly even if run completes abnormally.
        /// </summary>
        /// <param name="args">The arguments for the application (as passed to Main(string[])
        /// by the operating system.</param>
        /// <param name="configFile">The configuration file with which to initialize
        /// Ice properties.</param>
        /// <returns>The value returned by run. If run terminates with an exception,
        /// the return value is non-zero.</returns>
        public int main(string[] args, string configFile)
        {
            if(Util.getProcessLogger() is ConsoleLoggerI)
            {
                Util.setProcessLogger(new ConsoleLoggerI(appName__));
            }

            InitializationData initData = new InitializationData();
            if(configFile != null)
            {
                try
                {
                    initData.properties = Util.createProperties();
                    initData.properties.load(configFile);
                }
                catch(Ice.Exception ex)
                {
                    Util.getProcessLogger().error(ex.ToString());
                    return 1;
                }
                catch(System.Exception ex)
                {
                    Util.getProcessLogger().error("unknown exception:\n" + ex);
                    return 1;
                }
            }
            return main(args, initData);
        }

        /// <summary>
        /// The application must call main after it has
        /// instantiated the derived class. main creates
        /// a communicator, establishes the specified signal policy, and,
        /// once run returns, destroys the communicator.
        /// The method prints an error message for any exception that propagates
        /// out of run and ensures that the communicator is
        /// destroyed correctly even if run completes abnormally.
        /// </summary>
        /// <param name="args">The arguments for the application (as passed to Main(string[])
        /// by the operating system.</param>
        /// <param name="initializationData">Additional data used to initialize the communicator.</param>
        /// <returns>The value returned by run. If run terminates with an exception,
        /// the return value is non-zero.</returns>
        public int main(string[] args, InitializationData initializationData)
        {
            if(Util.getProcessLogger() is ConsoleLoggerI)
            {
                Util.setProcessLogger(new ConsoleLoggerI(appName__));
            }

            if(communicator__ != null)
            {
                Util.getProcessLogger().error("only one instance of the Application class can be used");
                return 1;
            }

            //
            // We parse the properties here to extract Ice.ProgramName.
            //
            InitializationData initData;
            if(initializationData != null)
            {
                initData = (InitializationData)initializationData.Clone();
            }
            else
            {
                initData = new InitializationData();
            }
            
            try
            {
                initData.properties = Util.createProperties(ref args, initData.properties);
            }
            catch(Ice.Exception ex)
            {
                Util.getProcessLogger().error(ex.ToString());
                return 1;
            }
            catch(System.Exception ex)
            {
                Util.getProcessLogger().error("unknown exception:\n" + ex);
                return 1;
            }
            appName__ = initData.properties.getPropertyWithDefault("Ice.ProgramName", appName__);

            nohup__ = initData.properties.getPropertyAsInt("Ice.Nohup") > 0;
            _application = this;

            int status;
#if COMPACT || UNITY
            status = doMain(args, initData);
#else

            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                if(IceInternal.AssemblyUtil.platform_ == IceInternal.AssemblyUtil.Platform.Windows)
                {
                    _signals = new WindowsSignals();
                }
                else
                {
                    _signals = new MonoSignals();
                }
                _signals.register(_handler);

                status = doMain(args, initData);

                _signals.destroy();
                _signals = null;
            }
            else
            {
                status = doMain(args, initData);
            }
#endif

            return status;
        }

        /// <summary>
        /// Returns the application name (which is also the value of Ice.ProgramName.
        /// This method is useful mainly for error messages that
        /// include the application name. Because appName is a static method, it is available from anywhere
        /// in the program.
        /// </summary>
        /// <returns>The name of the application.</returns>
        public static string appName()
        {
            return appName__;
        }

        /// <summary>
        /// Returns the communicator for the application. Because communicator is a static method,
        /// it permits access to the communicator from anywhere in the program. Note that, as a consequence,
        /// you cannot have more than one instance of Application in a program.
        /// </summary>
        /// <returns>The communicator for the application.</returns>
        public static Communicator communicator()
        {
            return communicator__;
        }

        /// <summary>
        /// Instructs Application to call Communicator.destroy on receipt of a signal.
        /// This is default signal handling policy established by the default constructor.
        /// </summary>
        public static void destroyOnInterrupt()
        {
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                mutex__.Lock();
                try
                {
                    if(_callback == _holdCallback)
                    {
                        released__ = true;
                        mutex__.Notify();
                    }
                    _callback = _destroyCallback;
                }
                finally
                {
                    mutex__.Unlock();
                }
            }
            else
            {
                Util.getProcessLogger().warning(
                    "interrupt method called on Application configured to not handle interrupts.");
            }
        }

        /// <summary>
        /// Instructs Application to call Communicator.shutdown on receipt of a signal.
        /// </summary>
        public static void shutdownOnInterrupt()
        {
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                mutex__.Lock();
                try
                {
                    if(_callback == _holdCallback)
                    {
                        released__ = true;
                        mutex__.Notify();
                    }
                    _callback = _shutdownCallback;
                }
                finally
                {
                    mutex__.Unlock();
                }
            }
            else
            {
                Util.getProcessLogger().warning(
                            "interrupt method called on Application configured to not handle interrupts.");
            }
        }

        /// <summary>
        /// Instructs Application to ignore signals.
        /// </summary>
        public static void ignoreInterrupt()
        {
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                mutex__.Lock();
                try
                {
                    if(_callback == _holdCallback)
                    {
                        released__ = true;
                        mutex__.Notify();
                    }
                    _callback = null;
                }
                finally
                {
                    mutex__.Unlock();
                }
            }
            else
            {
                Util.getProcessLogger().warning(
                            "interrupt method called on Application configured to not handle interrupts.");
            }
        }

        /// <summary>
        /// Instructs Application to call interruptCallback on receipt of a signal.
        /// The derived class can intercept signals by overriding interruptCallback.
        /// </summary>
        public static void callbackOnInterrupt()
        {
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                mutex__.Lock();
                try
                {
                    if(_callback == _holdCallback)
                    {
                        released__ = true;
                        mutex__.Notify();
                    }
                    _callback = _userCallback;
                }
                finally
                {
                    mutex__.Unlock();
                }
            }
            else
            {
                Util.getProcessLogger().warning(
                            "interrupt method called on Application configured to not handle interrupts.");
            }
        }

        /// <summary>
        /// Instructs Application to call to hold signals.
        /// </summary>
        public static void holdInterrupt()
        {
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                mutex__.Lock();
                try
                {
                    if(_callback != _holdCallback)
                    {
                        _previousCallback = _callback;
                        released__ = false;
                        _callback = _holdCallback;
                    }
                    // else, we were already holding signals
                }
                finally
                {
                    mutex__.Unlock();
                }
            }
            else
            {
                Util.getProcessLogger().warning(
                            "interrupt method called on Application configured to not handle interrupts.");
            }
        }

        /// <summary>
        /// Instructs Application respond to signals. If a signal arrived since the last call
        /// to holdInterrupt, it is delivered once you call releaseInterrupt.
        /// </summary>
        public static void releaseInterrupt()
        {
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                mutex__.Lock();
                try
                {
                    if(_callback == _holdCallback)
                    {
                        //
                        // Note that it's very possible no signal is held;
                        // in this case the callback is just replaced and
                        // setting released__ to true and signalling mutex__
                        // do no harm.
                        //

                        released__ = true;
                        _callback = _previousCallback;
                        mutex__.Notify();
                    }
                    // Else nothing to release.
                }
                finally
                {
                    mutex__.Unlock();
                }
            }
            else
            {
                Util.getProcessLogger().warning(
                            "interrupt method called on Application configured to not handle interrupts.");
            }
        }

        /// <summary>
        /// Determines whether the application shut down intentionally or was forced to shut down due to a signal.
        /// This is useful for logging purposes.
        /// </summary>
        /// <returns>True if a signal caused the communicator to shut down; false otherwise.</returns>
        public static bool interrupted()
        {
            mutex__.Lock();
            try
            {
                return interrupted__;
            }
            finally
            {
                mutex__.Unlock();
            }
        }

        protected virtual int doMain(string[] args, InitializationData initData)
        {
            int status = 0;

            try
            {
                //
                // If the process logger is the default logger, we replace it with a
                // a logger which is using the program name for the prefix.
                //
                if(initData.properties.getProperty("Ice.ProgramName").Length > 0 && 
                   Util.getProcessLogger() is ConsoleLoggerI)
                {
                    Util.setProcessLogger(new ConsoleLoggerI(initData.properties.getProperty("Ice.ProgramName")));
                }

                communicator__ = Util.initialize(ref args, initData);
                destroyed__ = false;

                //
                // The default is to destroy when a signal is received.
                //
                if(signalPolicy__ == SignalPolicy.HandleSignals)
                {
                    destroyOnInterrupt();
                }

                status = run(args);
            }
            catch(Ice.Exception ex)
            {
                Util.getProcessLogger().error(ex.ToString());
                status = 1;
            }
            catch(System.Exception ex)
            {
                Util.getProcessLogger().error("unknown exception:\n" + ex);
                status = 1;
            }

            //
            // Don't want any new interrupt. And at this point
            // (post-run), it would not make sense to release a held
            // signal to run shutdown or destroy.
            //
            if(signalPolicy__ == SignalPolicy.HandleSignals)
            {
                ignoreInterrupt();
            }

            mutex__.Lock();
            try
            {
                while(callbackInProgress__)
                {
                    mutex__.Wait();
                }
                if(destroyed__)
                {
                    communicator__ = null;
                }
                else
                {
                    destroyed__ = true;
                    //
                    // communicator__ != null means that it will be destroyed
                    // next; destroyed__ == true ensures that any
                    // remaining callback won't do anything
                    //
                }
                _application = null;
            }
            finally
            {
                mutex__.Unlock();
            }

            if(communicator__ != null)
            {
                try
                {
                    communicator__.destroy();
                }
                catch(Ice.Exception ex)
                {
                    Util.getProcessLogger().error(ex.ToString());
                    status = 1;
                }
                catch(System.Exception ex)
                {
                    Util.getProcessLogger().error("unknown exception:\n" + ex);
                    status = 1;
                }
                communicator__ = null;
            }

            return status;
        }

        //
        // First-level handler.
        //
        private static void signalHandler(int sig)
        {
            Callback callback;

            mutex__.Lock();
            try
            {
                callback = _callback;
            }
            finally
            {
                mutex__.Unlock();
            }

            if(callback != null)
            {
                try
                {
                    callback(sig);
                }
                catch(System.Exception)
                {
                    Debug.Assert(false);
                }
            }
        }

        //
        // The callbacks to be invoked from the handler.
        //
        private static void holdInterruptCallback(int sig)
        {
            Callback callback = null;
            mutex__.Lock();
            try
            {
                while(!released__)
                {
                    mutex__.Wait();
                }

                if(destroyed__)
                {
                    //
                    // Being destroyed by main thread
                    //
                    return;
                }

                callback = _callback;
            }
            finally
            {
                mutex__.Unlock();
            }

            if(callback != null)
            {
                callback(sig);
            }
        }

        //
        // The callbacks to be invoked from the handler.
        //
        private static void destroyOnInterruptCallback(int sig)
        {
            mutex__.Lock();
            try
            {
                if(destroyed__)
                {
                    //
                    // Being destroyed by main thread
                    //
                    return;
                }
                if(nohup__ && sig == SIGHUP)
                {
                    return;
                }

                Debug.Assert(!callbackInProgress__);
                callbackInProgress__ = true;
                interrupted__ = true;
                destroyed__ = true;
            }
            finally
            {
                mutex__.Unlock();
            }

            try
            {
                Debug.Assert(communicator__ != null);
                communicator__.destroy();
            }
            catch(System.Exception ex)
            {
                Util.getProcessLogger().error("(while destroying in response to signal " + sig + "):\n" + ex);
            }

            mutex__.Lock();
            try
            {
                callbackInProgress__ = false;
                mutex__.Notify();
            }
            finally
            {
                mutex__.Unlock();
            }
        }

        private static void shutdownOnInterruptCallback(int sig)
        {
            mutex__.Lock();
            try
            {
                if(destroyed__)
                {
                    //
                    // Being destroyed by main thread
                    //
                    return;
                }
                if(nohup__ && sig == SIGHUP)
                {
                    return;
                }

                Debug.Assert(!callbackInProgress__);
                callbackInProgress__ = true;
                interrupted__ = true;
            }
            finally
            {
                mutex__.Unlock();
            }

            try
            {
                Debug.Assert(communicator__ != null);
                communicator__.shutdown();
            }
            catch(System.Exception ex)
            {
                Util.getProcessLogger().error("(while shutting down in response to signal " + sig + "):\n" + ex);
            }

            mutex__.Lock();
            try
            {
                callbackInProgress__ = false;
                mutex__.Notify();
            }
            finally
            {
                mutex__.Unlock();
            }
        }

        private static void userCallbackOnInterruptCallback(int sig)
        {
            mutex__.Lock();
            try
            {
                if(destroyed__)
                {
                    //
                    // Being destroyed by main thread
                    //
                    return;
                }
                // For SIGHUP the user callback is always called. It can
                // decide what to do.
                Debug.Assert(!callbackInProgress__);
                callbackInProgress__ = true;
                interrupted__ = true;
            }
            finally
            {
                mutex__.Unlock();
            }

            try
            {
                Debug.Assert(_application != null);
                _application.interruptCallback(sig);
            }
            catch(System.Exception ex)
            {
                Util.getProcessLogger().error("(while interrupting in response to signal " + sig + "):\n" + ex);
            }

            mutex__.Lock();
            try
            {
                callbackInProgress__ = false;
                mutex__.Notify();
            }
            finally
            {
                mutex__.Unlock();
            }
        }

        protected static readonly IceUtilInternal.Monitor mutex__ = new IceUtilInternal.Monitor();

        protected static bool callbackInProgress__ = false;
        protected static bool destroyed__ = false;
        protected static bool interrupted__ = false;
        protected static bool released__ = false;
        protected static bool nohup__ = false;
        protected static SignalPolicy signalPolicy__ = SignalPolicy.HandleSignals;

        private delegate void Callback(int sig);
        private static readonly Callback _destroyCallback = new Callback(destroyOnInterruptCallback);
        private static readonly Callback _shutdownCallback = new Callback(shutdownOnInterruptCallback);
        private static readonly Callback _holdCallback = new Callback(holdInterruptCallback);
        private static readonly Callback _userCallback = new Callback(userCallbackOnInterruptCallback);

        private static Callback _callback = null; // Current callback
        private static Callback _previousCallback; // Remembers prev. callback when signals are held

        //
        // We use FriendlyName instead of Process.GetCurrentProcess().ProcessName because the latter
        // is terribly slow. (It takes around 1 second!)
        //
        protected static string appName__ = AppDomain.CurrentDomain.FriendlyName;
        protected static Communicator communicator__;
        private static Application _application;

        private static int SIGHUP;
        static Application()
        {
            if(IceInternal.AssemblyUtil.platform_ == IceInternal.AssemblyUtil.Platform.Windows)
            {
                SIGHUP = 5; // CTRL_LOGOFF_EVENT, from wincon.h
            }
            else
            {
                SIGHUP = 1;
            }
        }

        private delegate void SignalHandler(int sig);
        private static readonly SignalHandler _handler = new SignalHandler(signalHandler);
#if !COMPACT && !UNITY
        private Signals _signals;

        private interface Signals
        {
            void register(SignalHandler handler);
            void destroy();
        }

        private class MonoSignals : Signals
        {
            public void register(SignalHandler handler)
            {
                _handler = handler;
                _destroyed = false;

                try
                {
                    //
                    // Signal handling in Mono is provided in the Mono.Unix.Native namespace.
                    // We use reflection to do the equivalent of the following:
                    //
                    // Stdlib.signal(Signum.SIGHUP, delegate);
                    // Stdlib.signal(Signum.SIGINT, delegate);
                    // Stdlib.signal(Signum.SIGTERM, delegate);
                    //
                    // We don't use conditional compilation so that the Ice assembly can be
                    // used without change on Windows and Mono.
                    //
                    Assembly a = Assembly.Load(
                        "Mono.Posix, Version=2.0.0.0, Culture=neutral, PublicKeyToken=0738eb9f132ed756");
                    Type sigs = a.GetType("Mono.Unix.Native.Signum");
                    object SIGHUP = Enum.Parse(sigs, "SIGHUP");
                    object SIGINT = Enum.Parse(sigs, "SIGINT");
                    object SIGTERM = Enum.Parse(sigs, "SIGTERM");
                    Type stdlib = a.GetType("Mono.Unix.Native.Stdlib");
                    MethodInfo method = stdlib.GetMethod("signal", BindingFlags.Static | BindingFlags.Public);
                    Type delType = a.GetType("Mono.Unix.Native.SignalHandler");
                    Delegate del = Delegate.CreateDelegate(delType, this, "callback");
                    object[] args = new object[2];
                    args[0] = SIGHUP;
                    args[1] = del;
                    method.Invoke(null, args);
                    args[0] = SIGINT;
                    args[1] = del;
                    method.Invoke(null, args);
                    args[0] = SIGTERM;
                    args[1] = del;
                    method.Invoke(null, args);

                    //
                    // Doing certain activities within Mono's signal dispatch thread
                    // can cause the VM to crash, so we use a separate thread to invoke
                    // the handler.
                    //
                    _thread = new Thread(new ThreadStart(run));
                    _thread.IsBackground = true;
                    _thread.Name = "Ice.Application.SignalThread";
                    _thread.Start();
                }
                catch(System.DllNotFoundException)
                {
                    //
                    // The class Mono.Unix.Native.Stdlib requires libMonoPosixHelper.so. Mono raises
                    // DllNotFoundException if it cannot be found in the shared library search path.
                    //
                    Util.getProcessLogger().warning("unable to initialize signals");
                }
            }

            public void destroy()
            {
                _m.Lock();
                try
                {
                    _destroyed = true;
                    _m.Notify();
                }
                finally
                {
                    _m.Unlock();
                }

                if(_thread != null)
                {
                    _thread.Join();
                    _thread = null;
                }
            }

            private void callback(int sig)
            {
                _m.Lock();
                try
                {
                    _signals.Add(sig);
                    _m.Notify();
                }
                finally
                {
                    _m.Unlock();
                }
            }

            private void run()
            {
                while(true)
                {
                    List<int> signals = null;
                    bool destroyed = false;

                    _m.Lock();
                    try
                    {
                        if(!_destroyed && _signals.Count == 0)
                        {
                            _m.Wait();
                        }

                        if(_signals.Count > 0)
                        {
                            signals = _signals;
                            _signals = new List<int>();
                        }

                        destroyed = _destroyed;
                    }
                    finally
                    {
                        _m.Unlock();
                    }

                    if(signals != null)
                    {
                        foreach(int sig in signals)
                        {
                            _handler(sig);
                        }
                    }

                    if(destroyed)
                    {
                        break;
                    }
                }
            }

            private SignalHandler _handler;
            private bool _destroyed;
            private readonly IceUtilInternal.Monitor _m = new IceUtilInternal.Monitor();
            private Thread _thread;
            private List<int> _signals = new List<int>();
        }

        private class WindowsSignals : Signals
        {
#if MANAGED
            public void register(SignalHandler handler)
            {
                //
                // Signals aren't supported in managed code on Windows.
                //
            }
#else
            public void register(SignalHandler handler)
            {
                _handler = handler;
                _callback = new CtrlCEventHandler(callback);

                bool rc = NativeMethods.SetConsoleCtrlHandler(_callback, true);
                Debug.Assert(rc);
            }

            public void destroy()
            {
            }

            private CtrlCEventHandler _callback;
            private SignalHandler _handler;

            private bool callback(int sig)
            {
                _handler(sig);
                return true;
            }
#endif
        }
#endif
    }
    
    delegate bool CtrlCEventHandler(int sig);
}
#endif
