// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.Application;

import com.jgoodies.forms.builder.DefaultFormBuilder;

import IceGrid.*;
import IceGridGUI.*;

class PlainServerEditor extends AbstractServerEditor
{
    protected void writeDescriptor()
    {
        _subEditor.writeDescriptor();
    }

    protected boolean isSimpleUpdate()
    {
        return _subEditor.isSimpleUpdate();
    }

    PlainServerEditor()
    {
        _subEditor = new ServerSubEditor(this);
    }

    //
    // From Editor:
    //
    Utils.Resolver getDetailResolver()
    {
        if(_target.getCoordinator().substitute())
        {
            return _target.getResolver();
        }
        else
        {
            return null;
        }
    }

    protected void appendProperties(DefaultFormBuilder builder)
    {
        _subEditor.appendProperties(builder);
    }

    Object getSubDescriptor()
    {
        return _target.getDescriptor();
    }

    protected boolean validate()
    {
        return _subEditor.validate();
    }

    void show(PlainServer server)
    {
        detectUpdates(false);
        _target = server;

        _subEditor.show(true);

        _applyButton.setEnabled(server.isEphemeral());
        _discardButton.setEnabled(server.isEphemeral());
        detectUpdates(true);
        if(server.isEphemeral())
        {
            updated();
        }
    }

    private ServerSubEditor _subEditor;
}
