// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

//
// Class to provide a java.io.InputStream on top of a BasicStream.
// We use this to deserialize arbitrary Java serializable classes from
// a Slice byte sequence. This class is a wrapper around a BasicStream
// that passes all methods through.
//

public class InputStreamWrapper extends java.io.InputStream
{
    public
    InputStreamWrapper(int size, BasicStream s)
    {
        _s = s;
        _markPos = 0;
    }

    public int
    read()
        throws java.io.IOException
    {
        try
        {
            return _s.getBuffer().b.get();
        }
        catch(java.lang.Exception ex)
        {
            throw new java.io.IOException(ex.toString());
        }
    }

    public int
    read(byte[] b)
        throws java.io.IOException
    {
        return read(b, 0, b.length);
    }

    public int
    read(byte[] b, int offset, int count)
        throws java.io.IOException
    {
        try
        {
            _s.getBuffer().b.get(b, offset, count);
        }
        catch(java.lang.Exception ex)
        {
            throw new java.io.IOException(ex.toString());
        }
        return count;
    }

    public int
    available()
    {
        return _s.getBuffer().b.remaining();
    }

    public void
    mark(int readlimit)
    {
        _markPos = _s.pos();
    }

    public void
    reset()
        throws java.io.IOException
    {
        _s.pos(_markPos);
    }

    public boolean
    markSupported()
    {
        return true;
    }

    public void
    close()
        throws java.io.IOException
    {
    }

    private BasicStream _s;
    private int _markPos;
}
