// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

namespace Ice
{
    /// <summary>
    /// SlicedData holds the slices of unknown class or exception types.
    /// </summary>
    public class SlicedData
    {
        public SlicedData(SliceInfo[] slices)
        {
            this.slices = slices;
        }

        /**
         * The details of each slice, in order of most-derived to least-derived.
         **/
        public SliceInfo[] slices;
    }

    /// <summary>
    /// SliceInfo encapsulates the details of a slice for an unknown class or exception type.
    /// </summary>
    public class SliceInfo
    {
        /// <summary>
        /// The Slice type ID for this slice.
        /// </summary>
        public string typeId;

        /// <summary>
        /// The Slice compact type ID for this slice.
        /// </summary>
        public int compactId;

        /// <summary>
        /// The encoded bytes for this slice, including the leading size integer.
        /// </summary>
        public byte[] bytes;

        /// <summary>
        /// The Ice objects referenced by this slice.
        /// </summary>
        public Ice.Object[] objects;

        /// <summary>
        /// Whether or not the slice contains optional members.
        /// </summary>
        public bool hasOptionalMembers;

        /// <summary>
        /// Whether or not this is the last slice.
        /// </summary>
        public bool isLastSlice;
    }
}
