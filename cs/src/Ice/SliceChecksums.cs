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

    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Reflection;

    public sealed class SliceChecksums
    {
        public static Dictionary<string, string> checksums = new Dictionary<string, string>();

#if !COMPACT && !SILVERLIGHT
        static SliceChecksums()
        {
            Type[] types = IceInternal.AssemblyUtil.findTypesWithPrefix("IceInternal.SliceChecksums");
            foreach(Type t in types)
            {
                FieldInfo f = t.GetField("map", BindingFlags.Public | BindingFlags.Static);
                Hashtable map = (Hashtable)f.GetValue(null);
                foreach(DictionaryEntry entry in map)
                {
                    checksums.Add((string)entry.Key, (string)entry.Value);
                }
            }
        }
#endif
    }

}
