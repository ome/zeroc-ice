# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import Ice, Test, Twoways, TwowaysAMI, TwowaysNewAMI, Oneways, OnewaysAMI, OnewaysNewAMI, BatchOneways, sys

def test(b):
    if not b:
        raise RuntimeError('test assertion failed')

def allTests(communicator, collocated):
    ref = "test:default -p 12010"
    base = communicator.stringToProxy(ref)
    cl = Test.MyClassPrx.checkedCast(base)
    derived = Test.MyDerivedClassPrx.checkedCast(cl)

    sys.stdout.write("testing twoway operations... ")
    sys.stdout.flush()
    Twoways.twoways(communicator, cl)
    Twoways.twoways(communicator, derived)
    derived.opDerived()
    print("ok")

    sys.stdout.write("testing oneway operations... ")
    sys.stdout.flush()
    Oneways.oneways(communicator, cl)
    print("ok")

    if not collocated:
        sys.stdout.write("testing twoway operations with AMI... ")
        sys.stdout.flush()
        TwowaysAMI.twowaysAMI(communicator, cl)
        print("ok")

        sys.stdout.write("testing twoway operations with new AMI mapping... ")
        sys.stdout.flush()
        TwowaysNewAMI.twowaysNewAMI(communicator, cl)
        print("ok")

        sys.stdout.write("testing oneway operations with AMI... ")
        sys.stdout.flush()
        OnewaysAMI.onewaysAMI(communicator, cl)
        print("ok")

        sys.stdout.write("testing oneway operations with new AMI mapping... ")
        sys.stdout.flush()
        OnewaysNewAMI.onewaysNewAMI(communicator, cl)
        print("ok")

        sys.stdout.write("testing batch oneway operations...  ")
        sys.stdout.flush()
        BatchOneways.batchOneways(cl)
        BatchOneways.batchOneways(derived)
        print("ok")

    return cl
