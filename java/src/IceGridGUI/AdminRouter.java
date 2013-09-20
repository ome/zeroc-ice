// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceGridGUI;

import IceGrid.*;

class AdminRouter extends Ice.Blobject
{
    public boolean ice_invoke(byte[] inParams, Ice.ByteSeqHolder outParams, Ice.Current current)
    {
        if(_admin == null)
        {
            throw new Ice.ObjectNotExistException(current.id, current.facet, current.operation);
        }
        else if(current.operation.equals("ice_id") ||
                current.operation.equals("ice_ids") ||
                current.operation.equals("ice_isA") ||
                current.operation.equals("ice_ping") ||
                current.operation.equals("getDefaultApplicationDescriptor"))
        {
            return _admin.ice_invoke(current.operation, current.mode, inParams, outParams, current.ctx);
        }
        else
        {
            //
            // Routing other operations could be a security risk
            //
            throw new Ice.OperationNotExistException(current.id, current.facet, current.operation);
        }
    }

    AdminRouter(AdminPrx admin)
    {
        _admin = admin;
    }

    private final AdminPrx _admin;
}
