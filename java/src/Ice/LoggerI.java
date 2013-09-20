// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

public class LoggerI implements Logger
{
    public 
    LoggerI(String prefix, String file)
    {
        if(prefix.length() > 0)
        {
            _prefix = prefix + ": ";
        }

        _lineSeparator = System.getProperty("line.separator");
        _date = java.text.DateFormat.getDateInstance(java.text.DateFormat.SHORT);
        _time = new java.text.SimpleDateFormat(" HH:mm:ss:SSS");

        if(file.length() != 0)
        {
            _file = file;
            try
            {
                _out = new java.io.FileOutputStream(new java.io.File(_file), true);
            }
            catch(java.io.FileNotFoundException ex)
            {
                throw new InitializationException("FileLogger: cannot open " + _file);
            }
        }
    }

    public void
    print(String message)
    {
        StringBuilder s = new StringBuilder(256);
        s.append(message);
        write(s, false);
    }

    public void
    trace(String category, String message)
    {
        StringBuilder s = new StringBuilder(256);
        s.append("-- ");
        s.append(_date.format(new java.util.Date()));
        s.append(_time.format(new java.util.Date()));
        s.append(' ');
        s.append(_prefix);
        s.append(category);
        s.append(": ");
        s.append(message);
        write(s, true);
    }

    public void
    warning(String message)
    {
        StringBuilder s = new StringBuilder(256);
        s.append("-! ");
        s.append(_date.format(new java.util.Date()));
        s.append(_time.format(new java.util.Date()));
        s.append(' ');
        s.append(_prefix);
        s.append("warning: ");
        s.append(Thread.currentThread().getName());
        s.append(": ");
        s.append(message);
        write(s, true);
    }

    public void
    error(String message)
    {
        StringBuilder s = new StringBuilder(256);
        s.append("!! ");
        s.append(_date.format(new java.util.Date()));
        s.append(_time.format(new java.util.Date()));
        s.append(' ');
        s.append(_prefix);
        s.append("error: ");
        s.append(Thread.currentThread().getName());
        s.append(": ");
        s.append(message);
        write(s, true);
    }

    public Logger
    cloneWithPrefix(String prefix)
    {
        return new LoggerI(prefix, _file);
    }

    private void
    write(StringBuilder message, boolean indent)
    {
        if(indent)
        {
            int idx = 0;
            while((idx = message.indexOf("\n", idx)) != -1)
            {
                message.insert(idx + 1, "   ");
                ++idx;
            }
        }
        message.append(_lineSeparator);

        if(_out == null)
        {
            System.err.print(message.toString());
        }
        else
        {
            try
            {
                _out.write(message.toString().getBytes());
            }
            catch(java.io.IOException ex)
            {
            }
        }
    }

    String _prefix = "";
    String _file = "";
    String _lineSeparator;
    java.text.DateFormat _date;
    java.text.SimpleDateFormat _time;
    java.io.FileOutputStream _out = null;
}
