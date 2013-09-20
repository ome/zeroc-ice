// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.Application;

import javax.swing.tree.DefaultTreeModel;

import java.util.Enumeration;

import IceGrid.*;
import IceGridGUI.*;

//
// An editable TreeNode that holds a list of children
//
abstract class ListTreeNode extends TreeNode
{
    public Enumeration children()
    {
        return new Enumeration()
            {
                public boolean hasMoreElements()
                {
                    return _p.hasNext();
                }

                public Object nextElement()
                {
                    return _p.next();
                }
                
                private java.util.Iterator<TreeNodeBase> _p = _children.iterator();
            };
    }
    
    public boolean getAllowsChildren()
    {
        return true;
    }
    
    public javax.swing.tree.TreeNode getChildAt(int childIndex)
    {
        if(childIndex < 0)
        {
            throw new ArrayIndexOutOfBoundsException(childIndex);
        }
        else if(childIndex < _children.size())
        {
            return _children.get(childIndex);
        }
        else
        {
            throw new ArrayIndexOutOfBoundsException(childIndex);
        }
    }
   
    public int getChildCount()
    {
        return _children.size();
    }
    
    public int getIndex(javax.swing.tree.TreeNode node)
    {
        return _children.indexOf(node);
    }

    public boolean isLeaf()
    {
        return _children.isEmpty();
    }

    public Editor getEditor()
    {
        if(_editor == null)
        {
            _editor = new Editor();
        }
        return _editor;
    }

    protected Editor createEditor()
    {
        assert false;
        return null;
    }

    protected ListTreeNode(boolean brandNew, TreeNode parent, String id)
    {
        super(parent, id);
        _editable = new Editable(brandNew);
    }

    void write(XMLWriter writer)
        throws java.io.IOException
    {
        for(TreeNodeBase p : _children)
        {
            TreeNode node = (TreeNode)p;
            node.write(writer);
        }
    }

    void insertChild(TreeNode child, boolean fireEvent)
        throws UpdateFailedException
    {
        DefaultTreeModel treeModel = fireEvent ?  getRoot().getTreeModel() : null;
        
        if(!insertSortedChild(child, _children, treeModel))
        {
            throw new UpdateFailedException(this, child.getId());
        }
    }

    void insertChildren(java.util.List newChildren, boolean fireEvent)
        throws UpdateFailedException
    {
        DefaultTreeModel treeModel = fireEvent ?  getRoot().getTreeModel() : null;
        
        String badChildId = insertSortedChildren(newChildren, _children, treeModel);
        
        if(badChildId != null)
        {
            throw new UpdateFailedException(this, badChildId);
        }
    }

    int removeChild(TreeNode child)
    {
        int index = getIndex(child);
        _children.remove(child);
        
        getRoot().getTreeModel().nodesWereRemoved(this, new int[]{index}, new Object[]{child});
        return index;
    }

    void removeChildren(String[] childIds)
    {
        removeSortedChildren(childIds, _children, getRoot().getTreeModel());
    }

    void childrenChanged(java.util.List children)
    {
        childrenChanged(children, getRoot().getTreeModel());
    }

    Editable getEditable()
    {
        return _editable;
    }

    javax.swing.ComboBoxModel<Object> createComboBoxModel()
    {
        return new ComboBoxModel();
    }
    
    javax.swing.ComboBoxModel<Object> createComboBoxModel(Object item)
    {
        return new ComboBoxModel(item);
    }
    
    //
    // Adapts ListTreeNode to a ComboBoxModel
    //
    class ComboBoxModel extends javax.swing.AbstractListModel<Object> implements javax.swing.ComboBoxModel<Object>
    {
        public Object getElementAt(int index)
        {
            if(_firstItem != null)
            {
                if(index == 0)
                {
                    return _firstItem;
                }
                else
                {
                    return getChildAt(index - 1);
                }
            }
            else
            {
                return getChildAt(index);
            }
        }

        public int getSize()
        {
            if(_firstItem != null)
            {
                return getChildCount() + 1;
            }
            else
            {
                return getChildCount();
            }
        }
        
        public Object getSelectedItem()
        {
            return _selectedItem;
        }

        public void setSelectedItem(Object obj)
        {
            if(obj != _selectedItem)
            {
                _selectedItem = obj;
                fireContentsChanged(this, -1, -1);
            }
        }

        ComboBoxModel(Object firstItem)
        {
            _firstItem = firstItem;
        }

        ComboBoxModel()
        {
            _firstItem = null;
        }

        private final Object _firstItem;
        private Object _selectedItem;
    }

    protected final java.util.LinkedList<TreeNodeBase> _children = new java.util.LinkedList<TreeNodeBase>();
    protected Editable _editable;

    static private Editor _editor;
}
