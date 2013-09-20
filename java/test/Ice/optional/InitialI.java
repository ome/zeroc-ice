// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.optional;

import test.Ice.optional.Test.*;

public final class InitialI extends Initial
{
    public void
    shutdown(Ice.Current current)
    {
        current.adapter.getCommunicator().shutdown();
    }

    public Ice.Object
    pingPong(Ice.Object obj, Ice.Current current)
    {
        return obj;
    }

    public void
    opOptionalException(Ice.IntOptional a, Ice.Optional<String> b, Ice.Optional<OneOptional> o, Ice.Current current)
        throws OptionalException
    {
        OptionalException ex = new OptionalException();
        if(a.isSet())
        {
            ex.setA(a.get());
        }
        else
        {
            ex.clearA(); // The member "a" has a default value.
        }
        if(b.isSet())
        {
            ex.setB(b.get());
        }
        if(o.isSet())
        {
            ex.setO(o.get());
        }
        throw ex;
    }

    public void
    opDerivedException(Ice.IntOptional a, Ice.Optional<String> b, Ice.Optional<OneOptional> o, Ice.Current current)
        throws OptionalException
    {
        DerivedException ex = new DerivedException();
        if(a.isSet())
        {
            ex.setA(a.get());
        }
        else
        {
            ex.clearA(); // The member "a" has a default value.
        }
        if(b.isSet())
        {
            ex.setB(b.get());
            ex.setSs(b.get());
        }
        else
        {
            ex.clearSs(); // The member "ss" has a default value.
        }
        if(o.isSet())
        {
            ex.setO(o.get());
            ex.setO2(o.get());
        }
        throw ex;
    }

    public void
    opRequiredException(Ice.IntOptional a, Ice.Optional<String> b, Ice.Optional<OneOptional> o, Ice.Current current)
        throws OptionalException
    {
        RequiredException ex = new RequiredException();
        if(a.isSet())
        {
            ex.setA(a.get());
        }
        else
        {
            ex.clearA(); // The member "a" has a default value.
        }
        if(b.isSet())
        {
            ex.setB(b.get());
            ex.ss = b.get();
        }
        if(o.isSet())
        {
            ex.setO(o.get());
            ex.o2 = o.get();
        }
        throw ex;
    }

    public Ice.ByteOptional
    opByte(Ice.ByteOptional p1, Ice.ByteOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public byte
    opByteReq(Ice.ByteOptional p1, Ice.ByteHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.BooleanOptional
    opBool(Ice.BooleanOptional p1, Ice.BooleanOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public boolean
    opBoolReq(Ice.BooleanOptional p1, Ice.BooleanHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.ShortOptional
    opShort(Ice.ShortOptional p1, Ice.ShortOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public short
    opShortReq(Ice.ShortOptional p1, Ice.ShortHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.IntOptional
    opInt(Ice.IntOptional p1, Ice.IntOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public int
    opIntReq(Ice.IntOptional p1, Ice.IntHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.LongOptional
    opLong(Ice.LongOptional p1, Ice.LongOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public long
    opLongReq(Ice.LongOptional p1, Ice.LongHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.FloatOptional
    opFloat(Ice.FloatOptional p1, Ice.FloatOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public float
    opFloatReq(Ice.FloatOptional p1, Ice.FloatHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.DoubleOptional
    opDouble(Ice.DoubleOptional p1, Ice.DoubleOptional p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public double
    opDoubleReq(Ice.DoubleOptional p1, Ice.DoubleHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<String>
    opString(Ice.Optional<String> p1, Ice.Optional<String> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public String
    opStringReq(Ice.Optional<String> p1, Ice.StringHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<MyEnum>
    opMyEnum(Ice.Optional<MyEnum> p1, Ice.Optional<MyEnum> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public MyEnum
    opMyEnumReq(Ice.Optional<MyEnum> p1, MyEnumHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<SmallStruct>
    opSmallStruct(Ice.Optional<SmallStruct> p1, Ice.Optional<SmallStruct> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public SmallStruct
    opSmallStructReq(Ice.Optional<SmallStruct> p1, SmallStructHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<FixedStruct>
    opFixedStruct(Ice.Optional<FixedStruct> p1, Ice.Optional<FixedStruct> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public FixedStruct
    opFixedStructReq(Ice.Optional<FixedStruct> p1, FixedStructHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<VarStruct>
    opVarStruct(Ice.Optional<VarStruct> p1, Ice.Optional<VarStruct> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public VarStruct
    opVarStructReq(Ice.Optional<VarStruct> p1, VarStructHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<OneOptional>
    opOneOptional(Ice.Optional<OneOptional> p1, Ice.Optional<OneOptional> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public OneOptional
    opOneOptionalReq(Ice.Optional<OneOptional> p1, OneOptionalHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<OneOptionalPrx>
    opOneOptionalProxy(Ice.Optional<OneOptionalPrx> p1, Ice.Optional<OneOptionalPrx> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public OneOptionalPrx
    opOneOptionalProxyReq(Ice.Optional<OneOptionalPrx> p1, OneOptionalPrxHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<byte[]>
    opByteSeq(Ice.Optional<byte[]> p1, Ice.Optional<byte[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public byte[]
    opByteSeqReq(Ice.Optional<byte[]> p1, ByteSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<boolean[]>
    opBoolSeq(Ice.Optional<boolean[]> p1, Ice.Optional<boolean[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public boolean[]
    opBoolSeqReq(Ice.Optional<boolean[]> p1, BoolSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<short[]>
    opShortSeq(Ice.Optional<short[]> p1, Ice.Optional<short[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public short[]
    opShortSeqReq(Ice.Optional<short[]> p1, ShortSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<int[]>
    opIntSeq(Ice.Optional<int[]> p1, Ice.Optional<int[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public int[]
    opIntSeqReq(Ice.Optional<int[]> p1, IntSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<long[]>
    opLongSeq(Ice.Optional<long[]> p1, Ice.Optional<long[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public long[]
    opLongSeqReq(Ice.Optional<long[]> p1, LongSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<float[]>
    opFloatSeq(Ice.Optional<float[]> p1, Ice.Optional<float[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public float[]
    opFloatSeqReq(Ice.Optional<float[]> p1, FloatSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<double[]>
    opDoubleSeq(Ice.Optional<double[]> p1, Ice.Optional<double[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public double[]
    opDoubleSeqReq(Ice.Optional<double[]> p1, DoubleSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<String[]>
    opStringSeq(Ice.Optional<String[]> p1, Ice.Optional<String[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public String[]
    opStringSeqReq(Ice.Optional<String[]> p1, StringSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<SmallStruct[]>
    opSmallStructSeq(Ice.Optional<SmallStruct[]> p1, Ice.Optional<SmallStruct[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public SmallStruct[]
    opSmallStructSeqReq(Ice.Optional<SmallStruct[]> p1, SmallStructSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<java.util.List<SmallStruct>>
    opSmallStructList(Ice.Optional<java.util.List<SmallStruct>> p1,
                      Ice.Optional<java.util.List<SmallStruct>> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public java.util.List<SmallStruct>
    opSmallStructListReq(Ice.Optional<java.util.List<SmallStruct>> p1, SmallStructListHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<FixedStruct[]>
    opFixedStructSeq(Ice.Optional<FixedStruct[]> p1, Ice.Optional<FixedStruct[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public FixedStruct[]
    opFixedStructSeqReq(Ice.Optional<FixedStruct[]> p1, FixedStructSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<java.util.List<FixedStruct>>
    opFixedStructList(Ice.Optional<java.util.List<FixedStruct>> p1,
                      Ice.Optional<java.util.List<FixedStruct>> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public java.util.List<FixedStruct>
    opFixedStructListReq(Ice.Optional<java.util.List<FixedStruct>> p1, FixedStructListHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<VarStruct[]>
    opVarStructSeq(Ice.Optional<VarStruct[]> p1, Ice.Optional<VarStruct[]> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public VarStruct[]
    opVarStructSeqReq(Ice.Optional<VarStruct[]> p1, VarStructSeqHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<SerializableClass>
    opSerializable(Ice.Optional<SerializableClass> p1, Ice.Optional<SerializableClass> p3, Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public SerializableClass
    opSerializableReq(Ice.Optional<SerializableClass> p1, Ice.Holder<SerializableClass> p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<java.util.Map<Integer, Integer>>
    opIntIntDict(Ice.Optional<java.util.Map<Integer, Integer>> p1, Ice.Optional<java.util.Map<Integer, Integer>> p3,
                 Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public java.util.Map<Integer, Integer>
    opIntIntDictReq(Ice.Optional<java.util.Map<Integer, Integer>> p1, IntIntDictHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public Ice.Optional<java.util.Map<String, Integer>>
    opStringIntDict(Ice.Optional<java.util.Map<String, Integer>> p1, Ice.Optional<java.util.Map<String, Integer>> p3,
                    Ice.Current current)
    {
        p3.set(p1);
        return p1;
    }

    public java.util.Map<String, Integer>
    opStringIntDictReq(Ice.Optional<java.util.Map<String, Integer>> p1, StringIntDictHolder p3, Ice.Current current)
    {
        p3.value = p1.get();
        return p1.get();
    }

    public void
    opClassAndUnknownOptional(A p, Ice.Current current)
    {
    }

    public void
    sendOptionalClass(boolean req, Ice.Optional<OneOptional> o, Ice.Current current)
    {
    }

    public void
    returnOptionalClass(boolean req, Ice.Optional<OneOptional> o, Ice.Current current)
    {
        o.set(new OneOptional(53));
    }

    public boolean
    supportsRequiredParams(Ice.Current current)
    {
        return true;
    }

    public boolean
    supportsJavaSerializable(Ice.Current current)
    {
        return true;
    }

    public boolean
    supportsCsharpSerializable(Ice.Current current)
    {
        return false;
    }
}
