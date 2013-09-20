// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/UUID.h>
#include <IceUtil/Random.h>
#include <IceUtil/Time.h>
#include <IceUtil/Thread.h>
#include <IceUtil/Mutex.h>
#include <IceUtil/MutexPtrLock.h>
#include <TestCommon.h>
#include <set>
#include <vector>

using namespace IceUtil;
using namespace std;

namespace
{

Mutex* staticMutex = 0;

class Init
{
public:

    Init()
    {
        staticMutex = new IceUtil::Mutex;
    }

    ~Init()
    {
        delete staticMutex;
        staticMutex = 0;
    }
};

Init init;

}

inline void usage(const char* myName)
{
    cerr << "Usage: " << myName << " [number of UUIDs to generate] [number of threads]" << endl;
}

template<typename T, typename GenerateFunc> class InsertThread : public Thread
{
public:
    
    typedef set<T> ItemSet;
    
    InsertThread(int threadId, ItemSet& itemSet, GenerateFunc func, long howMany, bool verbose)
        : _threadId(threadId), _itemSet(itemSet), _func(func), _howMany(howMany), _verbose(verbose)
    {
    }

    void run()
    {
        for(long i = 0; i < _howMany; i++)
        {
            T item = _func();

            IceUtilInternal::MutexPtrLock<IceUtil::Mutex> lock(staticMutex);
            pair<typename ItemSet::iterator, bool> ok = _itemSet.insert(item);
            if(!ok.second)
            {
                cerr << "******* iteration " << i << endl;
                cerr << "******* Duplicate item: " << *ok.first << endl;
            }

            test(ok.second);

            if(_verbose && i > 0 && (i % 100000 == 0))
            {
                cout << "Thread " << _threadId << ": generated " << i << " UUIDs." << endl; 
            }
        }
    }


private:

    int _threadId;
    ItemSet& _itemSet;
    GenerateFunc _func;
    long _howMany;
    bool _verbose;
};

struct GenerateUUID
{
    string
    operator()()
    {
        return generateUUID();
    }
};

struct GenerateRandomString
{
    string
    operator()()
    {
        string s;
        s.resize(20);
        char buf[20];
        IceUtilInternal::generateRandom(buf, static_cast<int>(sizeof(buf)));
        for(unsigned int i = 0; i < sizeof(buf); ++i)
        {
            s[i] = 33 + buf[i] % (127-33); // We use ASCII 33-126 (from ! to ~, w/o space).
        }
        return s;
    }
};

struct GenerateRandomInt
{
public:

    int
    operator()()
    {
        return IceUtilInternal::random();
    }

};

template<typename T, typename GenerateFunc> void
runTest(int threadCount, GenerateFunc func, long howMany, bool verbose, string name)
{
    cout << "Generating " << howMany << " " << name << "s using " << threadCount << " thread";
    if(threadCount > 1)
    {
        cout << "s";
    }
    cout << "... ";
    
    if(verbose)
    {
        cout << endl;
    }
    else
    {
        cout << flush;
    }

    set<T> itemSet;
    
    vector<ThreadControl> threads;

    Time start = Time::now();
    for(int i = 0; i < threadCount; i++)
    {
        ThreadPtr t = new InsertThread<T, GenerateFunc>(i, itemSet, func, howMany / threadCount, verbose); 
        threads.push_back(t->start());
    }
    for(vector<ThreadControl>::iterator p = threads.begin(); p != threads.end(); ++p)
    {
        p->join();
    }
    Time finish = Time::now();

    cout << "ok" << endl;

    if(verbose)
    {
        cout << "Each " << name << " took an average of "  
             << (double) ((finish - start).toMicroSeconds()) / howMany 
             << " micro seconds to generate and insert into a set." 
             << endl;
    }
}

int main(int argc, char* argv[])
{
    long howMany = 300000;
    int threadCount = 3;
    bool verbose = false;

    if(argc > 3)
    {
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    else if(argc == 3)
    {
        howMany = atol(argv[1]);
        if (howMany == 0)
        {
            usage(argv[0]);
            return EXIT_FAILURE;
        }
        threadCount = atoi(argv[2]);
        if(threadCount <= 0)
        {
            usage(argv[0]);
            return EXIT_FAILURE;
        }
        verbose = true;
    }
    else if(argc == 2)
    {
        howMany = atol(argv[1]);
        if (howMany == 0)
        {
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    runTest<string, GenerateUUID>(threadCount, GenerateUUID(), howMany, verbose, "UUID");
    runTest<string, GenerateRandomString>(threadCount, GenerateRandomString(), howMany, verbose, "string");

    return EXIT_SUCCESS;
}
