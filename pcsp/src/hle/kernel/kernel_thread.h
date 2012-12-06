#ifndef kernel_thread_h__
#define kernel_thread_h__

#include "kernel_object.h"

#include "common_linked_list.h"
#include "common_fiber.h"
#include "common_thread.h"

struct KernelEventHandler;
struct KernelCallback;
struct KernelWaitQueue;
struct KernelThread;

#include "kernel_timer.h"
#include "kernel_threadqueue.h"
#include "kernel_waitqueue.h"
#include "kernel_callback.h"

#include "emulator.h"

#if 1

struct KernelThread
:   KernelObject
,   KernelThreadQueue::Node
,   ScFiber< KernelThread >
{
    declare_kernel_type(KernelThread, KernelObject);

    KernelThread(char const *name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr);
    
    KernelThread(char const *name);

    ~KernelThread();	

    /////////////////////////////////////////////////////////////////////////////////
    SceUInt                         m_current_attributes;
    SceUInt                         m_initial_attributes;

    /////////////////////////////////////////////////////////////////////////////////
    enum TheadStatus
    {
        STATUS_INEXISTENT       = 0x00,
        STATUS_RUN              = 0x01,
        STATUS_READY            = 0x02,
        STATUS_WAIT             = 0x04,
        STATUS_SUSPEND          = 0x08,
        STATUS_WAITSUSPEND      = STATUS_WAIT|STATUS_SUSPEND,
        STATUS_STOPPED          = 0x10,
        STATUS_KILLED           = 0x20,
        STATUS_DORMANT          = STATUS_STOPPED|STATUS_KILLED,
        STATUS_MASK             = STATUS_RUN|STATUS_READY|STATUS_WAITSUSPEND|STATUS_STOPPED|STATUS_KILLED
    };

    int                             m_status;
    SceKernelThreadEntry            m_entry;       //6c
    int                             m_exit_status; //18
    int                             m_argc;
    u32                             m_argp;

    static int                      Create(char const *name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr, int intr);
    int                             Delete(int intr);
    int                             Start(SceSize argc, u32 argp, int intr);
    void                            Exit(int status, int intr, bool is_deletable = false);
    void                            ExitDelete(int status, int intr) { (void)intr; Exit(status, true); }
    int                             Terminate(int intr, bool is_deletable = false);
    int                             TerminateDelete(int intr) { (void)intr; return Terminate(true); }
    int                             Suspend(int intr);
    int                             Resume(int intr);
    int                             WaitThreadEnd(SceUInt *timeout, bool cb, int intr);
    int                             Delay(SceUInt delay, bool cb, int intr);
    int                             DelaySysClock(SceKernelSysClock *delay, bool cb, int intr);

    void                            _Start(int intr);
    void                            _Exit(int intr);

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_initial_priority; //60
    int                             m_current_priority; //10
    
    int                             ChangeThreadPriority(int priority, int intr);

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_wakeup_count; //14

    int                             Sleep(bool cb);
    int                             WakeUp();
    int                             CancelWakeUp();

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_wait_type;  //1c
    KernelWaitQueue                *m_wait_queue; //20
    int                             m_cb_arg1;    //24
    int                             m_cb_arg2;    //28
    int                             m_cb_arg3;    //2c
    int                             m_cb_arg4;    //30
    int                             m_cb_arg5;    //34

    bool                            ReleaseWaitingThread();
    void                            ReleaseWaitingThread(int UNUSED(intr_context), int UNUSED(intr)) {}

    /////////////////////////////////////////////////////////////////////////////////
    KernelDelay                    *m_timeout_object;
    int                            *m_timeout; //3c

    int                             RequestTimeout(u64 timeout) { (void)timeout; return 0; }

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_event_mask;    //44 - events being fired
    KernelEventHandler             *m_event_handler; //48 - event handler being fired

    void                            DispatchThreadEventHandlers(int mask, int intr) { (void)mask; (void)intr; }

    /////////////////////////////////////////////////////////////////////////////////
    u32                             m_stack;
    SceUID                          m_stack_id;
    u32                             m_stack_size;
    u32                             m_stack_top;

    int                             GrabThreadStack(u32 stack_size);
    u32                             CheckStack();

    /////////////////////////////////////////////////////////////////////////////////
    void                           *m_gp; //88 ($gp or the module address)
    SceUID                          m_api_module_id;

    SceUID                          GetApiModuleId();

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_callback_status; //40 - callback status
    KernelCallbackQueue             m_callbacks;       //4c - callbacks for thread
    int                             m_check_callbacks; //54 - is callback
    int                             m_callback_notify; //58 - callback notify
    KernelCallback                 *m_callback;        //5c - callback

    int                             DispatchCallbacks(int intr);

    /////////////////////////////////////////////////////////////////////////////////
    SceKernelSysClock               m_run_clocks; //64

    /////////////////////////////////////////////////////////////////////////////////
    AlContext                       m_thread_context;
    AlContext                       m_callback_context;

    bool                            SwitchToNext();
    void                            SwitchTo(int intr);
    void                            ReleaseWait(bool released, int intr);
};

struct KernelScheduler
{
    /////////////////////////////////////////////////////////////////////////////////
    KernelThread              *m_current_thread;
    KernelThread              *m_next_thread;
    int                        m_priority_mask[128 / 32];
    KernelThreadQueue          m_ready_threads[128     ];
    KernelThreadQueue          m_sleeping_threads;
    KernelThreadQueue          m_delayed_threads;
    KernelThreadQueue          m_stopped_threads;
    KernelThreadQueue          m_suspended_threads;
    KernelThreadQueue          m_deletable_threads;


    KernelThread              *GetCurrentThread() { return m_current_thread; }

    void                       ElectNextRunningThread();

    void                       AddThreadToReadyQueue(KernelThread *);
    void                       RemoveThreadFromReadyQueue(KernelThread *);

    void                       AddThreadToDormantQueue(KernelThread *);
    void                       AddThreadToCleanupQueue(KernelThread *);

    void                       AddThreadToDelayList(KernelThread *);
    void                       RemoveThreadFromDelayList(KernelThread *);

    /////////////////////////////////////////////////////////////////////////////////
    int                        m_dispatch_thread_suspended; //418

    int                        SuspendDispatchThread(int intr);
    int                        ResumeDispatchThread(int old, int intr);

    /////////////////////////////////////////////////////////////////////////////////
    SceKernelSysClock          m_unk_428;
    SceKernelSysClock          m_unk_430; //system time
    SceKernelSysClock          m_unk_438;

    /////////////////////////////////////////////////////////////////////////////////
    int                        m_timer_id; //440

    /////////////////////////////////////////////////////////////////////////////////
    int                        m_do_cleanup; //5cc


    /////////////////////////////////////////////////////////////////////////////////
    int                        m_delay_count; //5f8

    KernelTimerList            m_timers; //5FC
    KernelDelayList            m_delays; //604

    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    SceUID                     m_heapuid;

    /////////////////////////////////////////////////////////////////////////////////
    int                        m_thread_switch_count[2]; //67c, 680

    /////////////////////////////////////////////////////////////////////////////////
    Mutex					   m_mutex;


    void                       ElectNextReadyThread(int priority);

    SceUID                     m_threadret_syscall;
    u32                        m_threadret_syscall_id;

    bool                       Reboot();
    bool                       ShutDown();
};

extern KernelScheduler theKernelScheduler;

#else

struct KernelThread
:   KernelObject
,   KernelThreadQueue::Node
,   ScFiber< KernelThread >
{
    declare_kernel_type(KernelThread, KernelObject);

    KernelThread(char const *name);
    ~KernelThread();	

    int                             Sleep(bool cb);
    int                             WakeUp();
    int                             CancelWakeUp();
    int                             Suspend();
    int                             Resume();
    int                             WaitThreadEnd(SceUInt *timeout, bool cb);
    int                             Delay(SceUInt delay, bool cb);
    int                             DelaySysClock(SceKernelSysClock *delay, bool cb);

    /////////////////////////////////////////////////////////////////////////////////
    void                            DispatchCallbacks(int state);
    void                            SwitchTo(int state);
    void                            ReleaseWait(bool released, int state);

    /////////////////////////////////////////////////////////////////////////////////
    enum TheadStatus
    {
        STATUS_RUN              = 0x01,
        STATUS_READY            = 0x02,
        STATUS_WAIT             = 0x04,
        STATUS_SUSPEND          = 0x08,
        STATUS_WAITSUSPEND      = STATUS_WAIT|STATUS_SUSPEND,
        STATUS_DORMANT          = 0x10,
        STATUS_DEAD             = 0x20,
        STATUS_MASK             = STATUS_RUN|STATUS_READY|STATUS_WAITSUSPEND|STATUS_DORMANT|STATUS_DEAD
    };

    int                             m_status;


    /////////////////////////////////////////////////////////////////////////////////
    int                             m_initial_priority; //60
    int                             m_current_priority; //10
    int                             m_wakeup_count; //14
    int                             m_exit_status; //18

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_wait_type; //1c
    int                             m_cb_arg1; //24
    int                             m_cb_arg2; //28
    int                             m_cb_arg3; //2c
    int                             m_cb_arg4; //30
    int                             m_cb_arg5; //34
    KernelWaitQueue                *m_wait_queue; //20

    bool ReleaseWaitingThread();
    void ReleaseWaitingThread(int intr_context, int state);

    /////////////////////////////////////////////////////////////////////////////////
    KernelDelay                    *m_timeout_object;
    int                            *m_timeout; //3c

    int  RequestTimeout(u64 timeout);

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_event_mask; //44 - events being fired
    KernelEventHandler             *m_event_handler; //48 - event handler being fired
    
    /////////////////////////////////////////////////////////////////////////////////
    int                             m_callback_status; //40 - callback status
    KernelThreadQueue               m_callbacks; //4c - callbacks for thread
    int                             m_check_callbacks; //54 - is callback
    int                             m_callback_notify; //58 - callback notify
    KernelCallback                 *m_callback; //5c - callback

    /////////////////////////////////////////////////////////////////////////////////
    SceKernelSysClock               m_run_clocks; //64
    SceKernelThreadEntry            m_entry; //6c

    /////////////////////////////////////////////////////////////////////////////////
    u32                             m_stack;
    SceUID                          m_stack_id;
    u32                             m_stack_size;
    u32                             m_stack_top;

    void GrabStack(int stack_size);

    /////////////////////////////////////////////////////////////////////////////////
    void                           *m_kernel_stack; //7c
    int                             m_kernel_stack_size; //80
    int                             m_kernel_stack_top; //104

    /////////////////////////////////////////////////////////////////////////////////
    SceSyscallStackInfo            *m_sc_stack_info; //84

    /////////////////////////////////////////////////////////////////////////////////
    int                             m_initial_attributes; //d4
    SceSize                         m_args; //d8
    void                           *m_argp; //dc
    SceKernelThreadOptParam        *m_opt_param; //e0
    
    /////////////////////////////////////////////////////////////////////////////////
    int                            *m_count; //e4 - pointer to intrPreemptCount or threadPreemptCount
    int                             m_intr_preempt_count; //e8
    int                             m_thread_preempt_count; //ec
    int                             m_release_count; //f0
    
    /////////////////////////////////////////////////////////////////////////////////
    AlContext                       m_thread_context;
    AlContext                      *m_callback_context;

    void GrabContexts() {}
    bool SwitchToNext();

    /////////////////////////////////////////////////////////////////////////////////
    void                           *m_gp; //88 ($gp or the module address)
    void                           *unk_8C;

    int                             m_ktls[16]; //90 - kernel thread local storage

    SceUID                          m_api_module_id;

    SceUID GetApiModuleId() { return (m_api_module_id > 0) ? m_api_module_id : 0x80020001; }
};

struct KernelScheduler
{
    KernelThread              *m_current_thread; //current thread?
    KernelThread              *m_next_thread; //4
    int                        m_priority_mask[128 / 32]; //8 - 1 bit per priority to indicate whether there are any threads running
    KernelThreadQueue          m_ready_threads[128     ]; //18 - threads grouped by priority
    
    int                        m_dispatch_thread_suspended; //418
    
    unsigned int             (*m_sceKernelGetSystemTimeLow)(void);
    
    SceKernelSysClock          m_unk_428;
    SceKernelSysClock          m_unk_430; //system time
    SceKernelSysClock          m_unk_438;
    
    int                        m_timer_id; //440
    
    //KTLSInfo ktls[0x10]; //KTLs?
    
    KernelThread              *m_idle_thread; //5c4
    KernelThread              *m_cleaner_thread; //5c8
    
    int                        m_do_cleanup; //5cc
    //ThreadCleanup cleanup; //5d0
    
    int                        m_delay_count; //5f8

    KernelTimerList            m_timers; //5FC
    KernelDelayList            m_delays; //604

    KernelThreadQueue          m_event_handlers; //60C
    
    KernelThreadQueue          m_sleeping_threads; //614
    KernelThreadQueue          m_delayed_threads; //61c
    KernelThreadQueue          m_stopped_threads; //624
    KernelThreadQueue          m_suspended_threads; //62c
    KernelThreadQueue          m_dead_threads; //634 - dormant/killed threads

    SceUID                     m_heapuid; //674
    int                        m_system_status_flag; //678
    int                        m_thread_switch_count; //67c
    int                        m_abort_switch_count; //680
    int                        m_vfpu_switch_count; //684
    int                        m_unk_688;
    int                        m_unk_68C;
    int                        m_unk_690;
    int                        m_unk_694;
    int                        m_unk_698; //_sceKernelExitThread syscall
    int                        m_unk_69C; //_sceKernelReturnFromCallback syscall
    u8                         m_unk_6A0[0x10]; //buffer for refer status - will overlap with the vars below, as the structs used tend to be about 0x30 bytes!
    u8                         m_unk_6B0[0x8]; //buffer used for storing option to pass to sceKernelAllocHeapMemoryWithOption in sceKernelCreateThread
    u8                         m_unk_6B8[0x8]; //buffer used for storing the SceKernelThreadOptParam passed in to sceKernelCreateThread
    u8                         m_unk_6C0[0x68]; //buffer used for holding stack names (0x20 chars) in sceKernelCreateThread
    int                        m_cpu_id; //728
    int                        m_timer_intr; //72c
    int                        m_cpu_profiler_mode; //CPU profiler enabled: 0 = none, 1 = thread mode, 2 = global mode

	QMutex					   m_mutex;

    KernelThread *GetCurrentThread() { return m_current_thread; }

	void          ElectNextRunningThread();

	void          AddThreadToReadyQueue(KernelThread *thread);
    void          RemoveThreadFromReadyQueue(KernelThread *thread);

    void          AddThreadToDelayList(KernelThread *thread);
    void          RemoveThreadFromDelayList(KernelThread *thread);

    void          ExitThread();
    SceUID        GetThreadId();
    int           GetThreadCurrentPriority();

	void          ElectNextReadyThread(int priority);

    bool          Reboot();
    bool          ShutDown();
    void          _AddThreadToCleanupQueue( SceUID id );
};

extern KernelScheduler theKernelScheduler;

#endif
#endif // kernel_thread_h__
