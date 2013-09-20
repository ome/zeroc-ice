# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import Ice, Test, TestI, sys

#
# Ice for Python behaves differently than Ice for C++, because
# collocated invocations are still sent "over the wire". Therefore
# we always need to install the factories, even for the collocated
# case.
#
class MyObjectFactory(Ice.ObjectFactory):
    def create(self, type):
        if type == '::Test::B':
            return TestI.BI()
        elif type == '::Test::C':
            return TestI.CI()
        elif type == '::Test::D':
            return TestI.DI()
        elif type == '::Test::E':
            return TestI.EI()
        elif type == '::Test::F':
            return TestI.FI()
        elif type == '::Test::I':
            return TestI.II()
        elif type == '::Test::J':
            return TestI.JI()
        elif type == '::Test::H':
            return TestI.HI()
        assert(False) # Should never be reached

    def destroy(self):
        # Nothing to do
        pass

def test(b):
    if not b:
        raise RuntimeError('test assertion failed')

def allTests(communicator, collocated):
    factory = MyObjectFactory()
    communicator.addObjectFactory(factory, '::Test::B')
    communicator.addObjectFactory(factory, '::Test::C')
    communicator.addObjectFactory(factory, '::Test::D')
    communicator.addObjectFactory(factory, '::Test::E')
    communicator.addObjectFactory(factory, '::Test::F')
    communicator.addObjectFactory(factory, '::Test::I')
    communicator.addObjectFactory(factory, '::Test::J')
    communicator.addObjectFactory(factory, '::Test::H')

    sys.stdout.write("testing stringToProxy... ")
    sys.stdout.flush()
    ref = "initial:default -p 12010"
    base = communicator.stringToProxy(ref)
    test(base)
    print("ok")

    sys.stdout.write("testing checked cast... ")
    sys.stdout.flush()
    initial = Test.InitialPrx.checkedCast(base)
    test(initial)
    test(initial == base)
    print("ok")

    sys.stdout.write("getting B1... ")
    sys.stdout.flush()
    b1 = initial.getB1()
    test(b1)
    print("ok")
    
    sys.stdout.write("getting B2... ")
    sys.stdout.flush()
    b2 = initial.getB2()
    test(b2)
    print("ok")
    
    sys.stdout.write("getting C... ")
    sys.stdout.flush()
    c = initial.getC()
    test(c)
    print("ok")
    
    sys.stdout.write("getting D... ")
    sys.stdout.flush()
    d = initial.getD()
    test(d)
    print("ok")

    sys.stdout.write("testing protected members... ")
    sys.stdout.flush()
    e = initial.getE()
    test(e.checkValues())
    test(e._i == 1)
    test(e._s == "hello")
    f = initial.getF()
    test(f.checkValues())
    test(f.e2.checkValues())
    test(f._e1.checkValues())
    print("ok")
    
    sys.stdout.write("getting I, J, H... ")
    sys.stdout.flush()
    i = initial.getI()
    test(i)
    j = initial.getJ()
    test(isinstance(j, Test.J))
    h = initial.getH()
    test(isinstance(h, Test.H))
    print("ok")

    sys.stdout.write("setting I... ")
    sys.stdout.flush()
    initial.setI(TestI.II())
    initial.setI(TestI.JI())
    initial.setI(TestI.HI())
    print("ok")
    
    sys.stdout.write("checking consistency... ")
    sys.stdout.flush()
    test(b1 != b2)
    test(b1 != c)
    test(b1 != d)
    test(b2 != c)
    test(b2 != d)
    test(c != d)
    test(b1.theB == b1)
    test(b1.theC == None)
    test(isinstance(b1.theA, Test.B))
    test(b1.theA.theA == b1.theA)
    test(b1.theA.theB == b1)
    test(b1.theA.theC)
    test(b1.theA.theC.theB == b1.theA)
    test(b1.preMarshalInvoked)
    test(b1.postUnmarshalInvoked())
    test(b1.theA.preMarshalInvoked)
    test(b1.theA.postUnmarshalInvoked())
    test(b1.theA.theC.preMarshalInvoked)
    test(b1.theA.theC.postUnmarshalInvoked())
    # More tests possible for b2 and d, but I think this is already sufficient.
    test(b2.theA == b2)
    test(d.theC == None)
    print("ok")

    sys.stdout.write("getting B1, B2, C, and D all at once... ")
    sys.stdout.flush()
    b1, b2, c, d = initial.getAll()
    test(b1)
    test(b2)
    test(c)
    test(d)
    print("ok")
    
    sys.stdout.write("checking consistency... ")
    sys.stdout.flush()
    test(b1 != b2)
    test(b1 != c)
    test(b1 != d)
    test(b2 != c)
    test(b2 != d)
    test(c != d)
    test(b1.theA == b2)
    test(b1.theB == b1)
    test(b1.theC == None)
    test(b2.theA == b2)
    test(b2.theB == b1)
    test(b2.theC == c)
    test(c.theB == b2)
    test(d.theA == b1)
    test(d.theB == b2)
    test(d.theC == None)
    test(d.preMarshalInvoked)
    test(d.postUnmarshalInvoked())
    test(d.theA.preMarshalInvoked)
    test(d.theA.postUnmarshalInvoked())
    test(d.theB.preMarshalInvoked)
    test(d.theB.postUnmarshalInvoked())
    test(d.theB.theC.preMarshalInvoked)
    test(d.theB.theC.postUnmarshalInvoked())
    print("ok")

    sys.stdout.write("testing sequences... ")
    try:
        sys.stdout.flush()
        initial.opBaseSeq([])

        retS, outS = initial.opBaseSeq([Test.Base()])
        test(len(retS) == 1 and len(outS) == 1)
    except Ice.OperationNotExistException:
        pass
    print("ok")

    sys.stdout.write("testing compact ID... ")
    sys.stdout.flush()
    try:
        r = initial.getCompact()
        test(r)
    except Ice.OperationNotExistException:
        pass
    print("ok")

    if not collocated:
        sys.stdout.write("testing UnexpectedObjectException... ")
        sys.stdout.flush()
        ref = "uoet:default -p 12010"
        base = communicator.stringToProxy(ref)
        test(base)
        uoet = Test.UnexpectedObjectExceptionTestPrx.uncheckedCast(base)
        test(uoet)
        try:
            uoet.op()
            test(False)
        except Ice.UnexpectedObjectException as ex:
            test(ex.type == "::Test::AlsoEmpty")
            test(ex.expectedType == "::Test::Empty")
        except Ice.Exception as ex:
            print(ex)
            test(False)
        except:
            print(sys.exc_info())
            test(False)
        print("ok")

    return initial
