
// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/LoggerUtil.h>
#include <Ice/Logger.h>
#include <Ice/Plugin.h>
#include <Ice/LocalException.h>
#include <Ice/Instance.h>

using namespace std;

namespace IceUtilInternal
{

extern bool ICE_DECLSPEC_IMPORT printStackTraces;

}

string
Ice::LoggerOutputBase::str() const
{
    return _str.str();
}

ostringstream&
Ice::LoggerOutputBase::__str()
{
    return _str;
}

Ice::LoggerOutputBase&
Ice::operator<<(Ice::LoggerOutputBase& out, ios_base& (*val)(ios_base&))
{
    out.__str() << val;
    return out;
}

Ice::LoggerOutputBase&
Ice::operator<<(Ice::LoggerOutputBase& out, const std::exception& ex)
{
    if(IceUtilInternal::printStackTraces)
    {
        const ::IceUtil::Exception* exception = dynamic_cast<const ::IceUtil::Exception*>(&ex);
        if(exception)
        {
            out.__str() << exception->what() << '\n' << exception->ice_stackTrace();
            return out;
        }
    }
    out.__str() << ex.what();
    return out;
}


Ice::Trace::Trace(const LoggerPtr& logger, const string& category) :
    _logger(logger),
    _category(category)
{
}

Ice::Trace::~Trace()
{
    flush();
}

void
Ice::Trace::flush()
{
    string s = __str().str();
    if(!s.empty())
    {
        _logger->trace(_category, s);
    }
    __str().str("");
}


Ice::LoggerPlugin::LoggerPlugin(const CommunicatorPtr& communicator, const LoggerPtr& logger)
{
    if(communicator == 0)
    {
        throw PluginInitializationException(__FILE__, __LINE__, "Communicator cannot be null");
    }

    if(logger == 0)
    {
        throw PluginInitializationException(__FILE__, __LINE__, "Logger cannot be null");
    }

    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    instance->setLogger(logger);
}

void
Ice::LoggerPlugin::initialize()
{
}

void
Ice::LoggerPlugin::destroy()
{
}
