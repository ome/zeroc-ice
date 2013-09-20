// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["java:package:test.Ice.slicing.exceptions.client"]]
module Test
{

//
// Duplicate types from Test.ice. We cannot use #include since
// that will use the types from the same prefix.
//

exception Base
{
    string b;
};

exception KnownDerived extends Base
{
    string kd;
};

exception KnownIntermediate extends Base
{
    string ki;
};

exception KnownMostDerived extends KnownIntermediate
{
    string kmd;
};

["preserve-slice"]
exception KnownPreserved extends Base
{
    string kp;
};

exception KnownPreservedDerived extends KnownPreserved
{
    string kpd;
};

["preserve-slice"]
class BaseClass
{
    string bc;
};

["format:sliced"]
interface Relay
{
    void knownPreservedAsBase() throws Base;
    void knownPreservedAsKnownPreserved() throws KnownPreserved;

    void unknownPreservedAsBase() throws Base;
    void unknownPreservedAsKnownPreserved() throws KnownPreserved;
};

["ami", "format:sliced"]
interface TestIntf
{
    void baseAsBase() throws Base;
    void unknownDerivedAsBase() throws Base;
    void knownDerivedAsBase() throws Base;
    void knownDerivedAsKnownDerived() throws KnownDerived;

    void unknownIntermediateAsBase() throws Base;
    void knownIntermediateAsBase() throws Base;
    void knownMostDerivedAsBase() throws Base;
    void knownIntermediateAsKnownIntermediate() throws KnownIntermediate;
    void knownMostDerivedAsKnownIntermediate() throws KnownIntermediate;
    void knownMostDerivedAsKnownMostDerived() throws KnownMostDerived;

    void unknownMostDerived1AsBase() throws Base;
    void unknownMostDerived1AsKnownIntermediate() throws KnownIntermediate;
    void unknownMostDerived2AsBase() throws Base;

    ["format:compact"] void unknownMostDerived2AsBaseCompact() throws Base;

    void knownPreservedAsBase() throws Base;
    void knownPreservedAsKnownPreserved() throws KnownPreserved;

    void relayKnownPreservedAsBase(Relay* r) throws Base;
    void relayKnownPreservedAsKnownPreserved(Relay* r) throws KnownPreserved;

    void unknownPreservedAsBase() throws Base;
    void unknownPreservedAsKnownPreserved() throws KnownPreserved;

    void relayUnknownPreservedAsBase(Relay* r) throws Base;
    void relayUnknownPreservedAsKnownPreserved(Relay* r) throws KnownPreserved;

    void shutdown();
};

//
// Types private to the client.
//

class PreservedClass extends BaseClass
{
    string pc;
};

exception Preserved1 extends KnownPreservedDerived
{
    BaseClass p1;
};

exception Preserved2 extends Preserved1
{
    BaseClass p2;
};

};
