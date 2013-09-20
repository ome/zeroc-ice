// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.invoke;

import test.Ice.invoke.Test.MyException;

public class BlobjectI extends Ice.Blobject
{
    public boolean
    ice_invoke(byte[] inParams, Ice.ByteSeqHolder outParams, Ice.Current current)
    {
        Ice.Communicator communicator = current.adapter.getCommunicator();
        Ice.InputStream in = Ice.Util.createInputStream(communicator, inParams);
        in.startEncapsulation();
        Ice.OutputStream out = Ice.Util.createOutputStream(communicator);
        out.startEncapsulation();
        if(current.operation.equals("opOneway"))
        {
            outParams.value = new byte[0];
            return true;
        }
        else if(current.operation.equals("opString"))
        {
            String s = in.readString();
            out.writeString(s);
            out.writeString(s);
            out.endEncapsulation();
            outParams.value = out.finished();
            return true;
        }
        else if(current.operation.equals("opException"))
        {
            MyException ex = new MyException();
            out.writeException(ex);
            out.endEncapsulation();
            outParams.value = out.finished();
            return false;
        }
        else if(current.operation.equals("shutdown"))
        {
            communicator.shutdown();
            return true;
        }
        else if(current.operation.equals("ice_isA"))
        {
            String s = in.readString();
            if(s.equals("::Test::MyClass"))
            {
                out.writeBool(true);
            }
            else
            {
                out.writeBool(false);
            }
            out.endEncapsulation();
            outParams.value = out.finished();
            return true;
        }
        else
        {
            Ice.OperationNotExistException ex = new Ice.OperationNotExistException();
            ex.id = current.id;
            ex.facet = current.facet;
            ex.operation = current.operation;
            throw ex;
        }
    }
}
