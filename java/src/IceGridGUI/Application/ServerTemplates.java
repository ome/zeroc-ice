// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.Application;

import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;

import IceGrid.*;
import IceGridGUI.*;

class ServerTemplates extends Templates
{
    static public java.util.Map<String, TemplateDescriptor>
    copyDescriptors(java.util.Map<String, TemplateDescriptor> descriptors)
    {
        java.util.Map<String, TemplateDescriptor> copy = new java.util.HashMap<String, TemplateDescriptor>();
        for(java.util.Map.Entry<String, TemplateDescriptor> p : descriptors.entrySet())
        {
            copy.put(p.getKey(), ServerTemplate.copyDescriptor(p.getValue()));
        }
        return copy;
    }

    //
    // Actions
    //
    public boolean[] getAvailableActions()
    {
        boolean[] actions = new boolean[ACTION_COUNT];
        actions[NEW_TEMPLATE_SERVER] = true;
        actions[NEW_TEMPLATE_SERVER_ICEBOX] = true;

        Object clipboard = getCoordinator().getClipboard();
        if(clipboard != null && clipboard instanceof TemplateDescriptor)
        {
            TemplateDescriptor d = (TemplateDescriptor)clipboard;
            actions[PASTE] = d.descriptor instanceof ServerDescriptor;
        }
        return actions;
    }

    public JPopupMenu getPopupMenu()
    {
        ApplicationActions actions = getCoordinator().getActionsForPopup();
        if(_popup == null)
        {
            _popup = new JPopupMenu();
            _popup.add(actions.get(NEW_TEMPLATE_SERVER));
            _popup.add(actions.get(NEW_TEMPLATE_SERVER_ICEBOX));
        }
        actions.setTarget(this);
        return _popup;
    }

    public void newTemplateServer()
    {
        newServerTemplate(new TemplateDescriptor(
                              PlainServer.newServerDescriptor(),
                              new java.util.LinkedList<String>(),
                              new java.util.TreeMap<String, String>()));
    }

    public void newTemplateServerIceBox()
    {
        newServerTemplate(new TemplateDescriptor(
                              PlainServer.newIceBoxDescriptor(),
                              new java.util.LinkedList<String>(),
                              new java.util.TreeMap<String, String>()));
    }

    public void paste()
    {
        Object descriptor =  getCoordinator().getClipboard();
        TemplateDescriptor td = ServerTemplate.copyDescriptor((TemplateDescriptor)descriptor);

        if(td.descriptor instanceof IceBoxDescriptor)
        {
            if(!getRoot().pasteIceBox((IceBoxDescriptor)td.descriptor))
            {
                return;
            }
        }

        newServerTemplate(td);
    }

    ServerTemplates(Root parent, java.util.Map<String, TemplateDescriptor> descriptors)
        throws UpdateFailedException
    {
        super(parent, "Server templates");

        _descriptors = descriptors;

        for(java.util.Map.Entry<String, TemplateDescriptor> p : _descriptors.entrySet())
        {
            insertChild(new ServerTemplate(false, this, p.getKey(), p.getValue()), false);
        }
    }

    //
    // Variable resolution does not make sense for templates / template children
    //
    Utils.Resolver getResolver()
    {
        return null;
    }

    java.util.Map<String, TemplateDescriptor> getUpdates()
    {
        java.util.Map<String, TemplateDescriptor> updates = new java.util.HashMap<String, TemplateDescriptor>();
        for(TreeNodeBase p : _children)
        {
            ServerTemplate t = (ServerTemplate)p;
            if(t.getEditable().isNew() || t.getEditable().isModified())
            {
                updates.put(t.getId(), (TemplateDescriptor)t.getDescriptor());
            }
        }
        return updates;
    }

    void commit()
    {
        _editable.commit();
        for(TreeNodeBase p : _children)
        {
            ServerTemplate st = (ServerTemplate)p;
            st.commit();
        }
    }

    java.util.List<ServiceInstance> findServiceInstances(String template)
    {
        java.util.List<ServiceInstance> result = new java.util.LinkedList<ServiceInstance>();
        for(TreeNodeBase p : _children)
        {
            ServerTemplate t = (ServerTemplate)p;
            result.addAll(t.findServiceInstances(template));
        }
        return result;
    }

    void removeServiceInstances(String template)
    {
        for(TreeNodeBase p : _children)
        {
            ServerTemplate t = (ServerTemplate)p;
            t.removeServiceInstances(template);
        }
    }

    void newServerTemplate(TemplateDescriptor descriptor)
    {
        String id;
        if(descriptor.descriptor instanceof IceBoxDescriptor)
        {
            id = makeNewChildId("NewIceBoxTemplate");
        }
        else
        {
            id = makeNewChildId("NewServerTemplate");
        }

        ServerTemplate t = new ServerTemplate(this, id, descriptor);
        try
        {
            insertChild(t, true);
        }
        catch(UpdateFailedException e)
        {
            assert false;
        }
        getRoot().setSelectedNode(t);
    }

    void tryAdd(String newId, TemplateDescriptor descriptor)
        throws UpdateFailedException
    {
        insertChild(new ServerTemplate(true, this, newId, descriptor), true);
        _descriptors.put(newId, descriptor);
    }

    void update(java.util.Map<String, TemplateDescriptor> updates, String[] removeTemplates,
                java.util.Set<String> serviceTemplates)
        throws UpdateFailedException
    {
        //
        // Note: _descriptors is updated by Root
        //

        Root root = getRoot();

        //
        // One big set of removes
        //
        removeChildren(removeTemplates);

        //
        // One big set of updates, followed by inserts
        //
        java.util.List<TreeNodeBase> newChildren = new java.util.ArrayList<TreeNodeBase>();
        java.util.List<TreeNodeBase> updatedChildren = new java.util.LinkedList<TreeNodeBase>();

        for(java.util.Map.Entry<String, TemplateDescriptor> p : updates.entrySet())
        {
            String name = p.getKey();
            TemplateDescriptor templateDescriptor = p.getValue();
            ServerTemplate child = (ServerTemplate)findChild(name);
            if(child == null)
            {
                newChildren.add(new ServerTemplate(false, this, name, templateDescriptor));
            }
            else
            {
                child.rebuild(templateDescriptor);
                updatedChildren.add(child);
            }
        }

        //
        // Rebuild template affected by service template updates
        //
        for(String p : serviceTemplates)
        {
            java.util.List<ServiceInstance> serviceInstances = findServiceInstances(p);
            for(ServiceInstance q : serviceInstances)
            {
                ServerTemplate serverTemplate = (ServerTemplate)q.getParent();

                if(!updatedChildren.contains(serverTemplate) && !newChildren.contains(serverTemplate))
                {
                    serverTemplate.rebuild();
                    updatedChildren.add(serverTemplate);
                }
            }
        }

        childrenChanged(updatedChildren);
        insertChildren(newChildren, true);
    }

    void removeDescriptor(String id)
    {
        _descriptors.remove(id);
    }

    Object getDescriptor()
    {
        return _descriptors;
    }

    private java.util.Map<String, TemplateDescriptor> _descriptors;
    static private JPopupMenu _popup;
}
