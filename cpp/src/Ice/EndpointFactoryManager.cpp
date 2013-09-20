// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/EndpointFactoryManager.h>
#include <Ice/Endpoint.h>
#include <Ice/OpaqueEndpointI.h>
#include <Ice/BasicStream.h>
#include <Ice/LocalException.h>
#include <Ice/Instance.h>
#include <Ice/Properties.h>
#include <Ice/DefaultsAndOverrides.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

IceUtil::Shared* IceInternal::upCast(EndpointFactoryManager* p) { return p; }

IceInternal::EndpointFactoryManager::EndpointFactoryManager(const InstancePtr& instance)
    : _instance(instance)
{
}

void
IceInternal::EndpointFactoryManager::add(const EndpointFactoryPtr& factory)
{
    IceUtil::Mutex::Lock sync(*this); // TODO: Necessary?

    //
    // TODO: Optimize with a map?
    //
    for(vector<EndpointFactoryPtr>::size_type i = 0; i < _factories.size(); i++)
    {
        if(_factories[i]->type() == factory->type())
        {
            assert(false); // TODO: Exception?
        }
    }
    _factories.push_back(factory);
}

EndpointFactoryPtr
IceInternal::EndpointFactoryManager::get(Short type) const
{
    IceUtil::Mutex::Lock sync(*this); // TODO: Necessary?

    //
    // TODO: Optimize with a map?
    //
    for(vector<EndpointFactoryPtr>::size_type i = 0; i < _factories.size(); i++)
    {
        if(_factories[i]->type() == type)
        {
            return _factories[i];
        }
    }
    return 0;
}

EndpointIPtr
IceInternal::EndpointFactoryManager::create(const string& str, bool oaEndpoint) const
{
    const string delim = " \t\n\r";

    string::size_type beg = str.find_first_not_of(delim);
    if(beg == string::npos)
    {
        EndpointParseException ex(__FILE__, __LINE__);
        ex.str = "value has no non-whitespace characters";
        throw ex;
    }

    string::size_type end = str.find_first_of(delim, beg);
    if(end == string::npos)
    {
        end = str.length();
    }

    string protocol = str.substr(beg, end - beg);

    if(protocol == "default")
    {
        protocol = _instance->defaultsAndOverrides()->defaultProtocol;
    }

    EndpointFactoryPtr factory;
    {
        IceUtil::Mutex::Lock sync(*this); // TODO: Necessary?
        
        //
        // TODO: Optimize with a map?
        //
        for(vector<EndpointFactoryPtr>::size_type i = 0; i < _factories.size(); i++)
        {
            if(_factories[i]->protocol() == protocol)
            {
                factory = _factories[i];
            }
        }
    }

    if(factory)
    {
#if 1
        return factory->create(str.substr(end), oaEndpoint);
#else
        // Code below left in place for debugging.

        EndpointIPtr e = factory->create(str.substr(end), oaEndpoint);
        BasicStream bs(_instance.get(), Ice::currentProtocolEncoding);
        e->streamWrite(&bs);
        bs.i = bs.b.begin();
        short type;
        bs.read(type);
        EndpointIPtr ue = new IceInternal::OpaqueEndpointI(type, &bs);
        cerr << "Normal: " << e->toString() << endl;
        cerr << "Opaque: " << ue->toString() << endl;
        return e;
#endif
    }

    //
    // If the stringified endpoint is opaque, create an unknown endpoint,
    // then see whether the type matches one of the known endpoints.
    //
    if(protocol == "opaque")
    {
        EndpointIPtr ue = new OpaqueEndpointI(str.substr(end));
        factory = get(ue->type());
        if(factory)
        {
            //
            // Make a temporary stream, write the opaque endpoint data into the stream,
            // and ask the factory to read the endpoint data from that stream to create
            // the actual endpoint.
            //
            BasicStream bs(_instance.get(), Ice::currentProtocolEncoding);
            ue->streamWrite(&bs);
            bs.i = bs.b.begin();
            short type;
            bs.read(type);
            return factory->read(&bs);
        }
        return ue; // Endpoint is opaque, but we don't have a factory for its type.
    }

    return 0;
}

EndpointIPtr
IceInternal::EndpointFactoryManager::read(BasicStream* s) const
{
    Short type;
    s->read(type);

    EndpointFactoryPtr factory = get(type);
    if(factory)
    {
        return factory->read(s);
    }

    return new OpaqueEndpointI(type, s);
}

void
IceInternal::EndpointFactoryManager::destroy()
{
    for(vector<EndpointFactoryPtr>::size_type i = 0; i < _factories.size(); i++)
    {
        _factories[i]->destroy();
    }
    _factories.clear();
}
