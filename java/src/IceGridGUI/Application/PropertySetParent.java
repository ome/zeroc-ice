// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.Application;

import IceGrid.*;
import IceGridGUI.*;

interface PropertySetParent
{
    void tryAdd(String id, PropertySetDescriptor descriptor)
        throws UpdateFailedException;

    void tryRename(String oldId, String oldUnresolveId, String newUnresolvedId)
        throws UpdateFailedException;

    void insertPropertySet(PropertySet nps, boolean fireEvent)
        throws UpdateFailedException;

    void removePropertySet(PropertySet nps);

    void removeDescriptor(String id);

    Editable getEditable();
}
