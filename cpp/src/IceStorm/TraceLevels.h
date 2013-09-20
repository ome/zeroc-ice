// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_STORM_TRACE_LEVELS_H
#define ICE_STORM_TRACE_LEVELS_H

#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <Ice/PropertiesF.h>
#include <Ice/LoggerF.h>

namespace IceStorm
{

class TraceLevels : public IceUtil::Shared
{
public:

    TraceLevels(const ::std::string name, const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
    virtual ~TraceLevels();

    const int topicMgr;
    const char* topicMgrCat;

    const int topic;
    const char* topicCat;

    const int subscriber;
    const char* subscriberCat;

    const int election;
    const char* electionCat;

    const int replication;
    const char* replicationCat;

    const Ice::LoggerPtr logger;
};

typedef IceUtil::Handle<TraceLevels> TraceLevelsPtr;

} // End namespace IceStorm

#endif
