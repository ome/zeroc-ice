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
 * This enumeration describes the possible formats for classes and exceptions.
 **/
public enum FormatType
{
    /**
     * Indicates that no preference was specified.
     **/
    DefaultFormat,
    /**
     * A minimal format that eliminates the possibility for slicing unrecognized types.
     **/
    CompactFormat,
    /**
     * Allow slicing and preserve slices for unknown types.
     **/
    SlicedFormat
}
