// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_UTIL_SCANNER_CONFIG_H
#define ICE_UTIL_SCANNER_CONFIG_H

#include <IceUtil/Config.h> // Required by generated Scanners.

//
// COMPILERFIX: VC compilers does not provide stdint.h header until VC100
// the header must be included before that macros for integral types
// in flex generated Scanners are defined.
//
// in C99 conformant compilers we don't need to include it because the
// header is included by inttypes.h, that is included by the gernated 
// Scanners.
//
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#   include <stdint.h>
#endif

#endif
