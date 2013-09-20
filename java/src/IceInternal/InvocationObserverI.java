// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

import IceMX.*;

public class InvocationObserverI extends IceMX.Observer<IceMX.InvocationMetrics> 
    implements Ice.Instrumentation.InvocationObserver
{
    static public final class RemoteInvocationHelper extends MetricsHelper<RemoteMetrics>
    {
        static private final AttributeResolver _attributes = new AttributeResolver()
            { 
                {
                    try
                    {
                        Class<?> cl = RemoteInvocationHelper.class;
                        add("parent", cl.getDeclaredMethod("getParent"));
                        add("id", cl.getDeclaredMethod("getId"));
                        add("requestId", cl.getDeclaredMethod("getRequestId"));
                        CommunicatorObserverI.addConnectionAttributes(this, RemoteInvocationHelper.class);
                    }
                    catch(Exception ex)
                    {
                        ex.printStackTrace();
                        assert(false);
                    }
                }
            };

        RemoteInvocationHelper(Ice.ConnectionInfo con, Ice.Endpoint endpt, int requestId, int size) 
        {
            super(_attributes);
            _connectionInfo = con;
            _endpoint = endpt;
            _requestId = requestId;
            _size = size;
        }

        public void 
        initMetrics(RemoteMetrics v)
        {
            v.size += _size;
        }

        public String
        getId()
        {
            if(_id == null)
            {
                _id = _endpoint.toString();
                if(_connectionInfo.connectionId != null && !_connectionInfo.connectionId.isEmpty())
                {
                    _id += " [" + _connectionInfo.connectionId + "]";
                }
            }
            return _id;
        }

        int
        getRequestId()
        {
            return _requestId;
        }

        public String 
        getParent()
        {
            if(_connectionInfo.adapterName != null && !_connectionInfo.adapterName.isEmpty())
            {
                return _connectionInfo.adapterName;
            }
            else
            {
                return "Communicator";
            }
        }
        
        public Ice.ConnectionInfo
        getConnectionInfo()
        {
            return _connectionInfo;
        }
        
        public Ice.Endpoint
        getEndpoint()
        {
            return _endpoint;
        }

        public Ice.EndpointInfo
        getEndpointInfo()
        {
            if(_endpointInfo == null)
            {
                _endpointInfo = _endpoint.getInfo();
            }
            return _endpointInfo;
        }

        final private Ice.ConnectionInfo _connectionInfo;
        final private Ice.Endpoint _endpoint;
        final private int _requestId;
        final private int _size;
        private String _id;
        private Ice.EndpointInfo _endpointInfo;
    };

    public void
    userException()
    {
        forEach(_userException);
    }

    public void
    retried()
    {
        forEach(_incrementRetry);
    }
    
    public Ice.Instrumentation.RemoteObserver 
    getRemoteObserver(Ice.ConnectionInfo con, Ice.Endpoint edpt, int requestId, int sz)
    {
        return (Ice.Instrumentation.RemoteObserver)getObserver("Remote",
                                                               new RemoteInvocationHelper(con, edpt, requestId, sz),
                                                               RemoteMetrics.class, 
                                                               RemoteObserverI.class);
    }

    final MetricsUpdate<InvocationMetrics> _incrementRetry = new MetricsUpdate<InvocationMetrics>()
        {
            public void
            update(InvocationMetrics v)
            {
                ++v.retry;
            }
        };

    final MetricsUpdate<InvocationMetrics> _userException = new MetricsUpdate<InvocationMetrics>()
        {
            public void
            update(InvocationMetrics v)
            {
                ++v.userException;
            }
        };
}