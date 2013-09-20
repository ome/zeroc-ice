#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import Ice, gc, sys, threading

Ice.loadSlice('-I. --all Forward.ice ClientPrivate.ice')
import Test

def test(b):
    if not b:
        raise RuntimeError('test assertion failed')

class CallbackBase:
    def __init__(self):
        self._called = False
        self._cond = threading.Condition()

    def check(self):
        self._cond.acquire()
        try:
            while not self._called:
                self._cond.wait()
            self._called = False
        finally:
            self._cond.release()

    def called(self):
        self._cond.acquire()
        self._called = True
        self._cond.notify()
        self._cond.release()

class Callback(CallbackBase):
    def response_SBaseAsObject(self, o):
        test(o)
        test(o.ice_id() == "::Test::SBase")
        sb = o
        test(isinstance(sb, Test.SBase))
        test(sb.sb == "SBase.sb")
        self.called()

    def response_SBaseAsSBase(self, sb):
        test(sb.sb == "SBase.sb")
        self.called()

    def response_SBSKnownDerivedAsSBase(self, sb):
        sbskd = sb
        test(isinstance(sbskd, Test.SBSKnownDerived))
        test(sbskd.sbskd == "SBSKnownDerived.sbskd")
        self.called()

    def response_SBSKnownDerivedAsSBSKnownDerived(self, sbskd):
        test(sbskd.sbskd == "SBSKnownDerived.sbskd")
        self.called()

    def response_SBSUnknownDerivedAsSBase(self, sb):
        test(sb.sb == "SBSUnknownDerived.sb")
        self.called()

    def response_SBSUnknownDerivedAsSBaseCompact(self, sb):
        test(False)

    def exception_SBSUnknownDerivedAsSBaseCompact(self, ex):
        test(isinstance(ex, Ice.NoObjectFactoryException))
        self.called()

    def response_SUnknownAsObject10(self, o):
        test(False)

    def exception_SUnknownAsObject10(self, exc):
        test(exc.ice_name() == "Ice::NoObjectFactoryException")
        self.called()

    def response_SUnknownAsObject11(self, o):
        test(isinstance(o, Ice.UnknownSlicedObject))
        test(o.unknownTypeId == "::Test::SUnknown")
        self.called()

    def exception_SUnknownAsObject11(self, exc):
        test(False)

    def response_oneElementCycle(self, b):
        test(b)
        test(b.ice_id() == "::Test::B")
        test(b.sb == "B1.sb")
        test(b.pb == b)
        self.called()

    def response_twoElementCycle(self, b1):
        test(b1)
        test(b1.ice_id() == "::Test::B")
        test(b1.sb == "B1.sb")

        b2 = b1.pb
        test(b2)
        test(b2.ice_id() == "::Test::B")
        test(b2.sb == "B2.sb")
        test(b2.pb == b1)
        self.called()

    def response_D1AsB(self, b1):
        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb)
        test(b1.pb != b1)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1)
        test(d1.pd1 != b1)
        test(b1.pb == d1.pd1)

        b2 = b1.pb
        test(b2)
        test(b2.pb == b1)
        test(b2.sb == "D2.sb")
        test(b2.ice_id() == "::Test::B")
        self.called()

    def response_D1AsD1(self, d1):
        test(d1)
        test(d1.ice_id() == "::Test::D1")
        test(d1.sb == "D1.sb")
        test(d1.pb)
        test(d1.pb != d1)

        b2 = d1.pb
        test(b2)
        test(b2.ice_id() == "::Test::B")
        test(b2.sb == "D2.sb")
        test(b2.pb == d1)
        self.called()

    def response_D2AsB(self, b2):
        test(b2)
        test(b2.ice_id() == "::Test::B")
        test(b2.sb == "D2.sb")
        test(b2.pb)
        test(b2.pb != b2)

        b1 = b2.pb
        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb == b2)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1 == b2)
        self.called()

    def response_paramTest1(self, b1, b2):
        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb == b2)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1 == b2)

        test(b2)
        test(b2.ice_id() == "::Test::B")        # No factory, must be sliced
        test(b2.sb == "D2.sb")
        test(b2.pb == b1)
        self.called()

    def response_returnTest1(self, r, p1, p2):
        test(r == p1)
        self.called()

    def response_returnTest2(self, r, p1, p2):
        test(r == p1)
        self.called()

    def response_returnTest3(self, b):
        self.r = b
        self.called()

    def response_paramTest3(self, ret, p1, p2):
        test(p1)
        test(p1.sb == "D2.sb (p1 1)")
        test(p1.pb == None)
        test(p1.ice_id() == "::Test::B")

        test(p2)
        test(p2.sb == "D2.sb (p2 1)")
        test(p2.pb == None)
        test(p2.ice_id() == "::Test::B")

        test(ret)
        test(ret.sb == "D1.sb (p2 2)")
        test(ret.pb == None)
        test(ret.ice_id() == "::Test::D1")
        self.called()

    def response_paramTest4(self, ret, b):
        test(b)
        test(b.sb == "D4.sb (1)")
        test(b.pb == None)
        test(b.ice_id() == "::Test::B")

        test(ret)
        test(ret.sb == "B.sb (2)")
        test(ret.pb == None)
        test(ret.ice_id() == "::Test::B")
        self.called()

    def response_sequenceTest(self, ss):
        self.r = ss
        self.called()

    def response_dictionaryTest(self, r, bout):
        self.r = r
        self.bout = bout
        self.called()

    def exception_throwBaseAsBase(self, ex):
        test(ex.ice_name() == "Test::BaseException")
        e = ex
        test(isinstance(e, Test.BaseException))
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb")
        test(e.pb.pb == e.pb)
        self.called()

    def exception_throwDerivedAsBase(self, ex):
        test(ex.ice_name() == "Test::DerivedException")
        e = ex
        test(isinstance(e, Test.DerivedException))
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb1")
        test(e.pb.pb == e.pb)
        test(e.sde == "sde1")
        test(e.pd1)
        test(e.pd1.sb == "sb2")
        test(e.pd1.pb == e.pd1)
        test(e.pd1.sd1 == "sd2")
        test(e.pd1.pd1 == e.pd1)
        self.called()

    def exception_throwDerivedAsDerived(self, ex):
        test(ex.ice_name() == "Test::DerivedException")
        e = ex
        test(isinstance(e, Test.DerivedException))
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb1")
        test(e.pb.pb == e.pb)
        test(e.sde == "sde1")
        test(e.pd1)
        test(e.pd1.sb == "sb2")
        test(e.pd1.pb == e.pd1)
        test(e.pd1.sd1 == "sd2")
        test(e.pd1.pd1 == e.pd1)
        self.called()

    def exception_throwUnknownDerivedAsBase(self, ex):
        test(ex.ice_name() == "Test::BaseException")
        e = ex
        test(isinstance(e, Test.BaseException))
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb d2")
        test(e.pb.pb == e.pb)
        self.called()

    def response_useForward(self, f):
        test(f)
        self.called()

    def response_preserved1(self, r):
        test(r)
        test(isinstance(r, Test.PDerived))
        test(r.pi == 3)
        test(r.ps == "preserved")
        test(r.pb == r)
        self.called()

    def response_preserved2(self, r):
        test(r)
        test(not isinstance(r, Test.PCUnknown))
        test(r.pi == 3)
        self.called()

    def response_preserved3(self, r):
        #
        # Encoding 1.0
        #
        test(not isinstance(r, Test.PCDerived))
        test(r.pi == 3)
        self.called()

    def response_preserved4(self, r):
        #
        # Encoding > 1.0
        #
        test(isinstance(r, Test.PCDerived))
        test(r.pi == 3)
        test(r.pbs[0] == r)
        self.called()

    def response_preserved5(self, r):
        test(isinstance(r, Test.PCDerived3))
        test(r.pi == 3)
        for i in range(0, 300):
            p2 = r.pbs[i]
            test(isinstance(p2, Test.PCDerived2))
            test(p2.pi == i)
            test(len(p2.pbs) == 1)
            test(not p2.pbs[0])
            test(p2.pcd2 == i)
        test(r.pcd2 == r.pi)
        test(r.pcd3 == r.pbs[10])
        self.called()

    def response_compactPreserved1(self, r):
        #
        # Encoding 1.0
        #
        test(not isinstance(r, Test.CompactPCDerived))
        test(r.pi == 3)
        self.called()

    def response_compactPreserved2(self, r):
        #
        # Encoding > 1.0
        #
        test(isinstance(r, Test.CompactPCDerived))
        test(r.pi == 3)
        test(r.pbs[0] == r)
        self.called()

    def response(self):
        test(False)

    def exception(self, exc):
        if(isinstance(exc, Ice.OperationNotExistException)):
            self.called()
            return
        test(False)

class PNodeI(Test.PNode):
    counter = 0

    def __init__(self):
        PNodeI.counter = PNodeI.counter + 1

    def __del__(self):
        PNodeI.counter = PNodeI.counter - 1

class NodeFactoryI(Ice.ObjectFactory):
    def create(self, id):
        if id == Test.PNode.ice_staticId():
            return PNodeI()
        return None

    def destroy(self):
        pass

class PreservedI(Test.Preserved):
    counter = 0

    def __init__(self):
        PreservedI.counter = PreservedI.counter + 1

    def __del__(self):
        PreservedI.counter = PreservedI.counter - 1

class PreservedFactoryI(Ice.ObjectFactory):
    def create(self, id):
        if id == Test.Preserved.ice_staticId():
            return PreservedI()
        return None

    def destroy(self):
        pass

def allTests(communicator):
    obj = communicator.stringToProxy("Test:default -p 12010")
    t = Test.TestIntfPrx.checkedCast(obj)

    sys.stdout.write("base as Object... ")
    sys.stdout.flush()
    o = None
    try:
        o = t.SBaseAsObject()
        test(o)
        test(o.ice_id() == "::Test::SBase")
    except Ice.Exception:
        test(False)
    sb = o
    test(isinstance(sb, Test.SBase))
    test(sb)
    test(sb.sb == "SBase.sb")
    print("ok")

    sys.stdout.write("base as Object (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_SBaseAsObject(cb.response_SBaseAsObject, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("base as base... ")
    sys.stdout.flush()
    try:
        sb = t.SBaseAsSBase()
        test(sb.sb == "SBase.sb")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("base as base (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_SBaseAsSBase(cb.response_SBaseAsSBase, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("base with known derived as base... ")
    sys.stdout.flush()
    try:
        sb = t.SBSKnownDerivedAsSBase()
        test(sb.sb == "SBSKnownDerived.sb")
    except Ice.Exception:
        test(False)
    sbskd = sb
    test(isinstance(sbskd, Test.SBSKnownDerived))
    test(sbskd)
    test(sbskd.sbskd == "SBSKnownDerived.sbskd")
    print("ok")

    sys.stdout.write("base with known derived as base (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_SBSKnownDerivedAsSBase(cb.response_SBSKnownDerivedAsSBase, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("base with known derived as known derived... ")
    sys.stdout.flush()
    try:
        sbskd = t.SBSKnownDerivedAsSBSKnownDerived()
        test(sbskd.sbskd == "SBSKnownDerived.sbskd")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("base with known derived as known derived (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_SBSKnownDerivedAsSBSKnownDerived(cb.response_SBSKnownDerivedAsSBSKnownDerived, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("base with unknown derived as base... ")
    sys.stdout.flush()
    try:
        sb = t.SBSUnknownDerivedAsSBase()
        test(sb.sb == "SBSUnknownDerived.sb")
    except Ice.Exception:
        test(False)
    if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
        try:
            #
            # This test succeeds for the 1.0 encoding.
            #
            sb = t.SBSUnknownDerivedAsSBaseCompact()
            test(sb.sb == "SBSUnknownDerived.sb")
        except Ice.OperationNotExistException:
            pass
        except:
            test(False)
    else:
        try:
            #
            # This test fails when using the compact format because the instance cannot
            # be sliced to a known type.
            #
            sb = t.SBSUnknownDerivedAsSBaseCompact()
            test(False)
        except Ice.OperationNotExistException:
            pass
        except Ice.NoObjectFactoryException:
            # Expected.
            pass
        except:
            test(False)
    print("ok")

    sys.stdout.write("base with unknown derived as base (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_SBSUnknownDerivedAsSBase(cb.response_SBSUnknownDerivedAsSBase, cb.exception)
    cb.check()
    if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
        #
        # This test succeeds for the 1.0 encoding.
        #
        cb = Callback()
        t.begin_SBSUnknownDerivedAsSBaseCompact(cb.response_SBSUnknownDerivedAsSBase, cb.exception)
        cb.check()
    else:
        #
        # This test fails when using the compact format because the instance cannot
        # be sliced to a known type.
        #
        cb = Callback()
        t.begin_SBSUnknownDerivedAsSBaseCompact(cb.response_SBSUnknownDerivedAsSBaseCompact,
                                                cb.exception_SBSUnknownDerivedAsSBaseCompact)
        cb.check()
    print("ok")

    sys.stdout.write("unknown with Object as Object... ")
    sys.stdout.flush()
    try:
        o = t.SUnknownAsObject()
        test(t.ice_getEncodingVersion() != Ice.Encoding_1_0)
        test(isinstance(o, Ice.UnknownSlicedObject))
        test(o.unknownTypeId == "::Test::SUnknown")
        t.checkSUnknown(o)
    except Ice.NoObjectFactoryException:
        test(t.ice_getEncodingVersion() == Ice.Encoding_1_0)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("unknown with Object as Object (AMI)... ")
    sys.stdout.flush()
    try:
        cb = Callback()
        if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
            t.begin_SUnknownAsObject(cb.response_SUnknownAsObject10, cb.exception_SUnknownAsObject10)
        else:
            t.begin_SUnknownAsObject(cb.response_SUnknownAsObject11, cb.exception_SUnknownAsObject11)
        cb.check()
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("one-element cycle... ")
    sys.stdout.flush()
    try:
        b = t.oneElementCycle()
        test(b)
        test(b.ice_id() == "::Test::B")
        test(b.sb == "B1.sb")
        test(b.pb == b)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("one-element cycle (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_oneElementCycle(cb.response_oneElementCycle, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("two-element cycle... ")
    sys.stdout.flush()
    try:
        b1 = t.twoElementCycle()
        test(b1)
        test(b1.ice_id() == "::Test::B")
        test(b1.sb == "B1.sb")

        b2 = b1.pb
        test(b2)
        test(b2.ice_id() == "::Test::B")
        test(b2.sb == "B2.sb")
        test(b2.pb == b1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("two-element cycle (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_twoElementCycle(cb.response_twoElementCycle, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("known derived pointer slicing as base... ")
    sys.stdout.flush()
    try:
        b1 = t.D1AsB()
        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb)
        test(b1.pb != b1)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1)
        test(d1.pd1 != b1)
        test(b1.pb == d1.pd1)

        b2 = b1.pb
        test(b2)
        test(b2.pb == b1)
        test(b2.sb == "D2.sb")
        test(b2.ice_id() == "::Test::B")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("known derived pointer slicing as base (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_D1AsB(cb.response_D1AsB, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("known derived pointer slicing as derived... ")
    sys.stdout.flush()
    try:
        d1 = t.D1AsD1()
        test(d1)
        test(d1.ice_id() == "::Test::D1")
        test(d1.sb == "D1.sb")
        test(d1.pb)
        test(d1.pb != d1)

        b2 = d1.pb
        test(b2)
        test(b2.ice_id() == "::Test::B")
        test(b2.sb == "D2.sb")
        test(b2.pb == d1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("known derived pointer slicing as derived (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_D1AsD1(cb.response_D1AsD1, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("unknown derived pointer slicing as base... ")
    sys.stdout.flush()
    try:
        b2 = t.D2AsB()
        test(b2)
        test(b2.ice_id() == "::Test::B")
        test(b2.sb == "D2.sb")
        test(b2.pb)
        test(b2.pb != b2)

        b1 = b2.pb
        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb == b2)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1 == b2)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("unknown derived pointer slicing as base (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_D2AsB(cb.response_D2AsB, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("param ptr slicing with known first... ")
    sys.stdout.flush()
    try:
        b1, b2 = t.paramTest1()

        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb == b2)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1 == b2)

        test(b2)
        test(b2.ice_id() == "::Test::B")        # No factory, must be sliced
        test(b2.sb == "D2.sb")
        test(b2.pb == b1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("param ptr slicing with known first (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_paramTest1(cb.response_paramTest1, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("param ptr slicing with unknown first... ")
    sys.stdout.flush()
    try:
        b2, b1 = t.paramTest2()

        test(b1)
        test(b1.ice_id() == "::Test::D1")
        test(b1.sb == "D1.sb")
        test(b1.pb == b2)
        d1 = b1
        test(isinstance(d1, Test.D1))
        test(d1.sd1 == "D1.sd1")
        test(d1.pd1 == b2)

        test(b2)
        test(b2.ice_id() == "::Test::B")        # No factory, must be sliced
        test(b2.sb == "D2.sb")
        test(b2.pb == b1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("return value identity with known first... ")
    sys.stdout.flush()
    try:
        r, p1, p2 = t.returnTest1()
        test(r == p1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("return value identity with known first (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_returnTest1(cb.response_returnTest1, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("return value identity with unknown first... ")
    sys.stdout.flush()
    try:
        r, p1, p2 = t.returnTest2()
        test(r == p1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("return value identity with unknown first (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_returnTest2(cb.response_returnTest2, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("return value identity for input params known first... ")
    sys.stdout.flush()
    try:
        d1 = Test.D1()
        d1.sb = "D1.sb"
        d1.sd1 = "D1.sd1"
        d3 = Test.D3()
        d3.pb = d1
        d3.sb = "D3.sb"
        d3.sd3 = "D3.sd3"
        d3.pd3 = d1
        d1.pb = d3
        d1.pd1 = d3

        b1 = t.returnTest3(d1, d3)

        test(b1)
        test(b1.sb == "D1.sb")
        test(b1.ice_id() == "::Test::D1")
        p1 = b1
        test(isinstance(p1, Test.D1))
        test(p1.sd1 == "D1.sd1")
        test(p1.pd1 == b1.pb)

        b2 = b1.pb
        test(b2)
        test(b2.sb == "D3.sb")
        test(b2.ice_id() == "::Test::B")        # Sliced by server
        test(b2.pb == b1)
        p3 = b2
        test(not isinstance(p3, Test.D3))

        test(b1 != d1)
        test(b1 != d3)
        test(b2 != d1)
        test(b2 != d3)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("return value identity for input params known first (AMI)... ")
    sys.stdout.flush()
    try:
        d1 = Test.D1()
        d1.sb = "D1.sb"
        d1.sd1 = "D1.sd1"
        d3 = Test.D3()
        d3.pb = d1
        d3.sb = "D3.sb"
        d3.sd3 = "D3.sd3"
        d3.pd3 = d1
        d1.pb = d3
        d1.pd1 = d3

        cb = Callback()
        t.begin_returnTest3(d1, d3, cb.response_returnTest3, cb.exception)
        cb.check()
        b1 = cb.r

        test(b1)
        test(b1.sb == "D1.sb")
        test(b1.ice_id() == "::Test::D1")
        p1 = b1
        test(isinstance(p1, Test.D1))
        test(p1.sd1 == "D1.sd1")
        test(p1.pd1 == b1.pb)

        b2 = b1.pb
        test(b2)
        test(b2.sb == "D3.sb")
        test(b2.ice_id() == "::Test::B")        # Sliced by server
        test(b2.pb == b1)
        p3 = b2
        test(not isinstance(p3, Test.D3))

        test(b1 != d1)
        test(b1 != d3)
        test(b2 != d1)
        test(b2 != d3)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("return value identity for input params unknown first... ")
    sys.stdout.flush()
    try:
        d1 = Test.D1()
        d1.sb = "D1.sb"
        d1.sd1 = "D1.sd1"
        d3 = Test.D3()
        d3.pb = d1
        d3.sb = "D3.sb"
        d3.sd3 = "D3.sd3"
        d3.pd3 = d1
        d1.pb = d3
        d1.pd1 = d3

        b1 = t.returnTest3(d3, d1)

        test(b1)
        test(b1.sb == "D3.sb")
        test(b1.ice_id() == "::Test::B")        # Sliced by server
        p1 = b1
        test(not isinstance(p1, Test.D3))

        b2 = b1.pb
        test(b2)
        test(b2.sb == "D1.sb")
        test(b2.ice_id() == "::Test::D1")
        test(b2.pb == b1)
        p3 = b2
        test(isinstance(p3, Test.D1))
        test(p3.sd1 == "D1.sd1")
        test(p3.pd1 == b1)

        test(b1 != d1)
        test(b1 != d3)
        test(b2 != d1)
        test(b2 != d3)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("return value identity for input params unknown first (AMI)... ")
    sys.stdout.flush()
    try:
        d1 = Test.D1()
        d1.sb = "D1.sb"
        d1.sd1 = "D1.sd1"
        d3 = Test.D3()
        d3.pb = d1
        d3.sb = "D3.sb"
        d3.sd3 = "D3.sd3"
        d3.pd3 = d1
        d1.pb = d3
        d1.pd1 = d3

        cb = Callback()
        t.begin_returnTest3(d3, d1, cb.response_returnTest3, cb.exception)
        cb.check()
        b1 = cb.r

        test(b1)
        test(b1.sb == "D3.sb")
        test(b1.ice_id() == "::Test::B")        # Sliced by server
        p1 = b1
        test(not isinstance(p1, Test.D3))

        b2 = b1.pb
        test(b2)
        test(b2.sb == "D1.sb")
        test(b2.ice_id() == "::Test::D1")
        test(b2.pb == b1)
        p3 = b2
        test(isinstance(p3, Test.D1))
        test(p3.sd1 == "D1.sd1")
        test(p3.pd1 == b1)

        test(b1 != d1)
        test(b1 != d3)
        test(b2 != d1)
        test(b2 != d3)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("remainder unmarshaling (3 instances)... ")
    sys.stdout.flush()
    try:
        ret, p1, p2 = t.paramTest3()

        test(p1)
        test(p1.sb == "D2.sb (p1 1)")
        test(p1.pb == None)
        test(p1.ice_id() == "::Test::B")

        test(p2)
        test(p2.sb == "D2.sb (p2 1)")
        test(p2.pb == None)
        test(p2.ice_id() == "::Test::B")

        test(ret)
        test(ret.sb == "D1.sb (p2 2)")
        test(ret.pb == None)
        test(ret.ice_id() == "::Test::D1")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("remainder unmarshaling (3 instances) (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_paramTest3(cb.response_paramTest3, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("remainder unmarshaling (4 instances)... ")
    sys.stdout.flush()
    try:
        ret, b = t.paramTest4()

        test(b)
        test(b.sb == "D4.sb (1)")
        test(b.pb == None)
        test(b.ice_id() == "::Test::B")

        test(ret)
        test(ret.sb == "B.sb (2)")
        test(ret.pb == None)
        test(ret.ice_id() == "::Test::B")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("remainder unmarshaling (4 instances) (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_paramTest4(cb.response_paramTest4, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("param ptr slicing, instance marshaled in unknown derived as base... ")
    sys.stdout.flush()
    try:
        b1 = Test.B()
        b1.sb = "B.sb(1)"
        b1.pb = b1

        d3 = Test.D3()
        d3.sb = "D3.sb"
        d3.pb = d3
        d3.sd3 = "D3.sd3"
        d3.pd3 = b1

        b2 = Test.B()
        b2.sb = "B.sb(2)"
        b2.pb = b1

        r = t.returnTest3(d3, b2)

        test(r)
        test(r.ice_id() == "::Test::B")
        test(r.sb == "D3.sb")
        test(r.pb == r)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("param ptr slicing, instance marshaled in unknown derived as base (AMI)... ")
    sys.stdout.flush()
    try:
        b1 = Test.B()
        b1.sb = "B.sb(1)"
        b1.pb = b1

        d3 = Test.D3()
        d3.sb = "D3.sb"
        d3.pb = d3
        d3.sd3 = "D3.sd3"
        d3.pd3 = b1

        b2 = Test.B()
        b2.sb = "B.sb(2)"
        b2.pb = b1

        cb = Callback()
        t.begin_returnTest3(d3, b2, cb.response_returnTest3, cb.exception)
        cb.check()
        r = cb.r

        test(r)
        test(r.ice_id() == "::Test::B")
        test(r.sb == "D3.sb")
        test(r.pb == r)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("param ptr slicing, instance marshaled in unknown derived as derived... ")
    sys.stdout.flush()
    try:
        d11 = Test.D1()
        d11.sb = "D1.sb(1)"
        d11.pb = d11
        d11.sd1 = "D1.sd1(1)"
        d11.pd1 = None

        d3 = Test.D3()
        d3.sb = "D3.sb"
        d3.pb = d3
        d3.sd3 = "D3.sd3"
        d3.pd3 = d11

        d12 = Test.D1()
        d12.sb = "D1.sb(2)"
        d12.pb = d12
        d12.sd1 = "D1.sd1(2)"
        d12.pd1 = d11

        r = t.returnTest3(d3, d12)
        test(r)
        test(r.ice_id() == "::Test::B")
        test(r.sb == "D3.sb")
        test(r.pb == r)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("param ptr slicing, instance marshaled in unknown derived as derived (AMI)... ")
    sys.stdout.flush()
    try:
        d11 = Test.D1()
        d11.sb = "D1.sb(1)"
        d11.pb = d11
        d11.sd1 = "D1.sd1(1)"
        d11.pd1 = None

        d3 = Test.D3()
        d3.sb = "D3.sb"
        d3.pb = d3
        d3.sd3 = "D3.sd3"
        d3.pd3 = d11

        d12 = Test.D1()
        d12.sb = "D1.sb(2)"
        d12.pb = d12
        d12.sd1 = "D1.sd1(2)"
        d12.pd1 = d11

        cb = Callback()
        t.begin_returnTest3(d3, d12, cb.response_returnTest3, cb.exception)
        cb.check()
        r = cb.r

        test(r)
        test(r.ice_id() == "::Test::B")
        test(r.sb == "D3.sb")
        test(r.pb == r)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("sequence slicing... ")
    sys.stdout.flush()
    try:
        ss = Test.SS3()
        ss1b = Test.B()
        ss1b.sb = "B.sb"
        ss1b.pb = ss1b

        ss1d1 = Test.D1()
        ss1d1.sb = "D1.sb"
        ss1d1.sd1 = "D1.sd1"
        ss1d1.pb = ss1b

        ss1d3 = Test.D3()
        ss1d3.sb = "D3.sb"
        ss1d3.sd3 = "D3.sd3"
        ss1d3.pb = ss1b

        ss2b = Test.B()
        ss2b.sb = "B.sb"
        ss2b.pb = ss1b

        ss2d1 = Test.D1()
        ss2d1.sb = "D1.sb"
        ss2d1.sd1 = "D1.sd1"
        ss2d1.pb = ss2b

        ss2d3 = Test.D3()
        ss2d3.sb = "D3.sb"
        ss2d3.sd3 = "D3.sd3"
        ss2d3.pb = ss2b

        ss1d1.pd1 = ss2b
        ss1d3.pd3 = ss2d1

        ss2d1.pd1 = ss1d3
        ss2d3.pd3 = ss1d1

        ss1 = Test.SS1()
        ss1.s = (ss1b, ss1d1, ss1d3)

        ss2 = Test.SS2()
        ss2.s = (ss2b, ss2d1, ss2d3)

        ss = t.sequenceTest(ss1, ss2)

        test(ss.c1)
        ss1b = ss.c1.s[0]
        ss1d1 = ss.c1.s[1]
        test(ss.c2)
        ss1d3 = ss.c1.s[2]

        test(ss.c2)
        ss2b = ss.c2.s[0]
        ss2d1 = ss.c2.s[1]
        ss2d3 = ss.c2.s[2]

        test(ss1b.pb == ss1b)
        test(ss1d1.pb == ss1b)
        test(ss1d3.pb == ss1b)

        test(ss2b.pb == ss1b)
        test(ss2d1.pb == ss2b)
        test(ss2d3.pb == ss2b)

        test(ss1b.ice_id() == "::Test::B")
        test(ss1d1.ice_id() == "::Test::D1")
        test(ss1d3.ice_id() == "::Test::B")

        test(ss2b.ice_id() == "::Test::B")
        test(ss2d1.ice_id() == "::Test::D1")
        test(ss2d3.ice_id() == "::Test::B")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("sequence slicing (AMI)... ")
    sys.stdout.flush()
    try:
        ss = Test.SS3()
        ss1b = Test.B()
        ss1b.sb = "B.sb"
        ss1b.pb = ss1b

        ss1d1 = Test.D1()
        ss1d1.sb = "D1.sb"
        ss1d1.sd1 = "D1.sd1"
        ss1d1.pb = ss1b

        ss1d3 = Test.D3()
        ss1d3.sb = "D3.sb"
        ss1d3.sd3 = "D3.sd3"
        ss1d3.pb = ss1b

        ss2b = Test.B()
        ss2b.sb = "B.sb"
        ss2b.pb = ss1b

        ss2d1 = Test.D1()
        ss2d1.sb = "D1.sb"
        ss2d1.sd1 = "D1.sd1"
        ss2d1.pb = ss2b

        ss2d3 = Test.D3()
        ss2d3.sb = "D3.sb"
        ss2d3.sd3 = "D3.sd3"
        ss2d3.pb = ss2b

        ss1d1.pd1 = ss2b
        ss1d3.pd3 = ss2d1

        ss2d1.pd1 = ss1d3
        ss2d3.pd3 = ss1d1

        ss1 = Test.SS1()
        ss1.s = (ss1b, ss1d1, ss1d3)

        ss2 = Test.SS2()
        ss2.s = (ss2b, ss2d1, ss2d3)

        cb = Callback()
        t.begin_sequenceTest(ss1, ss2, cb.response_sequenceTest, cb.exception)
        cb.check()
        ss = cb.r

        test(ss.c1)
        ss1b = ss.c1.s[0]
        ss1d1 = ss.c1.s[1]
        test(ss.c2)
        ss1d3 = ss.c1.s[2]

        test(ss.c2)
        ss2b = ss.c2.s[0]
        ss2d1 = ss.c2.s[1]
        ss2d3 = ss.c2.s[2]

        test(ss1b.pb == ss1b)
        test(ss1d1.pb == ss1b)
        test(ss1d3.pb == ss1b)

        test(ss2b.pb == ss1b)
        test(ss2d1.pb == ss2b)
        test(ss2d3.pb == ss2b)

        test(ss1b.ice_id() == "::Test::B")
        test(ss1d1.ice_id() == "::Test::D1")
        test(ss1d3.ice_id() == "::Test::B")

        test(ss2b.ice_id() == "::Test::B")
        test(ss2d1.ice_id() == "::Test::D1")
        test(ss2d3.ice_id() == "::Test::B")
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("dictionary slicing... ")
    sys.stdout.flush()
    try:
        bin = {}
        for i in range(0, 10):
            d1 = Test.D1()
            s = "D1." + str(i)
            d1.sb = s
            d1.pb = d1
            d1.sd1 = s
            d1.pd1 = None
            bin[i] = d1

        r, bout = t.dictionaryTest(bin)

        test(len(bout) == 10)
        for i in range(0, 10):
            b = bout[i * 10]
            test(b)
            s = "D1." + str(i)
            test(b.sb == s)
            test(b.pb)
            test(b.pb != b)
            test(b.pb.sb == s)
            test(b.pb.pb == b.pb)

        test(len(r) == 10)
        for i in range(0, 10):
            b = r[i * 20]
            test(b)
            s = "D1." + str(i * 20)
            test(b.sb == s)
            if i == 0:
                test(b.pb == None)
            else:
                test(b.pb == r[(i - 1) * 20])
            d1 = b
            test(isinstance(d1, Test.D1))
            test(d1.sd1 == s)
            test(d1.pd1 == d1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("dictionary slicing (AMI)... ")
    sys.stdout.flush()
    try:
        bin = {}
        for i in range(0, 10):
            d1 = Test.D1()
            s = "D1." + str(i)
            d1.sb = s
            d1.pb = d1
            d1.sd1 = s
            d1.pd1 = None
            bin[i] = d1

        cb = Callback()
        t.begin_dictionaryTest(bin, cb.response_dictionaryTest, cb.exception)
        cb.check()
        bout = cb.bout
        r = cb.r

        test(len(bout) == 10)
        for i in range(0, 10):
            b = bout[i * 10]
            test(b)
            s = "D1." + str(i)
            test(b.sb == s)
            test(b.pb)
            test(b.pb != b)
            test(b.pb.sb == s)
            test(b.pb.pb == b.pb)

        test(len(r) == 10)
        for i in range(0, 10):
            b = r[i * 20]
            test(b)
            s = "D1." + str(i * 20)
            test(b.sb == s)
            if i == 0:
                test(b.pb == None)
            else:
                test(b.pb == r[(i - 1) * 20])
            d1 = b
            test(isinstance(d1, Test.D1))
            test(d1.sd1 == s)
            test(d1.pd1 == d1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("base exception thrown as base exception... ")
    sys.stdout.flush()
    try:
        t.throwBaseAsBase()
        test(False)
    except Test.BaseException as e:
        test(e.ice_name() == "Test::BaseException")
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb")
        test(e.pb.pb == e.pb)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("base exception thrown as base exception (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_throwBaseAsBase(cb.response, cb.exception_throwBaseAsBase)
    cb.check()
    print("ok")

    sys.stdout.write("derived exception thrown as base exception... ")
    sys.stdout.flush()
    try:
        t.throwDerivedAsBase()
        test(False)
    except Test.DerivedException as e:
        test(e.ice_name() == "Test::DerivedException")
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb1")
        test(e.pb.pb == e.pb)
        test(e.sde == "sde1")
        test(e.pd1)
        test(e.pd1.sb == "sb2")
        test(e.pd1.pb == e.pd1)
        test(e.pd1.sd1 == "sd2")
        test(e.pd1.pd1 == e.pd1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("derived exception thrown as base exception (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_throwDerivedAsBase(cb.response, cb.exception_throwDerivedAsBase)
    cb.check()
    print("ok")

    sys.stdout.write("derived exception thrown as derived exception... ")
    sys.stdout.flush()
    try:
        t.throwDerivedAsDerived()
        test(False)
    except Test.DerivedException as e:
        test(e.ice_name() == "Test::DerivedException")
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb1")
        test(e.pb.pb == e.pb)
        test(e.sde == "sde1")
        test(e.pd1)
        test(e.pd1.sb == "sb2")
        test(e.pd1.pb == e.pd1)
        test(e.pd1.sd1 == "sd2")
        test(e.pd1.pd1 == e.pd1)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("derived exception thrown as derived exception (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_throwDerivedAsDerived(cb.response, cb.exception_throwDerivedAsDerived)
    cb.check()
    print("ok")

    sys.stdout.write("unknown derived exception thrown as base exception... ")
    sys.stdout.flush()
    try:
        t.throwUnknownDerivedAsBase()
        test(False)
    except Test.BaseException as e:
        test(e.ice_name() == "Test::BaseException")
        test(e.sbe == "sbe")
        test(e.pb)
        test(e.pb.sb == "sb d2")
        test(e.pb.pb == e.pb)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("unknown derived exception thrown as base exception (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_throwUnknownDerivedAsBase(cb.response, cb.exception_throwUnknownDerivedAsBase)
    cb.check()
    print("ok")

    sys.stdout.write("forward-declared class... ")
    sys.stdout.flush()
    try:
        f = t.useForward()
        test(f)
    except Ice.Exception:
        test(False)
    print("ok")

    sys.stdout.write("forward-declared class (AMI)... ")
    sys.stdout.flush()
    cb = Callback()
    t.begin_useForward(cb.response_useForward, cb.exception)
    cb.check()
    print("ok")

    sys.stdout.write("preserved classes... ")
    sys.stdout.flush()

    try:
        #
        # Server knows the most-derived class PDerived.
        #
        pd = Test.PDerived()
        pd.pi = 3
        pd.ps = "preserved"
        pd.pb = pd

        r = t.exchangePBase(pd)
        test(isinstance(r, Test.PDerived))
        test(r.pi == 3)
        test(r.ps == "preserved")
        test(r.pb == r)

        #
        # Server only knows the base (non-preserved) type, so the object is sliced.
        #
        pu = Test.PCUnknown()
        pu.pi = 3
        pu.pu = "preserved"

        r = t.exchangePBase(pu)
        test(not isinstance(r, Test.PCUnknown))
        test(r.pi == 3)

        #
        # Server only knows the intermediate type Preserved. The object will be sliced to
        # Preserved for the 1.0 encoding; otherwise it should be returned intact.
        #
        pcd = Test.PCDerived()
        pcd.pi = 3
        pcd.pbs = [ pcd ]

        r = t.exchangePBase(pcd)
        if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
            test(not isinstance(r, Test.PCDerived))
            test(r.pi == 3)
        else:
            test(isinstance(r, Test.PCDerived))
            test(r.pi == 3)
            test(r.pbs[0] == r)

        #
        # Server only knows the intermediate type CompactPDerived. The object will be sliced to
        # CompactPDerived for the 1.0 encoding; otherwise it should be returned intact.
        #
        pcd = Test.CompactPCDerived()
        pcd.pi = 3
        pcd.pbs = [ pcd ]

        r = t.exchangePBase(pcd)
        if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
            test(not isinstance(r, Test.CompactPCDerived))
            test(r.pi == 3)
        else:
            test(isinstance(r, Test.CompactPCDerived))
            test(r.pi == 3)
            test(r.pbs[0] == r)

        #
        # Send an object that will have multiple preserved slices in the server.
        # The object will be sliced to Preserved for the 1.0 encoding.
        #
        pcd = Test.PCDerived3()
        pcd.pi = 3
        #
        # Sending more than 254 objects exercises the encoding for object ids.
        #
        pcd.pbs = []
        for i in range(0, 300):
            p2 = Test.PCDerived2()
            p2.pi = i
            p2.pbs = [ None ] # Nil reference. This slice should not have an indirection table.
            p2.pcd2 = i
            pcd.pbs.append(p2)
        pcd.pcd2 = pcd.pi
        pcd.pcd3 = pcd.pbs[10]

        r = t.exchangePBase(pcd)
        if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
            test(not isinstance(r, Test.PCDerived3))
            test(isinstance(r, Test.Preserved))
            test(r.pi == 3)
        else:
            test(isinstance(r, Test.PCDerived3))
            test(r.pi == 3)
            for i in range(0, 300):
                p2 = r.pbs[i]
                test(isinstance(p2, Test.PCDerived2))
                test(p2.pi == i)
                test(len(p2.pbs) == 1)
                test(not p2.pbs[0])
                test(p2.pcd2 == i)
            test(r.pcd2 == r.pi)
            test(r.pcd3 == r.pbs[10])

        #
        # Obtain an object with preserved slices and send it back to the server.
        # The preserved slices should be excluded for the 1.0 encoding, otherwise
        # they should be included.
        #
        p = t.PBSUnknownAsPreserved()
        t.checkPBSUnknown(p)
        if t.ice_getEncodingVersion() != Ice.Encoding_1_0:
            t.ice_encodingVersion(Ice.Encoding_1_0).checkPBSUnknown(p)
    except Ice.OperationNotExistException:
        pass
    
    print("ok")

    sys.stdout.write("preserved classes (AMI)... ")
    sys.stdout.flush()

    #
    # Server knows the most-derived class PDerived.
    #
    pd = Test.PDerived()
    pd.pi = 3
    pd.ps = "preserved"
    pd.pb = pd

    cb = Callback()
    t.begin_exchangePBase(pd, cb.response_preserved1, cb.exception)
    cb.check()

    #
    # Server only knows the base (non-preserved) type, so the object is sliced.
    #
    pu = Test.PCUnknown()
    pu.pi = 3
    pu.pu = "preserved"

    cb = Callback()
    t.begin_exchangePBase(pu, cb.response_preserved2, cb.exception)
    cb.check()

    #
    # Server only knows the intermediate type Preserved. The object will be sliced to
    # Preserved for the 1.0 encoding; otherwise it should be returned intact.
    #
    pcd = Test.PCDerived()
    pcd.pi = 3
    pcd.pbs = [ pcd ]

    cb = Callback()
    if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
        t.begin_exchangePBase(pcd, cb.response_preserved3, cb.exception)
    else:
        t.begin_exchangePBase(pcd, cb.response_preserved4, cb.exception)
    cb.check()

    #
    # Server only knows the intermediate type CompactPDerived. The object will be sliced to
    # CompactPDerived for the 1.0 encoding; otherwise it should be returned intact.
    #
    pcd = Test.CompactPCDerived()
    pcd.pi = 3
    pcd.pbs = [ pcd ]

    cb = Callback()
    if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
        t.begin_exchangePBase(pcd, cb.response_compactPreserved1, cb.exception)
    else:
        t.begin_exchangePBase(pcd, cb.response_compactPreserved2, cb.exception)
    cb.check()

    #
    # Send an object that will have multiple preserved slices in the server.
    # The object will be sliced to Preserved for the 1.0 encoding.
    #
    pcd = Test.PCDerived3()
    pcd.pi = 3
    #
    # Sending more than 254 objects exercises the encoding for object ids.
    #
    pcd.pbs = []
    for i in range(0, 300):
        p2 = Test.PCDerived2()
        p2.pi = i
        p2.pbs = [ None ] # Nil reference. This slice should not have an indirection table.
        p2.pcd2 = i
        pcd.pbs.append(p2)
    pcd.pcd2 = pcd.pi
    pcd.pcd3 = pcd.pbs[10]

    cb = Callback()
    if t.ice_getEncodingVersion() == Ice.Encoding_1_0:
        t.begin_exchangePBase(pcd, cb.response_preserved3, cb.exception)
    else:
        t.begin_exchangePBase(pcd, cb.response_preserved5, cb.exception)
    cb.check()

    print("ok")

    sys.stdout.write("garbage collection of preserved classes... ")
    sys.stdout.flush()
    try:
        #
        # Register a factory in order to substitute our own subclass of
        # UCNode. This provides an easy way to determine how many
        # unmarshaled instances currently exist.
        #
        communicator.addObjectFactory(NodeFactoryI(), Test.PNode.ice_staticId())

        #
        # Relay a graph through the server. This test uses a preserved class
        # with a class member.
        #
        c = Test.PNode()
        c.next = Test.PNode()
        c.next.next = Test.PNode()
        c.next.next.next = c    # Create a cyclic graph.

        test(PNodeI.counter == 0)
        n = t.exchangePNode(c)
        test(PNodeI.counter == 3)
        test(n.next != None)
        test(n.next != n.next.next)
        test(n.next.next != n.next.next.next)
        test(n.next.next.next == n)
        n = None        # Release reference.
        #
        # The PNodeI class declares a __del__ method, which means the Python
        # garbage collector will NOT collect a cycle of PNodeI objects.
        #
        gc.collect()    # No effect.
        test(PNodeI.counter == 3)
        #
        # The uncollectable objects are stored in gc.garbage. We have to
        # manually break the cycle and then remove the objects from the
        # gc.garbage list.
        #
        test(len(gc.garbage) > 0)
        for o in gc.garbage:
            if isinstance(o, PNodeI):
                o.next = None
        o = None        # Remove last reference.
        del gc.garbage[:]
        test(PNodeI.counter == 0)

        #
        # Obtain a preserved object from the server where the most-derived
        # type is unknown. The preserved slice refers to a graph of PNode
        # objects.
        #
        test(PNodeI.counter == 0)
        p = t.PBSUnknownAsPreservedWithGraph()
        test(p)
        test(PNodeI.counter == 3)
        t.checkPBSUnknownWithGraph(p)
        p = None        # Release reference.
        #
        # The PNodeI class declares a __del__ method, which means the Python
        # garbage collector will NOT collect a cycle of PNodeI objects.
        #
        gc.collect()    # No effect.
        test(PNodeI.counter == 3)
        #
        # The uncollectable objects are stored in gc.garbage. We have to
        # manually break the cycle and then remove the objects from the
        # gc.garbage list.
        #
        test(len(gc.garbage) > 0)
        for o in gc.garbage:
            if isinstance(o, PNodeI):
                o.next = None
        o = None        # Remove last reference.
        del gc.garbage[:]
        test(PNodeI.counter == 0)

        #
        # Register a factory in order to substitute our own subclass of
        # Preserved. This provides an easy way to determine how many
        # unmarshaled instances currently exist.
        #
        communicator.addObjectFactory(PreservedFactoryI(), Test.Preserved.ice_staticId())

        #
        # Obtain a preserved object from the server where the most-derived
        # type is unknown. A data member in the preserved slice refers to the
        # outer object, so the chain of references looks like this:
        #
        # outer->slicedData->outer
        #
        test(PreservedI.counter == 0)
        p = t.PBSUnknown2AsPreservedWithGraph()
        test(p != None)
        test(PreservedI.counter == 1)
        t.checkPBSUnknown2WithGraph(p)
        p._ice_slicedData = None    # Break the cycle.
        p = None                    # Release reference.
        test(PreservedI.counter == 0)

        #
        # Throw a preserved exception where the most-derived type is unknown.
        # The preserved exception slice contains a class data member. This
        # object is also preserved, and its most-derived type is also unknown.
        # The preserved slice of the object contains a class data member that
        # refers to itself.
        #
        # The chain of references looks like this:
        #
        # ex->slicedData->obj->slicedData->obj
        #
        try:
            test(PreservedI.counter == 0)

            try:
                t.throwPreservedException()
            except Test.PreservedException as ex:
                #
                # The class instance is only retained when the encoding is > 1.0.
                #
                if t.ice_getEncodingVersion() != Ice.Encoding_1_0:
                    test(PreservedI.counter == 1)
                    gc.collect()        # No effect.
                    test(PreservedI.counter == 1)
                    ex._ice_slicedData = None   # Break the cycle.

            #
            # Exception has gone out of scope.
            #
            if t.ice_getEncodingVersion() != Ice.Encoding_1_0:
                gc.collect()
                test(len(gc.garbage) > 0)
                for o in gc.garbage:
                    if isinstance(o, PreservedI):
                        o._ice_slicedData = None
                o = None        # Remove last reference.
                del gc.garbage[:]
            test(PreservedI.counter == 0)
        except Ice.Exception:
            test(False)
    except Ice.OperationNotExistException:
        pass

    print("ok")

    return t
