// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;
using namespace Test;

class AbstractBaseI : public AbstractBase
{
public:
    
    virtual void op(const Ice::Current&) 
    {}
};

void
testUOE(const Ice::CommunicatorPtr& communicator)
{
    string ref = "uoet:default -p 12010";
    Ice::ObjectPrx base = communicator->stringToProxy(ref);
    test(base);
    UnexpectedObjectExceptionTestPrx uoet = UnexpectedObjectExceptionTestPrx::uncheckedCast(base);
    test(uoet);
    try
    {
        uoet->op();
        test(false);
    }
    catch(const Ice::UnexpectedObjectException& ex)
    {
        test(ex.type == "::Test::AlsoEmpty");
        test(ex.expectedType == "::Test::Empty");
    }
    catch(const Ice::Exception& ex)
    {
        cout << ex << endl;
        test(false);
    }
    catch(...)
    {
        test(false);
    }
}

InitialPrx
allTests(const Ice::CommunicatorPtr& communicator, bool collocated)
{
    cout << "testing stringToProxy... " << flush;
    string ref = "initial:default -p 12010";
    Ice::ObjectPrx base = communicator->stringToProxy(ref);
    test(base);
    cout << "ok" << endl;

    cout << "testing checked cast... " << flush;
    InitialPrx initial = InitialPrx::checkedCast(base);
    test(initial);
    test(initial == base);
    cout << "ok" << endl;

    cout << "testing constructor, copy constructor, and assignment operator... " << flush;

    BasePtr ba1 = new Base;
    test(ba1->theS.str == "");
    test(ba1->str == "");

    S s;
    s.str = "hello";
    BasePtr ba2 = new Base(s, "hi");
    test(ba2->theS.str == "hello");
    test(ba2->str == "hi");

    *ba1 = *ba2;
    test(ba1->theS.str == "hello");
    test(ba1->str == "hi");

    BasePtr bp1 = new Base();
    *bp1 = *ba2;
    test(bp1->theS.str == "hello");
    test(bp1->str == "hi");

    cout << "ok" << endl;

    cout << "testing ice_clone..." << flush;

    BasePtr bp2 = BasePtr::dynamicCast(bp1->ice_clone());
    test(bp1->theS.str == bp2->theS.str);
    test(bp1->str == bp2->str);
    
    AbstractBasePtr abp1 = new AbstractBaseI;
    try
    {
        abp1->ice_clone();
        test(false);
    }
    catch(const Ice::CloneNotImplementedException&)
    {
    }
    cout << "ok" << endl;

    cout << "getting B1... " << flush;
    BPtr b1 = initial->getB1();
    test(b1);
    cout << "ok" << endl;
    
    cout << "getting B2... " << flush;
    BPtr b2 = initial->getB2();
    test(b2);
    cout << "ok" << endl;
    
    cout << "getting C... " << flush;
    CPtr c = initial->getC();
    test(c);
    cout << "ok" << endl;
    
    cout << "getting D... " << flush;
    DPtr d = initial->getD();
    test(d);
    cout << "ok" << endl;
    
    cout << "checking consistency... " << flush;
    test(b1 != b2);
    test(b1 != c);
    test(b1 != d);
    test(b2 != c);
    test(b2 != d);
    test(c != d);
    test(b1->theB == b1);
    test(b1->theC == 0);
    test(BPtr::dynamicCast(b1->theA));
    test(BPtr::dynamicCast(b1->theA)->theA == b1->theA);
    test(BPtr::dynamicCast(b1->theA)->theB == b1);
    test(CPtr::dynamicCast(BPtr::dynamicCast(b1->theA)->theC));
    test(CPtr::dynamicCast(BPtr::dynamicCast(b1->theA)->theC)->theB == b1->theA);
    if(!collocated)
    {
        test(b1->preMarshalInvoked);
        test(b1->postUnmarshalInvoked());
        test(b1->theA->preMarshalInvoked);
        test(b1->theA->postUnmarshalInvoked());
        test(BPtr::dynamicCast(b1->theA)->theC->preMarshalInvoked);
        test(BPtr::dynamicCast(b1->theA)->theC->postUnmarshalInvoked());
    }
    // More tests possible for b2 and d, but I think this is already sufficient.
    test(b2->theA == b2);
    test(d->theC == 0);
    cout << "ok" << endl;

    cout << "getting B1, B2, C, and D all at once... " << flush;
    initial->getAll(b1, b2, c, d);
    test(b1);
    test(b2);
    test(c);
    test(d);
    cout << "ok" << endl;
    
    cout << "checking consistency... " << flush;
    test(b1 != b2);
    test(b1 != c);
    test(b1 != d);
    test(b2 != c);
    test(b2 != d);
    test(c != d);
    test(b1->theA == b2);
    test(b1->theB == b1);
    test(b1->theC == 0);
    test(b2->theA == b2);
    test(b2->theB == b1);
    test(b2->theC == c);
    test(c->theB == b2);
    test(d->theA == b1);
    test(d->theB == b2);
    test(d->theC == 0);
    if(!collocated)
    {
        test(d->preMarshalInvoked);
        test(d->postUnmarshalInvoked());
        test(d->theA->preMarshalInvoked);
        test(d->theA->postUnmarshalInvoked());
        test(d->theB->preMarshalInvoked);
        test(d->theB->postUnmarshalInvoked());
        test(d->theB->theC->preMarshalInvoked);
        test(d->theB->theC->postUnmarshalInvoked());
    }
    cout << "ok" << endl;

    cout << "testing protected members... " << flush;
    EPtr e = initial->getE();
    test(e->checkValues());
    FPtr f = initial->getF();
    test(f->checkValues());
    test(f->e2->checkValues());
    cout << "ok" << endl;

    cout << "getting I, J and H... " << flush;
    IPtr i = initial->getI();
    test(i);
    IPtr j = initial->getJ();
    test(j && JPtr::dynamicCast(j));
    IPtr h = initial->getH();
    test(h && HPtr::dynamicCast(h));
    cout << "ok" << endl;

    cout << "setting I... " << flush;
    initial->setI(i);
    initial->setI(j);
    initial->setI(h);
    cout << "ok" << endl;

    cout << "testing sequences... " << flush;
    BaseSeq inS, outS, retS;
    retS = initial->opBaseSeq(inS, outS);

    inS.resize(1);
    inS[0] = new Base();
    retS = initial->opBaseSeq(inS, outS);
    test(retS.size() == 1 && outS.size() == 1);
    cout << "ok" << endl;

    cout << "testing compact ID..." << flush;
    try
    {
        test(initial->getCompact());
    }
    catch(const Ice::OperationNotExistException&)
    {
    }
    cout << "ok" << endl;

    if(!collocated)
    {
        cout << "testing UnexpectedObjectException... " << flush;
        testUOE(communicator);
        cout << "ok" << endl;
    }

    return initial;
}
