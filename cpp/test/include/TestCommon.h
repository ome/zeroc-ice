// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <IceUtil/Config.h>
#include <cstdlib>

#ifdef __BCPLUSPLUS__
#include <stdlib.h>
#endif

#if defined(__FreeBSD__)
#  include <sys/types.h>
#  include <sys/sysctl.h>
inline bool inFreeBSDJail()
{
    int jailed;
    size_t size = sizeof(jailed);
    return (sysctlbyname("security.jail.jailed", &jailed, &size, NULL, 0) != -1 || jailed);
}
#else
inline bool inFreeBSDJail()
{
    return false;
}
#endif

void
inline testFailed(const char* expr, const char* file, unsigned int line)
{
    std::cout << "failed!" << std::endl;
    std::cout << file << ':' << line << ": assertion `" << expr << "' failed" << std::endl;
    abort();
}

#define test(ex) ((ex) ? ((void)0) : testFailed(#ex, __FILE__, __LINE__))

#endif
