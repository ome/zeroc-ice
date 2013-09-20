// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef CUSTOM_MAP_H
#define CUSTOM_MAP_H

#include <IceUtil/Config.h>

#ifdef ICE_CPP11
#   include <unordered_map>
#else
#   include <map>
#endif

namespace Test
{

#ifdef ICE_CPP11
template<typename K, typename V>
class CustomMap : public std::unordered_map<K, V>
{
};
#else
template<typename K, typename V>
class CustomMap : public std::map<K, V>
{
};
#endif

}

#endif
