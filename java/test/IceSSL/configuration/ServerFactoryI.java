// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.IceSSL.configuration;
import test.IceSSL.configuration.Test.ServerPrx;
import test.IceSSL.configuration.Test.ServerPrxHelper;
import test.IceSSL.configuration.Test._ServerFactoryDisp;

class ServerFactoryI extends _ServerFactoryDisp
{
    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    public ServerPrx
    createServer(java.util.Map<String, String> props, Ice.Current current)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties();
        for(java.util.Map.Entry<String, String> i : props.entrySet())
        {
            initData.properties.setProperty(i.getKey(), i.getValue());
        }

        String[] args = new String[0];
        Ice.Communicator communicator = Ice.Util.initialize(args, initData);
        Ice.ObjectAdapter adapter = communicator.createObjectAdapterWithEndpoints("ServerAdapter", "ssl");
        ServerI server = new ServerI(communicator);
        Ice.ObjectPrx obj = adapter.addWithUUID(server);
        _servers.put(obj.ice_getIdentity(), server);
        adapter.activate();

        return ServerPrxHelper.uncheckedCast(obj);
    }

    public void
    destroyServer(ServerPrx srv, Ice.Current current)
    {
        Ice.Identity key = srv.ice_getIdentity();
        if(_servers.containsKey(key))
        {
            ServerI server = _servers.get(key);
            server.destroy();
            _servers.remove(key);
        }
    }

    public void
    shutdown(Ice.Current current)
    {
        test(_servers.size() == 0);
        current.adapter.getCommunicator().shutdown();
    }

    private java.util.Map<Ice.Identity, ServerI> _servers = new java.util.HashMap<Ice.Identity, ServerI>();
}
