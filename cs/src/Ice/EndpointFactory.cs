// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

namespace IceInternal
{

    public interface EndpointFactory
    {
        short type();
        string protocol();
        EndpointI create(string str, bool oaEndpoint);
        EndpointI read(BasicStream s);
        void destroy();
    }

}
