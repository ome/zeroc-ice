// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_SSL_ACCEPTOR_I_H
#define ICE_SSL_ACCEPTOR_I_H

#include <Ice/LoggerF.h>
#include <Ice/TransceiverF.h>
#include <Ice/Acceptor.h>
#include <Ice/Protocol.h>
#include <IceSSL/InstanceF.h>
#include <Ice/Network.h>

#include <vector>

namespace IceSSL
{

class EndpointI;

class AcceptorI : public IceInternal::Acceptor, public IceInternal::NativeInfo
{
public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();
#ifdef ICE_USE_IOCP
    virtual IceInternal::AsyncInfo* getAsyncInfo(IceInternal::SocketOperation);
#endif

    virtual void close();
    virtual void listen();
#ifdef ICE_USE_IOCP
    virtual void startAccept();
    virtual void finishAccept();
#endif
    virtual IceInternal::TransceiverPtr accept();
    virtual std::string toString() const;

    int effectivePort() const;

private:

    AcceptorI(const InstancePtr&, const std::string&, const std::string&, int);
    virtual ~AcceptorI();
    friend class EndpointI;

    const InstancePtr _instance;
    const std::string _adapterName;
    const Ice::LoggerPtr _logger;
    const IceInternal::Address _addr;
    int _backlog;
#ifdef ICE_USE_IOCP
    SOCKET _acceptFd;
    int _acceptError;
    std::vector<char> _acceptBuf;
    IceInternal::AsyncInfo _info;
#endif
};

}

#endif
