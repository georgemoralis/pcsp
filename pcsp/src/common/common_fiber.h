#ifndef common_fiber_h__
#define common_fiber_h__

#define FIBER_STACK_SIZE 8 * 4096

#if !defined(FIBER_WIN32)
#   if defined(WIN32)
//#       define FIBER_WIN32
#   endif
#endif

typedef void (*FiberFunction)(void *);

#ifdef FIBER_WIN32

class Fiber
{
private:
    Fiber();

    static void   EntryPoint(void *);

public:
    Fiber(FiberFunction function, void *argument)
    :   m_function(function)
    ,   m_argument(argument)
    {
        static Fiber thread_converted_into_fiber;

        m_native_fiber = ::CreateFiber((SIZE_T)FIBER_STACK_SIZE, (LPFIBER_START_ROUTINE)EntryPoint, (LPVOID)this);
    }

    virtual ~Fiber()
    {
        if (m_thread == this)
        {
            ::ConvertFiberToThread();

            m_thread = 0;
        }
        else if (::GetCurrentFiber() != m_native_fiber)
        {
            ::DeleteFiber(m_native_fiber);
        }
    }

    static Fiber *Create(FiberFunction function, void *argument)
    { 
        return new Fiber(function, argument);
    }

    static void Delete(Fiber *fiber)
    {
        delete fiber;
    }

    void SwitchTo()
    {
        ::SwitchToFiber(m_native_fiber);
    }

private: // not copyable
    Fiber(Fiber const &);
    Fiber &operator =(Fiber const &);

    FiberFunction m_function;
    void         *m_argument;
    LPVOID        m_native_fiber;
    static Fiber *m_thread;
};

#else

class Fiber // this class is still not perfect (some games works, some games like lemmings can crash)
{
private:
    void          CreateFiber(FiberFunction, void *);
    void          DeleteFiber();
    void          ConvertThreadToFiber();
    void          ConvertFiberToThread();
    static void   SwitchToFiber(Fiber *);
    static void  *GetFiberData();
    static Fiber *GetCurrentFiber();

    static void   EntryPoint();
    static void   ThreadFunction(void *argument);

    Fiber();

public:
    Fiber(FiberFunction function, void *argument)
    :   m_function(function)
    ,   m_argument(argument)
    ,   m_stack_data(0)
    ,   m_stack_pointer(0)
    {
        static Fiber thread_converted_into_fiber;

        CreateFiber(function, argument);
    }

    virtual ~Fiber()
    {
        if (m_thread == this)
        {
            ConvertFiberToThread();

            m_thread = 0;
        }
        else if (GetCurrentFiber() != this)
        {
            DeleteFiber();
        }
    }

    static Fiber *Create(FiberFunction function, void *argument)
    {
        return new Fiber(function, argument);
    }

    static void Delete(Fiber *fiber)
    {
        delete fiber;
    }

    void SwitchTo()
    {
        SwitchToFiber(this);
    }

private: // not copyable
    Fiber(Fiber const &);
    Fiber &operator =(Fiber const &);

    FiberFunction m_function;
    void         *m_argument;
    void         *m_stack_data;
    void         *m_stack_pointer;
    static Fiber *m_thread;
    static Fiber *m_current;
};

#endif
#endif // common_fiber_h__
