# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import sys, Ice, Test

def test(b):
    if not b:
        raise RuntimeError('test assertion failed')

def allTests(communicator):
    sys.stdout.write("testing stringToProxy... ")
    sys.stdout.flush()
    base = communicator.stringToProxy("test:default -p 12010")
    test(base)
    print("ok")

    sys.stdout.write("testing checked cast... ")
    sys.stdout.flush()
    obj = Test.TestIntfPrx.checkedCast(base)
    test(obj)
    test(obj == base)
    print("ok")

    sys.stdout.write("creating/destroying/recreating object adapter... ")
    sys.stdout.flush()
    adapter = communicator.createObjectAdapterWithEndpoints("TransientTestAdapter", "default")
    try:
        communicator.createObjectAdapterWithEndpoints("TransientTestAdapter", "default")
        test(False)
    except Ice.LocalException:
        pass
    adapter.destroy()

    adapter = communicator.createObjectAdapterWithEndpoints("TransientTestAdapter", "default")
    adapter.destroy()
    print("ok")

    sys.stdout.write("creating/activating/deactivating object adapter in one operation... ")
    sys.stdout.flush()
    obj.transient()
    print("ok")

    sys.stdout.write("deactivating object adapter in the server... ")
    sys.stdout.flush()
    obj.deactivate()
    print("ok")

    sys.stdout.write("testing connection closure... ");
    sys.stdout.flush();
    for x in range(10):
        initData = Ice.InitializationData();
        initData.properties = communicator.getProperties().clone();
        comm = Ice.initialize(initData);
        comm.stringToProxy("test:default -p 12010").begin_ice_ping();
        comm.destroy();
    print("ok");

    sys.stdout.write("testing whether server is gone... ")
    sys.stdout.flush()
    try:
        obj.ice_ping()
        test(False)
    except Ice.LocalException:
        print("ok")

    return obj
