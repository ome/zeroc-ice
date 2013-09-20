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

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.DefaultCellEditor;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;

//
// A special field used to show/edit properties
//

public class PropertiesField extends JTable
{
    public PropertiesField(Editor editor)
    {
        _columnNames = new java.util.Vector<String>(2);
        _columnNames.add("Name");
        _columnNames.add("Value");

        _editor = editor;

        //
        // Adjust row height for larger fonts
        //
        int fontSize = getFont().getSize();
        int minRowHeight = fontSize + fontSize / 3;
        if(rowHeight < minRowHeight)
        {
            setRowHeight(minRowHeight);
        }

        Action deleteRow = new AbstractAction("Delete selected row(s)")
            {
                public void actionPerformed(ActionEvent e)
                {
                    if(_editable)
                    {
                        if(isEditing())
                        {
                            getCellEditor().stopCellEditing();
                        }

                        for(;;)
                        {
                            int selectedRow = getSelectedRow();
                            if(selectedRow == -1)
                            {
                                break;
                            }
                            else
                            {
                                _model.removeRow(selectedRow);
                            }
                        }
                    }
                }
            };
        getActionMap().put("delete", deleteRow);
        getInputMap().put(KeyStroke.getKeyStroke("DELETE"), "delete");
    }

    public void setProperties(java.util.List<PropertyDescriptor> properties,
                              java.util.List<AdapterDescriptor> adapters, String[] logs, Utils.Resolver resolver,
                              boolean editable)
    {
        _editable = editable;

        //
        // We don't show the .Endpoint and .PublishedEndpoints of adapters,
        // since they already appear in the Adapter pages
        //
        java.util.Set<String> hiddenPropertyNames = new java.util.HashSet<String>();

        //
        // We also hide properties whose value match an object or allocatable
        //
        java.util.Set<String> hiddenPropertyValues = new java.util.HashSet<String>();

        _hiddenProperties.clear();

        if(adapters != null)
        {
            //
            // Note that we don't substitute *on purpose*, i.e. the names or values
            // must match before substitution.
            //
            for(AdapterDescriptor p : adapters)
            {
                hiddenPropertyNames.add(p.name + ".Endpoints");
                hiddenPropertyNames.add(p.name + ".PublishedEndpoints");
                hiddenPropertyNames.add(p.name + ".ProxyOptions");

                for(ObjectDescriptor q : p.objects)
                {
                    hiddenPropertyValues.add(Ice.Util.identityToString(q.id));
                }
                for(ObjectDescriptor q : p.allocatables)
                {
                    hiddenPropertyValues.add(Ice.Util.identityToString(q.id));
                }
            }
        }

        if(logs != null)
        {
            for(String log : logs)
            {
                hiddenPropertyValues.add(log);
            }
        }

        //
        // Transform list into vector of vectors
        //
        java.util.Vector<java.util.Vector<String>> vector =
            new java.util.Vector<java.util.Vector<String>>(properties.size());
        for(PropertyDescriptor p : properties)
        {
            if(hiddenPropertyNames.contains(p.name))
            {
                //
                // We keep them at the top of the list
                //
                if(_editable)
                {
                    _hiddenProperties.add(p);
                }

                //
                // We hide only the first occurence
                //
                hiddenPropertyNames.remove(p.name);
            }
            else if(hiddenPropertyValues.contains(p.value))
            {
                //
                // We keep them at the top of the list
                //
                if(_editable)
                {
                    _hiddenProperties.add(p);
                }

                //
                // We hide only the first occurence
                //
                hiddenPropertyValues.remove(p.value);
            }
            else
            {
                java.util.Vector<String> row = new java.util.Vector<String>(2);
                row.add(Utils.substitute(p.name, resolver));
                row.add(Utils.substitute(p.value, resolver));
                vector.add(row);
            }
        }

        if(_editable)
        {
            java.util.Vector<String> newRow = new java.util.Vector<String>(2);
            newRow.add("");
            newRow.add("");
            vector.add(newRow);
        }

        _model = new DefaultTableModel(vector, _columnNames)
            {
                public boolean isCellEditable(int row, int column)
                {
                    return _editable;
                }
            };

        _model.addTableModelListener(new TableModelListener()
            {
                public void tableChanged(TableModelEvent e)
                {
                    if(_editable)
                    {
                        Object lastKey = _model.getValueAt(_model.getRowCount() - 1 , 0);
                        if(lastKey != null && !lastKey.equals(""))
                        {
                            _model.addRow(new Object[]{"", ""});
                        }
                        _editor.updated();
                    }
                }
            });
        setModel(_model);

        setCellSelectionEnabled(_editable);
        setOpaque(_editable);
        setPreferredScrollableViewportSize(getPreferredSize());

        DefaultTableCellRenderer cr = (DefaultTableCellRenderer)getDefaultRenderer(String.class);
        cr.setOpaque(_editable);
    }

    public java.util.LinkedList<PropertyDescriptor> getProperties()
    {
        assert _editable;

        if(isEditing())
        {
            getCellEditor().stopCellEditing();
        }
        @SuppressWarnings("unchecked")
        java.util.Vector<java.util.Vector<String>> vector =
            (java.util.Vector<java.util.Vector<String>>)_model.getDataVector();

        java.util.LinkedList<PropertyDescriptor> result =
            new java.util.LinkedList<PropertyDescriptor>(_hiddenProperties);

        for(java.util.Vector<String> row : vector)
        {
             //
             // Eliminate rows with null or empty keys
             //
             String key = row.elementAt(0);
             if(key != null)
             {
                 key = key.trim();
                 if(!key.equals(""))
                 {
                     String val = row.elementAt(1);
                     if(val == null)
                     {
                         val = "";
                     }

                     result.add(new PropertyDescriptor(key, val));
                 }
             }
        }
        return result;
    }

    private DefaultTableModel _model;
    private java.util.Vector<String> _columnNames;
    private boolean _editable = false;

    private java.util.LinkedList<PropertyDescriptor> _hiddenProperties =
        new java.util.LinkedList<PropertyDescriptor>();

    private Editor _editor;
}
