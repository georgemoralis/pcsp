#pragma once
#include "types.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QReadWriteLock>
#undef Yield
#ifdef QT_THREAD_SUPPORT

class Thread : protected QThread
{
public:
    Thread(size_t size = 0)                        { QThread::setStackSize(size); }
    virtual ~Thread()                              {}

    inline void BackgroundStart()                  { QThread::start(QThread::IdlePriority); };
    inline void TimeCriticalStart()                { QThread::start(QThread::TimeCriticalPriority); };

    static inline void Yield()                     { QThread::yieldCurrentThread(); }
    static inline void Sleep(u32 timeout)          { QThread::msleep(timeout); }

    virtual void Run() = 0;

    virtual void Exit()                            { QThread::terminate(); }

    inline bool IsRunning()                        { return QThread::isRunning(); };
private:
    virtual void run()                             { Run(); }
};

class JoinableThread : public Thread
{
public:
    JoinableThread(size_t size = 0) : Thread(size) {}
    ~JoinableThread()                              { Join(); }

    inline void Start()                            { QThread::start(); }

    void Join()                                    { if (IsRunning()) { if (this == QThread::currentThread()) QThread::terminate(); QThread::wait(); } }
};

class DetachedThread : public Thread
{
public:
    DetachedThread(size_t size = 0) : Thread(size) {}
    ~DetachedThread()                              {}

    inline void Start()                            { QThread::start(); }
    void Exit()                                    { delete this; }
};

class Mutex : protected QMutex
{
public:
    Mutex()                                        {}
    ~Mutex()                                       {}
    void Lock()                                    { QMutex::lock(); }
    void Unlock()                                  { QMutex::unlock(); }
    bool TryLock()                                 { return QMutex::tryLock(); }
    bool TryLock(u32 timeout)                      { return QMutex::tryLock(timeout); }
};

class RecursiveMutex : protected QMutex
{
public:
    RecursiveMutex() : QMutex(QMutex::Recursive)   {}
    ~RecursiveMutex()                              {}
    void Lock()                                    { QMutex::lock(); }
    void Unlock()                                  { QMutex::unlock(); }
    bool TryLock()                                 { return QMutex::tryLock(); }
    bool TryLock(u32 timeout)                      { return QMutex::tryLock(timeout); }
};

class MutexLocker
{
public:
    MutexLocker(Mutex &mutex) : m_mutex(mutex)     { m_mutex.Lock(); }
    ~MutexLocker()                                 { Unlock(); }
    void Relock()                                  { m_mutex.Lock(); }
    void Unlock()                                  { m_mutex.Unlock(); }
    operator Mutex &()                             { return m_mutex; }
protected:
    Mutex &m_mutex;
};

class Trigger : public Mutex, protected QWaitCondition 
{
public:
    Trigger(bool autoreset, bool state)
    :   Mutex()
    ,   QWaitCondition()
    ,   m_state(state)
    ,   m_autoreset(autoreset)                     {}
    ~Trigger()                                     {}
    void Wait()                                    { while (m_state == 0) QWaitCondition::wait(this); if (m_autoreset) m_state = 0; }
    bool Wait(u32 timeout)                         { while (m_state == 0) if (!QWaitCondition::wait(this, timeout)) return false; if (m_autoreset) m_state = 0; return true; }
    void Post()                                    { m_state = 1; if (m_autoreset) QWaitCondition::wakeOne(); else QWaitCondition::wakeAll(); }
    void Signal()                                  { Post(); }
    void Reset()                                   {}

protected:
    int             m_state;
    bool            m_autoreset;
};

class ReadWriteLock : protected QReadWriteLock
{
public:
    ReadWriteLock()                                {}
    ~ReadWriteLock()                               {}
    void LockForRead()                             { QReadWriteLock::lockForRead(); }
    void LockForWrite()                            { QReadWriteLock::lockForWrite(); }
    void Unlock()                                  { QReadWriteLock::unlock(); }
    void Lock()                                    { LockForWrite(); }
    bool TryLockForRead()                          { return QReadWriteLock::tryLockForRead(); }
    bool TryLockForRead(u32 timeout)               { return QReadWriteLock::tryLockForRead(timeout); }
    bool TryLockForWrite()                         { return QReadWriteLock::tryLockForWrite(); }
    bool TryLockForWrite(u32 timeout)              { return QReadWriteLock::tryLockForWrite(timeout); }
};

class Semaphore : public Mutex
{
public:
    Semaphore(int initial_value)
    :   m_count(initial_value)                     {}
    virtual ~Semaphore()                           {}
    void Wait()                                    { QMutexLocker locker(this); while (m_count <= 0) m_waitcondition.wait(this); m_count--; }
    bool Wait(u32 timeout)                         { QMutexLocker locker(this); while (m_count <= 0) if (!m_waitcondition.wait(this, timeout)) return false; m_count--; return true; }
    void Post()                                    {}
    void Signal()                                  { Post(); }
protected:
    QWaitCondition  m_waitcondition;
    int             m_count;
};

#if 0
struct Message
{
    Message *next;
    Semaphore *sync;
    friend struct JobQueue;
    friend struct MsgQueue;
    int id;
    void *param;
    void *result;
    Message(int id, void *param = 0) : next(0), sync(0), id(id), param(param), result(0) {}
    virtual ~Message() {}
};

struct JobQueue : Mutex
{
    int       limit;        // queue limit
    Message  *head;         // queue head
    Message  *tail;         // queue tail
    int       qcount;       // number of items in the queue
    Semaphore sem;          // queue semaphore
    Semaphore ovrsem;       // overflow semaphore

    bool EnQueue(Message *msg, int timeout = -1);
    bool Push(Message *msg, int timeout = -1);
    Message *DeQueue(bool safe = true, int timeout = -1);
    void Purge();

    JobQueue(int limit = 4096) : limit(limit), head(0), tail(0), qcount(0), sem(0), ovrsem(limit) {}
    virtual ~JobQueue() { purge(); }

    int  GetCount() const  { return qcount; }
    int  GetLimit() const  { return limit; }

    bool Post(Message *msg, int timeout = -1) { return EnQueue(msg, timeout); }
    bool Post(int id, void *param = 0, int timeout = -1) { return Post(new Message(id, param), timeout); }
    bool PostUrgent(Message *msg, int timeout = -1) { return Push(msg, timeout); }
    bool PostUrgent(int id, void *param = 0, int timeout = -1) { return PostUrgent(new Message(id, param), timeout); }
    Message *GetMessage(int timeout = -1) { return DeQueue(true, timeout); }
};

template< typename T > struct JobQueueOf : protected JobQueue
{
    JobQueueOf(int limit = 4096) : JobQueue(limit) {}

    int  GetCount() const                      { return JobQueue::GetCount(); }
    int  GetLimit() const                      { return JobQueue::GetLimit(); }
    bool Post(T *msg, int timeout = -1)        { return JobQueue::Post(msg, timeout); }
    bool PostUrgent(T *msg, int timeout = -1)  { return JobQueue::PostUrgent(msg, timeout); }
    T   *GetMessage(int timeout = -1)          { return (T *)JobQueue::GetMessage(timeout); }
};
#endif
#else
#pragma error Unimplemented thread class
#endif

