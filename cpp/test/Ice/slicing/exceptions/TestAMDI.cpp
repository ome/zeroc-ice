// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <TestAMDI.h>
#include <Ice/Ice.h>
#include <TestCommon.h>

using namespace Test;

TestI::TestI()
{
}

void
TestI::baseAsBase_async(const AMD_TestIntf_baseAsBasePtr& cb, const ::Ice::Current&)
{
    Base b;
    b.b = "Base.b";
    cb->ice_exception(b);
}

void
TestI::unknownDerivedAsBase_async(const AMD_TestIntf_unknownDerivedAsBasePtr& cb, const ::Ice::Current&)
{
    UnknownDerived d;
    d.b = "UnknownDerived.b";
    d.ud = "UnknownDerived.ud";
    cb->ice_exception(d);
}

void
TestI::knownDerivedAsBase_async(const AMD_TestIntf_knownDerivedAsBasePtr& cb, const ::Ice::Current&)
{
    KnownDerived d;
    d.b = "KnownDerived.b";
    d.kd = "KnownDerived.kd";
    cb->ice_exception(d);
}

void
TestI::knownDerivedAsKnownDerived_async(const AMD_TestIntf_knownDerivedAsKnownDerivedPtr& cb, const ::Ice::Current&)
{
    KnownDerived d;
    d.b = "KnownDerived.b";
    d.kd = "KnownDerived.kd";
    cb->ice_exception(d);
}

void
TestI::unknownIntermediateAsBase_async(const AMD_TestIntf_unknownIntermediateAsBasePtr& cb, const ::Ice::Current&)
{
    UnknownIntermediate ui;
    ui.b = "UnknownIntermediate.b";
    ui.ui = "UnknownIntermediate.ui";
    cb->ice_exception(ui);
}

void
TestI::knownIntermediateAsBase_async(const AMD_TestIntf_knownIntermediateAsBasePtr& cb, const ::Ice::Current&)
{
    KnownIntermediate ki;
    ki.b = "KnownIntermediate.b";
    ki.ki = "KnownIntermediate.ki";
    cb->ice_exception(ki);
}

void
TestI::knownMostDerivedAsBase_async(const AMD_TestIntf_knownMostDerivedAsBasePtr& cb, const ::Ice::Current&)
{
    KnownMostDerived kmd;
    kmd.b = "KnownMostDerived.b";
    kmd.ki = "KnownMostDerived.ki";
    kmd.kmd = "KnownMostDerived.kmd";
    cb->ice_exception(kmd);
}

void
TestI::knownIntermediateAsKnownIntermediate_async(const AMD_TestIntf_knownIntermediateAsKnownIntermediatePtr& cb,
                                                  const ::Ice::Current&)
{
    KnownIntermediate ki;
    ki.b = "KnownIntermediate.b";
    ki.ki = "KnownIntermediate.ki";
    cb->ice_exception(ki);
}

void
TestI::knownMostDerivedAsKnownIntermediate_async(const AMD_TestIntf_knownMostDerivedAsKnownIntermediatePtr& cb,
                                                 const ::Ice::Current&)
{
    KnownMostDerived kmd;
    kmd.b = "KnownMostDerived.b";
    kmd.ki = "KnownMostDerived.ki";
    kmd.kmd = "KnownMostDerived.kmd";
    cb->ice_exception(kmd);
}

void
TestI::
knownMostDerivedAsKnownMostDerived_async(const AMD_TestIntf_knownMostDerivedAsKnownMostDerivedPtr& cb,
                                         const ::Ice::Current&)
{
    KnownMostDerived kmd;
    kmd.b = "KnownMostDerived.b";
    kmd.ki = "KnownMostDerived.ki";
    kmd.kmd = "KnownMostDerived.kmd";
    cb->ice_exception(kmd);
}

void
TestI::unknownMostDerived1AsBase_async(const AMD_TestIntf_unknownMostDerived1AsBasePtr& cb, const ::Ice::Current&)
{
    UnknownMostDerived1 umd1;
    umd1.b = "UnknownMostDerived1.b";
    umd1.ki = "UnknownMostDerived1.ki";
    umd1.umd1 = "UnknownMostDerived1.umd1";
    cb->ice_exception(umd1);
}

void
TestI::unknownMostDerived1AsKnownIntermediate_async(const AMD_TestIntf_unknownMostDerived1AsKnownIntermediatePtr& cb,
                                                    const ::Ice::Current&)
{
    UnknownMostDerived1 umd1;
    umd1.b = "UnknownMostDerived1.b";
    umd1.ki = "UnknownMostDerived1.ki";
    umd1.umd1 = "UnknownMostDerived1.umd1";
    cb->ice_exception(umd1);
}

void
TestI::unknownMostDerived2AsBase_async(const AMD_TestIntf_unknownMostDerived2AsBasePtr& cb, const ::Ice::Current&)
{
    UnknownMostDerived2 umd2;
    umd2.b = "UnknownMostDerived2.b";
    umd2.ui = "UnknownMostDerived2.ui";
    umd2.umd2 = "UnknownMostDerived2.umd2";
    cb->ice_exception(umd2);
}

void
TestI::unknownMostDerived2AsBaseCompact_async(const AMD_TestIntf_unknownMostDerived2AsBaseCompactPtr& cb,
                                              const ::Ice::Current&)
{
    UnknownMostDerived2 umd2;
    umd2.b = "UnknownMostDerived2.b";
    umd2.ui = "UnknownMostDerived2.ui";
    umd2.umd2 = "UnknownMostDerived2.umd2";
    cb->ice_exception(umd2);
}

void
TestI::knownPreservedAsBase_async(const AMD_TestIntf_knownPreservedAsBasePtr& cb, const ::Ice::Current&)
{
    KnownPreservedDerived ex;
    ex.b = "base";
    ex.kp = "preserved";
    ex.kpd = "derived";
    cb->ice_exception(ex);
}

void
TestI::knownPreservedAsKnownPreserved_async(const AMD_TestIntf_knownPreservedAsKnownPreservedPtr& cb,
                                            const ::Ice::Current&)
{
    KnownPreservedDerived ex;
    ex.b = "base";
    ex.kp = "preserved";
    ex.kpd = "derived";
    cb->ice_exception(ex);
}

void
TestI::relayKnownPreservedAsBase_async(const AMD_TestIntf_relayKnownPreservedAsBasePtr& cb, const RelayPrx& r,
                                       const ::Ice::Current&)
{
    try
    {
        r->knownPreservedAsBase();
        test(false);
    }
    catch(const Ice::Exception& ex)
    {
        cb->ice_exception(ex);
    }
}

void
TestI::relayKnownPreservedAsKnownPreserved_async(const AMD_TestIntf_relayKnownPreservedAsKnownPreservedPtr& cb,
                                                 const RelayPrx& r, const ::Ice::Current&)
{
    try
    {
        r->knownPreservedAsKnownPreserved();
        test(false);
    }
    catch(const Ice::Exception& ex)
    {
        cb->ice_exception(ex);
    }
}

void
TestI::unknownPreservedAsBase_async(const AMD_TestIntf_unknownPreservedAsBasePtr& cb, const ::Ice::Current&)
{
    SPreserved2 ex;
    ex.b = "base";
    ex.kp = "preserved";
    ex.kpd = "derived";
    ex.p1 = new SPreservedClass("bc", "spc");
    ex.p2 = ex.p1;
    cb->ice_exception(ex);
}

void
TestI::unknownPreservedAsKnownPreserved_async(const AMD_TestIntf_unknownPreservedAsKnownPreservedPtr& cb,
                                              const ::Ice::Current&)
{
    SPreserved2 ex;
    ex.b = "base";
    ex.kp = "preserved";
    ex.kpd = "derived";
    ex.p1 = new SPreservedClass("bc", "spc");
    ex.p2 = ex.p1;
    cb->ice_exception(ex);
}

void
TestI::relayUnknownPreservedAsBase_async(const AMD_TestIntf_relayUnknownPreservedAsBasePtr& cb, const RelayPrx& r,
                                         const ::Ice::Current&)
{
    try
    {
        r->unknownPreservedAsBase();
        test(false);
    }
    catch(const Ice::Exception& ex)
    {
        cb->ice_exception(ex);
    }
}

void
TestI::relayUnknownPreservedAsKnownPreserved_async(const AMD_TestIntf_relayUnknownPreservedAsKnownPreservedPtr& cb,
                                                   const RelayPrx& r, const ::Ice::Current&)
{
    try
    {
        r->unknownPreservedAsKnownPreserved();
        test(false);
    }
    catch(const Ice::Exception& ex)
    {
        cb->ice_exception(ex);
    }
}

void
TestI::shutdown_async(const AMD_TestIntf_shutdownPtr& cb, const ::Ice::Current& current)
{
    current.adapter->getCommunicator()->shutdown();
    cb->ice_response();
}
