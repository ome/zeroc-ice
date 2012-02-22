// **********************************************************************
//
// Copyright (c) 2003-2011 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Stream.h>
#include <Ice/LocalException.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

IceUtil::Shared* Ice::upCast(InputStream* p) { return p; }
IceUtil::Shared* Ice::upCast(OutputStream* p) { return p; }

namespace IceInternal
{
  void delegateThrowMarshalException(const char* file, int line , const ::std::string& message)
  {
    throw Ice::MarshalException(file, line, message);
  }
}
