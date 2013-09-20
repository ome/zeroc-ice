// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

public interface NativePropertiesAdmin
{
    void addUpdateCallback(PropertiesAdminUpdateCallback callback); 
    void removeUpdateCallback(PropertiesAdminUpdateCallback callback);
}
