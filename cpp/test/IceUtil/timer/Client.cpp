// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/Timer.h>
#include <TestCommon.h>

#include <vector>

using namespace IceUtil;
using namespace std;

class TestTask : public IceUtil::TimerTask, IceUtil::Monitor<IceUtil::Mutex>
{
public:

    TestTask() : _count(0)
    {
    }

    TestTask(const IceUtil::Time& scheduledTime) : _scheduledTime(scheduledTime), _count(0)
    {
    }

    virtual void
    runTimerTask()
    {
        Lock sync(*this);
        ++_count;
        _run = IceUtil::Time::now(IceUtil::Time::Monotonic);
        //cerr << "run: " << _scheduledTime.toMilliSeconds() << " " << _run.toMilliSeconds() << endl;
        notifyAll();
    }

    virtual bool
    operator<(const TestTask& r) const
    {
        return _scheduledTime < r._scheduledTime;
    }

    virtual bool
    hasRun() const
    {
        Lock sync(*this);
        return _run != IceUtil::Time();
    }

    int
    getCount() const
    {
        Lock sync(*this);
        return _count;
    }

    virtual IceUtil::Time
    getRunTime() const
    {
        Lock sync(*this);
        return _run;
    }

    IceUtil::Time
    getScheduledTime() const
    {
        return _scheduledTime;
    }

    virtual void
    waitForRun()
    {
        Lock sync(*this);
        while(_run == IceUtil::Time())
        {
            if(!timedWait(IceUtil::Time::seconds(10)))
            {
                test(false); // Timeout.
            }
        }
    }

    void
    clear()
    {
        _run = IceUtil::Time();
        _count = 0;
    }

private:

    IceUtil::Time _run;
    IceUtil::Time _scheduledTime;
    int _count;
};
typedef IceUtil::Handle<TestTask> TestTaskPtr;


class DestroyTask : public IceUtil::TimerTask, IceUtil::Monitor<IceUtil::Mutex>
{
public:

    DestroyTask(const IceUtil::TimerPtr& timer) : _timer(timer), _run(false)
    {
    }

    virtual void
    runTimerTask()
    {
        Lock sync(*this);
        _timer->destroy();
        _run = true;
        notify();
    }

    virtual void
    waitForRun()
    {
        Lock sync(*this);
        while(!_run)
        {
            if(!timedWait(IceUtil::Time::seconds(10)))
            {
                test(false); // Timeout.
            }
        }
    }

private:

    IceUtil::TimerPtr _timer;
    bool _run;
};
typedef IceUtil::Handle<DestroyTask> DestroyTaskPtr;

int main(int, char**)
{
    cout << "testing timer... " << flush;
    {
        IceUtil::TimerPtr timer = new IceUtil::Timer();

        {
            TestTaskPtr task = new TestTask();
            timer->schedule(task, IceUtil::Time());
            task->waitForRun();
            task->clear();

            //
            // Verify that the same task cannot be scheduled more than once.
            //
            timer->schedule(task, IceUtil::Time::milliSeconds(100));
            try
            {
                timer->schedule(task, IceUtil::Time());
            }
            catch(const IceUtil::IllegalArgumentException&)
            {
                // Expected.
            }
            task->waitForRun();
            task->clear();
        }

        {
            TestTaskPtr task = new TestTask();
            test(!timer->cancel(task));
            timer->schedule(task, IceUtil::Time::seconds(1));
            test(!task->hasRun() && timer->cancel(task) && !task->hasRun());
            test(!timer->cancel(task));
            IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(1100));
            test(!task->hasRun());
        }

        {
            vector<TestTaskPtr> tasks;
            IceUtil::Time start = IceUtil::Time::now(IceUtil::Time::Monotonic) + IceUtil::Time::milliSeconds(500);
            for(int i = 0; i < 20; ++i)
            {
                tasks.push_back(new TestTask(IceUtil::Time::milliSeconds(500 + i * 5)));
            }

            random_shuffle(tasks.begin(), tasks.end());
            vector<TestTaskPtr>::const_iterator p;
            for(p = tasks.begin(); p != tasks.end(); ++p)
            {
                timer->schedule(*p, (*p)->getScheduledTime());
            }

            for(p = tasks.begin(); p != tasks.end(); ++p)
            {
                (*p)->waitForRun();
            }

            test(IceUtil::Time::now(IceUtil::Time::Monotonic) > start);

            sort(tasks.begin(), tasks.end());
            for(p = tasks.begin(); p + 1 != tasks.end(); ++p)
            {
                if((*p)->getRunTime() > (*(p + 1))->getRunTime())
                {
                    test(false);
                }
            }
        }

        {
            TestTaskPtr task = new TestTask();
            timer->scheduleRepeated(task, IceUtil::Time::milliSeconds(20));
            IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(500));
            test(task->hasRun());
            test(task->getCount() > 1);
            test(task->getCount() < 26);
            test(timer->cancel(task));
            int count = task->getCount();
            IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(100));
            test(count == task->getCount() || count + 1 == task->getCount());
        }

        timer->destroy();
    }
    cout << "ok" << endl;

    cout << "testing timer destroy... " << flush;
    {
        {
            IceUtil::TimerPtr timer = new IceUtil::Timer();
            DestroyTaskPtr destroyTask = new DestroyTask(timer);
            timer->schedule(destroyTask, IceUtil::Time());
            destroyTask->waitForRun();
            try
            {
                timer->schedule(destroyTask, IceUtil::Time());
            }
            catch(const IceUtil::IllegalArgumentException&)
            {
                // Expected;
            }
        }
        {
            IceUtil::TimerPtr timer = new IceUtil::Timer();
            TestTaskPtr testTask = new TestTask();
            timer->schedule(testTask, IceUtil::Time());
            timer->destroy();
            try
            {
                timer->schedule(testTask, IceUtil::Time());
            }
            catch(const IceUtil::IllegalArgumentException&)
            {
                // Expected;
            }
        }
    }
    cout << "ok" << endl;

    return EXIT_SUCCESS;
}
