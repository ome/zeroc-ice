// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.KeyStroke;

import IceGrid.*;
import IceGridGUI.Application.*;

//
// Holds all actions for the Application view
//
public class ApplicationActions
{
    public Action get(int index)
    {
        return _array[index];
    }

    public boolean[] setTarget(TreeNode target)
    {
        _target = target;

        boolean[] availableActions;
        if(_target == null)
        {
            availableActions = new boolean[TreeNode.ACTION_COUNT];
        }
        else
        {
            availableActions = _target.getAvailableActions();
        }

        for(int i = 0; i < _array.length; ++i)
        {
            _array[i].setEnabled(availableActions[i]);
        }

        return availableActions;
    }

    ApplicationActions(boolean popup)
    {
        final int MENU_MASK = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();

        _array[TreeNode.NEW_ADAPTER] = new AbstractAction(popup ? "New Adapter" : "Adapter")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newAdapter();
                    }
                }
            };

        _array[TreeNode.NEW_DBENV] = new AbstractAction(popup ? "New Database Environment" : "Database Environment")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newDbEnv();
                    }
                }
            };

        _array[TreeNode.NEW_NODE] = new AbstractAction(popup ? "New Node" : "Node")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newNode();
                    }
                }
            };

        _array[TreeNode.NEW_PROPERTY_SET] = new AbstractAction(popup ? "New Property Set" : "Property Set")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newPropertySet();
                    }
                }
            };

        _array[TreeNode.NEW_REPLICA_GROUP] = new AbstractAction(popup ? "New Replica Group" : "Replica Group" )
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newReplicaGroup();
                    }
                }
            };

        _array[TreeNode.NEW_SERVER] = new AbstractAction(popup ? "New Server" : "Server")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newServer();
                    }
                }
            };

        _array[TreeNode.NEW_SERVER_ICEBOX] = new AbstractAction(popup ? "New IceBox Server" : "IceBox Server")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newServerIceBox();
                    }
                }
            };

        _array[TreeNode.NEW_SERVER_FROM_TEMPLATE] = new AbstractAction(
            popup ? "New Server from Template" : "Server from Template")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newServerFromTemplate();
                    }
                }
            };


        _array[TreeNode.NEW_SERVICE] = new AbstractAction(popup ? "New Service" : "Service")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newService();
                    }
                }
            };

        _array[TreeNode.NEW_SERVICE_FROM_TEMPLATE] = new AbstractAction(
            popup ? "New Service from Template" : "Service from Template")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newServiceFromTemplate();
                    }
                }
            };

        _array[TreeNode.NEW_TEMPLATE_SERVER] = new AbstractAction(popup ? "New Server Template" : "Server Template")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newTemplateServer();
                    }
                }
            };

        _array[TreeNode.NEW_TEMPLATE_SERVER_ICEBOX] = new AbstractAction(
            popup ? "New IceBox Server Template" : "IceBox Server Template")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newTemplateServerIceBox();
                    }
                }
            };


        _array[TreeNode.NEW_TEMPLATE_SERVICE] = new AbstractAction(popup ? "New Service Template" : "Service Template")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.newTemplateService();
                    }
                }
            };

        _array[TreeNode.COPY] = new AbstractAction("Copy")
            {
                public void actionPerformed(ActionEvent e)
                {
                    _target.copy();
                }
            };

        _array[TreeNode.PASTE] = new AbstractAction("Paste")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.paste();
                    }
                }
            };

        _array[TreeNode.DELETE] = new AbstractAction("Delete")
            {
                public void actionPerformed(ActionEvent e)
                {
                    _target.delete();
                }
            };

        _array[TreeNode.SHOW_VARS] = new AbstractAction("Show Variables")
            {
                public void actionPerformed(ActionEvent e)
                {
                    _target.getCoordinator().showVars();
                }
            };

        _array[TreeNode.SHOW_VARS].putValue(
            Action.SHORT_DESCRIPTION,
            "Show variables and parameters in the Properties pane");

        _array[TreeNode.SUBSTITUTE_VARS] = new
            AbstractAction("Substitute Variables")
            {
                public void actionPerformed(ActionEvent e)
                {
                    _target.getCoordinator().substituteVars();
                }
            };

        _array[TreeNode.SUBSTITUTE_VARS].putValue(
            Action.SHORT_DESCRIPTION,
            "Substitute variables and parameters with their values in the Properties pane");

        _array[TreeNode.MOVE_UP] = new AbstractAction("Move Up")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.moveUp();
                    }
                }
            };

        _array[TreeNode.MOVE_DOWN] = new AbstractAction("Move Down")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(apply(_target))
                    {
                        _target.moveDown();
                    }
                }
            };
    }

    static private boolean apply(TreeNode target)
    {
        return target.getRoot().getPane().applyUpdates(false);
    }

    private TreeNode _target;
    private Action[] _array = new Action[TreeNode.ACTION_COUNT];
}
