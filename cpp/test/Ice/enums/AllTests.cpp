// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Ice/Stream.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;
using namespace Test;

TestIntfPrx
allTests(const Ice::CommunicatorPtr& communicator)
{
    string ref = "test:default -p 12010";
    Ice::ObjectPrx obj = communicator->stringToProxy(ref);
    test(obj);
    TestIntfPrx proxy = TestIntfPrx::checkedCast(obj);
    test(proxy);

    cout << "testing enum values... " << flush;

    test(static_cast<int>(benum1) == 0);
    test(static_cast<int>(benum2) == 1);
    test(static_cast<int>(benum3) == ByteConst1);
    test(static_cast<int>(benum4) == ByteConst1 + 1);
    test(static_cast<int>(benum5) == ShortConst1);
    test(static_cast<int>(benum6) == ShortConst1 + 1);
    test(static_cast<int>(benum7) == IntConst1);
    test(static_cast<int>(benum8) == IntConst1 + 1);
    test(static_cast<int>(benum9) == LongConst1);
    test(static_cast<int>(benum10) == LongConst1 + 1);
    test(static_cast<int>(benum11) == ByteConst2);

    test(static_cast<int>(senum1) == 3);
    test(static_cast<int>(senum2) == 4);
    test(static_cast<int>(senum3) == ByteConst1);
    test(static_cast<int>(senum4) == ByteConst1 + 1);
    test(static_cast<int>(senum5) == ShortConst1);
    test(static_cast<int>(senum6) == ShortConst1 + 1);
    test(static_cast<int>(senum7) == IntConst1);
    test(static_cast<int>(senum8) == IntConst1 + 1);
    test(static_cast<int>(senum9) == LongConst1);
    test(static_cast<int>(senum10) == LongConst1 + 1);
    test(static_cast<int>(senum11) == ShortConst2);

    test(static_cast<int>(ienum1) == 0);
    test(static_cast<int>(ienum2) == 1);
    test(static_cast<int>(ienum3) == ByteConst1);
    test(static_cast<int>(ienum4) == ByteConst1 + 1);
    test(static_cast<int>(ienum5) == ShortConst1);
    test(static_cast<int>(ienum6) == ShortConst1 + 1);
    test(static_cast<int>(ienum7) == IntConst1);
    test(static_cast<int>(ienum8) == IntConst1 + 1);
    test(static_cast<int>(ienum9) == LongConst1);
    test(static_cast<int>(ienum10) == LongConst1 + 1);
    test(static_cast<int>(ienum11) == IntConst2);
    test(static_cast<int>(ienum12) == LongConst2);

    test(static_cast<int>(red) == 0);
    test(static_cast<int>(green) == 1);
    test(static_cast<int>(blue) == 2);

    cout << "ok" << endl;

    cout << "testing enum streaming... " << flush;

    Ice::OutputStreamPtr out;
    Ice::ByteSeq bytes;

    const bool encoding_1_0 = communicator->getProperties()->getProperty("Ice.Default.EncodingVersion") == "1.0";

    out = Ice::createOutputStream(communicator);
    out->write(benum11);
    out->finished(bytes);
    test(bytes.size() == 1); // ByteEnum should require one byte

    out = Ice::createOutputStream(communicator);
    out->write(senum11);
    out->finished(bytes);
    test(bytes.size() == (encoding_1_0 ? 2 : 5));

    out = Ice::createOutputStream(communicator);
    out->write(ienum11);
    out->finished(bytes);
    test(bytes.size() == (encoding_1_0 ? 4 : 5));

    out = Ice::createOutputStream(communicator);
    out->write(blue);
    out->finished(bytes);
    test(bytes.size() == 1); // SimpleEnum should require one byte

    cout << "ok" << endl;

    cout << "testing enum operations... " << flush;

    ByteEnum byteEnum;
    test(proxy->opByte(benum1, byteEnum) == benum1);
    test(byteEnum == benum1);
    test(proxy->opByte(benum11, byteEnum) == benum11);
    test(byteEnum == benum11);

    ShortEnum shortEnum;
    test(proxy->opShort(senum1, shortEnum) == senum1);
    test(shortEnum == senum1);
    test(proxy->opShort(senum11, shortEnum) == senum11);
    test(shortEnum == senum11);

    IntEnum intEnum;
    test(proxy->opInt(ienum1, intEnum) == ienum1);
    test(intEnum == ienum1);
    test(proxy->opInt(ienum11, intEnum) == ienum11);
    test(intEnum == ienum11);
    test(proxy->opInt(ienum12, intEnum) == ienum12);
    test(intEnum == ienum12);

    SimpleEnum s;
    test(proxy->opSimple(green, s) == green);
    test(s == green);

    cout << "ok" << endl;

    cout << "testing enum exceptions... " << flush;

    try
    {
        proxy->opByte(static_cast<ByteEnum>(-1), byteEnum); // Negative enumerators are not supported
        test(false);
    }
    catch(const Ice::MarshalException&)
    {
    }

    try
    {
        proxy->opByte(static_cast<ByteEnum>(127), byteEnum); // Invalid enumerator
        test(false);
    }
    catch(const Ice::MarshalException&)
    {
    }

    try
    {
        proxy->opShort(static_cast<ShortEnum>(-1), shortEnum); // Negative enumerators are not supported
        test(false);
    }
    catch(const Ice::MarshalException&)
    {
    }

    try
    {
        proxy->opShort(static_cast<ShortEnum>(0), shortEnum); // Invalid enumerator
        test(false);
    }
    catch(const Ice::MarshalException&)
    {
    }

    try
    {
        proxy->opShort(static_cast<ShortEnum>(32767), shortEnum); // Invalid enumerator
        test(false);
    }
    catch(const Ice::MarshalException&)
    {
    }

    try
    {
        proxy->opInt(static_cast<IntEnum>(-1), intEnum); // Negative enumerators are not supported
        test(false);
    }
    catch(const Ice::MarshalException&)
    {
    }

    cout << "ok" << endl;

    return proxy;
}
