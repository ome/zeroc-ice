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
    using System.Collections.Generic;
    using Ice.Instrumentation;

    public sealed class ObserverHelper
    {
        static public InvocationObserver get(Instance instance, string op)
        {
            CommunicatorObserver obsv = instance.initializationData().observer;
            if(obsv != null)
            {
                InvocationObserver observer = obsv.getInvocationObserver(null, op, _emptyContext);
                if(observer != null)
                {
                    observer.attach();
                }
                return observer;
            }
            return null;
        }

        static public InvocationObserver get(Ice.ObjectPrx proxy, string op)
        {
            return get(proxy, op, null);
        }

        static public InvocationObserver get(Ice.ObjectPrx proxy, string op, Dictionary<string, string> context)
        {
            CommunicatorObserver obsv = 
                ((Ice.ObjectPrxHelperBase)proxy).reference__().getInstance().initializationData().observer;
            if(obsv != null)
            {
                InvocationObserver observer;
                if(context == null)
                {
                    observer = obsv.getInvocationObserver(proxy, op, _emptyContext);
                }
                else
                {
                    observer = obsv.getInvocationObserver(proxy, op, context);
                }
                if(observer != null)
                {
                    observer.attach();
                }
                return observer;
            }
            return null;
        }

        private static Dictionary<string, string> _emptyContext = new Dictionary<string, string>();
    }
}