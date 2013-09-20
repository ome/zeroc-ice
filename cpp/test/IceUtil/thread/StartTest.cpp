// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/IceUtil.h>

#include <stdio.h>

#include <StartTest.h>
#include <TestCommon.h>

using namespace std;
using namespace IceUtil;

static const string createTestName("thread start");

class StartTestThread : public Thread
{
public:
    
    StartTestThread()
    {
    }

    virtual void run()
    {
    }
};

typedef Handle<StartTestThread> StartTestThreadPtr;

StartTest::StartTest() :
    TestBase(createTestName)
{
}

void
StartTest::run()
{
    //
    // Check that calling start() more than once raises ThreadStartedException.
    //
    StartTestThreadPtr t = new StartTestThread();
    ThreadControl control = t->start();
    control.join();
    try
    {
        t->start();
        test(false);
    }
    catch(const ThreadStartedException&)
    {
    }

    //
    // Now let's create a bunch of short-lived threads
    //
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            Thread* t = new StartTestThread;
            t->start().detach();
        }
        ThreadControl::sleep(Time::milliSeconds(5));
    }
}
