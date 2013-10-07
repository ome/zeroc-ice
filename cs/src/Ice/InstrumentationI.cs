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
    using System.Diagnostics;
    using System.Text;
    using System.Collections.Generic;

    using IceMX;

    public class ObserverWithDelegate<T, O> : Observer<T>
        where T : Metrics, new() 
        where O : Ice.Instrumentation.Observer
    {
        override public void
        attach()
        {
            base.attach();
            if(delegate_ != null)
            {
                delegate_.attach();
            }
        }

        override public void
        detach()
        {
            base.detach();
            if(delegate_ != null)
            {
                delegate_.detach();
            }
        }

        override public void 
        failed(string exceptionName)
        {
            base.failed(exceptionName);
            if(delegate_ != null)
            {
                delegate_.failed(exceptionName);
            }
        }

        public O
        getDelegate()
        {
            return delegate_;
        }

        public void
        setDelegate(O del)
        {
            delegate_ = del;
        }

        public Observer getObserver<S, ObserverImpl, Observer>(string mapName, MetricsHelper<S> helper, Observer del)
            where S : Metrics, new()
            where ObserverImpl : ObserverWithDelegate<S, Observer>, Observer, new()
            where Observer : Ice.Instrumentation.Observer
        {
            ObserverImpl obsv = base.getObserver<S, ObserverImpl>(mapName, helper);
            if(obsv != null)
            {
                obsv.setDelegate(del);
                return (Observer)obsv;
            }
            return del;
        }

        protected O delegate_;
    };

    public class ObserverFactoryWithDelegate<T, OImpl, O> : ObserverFactory<T, OImpl>
        where T : Metrics, new() 
        where OImpl : ObserverWithDelegate<T, O>, O, new()
        where O : Ice.Instrumentation.Observer
    {
        public ObserverFactoryWithDelegate(IceInternal.MetricsAdminI metrics, string name) : base(metrics, name)
        {
        }

        public O getObserver(MetricsHelper<T> helper, O del)
        {
            OImpl o = base.getObserver(helper);
            if(o != null)
            {
                o.setDelegate(del);
                return o;
            }
            return del;
        }

        public O getObserver(MetricsHelper<T> helper, object observer, O del)
        {
            OImpl o = base.getObserver(helper, observer);
            if(o != null)
            {
                o.setDelegate(del);
                return o;
            }
            return del;
        }
    }

    static class AttrsUtil
    {
        public static void
        addEndpointAttributes<T>(MetricsHelper<T>.AttributeResolver r, Type cl) where T : IceMX.Metrics
        {
            r.add("endpoint", cl.GetMethod("getEndpoint"));

            Type cli = typeof(Ice.EndpointInfo);
            r.add("endpointType", cl.GetMethod("getEndpointInfo"), cli.GetMethod("type"));
            r.add("endpointIsDatagram", cl.GetMethod("getEndpointInfo"), cli.GetMethod("datagram"));
            r.add("endpointIsSecure", cl.GetMethod("getEndpointInfo"), cli.GetMethod("secure"));
            r.add("endpointTimeout", cl.GetMethod("getEndpointInfo"), cli.GetField("timeout"));
            r.add("endpointCompress", cl.GetMethod("getEndpointInfo"), cli.GetField("compress"));
            
            cli = typeof(Ice.IPEndpointInfo);
            r.add("endpointHost", cl.GetMethod("getEndpointInfo"), cli.GetField("host"));
            r.add("endpointPort", cl.GetMethod("getEndpointInfo"), cli.GetField("port"));
        }

        public static void
        addConnectionAttributes<T>(MetricsHelper<T>.AttributeResolver r, Type cl) where T : IceMX.Metrics
        {
            Type cli = typeof(Ice.ConnectionInfo);
            r.add("incoming", cl.GetMethod("getConnectionInfo"), cli.GetField("incoming"));
            r.add("adapterName", cl.GetMethod("getConnectionInfo"), cli.GetField("adapterName"));
            r.add("connectionId", cl.GetMethod("getConnectionInfo"), cli.GetField("connectionId"));
                
            cli = typeof(Ice.IPConnectionInfo);
            r.add("localHost", cl.GetMethod("getConnectionInfo"), cli.GetField("localAddress"));
            r.add("localPort", cl.GetMethod("getConnectionInfo"), cli.GetField("localPort"));
            r.add("remoteHost", cl.GetMethod("getConnectionInfo"), cli.GetField("remoteAddress"));
            r.add("remotePort", cl.GetMethod("getConnectionInfo"), cli.GetField("remotePort"));
            
            cli = typeof(Ice.UDPConnectionInfo);
            r.add("mcastHost", cl.GetMethod("getConnectionInfo"), cli.GetField("mcastAddress"));
            r.add("mcastPort", cl.GetMethod("getConnectionInfo"), cli.GetField("mcastPort"));
            
            AttrsUtil.addEndpointAttributes<T>(r, cl);
        }
    }

    class ConnectionHelper : MetricsHelper<ConnectionMetrics>
    {
        class AttributeResolverI : MetricsHelper<ConnectionMetrics>.AttributeResolver
        {
            public AttributeResolverI()
            {
                try
                {
                    Type cl = typeof(ConnectionHelper);
                    add("parent", cl.GetMethod("getParent"));
                    add("id", cl.GetMethod("getId"));
                    add("state", cl.GetMethod("getState"));
                    AttrsUtil.addConnectionAttributes<ConnectionMetrics>(this, cl);
                }
                catch(Exception)
                {
                    Debug.Assert(false);
                }
            }
        };
        static AttributeResolver _attributes = new AttributeResolverI();
        
        public ConnectionHelper(Ice.ConnectionInfo con, Ice.Endpoint endpt, Ice.Instrumentation.ConnectionState state) 
            : base(_attributes)
        {
            _connectionInfo = con;
            _endpoint = endpt;
            _state = state;
        }

        public string getId()
        {
            if(_id == null)
            {
                StringBuilder os = new StringBuilder();
                if(_connectionInfo is Ice.IPConnectionInfo)
                {
                    Ice.IPConnectionInfo info = (Ice.IPConnectionInfo)_connectionInfo;
                    os.Append(info.localAddress).Append(':').Append(info.localPort);
                    os.Append(" -> ");
                    os.Append(info.remoteAddress).Append(':').Append(info.remotePort);
                }
                else
                {
                    os.Append("connection-").Append(_connectionInfo);
                }
                if(_connectionInfo.connectionId.Length > 0)
                {
                    os.Append(" [").Append(_connectionInfo.connectionId).Append("]");
                }
                _id = os.ToString();
            }
            return _id;
        }

        public string getState()
        {
            switch(_state)
            {
            case Ice.Instrumentation.ConnectionState.ConnectionStateValidating:
                return "validating";
            case Ice.Instrumentation.ConnectionState.ConnectionStateHolding:
                return "holding";
            case Ice.Instrumentation.ConnectionState.ConnectionStateActive:
                return "active";
            case Ice.Instrumentation.ConnectionState.ConnectionStateClosing:
                return "closing";
            case Ice.Instrumentation.ConnectionState.ConnectionStateClosed:
                return "closed";
            default:
                Debug.Assert(false);
                return "";
            }
        }
        
        public string getParent()
        {
            if(_connectionInfo.adapterName != null && _connectionInfo.adapterName.Length > 0)
            {
                return _connectionInfo.adapterName;
            }
            else
            {
                return "Communicator";
            }
        }
    
        public Ice.ConnectionInfo getConnectionInfo()
        {
            return _connectionInfo;
        }

        public Ice.Endpoint getEndpoint()
        {
            return _endpoint;
        }

        public Ice.EndpointInfo getEndpointInfo()
        {
            if(_endpointInfo == null)
            {
                _endpointInfo = _endpoint.getInfo();
            }
            return _endpointInfo;
        }

        readonly private Ice.ConnectionInfo _connectionInfo;
        readonly private Ice.Endpoint _endpoint;
        readonly private Ice.Instrumentation.ConnectionState _state;
        private string _id;
        private Ice.EndpointInfo _endpointInfo;
    };

    class DispatchHelper : MetricsHelper<DispatchMetrics>
    {
        class AttributeResolverI : MetricsHelper<DispatchMetrics>.AttributeResolver
        {
            public AttributeResolverI()
            {
                try
                {
                    Type cl = typeof(DispatchHelper);
                    add("parent", cl.GetMethod("getParent"));
                    add("id", cl.GetMethod("getId"));
                    
                    AttrsUtil.addConnectionAttributes<DispatchMetrics>(this, cl);
                    
                    Type clc = typeof(Ice.Current);
                    add("operation", cl.GetMethod("getCurrent"), clc.GetField("operation"));
                    add("identity", cl.GetMethod("getIdentity"));
                    add("facet", cl.GetMethod("getCurrent"), clc.GetField("facet"));
                    add("current", cl.GetMethod("getCurrent"), clc.GetField("requestId"));
                    add("mode", cl.GetMethod("getMode"));
                }
                catch(Exception)
                {
                    Debug.Assert(false);
                }
            }
        };
        static AttributeResolver _attributes = new AttributeResolverI();
        
        public DispatchHelper(Ice.Current current, int size) : base(_attributes)
        {
            _current = current;
            _size = size;
        }

        override protected string defaultResolve(string attribute)
        {
            if(attribute.IndexOf("context.", 0) == 0)
            {
                string v;
                if(_current.ctx.TryGetValue(attribute.Substring(8), out v))
                {
                    return v;
                }
            }
            throw new ArgumentOutOfRangeException(attribute);
        }

        override public void initMetrics(DispatchMetrics v)
        {
            v.size += _size;
        }
        
        public string getMode()
        {
            return _current.requestId == 0 ? "oneway" : "twoway";
        }

        public string getId()
        {
            if(_id == null)
            {
                StringBuilder os = new StringBuilder();
                if(_current.id.category != null && _current.id.category.Length > 0)
                {
                    os.Append(_current.id.category).Append('/');
                }
                os.Append(_current.id.name).Append(" [").Append(_current.operation).Append(']');
                _id = os.ToString();
            }
            return _id;
        }

        public string getParent()
        {
            return _current.adapter.getName();
        }
        
        public Ice.ConnectionInfo getConnectionInfo()
        {
            return _current.con.getInfo();
        }
        
        public Ice.Endpoint getEndpoint()
        {
            return _current.con.getEndpoint();
        }

        public Ice.Connection getConnection()
        {
            return _current.con;
        }
        
        public Ice.EndpointInfo getEndpointInfo()
        {
            if(_endpointInfo == null)
            {
                _endpointInfo = _current.con.getEndpoint().getInfo();
            }
            return _endpointInfo;
        }

        public Ice.Current getCurrent()
        {
            return _current;
        }
        
        public string getIdentity()
        {
            return _current.adapter.getCommunicator().identityToString(_current.id);
        }
        
        readonly private Ice.Current _current;
        readonly private int _size;
        private string _id;
        private Ice.EndpointInfo _endpointInfo;
    };

    class InvocationHelper : MetricsHelper<InvocationMetrics>
    {
        class AttributeResolverI : MetricsHelper<InvocationMetrics>.AttributeResolver
        { 
            public AttributeResolverI()
            {
                try
                {
                    Type cl = typeof(InvocationHelper);
                    add("parent", cl.GetMethod("getParent"));
                    add("id", cl.GetMethod("getId"));
                        
                    add("operation", cl.GetMethod("getOperation"));
                    add("identity", cl.GetMethod("getIdentity"));
                        
                    Type cli = typeof(Ice.ObjectPrx);
                    add("facet", cl.GetMethod("getProxy"), cli.GetMethod("ice_getFacet"));
                    add("encoding", cl.GetMethod("getEncodingVersion"));
                    add("mode", cl.GetMethod("getMode"));
                    add("proxy", cl.GetMethod("getProxy"));
                }
                catch(Exception)
                {
                    Debug.Assert(false);
                }
            }
        };
        static AttributeResolver _attributes = new AttributeResolverI();
        
        public InvocationHelper(Ice.ObjectPrx proxy, string op, Dictionary<string, string> ctx) : base(_attributes)
        {
            _proxy = proxy;
            _operation = op;
            _context = ctx;
        }

        override protected string defaultResolve(string attribute)
        {
            if(attribute.IndexOf("context.", 0) == 0)
            {
                string v;
                if(_context.TryGetValue(attribute.Substring(8), out v))
                {
                    return v;
                }
            }
            throw new ArgumentOutOfRangeException(attribute);
        }
        
        public string getMode()
        {
            if(_proxy == null)
            {
                throw new ArgumentOutOfRangeException("mode");
            }
            
            if(_proxy.ice_isTwoway())
            {
                return "twoway";
            } 
            else if(_proxy.ice_isOneway())
            {
                return "oneway";
            } 
            else if(_proxy.ice_isBatchOneway())
            {
                return "batch-oneway";
            } 
            else if(_proxy.ice_isDatagram())
            {
                return "datagram";
            } 
            else if(_proxy.ice_isBatchDatagram())
            {
                return "batch-datagram";
            } 
            else
            {
                throw new ArgumentOutOfRangeException("mode");
            }
        }

        public string getId()
        {
            if(_id == null)
            {
                if(_proxy != null)
                {
                    StringBuilder os = new StringBuilder();
                    try
                    {
                        os.Append(_proxy.ice_endpoints(emptyEndpoints)).Append(" [").Append(_operation).Append(']');
                    }
                    catch(Ice.Exception)
                    {
                        // Either a fixed proxy or the communicator is destroyed.
                        os.Append(_proxy.ice_getCommunicator().identityToString(_proxy.ice_getIdentity()));
                        os.Append(" [").Append(_operation).Append(']');
                    }
                    _id = os.ToString();
                }
                else
                {
                    _id = _operation;
                }
            }
            return _id;
        }
        
        public string getParent()
        {
            return "Communicator";
        }
        
        public Ice.ObjectPrx getProxy()
        {
            return _proxy;
        }

        public string getEncodingVersion()
        {
            return Ice.Util.encodingVersionToString(_proxy.ice_getEncodingVersion());
        }
        
        public string getIdentity()
        {
            if(_proxy != null)
            {
                return _proxy.ice_getCommunicator().identityToString(_proxy.ice_getIdentity());
            }
            else
            {
                return "";
            }
        }
        
        public string getOperation()
        {
            return _operation;
        }
        
        readonly private Ice.ObjectPrx _proxy;
        readonly private string _operation;
        readonly private Dictionary<string, string> _context;
        private string _id;

        readonly static private Ice.Endpoint[] emptyEndpoints = new Ice.Endpoint[0];
    };
    
    class ThreadHelper : MetricsHelper<ThreadMetrics>
    {
        class AttributeResolverI : MetricsHelper<ThreadMetrics>.AttributeResolver
        { 
            public AttributeResolverI()
            {
                try
                {
                    Type cl = typeof(ThreadHelper);
                    add("parent", cl.GetField("_parent"));
                    add("id", cl.GetField("_id"));
                }
                catch(Exception)
                {
                    Debug.Assert(false);
                }
            }
        };
        static AttributeResolver _attributes = new AttributeResolverI();

        public ThreadHelper(string parent, string id, Ice.Instrumentation.ThreadState state) : base(_attributes)
        {
            _parent = parent;
            _id = id;
            _state = state;
        }

        override public void initMetrics(ThreadMetrics v)
        {
            switch(_state)
            {
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForIO:
                ++v.inUseForIO;
                break;
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForUser:
                ++v.inUseForUser;
                break;
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForOther:
                ++v.inUseForOther;
                break;
            default:
                break;
            }
        }
        
        readonly public string _parent;
        readonly public string _id;
        readonly private Ice.Instrumentation.ThreadState _state;
    };

    class EndpointHelper : MetricsHelper<Metrics>
    {
        class AttributeResolverI : MetricsHelper<Metrics>.AttributeResolver
        { 
            public AttributeResolverI()
            {
                try
                {
                    Type cl = typeof(EndpointHelper);
                    add("parent", cl.GetMethod("getParent"));
                    add("id", cl.GetMethod("getId"));
                    AttrsUtil.addEndpointAttributes<Metrics>(this, cl);
                }
                catch(Exception)
                {
                    Debug.Assert(false);
                }
            }
        };
        static AttributeResolver _attributes = new AttributeResolverI();

        public EndpointHelper(Ice.Endpoint endpt, string id) : base(_attributes)
        {
            _endpoint = endpt;
            _id = id;
        }

        public EndpointHelper(Ice.Endpoint endpt) : base(_attributes)
        {
            _endpoint = endpt;
        }
        
        public Ice.EndpointInfo getEndpointInfo()
        {
            if(_endpointInfo == null)
            {
                _endpointInfo = _endpoint.getInfo();
            }
            return _endpointInfo;
        }

        public string getParent()
        {
            return "Communicator";
        }
        
        public string getId()
        {
            if(_id == null)
            {
                _id = _endpoint.ToString();
            }
            return _id;
        }
        
        public string getEndpoint()
        {
            return _endpoint.ToString();
        }
        
        readonly private Ice.Endpoint _endpoint;
        private string _id;
        private Ice.EndpointInfo _endpointInfo;
    };
    
    public class RemoteInvocationHelper : MetricsHelper<RemoteMetrics>
    {
        class AttributeResolverI : MetricsHelper<RemoteMetrics>.AttributeResolver
        { 
            public AttributeResolverI()
            {
                try
                {
                    Type cl = typeof(RemoteInvocationHelper);
                    add("parent", cl.GetMethod("getParent"));
                    add("id", cl.GetMethod("getId"));
                    add("requestId", cl.GetMethod("getRequestId"));
                    AttrsUtil.addConnectionAttributes<RemoteMetrics>(this, cl);
                }
                catch(Exception)
                {
                    Debug.Assert(false);
                }
            }
        };
        static AttributeResolver _attributes = new AttributeResolverI();

        public RemoteInvocationHelper(Ice.ConnectionInfo con, Ice.Endpoint endpt, int requestId, int size) :
            base(_attributes)
        {
            _connectionInfo = con;
            _endpoint = endpt;
            _requestId = requestId;
            _size = size;
        }

        override public void initMetrics(RemoteMetrics v)
        {
            v.size += _size;
        }

        public string getId()
        {
            if(_id == null)
            {
                _id = _endpoint.ToString();
                if(_connectionInfo.connectionId != null && _connectionInfo.connectionId.Length > 0)
                {
                    _id += " [" + _connectionInfo.connectionId + "]";
                }
            }
            return _id;
        }

        public int getRequestId()
        {
            return _requestId;
        }
    
        public string getParent()
        {
            if(_connectionInfo.adapterName != null && _connectionInfo.adapterName.Length > 0)
            {
                return _connectionInfo.adapterName;
            }
            else
            {
                return "Communicator";
            }
        }
        
        public Ice.ConnectionInfo getConnectionInfo()
        {
            return _connectionInfo;
        }
        
        public Ice.Endpoint getEndpoint()
        {
            return _endpoint;
        }

        public Ice.EndpointInfo getEndpointInfo()
        {
            if(_endpointInfo == null)
            {
                _endpointInfo = _endpoint.getInfo();
            }
            return _endpointInfo;
        }

        readonly private Ice.ConnectionInfo _connectionInfo;
        readonly private Ice.Endpoint _endpoint;
        readonly private int _size;
        readonly private int _requestId;
        private string _id;
        private Ice.EndpointInfo _endpointInfo;
    };

    public class ObserverWithDelegateI : ObserverWithDelegate<Metrics, Ice.Instrumentation.Observer>
    {
    };

    public class ConnectionObserverI : ObserverWithDelegate<ConnectionMetrics, Ice.Instrumentation.ConnectionObserver>,
        Ice.Instrumentation.ConnectionObserver
    {
        public void sentBytes(int num)
        {
            _sentBytes = num;
            forEach(sentBytesUpdate);
            if(delegate_ != null)
            {
                delegate_.sentBytes(num);
            }
        }

        public void receivedBytes(int num)
        {
            _receivedBytes = num;
            forEach(receivedBytesUpdate);
            if(delegate_ != null)
            {
                delegate_.receivedBytes(num);
            }
        }

        private void sentBytesUpdate(ConnectionMetrics v)
        {
            v.sentBytes += _sentBytes;
        }

        private void receivedBytesUpdate(ConnectionMetrics v)
        {
            v.receivedBytes += _receivedBytes;
        }

        private int _sentBytes;
        private int _receivedBytes;
    };

    public class DispatchObserverI : ObserverWithDelegate<DispatchMetrics, Ice.Instrumentation.DispatchObserver>,
        Ice.Instrumentation.DispatchObserver
    {
        public void
        userException()
        {
            forEach(userException);
            if(delegate_ != null)
            {
                delegate_.userException();
            }
        }

        public void reply(int size)
        {
            forEach((DispatchMetrics v) => {
                    v.replySize += size;
                });
            if(delegate_ != null)
            {
                delegate_.reply(size);
            }
        }

        private void userException(DispatchMetrics v)
        {
            ++v.userException;
        }
    }

    public class RemoteObserverI : ObserverWithDelegate<RemoteMetrics, Ice.Instrumentation.RemoteObserver>,
        Ice.Instrumentation.RemoteObserver
    {
        public void reply(int size)
        {
            forEach((RemoteMetrics v) => {
                    v.replySize += size;
                });
            if(delegate_ != null)
            {
                delegate_.reply(size);
            }
        }
    }

    public class InvocationObserverI : ObserverWithDelegate<InvocationMetrics, Ice.Instrumentation.InvocationObserver>,
        Ice.Instrumentation.InvocationObserver
    {
        public void
        userException()
        {
            forEach(userException);
            if(delegate_ != null)
            {
                delegate_.userException();
            }
        }

        public void
        retried()
        {
            forEach(incrementRetry);
            if(delegate_ != null)
            {
                delegate_.retried();
            }
        }
    
        public Ice.Instrumentation.RemoteObserver getRemoteObserver(Ice.ConnectionInfo con, Ice.Endpoint endpt, 
                                                                    int requestId, int size)
        {
            Ice.Instrumentation.RemoteObserver del = null;
            if(delegate_ != null)
            {
                del = delegate_.getRemoteObserver(con, endpt, requestId, size);
            }
            return getObserver<RemoteMetrics, RemoteObserverI, 
                Ice.Instrumentation.RemoteObserver>("Remote", 
                                                    new RemoteInvocationHelper(con, endpt, requestId, size),
                                                    del);
        }

        private void incrementRetry(InvocationMetrics v)
        {
            ++v.retry;
        }

        private void userException(InvocationMetrics v)
        {
            ++v.userException;
        }
    }

    public class ThreadObserverI : ObserverWithDelegate<ThreadMetrics, Ice.Instrumentation.ThreadObserver>,
        Ice.Instrumentation.ThreadObserver
    {
        public void stateChanged(Ice.Instrumentation.ThreadState oldState, Ice.Instrumentation.ThreadState newState)
        {
            _oldState = oldState;
            _newState = newState;
            forEach(threadStateUpdate);
            if(delegate_ != null)
            {
                delegate_.stateChanged(oldState, newState);
            }
        }

        private void threadStateUpdate(ThreadMetrics v)
        {
            switch(_oldState)
            {
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForIO:
                --v.inUseForIO;
                break;
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForUser:
                --v.inUseForUser;
                break;
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForOther:
                --v.inUseForOther;
                break;
            default:
                break;
            }
            switch(_newState)
            {
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForIO:
                ++v.inUseForIO;
                break;
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForUser:
                ++v.inUseForUser;
                break;
            case Ice.Instrumentation.ThreadState.ThreadStateInUseForOther:
                ++v.inUseForOther;
                break;
            default:
                break;
            }
        }

        private Ice.Instrumentation.ThreadState _oldState;
        private Ice.Instrumentation.ThreadState _newState;
    };

    public class CommunicatorObserverI : Ice.Instrumentation.CommunicatorObserver
    {
        public CommunicatorObserverI(IceInternal.MetricsAdminI metrics) : this(metrics, null)
        {
        }

        public CommunicatorObserverI(IceInternal.MetricsAdminI metrics, 
                                     Ice.Instrumentation.CommunicatorObserver del)
        {
            _metrics = metrics;
            _delegate = del;
            _connections = new ObserverFactoryWithDelegate<ConnectionMetrics, ConnectionObserverI,
                Ice.Instrumentation.ConnectionObserver>(metrics, "Connection");
            _dispatch = new ObserverFactoryWithDelegate<DispatchMetrics, DispatchObserverI,
                Ice.Instrumentation.DispatchObserver>(metrics, "Dispatch");
            _invocations = new ObserverFactoryWithDelegate<InvocationMetrics, InvocationObserverI,
                Ice.Instrumentation.InvocationObserver>(metrics, "Invocation");
            _threads = new ObserverFactoryWithDelegate<ThreadMetrics, ThreadObserverI,
                Ice.Instrumentation.ThreadObserver>(metrics, "Thread");
            _connects = new ObserverFactoryWithDelegate<Metrics, ObserverWithDelegateI,
                Ice.Instrumentation.Observer>(metrics, "ConnectionEstablishment");
            _endpointLookups = new ObserverFactoryWithDelegate<Metrics, ObserverWithDelegateI,
                Ice.Instrumentation.Observer>(metrics, "EndpointLookup");

            try
            {
                _invocations.registerSubMap<RemoteMetrics>("Remote", typeof(InvocationMetrics).GetField("remotes"));
            }
            catch(Exception)
            {
                Debug.Assert(false);
            }
        }

        public Ice.Instrumentation.Observer getConnectionEstablishmentObserver(Ice.Endpoint endpt, string connector)
        {
            if(_connects.isEnabled())
            {
                try
                {
                    Ice.Instrumentation.Observer del = null;
                    if(_delegate != null)
                    {
                        del = _delegate.getConnectionEstablishmentObserver(endpt, connector);
                    }
                    return _connects.getObserver(new EndpointHelper(endpt, connector), del);
                }
                catch(Exception ex)
                {
                    _metrics.getLogger().error("unexpected exception trying to obtain observer:\n" + ex);
                }
            }
            return null;
        }

        public Ice.Instrumentation.Observer getEndpointLookupObserver(Ice.Endpoint endpt)
        {
            if(_endpointLookups.isEnabled())
            {
                try
                {
                    Ice.Instrumentation.Observer del = null;
                    if(_delegate != null)
                    {
                        del = _delegate.getEndpointLookupObserver(endpt);
                    }
                    return _endpointLookups.getObserver(new EndpointHelper(endpt), del);
                }
                catch(Exception ex)
                {
                    _metrics.getLogger().error("unexpected exception trying to obtain observer:\n" + ex);
                }
            }
            return null;
        }
    
        public Ice.Instrumentation.ConnectionObserver getConnectionObserver(Ice.ConnectionInfo c, 
                                                                            Ice.Endpoint e,
                                                                            Ice.Instrumentation.ConnectionState s,
                                                                            Ice.Instrumentation.ConnectionObserver obsv)
        {
            if(_connections.isEnabled())
            {
                try
                {
                    Ice.Instrumentation.ConnectionObserver del = null;
                    ConnectionObserverI o = obsv is ConnectionObserverI ? (ConnectionObserverI)obsv : null;
                    if(_delegate != null)
                    {
                        del = _delegate.getConnectionObserver(c, e, s, o != null ? o.getDelegate() : obsv);
                    }
                    return _connections.getObserver(new ConnectionHelper(c, e, s), obsv, del);
                }
                catch(Exception ex)
                {
                    _metrics.getLogger().error("unexpected exception trying to obtain observer:\n" + ex);
                }
            }
            return null;
        }
    
        public Ice.Instrumentation.ThreadObserver getThreadObserver(string parent, string id, 
                                                                    Ice.Instrumentation.ThreadState s, 
                                                                    Ice.Instrumentation.ThreadObserver obsv)
        {
            if(_threads.isEnabled())
            {
                try
                {
                    Ice.Instrumentation.ThreadObserver del = null;
                    ThreadObserverI o = obsv is ThreadObserverI ? (ThreadObserverI)obsv : null;
                    if(_delegate != null)
                    {
                        del = _delegate.getThreadObserver(parent, id, s, o != null ? o.getDelegate() : obsv);
                    }
                    return _threads.getObserver(new ThreadHelper(parent, id, s), obsv, del);
                }
                catch(Exception ex)
                {
                    _metrics.getLogger().error("unexpected exception trying to obtain observer:\n" + ex);
                }
            }
            return null;
        }
    
        public Ice.Instrumentation.InvocationObserver getInvocationObserver(Ice.ObjectPrx prx, string operation, 
                                                                            Dictionary<string, string> ctx)
        {
            if(_invocations.isEnabled())
            {
                try
                {
                    Ice.Instrumentation.InvocationObserver del = null;
                    if(_delegate != null)
                    {
                        del = _delegate.getInvocationObserver(prx, operation, ctx);
                    }
                    return _invocations.getObserver(new InvocationHelper(prx, operation, ctx), del);
                }
                catch(Exception ex)
                {
                    _metrics.getLogger().error("unexpected exception trying to obtain observer:\n" + ex);
                }
            }
            return null;
        }
    
        public Ice.Instrumentation.DispatchObserver getDispatchObserver(Ice.Current c, int size)
        {
            if(_dispatch.isEnabled())
            {
                try
                {
                    Ice.Instrumentation.DispatchObserver del = null;
                    if(_delegate != null)
                    {
                        del = _delegate.getDispatchObserver(c, size);
                    }
                    return _dispatch.getObserver(new DispatchHelper(c, size), del);
                }
                catch(Exception ex)
                {
                    _metrics.getLogger().error("unexpected exception trying to obtain observer:\n" + ex);
                }
            }
            return null;
        }
    
        public void setObserverUpdater(Ice.Instrumentation.ObserverUpdater updater)
        {
            _connections.setUpdater(updater.updateConnectionObservers);
            _threads.setUpdater(updater.updateThreadObservers);
            if(_delegate != null)
            {
                _delegate.setObserverUpdater(updater);
            }
        }

        public IceInternal.MetricsAdminI getMetricsAdmin()
        {
            return _metrics;
        }

        readonly private IceInternal.MetricsAdminI _metrics;
        readonly private Ice.Instrumentation.CommunicatorObserver _delegate;
        readonly private ObserverFactoryWithDelegate<ConnectionMetrics, ConnectionObserverI,
            Ice.Instrumentation.ConnectionObserver> _connections;
        readonly private ObserverFactoryWithDelegate<DispatchMetrics, DispatchObserverI,
            Ice.Instrumentation.DispatchObserver> _dispatch;
        readonly private ObserverFactoryWithDelegate<InvocationMetrics, InvocationObserverI,
            Ice.Instrumentation.InvocationObserver> _invocations;
        readonly private ObserverFactoryWithDelegate<ThreadMetrics, ThreadObserverI,
            Ice.Instrumentation.ThreadObserver> _threads;
        readonly private ObserverFactoryWithDelegate<Metrics, ObserverWithDelegateI,
            Ice.Instrumentation.Observer> _connects;
        readonly private ObserverFactoryWithDelegate<Metrics, ObserverWithDelegateI,
            Ice.Instrumentation.Observer> _endpointLookups;
    }
}