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
 * Provides information on IceStorm topics.
 *
 **/
class TopicMetrics extends Metrics
{
    /**
     *
     * Number of events published on the topic by publishers.
     *
     **/
    long published = 0;

    /**
     *
     * Number of events forwarded on the topic by IceStorm topic links.
     *
     **/
    long forwarded = 0;
};

/**
 *
 * Provides information on IceStorm subscribers.
 *
 **/
class SubscriberMetrics extends Metrics
{
    /**
     *
     * Number of queued events.
     *
     **/
    int queued = 0;

    /**
     *
     * Number of outstanding events.
     *
     **/
    int outstanding = 0; 

    /**
     *
     * Number of forwarded events.
     *
     **/
    long delivered = 0;
};

};
