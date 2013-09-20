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
 * SliceInfo encapsulates the details of a slice for an unknown class or exception type.
 **/
public class SliceInfo
{
    /**
     * The Slice type ID for this slice.
     **/
    public String typeId;

    /**
     * The Slice compact type ID for this slice.
     **/
    public int compactId;

    /**
     * The encoded bytes for this slice, including the leading size integer.
     **/
    public byte[] bytes;

    /**
     * The Ice objects referenced by this slice.
     **/
    public Ice.Object[] objects;

    /**
     * Whether or not the slice contains optional members.
     **/
    public boolean hasOptionalMembers;

    /**
     * Whether or not this is the last slice.
     **/
    public boolean isLastSlice;
}
