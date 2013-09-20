// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_GRID_UTIL_H
#define ICE_GRID_UTIL_H

#include <IceGrid/Descriptor.h>
#include <IceUtil/StringUtil.h>
#include <IceGrid/Exception.h>
#include <IceGrid/Admin.h>
#include <IceUtil/Random.h>
#include <functional>
#include <iterator>

namespace IceGrid
{

struct RandomNumberGenerator : public std::unary_function<ptrdiff_t, ptrdiff_t>
{
    ptrdiff_t operator()(ptrdiff_t d)
    {
        return IceUtilInternal::random(static_cast<int>(d));
    }
};


template<typename T> std::insert_iterator<T>
inline set_inserter(T& container) 
{ 
    return std::insert_iterator<T>(container, container.begin()); 
}

std::string toString(const std::vector<std::string>&, const std::string& = std::string(" "));
std::string toString(const Ice::Exception&);

std::string getProperty(const PropertyDescriptorSeq&, const std::string&, const std::string& = std::string());
bool hasProperty(const PropertyDescriptorSeq&, const std::string&);
PropertyDescriptor createProperty(const std::string&, const std::string& = std::string());
std::string escapeProperty(const std::string&, bool = false);

ObjectInfo toObjectInfo(const Ice::CommunicatorPtr&, const ObjectDescriptor&, const std::string&);

void setupThreadPool(const Ice::PropertiesPtr&, const std::string&, int, int = 0, bool = false);

int getMMVersion(const std::string&);

template<class Function>
struct ForEachCommunicator : std::unary_function<CommunicatorDescriptorPtr&, void>
{
    ForEachCommunicator(Function f) : _function(f)
    {
    }

    void
    operator()(const ServiceInstanceDescriptor& descriptor)
    {
        assert(descriptor.descriptor);
        operator()(descriptor.descriptor);
    }

    void
    operator()(const CommunicatorDescriptorPtr& descriptor)
    {
        _function(descriptor);
        IceBoxDescriptorPtr iceBox = IceBoxDescriptorPtr::dynamicCast(descriptor);
        if(iceBox)
        {
            for_each(iceBox->services.begin(), iceBox->services.end(), forEachCommunicator(_function));
        }
    }

    Function _function;
};

template<typename Function> ForEachCommunicator<Function>
inline forEachCommunicator(Function function) 
{ 
    return ForEachCommunicator<Function>(function);
}

template<class T, class A>
struct ObjFunc : std::unary_function<A, void>
{
    T& _obj;
    typedef void (T::*MemberFN)(A);
    MemberFN _mfn;

public:

     explicit ObjFunc(T& obj, void (T::*f)(A)) : _obj(obj), _mfn(f) { }
    void operator()(A arg) const
    {
        (_obj.*_mfn)(arg);
    }
};

template<class T, class A> ObjFunc<T, A>
inline objFunc(T& obj, void (T::*p)(A))
{ 
    return ObjFunc<T, A>(obj, p);
}

template <class T> std::vector<std::string>
inline getMatchingKeys(const T& m, const std::string& expression)
{
    std::vector<std::string> keys;
    for(typename T::const_iterator p = m.begin(); p != m.end(); ++p)
    {
        if(expression.empty() || IceUtilInternal::match(p->first, expression, true))
        {
            keys.push_back(p->first);
        }
    }
    return keys;
}

};

#endif
