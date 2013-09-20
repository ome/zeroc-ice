// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/TcpTransceiver.h>
#include <Ice/Connection.h>
#include <Ice/Instance.h>
#include <Ice/TraceLevels.h>
#include <Ice/LoggerUtil.h>
#include <Ice/Buffer.h>
#include <Ice/LocalException.h>

#include <IceUtil/DisableWarnings.h>
#include <Ice/Stats.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

NativeInfoPtr
IceInternal::TcpTransceiver::getNativeInfo()
{
    return this;
}

#ifdef ICE_USE_IOCP
AsyncInfo*
IceInternal::TcpTransceiver::getAsyncInfo(SocketOperation status)
{
    switch(status)
    {
    case SocketOperationRead:
        return &_read;
    case SocketOperationWrite:
        return &_write;
    default:
        assert(false);
        return 0;
    }
}
#endif

SocketOperation
IceInternal::TcpTransceiver::initialize()
{
    if(_state == StateNeedConnect)
    {
        _state = StateConnectPending;
        return SocketOperationConnect;
    }
    else if(_state <= StateConnectPending)
    {
        try
        {
#if defined(ICE_USE_IOCP)
            doFinishConnectAsync(_fd, _write);
#else
            doFinishConnect(_fd);
#endif
            _state = StateConnected;
            _desc = fdToString(_fd);
        }
        catch(const Ice::LocalException& ex)
        {
            if(_traceLevels->network >= 2)
            {
                Trace out(_logger, _traceLevels->networkCat);
                out << "failed to establish tcp connection\n";
#if !defined(_WIN32)
                //
                // The local address is only accessible with connected sockets on Windows.
                //
                Address localAddr;
                fdToLocalAddress(_fd, localAddr);
                out << "local address: " << addrToString(localAddr) << "\n";
#else
                out << "local address: <not available>\n";
#endif
                out << "remote address: " << addrToString(_connectAddr) << "\n" << ex;
            }
            throw;
        }

        if(_traceLevels->network >= 1)
        {
            Trace out(_logger, _traceLevels->networkCat);
            out << "tcp connection established\n" << _desc;
        }
    }
    assert(_state == StateConnected);
    return SocketOperationNone;
}

void
IceInternal::TcpTransceiver::close()
{
    if(_state == StateConnected && _traceLevels->network >= 1)
    {
        Trace out(_logger, _traceLevels->networkCat);
        out << "closing tcp connection\n" << toString();
    }

    assert(_fd != INVALID_SOCKET);
    try
    {
        closeSocket(_fd);
        _fd = INVALID_SOCKET;
    }
    catch(const SocketException&)
    {
        _fd = INVALID_SOCKET;
        throw;
    }
}

bool
IceInternal::TcpTransceiver::write(Buffer& buf)
{
    // Its impossible for the packetSize to be more than an Int.
    int packetSize = static_cast<int>(buf.b.end() - buf.i);
#   ifdef ICE_USE_IOCP
    //
    // Limit packet size to avoid performance problems on WIN32
    //
    if(_maxSendPacketSize > 0 && packetSize > _maxSendPacketSize)
    { 
        packetSize = _maxSendPacketSize;
    }
#   endif
    while(buf.i != buf.b.end())
    {
        assert(_fd != INVALID_SOCKET);

        ssize_t ret = ::send(_fd, reinterpret_cast<const char*>(&*buf.i), packetSize, 0);
        if(ret == 0)
        {
            ConnectionLostException ex(__FILE__, __LINE__);
            ex.error = 0;
            throw ex;
        }

        if(ret == SOCKET_ERROR)
        {
            if(interrupted())
            {
                continue;
            }

            if(noBuffers() && packetSize > 1024)
            {
                packetSize /= 2;
                continue;
            }

            if(wouldBlock())
            {
                return false;
            }
            
            if(connectionLost())
            {
                ConnectionLostException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
            else
            {
                SocketException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
        }

        if(_traceLevels->network >= 3)
        {
            Trace out(_logger, _traceLevels->networkCat);
            out << "sent " << ret << " of " << packetSize << " bytes via tcp\n" << toString();
        }

        if(_stats)
        {
            _stats->bytesSent(type(), static_cast<Int>(ret));
        }

        buf.i += ret;

        if(packetSize > buf.b.end() - buf.i)
        {
            packetSize = static_cast<int>(buf.b.end() - buf.i);
        }
    }
    return true;
}

bool
IceInternal::TcpTransceiver::read(Buffer& buf)
{
    // Its impossible for the packetSize to be more than an Int.
    int packetSize = static_cast<int>(buf.b.end() - buf.i);
    while(buf.i != buf.b.end())
    {
        assert(_fd != INVALID_SOCKET);
        ssize_t ret = ::recv(_fd, reinterpret_cast<char*>(&*buf.i), packetSize, 0);

        if(ret == 0)
        {
            ConnectionLostException ex(__FILE__, __LINE__);
            ex.error = 0;
            throw ex;
        }

        if(ret == SOCKET_ERROR)
        {
            if(interrupted())
            {
                continue;
            }
            
            if(noBuffers() && packetSize > 1024)
            {
                packetSize /= 2;
                continue;
            }

            if(wouldBlock())
            {
                return false;
            }
            
            if(connectionLost())
            {
                ConnectionLostException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
            else
            {
                SocketException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
        }

        if(_traceLevels->network >= 3)
        {
            Trace out(_logger, _traceLevels->networkCat);
            out << "received " << ret << " of " << packetSize << " bytes via tcp\n" << toString();
        }

        if(_stats)
        {
            _stats->bytesReceived(type(), static_cast<Int>(ret));
        }

        buf.i += ret;

        packetSize = static_cast<int>(buf.b.end() - buf.i);
    }
    return true;
}

#if defined(ICE_USE_IOCP)
bool
IceInternal::TcpTransceiver::startWrite(Buffer& buf)
{
    if(_state < StateConnected)
    {
        doConnectAsync(_fd, _connectAddr, _write);
        return false;
    }

    assert(!buf.b.empty());
    assert(buf.i != buf.b.end());

    int packetSize = static_cast<int>(buf.b.end() - buf.i);
    if(_maxSendPacketSize > 0 && packetSize > _maxSendPacketSize)
    { 
        packetSize = _maxSendPacketSize;
    }
    assert(packetSize > 0);
    _write.buf.len = packetSize;
    _write.buf.buf = reinterpret_cast<char*>(&*buf.i);
    int err = WSASend(_fd, &_write.buf, 1, &_write.count, 0, &_write, NULL);
    if(err == SOCKET_ERROR)
    {
        if(!wouldBlock())
        {
            if(connectionLost())
            {
                ConnectionLostException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
            else
            {
                SocketException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
        }
    }
    return packetSize == static_cast<int>(buf.b.end() - buf.i);
}

void
IceInternal::TcpTransceiver::finishWrite(Buffer& buf)
{
    if(_state < StateConnected)
    {
        return;
    }

    if(static_cast<int>(_write.count) == SOCKET_ERROR)
    {
        WSASetLastError(_write.error);
        if(connectionLost())
        {
            ConnectionLostException ex(__FILE__, __LINE__);
            ex.error = getSocketErrno();
            throw ex;
        }
        else
        {
            SocketException ex(__FILE__, __LINE__);
            ex.error = getSocketErrno();
            throw ex;
        }
    }

    if(_traceLevels->network >= 3)
    {
        int packetSize = static_cast<int>(buf.b.end() - buf.i);
        if(_maxSendPacketSize > 0 && packetSize > _maxSendPacketSize)
        { 
            packetSize = _maxSendPacketSize;
        }
        Trace out(_logger, _traceLevels->networkCat);

        out << "sent " << _write.count << " of " << packetSize << " bytes via tcp\n" << toString();
    }
    
    if(_stats)
    {
        _stats->bytesSent(type(), _write.count);
    }
    buf.i += _write.count;
}

void
IceInternal::TcpTransceiver::startRead(Buffer& buf)
{
    int packetSize = static_cast<int>(buf.b.end() - buf.i);
    if(_maxReceivePacketSize > 0 && packetSize > _maxReceivePacketSize)
    {
        packetSize = _maxReceivePacketSize;
    }
    assert(!buf.b.empty() && buf.i != buf.b.end());

    _read.buf.len = packetSize;
    _read.buf.buf = reinterpret_cast<char*>(&*buf.i);
    int err = WSARecv(_fd, &_read.buf, 1, &_read.count, &_read.flags, &_read, NULL);
    if(err == SOCKET_ERROR)
    {
        if(!wouldBlock())
        {
            if(connectionLost())
            {
                ConnectionLostException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
            else
            {
                SocketException ex(__FILE__, __LINE__);
                ex.error = getSocketErrno();
                throw ex;
            }
        }
    }
}

void
IceInternal::TcpTransceiver::finishRead(Buffer& buf)
{
    if(static_cast<int>(_read.count) == SOCKET_ERROR)
    {
        WSASetLastError(_read.error);
        if(connectionLost())
        {
            ConnectionLostException ex(__FILE__, __LINE__);
            ex.error = getSocketErrno();
            throw ex;
        }
        else
        {
            SocketException ex(__FILE__, __LINE__);
            ex.error = getSocketErrno();
            throw ex;
        }
    }
    else if(_read.count == 0)
    {
        ConnectionLostException ex(__FILE__, __LINE__);
        ex.error = 0;
        throw ex;
    }
    
    if(_traceLevels->network >= 3)
    {
        int packetSize = static_cast<int>(buf.b.end() - buf.i);
        if(_maxReceivePacketSize > 0 && packetSize > _maxReceivePacketSize)
        {
            packetSize = _maxReceivePacketSize;
        }
        Trace out(_logger, _traceLevels->networkCat);
        out << "received " << _read.count << " of " << packetSize << " bytes via tcp\n" << toString();
    }

    if(_stats)
    {
        _stats->bytesReceived(type(), static_cast<Int>(_read.count));
    }

    buf.i += _read.count;
}
#endif

string
IceInternal::TcpTransceiver::type() const
{
    return "tcp";
}

string
IceInternal::TcpTransceiver::toString() const
{
    return _desc;
}

Ice::ConnectionInfoPtr 
IceInternal::TcpTransceiver::getInfo() const
{
    Ice::TCPConnectionInfoPtr info = new Ice::TCPConnectionInfo();
    fdToAddressAndPort(_fd, info->localAddress, info->localPort, info->remoteAddress, info->remotePort);
    return info;
}

void
IceInternal::TcpTransceiver::checkSendSize(const Buffer& buf, size_t messageSizeMax)
{
    if(buf.b.size() > messageSizeMax)
    {
        Ex::throwMemoryLimitException(__FILE__, __LINE__, buf.b.size(), messageSizeMax);
    }
}

IceInternal::TcpTransceiver::TcpTransceiver(const InstancePtr& instance, SOCKET fd, bool connected) :
    NativeInfo(fd),
    _traceLevels(instance->traceLevels()),
    _logger(instance->initializationData().logger),
    _stats(instance->initializationData().stats),
    _state(connected ? StateConnected : StateNeedConnect),
    _desc(connected ? fdToString(_fd) : string())
#ifdef ICE_USE_IOCP
    , _read(SocketOperationRead), 
    _write(SocketOperationWrite)
#endif
{
    setBlock(_fd, false);

    setTcpBufSize(_fd, instance->initializationData().properties, _logger);

#ifdef ICE_USE_IOCP
    //
    // On Windows, limiting the buffer size is important to prevent
    // poor throughput performances when transfering large amount of
    // data. See Microsoft KB article KB823764.
    //
    _maxSendPacketSize = IceInternal::getSendBufferSize(fd) / 2;
    if(_maxSendPacketSize < 512)
    {
        _maxSendPacketSize = 0;
    }

    _maxReceivePacketSize = IceInternal::getRecvBufferSize(fd);
    if(_maxReceivePacketSize < 512)
    {
        _maxReceivePacketSize = 0;
    }
#endif
}

IceInternal::TcpTransceiver::~TcpTransceiver()
{
    assert(_fd == INVALID_SOCKET);
}

void
IceInternal::TcpTransceiver::connect(const Address& addr)
{
#if !defined(ICE_USE_IOCP)
    try
    {
        if(doConnect(_fd, addr))
        {
            _state = StateConnected;
            _desc = fdToString(_fd);
            if(_traceLevels->network >= 1)
            {
                Trace out(_logger, _traceLevels->networkCat);
                out << "tcp connection established\n" << _desc;
            }
        }
        else
        {
            _desc = fdToString(_fd);
        }
    }
    catch(...)
    {
        _fd = INVALID_SOCKET;
        throw;
    }
#endif
    _connectAddr = addr;
}
