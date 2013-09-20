// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Metrics.ice>

module IceMX
{

/**
 *
 * Provides information on Glacier2 sessions.
 *
 **/
class SessionMetrics extends Metrics
{
    /**
     *
     * Number of client requests forwared.
     *
     **/
    int forwardedClient = 0;

    /**
     *
     * Number of server requests forwared.
     *
     **/
    int forwardedServer = 0;
 
    /**
     *
     * The size of the routing table.
     * 
     **/
    int routingTableSize = 0;
 
    /**
     *
     * Number of client requests queued.
     *
     **/
    int queuedClient = 0;

    /**
     *
     * Number of server requests queued.
     *
     **/
    int queuedServer = 0;
 
    /**
     *
     * Number of client requests overridden.
     *
     **/
    int overriddenClient = 0;

    /**
     *
     * Number of server requests overridden.
     *
     **/
    int overriddenServer = 0;
};

};
