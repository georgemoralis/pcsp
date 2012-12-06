#pragma once

#include <QtCore>

#include "al/al.h"
#include "hle/kernel/kernel_timer.h"

enum EmulatorState
{
    EmuPausing,
    EmuRunning,
    EmuLeaving,

    EmuIdleThread,
    EmuCleanupThread,

    EmuThreadEvent,
    EmuThreadCreateEvent = EmuThreadEvent + 0,
    EmuThreadStartEvent  = EmuThreadEvent + 1,
    EmuThreadExitEvent   = EmuThreadEvent + 2,
    EmuThreadDeleteEvent = EmuThreadEvent + 3,

    EmuAudioEvent,
    EmuAudio0Event = EmuAudioEvent + 0,
    EmuAudio1Event = EmuAudioEvent + 1,
    EmuAudio2Event = EmuAudioEvent + 2,
    EmuAudio3Event = EmuAudioEvent + 3,
    EmuAudio4Event = EmuAudioEvent + 4,
    EmuAudio5Event = EmuAudioEvent + 5,
    EmuAudio6Event = EmuAudioEvent + 6,
    EmuAudio7Event = EmuAudioEvent + 7,
    EmuAudio8Event = EmuAudioEvent + 8,

    EmuClockEvent,
    
    EmuVsyncEvent,
    
    EmuGeEvent,

    EmuLoadExecEvent,
};

#include "sc_thread.h"

class NoThread : public JoinableThread { void Run() {} };

typedef NoThread GeThread;
typedef NoThread MeThread;

class Emulator
:   public Mutex
{
    template< typename Derived >
    friend class EmulatorFiber;

public:
    Emulator();
    ~Emulator();

    AlContext *context;
    bool       reschedule;

public:
    bool StartUp();
    bool ShutDown();

    void Reschedule();

    EmulatorState State() const                 { return m_current_state; }

    u32          &CurrentState()                { return *((u32 *)&m_current_state); }

    //void Run();                              
    void Resume()                               { m_current_state = EmuRunning; };
    void Pause()                                { m_current_state = EmuPausing; };
    void Leave()                                { m_current_state = EmuLeaving; };
    
    bool Start()                                { if (m_needs_start) { Resume(); m_needs_start = false; return true; }; return false; }
    void Load()                                 { m_needs_load = true; };
                                             
    bool IsRunning()                            { return m_current_state == EmuRunning; }
    bool IsPausing()                            { return m_current_state == EmuPausing; }
    bool IsLeaving()                            { return m_current_state == EmuLeaving; }
    bool IsLoading()                            { return m_needs_load; }
    bool IsGameLoaded()                         { return m_loaded_game; }

    void SetLoadExecEvent()                     { m_current_state = EmuLoadExecEvent;                       }
    void SetAudioEvent(u32 channel)             { m_current_state = EmulatorState(EmuAudioEvent + channel); }
    void SetClockEvent()                        { m_current_state = EmuClockEvent;                          }
    void SetVsyncEvent()                        { m_current_state = EmuVsyncEvent;                          }
    void SetGeEvent()                           { m_current_state = EmuGeEvent;                             }                                            

    void LoadExecEvent()                        { /*loop:*/ MutexLocker locker(*this); /*if (IsRunning())*/ SetLoadExecEvent(); /*else goto loop;*/     }
    void AudioEvent(u32 channel)                { /*loop:*/ MutexLocker locker(*this); /*if (IsRunning())*/ SetAudioEvent(channel); /*else goto loop;*/ }
    void ClockEvent()                           { /*loop:*/ MutexLocker locker(*this); /*if (IsRunning())*/ SetClockEvent(); /*else goto loop;*/        }
    void VsyncEvent()                           { /*loop:*/ MutexLocker locker(*this); /*if (IsRunning())*/ SetVsyncEvent(); /*else goto loop;*/        }
    void GeEvent()                              { /*loop:*/ MutexLocker locker(*this); /*if (IsRunning())*/ SetGeEvent(); /*else goto loop;*/           }                                            

    bool SetNewGame(QString const &filename)	{ m_current_game_filename = filename; m_needs_load = true; return true; }
    void StartGame()						    { if (IsPausing()) { m_needs_start = true; } }
    void PauseGame()						    { if (IsRunning()) { Pause(); } }
    void LoadGame();
    void UnloadGame();
    
    QString const &getGameFilename() const      { return m_current_game_filename; }

    int  EventCounter() const                   { return m_test_event_counter; }
    void IncreaseEventCounter()                 { m_test_event_counter++; }

    sc_Thread &Sc()								{ return m_sc_thread; }
    GeThread &Ge()                              { return m_ge_thread; }
    MeThread &Me()                              { return m_me_thread; }

    void RegisterGuiReceiver(QObject *receiver) { m_gui_receiver = receiver; }
    QObject const *GuiReceiver() const          { return m_gui_receiver; }

private:
    volatile EmulatorState	m_current_state;

    sc_Thread		        m_sc_thread;
    NoThread		        m_ge_thread;
    NoThread		        m_me_thread;

    volatile bool  			m_needs_load;
    volatile bool  			m_needs_start;
    volatile bool       	m_loaded_game;

    QString     			m_current_game_filename;

    volatile int            m_test_event_counter;

    QObject                *m_gui_receiver;

    Emulator(Emulator const &) {};			                    // copy constructor is hidden
    Emulator &operator = (Emulator const &) { return *this; };	// assign operator is hidden  
};

extern Emulator	theEmulator;

template< typename Derived >
class ScFiber
:   public Fiber
{
    friend class Emulator;

public:
    ScFiber()
    :   Fiber(&ScFiber::Run, static_cast< Derived * >(this))
    {

    }

    ~ScFiber()
    {
    }

    static void Run(void *arg)
    {
        Derived *that = static_cast< Derived * >(arg);
        MutexLocker locker(theEmulator);
loop:
        switch (theEmulator.State())
        {
        case EmuRunning:
            if (theEmulator.reschedule)
            {
                theEmulator.reschedule = false;
                locker.Unlock();        
                theEmulator.Reschedule();
            }
            else
            {
                locker.Unlock();
            }
            do { that->m_thread_context.Interpret(); } while (theEmulator.IsRunning());
            locker.Relock();
            goto loop;

        case EmuPausing:
            if (!theEmulator.Start())
            {
                sc_Thread::Sleep(100);
            }
            goto loop;

        case EmuThreadCreateEvent:
        case EmuThreadStartEvent:
        case EmuThreadExitEvent:
        case EmuThreadDeleteEvent:
            goto loop;

        case EmuAudio0Event:
        case EmuAudio1Event:
        case EmuAudio2Event:
        case EmuAudio3Event:
        case EmuAudio4Event:
        case EmuAudio5Event:
        case EmuAudio6Event:
        case EmuAudio7Event:
        case EmuAudio8Event:
            // wake up all the threads waiting on this event 
            that->HandleAudioEvent(theEmulator.State() - EmuAudioEvent);
            goto loop;

        case EmuClockEvent:
            that->HandleClockEvent();
            goto loop;

        case EmuVsyncEvent:
            that->HandleVsyncEvent();
            goto loop;

        case EmuGeEvent:
            that->HandleGeEvent();
            goto loop;

        case EmuIdleThread:
            that->DoIdle();
            goto loop;

        case EmuCleanupThread:
            that->DoCleanUp();
            goto loop;

		case EmuLoadExecEvent:
        case EmuLeaving:
            // this is quite brutal 
            break;

        default:
            goto loop;
        }
    }

    void HandleVsyncEvent()              { theEmulator.Resume(); } // default: do nothing
    void HandleGeEvent()                 { theEmulator.Resume(); } // default: do nothing
    void HandleClockEvent()              { theEmulator.Resume(); } // default: do nothing
    void HandleAudioEvent(u32 channel)   { theEmulator.Resume(); } // default: do nothing

    void DoIdle()                        { theEmulator.Resume(); } // default: do nothing
    void DoCleanUp()                     { theEmulator.Resume(); } // default: do nothing
};
