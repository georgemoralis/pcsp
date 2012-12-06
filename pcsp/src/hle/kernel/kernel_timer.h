#ifndef kernel_timer_h__
#define kernel_timer_h__

#include <QtCore>
#include "kernel_object.h"
#include "kernel_partition.h"
#include "common_linked_list.h"
#include "common_thread.h"
#include "common/common_timer.h"

struct KernelTimer;
struct KernelThread;

/// KernelTimerList /////////////////////////////////////////////////////////

struct KernelTimerList
:   LinkedList< KernelTimer >
{
    KernelTimerList() : LinkedList< KernelTimer >() { Clear(); }

    void AddTimerToList(KernelTimer *timer);
    void RemoveTimerFromList(KernelTimer *timer);

    void DispatchTimers();
    void RescheduleTimers();

    static void Initialize();
    static void Terminate() {}
};


/// KernelTimer /////////////////////////////////////////////////////////////

struct KernelTimer
:   KernelObject
,   KernelTimerList::Node
{
    declare_kernel_type(KernelTimer, KernelObject);

    KernelTimer(char const *name);
    ~KernelTimer();

    u64 m_time;
    int m_unk_10;
};

/// KernelDelay /////////////////////////////////////////////////////////////

struct KernelDelay
:   KernelTimer
{
    declare_kernel_type(KernelDelay, KernelTimer);

    KernelDelay(char const *name);
    ~KernelDelay();

    void Cancel();

    KernelThread *m_thread;
};

/// KernelDelayList /////////////////////////////////////////////////////////

struct KernelDelayList
:   protected KernelTimerList
{
    KernelDelayList();
    ~KernelDelayList();

    void         Release(KernelDelay *delay);
    KernelDelay *Acquire();
};

/// KernelAlarm /////////////////////////////////////////////////////////////

struct KernelAlarm
:   KernelTimer
{
    declare_kernel_type(KernelAlarm, KernelTimer);

    KernelAlarm(char const *name, u32 uhandler, u32 cookie);
    KernelAlarm(char const *name, SceKernelAlarmHandler khandler, void *cookie);
    ~KernelAlarm();

    static SceUID Set(u64 delta, SceKernelAlarmHandler khandler, void *cookie);
    static SceUID Set(u64 delta, u32                   uhandler, u32   cookie);
    static SceUID Set(SceUInt delta, SceKernelAlarmHandler khandler, void *cookie);
    static SceUID Set(SceUInt delta, u32                   uhandler, u32   cookie);
    static SceUID SetSysClock(SceKernelSysClock *delta, SceKernelAlarmHandler khandler, void *cookie);
    static SceUID SetSysClock(SceKernelSysClock *delta, u32                   uhandler, u32   cookie);

    int           Cancel();
    int           ReferStatus(SceKernelAlarmInfo *info);


    int                   m_uhandler; //is user mode
    SceKernelAlarmHandler m_khandler; //4
    u32                   m_cookie; //8
    int                   m_gp_reg; //C
    int                   m_unk_10;
    int                   m_unk_14;
    int                   m_unk_18;
    int                   m_unk_1C;
    int                   m_unk_20;
    int                   m_unk_24;
    int                   m_unk_28;
    int                   m_unk_2C;
};

/// KernelVTimer ////////////////////////////////////////////////////////////

struct KernelVTimer
:   KernelTimer
{
    declare_kernel_type(KernelVTimer, KernelTimer);

    int                    m_active; //0
    SceKernelSysClock      m_current; //4 - current?
    SceKernelSysClock      m_schedule; //C - schedule?
    int                    m_uhandler; //14 - is user mode
    SceKernelVTimerHandler m_khandler; //18
    void                  *m_cookie; //1C
    int                    m_gp_reg; //20
    int                    m_unk_24;
    int                    m_unk_28;
    int                    m_unk_2C;

};

/// KernelSysClock //////////////////////////////////////////////////////////

class KernelSysClock
:   public    DetachedThread
,   public    Timer
,   protected Trigger
{
public:
    KernelSysClock()
    :   DetachedThread()
    ,   Timer()
    ,   Trigger(true, false)
    {}

    static u64  Get();
    static void SetTimer(u64 us);

    void Run();

private: // methods
    static KernelSysClock &Instance();

    //volatile u64  m_0xBC60000; // current clock value (µs)
    //volatile u64  m_0xBC60004; // compare clock value (µs)
    volatile u64  m_compare_time;
};


#endif // kernel_timer_h__
