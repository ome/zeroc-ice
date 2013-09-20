// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_CONNECTION_ASYNC_H
#define ICE_CONNECTION_ASYNC_H

#include <Ice/Connection.h>
#include <Ice/Proxy.h>

namespace Ice
{

template<class T>
class CallbackNC_Connection_flushBatchRequests : public Callback_Connection_flushBatchRequests_Base,
                                                 public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);

    CallbackNC_Connection_flushBatchRequests(const TPtr& obj, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, 0, excb, sentcb)
    {
    }

    virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Ice::ConnectionPtr __con = __result->getConnection();
        assert(__con);
        try
        {
            __con->end_flushBatchRequests(__result);
            assert(false);
        }
        catch(::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::__exception(__result, ex);
        }
    }
};

#ifdef ICE_CPP11
class Cpp11FnCallbackNC_Connection_flushBatchRequests : virtual public ::IceInternal::Cpp11FnCallbackNC
{
public:
    
    Cpp11FnCallbackNC_Connection_flushBatchRequests(const ::IceInternal::Function<void (const ::Ice::Exception&)>& excb,
                            const ::IceInternal::Function<void (bool)>& sentcb) :
        ::IceInternal::Cpp11FnCallbackNC(excb, sentcb)
    {
        CallbackBase::checkCallback(true, excb != nullptr);
    }
    
    virtual void
    __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Ice::ConnectionPtr __con = __result->getConnection();
        assert(__con);
        try
        {
            __con->end_flushBatchRequests(__result);
            assert(false);
        }
        catch(::Ice::Exception& ex)
        {
            ::IceInternal::Cpp11FnCallbackNC::__exception(__result, ex);
        }
    }
};
#endif

template<class T> Callback_Connection_flushBatchRequestsPtr
newCallback_Connection_flushBatchRequests(const IceUtil::Handle<T>& instance,
                                          void (T::*excb)(const ::Ice::Exception&),
                                          void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Connection_flushBatchRequests<T>(instance, excb, sentcb);
}

template<class T> Callback_Connection_flushBatchRequestsPtr
newCallback_Connection_flushBatchRequests(T* instance, void (T::*excb)(const ::Ice::Exception&),
                                          void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Connection_flushBatchRequests<T>(instance, excb, sentcb);
}

template<class T, typename CT>
class Callback_Connection_flushBatchRequests : public Callback_Connection_flushBatchRequests_Base,
                                               public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);

    Callback_Connection_flushBatchRequests(const TPtr& obj, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, 0, excb, sentcb)
    {
    }

    virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Ice::ConnectionPtr __con = __result->getConnection();
        assert(__con);
        try
        {
            __con->end_flushBatchRequests(__result);
            assert(false);
        }
        catch(::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::__exception(__result, ex);
        }
    }
};

template<class T, typename CT> Callback_Connection_flushBatchRequestsPtr
newCallback_Connection_flushBatchRequests(const IceUtil::Handle<T>& instance,
                                          void (T::*excb)(const ::Ice::Exception&, const CT&),
                                          void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Connection_flushBatchRequests<T, CT>(instance, excb, sentcb);
}

template<class T, typename CT> Callback_Connection_flushBatchRequestsPtr
newCallback_Connection_flushBatchRequests(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&),
                                          void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Connection_flushBatchRequests<T, CT>(instance, excb, sentcb);
}

}

#endif
