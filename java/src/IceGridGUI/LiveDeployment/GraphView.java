// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI.LiveDeployment;

import java.util.Map;
import java.util.List;
import java.util.Stack;
import java.util.HashMap;
import java.util.ArrayList;

import java.util.Date;
import java.util.TimeZone;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;

import java.awt.Frame;
import java.awt.Color;
import java.awt.Rectangle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.KeyEvent;

import javax.swing.AbstractAction;
import javax.swing.AbstractCellEditor;
import javax.swing.Action;
import javax.swing.BorderFactory;
import javax.swing.border.Border;
import javax.swing.DefaultCellEditor;
import javax.swing.DefaultListCellRenderer;

import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JColorChooser;
import javax.swing.colorchooser.AbstractColorChooserPanel;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;
import javax.swing.ListCellRenderer;
import javax.swing.SwingUtilities;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingConstants;
import javax.swing.JSplitPane;

import javax.swing.ListSelectionModel;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;

import java.text.DecimalFormat;

import javafx.application.Platform;

import javafx.embed.swing.JFXPanel;

import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;

import javafx.scene.Scene;

import javafx.scene.input.MouseEvent;
import javafx.event.EventHandler;
import javafx.scene.input.MouseButton;

import javafx.scene.input.DragEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.input.DataFormat;
import javafx.scene.input.Dragboard;

import javafx.util.StringConverter;

import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.builder.DefaultFormBuilder;
import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.builder.ButtonBarBuilder;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.looks.Options;
import com.jgoodies.looks.HeaderStyle;
import com.jgoodies.looks.BorderStyle;
import com.jgoodies.looks.plastic.PlasticLookAndFeel;

import IceGrid.*;
import IceGridGUI.*;

import IceGridGUI.LiveDeployment.MetricsViewEditor.MetricsViewInfo;
import IceGridGUI.LiveDeployment.MetricsViewEditor.MetricsCell;
import IceGridGUI.LiveDeployment.MetricsViewEditor.MetricsViewTransferableData;
import IceGridGUI.LiveDeployment.MetricsViewEditor.FormatedNumberRenderer;

import java.util.prefs.Preferences;
import java.util.prefs.BackingStoreException;

public class GraphView extends JFrame implements MetricsFieldContext, Coordinator.IGraphView
{
    class WorkQueue extends Thread
    {
        private class WorkItem
        {
            public WorkItem(Runnable runnable, boolean javafx)
            {
                this.runnable = runnable;
                this.javafx = javafx;
            }

            Runnable runnable;
            boolean javafx;
        }

        public void run()
        {
            while(true)
            {
                WorkItem item = null;
                synchronized(this)
                {
                    while(_queue.isEmpty())
                    {
                        try
                        {
                            wait();
                        }
                        catch(java.lang.InterruptedException ex)
                        {
                        }
                    }
                    assert !_queue.isEmpty();
                    item = _queue.remove(0);
                }

                final java.util.concurrent.Semaphore sem = new java.util.concurrent.Semaphore(0);                
                final Runnable r = item.runnable;
                if(item.javafx)
                {
                    Platform.runLater(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                try
                                {
                                    r.run();
                                }
                                finally
                                {
                                    sem.release();
                                }
                            }
                        });
                }
                else
                {
                    SwingUtilities.invokeLater(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                try
                                {
                                    r.run();
                                }
                                finally
                                {
                                    sem.release();
                                }
                            }
                        });
                }
                sem.acquireUninterruptibly();
            }
        }

        synchronized public void enqueue(Runnable runnable, boolean javafx)
        {
            if(_queue.isEmpty())
            {
                notify();
            }
            _queue.add(new WorkItem(runnable, javafx));
        }

        private java.util.List<WorkItem> _queue = new java.util.LinkedList<WorkItem>();
    }

    class TimeFormatter extends StringConverter<java.lang.Number>
    {
        TimeFormatter(String format)
        {
            setDateFormat(format);
            _dateFormat.setTimeZone(TimeZone.getDefault());
        }

        @Override
        public synchronized String toString(Number timestamp)
        {
            Date date = new Date(timestamp.longValue());
            if(date.getTime() < 1000)
            {
                //
                // When the x axis is first draw we don't have times to display.
                //
                return "";
            }
            else
            {
                return _dateFormat.format(date);
            }
        }

        @Override
        public synchronized Number fromString(String time)
        {
            try
            {
                long t = _dateFormat.parse(time).getTime();
                return t;
            }
            catch(java.text.ParseException e)
            {
                return 0;
            }
        }

        public synchronized void setDateFormat(String format)
        {
            _dateFormat = new SimpleDateFormat(format);
        }

        private DateFormat _dateFormat;
    }

    class TransferHandler extends javax.swing.TransferHandler
    {
        @Override
        public boolean 
        canImport(TransferHandler.TransferSupport support)
        {
            boolean supported = false;
            for(DataFlavor f : support.getDataFlavors())
            {
                if(f.equals(MetricsViewTransferableData.dataFlavor()))
                {
                    supported = true;
                    break;
                }
            }
            return supported;
        }

        @Override
        public boolean
        importData(TransferHandler.TransferSupport support)
        {
            if(!canImport(support))
            {
                return false;
            }

            Transferable t = support.getTransferable();
            
            for(DataFlavor flavor : support.getDataFlavors())
            {
                try
                {
                    if(flavor.equals(MetricsViewTransferableData.dataFlavor()))
                    {
                        addSeries((MetricsViewTransferableData)t.getTransferData(flavor));
                        break;
                    }
                }
                catch(UnsupportedFlavorException ex)
                {
                }
                catch(java.io.IOException ex)
                {
                }
            }

            return true;
        }
    }

    private class RefreshThread extends Thread
    {
        RefreshThread(int period)
        {
            _period = period;
            _done = false;
        }

        synchronized void setRefreshPeriod(int period)
        {
            _period = period;
            notify();
        }

        synchronized public void
        run()
        {
            while(true)
            {
                java.util.Set<MetricsViewInfo> metrics = null;
                synchronized(GraphView.this)
                {
                    metrics = new  java.util.HashSet<MetricsViewInfo>(_series.keySet());
                }

                for(final MetricsViewInfo m : metrics)
                {
                    IceMX.Callback_MetricsAdmin_getMetricsView cb = new IceMX.Callback_MetricsAdmin_getMetricsView()
                        {
                            public void response(final java.util.Map<java.lang.String, IceMX.Metrics[]> data,
                                                 long timestamp)
                            {
                                addData(m, data, timestamp);
                            }

                            public void exception(final Ice.LocalException e)
                            {
                                addData(m, null, 0);
                            }

                            public void exception(final Ice.UserException e)
                            {
                                addData(m, null, 0);
                            }
                        };
                    try
                    {
                        m.admin.begin_getMetricsView(m.view, cb);
                    }
                    catch(Ice.LocalException e)
                    {
                        addData(m, null, 0);
                    }
                }
                if(!_done)
                {
                    try
                    {
                        wait(_period * 1000);
                    }
                    catch(InterruptedException ex)
                    {
                    }
                }

                if(_done)
                {
                    break;
                }
            }
        }

        synchronized public void
        done()
        {
            if(!_done)
            {
                _done = true;
                notify();
            }
        }

        private int _period;
        private boolean _done = false;
    }

    public GraphView(Coordinator coordinator, String title)
    {
        _coordinator = coordinator;
        _queue = new WorkQueue();
        _queue.setDaemon(true);
        _queue.start();

        setTitle(title);

        _preferences = Preferences.userNodeForPackage(getClass());

        //
        // Don't destroy JavaFX when the frame is disposed.
        //
        Platform.setImplicitExit(false);
        setIconImage(Utils.getIcon("/icons/16x16/metrics_graph.png").getImage());
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e) 
            {
                close();
            }
        });

        //
        // Graph preferences.
        //
        Action preferences = new AbstractAction("Preferences")
            {
                public void actionPerformed(ActionEvent event) 
                {
                    //
                    // Set the title
                    //
                    JTextField title = new JTextField(getTitle());
                    JPanel titlePanel;
                    {
                        DefaultFormBuilder builder =
                                                new DefaultFormBuilder(new FormLayout("pref,2dlu,pref:grow", "pref"));
                        builder.append("Title:", title);
                        titlePanel = builder.getPanel();
                    }

                    //
                    // SpinnerNumberModel to set a refresh period.
                    //
                    SpinnerNumberModel refreshPeriod = new SpinnerNumberModel(getRefreshPeriod(), _minRefreshPeriod, 
                                                                              _maxRefreshPeriod, 1);

                    //
                    // SpinnerNumberModel to set the maximum number of samples to keep in X axis.
                    //
                    final SpinnerNumberModel samples = new SpinnerNumberModel(_samples, _minSamples, 
                                                                              _maxSamples, 1);

                    JPanel refreshPanel;
                    {
                        DefaultFormBuilder builder =
                                                new DefaultFormBuilder(new FormLayout("pref,2dlu,pref:grow", "pref"));
                        builder.rowGroupingEnabled(true);
                        final JSpinner spinner = new JSpinner(refreshPeriod);
                        builder.append("Sample interval:", spinner);
                        builder.append("", new JLabel("<html><p>Sample interval in seconds; must be between 1" +
                                                      "<br/>and 3600 seconds.</p></html>"));
                        refreshPanel = builder.getPanel();
                    }

                    //
                    // JComboBox to select time format used in X Axis
                    //
                    JComboBox<String> dateFormats = new JComboBox<String>(_dateFormats);
                    dateFormats.setSelectedItem(getDateFormat());
                    JPanel xAxisPanel;
                    {
                        DefaultFormBuilder builder = 
                                                new DefaultFormBuilder(new FormLayout("pref,2dlu,pref:grow", "pref"));
                        builder.append("Samples displayed:", new JSpinner(samples));
                        builder.append("", new JLabel("<html><p>The number of samples displayed on a graph;" +
                                                      "<br/>must be between 2 and 300." + "</p></html>"));
                        builder.append("Time format:", dateFormats);

                        xAxisPanel = builder.getPanel();
                    }

                    FormLayout layout = new FormLayout("fill:pref:grow", "pref");
                    final DefaultFormBuilder builder = new DefaultFormBuilder(layout);
                    builder.border(Borders.DIALOG);
                    builder.append(titlePanel);
                    builder.nextLine();
                    builder.append(refreshPanel);
                    builder.nextLine();
                    builder.append(xAxisPanel);

                    if(JOptionPane.showConfirmDialog(GraphView.this, builder.getPanel(), "Metrics Graph Preferences", 
                       JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE) != JOptionPane.OK_OPTION)
                    {
                        return;
                    }

                    setTitle(title.getText());
                    setRefreshPeriod(refreshPeriod.getNumber().intValue());
                    setMaximumSamples(samples.getNumber().intValue());
                    setDateFormat((String)dateFormats.getSelectedItem());
                }
            };

        _legendTable = new JTable(_legendModel)
            {
                //Implement table cell tool tips.
                public String getToolTipText(java.awt.event.MouseEvent e)
                {
                    if(convertColumnIndexToModel(columnAtPoint(e.getPoint())) == 6)
                    {
                        return _legendModel.getRows(new int[]{rowAtPoint(e.getPoint())})[0].cell.getField().
                                                                                                    getColumnToolTip();
                    }
                    else
                    {
                        return null;
                    }
                }
            };
        
        //
        // Adjust row height for larger fonts
        //
        int fontSize = _legendTable.getFont().getSize();
        int minRowHeight = fontSize + fontSize / 3;
        if(_legendTable.getRowHeight() < minRowHeight)
        {
            _legendTable.setRowHeight(minRowHeight);
        }
        
        //
        // Graph preferences.
        //
        final Action delete = new AbstractAction("Delete")
            {
                public void actionPerformed(ActionEvent event) 
                {
                    int[] selectedRows = _legendTable.getSelectedRows();
                    for(int i = 0; i < selectedRows.length; ++i)
                    {
                        selectedRows[i] = _legendTable.convertRowIndexToModel(selectedRows[i]);
                    }
                    //
                    // Remove selected rows from the legend model.
                    //
                    final MetricsRow[] rows = _legendModel.removeRows(selectedRows);

                    //
                    // Remove rows from series hash maps
                    //
                    for(MetricsRow row : rows)
                    {
                        Map<String, Map<String, Map<String, MetricsRow>>> j = _series.get(row.info);
                        Map<String, Map<String, MetricsRow>> k = j.get(row.cell.getField().getMetricsName());
                        Map<String, MetricsRow> l = k.get(row.cell.getId());
                        l.remove(row.cell.getField().getFieldName());
                        if(l.size() == 0)
                        {
                            k.remove(row.cell.getId());
                            if(k.size() == 0)
                            {
                                j.remove(row.cell.getField().getMetricsName());
                                if(j.size() == 0)
                                {
                                    _series.remove(row.info);
                                    if(_series.size() == 0)
                                    {
                                        stopRefreshThread();
                                    }
                                }
                            }
                        }
                    }

                    //
                    // Remove series from the chart, in JavaFx thread.
                    //
                    _queue.enqueue(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                for(MetricsRow row : rows)
                                {
                                    for(int i = 0; i < row.series.size(); ++i)
                                    {
                                        XYChart.Series<Number, Number> series = row.series.get(i);
                                        String seriesClass = getSeriesClass(series);
                                        if(seriesClass != null)
                                        {
                                            _styles.remove(seriesClass);
                                        }
                                        //
                                        // Don't remove the XYChart.Series object here, to avoid the series
                                        // style classes to be reasign by JavaFX.
                                        //
                                        // _chart.getData().remove(row.series);
                                        try
                                        {
                                            series.getData().clear();
                                        }
                                        catch(NullPointerException ex)
                                        {
                                            // JavaFX bug
                                        }
                                    }
                                }
                            }
                        }, true);
                }
            };
        delete.setEnabled(false);
        delete.putValue(Action.ACCELERATOR_KEY, KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0));

        _legendTable.getSelectionModel().addListSelectionListener(new ListSelectionListener()
            {
                public void valueChanged(ListSelectionEvent e)
                {
                    if(!e.getValueIsAdjusting())
                    {
                        delete.setEnabled(_legendTable.getSelectedRows().length > 0);
                    }
                }
            });

        //
        // Create the tool bar
        //
        class ToolBar extends JToolBar
        {
            public ToolBar()
            {
                putClientProperty(Options.HEADER_STYLE_KEY, HeaderStyle.BOTH);
                putClientProperty(PlasticLookAndFeel.BORDER_STYLE_KEY, BorderStyle.SEPARATOR);
                setFloatable(false);
                putClientProperty("JToolBar.isRollover", Boolean.TRUE);

                JButton button = new JButton(delete);
                button.setText(null);
                button.setIcon(Utils.getIcon("/icons/24x24/delete.png"));
                add(button);
            }
        }

        //
        // Create menus
        //
        JMenuBar menuBar = new JMenuBar();

        JMenu fileMenu = new JMenu("File");
        fileMenu.setMnemonic(java.awt.event.KeyEvent.VK_F);
        fileMenu.add(preferences);
        menuBar.add(fileMenu);

        JMenu editMenu = new JMenu("Edit");
        editMenu.setMnemonic(java.awt.event.KeyEvent.VK_E);
        editMenu.add(delete);
        menuBar.add(editMenu);

        setJMenuBar(menuBar);

        //
        // Set default renderer for numeric values.
        //
        _legendTable.setDefaultRenderer(Double.class, new FormatedNumberRenderer("#0.000"));

        //
        // Set a combobox to edit the scale factors.
        //
        JComboBox<Double> scales = new JComboBox<Double>(_scales);
        scales.setRenderer(new DecimalRenderer(scales.getRenderer()));
        _legendTable.getColumnModel().getColumn(7).setCellEditor(new DefaultCellEditor(scales));

        //
        //Set default renderer and editor for Color.class column.
        //
        _legendTable.setDefaultRenderer(Color.class, new ColorRenderer(true));
        _legendTable.setDefaultEditor(Color.class, new ColorEditor());
        
        _legendTable.setAutoCreateRowSorter(true);

        final JFXPanel fxPanel = new JFXPanel();
        fxPanel.setMinimumSize(new Dimension(0, 200));
        fxPanel.setPreferredSize(new Dimension(800, 400));
        //
        // Build the split pane, with the chart graph and the legend table.
        //
        _splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
        _splitPane.setTopComponent(fxPanel);
        JScrollPane scrollPane = new JScrollPane(_legendTable);
        scrollPane.setTransferHandler(new TransferHandler());
        scrollPane.setMinimumSize(new Dimension(0, 50));
        scrollPane.setPreferredSize(new Dimension(800, 200));
        _splitPane.setBottomComponent(scrollPane);
        
        DefaultFormBuilder builder = new DefaultFormBuilder(new FormLayout("fill:pref:grow", "fill:pref:grow, pref"));
        builder.append(_splitPane);
        builder.nextLine();

        JPanel panel = builder.getPanel();
        panel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
        getContentPane().add(new ToolBar(), BorderLayout.PAGE_START);
        getContentPane().add(panel, BorderLayout.CENTER);
        setPreferredSize(new Dimension(800, 600));

        //
        // initialize the scene in JavaFX thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    _xAxis = new NumberAxis();
                    _yAxis = new NumberAxis();

                    _chart = new LineChart<Number, Number>(_xAxis, _yAxis);
                    _chart.setCreateSymbols(false);
                    _xAxis.setLabel("Time (" + getDateFormat() + ")");
                    _xAxis.setTickLabelFormatter(_timeFormater);
                    _xAxis.setForceZeroInRange(false);
                    _chart.setAnimated(true);
                    _chart.setLegendVisible(false);

                    final Scene scene = new Scene(_chart);
                    scene.setOnDragOver(
                        new EventHandler<DragEvent>()
                            {
                                public void handle(DragEvent event)
                                {
                                    Dragboard db = event.getDragboard();
                                    if(event.getGestureSource() != scene && db.hasContent(LocalObjectMimeType))
                                    {
                                        Object object = db.getContent(LocalObjectMimeType);
                                        if(object instanceof MetricsViewTransferableData)
                                        {
                                            event.acceptTransferModes(TransferMode.COPY);
                                        }
                                    }
                                    event.consume();
                                }
                            });

                    scene.setOnDragDropped(
                        new EventHandler<DragEvent>()
                            {
                                public void handle(DragEvent event)
                                {
                                    boolean success = false;
                                    Dragboard db = event.getDragboard();
                                    if(event.getGestureSource() != scene && db.hasContent(LocalObjectMimeType))
                                    {
                                        Object object = db.getContent(LocalObjectMimeType);
                                        if(object instanceof MetricsViewTransferableData)
                                        {
                                            addSeries((MetricsViewTransferableData)object);
                                            success = true;                                            
                                        }
                                    }
                                    event.setDropCompleted(success);
                                    event.consume();
                                }
                            });
                    fxPanel.setScene(scene);
                }
            }, true);

        pack();
        if(!loadPreferences())
        {
            Rectangle otherRect = _coordinator.getMainFrame().getBounds();
            Rectangle thisRect = getBounds();
            if(otherRect.width < thisRect.width || otherRect.height < thisRect.height)
            {
                setLocationRelativeTo(null);
            }
            else
            {
                setLocationRelativeTo(_coordinator.getMainFrame());
            }
            _splitPane.setDividerLocation(400);
        }
        setVisible(true);

        //
        // Show info dialog if required.
        //
        if(showInfo())
        {
            JCheckBox checkbox = new JCheckBox("Do not show this message again.");  
            String message = "Drop metrics cells to add them to the graph.";  

            JOptionPane.showConfirmDialog(this, new Object[]{message, checkbox}, "Information", 
                                          JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE);  
            if(checkbox.isSelected())
            {
                _preferences.node("GraphView").putBoolean("showInfo", false);
            }
        }
    }

    private void removeRows(MetricsViewInfo info)
    {
        //
        // Remove rows from series hash maps
        //
        Map<String, Map<String, Map<String, MetricsRow>>> j = _series.remove(info);
        if(j == null)
        {
            return;
        }

        final List<MetricsRow> rows = new ArrayList<MetricsRow>();
        for(Map.Entry<String, Map<String, Map<String, MetricsRow>>> i : j.entrySet())
        {
            for(Map.Entry<String, Map<String, MetricsRow>> k : i.getValue().entrySet())
            {
                for(Map.Entry<String, MetricsRow> l : k.getValue().entrySet())
                {
                    rows.add(l.getValue());
                }
            }
        }

        int rowIndexes[] = new int[rows.size()];
        for(int i = 0; i < rows.size(); ++i)
        {
            rowIndexes[i] = _legendModel.getRowIndex(rows.get(i));
        }
        _legendModel.removeRows(rowIndexes);

        //
        // Remove series from the chart, in JavaFx thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    for(MetricsRow row : rows)
                    {
                         String seriesClass = getSeriesClass(row.series.peek());
                         if(seriesClass != null)
                         {
                            _styles.remove(seriesClass);
                        }
                        //
                        // Don't remove the XYChart.Series object here, to avoid the series style classes 
                        // to be reasign by JavaFX.
                        //
                        // _chart.getData().remove(row.series);
                        for(int i = 0; i < row.series.size(); ++i)
                        {
                            XYChart.Series<Number, Number> series = row.series.get(i);
                            if(series == null || series.getData() == null)
                            {
                                continue;
                            }

                            while(series.getData().size() > 0)
                            {
                                series.getData().remove(0);
                            }
                        }
                    }
                }
            }, true);
    }

    private boolean showInfo()
    {
        try
        {
            if(!_preferences.nodeExists("GraphView"))
            {
                return true;
            }
        }
        catch(BackingStoreException ex)
        {
            return true;
        }
        return _preferences.node("GraphView").getBoolean("showInfo", true);
    }

    public void storePreferences()
    {
        Preferences preferences = _preferences.node("GraphView");
        Rectangle rect = getBounds();

        for(int i = _columnNames.length -1; i >= 0; --i)
        {
            preferences.putInt("colPos" + Integer.toString(i), _legendTable.convertColumnIndexToModel(i));
            preferences.putInt("colWidth" + Integer.toString(i), _legendTable.getColumnModel().getColumn(i).getWidth());
        }

        preferences.putInt("x", rect.x);
        preferences.putInt("y", rect.y);
        preferences.putInt("width", rect.width);
        preferences.putInt("height", rect.height);
        preferences.putBoolean("maximized", getExtendedState() == Frame.MAXIMIZED_BOTH);
        preferences.putInt("splitLocation", _splitPane.getDividerLocation());

        preferences.putInt("sampleInterval", getRefreshPeriod());
        preferences.putInt("maximumSamples", getMaximumSamples());
        preferences.put("dateFormat", getDateFormat());
    }

    public boolean loadPreferences()
    {
        try
        {
            if(!_preferences.nodeExists("GraphView"))
            {
                return false;
            }
        }
        catch(BackingStoreException ex)
        {
            return false;
        }

        Preferences preferences = _preferences.node("GraphView");

        int x = preferences.getInt("x", 0);
        int y = preferences.getInt("y", 0);
        int width = preferences.getInt("width", 0);
        int height = preferences.getInt("height", 0);
        setBounds(new Rectangle(x, y, width, height));
        if(preferences.getBoolean("maximized", false))
        {
            setExtendedState(Frame.MAXIMIZED_BOTH);
        }
        _splitPane.setDividerLocation(_preferences.node("GraphView").getInt("splitLocation", 600));
        for(int i = _columnNames.length -1; i >= 0; --i)
        {
            int pos = _legendTable.convertColumnIndexToView(preferences.getInt("columnPos" + Integer.toString(i), i));
            if(i != pos)
            {
                _legendTable.getColumnModel().moveColumn(pos, i);
            }            
            int columnWidth = preferences.getInt("colWidth" + Integer.toString(i), -1);
            if(columnWidth != -1)
            {
                _legendTable.getColumnModel().getColumn(i).setPreferredWidth(columnWidth);
            }
        }
        
        int refreshPeriod = preferences.getInt("refreshPeriod", _defaultRefreshPeriod);
        if(refreshPeriod < _minRefreshPeriod)
        {
            refreshPeriod = _minRefreshPeriod;
        }
        else if(refreshPeriod > _maxRefreshPeriod)
        {
            refreshPeriod = _maxRefreshPeriod;
        }
        setRefreshPeriod(refreshPeriod);

        int samples = preferences.getInt("maximumSamples", _defaultSamples);
        if(samples < _minSamples)
        {
            samples = _minSamples;
        }
        else if(samples > _maxSamples)
        {
            samples = _maxSamples;
        }
        setMaximumSamples(samples);

        setDateFormat(preferences.get("dateFormat", getDateFormat()));
        return true;
    }

    public void close()
    {
        storePreferences();
        stopRefreshThread();
        setVisible(false);
        _coordinator.removeGraphView(GraphView.this);
        dispose();
    }

    public void addSeries(final MetricsViewTransferableData data)
    {
        //
        // Must run in JavaFX thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    Map<String, Map<String, Map<String, MetricsRow>>> metrics = _series.get(data.info);
                    if(metrics == null)
                    {
                        metrics = new HashMap<String, Map<String, Map<String, MetricsRow>>>();
                        _series.put(data.info, metrics);
                    }

                    Map<String, Map<String, MetricsRow>> rows = metrics.get(data.name);
                    if(rows == null)
                    {
                        rows = new HashMap<String, Map<String, MetricsRow>>();
                        metrics.put(data.name, rows);
                    }

                    for(Map.Entry<String, List<MetricsCell>> i : data.rows.entrySet())
                    {
                        final String rowId = i.getKey();
                        Map<String, MetricsRow> columns = rows.get(rowId);
                        if(columns == null)
                        {
                            columns = new HashMap<String, MetricsRow>();
                            rows.put(rowId, columns);
                        }

                        for(MetricsCell j : i.getValue())
                        {
                            if(columns.get(j.getField().getFieldName()) == null)
                            {
                                String color = DefaultColors[_chart.getData().size() % DefaultColors.length];
                                final MetricsRow row = new MetricsRow(data.info, j, color, 
                                                                      new XYChart.Series<Number, Number>());

                                XYChart.Series<Number, Number> series = row.series.peek();
                                _chart.getData().add(series);

                                String styleClass = getSeriesClass(series);
                                addStyle(series, styleClass, color);
                                setNodesStyle(styleClass);

                                columns.put(j.getField().getFieldName(), row);
                                j.getField().setContext(GraphView.this);
                                //
                                // When a line is clicked we select the correspoding row in the legend table.
                                //
                                javafx.scene.Node n = _chart.lookup(".chart-series-line." + styleClass);
                                if(n != null)
                                {
                                    n.setOnMousePressed(new EventHandler<MouseEvent>()
                                    {
                                        @Override public void 
                                        handle(MouseEvent e)
                                        {
                                            if(e.getEventType() == MouseEvent.MOUSE_PRESSED &&
                                               e.getButton() == MouseButton.PRIMARY)
                                            {
                                                //
                                                // Must run in Swing thread.
                                                //
                                                _queue.enqueue(new Runnable()
                                                    {
                                                        public void run()
                                                        {
                                                            int i = _legendModel.getRowIndex(row);
                                                            if(i != -1)
                                                            {
                                                                i = _legendTable.convertRowIndexToView(i);
                                                                _legendTable.setRowSelectionInterval(i, i);
                                                            }
                                                        }
                                                    }, false);
                                            }
                                        }
                                    });
                                }
                                //
                                // Add the serie to the legend, must run in Swing thread.
                                //
                                _queue.enqueue(new Runnable()
                                    {
                                        public void run()
                                        {
                                            _legendModel.addRow(row);
                                        }
                                    }, false);
                            } 
                        }
                    }
                    if(_chart.getData().size() > 0)
                    {
                        startRefreshThread();
                    }
                }
            }, true);
    }

    //
    // Added a new chart series to an existing row, the graph series will use the
    // same configuration, the row cell field must be reset so calculations doesn't 
    // take into account previous data. If we don't reset fields here caculations
    // can be bogus in case the view was disabled and the data in the view was reset.
    //
    void addSeries(final MetricsRow row)
    {
        XYChart.Series<Number, Number> series = new XYChart.Series<Number, Number>();
        row.series.push(series);
        _chart.getData().add(series);

        //
        // Retrieve the style class asigned by JavaFX to this series, and set the
        // same style
        //
        String styleClass = getSeriesClass(series);
        addStyle(series, styleClass, row.color);
        setNodesStyle(styleClass);

        //
        // Reset the cell field necessary to avoid bogus calculations.
        //
        row.cell.resetField();

        //
        // We need also a new click handler so click works in all segments 
        // of the line.
        // 
        // When a line is clicked we select the correspoding row in the legend table.
        //
        javafx.scene.Node n = _chart.lookup(".chart-series-line." + styleClass);
        if(n != null)
        {
            n.setOnMousePressed(new EventHandler<MouseEvent>()
            {
                @Override public void 
                handle(MouseEvent e)
                {
                    if(e.getEventType() == MouseEvent.MOUSE_PRESSED &&
                       e.getButton() == MouseButton.PRIMARY)
                    {
                        //
                        // Must run in Swing thread.
                        //
                        _queue.enqueue(new Runnable()
                            {
                                public void run()
                                {
                                    int i = _legendModel.getRowIndex(row);
                                    if(i != -1)
                                    {
                                        i = _legendTable.convertRowIndexToView(i);
                                        _legendTable.setRowSelectionInterval(i, i);
                                    }
                                }
                            }, false);
                    }
                }
            });
        }
    }

    private void addData(final MetricsViewInfo info, final Map<String, IceMX.Metrics[]> data, 
                         final long timestamp)
    {
        //
        // Update the graph series in JavaFX thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    Map<String, Map<String, Map<String, MetricsRow>>> series = _series.get(info);
                    if(series == null)
                    {
                        return;
                    }

                    for(Map.Entry<String, Map<String, Map<String, MetricsRow>>> i : series.entrySet())
                    {
                        IceMX.Metrics[] metricsSeq = null;
                        if(data != null)
                        {
                            metricsSeq = data.get(i.getKey());
                        }

                        //
                        // Iterate over all configured values, if there isn't data for one configured
                        // field we need to add a gap.
                        //

                        for(Map.Entry<String, Map<String, MetricsRow>> j : i.getValue().entrySet())
                        {
                            IceMX.Metrics metrics = null;

                            if(metricsSeq != null)
                            {
                                for(IceMX.Metrics m : metricsSeq)
                                {
                                    if(m.id.equals(j.getKey()))
                                    {
                                        metrics = m;
                                        break;
                                    }
                                }
                            }
                            for(Map.Entry<String, MetricsRow> k : j.getValue().entrySet())
                            {
                                MetricsRow row = k.getValue();
                                //
                                // If there isn't a metrics object we disable the row and add a dummy value.
                                //
                                if(metrics == null)
                                {
                                    //
                                    // If the row isn't disabled we add a new serie to represent the gap
                                    // and mark the row as disabled.
                                    //
                                    if(!row.disabled)
                                    {
                                        row.series.push(new XYChart.Series<Number, Number>());
                                        row.disabled = true;
                                    }
                                    //
                                    // This dummy value is added to represent gap sizes, but isn't displayed
                                    // as the series isn't added to the graph.
                                    //
                                    row.series.peek().getData().add(new XYChart.Data<Number, Number>(0, 0));
                                }
                                else
                                {
                                    try
                                    {
                                        if(row.disabled)
                                        {
                                            addSeries(row);
                                            row.disabled = false;
                                        }

                                        Number value = row.cell.getValue(metrics, timestamp);
                                        //
                                        // The cell returns null to indicate the value must be skipped,
                                        // this is usually because it needs two values to calculate
                                        // the average.
                                        //
                                        if(value == null)
                                        {
                                            continue;
                                        }

                                        row.series.peek().getData().add(
                                            new XYChart.Data<Number, Number>(timestamp, value));
                                    }
                                    catch(java.lang.RuntimeException ex)
                                    {
                                        ex.printStackTrace();
                                    }
                                }

                                //
                                // Remove the vertices from the beginning of the series that exceeded 
                                // the maximum number of samples.
                                //
                                adjustSize(row);
                            }
                        }
                    }
                    //
                    // Fire an event on the legend model to update all cells.
                    //
                    _queue.enqueue(new Runnable()
                        {
                            public void run()
                            {
                                _legendModel.fireTableChanged(
                                            new TableModelEvent(_legendModel, 0, _legendModel.getRowCount() - 1, 
                                                                TableModelEvent.ALL_COLUMNS, 
                                                                TableModelEvent.UPDATE));
                            }
                        }, false);
                }
            }, true);
    }

    int seriesSize(MetricsRow row)
    {
        int size = 0;
        for(int i = 0; i < row.series.size(); ++i)
        {
            size += row.series.get(i).getData().size();
        }
        return size;
    }

    void adjustSize(MetricsRow row)
    {
        int samples = seriesSize(row);
        final int n = getMaximumSamples();
        while(samples > n)
        {
            for(int i = 0; i < row.series.size(); ++i)
            {
                XYChart.Series<Number, Number> series = row.series.get(i);
                while(series.getData().size() > 0 && samples > n)
                {
                    try
                    {
                        series.getData().remove(0);
                    }
                    catch(java.lang.NullPointerException ex)
                    {
                        // JavaFX bug
                    }
                    samples--;

                    //
                    // Remove empty series not longer in use, if there is only one
                    // series that is keep to add new values.
                    //
                    if(series.getData().size() == 0 && row.series.size() > 1)
                    {
                        row.series.remove(series);
                        i--;
                    }
                }
            }
        }
    }

    synchronized private void startRefreshThread()
    {
        if(_refreshThread == null)
        {
            _refreshThread = new RefreshThread(getRefreshPeriod());
            _refreshThread.start();
        }
    }

    synchronized private void stopRefreshThread()
    {
        if(_refreshThread != null)
        {
            _refreshThread.done();
            _refreshThread = null;
        }
    }

    public synchronized int getRefreshPeriod()
    {
        return _refreshPeriod;
    }

    synchronized void setRefreshPeriod(int refreshPeriod)
    {
        if(refreshPeriod == _refreshPeriod)
        {
            return;
        }

        _refreshPeriod = refreshPeriod;
        if(_refreshThread != null)
        {
            _refreshThread.setRefreshPeriod(_refreshPeriod);
        }
    }

    synchronized String getDateFormat()
    {
        return _dateFormat;
    }

    synchronized void setDateFormat(String dateFormat)
    {
        _dateFormat = dateFormat;
        _timeFormater.setDateFormat(dateFormat);
        //
        // Update the horizontal axis label, in JavaFx thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    _xAxis.setLabel("Time (" + getDateFormat() + ")");
                }
            }, true);
    }

    synchronized private void setMaximumSamples(final int samples)
    {
        if(samples == _samples)
        {
            return;
        }

        if(samples < _samples)
        {
            _samples = samples;
            //
            // If maximum samples change, we remove older samples.
            //
            _queue.enqueue(new Runnable()
                {
                    @Override
                    public void run()
                    {
                        MetricsRow[] rows = _legendModel.getRows();
                        for(MetricsRow row : rows)
                        {
                            adjustSize(row);
                        }
                    }
                }, true);
        }
        else
        {
            _samples = samples;
        }
    }

    synchronized private int getMaximumSamples()
    {
        return _samples;
    }

    class MetricsRow
    {
        public MetricsRow(MetricsViewInfo info, MetricsCell cell, String color, XYChart.Series<Number, Number> series)
        {
            this.visible = true;
            this.disabled = false;
            this.info = info;
            this.cell = cell;
            this.color = color;
            this.series.push(series);
        }

        boolean visible;
        boolean disabled;
        MetricsViewInfo info;
        MetricsCell cell;
        String color;
        //
        // Stack of all the chart series used to represent this metrics object
        // new values are added to the chart series at the top.
        //
        Stack<XYChart.Series<Number, Number>> series = new Stack<XYChart.Series<Number, Number>>();
    }

    class LegendTableModel extends javax.swing.table.AbstractTableModel
    {
        public String getColumnName(int col)
        {
            return _columnNames[col];
        }

        public int getRowCount()
        {
            return _rows.size();
        }

        public int getColumnCount()
        {
            return _columnNames.length;
        }

        public Class getColumnClass(int columnIndex)
            {
            switch(columnIndex)
            {
                case 0: // Node Name
                {
                    return Boolean.class;
                }
                case 1: // Node Name
                {
                    return String.class;
                }
                case 2: // Server Name
                {
                    return String.class;
                }
                case 3: // View Name
                {
                    return String.class;
                }
                case 4: // Metrics Name
                {
                    return String.class;
                }
                case 5: // Metrics Id
                {
                    return String.class;
                }
                case 6: // Column Name
                {
                    return String.class;
                }
                case 7: // Scale factor
                {
                    return Double.class;
                }
                case 8: // Last value
                {
                    return Double.class;
                }
                case 9: // Average value
                {
                    return Double.class;
                }
                case 10: // Min value
                {
                    return Double.class;
                }
                case 11: // Max value
                {
                    return Double.class;
                }
                case 12: // Color
                {
                    return Color.class;
                }
                default:
                {
                    return null;
                }
            }
            }

        public Object getValueAt(int rowIndex, int columnIndex)
        {
            if(rowIndex > _rows.size() || columnIndex > _columnNames.length)
            {
                return null;
            }
            MetricsRow row = _rows.get(rowIndex);
            switch(columnIndex)
            {
                case 0:
                {
                    return row.visible;
                }
                case 1:
                {
                    return row.info.node;
                }
                case 2:
                {
                    return row.info.server;
                }
                case 3:
                {
                    return row.info.view;
                }
                case 4:
                {
                    return row.cell.getField().getMetricsName();
                }
                case 5:
                {
                    return row.cell.getId();
                }
                case 6:
                {
                    return row.cell.getField().getColumnName();
                }
                case 7:
                {
                    return row.cell.getScaleFactor();
                }
                case 8:
                {
                    return row.cell.getLast();
                }
                case 9:
                {
                    return row.cell.getAverage();
                }
                case 10:
                {
                    return row.cell.getMin();
                }
                case 11:
                {
                    return row.cell.getMax();
                }
                case 12:
                {
                    return new Color(Integer.parseInt(row.color.substring(1), 16));
                }
                default:
                {
                    return null;
                }
            }
        }

        public boolean isCellEditable(int row, int col)
        {
            if(col < _columnNames.length && (_columnNames[col].equals("Show") || 
                                             _columnNames[col].equals("Scale") ||
                                             _columnNames[col].equals("Color")))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void setValueAt(final Object value, int rowIndex, int columnIndex)
        {
            if(isCellEditable(rowIndex, columnIndex))
            {
                final MetricsRow row = _rows.get(rowIndex);
                if(_columnNames[columnIndex].equals("Show"))
                {
                    row.visible = ((Boolean)value).booleanValue();
                    _queue.enqueue(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                for(int i = 0; i < row.series.size(); ++i)
                                {
                                    setNodesVisible(getSeriesClass(row.series.get(i)), row.visible);
                                }
                            }
                        }, true);
                }
                else if(_columnNames[columnIndex].equals("Scale"))
                {
                    double s1 = ((Double)getValueAt(rowIndex, columnIndex)).doubleValue();
                    double s2 = ((Double)value).doubleValue();
                    for(int i = 0; i < row.series.size(); ++i)
                    {
                        updateScaleFactor(row.series.get(i), s1, s2);
                    }
                    row.cell.setScaleFactor(((Double)value).doubleValue());
                }
                else if(_columnNames[columnIndex].equals("Color"))
                {
                    Color color = (Color)value;
                    //
                    // Convert color to the CSS representation used by JavaFX style.
                    // example: #ff00aa
                    //
                    row.color = "#" + String.format("%02X", color.getRed()) + 
                                      String.format("%02X", color.getGreen()) +
                                      String.format("%02X", color.getBlue());
                    for(int i = 0; i < row.series.size(); ++i)
                    {
                        updateSeriesColor(row.series.get(i), row.color);
                    }
                }
                fireTableCellUpdated(rowIndex, columnIndex);
            }
        }

        public void addRow(MetricsRow row)
        {
            int i = _rows.size();
            _rows.put(i, row);
            fireTableRowsInserted(i, i);
        }

        public MetricsRow[] removeRows(int[] rowIndexes)
        {
            MetricsRow[] deletedRows = new MetricsRow[rowIndexes.length];
            for(int i = 0; i < rowIndexes.length; i++)
            {
                deletedRows[i] = _rows.remove(rowIndexes[i]);
            }
            Map<Integer, MetricsRow> rows = new HashMap<Integer, MetricsRow>();
            for(Map.Entry<Integer, MetricsRow> e : _rows.entrySet())
            {
                rows.put(rows.size(), e.getValue());
            }
            _rows = rows;
            fireTableDataChanged();
            return deletedRows;
        }

        public MetricsRow[] getRows(int[] rowIndexes)
        {
            MetricsRow[] rows = new MetricsRow[rowIndexes.length];
            for(int i = 0; i < rowIndexes.length; i++)
            {
                rows[i] = _rows.get(rowIndexes[i]);
            }
            return rows;
        }

        public MetricsRow[] getRows()
        {
            return _rows.values().toArray(new MetricsRow[_rows.size()]);
        }

        public int getRowIndex(MetricsRow row)
        {
            int index = -1;
            for(Map.Entry<Integer, MetricsRow> entry : _rows.entrySet())
            {
                if(row == entry.getValue())
                {
                    index = entry.getKey();
                    break;
                }
            }
            return index;
        }

        private Map<Integer, MetricsRow> _rows = new HashMap<Integer, MetricsRow>();
    }

    void
    updateScaleFactor(final XYChart.Series<Number, Number> series, final double s1, final double s2)
    {
        //
        // Must run in JavaFX thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    for(XYChart.Data<Number, Number> i : series.getData())
                    {
                        i.setYValue(i.getYValue().doubleValue() * s2 / s1);
                    }
                }
            }, true);
    }

    void
    updateSeriesColor(final XYChart.Series<Number, Number> series, final String color)
    {
        //
        // Must run in JavaFX thread.
        //
        _queue.enqueue(new Runnable()
            {
                @Override
                public void run()
                {
                    String styleClass = getSeriesClass(series);
                    if(styleClass != null)
                    {
                        addStyle(series, styleClass, color);
                        setNodesStyle(styleClass);
                    }
                }
            }, true);
    }

    //
    // Must be called in JavaFX thread.
    //
    // Return the class used to style a serie.
    //
    public String getSeriesClass(XYChart.Series<Number, Number> series)
    {
        if(series == null || series.getNode() == null || series.getNode().getStyleClass() == null)
        {
            return null;
        }
        String value = null;
        for(String styleClass : series.getNode().getStyleClass())
        {
            if(styleClass.startsWith("series"))
            {
                value = styleClass;
                break;
            }
        }
        return value;
    }

    //
    // Must be called on JavaFX thread
    //
    private void setNodesStyle(String seriesClass)
    {
        String style = _styles.get(seriesClass);
        for(javafx.scene.Node n : _chart.lookupAll("." + seriesClass))
        {
            n.setStyle(style);
            //
            // Disable effects like shadows. This effect doesn't look good in some
            // Windows versions.
            //
            n.setEffect(null);
        }
    }

    //
    // Must be called on JavaFX thread
    //
    private void setNodesVisible(String seriesClass, boolean visible)
    {
        for(javafx.scene.Node n : _chart.lookupAll("." + seriesClass))
        {
            n.setVisible(visible);
        }
    }

    //
    // Must be called on JavaFX thread
    //
    private void addStyle(XYChart.Series<Number, Number> series, String seriesClass, String color)
    {
        //
        // Customize the style.
        //
        StringBuilder sb = new StringBuilder();
        sb.append("-fx-stroke: ");
        sb.append(color);
        sb.append("; ");
        sb.append("-fx-background-color: ");
        sb.append(color);
        sb.append(", white;");
        sb.append("-fx-stroke-width: 3;");
        _styles.put(seriesClass, sb.toString()); 
    }

    static class DecimalRenderer extends DefaultListCellRenderer
    { 
        public DecimalRenderer(ListCellRenderer renderer)
        {
            this._renderer = renderer;
        }
 
        @Override
        public Component
        getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus)
        {
            @SuppressWarnings("unchecked")
            Component c = _renderer.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
            if(c instanceof JLabel)
            {
                ((JLabel) c).setText(_format.format(value));
            }
            else
            {
                c = super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
                setText(_format.format(value));
            }
            return c;
        }

        private ListCellRenderer _renderer;
        private static final DecimalFormat _format = new DecimalFormat("#,###,###,##0.0########");
    }

    public class ColorEditor extends AbstractCellEditor implements TableCellEditor, ActionListener
    {
        public ColorEditor()
        {
            _button = new JButton();
            _button.setActionCommand(EDIT);
            _button.addActionListener(this);
            _button.setBorderPainted(false);

            _colorChooser = new JColorChooser();

            AbstractColorChooserPanel[] panels = _colorChooser.getChooserPanels();
            for(AbstractColorChooserPanel panel : panels)
            {
                if(!panel.getClass().getName().equals("javax.swing.colorchooser.DefaultSwatchChooserPanel"))
                {
                    _colorChooser.removeChooserPanel(panel);
                }
            }

            _dialog = JColorChooser.createDialog(_button, "Select the metrics color", true, _colorChooser, this, null);
            
        }

        public void actionPerformed(ActionEvent e)
        {
            if(EDIT.equals(e.getActionCommand()))
            {
                _button.setBackground(_currentColor);
                _colorChooser.setColor(_currentColor);
                _dialog.setVisible(true);
                //Make the renderer reappear.
                fireEditingStopped();
            }
            else
            {
                _currentColor = _colorChooser.getColor();
            }
        }

        public Object getCellEditorValue()
        {
            return _currentColor;
        }

        public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected,
                                                     int row, int column)
        {
            _currentColor = (Color)value;
            return _button;
        }

        Color _currentColor;
        JButton _button;
        JColorChooser _colorChooser;
        JDialog _dialog;
        protected static final String EDIT = "edit";
    }

    static class ColorRenderer extends JLabel implements TableCellRenderer
    {
        Border unselectedBorder = null;
        Border selectedBorder = null;
        boolean isBordered = true;
 
        public ColorRenderer(boolean isBordered)
        {
            this.isBordered = isBordered;
            setOpaque(true); //MUST do this for background to show up.
        }
 
        public Component getTableCellRendererComponent(JTable table, Object color, boolean isSelected, boolean hasFocus,
                                                       int row, int column)
        {
            Color newColor = (Color)color;
            setBackground(newColor);
            if(isBordered)
            {
                if(isSelected)
                {
                    if(selectedBorder == null)
                    {
                        selectedBorder = BorderFactory.createMatteBorder(2, 5, 2, 5, table.getSelectionBackground());
                    }
                    setBorder(selectedBorder);
                }
                else
                {
                    if(unselectedBorder == null)
                    {
                        unselectedBorder = BorderFactory.createMatteBorder(2, 5, 2, 5, table.getBackground());
                    }
                    setBorder(unselectedBorder);
                }
            }
            return this;
        }
    }

    private final Coordinator _coordinator;
    private RefreshThread _refreshThread;

    private final static int _minRefreshPeriod = 1;         //     1 seconds
    private final static int _maxRefreshPeriod = 60 * 60;   //  3600 seconds = 1 hour.
    private final static int _defaultRefreshPeriod = 5;     //     5 seconds
    private int _refreshPeriod = _defaultRefreshPeriod;

    private int _minSamples = 2;   // We need at least to points to draw a line.
    private int _maxSamples = 300; // More that 300 points in a line doesn't work well with JavaFX charts.
    private int _defaultSamples = 120;
    private int _samples = _defaultSamples;

    private String[] _dateFormats = new String[]{"HH:mm:ss", "mm:ss"};
    private String _dateFormat = _dateFormats[0];
    private final TimeFormatter _timeFormater = new TimeFormatter(_dateFormat);
    private final Object _monitor = new Object();

    private LineChart<Number, Number> _chart;
    private NumberAxis _xAxis;
    private NumberAxis _yAxis;

    private final static String[] _columnNames = new String[]{"Show", "Node", "Server", "Metrics View Name", 
                                                              "Metrics Name", "Metrics Id", "Metrics Field", "Scale", 
                                                              "Last", "Average", "Minimum", "Maximum", "Color"};


    //
    // The metrics view being graph
    //

    //
    // MetricsViewInfo (Metrics view of a server)
    // Metrics Name
    // Row identity
    // Field name
    //
    private final Map<MetricsViewInfo,
        Map<String, 
            Map<String, 
                Map<String, MetricsRow>>>> _series =
                                    new HashMap<MetricsViewInfo, Map<String, Map<String, Map<String, MetricsRow>>>>();

    private final static String MetricsCellFlavor = 
                            "application/x-icegridadmin-metrics-cells; class=java.io.InputStream";

    private final static String[] DefaultColors = new String[]
                                                    {
                                                        "#FF0000", // Red
                                                        "#00FF00", // Lime
                                                        "#00FFFF", // Aqua
                                                        "#FFA07A", // LightSalmon
                                                        "#FFC0CB", // Pink
                                                        "#FFD700", // Gold
                                                        "#CD5C5C", // Indian red
                                                        "#32CD32", // LimeGreen
                                                        "#AFEEEE", // PaleTurquoise
                                                        "#FF4500", // OrangeRed
                                                        "#FF69B4", // HotPink
                                                        "#BDB76B", // DarkKhaki
                                                        "#8B0000", // DarkRed
                                                        "#9ACD32", // YellowGreen
                                                        "#00BFFF", // DeepSkyBlue
                                                        "#4B0082", // Indigo
                                                    };

    private final JTable _legendTable;
    private final LegendTableModel _legendModel = new LegendTableModel();
    private JSplitPane _splitPane;

    private final Map<String, String> _styles = new HashMap<String, String>();

    private final Double[] _scales = new Double[]{0.000000001d, 
                                                  0.00000001d,
                                                  0.0000001d, 
                                                  0.000001d, 
                                                  0.00001d,
                                                  0.0001d, 
                                                  0.001d, 
                                                  0.01d, 
                                                  0.1d, 
                                                  1.0d, 
                                                  10.0d, 
                                                  100.0d,
                                                  1000.0d,
                                                  10000.0d, 
                                                  100000.0d, 
                                                  1000000.0d, 
                                                  10000000.0d,
                                                  100000000.0d,
                                                  1000000000.0d};
    private final WorkQueue _queue;
    private final Preferences _preferences;

    private final static DataFormat LocalObjectMimeType = new DataFormat("application/x-java-jvm-local-objectref");
}

