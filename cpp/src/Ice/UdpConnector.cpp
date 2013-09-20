// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/UdpConnector.h>

#include <Ice/UdpTransceiver.h>
#include <Ice/UdpEndpointI.h>
#include <Ice/LocalException.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

TransceiverPtr
IceInternal::UdpConnector::connect()
{
    return new UdpTransceiver(_instance, _addr, _mcastInterface, _mcastTtl);
}

Short
IceInternal::UdpConnector::type() const
{
    return UDPEndpointType;
}

string
IceInternal::UdpConnector::toString() const
{
    return addrToString(_addr);
}

bool
IceInternal::UdpConnector::operator==(const Connector& r) const
{
    const UdpConnector* p = dynamic_cast<const UdpConnector*>(&r);
    if(!p)
    {
        return false;
    }
    if(compareAddress(_addr, p->_addr) != 0)
    {
        return false;
    }

    if(_connectionId != p->_connectionId)
    {
        return false;
    }

    if(_mcastTtl != p->_mcastTtl)
    {
        return false;
    }

    if(_mcastInterface != p->_mcastInterface)
    {
        return false;
    }

    return true;
}

bool
IceInternal::UdpConnector::operator!=(const Connector& r) const
{
    return !operator==(r);
}

bool
IceInternal::UdpConnector::operator<(const Connector& r) const
{
    const UdpConnector* p = dynamic_cast<const UdpConnector*>(&r);
    if(!p)
    {
        return type() < r.type();
    }

    if(_connectionId < p->_connectionId)
    {
        return true;
    }
    else if(p->_connectionId < _connectionId)
    {
        return false;
    }

    if(_mcastTtl < p->_mcastTtl)
    {
        return true;
    }
    else if(p->_mcastTtl < _mcastTtl)
    {
        return false;
    }

    if(_mcastInterface < p->_mcastInterface)
    {
        return true;
    }
    else if(p->_mcastInterface < _mcastInterface)
    {
        return false;
    }
    return compareAddress(_addr, p->_addr) == -1;
}

IceInternal::UdpConnector::UdpConnector(const InstancePtr& instance, const Address& addr, 
                                        const string& mcastInterface, int mcastTtl, const std::string& connectionId) :
    _instance(instance),
    _addr(addr),
    _mcastInterface(mcastInterface),
    _mcastTtl(mcastTtl),
    _connectionId(connectionId)
{
}

IceInternal::UdpConnector::~UdpConnector()
{
}
