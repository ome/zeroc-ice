// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceUtil/Iterator.h>
#include <TestCommon.h>
#include <Test.h>
#include <Wstring.h>

#ifdef _MSC_VER
#   pragma warning( 4 : 4503 ) // C4503: ... : decorated name length exceeded, name was truncated
#endif

using namespace std;

namespace
{

template<typename T> bool
arrayRangeEquals(pair<const T*, const T*> lhs, pair<const T*, const T*> rhs)
{
    if(lhs.second - lhs.first != rhs.second - rhs.first)
    {
        return false;
    }

    T* l = const_cast<T*>(lhs.first);
    T* r = const_cast<T*>(rhs.first);
    while(l != lhs.second)
    {
        if(*l++ != *r++)
        {
            return false;
        }
    }
    return true;
}


}

class CallbackBase : public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    CallbackBase() :
        _called(false)
    {
    }

    virtual ~CallbackBase()
    {
    }

    void check()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
        while(!_called)
        {
            wait();
        }
        _called = false;
    }

protected:

    void called()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
        assert(!_called);
        _called = true;
        notify();
    }

private:

    bool _called;
};

class AMI_TestIntf_opDoubleArrayI : public Test::AMI_TestIntf_opDoubleArray, public CallbackBase
{
public:

    AMI_TestIntf_opDoubleArrayI(const ::std::pair<const double*, const double*>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const ::std::pair<const double*, const double*>& ret,
                              const ::std::pair<const double*, const double*>& out)
    {
        test(arrayRangeEquals<double>(out, _in));
        test(arrayRangeEquals<double>(ret, _in));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    const ::std::pair<const double*, const double*> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opDoubleArrayI> AMI_TestIntf_opDoubleArrayIPtr;

class AMI_TestIntf_opBoolArrayI : public Test::AMI_TestIntf_opBoolArray, public CallbackBase
{
public:

    AMI_TestIntf_opBoolArrayI(const ::std::pair<const bool*, const bool*>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const ::std::pair<const bool*, const bool*>& ret,
                              const ::std::pair<const bool*, const bool*>& out)
    {
        test(arrayRangeEquals<bool>(out, _in));
        test(arrayRangeEquals<bool>(ret, _in));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    const ::std::pair<const bool*, const bool*> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opBoolArrayI> AMI_TestIntf_opBoolArrayIPtr;

class AMI_TestIntf_opByteArrayI : public Test::AMI_TestIntf_opByteArray, public CallbackBase
{
public:

    AMI_TestIntf_opByteArrayI(const pair<const Ice::Byte*, const Ice::Byte*>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<const Ice::Byte*, const Ice::Byte*>& ret,
                              const pair<const Ice::Byte*, const Ice::Byte*>& out)
    {
        test(arrayRangeEquals<Ice::Byte>(out, _in));
        test(arrayRangeEquals<Ice::Byte>(ret, _in));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<const Ice::Byte*, const Ice::Byte*> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opByteArrayI> AMI_TestIntf_opByteArrayIPtr;

class AMI_TestIntf_opVariableArrayI : public Test::AMI_TestIntf_opVariableArray, public CallbackBase
{
public:

    AMI_TestIntf_opVariableArrayI(pair<const Test::Variable*, const Test::Variable*> in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<const Test::Variable*, const Test::Variable*>& ret,
                              const pair<const Test::Variable*, const Test::Variable*>& out)
    {
        test(arrayRangeEquals<Test::Variable>(out, _in));
        test(arrayRangeEquals<Test::Variable>(ret, _in));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<const Test::Variable*, const Test::Variable*> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opVariableArrayI> AMI_TestIntf_opVariableArrayIPtr;

class AMI_TestIntf_opBoolRangeI : public Test::AMI_TestIntf_opBoolRange, public CallbackBase
{
public:

    AMI_TestIntf_opBoolRangeI(pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& ret,
                              const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& out)
    {
        test(equal(out.first, out.second, _in.first));
        test(equal(ret.first, ret.second, _in.first));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opBoolRangeI> AMI_TestIntf_opBoolRangeIPtr;

class AMI_TestIntf_opByteRangeI : public Test::AMI_TestIntf_opByteRange, public CallbackBase
{
public:

    AMI_TestIntf_opByteRangeI(const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& ret,
                              const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& out)
    {
        test(equal(out.first, out.second, _in.first));
        test(equal(ret.first, ret.second, _in.first));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opByteRangeI> AMI_TestIntf_opByteRangeIPtr;

class AMI_TestIntf_opVariableRangeI : public Test::AMI_TestIntf_opVariableRange, public CallbackBase
{
public:

    AMI_TestIntf_opVariableRangeI(const pair<Test::VariableList::const_iterator, 
                                  Test::VariableList::const_iterator>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& ret,
                              const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& out)
    {
        test(equal(out.first, out.second, _in.first));
        test(equal(ret.first, ret.second, _in.first));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opVariableRangeI> AMI_TestIntf_opVariableRangeIPtr;

class AMI_TestIntf_opBoolRangeTypeI : public Test::AMI_TestIntf_opBoolRangeType, public CallbackBase
{
public:

    AMI_TestIntf_opBoolRangeTypeI(const pair<const bool*, const bool*>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<const bool*, const bool*>& ret,
                              const pair<const bool*, const bool*>& out)
    {
        test(arrayRangeEquals<bool>(out, _in));
        test(arrayRangeEquals<bool>(ret, _in));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<const bool*, const bool*> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opBoolRangeTypeI> AMI_TestIntf_opBoolRangeTypeIPtr;

class AMI_TestIntf_opByteRangeTypeI : public Test::AMI_TestIntf_opByteRangeType, public CallbackBase
{
public:

    AMI_TestIntf_opByteRangeTypeI(const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& ret,
                              const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& out)
    {
        test(equal(out.first, out.second, _in.first));
        test(equal(ret.first, ret.second, _in.first));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opByteRangeTypeI> AMI_TestIntf_opByteRangeTypeIPtr;

class AMI_TestIntf_opVariableRangeTypeI : public Test::AMI_TestIntf_opVariableRangeType, public CallbackBase
{
public:

    AMI_TestIntf_opVariableRangeTypeI(const pair<deque<Test::Variable>::const_iterator, 
                                      deque<Test::Variable>::const_iterator>& in)
        : _in(in)
    {
    }

    virtual void ice_response(const pair<deque<Test::Variable>::const_iterator, 
                              deque<Test::Variable>::const_iterator>& ret, 
                              const pair<deque<Test::Variable>::const_iterator, 
                              deque<Test::Variable>::const_iterator>& out)
    {
        test(equal(out.first, out.second, _in.first));
        test(equal(ret.first, ret.second, _in.first));
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opVariableRangeTypeI> AMI_TestIntf_opVariableRangeTypeIPtr;

class AMI_TestIntf_opBoolSeqI : public Test::AMI_TestIntf_opBoolSeq, public CallbackBase
{
public:

    AMI_TestIntf_opBoolSeqI(deque<bool> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<bool>& ret, const deque<bool>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<bool> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opBoolSeqI> AMI_TestIntf_opBoolSeqIPtr;

class AMI_TestIntf_opBoolListI : public Test::AMI_TestIntf_opBoolList, public CallbackBase
{
public:

    AMI_TestIntf_opBoolListI(list<bool> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<bool>& ret, const list<bool>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<bool> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opBoolListI> AMI_TestIntf_opBoolListIPtr;

class AMI_TestIntf_opByteSeqI : public Test::AMI_TestIntf_opByteSeq, public CallbackBase
{
public:

    AMI_TestIntf_opByteSeqI(deque<Ice::Byte> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Ice::Byte>& ret, const deque<Ice::Byte>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Ice::Byte> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opByteSeqI> AMI_TestIntf_opByteSeqIPtr;

class AMI_TestIntf_opByteListI : public Test::AMI_TestIntf_opByteList, public CallbackBase
{
public:

    AMI_TestIntf_opByteListI(list<Ice::Byte> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Ice::Byte>& ret, const list<Ice::Byte>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Ice::Byte> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opByteListI> AMI_TestIntf_opByteListIPtr;

class AMI_TestIntf_opMyByteSeqI : public Test::AMI_TestIntf_opMyByteSeq, public CallbackBase
{
public:

    AMI_TestIntf_opMyByteSeqI(MyByteSeq in)
        : _in(in)
    {
    }

    virtual void ice_response(const MyByteSeq& ret, const MyByteSeq& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    MyByteSeq _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opMyByteSeqI> AMI_TestIntf_opMyByteSeqIPtr;

class AMI_TestIntf_opStringSeqI : public Test::AMI_TestIntf_opStringSeq, public CallbackBase
{
public:

    AMI_TestIntf_opStringSeqI(deque<string> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<string>& ret, const deque<string>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<string> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opStringSeqI> AMI_TestIntf_opStringSeqIPtr;

class AMI_TestIntf_opStringListI : public Test::AMI_TestIntf_opStringList, public CallbackBase
{
public:

    AMI_TestIntf_opStringListI(list<string> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<string>& ret, const list<string>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<string> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opStringListI> AMI_TestIntf_opStringListIPtr;

class AMI_TestIntf_opFixedSeqI : public Test::AMI_TestIntf_opFixedSeq, public CallbackBase
{
public:

    AMI_TestIntf_opFixedSeqI(deque<Test::Fixed> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Test::Fixed>& ret, const deque<Test::Fixed>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Test::Fixed> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opFixedSeqI> AMI_TestIntf_opFixedSeqIPtr;

class AMI_TestIntf_opFixedListI : public Test::AMI_TestIntf_opFixedList, public CallbackBase
{
public:

    AMI_TestIntf_opFixedListI(list<Test::Fixed> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Test::Fixed>& ret, const list<Test::Fixed>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Test::Fixed> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opFixedListI> AMI_TestIntf_opFixedListIPtr;

class AMI_TestIntf_opVariableSeqI : public Test::AMI_TestIntf_opVariableSeq, public CallbackBase
{
public:

    AMI_TestIntf_opVariableSeqI(deque<Test::Variable> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Test::Variable>& ret, const deque<Test::Variable>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Test::Variable> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opVariableSeqI> AMI_TestIntf_opVariableSeqIPtr;

class AMI_TestIntf_opVariableListI : public Test::AMI_TestIntf_opVariableList, public CallbackBase
{
public:

    AMI_TestIntf_opVariableListI(list<Test::Variable> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Test::Variable>& ret, const list<Test::Variable>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Test::Variable> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opVariableListI> AMI_TestIntf_opVariableListIPtr;

class AMI_TestIntf_opStringStringDictSeqI : public Test::AMI_TestIntf_opStringStringDictSeq, public CallbackBase
{
public:

    AMI_TestIntf_opStringStringDictSeqI(deque<Test::StringStringDict> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Test::StringStringDict>& ret, const deque<Test::StringStringDict>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Test::StringStringDict> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opStringStringDictSeqI> AMI_TestIntf_opStringStringDictSeqIPtr;

class AMI_TestIntf_opStringStringDictListI : public Test::AMI_TestIntf_opStringStringDictList, public CallbackBase
{
public:

    AMI_TestIntf_opStringStringDictListI(list<Test::StringStringDict> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Test::StringStringDict>& ret, const list<Test::StringStringDict>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Test::StringStringDict> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opStringStringDictListI> AMI_TestIntf_opStringStringDictListIPtr;

class AMI_TestIntf_opESeqI : public Test::AMI_TestIntf_opESeq, public CallbackBase
{
public:

    AMI_TestIntf_opESeqI(deque<Test::E> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Test::E>& ret, const deque<Test::E>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Test::E> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opESeqI> AMI_TestIntf_opESeqIPtr;

class AMI_TestIntf_opEListI : public Test::AMI_TestIntf_opEList, public CallbackBase
{
public:

    AMI_TestIntf_opEListI(list<Test::E> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Test::E>& ret, const list<Test::E>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Test::E> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opEListI> AMI_TestIntf_opEListIPtr;

class AMI_TestIntf_opCPrxSeqI : public Test::AMI_TestIntf_opCPrxSeq, public CallbackBase
{
public:

    AMI_TestIntf_opCPrxSeqI(deque<Test::CPrx> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Test::CPrx>& ret, const deque<Test::CPrx>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Test::CPrx> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opCPrxSeqI> AMI_TestIntf_opCPrxSeqIPtr;

class AMI_TestIntf_opCPrxListI : public Test::AMI_TestIntf_opCPrxList, public CallbackBase
{
public:

    AMI_TestIntf_opCPrxListI(list<Test::CPrx> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Test::CPrx>& ret, const list<Test::CPrx>& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Test::CPrx> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opCPrxListI> AMI_TestIntf_opCPrxListIPtr;

class AMI_TestIntf_opCSeqI : public Test::AMI_TestIntf_opCSeq, public CallbackBase
{
public:

    AMI_TestIntf_opCSeqI(deque<Test::CPtr> in)
        : _in(in)
    {
    }

    virtual void ice_response(const deque<Test::CPtr>& ret, const deque<Test::CPtr>& out)
    {
        test(out.size() == _in.size());
        test(ret.size() == _in.size());
        for(unsigned int i = 1; i < _in.size(); ++i)
        {
            test(out[i] == out[0]);
            test(ret[i] == out[i]);
        }
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    deque<Test::CPtr> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opCSeqI> AMI_TestIntf_opCSeqIPtr;

class AMI_TestIntf_opCListI : public Test::AMI_TestIntf_opCList, public CallbackBase
{
public:

    AMI_TestIntf_opCListI(list<Test::CPtr> in)
        : _in(in)
    {
    }

    virtual void ice_response(const list<Test::CPtr>& ret, const list<Test::CPtr>& out)
    {
        test(out.size() == _in.size());
        test(ret.size() == _in.size());
        list<Test::CPtr>::const_iterator p1;
        list<Test::CPtr>::const_iterator p2;
        for(p1 = out.begin(), p2 = ret.begin(); p1 != out.end(); ++p1, ++p2)
        {
            test(*p1 == *p2);
        }
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    list<Test::CPtr> _in;
};

typedef IceUtil::Handle<AMI_TestIntf_opCListI> AMI_TestIntf_opCListIPtr;

class AMI_TestIntf_opClassStructI : public Test::AMI_TestIntf_opClassStruct, public CallbackBase
{
public:

    AMI_TestIntf_opClassStructI(const Test::ClassStructPtr& cs, const Test::ClassStructSeq& csseq1) :
        _cs(cs), _csseq1(csseq1)
    {
    }

    virtual void ice_response(const ::Test::ClassStructPtr& ret,
                              const ::Test::ClassStructPtr& cs1,
                              const ::Test::ClassStructSeq& seq)
    {
        test(ret == _cs);
        test(cs1 == _cs);
        test(seq == _csseq1);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    const Test::ClassStructPtr _cs;
    const Test::ClassStructSeq _csseq1;
};
typedef IceUtil::Handle<AMI_TestIntf_opClassStructI> AMI_TestIntf_opClassStructIPtr;

class AMI_Test1_opStringI : public Test1::AMI_WstringClass_opString, public CallbackBase
{
public:

    AMI_Test1_opStringI(wstring in)
        : _in(in)
    {
    }

    virtual void ice_response(const wstring& ret, const wstring& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    wstring _in;
};

typedef IceUtil::Handle<AMI_Test1_opStringI> AMI_Test1_opStringIPtr;

class AMI_Test2_opStringI : public Test2::AMI_WstringClass_opString, public CallbackBase
{
public:

    AMI_Test2_opStringI(wstring in)
        : _in(in)
    {
    }

    virtual void ice_response(const wstring& ret, const wstring& out)
    {
        test(out == _in);
        test(ret == _in);
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }

private:

    wstring _in;
};

typedef IceUtil::Handle<AMI_Test2_opStringI> AMI_Test2_opStringIPtr;

class AMI_Test1_throwExceptI : public Test1::AMI_WstringClass_throwExcept, public CallbackBase
{
public:

    AMI_Test1_throwExceptI(wstring in)
        : _in(in)
    {
    }

    virtual void ice_response()
    {
        test(false);
    }

    virtual void ice_exception(const ::Ice::Exception& ex)
    {
        try
        {
            ex.ice_throw();
        }
        catch(const Test1::WstringException& e)
        {
            test(e.reason == _in);
            called();
        }
        catch(...)
        {
            test(false);
        }
    }

private:

    wstring _in;
};

typedef IceUtil::Handle<AMI_Test1_throwExceptI> AMI_Test1_throwExceptIPtr;

class AMI_Test2_throwExceptI : public Test2::AMI_WstringClass_throwExcept, public CallbackBase
{
public:

    AMI_Test2_throwExceptI(wstring in)
        : _in(in)
    {
    }

    virtual void ice_response()
    {
        test(false);
    }

    virtual void ice_exception(const ::Ice::Exception& ex)
    {
        try
        {
            ex.ice_throw();
        }
        catch(const Test2::WstringException& e)
        {
            test(e.reason == _in);
            called();
        }
        catch(...)
        {
            test(false);
        }
    }

private:

    wstring _in;
};

typedef IceUtil::Handle<AMI_Test2_throwExceptI> AMI_Test2_throwExceptIPtr;

class InParam : public Ice::LocalObject
{
};
typedef IceUtil::Handle<InParam> InParamPtr;

template<class T>
class InParamT : public InParam
{
public:

    InParamT(const T& v) : in(v)
    {
    }

    T in;
};

template<typename T> InParamPtr newInParam(const T& v)
{
    return new InParamT<T>(v);
} 

template<typename T> const T& getIn(const InParamPtr& cookie)
{
    return dynamic_cast<InParamT<T>* >(cookie.get())->in;
} 

class Callback : public CallbackBase, public IceUtil::Shared
{
public:

    void opDoubleArray(const ::std::pair<const double*, const double*>& ret,
                       const ::std::pair<const double*, const double*>& out,
                       const InParamPtr& cookie)
    {
        const ::std::pair<const double*, const double*>& in = getIn<std::pair<const double*, const double*> >(cookie);
        test(arrayRangeEquals<double>(out, in));
        test(arrayRangeEquals<double>(ret, in));
        called();
    }

    void opBoolArray(const ::std::pair<const bool*, const bool*>& ret,
                     const ::std::pair<const bool*, const bool*>& out,
                     const InParamPtr& cookie)
    {
        const ::std::pair<const bool*, const bool*>& in = getIn<std::pair<const bool*, const bool*> >(cookie);
        test(arrayRangeEquals<bool>(out, in));
        test(arrayRangeEquals<bool>(ret, in));
        called();
    }

    void opByteArray(const pair<const Ice::Byte*, const Ice::Byte*>& ret,
                     const pair<const Ice::Byte*, const Ice::Byte*>& out,
                     const InParamPtr& cookie)
    {
        const pair<const Ice::Byte*, const Ice::Byte*>& in = getIn<pair<const Ice::Byte*, const Ice::Byte*> >(cookie);
        test(arrayRangeEquals<Ice::Byte>(out, in));
        test(arrayRangeEquals<Ice::Byte>(ret, in));
        called();
    }
    
    void opVariableArray(const pair<const Test::Variable*, const Test::Variable*>& ret,
                         const pair<const Test::Variable*, const Test::Variable*>& out,
                         const InParamPtr& cookie)
    {
        const pair<const Test::Variable*, const Test::Variable*>& in = 
            getIn<pair<const Test::Variable*, const Test::Variable*> >(cookie);
        test(arrayRangeEquals<Test::Variable>(out, in));
        test(arrayRangeEquals<Test::Variable>(ret, in));
        called();
    }
    
    void opBoolRange(const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& ret,
                     const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& out,
                     const InParamPtr& cookie)
    {
        const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& in 
            = getIn<pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> >(cookie);
        test(equal(out.first, out.second, in.first));
        test(equal(ret.first, ret.second, in.first));
        called();
    }

    void opByteRange(const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& ret,
                     const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& out,
                     const InParamPtr& cookie)
    {
        const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& in = 
            getIn<pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> >(cookie);
        test(equal(out.first, out.second, in.first));
        test(equal(ret.first, ret.second, in.first));
        called();
    }

    void opVariableRange(const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& ret,
                         const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& out,
                         const InParamPtr& cookie)
    {
        const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& in = 
            getIn<pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> >(cookie);
        test(equal(out.first, out.second, in.first));
        test(equal(ret.first, ret.second, in.first));
        called();
    }

    void opBoolRangeType(const pair<const bool*, const bool*>& ret,
                         const pair<const bool*, const bool*>& out,
                         const InParamPtr& cookie)
    {
        const pair<const bool*, const bool*>& in = getIn<pair<const bool*, const bool*> >(cookie);
        test(arrayRangeEquals<bool>(out, in));
        test(arrayRangeEquals<bool>(ret, in));
        called();
    }

    void opByteRangeType(const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& ret,
                         const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& out,
                         const InParamPtr& cookie)
    {
        const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& in = 
            getIn<pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> >(cookie);
        test(equal(out.first, out.second, in.first));
        test(equal(ret.first, ret.second, in.first));
        called();
    }

    void opVariableRangeType(const pair<deque<Test::Variable>::const_iterator, 
                             deque<Test::Variable>::const_iterator>& ret, 
                             const pair<deque<Test::Variable>::const_iterator, 
                             deque<Test::Variable>::const_iterator>& out,
                             const InParamPtr& cookie)
    {
        const pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator>& in = 
            getIn<pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator> >(cookie);

        test(equal(out.first, out.second, in.first));
        test(equal(ret.first, ret.second, in.first));
        called();
    }

    void opBoolSeq(const deque<bool>& ret, const deque<bool>& out, const InParamPtr& cookie)
    {
        const deque<bool>& in = getIn<deque<bool> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opBoolList(const list<bool>& ret, const list<bool>& out, const InParamPtr& cookie)
    {
        const list<bool>& in = getIn<list<bool> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }
    
    void opByteSeq(const deque<Ice::Byte>& ret, const deque<Ice::Byte>& out, const InParamPtr& cookie)
    {
        const deque<Ice::Byte>& in = getIn< deque<Ice::Byte> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opByteList(const list<Ice::Byte>& ret, const list<Ice::Byte>& out, const InParamPtr& cookie)
    {
        const list<Ice::Byte>& in = getIn<list<Ice::Byte> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opMyByteSeq(const MyByteSeq& ret, const MyByteSeq& out, const InParamPtr& cookie)
    {
        const MyByteSeq& in = getIn<MyByteSeq>(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opStringSeq(const deque<string>& ret, const deque<string>& out, const InParamPtr& cookie)
    {
        const deque<string>& in = getIn<deque<string> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }
    
    void opStringList(const list<string>& ret, const list<string>& out, const InParamPtr& cookie)
    {
        const list<string>& in = getIn<list<string> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opFixedSeq(const deque<Test::Fixed>& ret, const deque<Test::Fixed>& out, const InParamPtr& cookie)
    {
        const deque<Test::Fixed>& in = getIn<deque<Test::Fixed> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opFixedList(const list<Test::Fixed>& ret, const list<Test::Fixed>& out, const InParamPtr& cookie)
    {
        const list<Test::Fixed>& in = getIn<list<Test::Fixed> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opVariableSeq(const deque<Test::Variable>& ret, const deque<Test::Variable>& out,
                       const InParamPtr& cookie)
    {
        const deque<Test::Variable>& in = getIn<deque<Test::Variable> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opVariableList(const list<Test::Variable>& ret, const list<Test::Variable>& out, const InParamPtr& cookie)
    {
        const list<Test::Variable>& in = getIn<list<Test::Variable> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opStringStringDictSeq(const deque<Test::StringStringDict>& ret, const deque<Test::StringStringDict>& out,
                               const InParamPtr& cookie)
    {
        const deque<Test::StringStringDict>& in = getIn<deque<Test::StringStringDict> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opStringStringDictList(const list<Test::StringStringDict>& ret, const list<Test::StringStringDict>& out,
                                const InParamPtr& cookie)
    {
        const list<Test::StringStringDict>& in = getIn<list<Test::StringStringDict> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opESeq(const deque<Test::E>& ret, const deque<Test::E>& out, const InParamPtr& cookie)
    {
        const deque<Test::E>& in = getIn<deque<Test::E> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opEList(const list<Test::E>& ret, const list<Test::E>& out, const InParamPtr& cookie)
    {
        const list<Test::E>& in = getIn<list<Test::E> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opCPrxSeq(const deque<Test::CPrx>& ret, const deque<Test::CPrx>& out, const InParamPtr& cookie)
    {
        const deque<Test::CPrx>& in = getIn<deque<Test::CPrx> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opCPrxList(const list<Test::CPrx>& ret, const list<Test::CPrx>& out, const InParamPtr& cookie)
    {
        const list<Test::CPrx>& in = getIn<list<Test::CPrx> >(cookie);
        test(out == in);
        test(ret == in);
        called();
    }

    void opCSeq(const deque<Test::CPtr>& ret, const deque<Test::CPtr>& out, const InParamPtr& cookie)
    {
        const deque<Test::CPtr>& in = getIn<deque<Test::CPtr> >(cookie);
        test(out.size() == in.size());
        test(ret.size() == in.size());
        for(unsigned int i = 1; i < in.size(); ++i)
        {
            test(out[i] == out[0]);
            test(ret[i] == out[i]);
        }
        called();
    }

    void opCList(const list<Test::CPtr>& ret, const list<Test::CPtr>& out, const InParamPtr& cookie)
    {
        const list<Test::CPtr>& in = getIn<list<Test::CPtr> >(cookie);
        test(out.size() == in.size());
        test(ret.size() == in.size());
        list<Test::CPtr>::const_iterator p1;
        list<Test::CPtr>::const_iterator p2;
        for(p1 = out.begin(), p2 = ret.begin(); p1 != out.end(); ++p1, ++p2)
        {
            test(*p1 == *p2);
        }
        called();
    }

    void opClassStruct(const ::Test::ClassStructPtr& ret,
                       const ::Test::ClassStructPtr& cs1,
                       const ::Test::ClassStructSeq& seq,
                       const InParamPtr& cookie)
    {
        pair< ::Test::ClassStructPtr, ::Test::ClassStructSeq> in = 
            getIn<pair< ::Test::ClassStructPtr, ::Test::ClassStructSeq> >(cookie);
        test(ret == in.first);
        test(cs1 == in.first);
        test(seq == in.second);
        called();
    }
    
    void opString(const wstring& ret, const wstring& out, const InParamPtr& cookie)
    {
        const wstring& in = getIn<wstring>(cookie);
        test(out == in);
        test(ret == in);
        called();
    }
    
    void opOutArrayByteSeq(const ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*>& data, const InParamPtr& cookie)
    {
        const Test::ByteSeq& in = getIn<Test::ByteSeq>(cookie);
        Test::ByteSeq out(data.first, data.second);
        Test::ByteSeq::const_iterator p1;
        Test::ByteSeq::const_iterator p2;
                
        for(p1 = out.begin(), p2 = in.begin(); p1 != out.end(); ++p1, ++p2)
        {
            test(*p1 == *p2);
        }
        called();
    }
    
    void opOutRangeByteSeq(const ::std::pair< ::Test::ByteSeq::const_iterator, ::Test::ByteSeq::const_iterator>& data, 
                           const InParamPtr& cookie)
    {
        const Test::ByteSeq& in = getIn<Test::ByteSeq>(cookie);
        Test::ByteSeq out(data.first, data.second);
        Test::ByteSeq::const_iterator p1;
        Test::ByteSeq::const_iterator p2;
                
        for(p1 = out.begin(), p2 = in.begin(); p1 != out.end(); ++p1, ++p2)
        {
            test(*p1 == *p2);
        }
        called();
    }

    void opIntStringDict(const Test::IntStringDict& ret, const Test::IntStringDict& out, const InParamPtr& cookie)
    {
        const Test::IntStringDict& in = getIn<Test::IntStringDict>(cookie);
        
        test(ret == in);
        test(out == in);
        called();
    }

    void opVarDict(const Test::CustomMap<Ice::Long, Ice::Long>& ret, 
                   const Test::CustomMap<std::string, Ice::Int>& out, const InParamPtr& cookie)
    {
        const Test::CustomMap<std::string, Ice::Int>& in = getIn<Test::CustomMap<std::string, Ice::Int> >(cookie);

#if defined(_MSC_VER) && (_MSC_VER == 1600)
        //
        // operator== for std::unordered_map does not work with Visual Studio 2010
        //
        test(out.size() == in.size());
        
        for(Test::CustomMap<std::string, Ice::Int>::const_iterator p = in.begin(); p != in.end(); ++p)
        {
            Test::CustomMap<std::string, Ice::Int>::const_iterator q = out.find(p->first);
            test(q != out.end() && q->second == p->second);
        } 
#else   
        test(out == in);
#endif
        test(ret.size() == 1000);
        for(Test::CustomMap<Ice::Long, Ice::Long>::const_iterator i = ret.begin(); i != ret.end(); ++i)
        {
            test(i->second == i->first * i->first);
        }

        called();
    }


    void throwExcept1(const Ice::AsyncResultPtr& result)
    {
        const wstring& in = getIn<wstring>(InParamPtr::dynamicCast(result->getCookie()));
        try
        {
            Test1::WstringClassPrx t = Test1::WstringClassPrx::uncheckedCast(result->getProxy());
            t->end_throwExcept(result);
        }
        catch(const Test1::WstringException& e)
        {
            test(e.reason == in);
            called();
        }
        catch(...)
        {
            test(false);
        }
    }
    
    void throwExcept1(const Ice::Exception& ex, const wstring& in)
    {
        try
        {
            ex.ice_throw();
        }
        catch(const Test1::WstringException& e)
        {
            test(e.reason == in);
            called();
        }
        catch(...)
        {
            test(false);
        }
    }

    void throwExcept2(const Ice::AsyncResultPtr& result)
    {
        const wstring& in = getIn<wstring>(InParamPtr::dynamicCast(result->getCookie()));
        try
        {
            Test2::WstringClassPrx t = Test2::WstringClassPrx::uncheckedCast(result->getProxy());
            t->end_throwExcept(result);
        }
        catch(const Test2::WstringException& e)
        {
            test(e.reason == in);
            called();
        }
        catch(...)
        {
            test(false);
        }
    }
    
    void throwExcept2(const Ice::Exception& ex, const wstring& in)
    {
        try
        {
            ex.ice_throw();
        }
        catch(const Test2::WstringException& e)
        {
            test(e.reason == in);
            called();
        }
        catch(...)
        {
            test(false);
        }
    }

    void 
    noEx(const Ice::Exception& ex, const InParamPtr&)
    {
        cerr << ex << endl;
        test(false);
    }
};
typedef IceUtil::Handle<Callback> CallbackPtr;

Test::TestIntfPrx
allTests(const Ice::CommunicatorPtr& communicator, bool collocated)
{
    cout << "testing stringToProxy... " << flush;
    string ref = communicator->getProperties()->getPropertyWithDefault(
        "Custom.Proxy", "test:default -p 12010");
    Ice::ObjectPrx base = communicator->stringToProxy(ref);
    test(base);
    cout << "ok" << endl;

    cout << "testing checked cast... " << flush;
    Test::TestIntfPrx t = Test::TestIntfPrx::checkedCast(base);
    test(t);
    test(t == base);
    cout << "ok" << endl;

    cout << "testing alternate sequences... " << flush;

    {
        Test::DoubleSeq in(5);
        in[0] = 3.14;
        in[1] = 1 / 3;
        in[2] = 0.375;
        in[3] = 4 / 3;
        in[4] = -5.725;
        Ice::Double inArray[5];
        for(int i = 0; i < 5; ++i)
        {
            inArray[i] = in[i];
        }
        pair<const Ice::Double*, const Ice::Double*> inPair(inArray, inArray + 5);

        Test::DoubleSeq out;
        Test::DoubleSeq ret = t->opDoubleArray(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::BoolSeq in(5);
        in[0] = false;
        in[1] = true;
        in[2] = true;
        in[3] = false;
        in[4] = true;
        bool inArray[5];
        for(int i = 0; i < 5; ++i)
        {
            inArray[i] = in[i];
        }
        pair<const bool*, const bool*> inPair(inArray, inArray + 5);

        Test::BoolSeq out;
        Test::BoolSeq ret = t->opBoolArray(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::ByteList in;
        Ice::Byte inArray[5];
        inArray[0] = '1';
        in.push_back(inArray[0]);
        inArray[1] = '2';
        in.push_back(inArray[1]);
        inArray[2] = '3';
        in.push_back(inArray[2]);
        inArray[3] = '4';
        in.push_back(inArray[3]);
        inArray[4] = '5';
        in.push_back(inArray[4]);
        pair<const Ice::Byte*, const Ice::Byte*> inPair(inArray, inArray + 5);

        Test::ByteList out;
        Test::ByteList ret = t->opByteArray(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::VariableList in;
        Test::Variable inArray[5];
        inArray[0].s = "These";
        in.push_back(inArray[0]);
        inArray[1].s = "are";
        in.push_back(inArray[1]);
        inArray[2].s = "five";
        in.push_back(inArray[2]);
        inArray[3].s = "short";
        in.push_back(inArray[3]);
        inArray[4].s = "strings.";
        in.push_back(inArray[4]);
        pair<const Test::Variable*, const Test::Variable*> inPair(inArray, inArray + 5);

        Test::VariableList out;
        Test::VariableList ret = t->opVariableArray(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::BoolSeq in(5);
        in[0] = false;
        in[1] = true;
        in[2] = true;
        in[3] = false;
        in[4] = true;
        pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> inPair(in.begin(), in.end());

        Test::BoolSeq out;
        Test::BoolSeq ret = t->opBoolRange(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::ByteList in;
        in.push_back('1');
        in.push_back('2');
        in.push_back('3');
        in.push_back('4');
        in.push_back('5');
        pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

        Test::ByteList out;
        Test::ByteList ret = t->opByteRange(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::VariableList in;
        Test::Variable v;
        v.s = "These";
        in.push_back(v);
        v.s = "are";
        in.push_back(v);
        v.s = "five";
        in.push_back(v);
        v.s = "short";
        in.push_back(v);
        v.s = "strings.";
        in.push_back(v);
        pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> inPair(in.begin(), in.end());

        Test::VariableList out;
        Test::VariableList ret = t->opVariableRange(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::BoolSeq in(5);
        in[0] = false;
        in[1] = true;
        in[2] = true;
        in[3] = false;
        in[4] = true;
        bool inArray[5];
        for(int i = 0; i < 5; ++i)
        {
            inArray[i] = in[i];
        }
        pair<const bool*, const bool*> inPair(inArray, inArray + 5);

        Test::BoolSeq out;
        Test::BoolSeq ret = t->opBoolRangeType(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::ByteList in;
        in.push_back('1');
        in.push_back('2');
        in.push_back('3');
        in.push_back('4');
        in.push_back('5');
        pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

        Test::ByteList out;
        Test::ByteList ret = t->opByteRangeType(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        Test::VariableList in;
        deque<Test::Variable> inSeq;
        Test::Variable v;
        v.s = "These";
        in.push_back(v);
        inSeq.push_back(v);
        v.s = "are";
        in.push_back(v);
        inSeq.push_back(v);
        v.s = "five";
        in.push_back(v);
        inSeq.push_back(v);
        v.s = "short";
        in.push_back(v);
        inSeq.push_back(v);
        v.s = "strings.";
        in.push_back(v);
        inSeq.push_back(v);
        pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator>
            inPair(inSeq.begin(), inSeq.end());

        Test::VariableList out;
        Test::VariableList ret = t->opVariableRangeType(inPair, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<bool> in(5);
        in[0] = false;
        in[1] = true;
        in[2] = true;
        in[3] = false;
        in[4] = true;

        deque<bool> out;
        deque<bool> ret = t->opBoolSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<bool> in;
        in.push_back(false);
        in.push_back(true);
        in.push_back(true);
        in.push_back(false);
        in.push_back(true);

        list<bool> out;
        list<bool> ret = t->opBoolList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque< ::Ice::Byte> in(5);
        in[0] = '1';
        in[1] = '2';
        in[2] = '3';
        in[3] = '4';
        in[4] = '5';

        deque< ::Ice::Byte> out;
        deque< ::Ice::Byte> ret = t->opByteSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list< ::Ice::Byte> in;
        in.push_back('1');
        in.push_back('2');
        in.push_back('3');
        in.push_back('4');
        in.push_back('5');

        list< ::Ice::Byte> out;
        list< ::Ice::Byte> ret = t->opByteList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        MyByteSeq in(5);
        int i = 0;
        for(MyByteSeq::iterator p = in.begin(); p != in.end(); ++p)
        {
            *p = '1' + i++;
        }

        MyByteSeq out;
        MyByteSeq ret = t->opMyByteSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<string> in(5);
        in[0] = "These";
        in[1] = "are";
        in[2] = "five";
        in[3] = "short";
        in[4] = "strings.";

        deque<string> out;
        deque<string> ret = t->opStringSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<string> in;
        in.push_back("These");
        in.push_back("are");
        in.push_back("five");
        in.push_back("short");
        in.push_back("strings.");

        list<string> out;
        list<string> ret = t->opStringList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<Test::Fixed> in(5);
        in[0].s = 1;
        in[1].s = 2;
        in[2].s = 3;
        in[3].s = 4;
        in[4].s = 5;

        deque<Test::Fixed> out;
        deque<Test::Fixed> ret = t->opFixedSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<Test::Fixed> in(5);
        short num = 1;
        for(list<Test::Fixed>::iterator p = in.begin(); p != in.end(); ++p)
        {
            (*p).s = num++;
        }

        list<Test::Fixed> out;
        list<Test::Fixed> ret = t->opFixedList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<Test::Variable> in(5);
        in[0].s = "These";
        in[1].s = "are";
        in[2].s = "five";
        in[3].s = "short";
        in[4].s = "strings.";

        deque<Test::Variable> out;
        deque<Test::Variable> ret = t->opVariableSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<Test::Variable> in;
        Test::Variable v;
        v.s = "These";
        in.push_back(v);
        v.s = "are";
        in.push_back(v);
        v.s = "five";
        in.push_back(v);
        v.s = "short";
        in.push_back(v);
        v.s = "strings.";
        in.push_back(v);

        list<Test::Variable> out;
        list<Test::Variable> ret = t->opVariableList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<Test::StringStringDict> in(5);
        in[0]["A"] = "a";
        in[1]["B"] = "b";
        in[2]["C"] = "c";
        in[3]["D"] = "d";
        in[4]["E"] = "e";

        deque<Test::StringStringDict> out;
        deque<Test::StringStringDict> ret = t->opStringStringDictSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<Test::StringStringDict> in;
        Test::StringStringDict ssd;
        ssd["A"] = "a";
        in.push_back(ssd);
        ssd["B"] = "b";
        in.push_back(ssd);
        ssd["C"] = "c";
        in.push_back(ssd);
        ssd["D"] = "d";
        in.push_back(ssd);
        ssd["E"] = "e";
        in.push_back(ssd);

        list<Test::StringStringDict> out;
        list<Test::StringStringDict> ret = t->opStringStringDictList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<Test::E> in(5);
        in[0] = Test::E1;
        in[1] = Test::E2;
        in[2] = Test::E3;
        in[3] = Test::E1;
        in[4] = Test::E3;

        deque<Test::E> out;
        deque<Test::E> ret = t->opESeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<Test::E> in;
        in.push_back(Test::E1);
        in.push_back(Test::E2);
        in.push_back(Test::E3);
        in.push_back(Test::E1);
        in.push_back(Test::E3);

        list<Test::E> out;
        list<Test::E> ret = t->opEList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<Test::CPrx> in(5);
        in[0] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000"));
        in[1] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001"));
        in[2] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002"));
        in[3] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003"));
        in[4] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004"));

        deque<Test::CPrx> out;
        deque<Test::CPrx> ret = t->opCPrxSeq(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        list<Test::CPrx> in;
        in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000")));
        in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001")));
        in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002")));
        in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003")));
        in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004")));

        list<Test::CPrx> out;
        list<Test::CPrx> ret = t->opCPrxList(in, out);
        test(out == in);
        test(ret == in);
    }

    {
        deque<Test::CPtr> in(5);
        in[0] = new Test::C();
        in[1] = in[0];
        in[2] = in[0];
        in[3] = in[0];
        in[4] = in[0];

        deque<Test::CPtr> out;
        deque<Test::CPtr> ret = t->opCSeq(in, out);
        test(out.size() == in.size());
        test(ret.size() == in.size());
        for(unsigned int i = 1; i < in.size(); ++i)
        {
            test(out[i] == out[0]);
            test(ret[i] == out[i]);
        }
    }

    {
        list<Test::CPtr> in;
        in.push_back(new Test::C());
        in.push_back(new Test::C());
        in.push_back(new Test::C());
        in.push_back(new Test::C());
        in.push_back(new Test::C());

        list<Test::CPtr> out;
        list<Test::CPtr> ret = t->opCList(in, out);
        test(out.size() == in.size());
        test(ret.size() == in.size());
        list<Test::CPtr>::const_iterator p1;
        list<Test::CPtr>::const_iterator p2;
        for(p1 = out.begin(), p2 = ret.begin(); p1 != out.end(); ++p1, ++p2)
        {
            test(*p1 == *p2);
        }
    }

    cout << "ok" << endl;

    cout << "testing alternate dictionaries... " << flush;
    
    {
        Test::IntStringDict idict;

        idict[1] = "one";
        idict[2] = "two";
        idict[3] = "three";
        idict[-1] = "minus one";
        
        Test::IntStringDict out;
        out[5] = "five";
        
        Test::IntStringDict ret = t->opIntStringDict(idict, out);
        test(out == idict);
        test(ret == idict);
    }

    {
        Test::CustomMap<std::string, Ice::Int> idict;

        idict["one"] = 1;
        idict["two"] = 2;
        idict["three"] = 3;
        idict["minus one"] = -1;
        
        Test::CustomMap<std::string, Ice::Int> out;
        out["five"] = 5;
        
        Test::CustomMap<Ice::Long, Ice::Long> ret = t->opVarDict(idict, out);
        
#if defined(_MSC_VER) && (_MSC_VER == 1600)
        //
        // operator== for std::unordered_map does not work with Visual Studio 2010
        //
        test(out.size() == idict.size());
        
        for(Test::CustomMap<std::string, Ice::Int>::iterator p = idict.begin(); p != idict.end(); ++p)
        {
            test(out[p->first] == p->second);
        } 
#else
        test(out == idict);
#endif

        test(ret.size() == 1000);
        for(Test::CustomMap<Ice::Long, Ice::Long>::const_iterator i = ret.begin(); i != ret.end(); ++i)
        {
            test(i->second == i->first * i->first);
        }
    }

    cout << "ok" << endl;

    cout << "testing alternate custom sequences... " << flush;
    {
        Test::ShortBuffer inS;
        inS.setAndInit(new Ice::Short[3], 3);
        Test::ShortBuffer outS;
        Test::ShortBuffer ret = t->opShortBuffer(inS, outS);

        test(outS == inS);
        test(ret == inS);

        Test::CustomBuffer<bool> inBS;
        inBS.setAndInit(new bool[2], 2);
        
        Test::CustomBuffer<bool> outBS;
        Test::CustomBuffer<bool> retBS = t->opBoolBuffer(inBS, outBS);

        test(outBS == inBS);
        test(retBS == inBS);

        Test::BufferStruct bs;
        bs.byteBuf.setAndInit(new Ice::Byte[10], 10);
        bs.boolBuf.setAndInit(new bool[10], 10);
        bs.shortBuf.setAndInit(new Ice::Short[10], 10);
        bs.intBuf.setAndInit(new Ice::Int[10], 10);
        bs.longBuf.setAndInit(new Ice::Long[10], 10);
        bs.floatBuf.setAndInit(new Ice::Float[10], 10);
        bs.doubleBuf.setAndInit(new Ice::Double[10], 10);

        Test::BufferStruct rs = t->opBufferStruct(bs);
        test(rs == bs);

        Ice::OutputStreamPtr os = Ice::createOutputStream(communicator);
        os->write(rs);
        Ice::ByteSeq bytes;
        os->finished(bytes);

        Ice::InputStreamPtr is = Ice::wrapInputStream(communicator, bytes);
        Test::BufferStruct rs2;
        is->read(rs2);
        test(rs == rs2);
    }
    cout << "ok" << endl;
    
    if(!collocated)
    {
        cout << "testing alternate sequences with AMI... " << flush;

        {
            Test::DoubleSeq in(5);
            in[0] = 3.14;
            in[1] = 1 / 3;
            in[2] = 0.375;
            in[3] = 4 / 3;
            in[4] = -5.725;
            Ice::Double inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const Ice::Double*, const Ice::Double*> inPair(inArray, inArray + 5);

            AMI_TestIntf_opDoubleArrayIPtr cb = new AMI_TestIntf_opDoubleArrayI(inPair);
            t->opDoubleArray_async(cb, inPair);
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            bool inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const bool*, const bool*> inPair(inArray, inArray + 5);

            AMI_TestIntf_opBoolArrayIPtr cb = new AMI_TestIntf_opBoolArrayI(inPair);
            t->opBoolArray_async(cb, inPair);
            cb->check();
        }

        {
            Ice::Byte in[5];
            in[0] = '1';
            in[1] = '2';
            in[2] = '3';
            in[3] = '4';
            in[4] = '5';
            pair<const Ice::Byte*, const Ice::Byte*> inPair(in, in + 5);

            AMI_TestIntf_opByteArrayIPtr cb = new AMI_TestIntf_opByteArrayI(inPair);
            t->opByteArray_async(cb, inPair);
            cb->check();
        }

        {
            Test::VariableList in;
            Test::Variable inArray[5];
            inArray[0].s = "These";
            in.push_back(inArray[0]);
            inArray[1].s = "are";
            in.push_back(inArray[1]);
            inArray[2].s = "five";
            in.push_back(inArray[2]);
            inArray[3].s = "short";
            in.push_back(inArray[3]);
            inArray[4].s = "strings.";
            in.push_back(inArray[4]);
            pair<const Test::Variable*, const Test::Variable*> inPair(inArray, inArray + 5);

            AMI_TestIntf_opVariableArrayIPtr cb = new AMI_TestIntf_opVariableArrayI(inPair);
            t->opVariableArray_async(cb, inPair);
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> inPair(in.begin(), in.end());

            AMI_TestIntf_opBoolRangeIPtr cb = new AMI_TestIntf_opBoolRangeI(inPair);
            t->opBoolRange_async(cb, inPair);
            cb->check();
        }

        {
            Test::ByteList in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');
            pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

            AMI_TestIntf_opByteRangeIPtr cb = new AMI_TestIntf_opByteRangeI(inPair);
            t->opByteRange_async(cb, inPair);
            cb->check();
        }

        {
            Test::VariableList in;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            v.s = "are";
            in.push_back(v);
            v.s = "five";
            in.push_back(v);
            v.s = "short";
            in.push_back(v);
            v.s = "strings.";
            in.push_back(v);
            pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> inPair(in.begin(), in.end());

            AMI_TestIntf_opVariableRangeIPtr cb = new AMI_TestIntf_opVariableRangeI(inPair);
            t->opVariableRange_async(cb, inPair);
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            bool inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const bool*, const bool*> inPair(inArray, inArray + 5);

            AMI_TestIntf_opBoolRangeTypeIPtr cb = new AMI_TestIntf_opBoolRangeTypeI(inPair);
            t->opBoolRangeType_async(cb, inPair);
            cb->check();
        }

        {
            Test::ByteList in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');
            pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

            AMI_TestIntf_opByteRangeTypeIPtr cb = new AMI_TestIntf_opByteRangeTypeI(inPair);
            t->opByteRangeType_async(cb, inPair);
            cb->check();
        }

        {
            Test::VariableList in;
            deque<Test::Variable> inSeq;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "are";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "five";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "short";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "strings.";
            in.push_back(v);
            inSeq.push_back(v);
            pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator> inPair(inSeq.begin(), 
                                                                                                      inSeq.end());

            AMI_TestIntf_opVariableRangeTypeIPtr cb = new AMI_TestIntf_opVariableRangeTypeI(inPair);
            t->opVariableRangeType_async(cb, inPair);
            cb->check();
        }

        {
            deque<bool> in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;

            AMI_TestIntf_opBoolSeqIPtr cb = new AMI_TestIntf_opBoolSeqI(in);
            t->opBoolSeq_async(cb, in);
            cb->check();
        }

        {
            list<bool> in;
            in.push_back(false);
            in.push_back(true);
            in.push_back(true);
            in.push_back(false);
            in.push_back(true);

            AMI_TestIntf_opBoolListIPtr cb = new AMI_TestIntf_opBoolListI(in);
            t->opBoolList_async(cb, in);
            cb->check();
        }

        {
            deque< ::Ice::Byte> in(5);
            in[0] = '1';
            in[1] = '2';
            in[2] = '3';
            in[3] = '4';
            in[4] = '5';

            AMI_TestIntf_opByteSeqIPtr cb = new AMI_TestIntf_opByteSeqI(in);
            t->opByteSeq_async(cb, in);
            cb->check();
        }

        {
            list< ::Ice::Byte> in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');

            AMI_TestIntf_opByteListIPtr cb = new AMI_TestIntf_opByteListI(in);
            t->opByteList_async(cb, in);
            cb->check();
        }

        {
            MyByteSeq in(5);
            int i = 0;
            for(MyByteSeq::iterator p = in.begin(); p != in.end(); ++p)
            {
                *p = '1' + i++;
            }

            AMI_TestIntf_opMyByteSeqIPtr cb = new AMI_TestIntf_opMyByteSeqI(in);
            t->opMyByteSeq_async(cb, in);
            cb->check();
        }

        {
            deque<string> in(5);
            in[0] = "These";
            in[1] = "are";
            in[2] = "five";
            in[3] = "short";
            in[4] = "strings.";

            AMI_TestIntf_opStringSeqIPtr cb = new AMI_TestIntf_opStringSeqI(in);
            t->opStringSeq_async(cb, in);
            cb->check();
        }

        {
            list<string> in;
            in.push_back("These");
            in.push_back("are");
            in.push_back("five");
            in.push_back("short");
            in.push_back("strings.");

            AMI_TestIntf_opStringListIPtr cb = new AMI_TestIntf_opStringListI(in);
            t->opStringList_async(cb, in);
            cb->check();
        }

        {
            deque<Test::Fixed> in(5);
            in[0].s = 1;
            in[1].s = 2;
            in[2].s = 3;
            in[3].s = 4;
            in[4].s = 5;

            AMI_TestIntf_opFixedSeqIPtr cb = new AMI_TestIntf_opFixedSeqI(in);
            t->opFixedSeq_async(cb, in);
            cb->check();
        }

        {
            list<Test::Fixed> in(5);
            short num = 1;
            for(list<Test::Fixed>::iterator p = in.begin(); p != in.end(); ++p)
            {
                (*p).s = num++;
            }

            AMI_TestIntf_opFixedListIPtr cb = new AMI_TestIntf_opFixedListI(in);
            t->opFixedList_async(cb, in);
            cb->check();
        }

        {
            deque<Test::Variable> in(5);
            in[0].s = "These";
            in[1].s = "are";
            in[2].s = "five";
            in[3].s = "short";
            in[4].s = "strings.";

            AMI_TestIntf_opVariableSeqIPtr cb = new AMI_TestIntf_opVariableSeqI(in);
            t->opVariableSeq_async(cb, in);
            cb->check();
        }

        {
            list<Test::Variable> in;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            v.s = "are";
            in.push_back(v);
            v.s = "five";
            in.push_back(v);
            v.s = "short";
            in.push_back(v);
            v.s = "strings.";
            in.push_back(v);

            AMI_TestIntf_opVariableListIPtr cb = new AMI_TestIntf_opVariableListI(in);
            t->opVariableList_async(cb, in);
            cb->check();
        }

        {
            deque<Test::StringStringDict> in(5);
            in[0]["A"] = "a";
            in[1]["B"] = "b";
            in[2]["C"] = "c";
            in[3]["D"] = "d";
            in[4]["E"] = "e";

            AMI_TestIntf_opStringStringDictSeqIPtr cb = new AMI_TestIntf_opStringStringDictSeqI(in);
            t->opStringStringDictSeq_async(cb, in);
            cb->check();
        }

        {
            list<Test::StringStringDict> in;
            Test::StringStringDict ssd;
            ssd["A"] = "a";
            in.push_back(ssd);
            ssd["B"] = "b";
            in.push_back(ssd);
            ssd["C"] = "c";
            in.push_back(ssd);
            ssd["D"] = "d";
            in.push_back(ssd);
            ssd["E"] = "e";
            in.push_back(ssd);

            AMI_TestIntf_opStringStringDictListIPtr cb = new AMI_TestIntf_opStringStringDictListI(in);
            t->opStringStringDictList_async(cb, in);
            cb->check();
        }

        {
            deque<Test::E> in(5);
            in[0] = Test::E1;
            in[1] = Test::E2;
            in[2] = Test::E3;
            in[3] = Test::E1;
            in[4] = Test::E3;

            AMI_TestIntf_opESeqIPtr cb = new AMI_TestIntf_opESeqI(in);
            t->opESeq_async(cb, in);
            cb->check();
        }

        {
            list<Test::E> in;
            in.push_back(Test::E1);
            in.push_back(Test::E2);
            in.push_back(Test::E3);
            in.push_back(Test::E1);
            in.push_back(Test::E3);

            AMI_TestIntf_opEListIPtr cb = new AMI_TestIntf_opEListI(in);
            t->opEList_async(cb, in);
            cb->check();
        }

        {
            deque<Test::CPrx> in(5);
            in[0] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000"));
            in[1] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001"));
            in[2] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002"));
            in[3] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003"));
            in[4] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004"));

            AMI_TestIntf_opCPrxSeqIPtr cb = new AMI_TestIntf_opCPrxSeqI(in);
            t->opCPrxSeq_async(cb, in);
            cb->check();
        }

        {
            list<Test::CPrx> in;
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004")));

            AMI_TestIntf_opCPrxListIPtr cb = new AMI_TestIntf_opCPrxListI(in);
            t->opCPrxList_async(cb, in);
            cb->check();
        }

        {
            deque<Test::CPtr> in(5);
            in[0] = new Test::C();
            in[1] = in[0];
            in[2] = in[0];
            in[3] = in[0];
            in[4] = in[0];

            AMI_TestIntf_opCSeqIPtr cb = new AMI_TestIntf_opCSeqI(in);
            t->opCSeq_async(cb, in);
            cb->check();
        }
    
        {
            list<Test::CPtr> in;
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());

            AMI_TestIntf_opCListIPtr cb = new AMI_TestIntf_opCListI(in);
            t->opCList_async(cb, in);
            cb->check();
        }

        cout << "ok" << endl;

        cout << "testing alternate sequences with new AMI... " << flush;
        {
            {
                Test::DoubleSeq in(5);
                in[0] = 3.14;
                in[1] = 1 / 3;
                in[2] = 0.375;
                in[3] = 4 / 3;
                in[4] = -5.725;
                Ice::Double inArray[5];
                for(int i = 0; i < 5; ++i)
                {
                    inArray[i] = in[i];
                }
                pair<const Ice::Double*, const Ice::Double*> inPair(inArray, inArray + 5);

                Test::DoubleSeq out;
                Ice::AsyncResultPtr r = t->begin_opDoubleArray(inPair);
                Test::DoubleSeq ret = t->end_opDoubleArray(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::BoolSeq in(5);
                in[0] = false;
                in[1] = true;
                in[2] = true;
                in[3] = false;
                in[4] = true;
                bool inArray[5];
                for(int i = 0; i < 5; ++i)
                {
                    inArray[i] = in[i];
                }
                pair<const bool*, const bool*> inPair(inArray, inArray + 5);

                Test::BoolSeq out;
                Ice::AsyncResultPtr r = t->begin_opBoolArray(inPair);
                Test::BoolSeq ret = t->end_opBoolArray(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::ByteList in;
                Ice::Byte inArray[5];
                inArray[0] = '1';
                in.push_back(inArray[0]);
                inArray[1] = '2';
                in.push_back(inArray[1]);
                inArray[2] = '3';
                in.push_back(inArray[2]);
                inArray[3] = '4';
                in.push_back(inArray[3]);
                inArray[4] = '5';
                in.push_back(inArray[4]);
                pair<const Ice::Byte*, const Ice::Byte*> inPair(inArray, inArray + 5);

                Test::ByteList out;
                Ice::AsyncResultPtr r = t->begin_opByteArray(inPair);
                Test::ByteList ret = t->end_opByteArray(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::VariableList in;
                Test::Variable inArray[5];
                inArray[0].s = "These";
                in.push_back(inArray[0]);
                inArray[1].s = "are";
                in.push_back(inArray[1]);
                inArray[2].s = "five";
                in.push_back(inArray[2]);
                inArray[3].s = "short";
                in.push_back(inArray[3]);
                inArray[4].s = "strings.";
                in.push_back(inArray[4]);
                pair<const Test::Variable*, const Test::Variable*> inPair(inArray, inArray + 5);

                Test::VariableList out;
                Ice::AsyncResultPtr r = t->begin_opVariableArray(inPair);
                Test::VariableList ret = t->end_opVariableArray(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::BoolSeq in(5);
                in[0] = false;
                in[1] = true;
                in[2] = true;
                in[3] = false;
                in[4] = true;
                pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> inPair(in.begin(), in.end());

                Test::BoolSeq out;
                Ice::AsyncResultPtr r = t->begin_opBoolRange(inPair);
                Test::BoolSeq ret = t->end_opBoolRange(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::ByteList in;
                in.push_back('1');
                in.push_back('2');
                in.push_back('3');
                in.push_back('4');
                in.push_back('5');
                pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

                Test::ByteList out;
                Ice::AsyncResultPtr r = t->begin_opByteRange(inPair);
                Test::ByteList ret = t->end_opByteRange(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::VariableList in;
                Test::Variable v;
                v.s = "These";
                in.push_back(v);
                v.s = "are";
                in.push_back(v);
                v.s = "five";
                in.push_back(v);
                v.s = "short";
                in.push_back(v);
                v.s = "strings.";
                in.push_back(v);
                pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> inPair(in.begin(), in.end());

                Test::VariableList out;
                Ice::AsyncResultPtr r = t->begin_opVariableRange(inPair);
                Test::VariableList ret = t->end_opVariableRange(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::BoolSeq in(5);
                in[0] = false;
                in[1] = true;
                in[2] = true;
                in[3] = false;
                in[4] = true;
                bool inArray[5];
                for(int i = 0; i < 5; ++i)
                {
                    inArray[i] = in[i];
                }
                pair<const bool*, const bool*> inPair(inArray, inArray + 5);

                Test::BoolSeq out;
                Ice::AsyncResultPtr r = t->begin_opBoolRangeType(inPair);
                Test::BoolSeq ret = t->end_opBoolRangeType(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::ByteList in;
                in.push_back('1');
                in.push_back('2');
                in.push_back('3');
                in.push_back('4');
                in.push_back('5');
                pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

                Test::ByteList out;
                Ice::AsyncResultPtr r = t->begin_opByteRangeType(inPair);
                Test::ByteList ret = t->end_opByteRangeType(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                Test::VariableList in;
                deque<Test::Variable> inSeq;
                Test::Variable v;
                v.s = "These";
                in.push_back(v);
                inSeq.push_back(v);
                v.s = "are";
                in.push_back(v);
                inSeq.push_back(v);
                v.s = "five";
                in.push_back(v);
                inSeq.push_back(v);
                v.s = "short";
                in.push_back(v);
                inSeq.push_back(v);
                v.s = "strings.";
                in.push_back(v);
                inSeq.push_back(v);
                pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator>
                    inPair(inSeq.begin(), inSeq.end());

                Test::VariableList out;
                Ice::AsyncResultPtr r = t->begin_opVariableRangeType(inPair);
                Test::VariableList ret = t->end_opVariableRangeType(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<bool> in(5);
                in[0] = false;
                in[1] = true;
                in[2] = true;
                in[3] = false;
                in[4] = true;

                deque<bool> out;
                Ice::AsyncResultPtr r = t->begin_opBoolSeq(in);
                deque<bool> ret = t->end_opBoolSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<bool> in;
                in.push_back(false);
                in.push_back(true);
                in.push_back(true);
                in.push_back(false);
                in.push_back(true);

                list<bool> out;
                Ice::AsyncResultPtr r = t->begin_opBoolList(in);
                list<bool> ret = t->end_opBoolList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque< ::Ice::Byte> in(5);
                in[0] = '1';
                in[1] = '2';
                in[2] = '3';
                in[3] = '4';
                in[4] = '5';

                deque< ::Ice::Byte> out;
                Ice::AsyncResultPtr r = t->begin_opByteSeq(in);
                deque< ::Ice::Byte> ret = t->end_opByteSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list< ::Ice::Byte> in;
                in.push_back('1');
                in.push_back('2');
                in.push_back('3');
                in.push_back('4');
                in.push_back('5');

                list< ::Ice::Byte> out;
                Ice::AsyncResultPtr r = t->begin_opByteList(in);
                list< ::Ice::Byte> ret = t->end_opByteList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                MyByteSeq in(5);
                int i = 0;
                for(MyByteSeq::iterator p = in.begin(); p != in.end(); ++p)
                {
                    *p = '1' + i++;
                }

                MyByteSeq out;
                Ice::AsyncResultPtr r = t->begin_opMyByteSeq(in);
                MyByteSeq ret = t->end_opMyByteSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<string> in(5);
                in[0] = "These";
                in[1] = "are";
                in[2] = "five";
                in[3] = "short";
                in[4] = "strings.";

                deque<string> out;
                Ice::AsyncResultPtr r = t->begin_opStringSeq(in);
                deque<string> ret = t->end_opStringSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<string> in;
                in.push_back("These");
                in.push_back("are");
                in.push_back("five");
                in.push_back("short");
                in.push_back("strings.");

                list<string> out;
                Ice::AsyncResultPtr r = t->begin_opStringList(in);
                list<string> ret = t->end_opStringList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<Test::Fixed> in(5);
                in[0].s = 1;
                in[1].s = 2;
                in[2].s = 3;
                in[3].s = 4;
                in[4].s = 5;

                deque<Test::Fixed> out;
                Ice::AsyncResultPtr r = t->begin_opFixedSeq(in);
                deque<Test::Fixed> ret = t->end_opFixedSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<Test::Fixed> in(5);
                short num = 1;
                for(list<Test::Fixed>::iterator p = in.begin(); p != in.end(); ++p)
                {
                    (*p).s = num++;
                }

                list<Test::Fixed> out;
                Ice::AsyncResultPtr r = t->begin_opFixedList(in);
                list<Test::Fixed> ret = t->end_opFixedList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<Test::Variable> in(5);
                in[0].s = "These";
                in[1].s = "are";
                in[2].s = "five";
                in[3].s = "short";
                in[4].s = "strings.";

                deque<Test::Variable> out;
                Ice::AsyncResultPtr r = t->begin_opVariableSeq(in);
                deque<Test::Variable> ret = t->end_opVariableSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<Test::Variable> in;
                Test::Variable v;
                v.s = "These";
                in.push_back(v);
                v.s = "are";
                in.push_back(v);
                v.s = "five";
                in.push_back(v);
                v.s = "short";
                in.push_back(v);
                v.s = "strings.";
                in.push_back(v);

                list<Test::Variable> out;
                Ice::AsyncResultPtr r = t->begin_opVariableList(in);
                list<Test::Variable> ret = t->end_opVariableList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<Test::StringStringDict> in(5);
                in[0]["A"] = "a";
                in[1]["B"] = "b";
                in[2]["C"] = "c";
                in[3]["D"] = "d";
                in[4]["E"] = "e";

                deque<Test::StringStringDict> out;
                Ice::AsyncResultPtr r = t->begin_opStringStringDictSeq(in);
                deque<Test::StringStringDict> ret = t->end_opStringStringDictSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<Test::StringStringDict> in;
                Test::StringStringDict ssd;
                ssd["A"] = "a";
                in.push_back(ssd);
                ssd["B"] = "b";
                in.push_back(ssd);
                ssd["C"] = "c";
                in.push_back(ssd);
                ssd["D"] = "d";
                in.push_back(ssd);
                ssd["E"] = "e";
                in.push_back(ssd);

                list<Test::StringStringDict> out;
                Ice::AsyncResultPtr r = t->begin_opStringStringDictList(in);
                list<Test::StringStringDict> ret = t->end_opStringStringDictList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<Test::E> in(5);
                in[0] = Test::E1;
                in[1] = Test::E2;
                in[2] = Test::E3;
                in[3] = Test::E1;
                in[4] = Test::E3;

                deque<Test::E> out;
                Ice::AsyncResultPtr r = t->begin_opESeq(in);
                deque<Test::E> ret = t->end_opESeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<Test::E> in;
                in.push_back(Test::E1);
                in.push_back(Test::E2);
                in.push_back(Test::E3);
                in.push_back(Test::E1);
                in.push_back(Test::E3);

                list<Test::E> out;
                Ice::AsyncResultPtr r = t->begin_opEList(in);
                list<Test::E> ret = t->end_opEList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<Test::CPrx> in(5);
                in[0] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000"));
                in[1] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001"));
                in[2] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002"));
                in[3] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003"));
                in[4] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004"));

                deque<Test::CPrx> out;
                Ice::AsyncResultPtr r = t->begin_opCPrxSeq(in);
                deque<Test::CPrx> ret = t->end_opCPrxSeq(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                list<Test::CPrx> in;
                in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000")));
                in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001")));
                in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002")));
                in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003")));
                in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004")));

                list<Test::CPrx> out;
                Ice::AsyncResultPtr r = t->begin_opCPrxList(in);
                list<Test::CPrx> ret = t->end_opCPrxList(out, r);
                test(out == in);
                test(ret == in);
            }

            {
                deque<Test::CPtr> in(5);
                in[0] = new Test::C();
                in[1] = in[0];
                in[2] = in[0];
                in[3] = in[0];
                in[4] = in[0];

                deque<Test::CPtr> out;
                Ice::AsyncResultPtr r = t->begin_opCSeq(in);
                deque<Test::CPtr> ret = t->end_opCSeq(out, r);
                test(out.size() == in.size());
                test(ret.size() == in.size());
                for(unsigned int i = 1; i < in.size(); ++i)
                {
                    test(out[i] == out[0]);
                    test(ret[i] == out[i]);
                }
            }

            {
                list<Test::CPtr> in;
                in.push_back(new Test::C());
                in.push_back(new Test::C());
                in.push_back(new Test::C());
                in.push_back(new Test::C());
                in.push_back(new Test::C());

                list<Test::CPtr> out;
                Ice::AsyncResultPtr r = t->begin_opCList(in);
                list<Test::CPtr> ret = t->end_opCList(out, r);
                test(out.size() == in.size());
                test(ret.size() == in.size());
                list<Test::CPtr>::const_iterator p1;
                list<Test::CPtr>::const_iterator p2;
                for(p1 = out.begin(), p2 = ret.begin(); p1 != out.end(); ++p1, ++p2)
                {
                    test(*p1 == *p2);
                }
            }
            
            
            {
                Test::ByteSeq in;
                in.push_back('1');
                in.push_back('2');
                in.push_back('3');
                in.push_back('4');
                
                Ice::AsyncResultPtr r = t->begin_opOutArrayByteSeq(in);
                
                Test::ByteSeq out;
                t->end_opOutArrayByteSeq(out, r);
                
                test(out.size() == in.size());
                Test::ByteSeq::const_iterator p1;
                Test::ByteSeq::const_iterator p2;
                
                for(p1 = out.begin(), p2 = in.begin(); p1 != out.end(); ++p1, ++p2)
                {
                    test(*p1 == *p2);
                }
            }
            
            {
                Test::ByteSeq in;
                in.push_back('1');
                in.push_back('2');
                in.push_back('3');
                in.push_back('4');
                
                Ice::AsyncResultPtr r = t->begin_opOutRangeByteSeq(in);
                
                Test::ByteSeq out;
                t->end_opOutRangeByteSeq(out, r);
                
                test(out.size() == in.size());
                Test::ByteSeq::const_iterator p1;
                Test::ByteSeq::const_iterator p2;
                
                for(p1 = out.begin(), p2 = in.begin(); p1 != out.end(); ++p1, ++p2)
                {
                    test(*p1 == *p2);
                }
            }
        }
        cout << "ok" << endl;

        cout << "testing alternate sequences with new AMI callbacks... " << flush;

        {
            Test::DoubleSeq in(5);
            in[0] = 3.14;
            in[1] = 1 / 3;
            in[2] = 0.375;
            in[3] = 4 / 3;
            in[4] = -5.725;
            Ice::Double inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const Ice::Double*, const Ice::Double*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opDoubleArrayPtr callback = 
                Test::newCallback_TestIntf_opDoubleArray(cb, &Callback::opDoubleArray, &Callback::noEx);
            t->begin_opDoubleArray(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            bool inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const bool*, const bool*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opBoolArrayPtr callback = 
                Test::newCallback_TestIntf_opBoolArray(cb, &Callback::opBoolArray, &Callback::noEx);
            t->begin_opBoolArray(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Ice::Byte in[5];
            in[0] = '1';
            in[1] = '2';
            in[2] = '3';
            in[3] = '4';
            in[4] = '5';
            pair<const Ice::Byte*, const Ice::Byte*> inPair(in, in + 5);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opByteArrayPtr callback = 
                Test::newCallback_TestIntf_opByteArray(cb, &Callback::opByteArray, &Callback::noEx);
            t->begin_opByteArray(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::VariableList in;
            Test::Variable inArray[5];
            inArray[0].s = "These";
            in.push_back(inArray[0]);
            inArray[1].s = "are";
            in.push_back(inArray[1]);
            inArray[2].s = "five";
            in.push_back(inArray[2]);
            inArray[3].s = "short";
            in.push_back(inArray[3]);
            inArray[4].s = "strings.";
            in.push_back(inArray[4]);
            pair<const Test::Variable*, const Test::Variable*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opVariableArrayPtr callback =
                Test::newCallback_TestIntf_opVariableArray(cb, &Callback::opVariableArray, &Callback::noEx);
            t->begin_opVariableArray(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opBoolRangePtr callback = 
                Test::newCallback_TestIntf_opBoolRange(cb, &Callback::opBoolRange, &Callback::noEx);
            t->begin_opBoolRange(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::ByteList in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');
            pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opByteRangePtr callback = 
                Test::newCallback_TestIntf_opByteRange(cb, &Callback::opByteRange, &Callback::noEx);
            t->begin_opByteRange(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::VariableList in;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            v.s = "are";
            in.push_back(v);
            v.s = "five";
            in.push_back(v);
            v.s = "short";
            in.push_back(v);
            v.s = "strings.";
            in.push_back(v);
            pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opVariableRangePtr callback =
                Test::newCallback_TestIntf_opVariableRange(cb, &Callback::opVariableRange, &Callback::noEx);
            t->begin_opVariableRange(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            bool inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const bool*, const bool*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opBoolRangeTypePtr callback = 
                Test::newCallback_TestIntf_opBoolRangeType(cb, &Callback::opBoolRangeType, &Callback::noEx);
            t->begin_opBoolRangeType(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::ByteList in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');
            pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opByteRangeTypePtr callback =
                Test::newCallback_TestIntf_opByteRangeType(cb, &Callback::opByteRangeType, &Callback::noEx);
            t->begin_opByteRangeType(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::VariableList in;
            deque<Test::Variable> inSeq;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "are";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "five";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "short";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "strings.";
            in.push_back(v);
            inSeq.push_back(v);
            pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator> inPair(inSeq.begin(), 
                                                                                                      inSeq.end());

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opVariableRangeTypePtr callback = 
                Test::newCallback_TestIntf_opVariableRangeType(cb, &Callback::opVariableRangeType, &Callback::noEx);
            t->begin_opVariableRangeType(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            deque<bool> in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opBoolSeqPtr callback = 
                Test::newCallback_TestIntf_opBoolSeq(cb, &Callback::opBoolSeq, &Callback::noEx);
            t->begin_opBoolSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<bool> in;
            in.push_back(false);
            in.push_back(true);
            in.push_back(true);
            in.push_back(false);
            in.push_back(true);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opBoolListPtr callback = 
                Test::newCallback_TestIntf_opBoolList(cb, &Callback::opBoolList, &Callback::noEx);
            t->begin_opBoolList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque< ::Ice::Byte> in(5);
            in[0] = '1';
            in[1] = '2';
            in[2] = '3';
            in[3] = '4';
            in[4] = '5';

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opByteSeqPtr callback = 
                Test::newCallback_TestIntf_opByteSeq(cb, &Callback::opByteSeq, &Callback::noEx);
            t->begin_opByteSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list< ::Ice::Byte> in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opByteListPtr callback = 
                Test::newCallback_TestIntf_opByteList(cb, &Callback::opByteList, &Callback::noEx);
            t->begin_opByteList(in, callback, newInParam(in));
            cb->check();
        }

        {
            MyByteSeq in(5);
            int i = 0;
            for(MyByteSeq::iterator p = in.begin(); p != in.end(); ++p)
            {
                *p = '1' + i++;
            }

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opMyByteSeqPtr callback = 
                Test::newCallback_TestIntf_opMyByteSeq(cb, &Callback::opMyByteSeq, &Callback::noEx);
            t->begin_opMyByteSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<string> in(5);
            in[0] = "These";
            in[1] = "are";
            in[2] = "five";
            in[3] = "short";
            in[4] = "strings.";

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opStringSeqPtr callback = 
                Test::newCallback_TestIntf_opStringSeq(cb, &Callback::opStringSeq, &Callback::noEx);
            t->begin_opStringSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<string> in;
            in.push_back("These");
            in.push_back("are");
            in.push_back("five");
            in.push_back("short");
            in.push_back("strings.");

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opStringListPtr callback = 
                Test::newCallback_TestIntf_opStringList(cb, &Callback::opStringList, &Callback::noEx);
            t->begin_opStringList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<Test::Fixed> in(5);
            in[0].s = 1;
            in[1].s = 2;
            in[2].s = 3;
            in[3].s = 4;
            in[4].s = 5;

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opFixedSeqPtr callback = 
                Test::newCallback_TestIntf_opFixedSeq(cb, &Callback::opFixedSeq, &Callback::noEx);
            t->begin_opFixedSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<Test::Fixed> in(5);
            short num = 1;
            for(list<Test::Fixed>::iterator p = in.begin(); p != in.end(); ++p)
            {
                (*p).s = num++;
            }

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opFixedListPtr callback = 
                Test::newCallback_TestIntf_opFixedList(cb, &Callback::opFixedList, &Callback::noEx);
            t->begin_opFixedList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<Test::Variable> in(5);
            in[0].s = "These";
            in[1].s = "are";
            in[2].s = "five";
            in[3].s = "short";
            in[4].s = "strings.";

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opVariableSeqPtr callback = 
                Test::newCallback_TestIntf_opVariableSeq(cb, &Callback::opVariableSeq, &Callback::noEx);
            t->begin_opVariableSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<Test::Variable> in;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            v.s = "are";
            in.push_back(v);
            v.s = "five";
            in.push_back(v);
            v.s = "short";
            in.push_back(v);
            v.s = "strings.";
            in.push_back(v);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opVariableListPtr callback = 
                Test::newCallback_TestIntf_opVariableList(cb, &Callback::opVariableList, &Callback::noEx);
            t->begin_opVariableList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<Test::StringStringDict> in(5);
            in[0]["A"] = "a";
            in[1]["B"] = "b";
            in[2]["C"] = "c";
            in[3]["D"] = "d";
            in[4]["E"] = "e";

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opStringStringDictSeqPtr callback = 
                Test::newCallback_TestIntf_opStringStringDictSeq(cb, &Callback::opStringStringDictSeq, &Callback::noEx);
            t->begin_opStringStringDictSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<Test::StringStringDict> in;
            Test::StringStringDict ssd;
            ssd["A"] = "a";
            in.push_back(ssd);
            ssd["B"] = "b";
            in.push_back(ssd);
            ssd["C"] = "c";
            in.push_back(ssd);
            ssd["D"] = "d";
            in.push_back(ssd);
            ssd["E"] = "e";
            in.push_back(ssd);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opStringStringDictListPtr callback = 
                Test::newCallback_TestIntf_opStringStringDictList(cb, &Callback::opStringStringDictList, &Callback::noEx);
            t->begin_opStringStringDictList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<Test::E> in(5);
            in[0] = Test::E1;
            in[1] = Test::E2;
            in[2] = Test::E3;
            in[3] = Test::E1;
            in[4] = Test::E3;

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opESeqPtr callback = 
                Test::newCallback_TestIntf_opESeq(cb, &Callback::opESeq, &Callback::noEx);
            t->begin_opESeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<Test::E> in;
            in.push_back(Test::E1);
            in.push_back(Test::E2);
            in.push_back(Test::E3);
            in.push_back(Test::E1);
            in.push_back(Test::E3);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opEListPtr callback = 
                Test::newCallback_TestIntf_opEList(cb, &Callback::opEList, &Callback::noEx);
            t->begin_opEList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<Test::CPrx> in(5);
            in[0] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000"));
            in[1] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001"));
            in[2] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002"));
            in[3] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003"));
            in[4] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004"));

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opCPrxSeqPtr callback = 
                Test::newCallback_TestIntf_opCPrxSeq(cb, &Callback::opCPrxSeq, &Callback::noEx);
            t->begin_opCPrxSeq(in, callback, newInParam(in));
            cb->check();
        }

        {
            list<Test::CPrx> in;
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004")));

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opCPrxListPtr callback = 
                Test::newCallback_TestIntf_opCPrxList(cb, &Callback::opCPrxList, &Callback::noEx);
            t->begin_opCPrxList(in, callback, newInParam(in));
            cb->check();
        }

        {
            deque<Test::CPtr> in(5);
            in[0] = new Test::C();
            in[1] = in[0];
            in[2] = in[0];
            in[3] = in[0];
            in[4] = in[0];

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opCSeqPtr callback = Test::newCallback_TestIntf_opCSeq(cb, &Callback::opCSeq, &Callback::noEx);
            t->begin_opCSeq(in, callback, newInParam(in));
            cb->check();
        }
    
        {
            list<Test::CPtr> in;
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opCListPtr callback = 
                Test::newCallback_TestIntf_opCList(cb, &Callback::opCList, &Callback::noEx);
            t->begin_opCList(in, callback, newInParam(in));
            cb->check();
        }
        
        
        {
            Test::ByteSeq in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            
            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opOutArrayByteSeqPtr callback = Test::newCallback_TestIntf_opOutArrayByteSeq(cb, 
                                            &Callback::opOutArrayByteSeq, &Callback::noEx);
            
            t->begin_opOutArrayByteSeq(in, callback, newInParam(in));
            cb->check();
        }
        
        {
            Test::ByteSeq in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            
            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opOutRangeByteSeqPtr callback = Test::newCallback_TestIntf_opOutRangeByteSeq(cb, 
                                            &Callback::opOutRangeByteSeq, &Callback::noEx);
            
            t->begin_opOutRangeByteSeq(in, callback, newInParam(in));
            cb->check();
        }

        cout << "ok" << endl;
#ifdef ICE_CPP11
        cout << "testing alternate sequences with C++11 AMI callbacks... " << flush;

        {
            Test::DoubleSeq in(5);
            in[0] = 3.14;
            in[1] = 1 / 3;
            in[2] = 0.375;
            in[3] = 4 / 3;
            in[4] = -5.725;
            Ice::Double inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const Ice::Double*, const Ice::Double*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            t->begin_opDoubleArray(inPair, 
                                    [=](const pair<const Ice::Double*, const Ice::Double*>& p1, const pair<const Ice::Double*, const Ice::Double*>& p2)
                                        {
                                            cb->opDoubleArray(p1, p2, newInParam(inPair));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(inPair));
                                        });
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            bool inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const bool*, const bool*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            t->begin_opBoolArray(inPair, 
                                    [=](const pair<const bool*, const bool*>& p1, const pair<const bool*, const bool*>& p2)
                                        {
                                            cb->opBoolArray(p1, p2, newInParam(inPair));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(inPair));
                                        });
            cb->check();
        }

        {
            Ice::Byte in[5];
            in[0] = '1';
            in[1] = '2';
            in[2] = '3';
            in[3] = '4';
            in[4] = '5';
            pair<const Ice::Byte*, const Ice::Byte*> inPair(in, in + 5);

            CallbackPtr cb = new Callback();
            t->begin_opByteArray(inPair, 
                                    [=](const pair<const Ice::Byte*, const Ice::Byte*>& p1, 
                                        const pair<const Ice::Byte*, const Ice::Byte*>& p2)
                                        {
                                            cb->opByteArray(p1, p2, newInParam(inPair));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(inPair));
                                        });
            cb->check();
        }

        {
            Test::VariableList in;
            Test::Variable inArray[5];
            inArray[0].s = "These";
            in.push_back(inArray[0]);
            inArray[1].s = "are";
            in.push_back(inArray[1]);
            inArray[2].s = "five";
            in.push_back(inArray[2]);
            inArray[3].s = "short";
            in.push_back(inArray[3]);
            inArray[4].s = "strings.";
            in.push_back(inArray[4]);
            pair<const Test::Variable*, const Test::Variable*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            t->begin_opVariableArray(inPair, 
                                        [=](const pair<const Test::Variable*, const Test::Variable*>& p1,
                                            const pair<const Test::Variable*, const Test::Variable*>& p2)
                                            {
                                                cb->opVariableArray(p1, p2, newInParam(inPair));
                                            },
                                        [=](const Ice::Exception& ex)
                                            {
                                                cb->noEx(ex, newInParam(inPair));
                                            });
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            t->begin_opBoolRange(inPair,
                                    [=](const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& p1,
                                        const pair<Test::BoolSeq::const_iterator, Test::BoolSeq::const_iterator>& p2)
                                        {
                                            cb->opBoolRange(p1, p2, newInParam(inPair));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(inPair));
                                        });
            cb->check();
        }

        {
            Test::ByteList in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');
            pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            t->begin_opByteRange(inPair, 
                                    [=](const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& p1,
                                        const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& p2)
                                        {
                                            cb->opByteRange(p1, p2, newInParam(inPair));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(inPair));
                                        });
            cb->check();
        }

        {
            Test::VariableList in;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            v.s = "are";
            in.push_back(v);
            v.s = "five";
            in.push_back(v);
            v.s = "short";
            in.push_back(v);
            v.s = "strings.";
            in.push_back(v);
            pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            t->begin_opVariableRange(inPair, 
                                        [=](const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& p1,
                                            const pair<Test::VariableList::const_iterator, Test::VariableList::const_iterator>& p2)
                                            {
                                                cb->opVariableRange(p1, p2, newInParam(inPair));
                                            },
                                        [=](const Ice::Exception& ex)
                                            {
                                                cb->noEx(ex, newInParam(inPair));
                                            });
            cb->check();
        }

        {
            Test::BoolSeq in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;
            bool inArray[5];
            for(int i = 0; i < 5; ++i)
            {
                inArray[i] = in[i];
            }
            pair<const bool*, const bool*> inPair(inArray, inArray + 5);

            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opBoolRangeTypePtr callback = 
                Test::newCallback_TestIntf_opBoolRangeType(cb, &Callback::opBoolRangeType, &Callback::noEx);
            t->begin_opBoolRangeType(inPair, callback, newInParam(inPair));
            cb->check();
        }

        {
            Test::ByteList in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');
            pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator> inPair(in.begin(), in.end());

            CallbackPtr cb = new Callback();
            t->begin_opByteRangeType(inPair, 
                                        [=](const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& p1,
                                            const pair<Test::ByteList::const_iterator, Test::ByteList::const_iterator>& p2)
                                            {
                                                cb->opByteRangeType(p1, p2, newInParam(inPair));
                                            },
                                        [=](const Ice::Exception& ex)
                                            {
                                                cb->noEx(ex, newInParam(inPair));
                                            });
            cb->check();
        }

        {
            Test::VariableList in;
            deque<Test::Variable> inSeq;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "are";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "five";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "short";
            in.push_back(v);
            inSeq.push_back(v);
            v.s = "strings.";
            in.push_back(v);
            inSeq.push_back(v);
            pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator> inPair(inSeq.begin(), 
                                                                                                    inSeq.end());

            CallbackPtr cb = new Callback();
            t->begin_opVariableRangeType(inPair, 
                                        [=](const pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator>& p1,
                                            const pair<deque<Test::Variable>::const_iterator, deque<Test::Variable>::const_iterator>& p2)
                                            {
                                                cb->opVariableRangeType(p1, p2, newInParam(inPair));
                                            },
                                         [=](const Ice::Exception& ex)
                                            {
                                                cb->noEx(ex, newInParam(inPair));
                                            });
            cb->check();
        }

        {
            deque<bool> in(5);
            in[0] = false;
            in[1] = true;
            in[2] = true;
            in[3] = false;
            in[4] = true;

            CallbackPtr cb = new Callback();
            t->begin_opBoolSeq(in, 
                                [=](const deque<bool>& p1, const deque<bool>& p2)
                                    {
                                        cb->opBoolSeq(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            list<bool> in;
            in.push_back(false);
            in.push_back(true);
            in.push_back(true);
            in.push_back(false);
            in.push_back(true);

            CallbackPtr cb = new Callback();
            t->begin_opBoolList(in,
                                [=](const list<bool>& p1, const list<bool>& p2)
                                    {
                                        cb->opBoolList(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            deque< ::Ice::Byte> in(5);
            in[0] = '1';
            in[1] = '2';
            in[2] = '3';
            in[3] = '4';
            in[4] = '5';

            CallbackPtr cb = new Callback();
            t->begin_opByteSeq(in, 
                                [=](const deque< ::Ice::Byte>& p1, const deque< ::Ice::Byte>& p2)
                                    {
                                        cb->opByteSeq(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            list< ::Ice::Byte> in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            in.push_back('5');

            CallbackPtr cb = new Callback();
            t->begin_opByteList(in, 
                                [=](const list< ::Ice::Byte>& p1, const list< ::Ice::Byte>& p2)
                                    {
                                        cb->opByteList(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            MyByteSeq in(5);
            int i = 0;
            for(MyByteSeq::iterator p = in.begin(); p != in.end(); ++p)
            {
                *p = '1' + i++;
            }

            CallbackPtr cb = new Callback();
            t->begin_opMyByteSeq(in,
                                    [=](const MyByteSeq& p1, const MyByteSeq& p2)
                                        {
                                            cb->opMyByteSeq(p1, p2, newInParam(in));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(in));
                                        });
            cb->check();
        }

        {
            deque<string> in(5);
            in[0] = "These";
            in[1] = "are";
            in[2] = "five";
            in[3] = "short";
            in[4] = "strings.";

            CallbackPtr cb = new Callback();
            t->begin_opStringSeq(in, 
                                    [=](const deque<string>& p1, const deque<string>& p2)
                                        {
                                            cb->opStringSeq(p1, p2, newInParam(in));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(in));
                                        });
            cb->check();
        }

        {
            list<string> in;
            in.push_back("These");
            in.push_back("are");
            in.push_back("five");
            in.push_back("short");
            in.push_back("strings.");

            CallbackPtr cb = new Callback();
            t->begin_opStringList(in,
                                    [=](const list<string>& p1, const list<string>& p2)
                                        {
                                            cb->opStringList(p1, p2, newInParam(in));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(in));
                                        });
            cb->check();
        }

        {
            deque<Test::Fixed> in(5);
            in[0].s = 1;
            in[1].s = 2;
            in[2].s = 3;
            in[3].s = 4;
            in[4].s = 5;

            CallbackPtr cb = new Callback();
            t->begin_opFixedSeq(in, 
                                [=](const deque<Test::Fixed>& p1, const deque<Test::Fixed>& p2)
                                    {
                                        cb->opFixedSeq(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            list<Test::Fixed> in(5);
            short num = 1;
            for(list<Test::Fixed>::iterator p = in.begin(); p != in.end(); ++p)
            {
                (*p).s = num++;
            }

            CallbackPtr cb = new Callback();
            t->begin_opFixedList(in,
                                    [=](const list<Test::Fixed> p1, const list<Test::Fixed> p2)
                                        {
                                            cb->opFixedList(p1, p2, newInParam(in));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(in));
                                        });
            cb->check();
        }

        {
            deque<Test::Variable> in(5);
            in[0].s = "These";
            in[1].s = "are";
            in[2].s = "five";
            in[3].s = "short";
            in[4].s = "strings.";

            CallbackPtr cb = new Callback();
            t->begin_opVariableSeq(in,
                                    [=](const deque<Test::Variable>& p1, const deque<Test::Variable>& p2)
                                        {
                                            cb->opVariableSeq(p1, p2, newInParam(in));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(in));
                                        });
            cb->check();
        }

        {
            list<Test::Variable> in;
            Test::Variable v;
            v.s = "These";
            in.push_back(v);
            v.s = "are";
            in.push_back(v);
            v.s = "five";
            in.push_back(v);
            v.s = "short";
            in.push_back(v);
            v.s = "strings.";
            in.push_back(v);

            CallbackPtr cb = new Callback();
            t->begin_opVariableList(in,
                                    [=](const list<Test::Variable>& p1, const list<Test::Variable>& p2)
                                        {
                                            cb->opVariableList(p1, p2, newInParam(in));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(in));
                                        });
            cb->check();
        }

        {
            deque<Test::StringStringDict> in(5);
            in[0]["A"] = "a";
            in[1]["B"] = "b";
            in[2]["C"] = "c";
            in[3]["D"] = "d";
            in[4]["E"] = "e";

            CallbackPtr cb = new Callback();
            t->begin_opStringStringDictSeq(in,
                                            [=](const deque<Test::StringStringDict>& p1, const deque<Test::StringStringDict>& p2)
                                                {
                                                    cb->opStringStringDictSeq(p1, p2, newInParam(in));
                                                },
                                            [=](const Ice::Exception& ex)
                                                {
                                                    cb->noEx(ex, newInParam(in));
                                                });
            cb->check();
        }

        {
            list<Test::StringStringDict> in;
            Test::StringStringDict ssd;
            ssd["A"] = "a";
            in.push_back(ssd);
            ssd["B"] = "b";
            in.push_back(ssd);
            ssd["C"] = "c";
            in.push_back(ssd);
            ssd["D"] = "d";
            in.push_back(ssd);
            ssd["E"] = "e";
            in.push_back(ssd);

            CallbackPtr cb = new Callback();
            t->begin_opStringStringDictList(in,
                                            [=](const list<Test::StringStringDict>& p1, 
                                                const list<Test::StringStringDict>& p2)
                                                {
                                                    cb->opStringStringDictList(p1, p2, newInParam(in));
                                                },
                                            [=](const Ice::Exception& ex)
                                                {
                                                    cb->noEx(ex, newInParam(in));
                                                });
            cb->check();
        }

        {
            deque<Test::E> in(5);
            in[0] = Test::E1;
            in[1] = Test::E2;
            in[2] = Test::E3;
            in[3] = Test::E1;
            in[4] = Test::E3;

            CallbackPtr cb = new Callback();
            t->begin_opESeq(in,
                            [=](const deque<Test::E>& p1, const deque<Test::E>& p2)
                                {
                                    cb->opESeq(p1, p2, newInParam(in));
                                },
                            [=](const Ice::Exception& ex)
                                {
                                    cb->noEx(ex, newInParam(in));
                                });
            cb->check();
        }

        {
            list<Test::E> in;
            in.push_back(Test::E1);
            in.push_back(Test::E2);
            in.push_back(Test::E3);
            in.push_back(Test::E1);
            in.push_back(Test::E3);

            CallbackPtr cb = new Callback();
            t->begin_opEList(in,
                                [=](const list<Test::E>& p1, const list<Test::E>& p2)
                                    {
                                        cb->opEList(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            deque<Test::CPrx> in(5);
            in[0] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000"));
            in[1] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001"));
            in[2] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002"));
            in[3] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003"));
            in[4] = Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004"));

            CallbackPtr cb = new Callback();
            t->begin_opCPrxSeq(in,
                                [=](const deque<Test::CPrx>& p1, const deque<Test::CPrx>& p2)
                                    {
                                        cb->opCPrxSeq(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            list<Test::CPrx> in;
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C1:default -p 12010 -t 10000")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C2:default -p 12010 -t 10001")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C3:default -p 12010 -t 10002")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C4:default -p 12010 -t 10003")));
            in.push_back(Test::CPrx::uncheckedCast(communicator->stringToProxy("C5:default -p 12010 -t 10004")));

            CallbackPtr cb = new Callback();
            t->begin_opCPrxList(in,
                                [=](const list<Test::CPrx>& p1, const list<Test::CPrx>& p2)
                                    {
                                        cb->opCPrxList(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }

        {
            deque<Test::CPtr> in(5);
            in[0] = new Test::C();
            in[1] = in[0];
            in[2] = in[0];
            in[3] = in[0];
            in[4] = in[0];

            CallbackPtr cb = new Callback();
            t->begin_opCSeq(in,
                            [=](const deque<Test::CPtr>& p1, const deque<Test::CPtr>& p2)
                                {
                                    cb->opCSeq(p1, p2, newInParam(in));
                                },
                            [=](const Ice::Exception& ex)
                                {
                                    cb->noEx(ex, newInParam(in));
                                });
            cb->check();
        }
    
        {
            list<Test::CPtr> in;
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());
            in.push_back(new Test::C());

            CallbackPtr cb = new Callback();
            t->begin_opCList(in,
                                [=](const list<Test::CPtr>& p1, const list<Test::CPtr>& p2)
                                    {
                                        cb->opCList(p1, p2, newInParam(in));
                                    },
                                [=](const Ice::Exception& ex)
                                    {
                                        cb->noEx(ex, newInParam(in));
                                    });
            cb->check();
        }
        
        
        {
            Test::ByteSeq in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            
            CallbackPtr cb = new Callback();
            t->begin_opOutArrayByteSeq(in,
                                        [=](const ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*>& p1)
                                            {
                                                cb->opOutArrayByteSeq(p1, newInParam(in));
                                            },
                                        [=](const Ice::Exception& ex)
                                            {
                                                cb->noEx(ex, newInParam(in));
                                            });
            cb->check();
        }
        
        {
            Test::ByteSeq in;
            in.push_back('1');
            in.push_back('2');
            in.push_back('3');
            in.push_back('4');
            
            CallbackPtr cb = new Callback();
            t->begin_opOutRangeByteSeq(in,
                                        [=](const ::std::pair< ::Test::ByteSeq::const_iterator, ::Test::ByteSeq::const_iterator>& p1)
                                            {
                                                cb->opOutRangeByteSeq(p1, newInParam(in));
                                            },
                                        [=](const Ice::Exception& ex)
                                            {
                                                cb->noEx(ex, newInParam(in));
                                            });
            cb->check();
        }
        cout << "ok" << endl;
#endif

        cout << "testing alternate dictionaries with new AMI... " << flush;
        {
            {
                Test::IntStringDict idict;
                
                idict[1] = "one";
                idict[2] = "two";
                idict[3] = "three";
                idict[-1] = "minus one";
                
                Test::IntStringDict out;
                out[5] = "five";
                
                Ice::AsyncResultPtr r = t->begin_opIntStringDict(idict);
                Test::IntStringDict ret = t->end_opIntStringDict(out, r);
                test(out == idict);
                test(ret == idict);
            }

            {
                Test::CustomMap<std::string, Ice::Int> idict;
                
                idict["one"] = 1;
                idict["two"] = 2;
                idict["three"] = 3;
                idict["minus one"] = -1;
                
                Test::CustomMap<std::string, Ice::Int> out;
                out["five"] = 5;
                
                Ice::AsyncResultPtr r = t->begin_opVarDict(idict);
                Test::CustomMap<Ice::Long, Ice::Long> ret = t->end_opVarDict(out, r);
#if defined(_MSC_VER) && (_MSC_VER == 1600)
                //
                // operator== for std::unordered_map does not work with Visual Studio 2010
                //
                test(out.size() == idict.size());
        
                for(Test::CustomMap<std::string, Ice::Int>::iterator p = idict.begin(); p != idict.end(); ++p)
                {
                    test(out[p->first] == p->second);
                } 
#else
                test(out == idict);
#endif
                test(ret.size() == 1000);
                for(Test::CustomMap<Ice::Long, Ice::Long>::const_iterator i = ret.begin(); i != ret.end(); ++i)
                {
                    test(i->second == i->first * i->first);
                }
            }
        }
        cout << "ok" << endl;
        
        cout << "testing alternate dictionaries with new AMI callbacks... " << flush;
        {
            {
                Test::IntStringDict idict;
                
                idict[1] = "one";
                idict[2] = "two";
                idict[3] = "three";
                idict[-1] = "minus one";
                
                Test::IntStringDict out;
                out[5] = "five";
                
                CallbackPtr cb = new Callback();
                Test::Callback_TestIntf_opIntStringDictPtr callback = 
                    Test::newCallback_TestIntf_opIntStringDict(cb, &Callback::opIntStringDict, &Callback::noEx);
                t->begin_opIntStringDict(idict, callback, newInParam(idict));
                cb->check();
            }

            {
                Test::CustomMap<std::string, Ice::Int> idict;
                
                idict["one"] = 1;
                idict["two"] = 2;
                idict["three"] = 3;
                idict["minus one"] = -1;
                
                Test::CustomMap<std::string, Ice::Int> out;
                out["five"] = 5;
                
                CallbackPtr cb = new Callback();
                Test::Callback_TestIntf_opVarDictPtr callback = 
                    Test::newCallback_TestIntf_opVarDict(cb, &Callback::opVarDict, &Callback::noEx);
                t->begin_opVarDict(idict, callback, newInParam(idict));
                cb->check();
            }
        }
        cout << "ok" << endl;

#ifdef ICE_CPP11  
        cout << "testing alternate dictionaries with new C++11 AMI callbacks... " << flush;
        {
            {
                Test::IntStringDict idict;
                
                idict[1] = "one";
                idict[2] = "two";
                idict[3] = "three";
                idict[-1] = "minus one";
                
                Test::IntStringDict out;
                out[5] = "five";
                
                CallbackPtr cb = new Callback();
                
                t->begin_opIntStringDict(idict, 
                                         [=](const Test::IntStringDict& ret, const Test::IntStringDict& out)
                                         {
                                             cb->opIntStringDict(ret, out, newInParam(idict));
                                         },
                                         [=](const Ice::Exception& ex)
                                         {
                                             cb->noEx(ex, newInParam(idict));
                                         });               
                cb->check();
            }

            {
                Test::CustomMap<std::string, Ice::Int> idict;
                
                idict["one"] = 1;
                idict["two"] = 2;
                idict["three"] = 3;
                idict["minus one"] = -1;
                
                Test::CustomMap<std::string, Ice::Int> out;
                out["five"] = 5;
                
                CallbackPtr cb = new Callback();
                
                t->begin_opVarDict(idict, 
                                   [=](const Test::CustomMap<Ice::Long, Ice::Long>& ret, 
                                       const Test::CustomMap<std::string, Ice::Int>& out)
                                   {
                                       cb->opVarDict(ret, out, newInParam(idict));
                                   },
                                   [=](const Ice::Exception& ex)
                                   {
                                       cb->noEx(ex, newInParam(idict));
                                   });               
                cb->check();
            }
        }
        cout << "ok" << endl;
#endif
    }

    cout << "testing class mapped structs ... " << flush;
    Test::ClassStructPtr cs = new Test::ClassStruct();
    cs->y = 10;
    cs->other = new Test::ClassOtherStruct;
    cs->other->x = 20;
    cs->otherSeq.push_back(new Test::ClassOtherStruct);
    cs->otherSeq[0]->x = 30;
    cs->otherSeq.push_back(new Test::ClassOtherStruct);
    cs->otherSeq[1]->x = 40;
    Test::ClassStructSeq csseq1;
    csseq1.push_back(cs);
    Test::ClassStructPtr cs2;
    Test::ClassStructSeq csseq2;
    Test::ClassStructPtr cs3 = t->opClassStruct(cs, csseq1, cs2, csseq2);
    assert(cs3 == cs);
    assert(csseq1.size() == csseq2.size());
    assert(csseq1[0] == csseq2[0]);
    cout << "ok" << endl;

    if(!collocated)
    {
        cout << "testing class mapped structs with AMI... " << flush;
        {
            AMI_TestIntf_opClassStructIPtr cb = new AMI_TestIntf_opClassStructI(cs, csseq1);
            t->opClassStruct_async(cb, cs, csseq1);
            cb->check();
        }
        cout << "ok" << endl;

        cout << "testing class mapped structs with new AMI... " << flush;
        {
            Test::ClassStructPtr cs2;
            Test::ClassStructSeq csseq2;
            Ice::AsyncResultPtr r = t->begin_opClassStruct(cs, csseq1);
            Test::ClassStructPtr cs3 = t->end_opClassStruct(cs2, csseq2, r);
            assert(cs3 == cs);
            assert(csseq1.size() == csseq2.size());
            assert(csseq1[0] == csseq2[0]);
        }
        {
            CallbackPtr cb = new Callback();
            Test::Callback_TestIntf_opClassStructPtr callback = 
                Test::newCallback_TestIntf_opClassStruct(cb, &Callback::opClassStruct, &Callback::noEx);
            t->begin_opClassStruct(cs, csseq1, callback, newInParam(make_pair(cs, csseq1)));
            cb->check();
        }
        cout << "ok" << endl;
#ifdef ICE_CPP11
        cout << "testing class mapped structs with C++11 AMI... " << flush;
        {
            CallbackPtr cb = new Callback();
            t->begin_opClassStruct(cs, csseq1,
                                    [=](const ::Test::ClassStructPtr& p1,
                                        const ::Test::ClassStructPtr& p2,
                                        const ::Test::ClassStructSeq& p3)
                                        {
                                            cb->opClassStruct(p1, p2, p3, newInParam(make_pair(cs, csseq1)));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(make_pair(cs, csseq1)));
                                        });
            cb->check();
        }
        cout << "ok" << endl;
#endif
    }

    cout << "testing wstring... " << flush;

    Test1::WstringSeq wseq1;
    wseq1.push_back(L"Wide String");

    Test2::WstringSeq wseq2;
    wseq2 = wseq1;

    Test1::WstringWStringDict wdict1;
    wdict1[L"Key"] = L"Value";

    Test2::WstringWStringDict wdict2;
    wdict2 = wdict1;

    ref = communicator->getProperties()->getPropertyWithDefault("Custom.WstringProxy1", "wstring1:default -p 12010");
    base = communicator->stringToProxy(ref);
    test(base);
    Test1::WstringClassPrx wsc1 = Test1::WstringClassPrx::checkedCast(base);
    test(t);

    ref = communicator->getProperties()->getPropertyWithDefault("Custom.WstringProxy2", "wstring2:default -p 12010");
    base = communicator->stringToProxy(ref);
    test(base);
    Test2::WstringClassPrx wsc2 = Test2::WstringClassPrx::checkedCast(base);
    test(t);

    wstring wstr = L"A Wide String";
    wstring out;
    wstring ret = wsc1->opString(wstr, out);
    test(out == wstr);
    test(ret == wstr);

    if(!collocated)
    {
        {
            AMI_Test1_opStringIPtr cb = new AMI_Test1_opStringI(wstr);
            wsc1->opString_async(cb, wstr);
            cb->check();
        }
        {
            Ice::AsyncResultPtr r = wsc1->begin_opString(wstr);
            wstring out;
            wstring ret = wsc1->end_opString(out, r);
            test(out == wstr);
            test(ret == wstr);
        }
        {
            CallbackPtr cb = new Callback();
            wsc1->begin_opString(wstr, Test1::newCallback_WstringClass_opString(cb, &Callback::opString, &Callback::noEx),
                                 newInParam(wstr));
            cb->check();
        }
#ifdef ICE_CPP11
        {
            CallbackPtr cb = new Callback();
            wsc1->begin_opString(wstr,
                                    [=](const wstring& p1, const wstring& p2)
                                        {
                                            cb->opString(p1, p2, newInParam(wstr));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(wstr));
                                        });
            cb->check();
        }
#endif
    }

    ret = wsc2->opString(wstr, out);
    test(out == wstr);
    test(ret == wstr);

    if(!collocated)
    {
        {
            AMI_Test2_opStringIPtr cb = new AMI_Test2_opStringI(wstr);
            wsc2->opString_async(cb, wstr);
            cb->check();
        }
        {
            Ice::AsyncResultPtr r = wsc2->begin_opString(wstr);
            wstring out;
            wstring ret = wsc2->end_opString(out, r);
            test(out == wstr);
            test(ret == wstr);
        }
        {
            CallbackPtr cb = new Callback();
            wsc2->begin_opString(wstr, Test2::newCallback_WstringClass_opString(cb, &Callback::opString, 
                                                                                &Callback::noEx), newInParam(wstr));
            cb->check();
        }
        {
            CallbackPtr cb = new Callback();
            wsc2->begin_opString(wstr, Test2::newCallback_WstringClass_opString(cb, &Callback::opString, 
                                                                                &Callback::noEx), newInParam(wstr));
            cb->check();
        }
#ifdef ICE_CPP11
        {
            CallbackPtr cb = new Callback();
            wsc2->begin_opString(wstr,
                                    [=](const wstring& p1, const wstring& p2)
                                        {
                                            cb->opString(p1, p2, newInParam(wstr));
                                        },
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->noEx(ex, newInParam(wstr));
                                        });
            cb->check();
        }
#endif
    }

    Test1::WstringStruct wss1;
    wss1.s = wstr;
    Test1::WstringStruct wss1out;
    Test1::WstringStruct wss1ret = wsc1->opStruct(wss1, wss1out);
    test(wss1out == wss1);
    test(wss1ret == wss1);

    Test2::WstringStruct wss2;
    wss2.s = wstr;
    Test2::WstringStruct wss2out;
    Test2::WstringStruct wss2ret = wsc2->opStruct(wss2, wss2out);
    test(wss2out == wss2);
    test(wss2ret == wss2);

    try
    {
        wsc1->throwExcept(wstr);
    }
    catch(const Test1::WstringException& ex)
    {
        test(ex.reason == wstr);
    }

    if(!collocated)
    {
        {
            AMI_Test1_throwExceptIPtr cb = new AMI_Test1_throwExceptI(wstr);
            wsc1->throwExcept_async(cb, wstr);
            cb->check();
        }
        {
            Ice::AsyncResultPtr r = wsc1->begin_throwExcept(wstr);
            try
            {
                wsc1->end_throwExcept(r);
                test(false);
            }
            catch(const Test1::WstringException& ex)
            {
                test(ex.reason == wstr);
            }
        }
        {
            CallbackPtr cb = new Callback();
            wsc1->begin_throwExcept(wstr, Ice::newCallback(cb, &Callback::throwExcept1), newInParam(wstr));
            cb->check();
        }
#ifdef ICE_CPP11
        {
            CallbackPtr cb = new Callback();
            wsc1->begin_throwExcept(wstr, nullptr,
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->throwExcept1(ex, wstr);
                                        });
            cb->check();
        }
#endif
    }

    try
    {
        wsc2->throwExcept(wstr);
    }
    catch(const Test2::WstringException& ex)
    {
        test(ex.reason == wstr);
    }

    if(!collocated)
    {
        {
            AMI_Test2_throwExceptIPtr cb = new AMI_Test2_throwExceptI(wstr);
            wsc2->throwExcept_async(cb, wstr);
            cb->check();
        }
        {
            Ice::AsyncResultPtr r = wsc2->begin_throwExcept(wstr);
            try
            {
                wsc2->end_throwExcept(r);
                test(false);
            }
            catch(const Test2::WstringException& ex)
            {
                test(ex.reason == wstr);
            }
        }
        {
            CallbackPtr cb = new Callback();
            wsc2->begin_throwExcept(wstr, Ice::newCallback(cb, &Callback::throwExcept2), newInParam(wstr));
            cb->check();
        }
#ifdef ICE_CPP11
        {
            CallbackPtr cb = new Callback();
            wsc2->begin_throwExcept(wstr, nullptr,
                                    [=](const Ice::Exception& ex)
                                        {
                                            cb->throwExcept2(ex, wstr);
                                        });
            cb->check();
        }
#endif
    }

    cout << "ok" << endl;

    return t;
}
