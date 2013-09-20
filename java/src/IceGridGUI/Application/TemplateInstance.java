// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.Application;

interface TemplateInstance
{
    Object rebuild(java.util.List<Editable> editables) throws UpdateFailedException;
    void restore(Object backupObj);
}

