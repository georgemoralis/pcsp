#include "stdafx.h"
#include "sc_thread.h"
#include "renderer.h"
#include "qinputsystem.h"
#include "system.h"
#include "hle/kernel.h"
#include "hardware/memorystick.h"

sc_Thread::sc_Thread()
{
}

sc_Thread::~sc_Thread()
{
}

void sc_Thread::Run()
{
    ConnectSignals();

    mem_stick::init();

    if (Memory::Initialize() && theRenderer.Initialize() && kernel::Reboot())
    {
loop:
        switch (theEmulator.State())
        {
        case EmuLeaving: 
            break;

        case EmuLoadExecEvent:
            theEmulator.Pause();
            theEmulator.UnloadGame();
            kernel::Reboot();
            theEmulator.Load();
            theEmulator.StartGame();
            goto loop;

        case EmuPausing:
            if (theEmulator.IsLoading())
            {
                theEmulator.LoadGame();
            }

        default:
            Thread::Sleep(100);
            goto loop;
        }
    }
    else
    {
        EmitShutDown();
    }

    theEmulator.UnloadGame();
    kernel::ShutDown();
    theRenderer.Terminate();
    Memory::Terminate();

    DisconnectSignals();
}

void sc_Thread::ConnectSignals() const
{
    connect(this, SIGNAL(EmitCritical(QString,QString)             ), theEmulator.GuiReceiver(), SLOT(onCritical(QString,QString)             ), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(EmitWarning(QString,QString)              ), theEmulator.GuiReceiver(), SLOT(onWarning(QString,QString)              ), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(EmitOsk(SceUtilityOskParam*)              ), theEmulator.GuiReceiver(), SLOT(onOsk(SceUtilityOskParam*)              ), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(EmitMsgDialog(SceUtilityMsgDialogParam*)  ), theEmulator.GuiReceiver(), SLOT(onMsgDialog(SceUtilityMsgDialogParam*)  ), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(EmitSavedataSave(SceUtilitySavedataParam*)), theEmulator.GuiReceiver(), SLOT(onSavedataSave(SceUtilitySavedataParam*)), Qt::BlockingQueuedConnection);
	connect(this, SIGNAL(EmitSavedataLoad(SceUtilitySavedataParam*)), theEmulator.GuiReceiver(), SLOT(onSavedataLoad(SceUtilitySavedataParam*)), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(EmitShutDown())                            , theEmulator.GuiReceiver(), SLOT(menuExit())                                                            );
}

void sc_Thread::DisconnectSignals()
{
    disconnect(theEmulator.GuiReceiver(), SLOT(onCritical(QString,QString))             );
    disconnect(theEmulator.GuiReceiver(), SLOT(onWarning(QString,QString))              );
    disconnect(theEmulator.GuiReceiver(), SLOT(onOsk(SceUtilityOskParam*))              );
    disconnect(theEmulator.GuiReceiver(), SLOT(onMsgDialog(SceUtilityMsgDialogParam*))  );
	disconnect(theEmulator.GuiReceiver(), SLOT(onSavedataSave(SceUtilitySavedataParam*)));
    disconnect(theEmulator.GuiReceiver(), SLOT(onSavedataLoad(SceUtilitySavedataParam*)));
    disconnect(theEmulator.GuiReceiver(), SLOT(menuExit())                              );
}

#include "hle/modules/iofilemgr/IoFileMgrForUser.h"
#include "hle/modules/utility/sceUtility.h"
#include "hle/modules/utility/sceUtilityOSK.h"
#include "hle/modules/utility/sceUtilityMsgDialog.h"
#include "hle/modules/utility/sceUtilitySave.h"

void sc_Thread::Osk(SceUtilityOskParam *param)
{
    EmitOsk(param);
}

void sc_Thread::MsgDialog(SceUtilityMsgDialogParam *param)
{
    EmitMsgDialog(param);
}
void sc_Thread::SavedataSave(SceUtilitySavedataParam *param)
{
    EmitSavedataSave(param);
}
void sc_Thread::SavedataLoad(SceUtilitySavedataParam *param)
{
    EmitSavedataLoad(param);
}