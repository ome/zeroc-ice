// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.Application;

public class UpdateFailedException extends Exception
{
    UpdateFailedException(TreeNode parent, String id)
    {
        _message = parent.getFullId().toString() + " has already a child with '" + id + "' as ID.";
    }

    UpdateFailedException(String message)
    {
        _message = message;
    }
    
    public String toString()
    {
        return _message;
    }

    private String _message;
}
