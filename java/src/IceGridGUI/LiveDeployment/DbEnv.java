// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.LiveDeployment;

import java.awt.Component;
import javax.swing.JTree;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;
import java.util.Enumeration;

import IceGrid.*;
import IceGridGUI.*;

class DbEnv extends TreeNode
{
    public Component getTreeCellRendererComponent(
        JTree tree,
        Object value,
        boolean sel,
        boolean expanded,
        boolean leaf,
        int row,
        boolean hasFocus)
    {
        if(_cellRenderer == null)
        {
            _cellRenderer = new DefaultTreeCellRenderer();
            _cellRenderer.setLeafIcon(Utils.getIcon("/icons/16x16/database.png"));
        }
        return _cellRenderer.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);
    }

    public Editor getEditor()
    {
        if(_editor == null)
        {
            _editor = new DbEnvEditor();
        }
        _editor.show(this);
        return _editor;
    }

    DbEnv(TreeNode parent, String dbEnvName, Utils.Resolver resolver, DbEnvDescriptor descriptor)
    {
        super(parent, dbEnvName);
        _resolver = resolver;
        _descriptor = descriptor;

    }

    Utils.Resolver getResolver()
    {
        return _resolver;
    }

    DbEnvDescriptor getDescriptor()
    {
        return _descriptor;
    }

    private Utils.Resolver _resolver;
    private DbEnvDescriptor _descriptor;

    static private DbEnvEditor _editor;
    static private DefaultTreeCellRenderer _cellRenderer;
}
