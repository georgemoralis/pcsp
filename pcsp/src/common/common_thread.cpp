#include "stdafx.h"
#include "common_thread.h"

#if 0
#include <time.h>

#ifdef	WIN32
#ifdef	_WIN32_WCE
extern "C" int gettimeofday(struct timeval *tv_,  void *tz_)
{
	// We could use _ftime(), but it is not available on WinCE.
	// (WinCE also lacks time.h)
	// Note also that the average error of _ftime is around 20 ms :)
	DWORD ms = GetTickCount();
	tv_->tv_sec = ms / 1000;
	tv_->tv_usec = ms * 1000;
	return 0;
}
#else
//#ifdef	HAVE_SYS_TIMEB_H
#include <sys/timeb.h>
//#endif

extern "C" int gettimeofday(struct timeval *tv_, void *tz_)
{
#if defined(_MSC_VER) && _MSC_VER >= 1300 
	struct __timeb64 tb;
	_ftime64(&tb);
#else
# ifndef __BORLANDC__
	struct _timeb tb;
	_ftime(&tb);
# else
	struct timeb tb;
	ftime(&tb);
# endif
#endif
	tv_->tv_sec = (long)tb.time;
	tv_->tv_usec = tb.millitm * 1000;
	return 0;
}
#endif
#endif


/// Thread ///////////////////////////////////////////////

#if _POSIX_PRIORITY_SCHEDULING > 0
#include <sched.h>
static int realtime_policy = SCHED_FIFO;
#endif

#if defined(WIN32)
void Thread::SetPriority()
{
	HANDLE hThread = GetCurrentThread();
	priority += THREAD_PRIORITY_NORMAL;
	if(priority < THREAD_PRIORITY_LOWEST)
		priority = THREAD_PRIORITY_LOWEST;
	else if(priority > THREAD_PRIORITY_HIGHEST)
		priority = THREAD_PRIORITY_HIGHEST;

	SetThreadPriority(hThread, priority);
}
#elif _POSIX_PRIORITY_SCHEDULING > 0
void Thread::SetPriority()
{
	int policy;
	struct sched_param sp;
	pthread_t ptid = pthread_self();
	int pri = 0;

	if (priority)
	{
		if (!pthread_getschedparam(ptid, &policy, &sp))
		{
			if (priority > 0)
			{
				policy = realtime_policy;
				if (realtime_policy == SCHED_OTHER)
				{
					pri = sp.sched_priority + priority;
				}
				else
				{
					pri = sched_get_priority_min(policy) + priority;
				}
				policy = realtime_policy;
				if (pri > sched_get_priority_max(policy))
				{
					pri = sched_get_priority_max(policy);
				}
			}
			else if (priority < 0)
			{
				pri = sp.sched_priority - priority;
				if (pri < sched_get_priority_min(policy))
				{
					pri = sched_get_priority_min(policy);
				}
			}

			sp.sched_priority = pri;
			pthread_setschedparam(ptid, policy, &sp);
		}
	}
}
#else
void Thread::SetPriority()
{
}
#endif


void Thread::Policy(int polid)
{
#if	_POSIX_PRIORITY_SCHEDULING > 0
	realtime_policy = polid;
#endif
}

void Thread::Sleep(u32 timeout)
{
	timespec ts;
	ts.tv_sec = timeout / 1000l;
	ts.tv_nsec = (timeout % 1000l) * 1000000l;
	pthread_delay_np(&ts);
}

void Thread::Yield()
{
#if defined(HAVE_PTHREAD_YIELD_NP)
	pthread_yield_np();
#elif defined(HAVE_PTHREAD_YIELD)
	pthread_yield();
#else
	sched_yield();
#endif
}

static void *exec_thread(void *obj)
{
	Thread *th = static_cast< Thread * >(obj);
	th->SetPriority();
	th->run();
	th->exit();
	return NULL;
}

/// JoinableThread : Thread //////////////////////////////

void JoinableThread::Start(int adj)
{
	int result;

	if (!running)
	{
		priority = adj;

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
		pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);

		// we typically use "stack 1" for min stack...
#ifdef	PTHREAD_STACK_MIN
		if (stack && stack < PTHREAD_STACK_MIN)
		{
			stack = PTHREAD_STACK_MIN;
		}
#else
		if (stack && stack < 2)
		{
			stack = 0;
		}
#endif
		if (stack)
		{
			pthread_attr_setstacksize(&attr, stack);
		}
		result = pthread_create(&tid, &attr, &exec_thread, this);
		pthread_attr_destroy(&attr);
		if (!result)
		{
			running = true;
		}
	}
}

/// DetachedThread : Thread //////////////////////////////

void DetachedThread::Start(int adj)
{
	Thread::priority = adj;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
	// we typically use "stack 1" for min stack...
#ifdef	PTHREAD_STACK_MIN
	if (stack && stack < PTHREAD_STACK_MIN)
	{
		stack = PTHREAD_STACK_MIN;
	}
#else
	if (stack && stack < 2)
	{
		stack = 0;
	}
#endif
	if (stack)
	{
		pthread_attr_setstacksize(&attr, stack);
	}
	pthread_create(&tid, &attr, &exec_thread, this);
	pthread_attr_destroy(&attr);
}

/// Trigger : Mutex //////////////////////////////////////

Trigger::Trigger(bool autoreset, bool state)
: Mutex(), state(int(state)), autoreset(autoreset)
{
	pthread_cond_init(&cond, 0);
}


Trigger::~Trigger()
{
	pthread_cond_destroy(&cond);
}


void Trigger::Wait()
{
	Mutex::Lock();

	while (state == 0)
	{
		pthread_cond_wait(&cond, &mutex);
	}
	if (autoreset)
	{
		state = 0;
	}
	
	Mutex::Unlock();
} 


void Trigger::Post()
{
	Mutex::Lock();
	state = 1;
	if (autoreset)
	{
		pthread_cond_signal(&cond);
	}
	else
	{
		pthread_cond_broadcast(&cond);
	}
	Mutex::Unlock();
}

void Trigger::Reset()
{
	state = 0;
}

/// Semaphore : Mutex ////////////////////////////////////

bool Semaphore::Wait(int timeout)
{
	Mutex::Lock();

	while (count <= 0)
	{ 
		if (timeout >= 0)
		{
			timespec abs_ts; 
			timeval cur_tv;
			gettimeofday(&cur_tv, NULL);
			abs_ts.tv_sec = cur_tv.tv_sec + timeout / 1000; 
			abs_ts.tv_nsec = cur_tv.tv_usec * 1000 + (timeout % 1000) * 1000000;
			int rc = pthread_cond_timedwait(&cond, &mutex, &abs_ts);
			if (rc == ETIMEDOUT)
			{ 
				Mutex::unlock();

				return false;
			}
		}
		else
		{
			pthread_cond_wait(&cond, &mutex);
		}
	} 
	count--;

	Mutex::Unlock();

	return true;
} 


void Semaphore::Post()
{
	Mutex::Lock();

	count++; 
	pthread_cond_signal(&cond);

	Mutex::Unlock();
}

/// JobQueue : Mutex /////////////////////////////////////

bool JobQueue::EnQueue(Message* msg, int timeout)
{
	if (msg)
	{
		if (ovrsem.Wait(timeout))
		{
			Mutex::Lock();

			msg->next = 0;
			if (head != 0)
			{
				head->next = msg;
			}
			head = msg;
			if (tail == 0)
			{
				tail = msg;
			}
			qcount++;
			
			Mutex::Unlock();
			
			sem.Post();

			return true;
		}
	}

	return false;
}


bool JobQueue::Push(Message *msg, int timeout)
{
	if (msg)
	{
		if (ovrsem.Wait(timeout))
		{
			Mutex::Lock();

			msg->next = tail;
			tail = msg;
			if (head == 0)
			{
				head = msg;
			}
			qcount++;
	
			Mutex::Unlock();

			sem.Post();

			return true;
		}
	}
	return false;
}


Message *JobQueue::DeQueue(bool safe, int timeout)
{
	if (sem.Wait(timeout))
	{
		if (safe) Mutex::Lock();

		Message *msg = tail;
		
		tail = msg->next;
		
		qcount--;
		
		if (tail == 0)
		{
			head = 0;
		}

		if (safe) Mutex::Unlock();

		ovrsem.Post();
		
		return msg;
	}

	return 0;
}


void JobQueue::Purge()
{
	Mutex::Lock();
	
	while (get_count() > 0)
	{
		delete DeQueue(false);
	}

	Mutex::Unlock();
}
#endif