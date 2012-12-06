#include "stdafx.h"

#include "kernel_thread.h"
#include "kernel_timer.h"
#include "kernel_module.h"
#include "modules/sysmem/sysmem.h"

#include <new>

#define MAX_THREAD_PRIORITY     127
#define MIN_THREAD_STACKSIZE    0x200
#define THREAD_KSTACKSIZE       0x800

////

void KernelThread::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelThread::KernelThread(char const *name)
:   KernelObject(name)
,   ScFiber< KernelThread >()
{
}

#if 1

KernelThread::KernelThread(char const *name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr)
:   KernelObject(name)
,   ScFiber< KernelThread >()
,   m_current_attributes(attr)
,   m_initial_attributes(attr)
,   m_status(STATUS_INEXISTENT)
,   m_entry(entry)
,   m_exit_status(SCE_KERNEL_ERROR_DORMANT)
,   m_argc(0)
,   m_argp(0)
,   m_initial_priority(priority)
,   m_current_priority(priority)
,   m_wakeup_count(0)
,   m_wait_type(KernelWaitQueue::WAITTYPE_NONE)
,   m_wait_queue(0)
,   m_cb_arg1(0)
,   m_cb_arg2(0)
,   m_cb_arg3(0)
,   m_cb_arg4(0)
,   m_cb_arg5(0)
,   m_timeout_object(0)
,   m_timeout(0)
,   m_event_mask(0)
,   m_event_handler(0)
,   m_stack(0)
,   m_stack_id(0)
,   m_stack_size(0)
,   m_stack_top(0)
,   m_gp(0)
,   m_api_module_id(0)
,   m_callback_status(0)
,   m_check_callbacks(0)
,   m_callback_notify(0)
,   m_callback(0)
,   m_run_clocks(0LL)
{
    this->m_api_module_id = theKernelScheduler.m_current_thread->GetApiModuleId();
}

KernelThread::~KernelThread()
{
    if (m_stack_id)
    {
        sysmem::hleKernelFreePartitionMemory(m_stack_id);
    }
}

int KernelThread::Create(char const *name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr, int intr)
{
    KernelThread *created_thread = new KernelThread(name, entry, priority, stacksize, attr);

    created_thread->GrabThreadStack(stacksize);

    theKernelScheduler.AddThreadToDormantQueue(created_thread);

    created_thread->DispatchThreadEventHandlers(SCE_KERNEL_THREAD_EVENT_CREATE, intr);

    return created_thread->GetUid();
}

int KernelThread::Delete(int intr)
{
    if (this->m_status != STATUS_STOPPED && this->m_status != STATUS_KILLED)
    {
        return SCE_KERNEL_ERROR_NOT_DORMANT;
    }

    if (this->m_event_mask)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    this->DispatchThreadEventHandlers(SCE_KERNEL_THREAD_EVENT_DELETE, intr);

    this->m_status = STATUS_INEXISTENT;

    this->RemoveFromList();

    if (this->m_current_attributes & SCE_KERNEL_THREAD_ATTR_CLEAR_STACK)
    {
        ::memset(Memory::addrb(this->m_stack), 0, this->m_stack_size);
    }

    delete this;

    return SCE_KERNEL_ERROR_OK;
}

int KernelThread::Start(SceSize argc, u32 argp, int intr)
{
    if (this->m_status == STATUS_STOPPED)
    {
        if (this->m_event_mask)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        this->m_stack_top  = this->m_stack + this->m_stack_size - 256;
        ::memset(Memory::addrb(this->m_stack_top), 0, 64);
        Memory::mem< SceThreadStack >(this->m_stack).thread_id = this->GetUid();
        
        this->m_wait_type          = KernelWaitQueue::WAITTYPE_NONE;
        this->m_current_attributes = this->m_initial_attributes;
        this->m_current_priority   = this->m_initial_priority;
        this->m_wait_queue         = 0;
        this->m_wakeup_count       = 0;

        this->m_stack_top -= (u32(argc) + 15) & ~15;
        if (argc > 0 && argp)
        {
            this->m_argc = argc;
            this->m_argp = this->m_stack_top; 
            ::memcpy(Memory::addr< char >(this->m_stack_top), Memory::addr< char >(argp), int(argc));
        }
        else
        {
            this->m_argc = 0;
            this->m_argp = 0; 
        }

        this->m_stack_top -= 64;
        theKernelModuleManager.WriteSyscall("ThreadManForUser", 0xC0DE0000, this->m_stack_top + 0); // _sceKernelStartThread syscall
        theKernelModuleManager.WriteSyscall("ThreadManForUser", 0xC0DE0001, this->m_stack_top + 8); // _sceKernelExitThread syscall
        Memory::memw(this->m_stack_top + 0) = 0;
        Memory::memw(this->m_stack_top + 8) = 0;

        this->m_thread_context.pc = u32(this->m_stack_top);


        this->m_exit_status = SCE_KERNEL_ERROR_NOT_DORMANT;

        this->RemoveFromList();
        this->SwitchTo(intr);

        return SCE_KERNEL_ERROR_OK;
    }

    return SCE_KERNEL_ERROR_NOT_DORMANT;
}

void KernelThread::Exit(int status, int intr, bool is_deletable)
{
    if (theKernelScheduler.m_dispatch_thread_suspended)
    {
        theKernelScheduler.m_dispatch_thread_suspended = 0;
    }

    if (is_deletable)
    {
        this->m_event_mask |= SCE_KERNEL_THREAD_EVENT_DELETE;
    }

    this->DispatchThreadEventHandlers(SCE_KERNEL_THREAD_EVENT_EXIT, intr);

    //sub_000004C0(cb, status);
    // Release all threads being waiting on this thread

    //sub_0000237C(this);
    // Release all the registered callbacks to this thread

    if (is_deletable)
    {
        this->m_status = STATUS_DORMANT;

        theKernelScheduler.m_deletable_threads.Append(this);
        theKernelScheduler.m_do_cleanup = true;
    }
    else
    {
        this->m_status = STATUS_STOPPED;

        theKernelScheduler.m_stopped_threads.Append(this);
    }

    theKernelScheduler.m_next_thread = 0;

    this->ReleaseWait(true, 1);
}

int KernelThread::Terminate(int intr, bool is_deletable)
{
    // ...

    return SCE_KERNEL_ERROR_OK;
}

void KernelThread::_Start(int intr)
{
    ::memset(&this->m_thread_context.gpr[ALLEGREX_ZR], 0, sizeof(u32)*32);
    ::memset(&this->m_thread_context.fpr[ALLEGREX_F0], 0, sizeof(f32)*32);
    ::memset(&this->m_thread_context.vpr[0          ], 0, sizeof(f32)*4*4*8);

    this->m_thread_context.fcr31 = 0;
    this->m_thread_context.hilo  = 0;
    this->m_thread_context.vcr.Reset();
    this->m_thread_context.rnd.SetSeed(0x3f800001);

    this->m_thread_context.gpr[ALLEGREX_A0] = u32(this->m_argc);
    this->m_thread_context.gpr[ALLEGREX_A1] = u32(this->m_argp); 
    this->m_thread_context.gpr[ALLEGREX_K0] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_GP] = this->m_api_module_id;
    this->m_thread_context.gpr[ALLEGREX_SP] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_FP] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_RA] = u32(this->m_stack_top);
    this->m_thread_context.pc               = u32(this->m_entry);

    this->DispatchThreadEventHandlers(SCE_KERNEL_THREAD_EVENT_START, intr);
}


void KernelThread::_Exit(int intr)
{

}

int KernelThread::ChangeThreadPriority(int priority, int)
{
    int is_intr_context = sceKernelIsIntrContext();

    if (this->m_status & STATUS_DORMANT)
    {
        return SCE_KERNEL_ERROR_DORMANT;
    }

    if (!priority)
    {
        priority = this->m_current_priority;
    }

    // Argh, we need a more complex emulation

    //if (this == theKernelScheduler.m_current_thread)
    //{
    //    if (is_intr_context)
    //    {
    //        return SCE_KERNEL_ERROR_ILLEGAL_THID;
    //    }

    //    if (theKernelScheduler.m_dispatch_thread_suspended)
    //    {
    //        this->m_current_priority = priority;
    //    }
    //    else
    //    {
    //        if (intr)
    //        {
    //            this->m_current_priority = priority;
    //            theKernelScheduler.AddThreadToReadyQueue(this);

    //        }
    //    }
    //}
    //else
    //{
    //    if (this->m_current_priority != priority)
    //    {
    //        theKernelScheduler.RemoveThreadFromReadyQueue(this);

    //        this->m_current_priority = priority;

    //        theKernelScheduler.AddThreadToReadyQueue(this);
    //    }
    //}

    return SCE_KERNEL_ERROR_OK;
}

int KernelThread::GrabThreadStack(u32 stack_size)
{
    stack_size = ((stack_size + 255) & ~255);

    m_stack_id = sysmem::hleKernelAllocPartitionMemory(2, m_name, 1, stack_size, 0);
    if (m_stack_id > 0)
    {
        m_stack = (u32)sysmem::hleKernelGetBlockHeadAddr(m_stack_id);
        if (m_stack < 0)
        {
            return SCE_KERNEL_ERROR_NO_MEMORY;
        }

        m_stack_size = stack_size;

        if (!(this->m_current_attributes & SCE_KERNEL_THREAD_ATTR_NO_FILLSTACK))
        {
            ::memset(Memory::addrb(this->m_stack), 255, this->m_stack_size);
        }
    }

    return SCE_KERNEL_ERROR_OK;
}

u32 KernelThread::CheckStack()
{
    return this->m_thread_context.gpr[ALLEGREX_SP] - this->m_stack;
}

SceUID KernelThread::GetApiModuleId()
{
    return (m_api_module_id > 0) ? m_api_module_id : 0x80020001;
}

bool KernelThread::SwitchToNext()
{
    if (theKernelScheduler.m_dispatch_thread_suspended)
    {
        return true;
    }

    if (theKernelScheduler.m_next_thread == 0)
    {
        theKernelScheduler.ElectNextRunningThread();
    }

    if (theKernelScheduler.m_next_thread == theKernelScheduler.m_current_thread)
    {
        theKernelScheduler.m_thread_switch_count[1]++;
    }
    else
    {
        SceKernelSysClock sysclock(KernelSysClock::Get());

        this->m_run_clocks           = sysclock - theKernelScheduler.m_unk_428;
        theKernelScheduler.m_unk_428 = sysclock;

        theKernelScheduler.m_thread_switch_count[0]++;
    }

    KernelThread *next_thread           = theKernelScheduler.m_next_thread;
    theEmulator.context                 = &next_thread->m_thread_context;
    theKernelScheduler.m_current_thread = next_thread;
    next_thread->Fiber::SwitchTo();
    return true;
}

bool KernelThread::ReleaseWaitingThread()
{
    if (this->m_status == STATUS_INEXISTENT)
    {
        return false;
    }

    this->m_check_callbacks = false;

    if (this->m_timeout_object)
    {
        this->m_timeout_object->Cancel();
        this->m_timeout_object = 0;
        this->m_timeout        = 0;
    }

    if (this->m_wait_queue)
    {
        this->m_wait_queue->Release();
    }

    this->RemoveFromList();

    if (this->m_status == STATUS_WAITSUSPEND)
    {
        theKernelScheduler.m_suspended_threads.Append(this);
        this->m_status = STATUS_SUSPEND;

        return false;
    }

    return true;
}

void KernelThread::SwitchTo(int intr)
{
    if (this->m_current_priority >= theKernelScheduler.m_current_thread->m_current_priority || theKernelScheduler.m_dispatch_thread_suspended)
    {
        theKernelScheduler.AddThreadToReadyQueue(this);

        return;
    }

    if (intr)
    {
        theKernelScheduler.AddThreadToReadyQueue(theKernelScheduler.m_current_thread);

        this->m_status = STATUS_RUN;
        theKernelScheduler.m_next_thread = this;
    }
    else
    {
        theKernelScheduler.AddThreadToReadyQueue(this);
        theKernelScheduler.m_next_thread = 0;
    }

    ReleaseWait(false, intr);
}

void KernelThread::ReleaseWait(bool released, int /*state*/)
{
    //this->m_count = released ? &this->m_release_count : &this->m_thread_preempt_count;
    this->SwitchToNext();
    this->m_check_callbacks = 0;
}

#else

KernelThread::~KernelThread()
{
    if (m_stack_id)
    {
        sysmem::hleKernelFreePartitionMemory(m_stack_id);
    }
}


bool KernelThread::SwitchToNext()
{
    if (theKernelScheduler.m_dispatch_thread_suspended)
    {
        return true;
    }

    if (theKernelScheduler.m_next_thread == 0)
    {
        theKernelScheduler.ElectNextRunningThread();
    }

    if (theKernelScheduler.m_next_thread == theKernelScheduler.m_current_thread)
    {
        theKernelScheduler.m_abort_switch_count++;
    }
    else
    {
        SceKernelSysClock sysclock(KernelSysClock::Get());

        this->m_run_clocks           = sysclock - theKernelScheduler.m_unk_428;
        theKernelScheduler.m_unk_428 = sysclock;

        theKernelScheduler.m_thread_switch_count++;
        (*theKernelScheduler.m_current_thread->m_count)++;
    }

    KernelThread *next_thread           = theKernelScheduler.m_next_thread;
    theEmulator.context                 = &next_thread->m_thread_context;
    theKernelScheduler.m_current_thread = next_thread;
    next_thread->SwitchTo();
    return true;
}

bool KernelThread::ReleaseWaitingThread()
{
    if (this->m_status == STATUS_DEAD)
    {
        return false;
    }

    this->m_check_callbacks = false;

    if (this->m_timeout_object)
    {
        this->m_timeout_object->Cancel();
        this->m_timeout_object = 0;
        this->m_timeout        = 0;
    }

    if (this->m_wait_queue)
    {
        this->m_wait_queue->Release();
    }

    this->RemoveFromList();

    if (this->m_status == STATUS_WAITSUSPEND)
    {
        theKernelScheduler.m_suspended_threads.Append(this);
        this->m_status = STATUS_SUSPEND;

        return false;
    }

    this->m_status = STATUS_READY;

    theKernelScheduler.AddThreadToReadyQueue(this);

    return true;
}

void KernelThread::ReleaseWaitingThread(int intr_context, int state)
{
    if (this->m_status == STATUS_DEAD)
    {
        return;
    }

    this->m_check_callbacks = false;

    if (this->m_timeout_object)
    {
        this->m_timeout_object->Cancel();
        this->m_timeout_object = 0;
        this->m_timeout        = 0;
    }

    if (this->m_wait_queue)
    {
        this->m_wait_queue->Release();
    }

    this->RemoveFromList();

    if (this->m_status == STATUS_WAITSUSPEND)
    {
        theKernelScheduler.m_suspended_threads.Append(this);
        this->m_status = STATUS_SUSPEND;
    }
    else
    {
        this->m_status = STATUS_READY;

        if (intr_context)
        {
            theKernelScheduler.AddThreadToReadyQueue(this);
            theKernelScheduler.m_next_thread = 0;
        }
        else
        {
            this->SwitchTo(state);
        }
    }
}


void KernelThread::GrabStack(int stack_size)
{
    char thread_stack_name[256];
    ::sprintf(thread_stack_name, "%s stack", m_name);
    m_stack_id = sysmem::hleKernelAllocPartitionMemory(2, thread_stack_name, 1, stack_size, 0);
    if (m_stack_id > 0)
    {
        m_stack      = (u32)sysmem::hleKernelGetBlockHeadAddr(m_stack_id);
        m_stack_size = stack_size;
        m_stack_top  = m_stack + m_stack_size - 512;

        m_thread_context.gpr[ALLEGREX_SP] = m_stack_top;
        m_thread_context.gpr[ALLEGREX_K0] = m_stack_top;
    }
}

// for sceKernelSleepThread/sceKernelSleepThreadCB
int KernelThread::Sleep(bool cb)
{
    if (sceKernelIsIntrContext())
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (state == 0 || theKernelScheduler.m_dispatch_thread_suspended != 0)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    for (;;)
    {
        if (cb && this->m_callback_notify)
        {
            DispatchCallbacks(state);
        }

        this->m_callback_status = 0;

        if (this->m_wakeup_count == 0)
        {
            theKernelScheduler.m_sleeping_threads.AddWaitingThread(this, KernelWaitQueue::WAITTYPE_SLEEP);

            this->m_check_callbacks = true;

            theKernelScheduler.m_next_thread = 0;

            ReleaseWait(true, 1);
        }
        else
        {
            this->m_wakeup_count--;
        }

        if (!cb || this->m_callback_status != SCE_KERNEL_ERROR_NOTIFY_CALLBACK)
        {
            break;
        }
    }

    sceKernelCpuResumeIntr(state);

    return this->m_callback_status;
}

// for sceKernelWakeupThread
int KernelThread::WakeUp()
{
    int is_intr_context = sceKernelIsIntrContext();

    int state = sceKernelCpuSuspendIntr();

    if (!is_intr_context && this == theKernelScheduler.m_current_thread)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_ILLEGAL_THID;
    }

    if (this->m_status & (STATUS_DORMANT|STATUS_DEAD))
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_DORMANT;
    }

    if ((this->m_status & STATUS_WAIT) && this->m_wait_type == KernelWaitQueue::WAITTYPE_SLEEP)
    {
        this->ReleaseWaitingThread(is_intr_context, state);
    }
    else
    {
        this->m_wakeup_count++;
    }

    sceKernelCpuResumeIntr(state);

    return 0;
}


// for sceKernelCancelWakeupThread
int KernelThread::CancelWakeUp()
{
    int state = sceKernelCpuSuspendIntr();

    int result = this->m_wakeup_count;
    this->m_wakeup_count = 0;

    sceKernelCpuResumeIntr(state);

    return result;
}


// for sceKernelSuspendThread
int KernelThread::Suspend()
{
    int intr_context = sceKernelIsIntrContext();

    int state = sceKernelCpuSuspendIntr();

    if (!intr_context && this == theKernelScheduler.m_current_thread)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_ILLEGAL_THID;
    }

    int result;

    switch (this->m_status)
    {
    case STATUS_RUN:
        if (theKernelScheduler.m_dispatch_thread_suspended)
        {
            if (theKernelScheduler.m_dispatch_thread_suspended == 3) // ???
            {
                theKernelScheduler.m_dispatch_thread_suspended = 2; // ???
            }
            result = 0;
            break;
        }

    case STATUS_READY:
        {
            if (intr_context && this == theKernelScheduler.m_current_thread)
            {
                theKernelScheduler.m_next_thread = 0;
            }
            else
            {
                theKernelScheduler.RemoveThreadFromReadyQueue(this);
            }           
            theKernelScheduler.m_suspended_threads.Append(this);

            this->m_status = STATUS_SUSPEND;
            result = 0;
        }
        break;

    case STATUS_WAIT:
        {
            this->m_status |= STATUS_SUSPEND;
            result = 0;
        }
        break;

    case STATUS_SUSPEND:
    case STATUS_WAITSUSPEND:
        {
            result = SCE_KERNEL_ERROR_SUSPEND;
        }
        break;

    default:
        {
            result = SCE_KERNEL_ERROR_DORMANT;
        }
        break;
    }

    sceKernelCpuResumeIntr(state);

    return result;
}

// for sceKernelResumeThread
int KernelThread::Resume()
{
    int intr_context = sceKernelIsIntrContext();

    int state = sceKernelCpuSuspendIntr();

    int result;

    switch (this->m_status)
    {
    case STATUS_RUN:
        {
            if (theKernelScheduler.m_dispatch_thread_suspended == 2)
            {
                theKernelScheduler.m_dispatch_thread_suspended = 1;
                result = 0;
            }
            else
            {
                result = SCE_KERNEL_ERROR_NOT_SUSPEND;
            }
        }
        break;

    case STATUS_SUSPEND:
        {
            this->RemoveFromList();

            if (!intr_context)
            {
                this->m_status = STATUS_READY;
                this->SwitchTo(state);
            }
            else
            {
                theKernelScheduler.AddThreadToReadyQueue(this);
                theKernelScheduler.m_next_thread = 0;
            }

            result = 0;
        }
        break;

    case STATUS_WAITSUSPEND:
        {
            this->m_status = STATUS_WAIT;
            result = 0;
        }
        break;

    default:
        {
            result = SCE_KERNEL_ERROR_NOT_SUSPEND;
        }
        break;

    }

    sceKernelCpuResumeIntr(state);

    return result;
}

int KernelThread::WaitThreadEnd(SceUInt *timeout, bool cb)
{
    if (sceKernelIsIntrContext())
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (!state || theKernelScheduler.m_dispatch_thread_suspended)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    if (this == theKernelScheduler.m_current_thread)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_ILLEGAL_THID;
    }

    if (this->m_status >= STATUS_DORMANT)
    {
        sceKernelCpuResumeIntr(state);

        return this->m_exit_status;
    }

    SceKernelSysClock clk;

    if (timeout)
    {
        clk += u64(*timeout);
    }

    int result;
    do
    {
        if (cb && this->m_callback_notify)
        {
            DispatchCallbacks(state);
        }

        this->m_check_callbacks = cb;

        result = 0;
        //result = AddThreadToWaitQueue(cb, 0x9, 0, &clk, timeout);
    } while(cb && result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK);

    sceKernelCpuResumeIntr(state);

    return result;
}

int KernelThread::Delay(SceUInt delay, bool cb)
{
    if (sceKernelIsIntrContext())
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (state == 0 || theKernelScheduler.m_dispatch_thread_suspended != 0)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    u64 time = delay + KernelSysClock::Get();

    do
    {
        if (cb && this->m_callback_notify)
        {
            DispatchCallbacks(state);
        }

        this->m_timeout = 0;

        int result = RequestTimeout(time);
        if (result < 0)
        {
            sceKernelCpuResumeIntr(state);

            return (result == SCE_KERNEL_ERROR_WAIT_TIMEOUT) ? 0 : result;
        }

        theKernelScheduler.m_delayed_threads.AddWaitingThread(this, KernelWaitQueue::WAITTYPE_DELAY);

        ReleaseWait(true, 1);
    }
    while (cb && this->m_callback_status == SCE_KERNEL_ERROR_NOTIFY_CALLBACK);

    sceKernelCpuResumeIntr(state);

    return this->m_callback_status;
}

void KernelThread::DispatchCallbacks(int state)
{
    this->m_callback_notify = 0;

    //TODO
}

void KernelThread::SwitchTo(int intr)
{
    if (this->m_current_priority >= theKernelScheduler.m_current_thread->m_current_priority || theKernelScheduler.m_dispatch_thread_suspended)
    {
        theKernelScheduler.AddThreadToReadyQueue(this);

        return;
    }

    if (intr)
    {
        theKernelScheduler.AddThreadToReadyQueue(theKernelScheduler.m_current_thread);

        this->m_status = STATUS_RUN;
        theKernelScheduler.m_next_thread = this;
    }
    else
    {
        theKernelScheduler.AddThreadToReadyQueue(this);
        theKernelScheduler.m_next_thread = 0;
    }

    ReleaseWait(false, intr);
}

void KernelThread::ReleaseWait(bool released, int state)
{
    this->m_count = released ? &this->m_release_count : &this->m_thread_preempt_count;
    if (state)
    {
        //    _MTC0(_MFC0(COP0_SR_CAUSE) | 0x200, COP0_SR_CAUSE);
        //    sceKernelEnableIntr(0x41);
    }
    else
    {
        this->SwitchToNext();
        this->m_check_callbacks = 0;
    }
}

int KernelThread::RequestTimeout(u64 timeout)
{
    KernelDelay *delay = theKernelScheduler.m_delays.Acquire();

    if (delay)
    {
        u64 compare_time = timeout;
        u64 current_time = KernelSysClock::Get();

        if (compare_time <= current_time)
        {
            theKernelScheduler.m_delays.Release(delay);
            return SCE_KERNEL_ERROR_WAIT_TIMEOUT;
        }

        delay->m_time   = timeout;
        delay->m_thread = this;

        theKernelScheduler.m_timers.AddTimerToList(delay);
        theKernelScheduler.m_timers.RescheduleTimers();

        this->m_timeout_object = delay;

        return delay->GetUid();
    }

    return SCE_KERNEL_ERROR_NO_MEMORY;
}
#endif

////

#if 1

void KernelScheduler::ElectNextRunningThread()
{
    int i, bit, priority;

    this->m_next_thread = this->m_current_thread;

    if (this->m_do_cleanup)
    {
        this->m_do_cleanup = 0;

        for (KernelThread *deletable_thread = theKernelScheduler.m_deletable_threads.First(); deletable_thread; )
        {
            KernelThread *next_thread = theKernelScheduler.m_deletable_threads.Next(deletable_thread);

            deletable_thread->Delete(0);

            deletable_thread = next_thread;
        }
    }

    for (i = 0; i < (MAX_THREAD_PRIORITY + 1) / 32; i++)
    {
        int mask = this->m_priority_mask[i];
        if (mask != 0)
        {
            for (bit = 0; bit < 31; bit++)
            {
                if (mask & (1 << bit))
                {
                    break;
                }
            }
            priority = i * 32 + bit;
            break;
        }
    }

    if (i == (MAX_THREAD_PRIORITY + 1) / 32)
    {
        priority = MAX_THREAD_PRIORITY + 1;
    }

    if (priority > MAX_THREAD_PRIORITY)
    {
        return;
    }

    KernelThread *current_thread = this->m_current_thread;

    if (current_thread->m_status == KernelThread::STATUS_RUN)
    {
        int current_priority = current_thread->m_current_priority;

        if (priority >= current_priority)
        {
            return;
        }

        // make current thread ready
        theKernelScheduler.AddThreadToReadyQueue(current_thread);
    }

    // set next thread to run
    theKernelScheduler.ElectNextReadyThread(priority);
}

void KernelScheduler::AddThreadToReadyQueue(KernelThread *runnable_thread)
{
    int current_priority = runnable_thread->m_current_priority;
    this->m_priority_mask[current_priority / 32] |= 1 << (current_priority % 32);
    this->m_ready_threads[current_priority].Append(runnable_thread);
    runnable_thread->m_status = KernelThread::STATUS_READY;
}

void KernelScheduler::RemoveThreadFromReadyQueue(KernelThread *runnable_thread)
{
    int current_priority = runnable_thread->m_current_priority;
    runnable_thread->RemoveFromList();
    if (this->m_ready_threads[current_priority].Empty())
    {
        this->m_priority_mask[current_priority / 32] &= ~(1 << (current_priority % 32));
    }
}

void KernelScheduler::AddThreadToDormantQueue(KernelThread *dormant_thread)
{
    this->m_stopped_threads.Append(dormant_thread);
    dormant_thread->m_status = KernelThread::STATUS_STOPPED;
}

void KernelScheduler::AddThreadToCleanupQueue(KernelThread *deletable_thread)
{
    this->m_stopped_threads.Append(deletable_thread);
    deletable_thread->m_status = KernelThread::STATUS_DORMANT;
}

void KernelScheduler::ElectNextReadyThread(int priority)
{
    KernelThread *next_thread = this->m_ready_threads[priority].First();
    if (!(this->m_ready_threads[priority].Empty()) && next_thread == this->m_ready_threads[priority].Last())
    {
        this->m_priority_mask[priority / 32] &= ~(1 << (priority % 32));
    }
    next_thread->RemoveFromList();
    this->m_next_thread = next_thread;
    next_thread->m_status = KernelThread::STATUS_RUN;
}

#else

void KernelScheduler::ElectNextRunningThread()
{
	int i, bit, priority;

	this->m_next_thread = this->m_current_thread;

	if (this->m_do_cleanup == 0)
	{
		for (i = 0; i < (MAX_THREAD_PRIORITY + 1) / 32; i++)
		{
			int mask = this->m_priority_mask[i];
			if (mask != 0)
			{
				for (bit = 0; bit < 31; bit++)
				{
					if (mask & (1 << bit))
					{
						break;
					}
				}
				priority = i * 32 + bit;
				break;
			}
		}

		if (i == (MAX_THREAD_PRIORITY + 1) / 32)
		{
			priority = MAX_THREAD_PRIORITY + 1;
		}

		if (priority > MAX_THREAD_PRIORITY)
		{
			//Kprintf("Panic: not found ready Thread\n");
			return;
		}

		KernelThread *current_thread = this->m_current_thread;

		if (current_thread->m_status == KernelThread::STATUS_RUN)
		{
			int current_priority = current_thread->m_current_priority;

			if (priority >= current_priority)
			{
				return;
			}

			// make current thread ready
			theKernelScheduler.AddThreadToReadyQueue(current_thread);
		}

		// set next thread to run
		theKernelScheduler.ElectNextReadyThread(priority);
	}
	else
	{
		this->m_do_cleanup = 0;

		// set the cleaner thread to run next
		this->m_cleaner_thread->m_status = KernelThread::STATUS_RUN;
		this->m_next_thread = this->m_cleaner_thread;

		KernelThread *current_thread = this->m_current_thread;

		if (current_thread->m_status != KernelThread::STATUS_RUN)
		{
			return;
		}

		// make current thread ready
		theKernelScheduler.AddThreadToReadyQueue(current_thread);
	}
}

void KernelScheduler::AddThreadToReadyQueue(KernelThread *thread)
{
    int current_priority = thread->m_current_priority;
    this->m_priority_mask[current_priority / 32] |= 1 << (current_priority % 32);
    this->m_ready_threads[current_priority].Append(thread);
    thread->m_status = KernelThread::STATUS_READY;
}

void KernelScheduler::RemoveThreadFromReadyQueue(KernelThread *thread)
{
    int priority = thread->m_current_priority;
    thread->RemoveFromList();
    if (this->m_ready_threads[priority].Empty())
    {
        this->m_priority_mask[priority / 32] &= ~(1 << (priority % 32));
    }
}

void KernelScheduler::ElectNextReadyThread(int priority)
{
    KernelThread *next_thread = this->m_ready_threads[priority].First();
    if (!(this->m_ready_threads[priority].Empty()) && next_thread == this->m_ready_threads[priority].Last())
    {
        this->m_priority_mask[priority / 32] &= ~(1 << (priority % 32));
    }
    next_thread->RemoveFromList();
    this->m_next_thread = next_thread;
    next_thread->m_status = KernelThread::STATUS_RUN;
}

void KernelScheduler::_AddThreadToCleanupQueue( SceUID id )
{

}

void KernelScheduler::AddThreadToDelayList(KernelThread *thread)
{

}

void KernelScheduler::RemoveThreadFromDelayList(KernelThread *thread)
{

}

#endif

bool KernelScheduler::Reboot()
{
#if 0
    m_threadret_syscall_id = sysmem::hleKernelAllocPartitionMemory(1, "threadret_syscall", 0, 8, 0);
    m_threadret_syscall    = sysmem::hleKernelGetBlockHeadAddr(m_threadret_syscall_id);
    theKernelModuleManager.WriteSyscall("threadret_syscall", 0xc0debabe, m_threadret_syscall);
#endif
    return true;
}

bool KernelScheduler::ShutDown()
{
#if 0
    if (m_threadret_syscall_id > 0)
    {
        sysmem::hleKernelFreePartitionMemory(m_threadret_syscall_id);
    }
    m_threadret_syscall    = 0;
    m_threadret_syscall_id = 0;
    m_current_thread       = 0;
#endif
    return true;
}

int KernelScheduler::SuspendDispatchThread(int intr)
{
    if (!intr)
    {
        return SCE_KERNEL_ERROR_CPUDI;
    }

    if (!this->m_dispatch_thread_suspended)
    {
        this->m_dispatch_thread_suspended = 1;
        return 1;
    }
    return 0;
}

int KernelScheduler::ResumeDispatchThread(int old, int intr)
{
    if (!intr)
    {
        return SCE_KERNEL_ERROR_CPUDI;
    }

    if (old)
    {
        if (this->m_dispatch_thread_suspended)
        {
            switch (this->m_dispatch_thread_suspended)
            {
            case 1: // running thread
                this->m_dispatch_thread_suspended = 0;
                break;
            case 2: // running thread must be now suspended (deferred operation)
                this->m_dispatch_thread_suspended = 0;
                theKernelScheduler.m_suspended_threads.Append(this->m_current_thread);
                this->m_current_thread->m_status = KernelThread::STATUS_SUSPEND;
                break;
            case 3: // running thread must be now killed (deferred operation)
                this->m_dispatch_thread_suspended = 0;
                this->m_current_thread->Exit(SCE_KERNEL_ERROR_THREAD_TERMINATED, intr);
                break;
            default:
                return SCE_KERNEL_ERROR_OK;
            }

            theKernelScheduler.m_next_thread = 0;

            this->m_current_thread->ReleaseWait(0, intr);
        }
    }
    else if (!this->m_dispatch_thread_suspended)
    {
        this->m_dispatch_thread_suspended = 1;
    }

    return SCE_KERNEL_ERROR_OK;
}

