// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_UTIL_THREAD_H
#define ICE_UTIL_THREAD_H

#include <IceUtil/Config.h>
#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <IceUtil/Mutex.h>

#ifdef ICE_OS_WINRT
#   include <memory>
#   include <thread>
#endif

namespace IceUtil
{

class Time;

class ICE_UTIL_API ThreadControl
{
public:

    //
    // Constructs a ThreadControl representing the current thread.
    // join and detach cannot be called on such ThreadControl object.
    //
    ThreadControl();

#ifdef ICE_OS_WINRT
    ThreadControl(const std::shared_ptr<std::thread>&);
#elif defined(_WIN32)
    ThreadControl(HANDLE, DWORD);
#else
    explicit ThreadControl(pthread_t);
#endif

    //
    // Default copy destructor, assignment operator and destructor OK
    //

    //
    // == and != are meaningful only before the thread is joined/detached,
    // or while the thread is still running.
    //
    bool operator==(const ThreadControl&) const;
    bool operator!=(const ThreadControl&) const;

    //
    // Wait until the controlled thread terminates. The call has POSIX
    // semantics.
    //
    // At most one thread can wait for the termination of a given
    // thread. Calling join on a thread on which another thread is
    // already waiting for termination results in undefined behaviour,
    // as does joining with a thread after having joined with it
    // previously, or joining with a detached thread.
    //
    void join();

    //
    // Detach a thread. Once a thread is detached, it cannot be
    // detached again, nor can it be joined with. Every thread that
    // was created using the IceUtil::Thread class must either be
    // joined with or detached exactly once. Detaching a thread a
    // second time, or detaching a thread that was previously joined
    // with results in undefined behavior.
    //
    void detach();

    //
    // id() returns the Thread ID on Windows and the underlying pthread_t
    // on POSIX platforms.
    //
#ifdef ICE_OS_WINRT
    typedef std::thread::id ID;
#elif defined(_WIN32)
    typedef DWORD ID;
#else
    typedef pthread_t ID;
#endif 
    ID id() const;

    static void sleep(const Time&);
    static void yield();

private:

#ifdef ICE_OS_WINRT
    std::shared_ptr<std::thread> _thread;
    std::thread::id _id;
#elif defined(_WIN32)
    HANDLE _handle;
    DWORD  _id;
#else
    pthread_t _thread;

    //
    // Used to prevent joining/detaching a ThreadControl constructed
    // with the default constructor. Only needed to enforce our
    // portable join/detach behavior.
    //
    bool _detachable;
#endif
};

class ICE_UTIL_API Thread : virtual public IceUtil::Shared
{
public:

    Thread();
    Thread(const std::string&);
    virtual ~Thread();

    virtual void run() = 0;

    ThreadControl start(size_t = 0);
    ThreadControl start(size_t, int priority);

    ThreadControl getThreadControl() const;

    bool operator==(const Thread&) const;
    bool operator!=(const Thread&) const;
    bool operator<(const Thread&) const;

    //
    // Check whether a thread is still alive.
    //
    bool isAlive() const;

    //
    // This function is an implementation detail;
    // do not call it.
    //
    void _done();

    //
    // Get the thread name
    //
    const std::string& name() const;

protected:
    const std::string _name;
    Mutex _stateMutex;
    bool _started;
    bool _running;

#ifdef ICE_OS_WINRT
    std::shared_ptr<std::thread> _thread;
#elif defined(_WIN32)
    HANDLE _handle;
    DWORD  _id;
#else
    pthread_t _thread;
#endif

private:

#ifdef _WIN32
#else
    ThreadControl start(size_t, bool, int);
#endif

    Thread(const Thread&);              // Copying is forbidden
    void operator=(const Thread&);      // Assignment is forbidden
};

typedef Handle<Thread> ThreadPtr;
    
}

#endif

