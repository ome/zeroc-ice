// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

/**
 * Interface for incoming requests.
 **/
public interface Request
{   
    /**
     * Returns whether this request is collocated.
     *
     * @return <code>true</code> if the invocation was made via proxy created by the same communicator
     * that hosts the target's object adapter; <code>false</code>, otherwise.
     **/
    boolean isCollocated();

    /**
     * Returns the {@link Current} object for this the request.
     *
     * @return The {@link Current} object for this request.
     **/
    Current getCurrent();
}
