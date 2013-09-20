// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

using Glacier2;
using Test;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;

[assembly: CLSCompliant(true)]

[assembly: AssemblyTitle("IceTest")]
[assembly: AssemblyDescription("Ice test")]
[assembly: AssemblyCompany("ZeroC, Inc.")]

public class Client
{
    public class App : Ice.Application
    {
        public override int run(string[] args)
        {
            Ice.ObjectPrx routerBase;

            {
                Console.Out.Write("testing stringToProxy for router... ");
                Console.Out.Flush();
                routerBase = communicator().stringToProxy("Glacier2/router:default -p 12347");
                Console.Out.WriteLine("ok");
            }

            Glacier2.RouterPrx router;

            {
                Console.Out.Write("testing checked cast for router... ");
                Console.Out.Flush();
                router = Glacier2.RouterPrxHelper.checkedCast(routerBase);
                test(router != null);
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("installing router with communicator... ");
                Console.Out.Flush();
                communicator().setDefaultRouter(router);
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("getting the session timeout... ");
                Console.Out.Flush();
                long timeout = router.getSessionTimeout();
                test(timeout == 30);
                Console.Out.WriteLine("ok");
            }

            Ice.ObjectPrx @base;

            {
                Console.Out.Write("testing stringToProxy for server object... ");
                Console.Out.Flush();
                @base = communicator().stringToProxy("c1/callback:tcp -p 12010");
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("trying to ping server before session creation... ");
                Console.Out.Flush();
                try
                {
                    @base.ice_ping();
                    test(false);
                }
                catch(Ice.ConnectionLostException)
                {
                    Console.Out.WriteLine("ok");
                }
                catch(Ice.SocketException)
                {
                    test(false);
                }
            }


            {
                Console.Out.Write("trying to create session with wrong password... ");
                Console.Out.Flush();
                try
                {
                    router.createSession("userid", "xxx");
                    test(false);
                }
                catch(Glacier2.PermissionDeniedException)
                {
                    Console.Out.WriteLine("ok");
                }
                catch(Glacier2.CannotCreateSessionException)
                {
                    test(false);
                }
            }

            {
                Console.Out.Write("trying to destroy non-existing session... ");
                Console.Out.Flush();
                try
                {
                    router.destroySession();
                    test(false);
                }
                catch(Glacier2.SessionNotExistException)
                {
                    Console.Out.WriteLine("ok");
                }
            }

            {
                Console.Out.Write("creating session with correct password... ");
                Console.Out.Flush();
                try
                {
                    router.createSession("userid", "abc123");
                }
                catch(Glacier2.PermissionDeniedException)
                {
                    test(false);
                }
                catch(Glacier2.CannotCreateSessionException)
                {
                    test(false);
                }
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("trying to create a second session... ");
                Console.Out.Flush();
                try
                {
                    router.createSession("userid", "abc123");
                    test(false);
                }
                catch(Glacier2.PermissionDeniedException)
                {
                    test(false);
                }
                catch(Glacier2.CannotCreateSessionException)
                {
                    Console.Out.WriteLine("ok");
                }
            }

            {
                Console.Out.Write("pinging server after session creation... ");
                Console.Out.Flush();
                @base.ice_ping();
                Console.Out.WriteLine("ok");
            }

            CallbackPrx twoway;

            {
                Console.Out.Write("testing checked cast for server object... ");
                Console.Out.Flush();
                twoway = CallbackPrxHelper.checkedCast(@base);
                test(twoway != null);
                Console.Out.WriteLine("ok");
            }

            Ice.ObjectAdapter adapter;

            {
                Console.Out.Write("creating and activating callback receiver adapter... ");
                Console.Out.Flush();
                communicator().getProperties().setProperty("Ice.PrintAdapterReady", "0");
                adapter = communicator().createObjectAdapterWithRouter("CallbackReceiverAdapter", router);
                adapter.activate();
                Console.Out.WriteLine("ok");
            }

            String category;

            {
                Console.Out.Write("getting category from router... ");
                Console.Out.Flush();
                category = router.getCategoryForClient();
                Console.Out.WriteLine("ok");
            }

            CallbackReceiverI callbackReceiverImpl;
            Ice.Object callbackReceiver;
            CallbackReceiverPrx twowayR;
            CallbackReceiverPrx fakeTwowayR;

            {
                Console.Out.Write("creating and adding callback receiver object... ");
                Console.Out.Flush();
                callbackReceiverImpl = new CallbackReceiverI();
                callbackReceiver = callbackReceiverImpl;
                Ice.Identity callbackReceiverIdent = new Ice.Identity();
                callbackReceiverIdent.name = "callbackReceiver";
                callbackReceiverIdent.category = category;
                twowayR = CallbackReceiverPrxHelper.uncheckedCast(adapter.add(callbackReceiver, callbackReceiverIdent));
                Ice.Identity fakeCallbackReceiverIdent = new Ice.Identity();
                fakeCallbackReceiverIdent.name = "callbackReceiver";
                fakeCallbackReceiverIdent.category = "dummy";
                fakeTwowayR = CallbackReceiverPrxHelper.uncheckedCast(
                    adapter.add(callbackReceiver, fakeCallbackReceiverIdent));
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("testing oneway callback... ");
                Console.Out.Flush();
                CallbackPrx oneway = CallbackPrxHelper.uncheckedCast(twoway.ice_oneway());
                CallbackReceiverPrx onewayR = CallbackReceiverPrxHelper.uncheckedCast(twowayR.ice_oneway());
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] =  "o";
                oneway.initiateCallback(onewayR, context);
                callbackReceiverImpl.callbackOK();
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("testing twoway callback... ");
                Console.Out.Flush();
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] = "t";
                twoway.initiateCallback(twowayR, context);
                callbackReceiverImpl.callbackOK();
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("ditto, but with user exception... ");
                Console.Out.Flush();
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] = "t";
                try
                {
                    twoway.initiateCallbackEx(twowayR, context);
                    test(false);
                }
                catch(CallbackException ex)
                {
                    test(ex.someValue == 3.14);
                    test(ex.someString.Equals("3.14"));
                }
                callbackReceiverImpl.callbackOK();
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("trying twoway callback with fake category... ");
                Console.Out.Flush();
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] = "t";
                try
                {
                    twoway.initiateCallback(fakeTwowayR, context);
                    test(false);
                }
                catch(Ice.ObjectNotExistException)
                {
                    Console.Out.WriteLine("ok");
                }
            }

            {
                Console.Out.Write("testing whether other allowed category is accepted... ");
                Console.Out.Flush();
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] =  "t";
                CallbackPrx otherCategoryTwoway = CallbackPrxHelper.uncheckedCast(
                    twoway.ice_identity(communicator().stringToIdentity("c2/callback")));
                otherCategoryTwoway.initiateCallback(twowayR, context);
                callbackReceiverImpl.callbackOK();
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("testing whether disallowed category gets rejected... ");
                Console.Out.Flush();
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] = "t";
                try
                {
                    CallbackPrx otherCategoryTwoway = CallbackPrxHelper.uncheckedCast(
                        twoway.ice_identity(communicator().stringToIdentity("c3/callback")));
                    otherCategoryTwoway.initiateCallback(twowayR, context);
                    test(false);
                }
                catch(Ice.ObjectNotExistException)
                {
                    Console.Out.WriteLine("ok");
                }
            }

            {
                Console.Out.Write("testing whether user-id as category is accepted... ");
                Console.Out.Flush();
                Dictionary<string, string> context = new Dictionary<string, string>();
                context["_fwd"] = "t";
                CallbackPrx otherCategoryTwoway = CallbackPrxHelper.uncheckedCast(
                    twoway.ice_identity(communicator().stringToIdentity("_userid/callback")));
                otherCategoryTwoway.initiateCallback(twowayR, context);
                callbackReceiverImpl.callbackOK();
                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("testing server shutdown... ");
                Console.Out.Flush();
                twoway.shutdown();
                // No ping, otherwise the router prints a warning message if it's
                // started with --Ice.Warn.Connections.
                Console.Out.WriteLine("ok");
                /*
                  try
                  {
                      base.ice_ping();
                      test(false);
                  }
                  // If we use the glacier router, the exact exception reason gets
                  // lost.
                  catch(Ice.UnknownLocalException ex)
                  {
                      Console.Out.WriteLine("ok");
                  }
                */
            }

            {
                Console.Out.Write("destroying session... ");
                Console.Out.Flush();
                try
                {
                    router.destroySession();
                }
                catch(Ice.LocalException)
                {
                    test(false);
                }

                Console.Out.WriteLine("ok");
            }

            {
                Console.Out.Write("trying to ping server after session destruction... ");
                Console.Out.Flush();
                try
                {
                    @base.ice_ping();
                    test(false);
                }
                catch(Ice.ConnectionLostException)
                {
                    Console.Out.WriteLine("ok");
                }
                catch(Ice.SocketException)
                {
                    test(false);
                }
            }

            if(args.Length >= 1 && args[0].Equals("--shutdown"))
            {
                {
                    Console.Out.Write("uninstalling router with communicator... ");
                    Console.Out.Flush();
                    communicator().setDefaultRouter(null);
                    Console.Out.WriteLine("ok");
                }

                Ice.ObjectPrx processBase;

                {
                    Console.Out.Write("testing stringToProxy for admin object... ");
                    processBase = communicator().stringToProxy("Glacier2/admin -f Process:tcp -h 127.0.0.1 -p 12348");
                    Console.Out.WriteLine("ok");
                }

    /*
                {
                    Console.Out.Write("uninstalling router with process object... ");
                    processBase.ice_router(null);
                    Console.Out.WriteLine("ok");
                }
    */

                Ice.ProcessPrx process;

                {
                    Console.Out.Write("testing checked cast for process object... ");
                    process = Ice.ProcessPrxHelper.checkedCast(processBase);
                    test(process != null);
                    Console.Out.WriteLine("ok");
                }

                Console.Out.Write("testing Glacier2 shutdown... ");
                process.shutdown();
                try
                {
                    process.ice_ping();
                    test(false);
                }
                catch(Ice.LocalException)
                {
                    Console.Out.WriteLine("ok");
                }
            }

            return 0;
        }

        private static void
        test(bool b)
        {
            if(!b)
            {
                throw new Exception();
            }
        }
    }

    public static int Main(string[] args)
    {
        //
        // We must disable connection warnings, because we attempt to
        // ping the router before session establishment, as well as
        // after session destruction. Both will cause a
        // ConnectionLostException.
        //
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(ref args);

        initData.properties.setProperty("Ice.Warn.Connections", "0");

#if COMPACT
        //
        // When using Ice for .NET Compact Framework, we need to specify
        // the assembly so that Ice can locate classes and exceptions.
        //
        initData.properties.setProperty("Ice.FactoryAssemblies", "client");
#endif

        App app = new App();
        return app.main(args, initData);
    }
}
