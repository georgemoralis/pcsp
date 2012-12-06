#include "stdafx.h"

#include "kernel_timer.h"
#include "kernel_thread.h"

/// KernelTimerList /////////////////////////////////////////////////////////

void KernelTimerList::AddTimerToList(KernelTimer *timer)
{
    u64 time = timer->m_time;
    KernelTimer *next_timer;
    for (next_timer = this->First(); next_timer; next_timer = this->Next(next_timer))
    {
        if (time < next_timer->m_time)
        {
            timer->InsertInListBefore(next_timer);
            return;
        }
    }
    this->Append(timer);
}

void KernelTimerList::RemoveTimerFromList(KernelTimer *timer)
{
    timer->RemoveFromList();
}

void KernelTimerList::Initialize()
{
#if 0
    theKernelScheduler.m_unk_690 = 1;
    theKernelScheduler.m_unk_694 = 1;

    theKernelScheduler.m_unk_688 = 100 /* µs */;
    theKernelScheduler.m_unk_68C = theKernelScheduler.m_unk_688 << 1;

    theKernelScheduler.m_sceKernelGetSystemTimeLow = 0 /* &sceKernelGetSystemTimeLow */;

    theKernelScheduler.m_timer_intr = 0x13;

    //*(0xBC600008) = 0x30;
    //*(0xBC60000C) = 0x1;
    //*(0xBC600010) = 0;
    //_SYNC();

    sceKernelRegisterIntrHandler(theKernelScheduler.m_timer_intr, 0x1, DispatchTimers, &gInfo, 0);

    sceKernelSetIntrLevel(theKernelScheduler.m_timer_intr, 0x2);

    CLEAR_LIST(gInfo.unk_604);

    CLEAR_LIST(gInfo.timers);

    gInfo.unk_5F8 = 0;

    int intr = sceKernelCpuSuspendIntr();

    uidControlBlock *cb;
    ASSERT(sceKernelCreateUID(uidTimerType, "SceThreadmanSysTimerOVF", 0, &cb) <= 0);

    TimerInfo *timer = UID_INFO(TimerInfo, cb, uidTimerType); //t6
    timer->time.low = 0xF0000000;
    timer->time.hi = 0;

    ADD_TO_LIST(timer, gInfo.timers);

    gInfo.unk_430.low = 0;
    gInfo.unk_430.hi = 0;

    gInfo.unk_438.low = timer->time.low;

    for(i = 31; i >= 0; i--)
    {
        ASSERT(sceKernelCreateUID(uidDelayType, "SceThreadmanDelay", 0, &cb) <= 0);

        AddToDelayList(cb);
    }

    *(0xBC600004) = gInfo.unk_438.low;
    _SYNC();

    *(0xBC600000) = 0;
    _SYNC();

    sceKernelSetPrimarySyscallHandler(0x18, loc_0000DDB0);

    sceKernelRegisterSuspendHandler(0x18, sub_0000DDC8, 0);

    sceKernelRegisterResumeHandler(0x18, loc_0000DE3C, 0);

    sceKernelEnableIntr(gInfo.unk_72C);

    sceKernelCpuResumeIntr(intr);
#endif
}

void KernelTimerList::DispatchTimers()
{
    u32 result;

    int state = sceKernelCpuSuspendIntr();

    theKernelScheduler.m_unk_430 = theKernelScheduler.m_unk_438;

    u64 time = KernelSysClock::Get();

    KernelTimer *timer, *next_timer = 0;

    for (timer = this->First(); next_timer = this->Next(next_timer), timer; timer = next_timer)
    {
        if (timer->m_time > time)
        {
            break;
        }

        this->RemoveTimerFromList(timer);

        if (timer->CheckExactType(KernelDelay::m_object_type))
        {
            KernelDelay *delay = static_cast< KernelDelay * >(timer);
            
            KernelThread *this_thread = delay->m_thread;
            if (this_thread)
            {
                this_thread->m_timeout_object = 0;

                if (this_thread->ReleaseWaitingThread())
                {
                    theKernelScheduler.m_next_thread = 0;
                }
            }

            theKernelScheduler.m_delays.Release(delay);
        }
        else if (timer->CheckExactType(KernelAlarm::m_object_type))
        {
            theKernelScheduler.m_timer_id = timer->GetUid();

            KernelAlarm *alarm = static_cast< KernelAlarm * >(timer);

            AlContext &context = theKernelScheduler.m_current_thread->m_thread_context;

            if (alarm->m_uhandler)
            {
                u32 old_gp = context.gpr[ALLEGREX_GP];
                context.gpr[ALLEGREX_GP] = alarm->m_gp_reg;

                //result = sceKernelCallUserIntrHandler(alarm->m_arg, 0, 0, 0, alarm->m_handler, sceKernelGetUserIntrStack());

                context.gpr[ALLEGREX_GP] = old_gp;
            }
            else
            {
                sceKernelCpuResumeIntr(state);

                result = alarm->m_khandler((void *)alarm->m_cookie);

                state = sceKernelCpuSuspendIntr();
            }

            theKernelScheduler.m_timer_id = 0;

            if (!result)
            {
                timer->m_unk_10 = 1;

                //theKernelScheduler._AddThreadToCleanupQueue(timer->GetUid()); //???
            }
            else
            {
                timer->m_time += (u64)(result < 100 ? 100 : result);

                this->AddTimerToList(timer);
            }
        }
        else if (timer->CheckExactType(KernelVTimer::m_object_type))
        {
            KernelVTimer *vtimer = static_cast< KernelVTimer * >(timer);

            (void)vtimer;

            //result = sub_0000DF4C(cb);
#if 0
            if (result)
            {
                v1 = MAX(result, info->unk_688);

                t1 = s2 + v1;
                t3 = 0;
                s4 = t1 < v1;
                t9 = s3 + t3;
                t8 = t9 + s4;
                a0 = t8 >> 0;
                timer->time.hi = a0;
                s6 = s1 + 0xC;
                v0 = 0;
                timer->time.low = t1;
                t2 = 0;
                t4 = v1;
                t6 = vtimer->schedule.low;
                t7 = vtimer->schedule.hi;
                a0 = timer;
                t0 = v0 + t6;
                t5 = t7 << 0;
                s3 = t0 < t6;
                s2 = t5 + t2;
                v1 = t0 + v1;
                a3 = s2 + s3;
                a2 = v1 < t4;
                timer = a3 + t3;
                fp = timer + a2;
                s7 = fp >> 0;
                vtimer->schedule.low = v1;
                vtimer->schedule.hi = s7;

                AddToTimerList(timer);
            }
            else
            {
                vtimer->handler = 0;
            }
#endif 
        }
        else
        {
            timer->m_time = time + 0x00000000F0000000ULL;

            this->AddTimerToList(timer);
        }
    }

    RescheduleTimers();

    sceKernelCpuResumeIntr(state);
}

void KernelTimerList::RescheduleTimers()
{
    KernelTimer *timer = First();

    u64 next_time = timer->m_time + 100;

    do
    {
        if (next_time <= timer->m_time)
        {
            next_time = timer->m_time;
            break;
        }
    }
    while (timer = Next(timer));

    u64 current_time = KernelSysClock::Get();
    if (next_time - current_time < 100)
    {
        next_time = current_time + 100;
    }

    theKernelScheduler.m_unk_438 = next_time;

    KernelSysClock::SetTimer(next_time);
}

/// KernelTimer /////////////////////////////////////////////////////////////

void KernelTimer::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelTimer::KernelTimer(char const *name)
:   KernelObject(name)
{
    this->Clear();
    this->m_unk_10 = 0;
}

KernelTimer::~KernelTimer()
{
    if (this->m_next != this)
    {
        this->RemoveFromList();
    }
}

/// KernelDelay /////////////////////////////////////////////////////////////

void KernelDelay::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelDelay::KernelDelay(char const *name)
:   KernelTimer(name)
,   m_thread(0)
{
}

KernelDelay::~KernelDelay()
{
}

void KernelDelay::Cancel()
{
    if (this->m_thread)
    {
        if (this->m_thread->m_timeout)
        {
            *this->m_thread->m_timeout = u32(u64(this->m_time) - KernelSysClock::Get());
        }

        this->m_thread->m_timeout_object = 0;

        this->RemoveFromList();

        theKernelScheduler.m_delays.Release(this);
        theKernelScheduler.m_timers.RescheduleTimers();
    }
}

/// KernelDelayList /////////////////////////////////////////////////////////

KernelDelayList::KernelDelayList()
:   KernelTimerList()
{
    // reserve 32 delay objects at first
    for (int i = 0; i < 32; ++i)
    {
        Release(new KernelDelay("SceThreadmanDelay"));
    }
}

KernelDelayList::~KernelDelayList()
{
    KernelTimer *timer;
    while (timer = First())
    {
        delete timer;
    }
}

void KernelDelayList::Release(KernelDelay *delay)
{
    delay->m_thread = 0;

    // recycle this delay object
    Append(delay);
}

KernelDelay *KernelDelayList::Acquire()
{
    // try to acquire a recycled delay object
    KernelDelay *delay = static_cast< KernelDelay * >(First());
    if (delay)
    {
        delay->RemoveFromList();
        return delay;
    }
    // if none, get a new delay object
    return new KernelDelay("SceThreadmanDelay");
}

/// KernelAlarm /////////////////////////////////////////////////////////////

void KernelAlarm::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelAlarm::KernelAlarm(char const *name, u32 uhandler, u32 cookie)
:   KernelTimer(name)
,   m_uhandler(uhandler)
,   m_khandler(0)
,   m_cookie(cookie)
{
}

KernelAlarm::KernelAlarm(char const *name, SceKernelAlarmHandler khandler, void * /*cookie*/)
:   KernelTimer(name)
,   m_uhandler(0)
,   m_khandler(khandler)
,   m_cookie(0) //TODO (u32)cookie
{
}

KernelAlarm::~KernelAlarm()
{
}

SceUID KernelAlarm::Set(u64 delta, SceKernelAlarmHandler khandler, void *cookie)
{
    int state = sceKernelCpuSuspendIntr();

    KernelAlarm *alarm = new KernelAlarm("SceThreadmanAlarm", khandler, cookie);

    SceUID result = alarm->GetUid();

    if ((int)result <= 0)
    {
        delete alarm;

        sceKernelCpuResumeIntr(state);
        
        return result;
    }

    alarm->m_time = KernelSysClock::Get() + delta;

    //u32 *mod = (u32 *)sceKernelFindModuleByAddress(s2);
    //alarm->m_gp_reg = mod ? mod[0x68 / 4] : gp;

    theKernelScheduler.m_timers.AddTimerToList(alarm);

#if 0
    sub_0000B304();
#endif
    sceKernelCpuResumeIntr(state);

    return result;
}

SceUID KernelAlarm::Set(u64 delta, u32 uhandler, u32 cookie)
{
    int state = sceKernelCpuSuspendIntr();

    KernelAlarm *alarm = new KernelAlarm("SceThreadmanAlarm", uhandler, cookie);

    SceUID result = alarm->GetUid();

    if ((int)result <= 0)
    {
        delete alarm;

        sceKernelCpuResumeIntr(state);

        return result;
    }

    alarm->m_time = KernelSysClock::Get() + delta;

    //u32 *mod = (u32 *)sceKernelFindModuleByAddress(s2);
    //alarm->m_gp_reg = mod ? mod[0x68 / 4] : gp;

    theKernelScheduler.m_timers.AddTimerToList(alarm);

#if 0
    sub_0000B304();
#endif
    sceKernelCpuResumeIntr(state);

    return result;
}

SceUID KernelAlarm::Set(SceUInt delta, SceKernelAlarmHandler khandler, void *cookie)
{
    return Set(u64(delta), khandler, cookie);
}

SceUID KernelAlarm::Set(SceUInt delta, u32 uhandler, u32 cookie)
{
    if (!uhandler)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_ADDR;
    }

    return Set(u64(delta), uhandler, cookie);
}

SceUID KernelAlarm::SetSysClock(SceKernelSysClock *delta, SceKernelAlarmHandler khandler, void *cookie)
{
    if (!delta)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_ADDR;
    }

    return Set(u64(*delta), khandler, cookie);
}

SceUID KernelAlarm::SetSysClock(SceKernelSysClock *delta, u32 uhandler, u32 cookie)
{
    if (!delta || !uhandler)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_ADDR;
    }

    return Set(u64(*delta), uhandler, cookie);
}

int KernelAlarm::Cancel()
{
    if (this->GetUid() == theKernelScheduler.m_timer_id)
    {
        return SCE_KERNEL_ERROR_UNKNOWN_ALMID;
    }

    int state = sceKernelCpuSuspendIntr();

    KernelTimer *timer = static_cast< KernelTimer * >(this);
    
    if (timer->m_unk_10)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_UNKNOWN_ALMID;
    }

    timer->RemoveFromList();

    if (!sceKernelIsIntrContext())
    {
        //ASSERT(sceKernelDeleteUID(alarmid) <= 0);
    }

    timer->m_unk_10 = 1;

    int result = 0; //sub_0000F0DC(alarmid);

    if (result == 0)
    {
        theKernelScheduler.m_timers.RescheduleTimers(); //sub_0000B304();
    }

    sceKernelCpuResumeIntr(state);

    return result;
}

int KernelAlarm::ReferStatus(SceKernelAlarmInfo *info)
{
    (void)info;
    return 0;
}

/// KernelVTimer ////////////////////////////////////////////////////////////

void KernelVTimer::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

/// KernelSysClock //////////////////////////////////////////////////////////

KernelSysClock &KernelSysClock::Instance()
{
    static KernelSysClock instance;
    return instance;
}

u64 KernelSysClock::Get()
{
    return Instance().Timer::Get();
}

void KernelSysClock::Run()
{
    MutexLocker locker(*this); 

    while (!theEmulator.IsLeaving()) 
    {
        u64 compare_time = m_compare_time;
        u64 current_time = Timer::Get();
        s64 delta_time   = compare_time - current_time;

        if (delta_time > 100000)
        {
            if (Trigger::Wait(100)) continue;
        }
        else if (delta_time > 10000)
        {
            if (Trigger::Wait(10)) continue;
        }
        else if (delta_time > 1)
        {
            Trigger::Wait(1);
            continue;
        }
        else
        {
            locker.Unlock();
            theEmulator.ClockEvent();
            locker.Relock();
            break;
        }
    }
}

void KernelSysClock::SetTimer(u64 us)
{
    //KernelSysClock &instance = Instance();
    //MutexLocker locker(instance);
    //instance.m_compare_time = us;
    //if (!instance.IsRunning())
    //{
    //    instance.DetachedThread::TimeCriticalStart();
    //}
    //instance.Trigger::Signal();
}

