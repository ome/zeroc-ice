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

sequence<byte> AByteS;
["clr:generic:List"] sequence<byte> LByteS;
["clr:generic:LinkedList"] sequence<byte> KByteS;
["clr:generic:Queue"] sequence<byte> QByteS;
["clr:generic:Stack"] sequence<byte> SByteS;
["clr:collection"] sequence<byte> CByteS;

sequence<bool> ABoolS;
["clr:generic:List"] sequence<bool> LBoolS;
["clr:generic:LinkedList"] sequence<bool> KBoolS;
["clr:generic:Queue"] sequence<bool> QBoolS;
["clr:generic:Stack"] sequence<bool> SBoolS;
["clr:collection"] sequence<bool> CBoolS;

sequence<short> AShortS;
["clr:generic:List"] sequence<short> LShortS;
["clr:generic:LinkedList"] sequence<short> KShortS;
["clr:generic:Queue"] sequence<short> QShortS;
["clr:generic:Stack"] sequence<short> SShortS;
["clr:collection"] sequence<short> CShortS;

sequence<int> AIntS;
["clr:generic:List"] sequence<int> LIntS;
["clr:generic:LinkedList"] sequence<int> KIntS;
["clr:generic:Queue"] sequence<int> QIntS;
["clr:generic:Stack"] sequence<int> SIntS;
["clr:collection"] sequence<int> CIntS;

sequence<long> ALongS;
["clr:generic:List"] sequence<long> LLongS;
["clr:generic:LinkedList"] sequence<long> KLongS;
["clr:generic:Queue"] sequence<long> QLongS;
["clr:generic:Stack"] sequence<long> SLongS;
["clr:collection"] sequence<long> CLongS;

sequence<float> AFloatS;
["clr:generic:List"] sequence<float> LFloatS;
["clr:generic:LinkedList"] sequence<float> KFloatS;
["clr:generic:Queue"] sequence<float> QFloatS;
["clr:generic:Stack"] sequence<float> SFloatS;
["clr:collection"] sequence<float> CFloatS;

sequence<double> ADoubleS;
["clr:generic:List"] sequence<double> LDoubleS;
["clr:generic:LinkedList"] sequence<double> KDoubleS;
["clr:generic:Queue"] sequence<double> QDoubleS;
["clr:generic:Stack"] sequence<double> SDoubleS;
["clr:collection"] sequence<double> CDoubleS;

sequence<string> AStringS;
["clr:generic:List"] sequence<string> LStringS;
["clr:generic:LinkedList"] sequence<string> KStringS;
["clr:generic:Queue"] sequence<string> QStringS;
["clr:generic:Stack"] sequence<string> SStringS;
["clr:collection"] sequence<string> CStringS;

sequence<Object> AObjectS;
["clr:generic:List"] sequence<Object> LObjectS;
["clr:collection"] sequence<Object> CObjectS;

sequence<Object*> AObjectPrxS;
["clr:generic:List"] sequence<Object*> LObjectPrxS;
["clr:generic:LinkedList"] sequence<Object*> KObjectPrxS;
["clr:generic:Queue"] sequence<Object*> QObjectPrxS;
["clr:generic:Stack"] sequence<Object*> SObjectPrxS;
["clr:collection"] sequence<Object*> CObjectPrxS;

struct S
{
    int i;
};

sequence<S> AStructS;
["clr:generic:List"] sequence<S> LStructS;
["clr:generic:LinkedList"] sequence<S> KStructS;
["clr:generic:Queue"] sequence<S> QStructS;
["clr:generic:Stack"] sequence<S> SStructS;
["clr:collection"] sequence<S> CStructS;

class CV
{
    int i;
};

sequence<CV> ACVS;
["clr:generic:List"] sequence<CV> LCVS;
["clr:collection"] sequence<CV> CCVS;

sequence<CV*> ACVPrxS;
["clr:generic:List"] sequence<CV*> LCVPrxS;
["clr:generic:LinkedList"] sequence<CV*> KCVPrxS;
["clr:generic:Queue"] sequence<CV*> QCVPrxS;
["clr:generic:Stack"] sequence<CV*> SCVPrxS;
["clr:collection"] sequence<CV*> CCVPrxS;

class CR
{
    CV v;
};

sequence<CR> ACRS;
["clr:generic:List"] sequence<CR> LCRS;
["clr:collection"] sequence<CR> CCRS;

enum En { A, B, C };

sequence<En> AEnS;
["clr:generic:List"] sequence<En> LEnS;
["clr:generic:LinkedList"] sequence<En> KEnS;
["clr:generic:Queue"] sequence<En> QEnS;
["clr:generic:Stack"] sequence<En> SEnS;
["clr:collection"] sequence<En> CEnS;

["clr:generic:Custom"] sequence<int> CustomIntS;
["clr:generic:Custom"] sequence<CV> CustomCVS;

["clr:generic:Custom"] sequence<CustomIntS> CustomIntSS;
["clr:generic:Custom"] sequence<CustomCVS> CustomCVSS;

["clr:serializable:Serialize.Small"] sequence<byte> SerialSmall;
["clr:serializable:Serialize.Large"] sequence<byte> SerialLarge;
["clr:serializable:Serialize.Struct"] sequence<byte> SerialStruct;

["ami", "amd"] class MyClass
{
    void shutdown();

    AByteS opAByteS(AByteS i, out AByteS o);
    LByteS opLByteS(LByteS i, out LByteS o);
    KByteS opKByteS(KByteS i, out KByteS o);
    QByteS opQByteS(QByteS i, out QByteS o);
    SByteS opSByteS(SByteS i, out SByteS o);
    CByteS opCByteS(CByteS i, out CByteS o);

    ABoolS opABoolS(ABoolS i, out ABoolS o);
    LBoolS opLBoolS(LBoolS i, out LBoolS o);
    KBoolS opKBoolS(KBoolS i, out KBoolS o);
    QBoolS opQBoolS(QBoolS i, out QBoolS o);
    SBoolS opSBoolS(SBoolS i, out SBoolS o);
    CBoolS opCBoolS(CBoolS i, out CBoolS o);

    AShortS opAShortS(AShortS i, out AShortS o);
    LShortS opLShortS(LShortS i, out LShortS o);
    KShortS opKShortS(KShortS i, out KShortS o);
    QShortS opQShortS(QShortS i, out QShortS o);
    SShortS opSShortS(SShortS i, out SShortS o);
    CShortS opCShortS(CShortS i, out CShortS o);

    AIntS opAIntS(AIntS i, out AIntS o);
    LIntS opLIntS(LIntS i, out LIntS o);
    KIntS opKIntS(KIntS i, out KIntS o);
    QIntS opQIntS(QIntS i, out QIntS o);
    SIntS opSIntS(SIntS i, out SIntS o);
    CIntS opCIntS(CIntS i, out CIntS o);

    ALongS opALongS(ALongS i, out ALongS o);
    LLongS opLLongS(LLongS i, out LLongS o);
    KLongS opKLongS(KLongS i, out KLongS o);
    QLongS opQLongS(QLongS i, out QLongS o);
    SLongS opSLongS(SLongS i, out SLongS o);
    CLongS opCLongS(CLongS i, out CLongS o);

    AFloatS opAFloatS(AFloatS i, out AFloatS o);
    LFloatS opLFloatS(LFloatS i, out LFloatS o);
    KFloatS opKFloatS(KFloatS i, out KFloatS o);
    QFloatS opQFloatS(QFloatS i, out QFloatS o);
    SFloatS opSFloatS(SFloatS i, out SFloatS o);
    CFloatS opCFloatS(CFloatS i, out CFloatS o);

    ADoubleS opADoubleS(ADoubleS i, out ADoubleS o);
    LDoubleS opLDoubleS(LDoubleS i, out LDoubleS o);
    KDoubleS opKDoubleS(KDoubleS i, out KDoubleS o);
    QDoubleS opQDoubleS(QDoubleS i, out QDoubleS o);
    SDoubleS opSDoubleS(SDoubleS i, out SDoubleS o);
    CDoubleS opCDoubleS(CDoubleS i, out CDoubleS o);

    AStringS opAStringS(AStringS i, out AStringS o);
    LStringS opLStringS(LStringS i, out LStringS o);
    KStringS opKStringS(KStringS i, out KStringS o);
    QStringS opQStringS(QStringS i, out QStringS o);
    SStringS opSStringS(SStringS i, out SStringS o);
    CStringS opCStringS(CStringS i, out CStringS o);

    AObjectS opAObjectS(AObjectS i, out AObjectS o);
    LObjectS opLObjectS(LObjectS i, out LObjectS o);
    CObjectS opCObjectS(CObjectS i, out CObjectS o);

    AObjectPrxS opAObjectPrxS(AObjectPrxS i, out AObjectPrxS o);
    LObjectPrxS opLObjectPrxS(LObjectPrxS i, out LObjectPrxS o);
    KObjectPrxS opKObjectPrxS(KObjectPrxS i, out KObjectPrxS o);
    QObjectPrxS opQObjectPrxS(QObjectPrxS i, out QObjectPrxS o);
    SObjectPrxS opSObjectPrxS(SObjectPrxS i, out SObjectPrxS o);
    CObjectPrxS opCObjectPrxS(CObjectPrxS i, out CObjectPrxS o);

    AStructS opAStructS(AStructS i, out AStructS o);
    LStructS opLStructS(LStructS i, out LStructS o);
    KStructS opKStructS(KStructS i, out KStructS o);
    QStructS opQStructS(QStructS i, out QStructS o);
    SStructS opSStructS(SStructS i, out SStructS o);
    CStructS opCStructS(CStructS i, out CStructS o);

    ACVS opACVS(ACVS i, out ACVS o);
    LCVS opLCVS(LCVS i, out LCVS o);
    CCVS opCCVS(CCVS i, out CCVS o);

    ACRS opACRS(ACRS i, out ACRS o);
    LCRS opLCRS(LCRS i, out LCRS o);
    CCRS opCCRS(CCRS i, out CCRS o);

    AEnS opAEnS(AEnS i, out AEnS o);
    LEnS opLEnS(LEnS i, out LEnS o);
    KEnS opKEnS(KEnS i, out KEnS o);
    QEnS opQEnS(QEnS i, out QEnS o);
    SEnS opSEnS(SEnS i, out SEnS o);
    CEnS opCEnS(CEnS i, out CEnS o);

    ACVPrxS opACVPrxS(ACVPrxS i, out ACVPrxS o);
    LCVPrxS opLCVPrxS(LCVPrxS i, out LCVPrxS o);
    KCVPrxS opKCVPrxS(KCVPrxS i, out KCVPrxS o);
    QCVPrxS opQCVPrxS(QCVPrxS i, out QCVPrxS o);
    SCVPrxS opSCVPrxS(SCVPrxS i, out SCVPrxS o);
    CCVPrxS opCCVPrxS(CCVPrxS i, out CCVPrxS o);

    CustomIntS opCustomIntS(CustomIntS i, out CustomIntS o);
    CustomCVS opCustomCVS(CustomCVS i, out CustomCVS o);

    CustomIntSS opCustomIntSS(CustomIntSS i, out CustomIntSS o);
    CustomCVSS opCustomCVSS(CustomCVSS i, out CustomCVSS o);

    SerialSmall opSerialSmallCSharp(SerialSmall i, out SerialSmall o);
    SerialLarge opSerialLargeCSharp(SerialLarge i, out SerialLarge o);
    SerialStruct opSerialStructCSharp(SerialStruct i, out SerialStruct o);
};

};
