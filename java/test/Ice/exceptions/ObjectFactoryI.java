// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.exceptions;


public final class ObjectFactoryI implements Ice.ObjectFactory
{
    public Ice.Object create(String s)
    {
        return null;
    }

    public void destroy()
    {
    }
}
