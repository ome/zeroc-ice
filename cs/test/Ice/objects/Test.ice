// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

module Test
{

struct S
{
    string str;
};

class Base
{
    S theS;
    string str;
};

class AbstractBase extends Base
{
    void op();
};

class B;
class C;

class A
{
    B theB;
    C theC;

    bool preMarshalInvoked;
    bool postUnmarshalInvoked();
};

class B extends A
{
    A theA;
};

class C
{
    B theB;

    bool preMarshalInvoked;
    bool postUnmarshalInvoked();
};

class D
{
    A theA;
    B theB;
    C theC;    

    bool preMarshalInvoked;
    bool postUnmarshalInvoked();
};

["protected"] class E
{
    int i;
    string s;

    bool checkValues();
};

class F
{
    ["protected"] E e1;
    E e2;

    bool checkValues();
};

interface I
{
};

interface J extends I
{
};

class H implements I
{
};

sequence<Base> BaseSeq;

class CompactExt;

class Compact(1)
{
};

const int CompactExtId = 789;

class CompactExt(CompactExtId) extends Compact
{
};

class Initial
{
    void shutdown();
    B getB1();
    B getB2();
    C getC();
    D getD();
    E getE();
    F getF();

    void getAll(out B b1, out B b2, out C theC, out D theD);

    I getI();
    I getJ();
    I getH();

    void setI(I theI);

    BaseSeq opBaseSeq(BaseSeq inSeq, out BaseSeq outSeq);

    Compact getCompact();
};

class Empty
{
};

class AlsoEmpty
{
};

interface UnexpectedObjectExceptionTest
{
    Empty op();
};

//
// Remaining definitions are here to ensure that the generated code compiles.
//

class COneMember
{
    Empty e;
};

class CTwoMembers
{
    Empty e1;
    Empty e2;
};

exception EOneMember
{
    Empty e;
};

exception ETwoMembers
{
    Empty e1;
    Empty e2;
};

struct SOneMember
{
    Empty e;
};

struct STwoMembers
{
    Empty e1;
    Empty e2;
};

dictionary<int, COneMember> DOneMember;
dictionary<int, CTwoMembers> DTwoMembers;

};
