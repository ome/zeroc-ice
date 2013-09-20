// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef TEST_I_H
#define TEST_I_H

#include <TestAMD.h>

bool
endsWith(const std::string&, const std::string&);

class ThrowerI : public Test::Thrower
{
public:

    ThrowerI();

    virtual void shutdown_async(const Test::AMD_Thrower_shutdownPtr&,
                                const Ice::Current&);
    virtual void supportsUndeclaredExceptions_async(const Test::AMD_Thrower_supportsUndeclaredExceptionsPtr&,
                                                    const Ice::Current&);
    virtual void supportsAssertException_async(const Test::AMD_Thrower_supportsAssertExceptionPtr&,
                                               const Ice::Current&);

    virtual void throwAasA_async(const Test::AMD_Thrower_throwAasAPtr&,
                                 Ice::Int, const Ice::Current&);
    virtual void throwAorDasAorD_async(const Test::AMD_Thrower_throwAorDasAorDPtr&,
                                       Ice::Int, const Ice::Current&);
    virtual void throwBasA_async(const Test::AMD_Thrower_throwBasAPtr&,
                                 Ice::Int, Ice::Int, const Ice::Current&);
    virtual void throwCasA_async(const Test::AMD_Thrower_throwCasAPtr&,
                                 Ice::Int, Ice::Int, Ice::Int, const Ice::Current&);
    virtual void throwBasB_async(const Test::AMD_Thrower_throwBasBPtr&,
                                 Ice::Int, Ice::Int, const Ice::Current&);
    virtual void throwCasB_async(const Test::AMD_Thrower_throwCasBPtr&,
                                 Ice::Int, Ice::Int, Ice::Int, const Ice::Current&);
    virtual void throwCasC_async(const Test::AMD_Thrower_throwCasCPtr&,
                                 Ice::Int, Ice::Int, Ice::Int, const Ice::Current&);

    virtual void throwModA_async(const Test::AMD_Thrower_throwModAPtr&,
                                 Ice::Int, Ice::Int, const Ice::Current&);

    virtual void throwUndeclaredA_async(const Test::AMD_Thrower_throwUndeclaredAPtr&,
                                        Ice::Int, const Ice::Current&);
    virtual void throwUndeclaredB_async(const Test::AMD_Thrower_throwUndeclaredBPtr&,
                                        Ice::Int, Ice::Int, const Ice::Current&);
    virtual void throwUndeclaredC_async(const Test::AMD_Thrower_throwUndeclaredCPtr&,
                                        Ice::Int, Ice::Int, Ice::Int, const Ice::Current&);
    virtual void throwLocalException_async(const Test::AMD_Thrower_throwLocalExceptionPtr&,
                                           const Ice::Current&);
    virtual void throwNonIceException_async(const Test::AMD_Thrower_throwNonIceExceptionPtr&,
                                            const Ice::Current&);
    virtual void throwAssertException_async(const Test::AMD_Thrower_throwAssertExceptionPtr&,
                                            const Ice::Current&);

    virtual void throwLocalExceptionIdempotent_async(const Test::AMD_Thrower_throwLocalExceptionIdempotentPtr&,
                                                     const Ice::Current&);

    virtual void throwAfterResponse_async(const Test::AMD_Thrower_throwAfterResponsePtr&, const Ice::Current&);
    virtual void throwAfterException_async(const Test::AMD_Thrower_throwAfterExceptionPtr&, const Ice::Current&);
    
    virtual void throwE_async(const Test::AMD_Thrower_throwEPtr&, const Ice::Current&);
    virtual void throwF_async(const Test::AMD_Thrower_throwFPtr&, const Ice::Current&);
    virtual void throwG_async(const Test::AMD_Thrower_throwGPtr&, const Ice::Current&);
    virtual void throwH_async(const Test::AMD_Thrower_throwHPtr&, const Ice::Current&);
};

#endif
