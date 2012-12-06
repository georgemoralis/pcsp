#include "stdafx.h"

#include "common_fiber.h"

Fiber *Fiber::m_thread = 0;

#ifdef FIBER_WIN32

Fiber::Fiber()
:   m_function(0)
,   m_argument(0)

{
    m_thread       = this;
    m_native_fiber = ::ConvertThreadToFiber((LPVOID)0);
}


void Fiber::EntryPoint(void *that)
{
    Fiber *fiber = (Fiber *)that;
    
    if (fiber->m_function)
    {
        fiber->m_function(fiber->m_argument);
    }

    m_thread->SwitchTo();
}

#else

Fiber *Fiber::m_current = 0;

#include <stdlib.h>
#include <QtCore/QtGlobal>
#include <QtCore/QThreadStorage>

#undef  assert
#define assert(x) Q_ASSERT(x)

#ifdef Q_OS_MAC
extern "C" void SwitchStackInternal(void *to, void **from);
#define SwitchStack(to, from) SwitchStackInternal(to, from)
#else
extern "C" void _SwitchStackInternal(void *to, void **from);
#define SwitchStack(to, from) _SwitchStackInternal(to, from)
#endif

#if (defined(_M_IX86) /* msvc */ || defined(__i386__) /* gcc */)

void InitializeStack(void *data, int size, void (*entry)(), void **stack_pointer)
{
    void  *stack_bottom = (void  *)(((u32)data + size) & ~15);
    void **p            = (void **)stack_bottom;

    *(--p) = 0;                     // 16-byte alignment 
    *(--p) = (void *)entry;         // eip
    *(--p) = stack_bottom;          // ebp
    *(--p) = 0;                     // ebx
    *(--p) = 0;                     // esi
    *(--p) = 0;                     // edi
    *(--p) = (void *)0x00001f80;    // SIMD floating point control default
    *(--p) = (void *)0x0000033f;    // floating point control default
    
    *stack_pointer = p;
}

#elif (defined(__x86_64__) /* gcc */)

void InitializeStack(void *data, int size, void (*entry)(), void **stack_pointer)
{
    void  *stack_bottom = (void  *)(((u64)data + size) & ~15);
    void **p            = (void **)stack_bottom;

    *(--p) = (void*)entry;               // rip
    *(--p) = stack_bottom;               // rbp

    *(--p) = 0;                          // rbx
    *(--p) = 0;                          // r12

    *(--p) = 0;                          // r13
    *(--p) = 0;                          // r14

    *(--p) = 0;                          // r15
    *(--p) = (void *)0x00001f800000033f; // SIMD and regular floating point control defaults

    *stack_pointer = p;
}

#endif

#if (defined(_WIN32) && defined(_M_IX86) /* msvc */)
extern "C"
{
    void __declspec(naked, noinline) _SwitchStackInternal(void *to, void **from)
    {
        __asm
        {
            // save callee-saved registers
            PUSH        EBP;
            PUSH        EBX;
            PUSH        ESI;
            PUSH        EDI;

            SUB         ESP, 4;
            // store SIMD floating point control word
            STMXCSR     [ESP];

            // store floating point control bytes
            SUB         ESP, 4;
            FSTCW       [ESP];

            // save the old stack pointer
            MOV         EAX, dword ptr 32[ESP]; // 8+4*6 = 32
            MOV         dword ptr 0[EAX], ESP;

            // set the new stack pointer
            MOV         ESP, dword ptr 28[ESP]; // 4+4*6 = 28

            // restore floating point control bytes
            FNCLEX;
            FLDCW       [ESP];
            ADD         ESP, 4;

            // restore SIMD floating point control word
            LDMXCSR     [ESP];
            ADD         ESP, 4;

            // pop callee-saved registers
            POP         EDI;
            POP         ESI;
            POP         EBX;
            POP         EBP;

            RET;
        }
    }
}

#endif

//#undef  Q_ASSERT
//#define Q_ASSERT(x)

void Fiber::EntryPoint()
{
    Fiber *fiber = Fiber::m_current;

    if (fiber->m_function)
    {
        fiber->m_function(fiber->m_argument);
    }

    m_thread->SwitchTo();
}

void Fiber::CreateFiber(FiberFunction function, void *argument)
{
    m_stack_data = new u8[FIBER_STACK_SIZE];

    InitializeStack(m_stack_data, FIBER_STACK_SIZE, &EntryPoint, &m_stack_pointer);
}

void Fiber::DeleteFiber()
{
    Fiber *that = GetCurrentFiber();

    assert(that != this);

    if (m_stack_data)
    {
        delete[] (u8 *)m_stack_data;
    }
    m_stack_data    = 0;
    m_stack_pointer = 0;
}

void Fiber::ConvertThreadToFiber()
{
    if (!m_current)
    {
        Fiber * volatile trampoline = new Fiber(&ThreadFunction, this); // msvc global optimization is too much aggressive without    
        Fiber *          that       = trampoline;

        m_current = that;

        SwitchStack(that->m_stack_pointer, &this->m_stack_pointer);

        m_thread = this;

        that = trampoline; // msvc global optimization is too much aggressive without 

        delete that;
    }
}

void Fiber::ConvertFiberToThread()
{
    m_current = 0;
    m_thread  = 0;
}

void Fiber::SwitchToFiber(Fiber *next)
{
    Fiber *prev = m_current;

    m_current = next;

    if (next != prev)
    {
        SwitchStack(next->m_stack_pointer, &prev->m_stack_pointer);
    }
}

void *Fiber::GetFiberData()
{
    Fiber *that = GetCurrentFiber();

    if (that)
    {
        return that->m_argument;
    }

    return 0;
}

Fiber *Fiber::GetCurrentFiber()
{
    if (!m_current)
    {
        return 0;
    }

    return m_current;
}

void Fiber::ThreadFunction(void *argument)
{
    Fiber *next = (Fiber *)argument;
    Fiber *prev = GetCurrentFiber();

    m_current = next;

    SwitchStack(next->m_stack_pointer, &prev->m_stack_pointer);
}

Fiber::Fiber()
:   m_function(0)
,   m_argument(0)
,   m_stack_data(0)
,   m_stack_pointer(0)
{
    ConvertThreadToFiber();
}
#endif