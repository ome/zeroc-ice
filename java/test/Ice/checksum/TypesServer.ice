// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["java:package:test.Ice.checksum.server"]]
module Test
{

//
// TEST: Same
//
const int IntConst1 = 100;

//
// TEST: Value changed
//
const int IntConst2 = 1000;

//
// TEST: Type changed
//
const short IntConst3 = 100;

//
// TEST: Same
//
enum Enum1 { Enum11, Enum12, Enum13 };

//
// TEST: Add enumerator
//
enum Enum2 { Enum21, Enum22, Enum23, Enum24 };

//
// TEST: Remove enumerator
//
enum Enum3 { Enum32, Enum33 };

//
// TEST: Change to a different type
//
class Enum4 {};

//
// TEST: Same
//
sequence<int> Sequence1;

//
// TEST: Change sequence type
//
sequence<short> Sequence2;

//
// TEST: Change to a different type
//
class Sequence3 {};

//
// TEST: Same
//
dictionary<string, int> Dictionary1;

//
// TEST: Change key type
//
dictionary<long, int> Dictionary2;

//
// TEST: Change value type
//
dictionary<string, bool> Dictionary3;

//
// TEST: Change to a different type
//
class Dictionary4 {};

//
// TEST: Same
//
struct Struct1
{
    string str;
    bool b;
};

//
// TEST: Add member
//
struct Struct2
{
    string str;
    bool b;
    float f;
};

//
// TEST: Change member type
//
struct Struct3
{
    string str;
    double b;
};

//
// TEST: Remove member
//
struct Struct4
{
    bool b;
};

//
// TEST: Change to a different type
//
class Struct5 {};

//
// TEST: Same
//
interface Interface1
{
};

//
// TEST: Change interface to class
//
class Interface2
{
};

//
// TEST: Add base interface
//
interface Interface3 extends Interface1
{
};

//
// TEST: Add operation
//
interface Interface4
{
    void opInterface4();
};

//
// TEST: Same
//
class EmptyClass1
{
};

//
// TEST: Add data member
//
class EmptyClass2
{
    double d;
};

//
// TEST: Add operation
//
class EmptyClass3
{
    void newOp();
};

//
// TEST: Add base class
//
class EmptyClass4 extends EmptyClass1
{
};

//
// TEST: Add interface
//
class EmptyClass5 implements Interface1
{
};

//
// TEST: Same
//
class SimpleClass1
{
    string str;
    float f;
};

//
// TEST: Add operation
//
class SimpleClass2
{
    string str;
    float f;
    void newOp();
};

//
// TEST: Rename member
//
class SimpleClass3
{
    string str;
    float g;
};

//
// TEST: Add member
//
class SimpleClass4
{
    string str;
    float f;
    bool b;
};

//
// TEST: Remove member
//
class SimpleClass5
{
    string str;
};

//
// TEST: Reorder members
//
class SimpleClass6
{
    float f;
    string str;
};

//
// TEST: Change member type
//
class SimpleClass7
{
    string str;
    double f;
};

//
// TEST: Same
//
exception Exception1
{
    string str;
    bool b;
};

//
// TEST: Add member
//
exception Exception2
{
    string str;
    bool b;
    float f;
};

//
// TEST: Change member type
//
exception Exception3
{
    string str;
    double b;
};

//
// TEST: Remove member
//
exception Exception4
{
    bool b;
};

//
// TEST: Add base exception
//
exception Exception5 extends Exception1
{
};

//
// TEST: Change to a different type
//
class Exception6 {};

//
// TEST: Same
//
class BaseClass1
{
    void baseOp1();
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Change return type
//
class BaseClass2
{
    int baseOp();
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Add parameter
//
class BaseClass3
{
    void baseOp(Object o);
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Add exception
//
class BaseClass4
{
    void baseOp();
    void baseOp2(int i, out string s) throws Exception1, Exception2;
};

//
// TEST: Change out parameter to in parameter
//
class BaseClass5
{
    void baseOp();
    void baseOp2(int i, string s) throws Exception1;
};

//
// TEST: Remove parameter
//
class BaseClass6
{
    void baseOp();
    void baseOp2(out string s) throws Exception1;
};

//
// TEST: Remove exception
//
class BaseClass7
{
    void baseOp();
    void baseOp2(int i, out string s);
};

//
// TEST: Remove operation
//
class BaseClass8
{
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Add base class
//
class BaseClass9 extends EmptyClass1
{
    void baseOp();
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Add interface
//
class BaseClass10 implements Interface1
{
    void baseOp();
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Add base class and interface
//
class BaseClass11 extends EmptyClass1 implements Interface1
{
    void baseOp();
    void baseOp2(int i, out string s) throws Exception1;
};

//
// TEST: Local
//
local enum LocalEnum { LocalEnum1, LocalEnum2, LocalEnum3 };

//
// TEST: Local
//
local sequence<string> LocalSequence;

//
// TEST: Local
//
local dictionary<string, string> LocalDictionary;

//
// TEST: Local
//
local struct LocalStruct
{
    string str;
};

//
// TEST: Local
//
local class LocalClass
{
};

};
