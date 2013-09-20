// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.defaultValue;

import java.io.PrintWriter;
import test.Ice.defaultValue.Test.*;

public class AllTests
{
    private static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    public static void
    allTests(test.Util.Application app, PrintWriter out)
    {
        out.print("testing default values... ");
        out.flush();

        {
            Struct1 v = new Struct1();
            test(!v.boolFalse);
            test(v.boolTrue);
            test(v.b == (byte)254);
            test(v.s == 16000);
            test(v.i == 3);
            test(v.l == 4);
            test(v.f == 5.1F);
            test(v.d == 6.2);
            test(v.str == "foo \\ \"bar\n \r\n\t\u000b\f\u0007\b? \u0007 \u0007");
            test(v.c1 == Color.red);
            test(v.c2 == Color.green);
            test(v.c3 == Color.blue);
            test(v.nc1 == test.Ice.defaultValue.Test.Nested.Color.red);
            test(v.nc2 == test.Ice.defaultValue.Test.Nested.Color.green);
            test(v.nc3 == test.Ice.defaultValue.Test.Nested.Color.blue);
            test(v.noDefault == null);
            test(v.zeroI == 0);
            test(v.zeroL == 0);
            test(v.zeroF == 0);
            test(v.zeroDotF == 0);
            test(v.zeroD == 0);
            test(v.zeroDotD == 0);
        }

        {
            Struct2 v = new Struct2();
            test(v.boolTrue == ConstBool.value);
            test(v.b == ConstByte.value);
            test(v.s == ConstShort.value);
            test(v.i == ConstInt.value);
            test(v.l == ConstLong.value);
            test(v.f == ConstFloat.value);
            test(v.d == ConstDouble.value);
            test(v.str.equals(ConstString.value));
            test(v.c1 == ConstColor1.value);
            test(v.c2 == ConstColor2.value);
            test(v.c3 == ConstColor3.value);
            test(v.nc1 == ConstNestedColor1.value);
            test(v.nc2 == ConstNestedColor2.value);
            test(v.nc3 == ConstNestedColor3.value);
        }

        {
            Base v = new Base();
            test(!v.boolFalse);
            test(v.boolTrue);
            test(v.b == 1);
            test(v.s == 2);
            test(v.i == 3);
            test(v.l == 4);
            test(v.f == 5.1F);
            test(v.d == 6.2);
            test(v.str.equals("foo \\ \"bar\n \r\n\t\u000b\f\u0007\b? \007 \u0007"));
            test(v.noDefault == null);
            test(v.zeroI == 0);
            test(v.zeroL == 0);
            test(v.zeroF == 0);
            test(v.zeroDotF == 0);
            test(v.zeroD == 0);
            test(v.zeroDotD == 0);
        }

        {
            Derived v = new Derived();
            test(!v.boolFalse);
            test(v.boolTrue);
            test(v.b == 1);
            test(v.s == 2);
            test(v.i == 3);
            test(v.l == 4);
            test(v.f == 5.1F);
            test(v.d == 6.2);
            test(v.str.equals("foo \\ \"bar\n \r\n\t\u000b\f\u0007\b? \007 \u0007"));
            test(v.c1 == Color.red);
            test(v.c2 == Color.green);
            test(v.c3 == Color.blue);
            test(v.nc1 == test.Ice.defaultValue.Test.Nested.Color.red);
            test(v.nc2 == test.Ice.defaultValue.Test.Nested.Color.green);
            test(v.nc3 == test.Ice.defaultValue.Test.Nested.Color.blue);
            test(v.noDefault == null);
            test(v.zeroI == 0);
            test(v.zeroL == 0);
            test(v.zeroF == 0);
            test(v.zeroDotF == 0);
            test(v.zeroD == 0);
            test(v.zeroDotD == 0);
        }

        {
            BaseEx v = new BaseEx();
            test(!v.boolFalse);
            test(v.boolTrue);
            test(v.b == 1);
            test(v.s == 2);
            test(v.i == 3);
            test(v.l == 4);
            test(v.f == 5.1F);
            test(v.d == 6.2);
            test(v.str == "foo \\ \"bar\n \r\n\t\u000b\f\u0007\b? \007 \u0007");
            test(v.noDefault == null);
            test(v.zeroI == 0);
            test(v.zeroL == 0);
            test(v.zeroF == 0);
            test(v.zeroDotF == 0);
            test(v.zeroD == 0);
            test(v.zeroDotD == 0);
        }

        {
            DerivedEx v = new DerivedEx();
            test(!v.boolFalse);
            test(v.boolTrue);
            test(v.b == 1);
            test(v.s == 2);
            test(v.i == 3);
            test(v.l == 4);
            test(v.f == 5.1F);
            test(v.d == 6.2);
            test(v.str == "foo \\ \"bar\n \r\n\t\u000b\f\u0007\b? \007 \u0007");
            test(v.noDefault == null);
            test(v.c1 == Color.red);
            test(v.c2 == Color.green);
            test(v.c3 == Color.blue);
            test(v.nc1 == test.Ice.defaultValue.Test.Nested.Color.red);
            test(v.nc2 == test.Ice.defaultValue.Test.Nested.Color.green);
            test(v.nc3 == test.Ice.defaultValue.Test.Nested.Color.blue);
            test(v.zeroI == 0);
            test(v.zeroL == 0);
            test(v.zeroF == 0);
            test(v.zeroDotF == 0);
            test(v.zeroD == 0);
            test(v.zeroDotD == 0);
        }

        out.println("ok");
    }
}
