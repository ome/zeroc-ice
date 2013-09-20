// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <EndpointI.h>
#include <Transceiver.h>
#include <Connector.h>
#include <Acceptor.h>
#include <Ice/BasicStream.h>

#ifdef _MSC_VER
// For 'Ice::Object::ice_getHash': was declared deprecated
#pragma warning( disable : 4996 )
#endif

#if defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

using namespace std;

Ice::Short EndpointI::TYPE_BASE = 100;
 
EndpointI::EndpointI(const IceInternal::EndpointIPtr& endpoint) : 
    _endpoint(endpoint),
    _configuration(Configuration::getInstance())
{
}

void
EndpointI::streamWrite(IceInternal::BasicStream* s) const
{
    s->write(type());
    _endpoint->streamWrite(s);
}

Ice::Short
EndpointI::type() const
{
    return (Ice::Short)(TYPE_BASE + _endpoint->type());
}

std::string
EndpointI::protocol() const
{
    return _endpoint->protocol();
}

int
EndpointI::timeout() const
{
    return _endpoint->timeout();
}

IceInternal::EndpointIPtr
EndpointI::timeout(int timeout) const
{
    IceInternal::EndpointIPtr endpoint = _endpoint->timeout(timeout);
    if(endpoint == _endpoint)
    {
        return const_cast<EndpointI*>(this);
    }
    else
    {
        return new EndpointI(endpoint);
    }
}

IceInternal::EndpointIPtr
EndpointI::connectionId(const string& connectionId) const
{
    IceInternal::EndpointIPtr endpoint = _endpoint->connectionId(connectionId);
    if(endpoint == _endpoint)
    {
        return const_cast<EndpointI*>(this);
    }
    else
    {
        return new EndpointI(endpoint);
    }
}

bool
EndpointI::compress() const
{
    return _endpoint->compress();
}

IceInternal::EndpointIPtr
EndpointI::compress(bool compress) const
{
    IceInternal::EndpointIPtr endpoint = _endpoint->compress(compress);
    if(endpoint == _endpoint)
    {
        return const_cast<EndpointI*>(this);
    }
    else
    {
        return new EndpointI(endpoint);
    }
}

bool
EndpointI::datagram() const
{
    return _endpoint->datagram();
}

bool
EndpointI::secure() const
{
    return _endpoint->secure();
}

IceInternal::TransceiverPtr
EndpointI::transceiver(IceInternal::EndpointIPtr& endpoint) const
{
    IceInternal::EndpointIPtr endpt = _endpoint;
    IceInternal::TransceiverPtr transceiver = _endpoint->transceiver(endpt);
    if(endpt == _endpoint)
    {
        endpoint = const_cast<EndpointI*>(this);
    }
    else
    {
        endpoint = new EndpointI(endpoint);
    }

    if(transceiver)
    {
        return new Transceiver(transceiver);
    }
    else
    {
        return 0;
    }
}

vector<IceInternal::ConnectorPtr>
EndpointI::connectors(Ice::EndpointSelectionType selType) const
{
    _configuration->checkConnectorsException();
    vector<IceInternal::ConnectorPtr> c = _endpoint->connectors(selType);
    for(vector<IceInternal::ConnectorPtr>::iterator p = c.begin(); p != c.end(); ++p)
    {
        *p = new Connector(*p);
    }
    return c;
}

void
EndpointI::connectors_async(Ice::EndpointSelectionType selType, const IceInternal::EndpointI_connectorsPtr& cb) const
{
    class Callback : public IceInternal::EndpointI_connectors
    {
    public:
        
        Callback(const IceInternal::EndpointI_connectorsPtr& callback) : _callback(callback)
        {
        }
        
        void
        connectors(const vector<IceInternal::ConnectorPtr>& connectors)
        {
            vector<IceInternal::ConnectorPtr> c;
            for(vector<IceInternal::ConnectorPtr>::const_iterator p = connectors.begin(); p != connectors.end(); ++p)
            {
                c.push_back(new Connector(*p));
            }
            _callback->connectors(c);
        }

        void
        exception(const Ice::LocalException& ex)
        {
            _callback->exception(ex);
        }
        
    private:
        
        IceInternal::EndpointI_connectorsPtr _callback;
    };

    try
    {
        _configuration->checkConnectorsException();
        _endpoint->connectors_async(selType, new Callback(cb));
    }
    catch(const Ice::LocalException& ex)
    {
        cb->exception(ex);
    }
}

IceInternal::AcceptorPtr
EndpointI::acceptor(IceInternal::EndpointIPtr& endpoint, const string& adapterName) const
{
    IceInternal::AcceptorPtr p = new Acceptor(_endpoint->acceptor(endpoint, adapterName));
    endpoint = new EndpointI(endpoint);
    return p;
}

vector<IceInternal::EndpointIPtr>
EndpointI::expand() const
{
    vector<IceInternal::EndpointIPtr> e = _endpoint->expand();
    for(vector<IceInternal::EndpointIPtr>::iterator p = e.begin(); p != e.end(); ++p)
    {
        *p = (*p == _endpoint) ? const_cast<EndpointI*>(this) : new EndpointI(*p);
    }
    return e;
}

bool
EndpointI::equivalent(const IceInternal::EndpointIPtr& endpoint) const
{
    const EndpointI* testEndpointI = dynamic_cast<const EndpointI*>(endpoint.get());
    if(!testEndpointI)
    {
        return false;
    }
    return testEndpointI->_endpoint->equivalent(_endpoint);
}

string
EndpointI::toString() const
{
    return "test-" + _endpoint->toString();
}

Ice::EndpointInfoPtr
EndpointI::getInfo() const
{
    return _endpoint->getInfo();
}

bool
EndpointI::operator==(const Ice::LocalObject& r) const
{
    const EndpointI* p = dynamic_cast<const EndpointI*>(&r);
    if(!p)
    {
        return false;
    }

    if(this == p)
    {
        return true;
    }

    
    return *p->_endpoint == *_endpoint;
}

bool
EndpointI::operator<(const Ice::LocalObject& r) const
{
    const EndpointI* p = dynamic_cast<const EndpointI*>(&r);
    if(!p)
    {
        const IceInternal::EndpointI* e = dynamic_cast<const IceInternal::EndpointI*>(&r);
        if(!e)
        {
            return false;
        }
        return type() < e->type();
    }

    if(this == p)
    {
        return false;
    }

    return *p->_endpoint < *_endpoint;
}

Ice::Int
EndpointI::hashInit() const
{
    return _endpoint->ice_getHash();
}
