// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

module MetadataTest
{
    sequence<int> IntSeq;
    ["java:type:java.util.LinkedList<Integer>"] sequence<int> IntList;
    ["java:type:java.util.LinkedList<int[]>"] sequence<IntSeq> IntSeqList;

    sequence<Object> ObjectSeq;
    ["java:type:java.util.LinkedList<Ice.Object>"] sequence<Object> ObjectList;
    ["java:type:java.util.LinkedList<Ice.Object[]>"] sequence<ObjectSeq> ObjectSeqList;

    dictionary<string, string> StringDict;
    ["java:type:java.util.TreeMap<String, String>"] dictionary<string, string> StringMap;

    dictionary<string, Object> ObjectDict;
    ["java:type:java.util.TreeMap<String, Ice.Object>"] dictionary<string, Object> ObjectMap;

    sequence<StringDict> StringDictSeq;
    sequence<string> StringSeq;
    ["java:type:java.util.ArrayList<String>"] sequence<string> StringList;
    sequence<StringList> StringListSeq;
    sequence<StringListSeq> StringListSeqSeq;

    dictionary<string, StringSeq> StringSeqDict;
    dictionary<string, StringList> StringListDict;
    dictionary<string, StringListSeq> StringListSeqDict;

    ["java:getset"] class C
    {
        IntSeq intSeqMember;
        IntList intListMember;
        ["java:type:java.util.ArrayList<Integer>"] IntSeq modifiedIntSeqMember;
        ["java:type:Test.CustomList<Integer>"] IntList modifiedIntListMember;

        ObjectSeq objectSeqMember;
        ObjectList objectListMember;
        ["java:type:java.util.ArrayList<Ice.Object>"] ObjectSeq modifiedObjectSeqMember;
        ["java:type:Test.CustomList<Ice.Object>"] ObjectList modifiedObjectListMember;

        StringDict stringDictMember;
        StringMap stringMapMember;
        ["java:type:java.util.TreeMap<String, String>"] StringDict modifiedStringDictMember;
        ["java:type:java.util.IdentityHashMap<String, String>"] StringMap modifiedStringMapMember;

        ObjectDict objectDictMember;
        ObjectMap objectMapMember;
        ["java:type:java.util.TreeMap<String, Ice.Object>"] ObjectDict modifiedObjectDictMember;
        ["java:type:java.util.IdentityHashMap<String, Ice.Object>"] ObjectMap modifiedObjectMapMember;

        IntSeq opIntSeq(IntSeq inArg, out IntSeq outArg);
        IntList opIntList(IntList inArg, out IntList outArg);

        ObjectSeq opObjectSeq(ObjectSeq inArg, out ObjectSeq outArg);
        ObjectList opObjectList(ObjectList inArg, out ObjectList outArg);

        StringDict opStringDict(StringDict inArg, out StringDict outArg);
        StringMap opStringMap(StringMap inArg, out StringMap outArg);

        ["ami"] IntSeq opIntSeqAMI(IntSeq inArg, out IntSeq outArg);
        ["ami"] IntList opIntListAMI(IntList inArg, out IntList outArg);

        ["ami"] ObjectSeq opObjectSeqAMI(ObjectSeq inArg, out ObjectSeq outArg);
        ["ami"] ObjectList opObjectListAMI(ObjectList inArg, out ObjectList outArg);

        ["ami"] StringDict opStringDictAMI(StringDict inArg, out StringDict outArg);
        ["ami"] StringMap opStringMapAMI(StringMap inArg, out StringMap outArg);

        ["amd"] IntSeq opIntSeqAMD(IntSeq inArg, out IntSeq outArg);
        ["amd"] IntList opIntListAMD(IntList inArg, out IntList outArg);

        ["amd"] ObjectSeq opObjectSeqAMD(ObjectSeq inArg, out ObjectSeq outArg);
        ["amd"] ObjectList opObjectListAMD(ObjectList inArg, out ObjectList outArg);

        ["amd"] StringDict opStringDictAMD(StringDict inArg, out StringDict outArg);
        ["amd"] StringMap opStringMapAMD(StringMap inArg, out StringMap outArg);

        ["java:type:java.util.LinkedList<Integer>"] IntSeq
        opIntSeq2(["java:type:java.util.ArrayList<Integer>"] IntSeq inArg,
                  out ["java:type:Test.CustomList<Integer>"] IntSeq outArg);

        ["java:type:java.util.ArrayList<Integer>"] IntList
        opIntList2(["java:type:java.util.ArrayList<Integer>"] IntList inArg,
                   out ["java:type:Test.CustomList<Integer>"] IntList outArg);

        ["java:type:java.util.LinkedList<Ice.Object>"] ObjectSeq
        opObjectSeq2(["java:type:java.util.ArrayList<Ice.Object>"] ObjectSeq inArg,
                     out ["java:type:Test.CustomList<Ice.Object>"] ObjectSeq outArg);

        ["java:type:java.util.ArrayList<Ice.Object>"] ObjectList
        opObjectList2(["java:type:java.util.ArrayList<Ice.Object>"] ObjectList inArg,
                      out ["java:type:Test.CustomList<Ice.Object>"] ObjectList outArg);

        ["java:type:java.util.IdentityHashMap<String, String>"] StringMap
        opStringMap2(["java:type:java.util.IdentityHashMap<String, String>"] StringMap inArg,
                     out ["java:type:java.util.IdentityHashMap<String, String>"] StringMap outArg);

        ["ami", "java:type:java.util.LinkedList<Integer>"] IntSeq
        opIntSeq2AMI(["java:type:java.util.ArrayList<Integer>"] IntSeq inArg,
                     out ["java:type:Test.CustomList<Integer>"] IntSeq outArg);

        ["ami", "java:type:java.util.ArrayList<Integer>"] IntList
        opIntList2AMI(["java:type:java.util.ArrayList<Integer>"] IntList inArg,
                      out ["java:type:Test.CustomList<Integer>"] IntList outArg);

        ["ami", "java:type:java.util.LinkedList<Ice.Object>"] ObjectSeq
        opObjectSeq2AMI(["java:type:java.util.ArrayList<Ice.Object>"] ObjectSeq inArg,
                        out ["java:type:Test.CustomList<Ice.Object>"] ObjectSeq outArg);

        ["ami", "java:type:java.util.ArrayList<Ice.Object>"] ObjectList
        opObjectList2AMI(["java:type:java.util.ArrayList<Ice.Object>"] ObjectList inArg,
                         out ["java:type:Test.CustomList<Ice.Object>"] ObjectList outArg);

        ["amd", "java:type:java.util.LinkedList<Integer>"] IntSeq
        opIntSeq2AMD(["java:type:java.util.ArrayList<Integer>"] IntSeq inArg,
                     out ["java:type:Test.CustomList<Integer>"] IntSeq outArg);

        ["amd", "java:type:java.util.ArrayList<Integer>"] IntList
        opIntList2AMD(["java:type:java.util.ArrayList<Integer>"] IntList inArg,
                      out ["java:type:Test.CustomList<Integer>"] IntList outArg);

        ["amd", "java:type:java.util.LinkedList<Ice.Object>"] ObjectSeq
        opObjectSeq2AMD(["java:type:java.util.ArrayList<Ice.Object>"] ObjectSeq inArg,
                     out ["java:type:Test.CustomList<Ice.Object>"] ObjectSeq outArg);

        ["amd", "java:type:java.util.ArrayList<Ice.Object>"] ObjectList
        opObjectList2AMD(["java:type:java.util.ArrayList<Ice.Object>"] ObjectList inArg,
                      out ["java:type:Test.CustomList<Ice.Object>"] ObjectList outArg);
    };

    ["protected", "java:getset"] class C2
    {
        IntSeq intSeqMember;
        ["java:type:java.util.ArrayList<Integer>"] IntSeq modifiedIntSeqMember;
    };

    class C3
    {
        ["protected"] IntSeq intSeqMember;
        ["protected", "java:type:java.util.ArrayList<Integer>"] IntSeq modifiedIntSeqMember;
    };
};
