// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

using System;
using System.Diagnostics;
using Test;

public class AllTests : TestCommon.TestApp
{
#if SILVERLIGHT
    public override Ice.InitializationData initData()
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties();
        initData.properties.setProperty("Ice.FactoryAssemblies", "optional,version=1.0.0.0");
        return initData;
    }

    override
    public void run(Ice.Communicator communicator)
#else
    public static TestIntfPrx allTests(Ice.Communicator communicator)
#endif
    {
        string sref = "test:default -p 12010";
        Ice.ObjectPrx obj = communicator.stringToProxy(sref);
        test(obj != null);
        TestIntfPrx proxy = TestIntfPrxHelper.uncheckedCast(obj);
        test(proxy != null);

        Console.Out.Write("testing enum values... ");
        Console.Out.Flush();

        test((int)ByteEnum.benum1 == 0);
        test((int)ByteEnum.benum2 == 1);
        test((int)ByteEnum.benum3 == ByteConst1.value);
        test((int)ByteEnum.benum4 == ByteConst1.value + 1);
        test((int)ByteEnum.benum5 == ShortConst1.value);
        test((int)ByteEnum.benum6 == ShortConst1.value + 1);
        test((int)ByteEnum.benum7 == IntConst1.value);
        test((int)ByteEnum.benum8 == IntConst1.value + 1);
        test((int)ByteEnum.benum9 == LongConst1.value);
        test((int)ByteEnum.benum10 == LongConst1.value + 1);
        test((int)ByteEnum.benum11 == ByteConst2.value);

        test((int)ShortEnum.senum1 == 3);
        test((int)ShortEnum.senum2 == 4);
        test((int)ShortEnum.senum3 == ByteConst1.value);
        test((int)ShortEnum.senum4 == ByteConst1.value + 1);
        test((int)ShortEnum.senum5 == ShortConst1.value);
        test((int)ShortEnum.senum6 == ShortConst1.value + 1);
        test((int)ShortEnum.senum7 == IntConst1.value);
        test((int)ShortEnum.senum8 == IntConst1.value + 1);
        test((int)ShortEnum.senum9 == LongConst1.value);
        test((int)ShortEnum.senum10 == LongConst1.value + 1);
        test((int)ShortEnum.senum11 == ShortConst2.value);

        test((int)IntEnum.ienum1 == 0);
        test((int)IntEnum.ienum2 == 1);
        test((int)IntEnum.ienum3 == ByteConst1.value);
        test((int)IntEnum.ienum4 == ByteConst1.value + 1);
        test((int)IntEnum.ienum5 == ShortConst1.value);
        test((int)IntEnum.ienum6 == ShortConst1.value + 1);
        test((int)IntEnum.ienum7 == IntConst1.value);
        test((int)IntEnum.ienum8 == IntConst1.value + 1);
        test((int)IntEnum.ienum9 == LongConst1.value);
        test((int)IntEnum.ienum10 == LongConst1.value + 1);
        test((int)IntEnum.ienum11 == IntConst2.value);
        test((int)IntEnum.ienum12 == LongConst2.value);

        test((int)SimpleEnum.red == 0);
        test((int)SimpleEnum.green == 1);
        test((int)SimpleEnum.blue == 2);

        Console.Out.WriteLine("ok");

        Console.Out.Write("testing enum streaming... ");
        Console.Out.Flush();

        Ice.OutputStream ostr;
        byte[] bytes;

        bool encoding_1_0 = communicator.getProperties().getProperty("Ice.Default.EncodingVersion").Equals("1.0");

        ostr = Ice.Util.createOutputStream(communicator);
        ByteEnumHelper.write(ostr, ByteEnum.benum11);
        bytes = ostr.finished();
        test(bytes.Length == 1); // ByteEnum should require one byte

        ostr = Ice.Util.createOutputStream(communicator);
        ShortEnumHelper.write(ostr, ShortEnum.senum11);
        bytes = ostr.finished();
        test(bytes.Length == (encoding_1_0 ? 2 : 5));

        ostr = Ice.Util.createOutputStream(communicator);
        IntEnumHelper.write(ostr, IntEnum.ienum11);
        bytes = ostr.finished();
        test(bytes.Length == (encoding_1_0 ? 4 : 5));

        ostr = Ice.Util.createOutputStream(communicator);
        SimpleEnumHelper.write(ostr, SimpleEnum.blue);
        bytes = ostr.finished();
        test(bytes.Length == 1); // SimpleEnum should require one byte

        Console.Out.WriteLine("ok");

        Console.Out.Write("testing enum operations... ");
        Console.Out.Flush();

        ByteEnum byteEnum;
        test(proxy.opByte(ByteEnum.benum1, out byteEnum) == ByteEnum.benum1);
        test(byteEnum == ByteEnum.benum1);
        test(proxy.opByte(ByteEnum.benum11, out byteEnum) == ByteEnum.benum11);
        test(byteEnum == ByteEnum.benum11);

        ShortEnum shortEnum;
        test(proxy.opShort(ShortEnum.senum1, out shortEnum) == ShortEnum.senum1);
        test(shortEnum == ShortEnum.senum1);
        test(proxy.opShort(ShortEnum.senum11, out shortEnum) == ShortEnum.senum11);
        test(shortEnum == ShortEnum.senum11);

        IntEnum intEnum;
        test(proxy.opInt(IntEnum.ienum1, out intEnum) == IntEnum.ienum1);
        test(intEnum == IntEnum.ienum1);
        test(proxy.opInt(IntEnum.ienum11, out intEnum) == IntEnum.ienum11);
        test(intEnum == IntEnum.ienum11);
        test(proxy.opInt(IntEnum.ienum12, out intEnum) == IntEnum.ienum12);
        test(intEnum == IntEnum.ienum12);

        SimpleEnum s;
        test(proxy.opSimple(SimpleEnum.green, out s) == SimpleEnum.green);
        test(s == SimpleEnum.green);

        Console.Out.WriteLine("ok");

        Console.Out.Write("testing enum exceptions... ");
        Console.Out.Flush();

        try
        {
            ostr = Ice.Util.createOutputStream(communicator);
            ostr.writeByte((byte)128); // Invalid enumerator
            Ice.InputStream istr = Ice.Util.createInputStream(communicator, ostr.finished());
            ByteEnumHelper.read(istr);
            test(false);
        }
        catch(Ice.MarshalException)
        {
        }

        try
        {
            ostr = Ice.Util.createOutputStream(communicator);
            ostr.writeShort((short)-1); // Negative enumerators are not supported
            Ice.InputStream istr = Ice.Util.createInputStream(communicator, ostr.finished());
            ShortEnumHelper.read(istr);
            test(false);
        }
        catch(Ice.MarshalException)
        {
        }

        try
        {
            ostr = Ice.Util.createOutputStream(communicator);
            ostr.writeShort((short)0); // Invalid enumerator
            Ice.InputStream istr = Ice.Util.createInputStream(communicator, ostr.finished());
            ShortEnumHelper.read(istr);
            test(false);
        }
        catch(Ice.MarshalException)
        {
        }

        try
        {
            ostr = Ice.Util.createOutputStream(communicator);
            ostr.writeShort((short)32767); // Invalid enumerator
            Ice.InputStream istr = Ice.Util.createInputStream(communicator, ostr.finished());
            ShortEnumHelper.read(istr);
            test(false);
        }
        catch(Ice.MarshalException)
        {
        }

        try
        {
            ostr = Ice.Util.createOutputStream(communicator);
            ostr.writeInt(-1); // Negative enumerators are not supported
            Ice.InputStream istr = Ice.Util.createInputStream(communicator, ostr.finished());
            IntEnumHelper.read(istr);
            test(false);
        }
        catch(Ice.MarshalException)
        {
        }

        Console.Out.WriteLine("ok");
#if SILVERLIGHT
        proxy.shutdown();
#else
        return proxy;
#endif
    }
}
