// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["cpp:header-ext:h"]]

#include <IceStorm/FreezeDB/LinkRecord.ice>

module IceStorm
{

/** Dictionary of link name to link record. */
dictionary<string, LinkRecord> LinkRecordDict;

}; // End module IceStorm

