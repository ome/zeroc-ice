// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/winrt/StreamTransceiver.h>
#include <Ice/Connection.h>
#include <Ice/Instance.h>
#include <Ice/TraceLevels.h>
#include <Ice/LoggerUtil.h>
#include <Ice/Buffer.h>
#include <Ice/LocalException.h>
#include <Ice/Properties.h>

#include <IceSSL/EndpointInfo.h>
#include <IceSSL/ConnectionInfo.h>

#include <IceUtil/DisableWarnings.h>
#include <Ice/Stats.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;

namespace
{

AsyncOperationCompletedHandler<unsigned int>^
createAsyncOperationCompletedHandler(SocketOperationCompletedHandler^ cb, SocketOperation op, AsyncInfo& info)
{
    return ref new AsyncOperationCompletedHandler<unsigned int>(
        [=,&info] (IAsyncOperation<unsigned int>^ operation, Windows::Foundation::AsyncStatus status)
        {
            if(status != Windows::Foundation::AsyncStatus::Completed)
            {
                info.count = SOCKET_ERROR;
                info.error = operation->ErrorCode.Value;
            }
            else
            {
                info.count = static_cast<int>(operation->GetResults());
            }
            cb(op);
        });
}

}

string
IceInternal::typeToString(Ice::Short type)
{
    switch(type)
    {
    case TCPEndpointType:
        return "tcp";
    case IceSSL::EndpointType:
        return "ssl";
    default:
        assert(false);
        return "";
    }
}

NativeInfoPtr
IceInternal::StreamTransceiver::getNativeInfo()
{
    return this;
}

void 
IceInternal::StreamTransceiver::setCompletedHandler(SocketOperationCompletedHandler^ handler)
{
    _completedHandler = handler;
    _readOperationCompletedHandler = createAsyncOperationCompletedHandler(handler, SocketOperationRead, _read);
    _writeOperationCompletedHandler = createAsyncOperationCompletedHandler(handler, SocketOperationWrite, _write);
}

SocketOperation
IceInternal::StreamTransceiver::initialize()
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
            if(_write.count == SOCKET_ERROR)
            {
                checkConnectErrorCode(__FILE__, __LINE__, _write.error, _connectAddr.host);
            }
            _state = StateConnected;
            _desc = fdToString(_fd);
        }
        catch(const Ice::LocalException& ex)
        {
            if(_traceLevels->network >= 2)
            {
                Trace out(_logger, _traceLevels->networkCat);
                out << "failed to establish " << typeToString(_type) << " connection\n";
                out << "local address: <not available>\n";
                out << "remote address: " << addrToString(_connectAddr) << "\n" << ex;
            }
            throw;
        }

        if(_traceLevels->network >= 1)
        {
            Trace out(_logger, _traceLevels->networkCat);
            out << "" << typeToString(_type) << " connection established\n" << _desc;
        }
    }
    assert(_state == StateConnected);
    return SocketOperationNone;
}

void
IceInternal::StreamTransceiver::close()
{
    if(_state == StateConnected && _traceLevels->network >= 1)
    {
        Trace out(_logger, _traceLevels->networkCat);
        out << "closing " << typeToString(_type) << " connection\n" << toString();
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
IceInternal::StreamTransceiver::write(Buffer&)
{
    return false;
}

bool
IceInternal::StreamTransceiver::read(Buffer&)
{
    return false;
}

bool
IceInternal::StreamTransceiver::startWrite(Buffer& buf)
{
    if(_state < StateConnected)
    {
        try
        {
            IAsyncAction^ action = safe_cast<StreamSocket^>(_fd)->ConnectAsync(
                _connectAddr.host,
                _connectAddr.port,
                _type == IceSSL::EndpointType ? SocketProtectionLevel::Ssl : SocketProtectionLevel::PlainSocket);

            if(!checkIfErrorOrCompleted(SocketOperationConnect, action))
            {
                action->Completed = ref new AsyncActionCompletedHandler(
                    [=] (IAsyncAction^ info, Windows::Foundation::AsyncStatus status)
                    {
                        if(status != Windows::Foundation::AsyncStatus::Completed)
                        {
                            _write.count = SOCKET_ERROR;
                            _write.error = info->ErrorCode.Value;
                        }
                        else
                        {
                            _write.count = 0;
                        }
                        _completedHandler(SocketOperationConnect);
                    });
            }
        }
        catch(Platform::Exception^ ex)
        {
            checkConnectErrorCode(__FILE__, __LINE__, ex->HResult, _connectAddr.host);
        }
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
    _writer->WriteBytes(ref new Array<unsigned char>(&*buf.i, packetSize));
    try
    {
        DataWriterStoreOperation^ operation = _writer->StoreAsync();
        if(checkIfErrorOrCompleted(SocketOperationWrite, operation))
        {
            _write.count = operation->GetResults();
        }
        else
        {
            operation->Completed = _writeOperationCompletedHandler;
        }
    }
    catch(Platform::Exception^ ex)
    {
        checkErrorCode(__FILE__, __LINE__, ex->HResult);
    }
    return packetSize == static_cast<int>(buf.b.end() - buf.i);
}

void
IceInternal::StreamTransceiver::finishWrite(Buffer& buf)
{
    if(_state < StateConnected)
    {
        return;
    }

    if(_write.count == SOCKET_ERROR)
    {
        checkErrorCode(__FILE__, __LINE__, _write.error);
    }

    if(_traceLevels->network >= 3)
    {
        int packetSize = static_cast<int>(buf.b.end() - buf.i);
        if(_maxSendPacketSize > 0 && packetSize > _maxSendPacketSize)
        { 
            packetSize = _maxSendPacketSize;
        }
        Trace out(_logger, _traceLevels->networkCat);
        out << "sent " << _write.count << " of " << packetSize << " bytes via " << typeToString(_type) << "\n"
            << toString();
    }
    
    if(_stats)
    {
        _stats->bytesSent(type(), _write.count);
    }
    buf.i += _write.count;
}

void
IceInternal::StreamTransceiver::startRead(Buffer& buf)
{
    int packetSize = static_cast<int>(buf.b.end() - buf.i);
    if(_maxReceivePacketSize > 0 && packetSize > _maxReceivePacketSize)
    {
        packetSize = _maxReceivePacketSize;
    }
    assert(!buf.b.empty() && buf.i != buf.b.end());

    try
    {
        DataReaderLoadOperation^ operation = _reader->LoadAsync(packetSize);
        if(checkIfErrorOrCompleted(SocketOperationRead, operation))
        {
            _read.count = operation->GetResults();
        }
        else
        {
            operation->Completed = _readOperationCompletedHandler;
        }
    }
    catch(Platform::Exception^ ex)
    {
        checkErrorCode(__FILE__, __LINE__, ex->HResult);
    }
}

void
IceInternal::StreamTransceiver::finishRead(Buffer& buf)
{
    if(_read.count == SOCKET_ERROR)
    {
        checkErrorCode(__FILE__, __LINE__, _read.error);
    }
    else if(_read.count == 0)
    {
        ConnectionLostException ex(__FILE__, __LINE__);
        ex.error = 0;
        throw ex;
    }

    try
    {
        auto data = ref new Platform::Array<unsigned char>(_read.count);
        _reader->ReadBytes(data);
        memcpy(&*buf.i, data->Data, _read.count);
    }
    catch(Platform::Exception^ ex)
    {
        checkErrorCode(__FILE__, __LINE__, ex->HResult);
    }

    if(_traceLevels->network >= 3)
    {
        int packetSize = static_cast<int>(buf.b.end() - buf.i);
        if(_maxReceivePacketSize > 0 && packetSize > _maxReceivePacketSize)
        {
            packetSize = _maxReceivePacketSize;
        }
        Trace out(_logger, _traceLevels->networkCat);
        out << "received " << _read.count << " of " << packetSize << " bytes via " << typeToString(_type) << "\n"
            << toString();
    }

    if(_stats)
    {
        _stats->bytesReceived(type(), static_cast<Int>(_read.count));
    }

    buf.i += _read.count;
}

string
IceInternal::StreamTransceiver::type() const
{
    return "tcp";
}

string
IceInternal::StreamTransceiver::toString() const
{
    return _desc;
}

Ice::ConnectionInfoPtr 
IceInternal::StreamTransceiver::getInfo() const
{
    Ice::IPConnectionInfoPtr info;
    if(_type == IceSSL::EndpointType)
    {
        info = new IceSSL::ConnectionInfo();
    }
    else
    {
        info = new Ice::TCPConnectionInfo();
    }
    fdToAddressAndPort(_fd, info->localAddress, info->localPort, info->remoteAddress, info->remotePort);
    return info;
}

void
IceInternal::StreamTransceiver::checkSendSize(const Buffer& buf, size_t messageSizeMax)
{
    if(buf.b.size() > messageSizeMax)
    {
        Ex::throwMemoryLimitException(__FILE__, __LINE__, buf.b.size(), messageSizeMax);
    }
}

IceInternal::StreamTransceiver::StreamTransceiver(const InstancePtr& instance, 
                                                  Ice::Short type, 
                                                  SOCKET fd, 
                                                  bool connected) :
    NativeInfo(fd),
    _traceLevels(instance->traceLevels()),
    _type(type),
    _logger(instance->initializationData().logger),
    _stats(instance->initializationData().stats),
    _state(connected ? StateConnected : StateNeedConnect),
    _desc(connected ? fdToString(_fd) : string())
{
    StreamSocket^ streamSocket = safe_cast<StreamSocket^>(_fd);
    _writer = ref new DataWriter(streamSocket->OutputStream);
    _reader = ref new DataReader(streamSocket->InputStream);
    _reader->InputStreamOptions = InputStreamOptions::Partial;

    Ice::PropertiesPtr properties = instance->initializationData().properties;
    setTcpBufSize(_fd, properties, _logger);

    _maxSendPacketSize = streamSocket->Control->OutboundBufferSizeInBytes / 2;
    if(_maxSendPacketSize < 512)
    {
        _maxSendPacketSize = 0;
    }

    _maxReceivePacketSize = properties->getPropertyAsIntWithDefault("Ice.TCP.RcvSize", 128 * 1024);
}

IceInternal::StreamTransceiver::~StreamTransceiver()
{
    assert(_fd == INVALID_SOCKET);
}

void
IceInternal::StreamTransceiver::connect(const Address& addr)
{
    _connectAddr = addr;
}

bool
IceInternal::StreamTransceiver::checkIfErrorOrCompleted(SocketOperation op, IAsyncInfo^ info)
{
    //
    // NOTE: It's important to only check for info->Status once as it
    // might change during the checks below (the Status can be changed
    // by the Windows thread pool concurrently).
    //
    // We consider that a canceled async status is the same as an
    // error. A canceled async status can occur if there's a timeout
    // and the socket is closed.
    //
    Windows::Foundation::AsyncStatus status = info->Status;
    if(status == Windows::Foundation::AsyncStatus::Completed)
    {
        _completedHandler(op);
        return true;
    }
    else if (status == Windows::Foundation::AsyncStatus::Started)
    {
        return false;
    }
    else
    {
        if(_state < StateConnected)
        {
            checkConnectErrorCode(__FILE__, __LINE__, info->ErrorCode.Value, _connectAddr.host);
        }
        else 
        {
            checkErrorCode(__FILE__, __LINE__, info->ErrorCode.Value);
        }
        return true; // Prevent compiler warning.
    }
}
