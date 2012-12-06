#include "stdafx.h"
#include "sceGe_user.h"
#include "hle/types.h"
#include "log.h"
#include "ge_DisplayListInterpreter.h"
#include "ge_Context.h"
#include "ge_Types.h"
#include "kernel/kernel_vsync.h"
#include "renderer.h"

namespace sceGe_user
{
	static bool geman_ready = false;

    bool ShutDown()
    {
        if (geman_ready)
        {
            geman_ready = false;
        }
        return true;
    }
    bool Reboot()
    {
        ShutDown();
        geman_ready = true;
        return true;
    }

	int GeState = 0;

	bool geBufChanged = false;

	SceGeStack	stack;

	const u32 START_VRAM               = 0x04000000;
	const u32 END_VRAM                 = 0x041FFFFF;
	const u32 SIZE_VRAM                = END_VRAM - START_VRAM + 1;

	
	int sceGeGetStack()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeGetStack instruction");
		return 0;
	}
	int sceGeEdramGetAddr()
	{
		u32 retVal = START_VRAM;
		return retVal;
	}
	int sceGeListUpdateStallAddr(u32 a0, u32 a1)
	{
		u32 displayListID	= a0;
		u32 stallAddress	= a1;

		theDisplayInterpreter.UpdateStall(displayListID, stallAddress);

		return 0;
	}
	int sceGeGetCmd()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeGetCmd instruction");
		return 0;
	}
	int sceGeEdramSetAddrTranslation()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeEdramSetAddrTranslation instruction");
		return 0;
	}
	int sceGeBreak()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeBreak instruction");
		return 0;
	}
	int sceGeDrawSync()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeDrawSync instruction");
        //KernelVsync::NextFrame();
		return 0;
	}
	int sceGeListEnQueue(u32 a0, u32 a1, u32 a2, u32 a3)
	{
		u32 listAddress		= a0; // Display list starting address
        u32 stallAddress	= a1; // Initial stall address
		u32 callbackId		= a2; // Callback ID
		u32 optParamAddr	= a3; // Option specification (context save area specification)
		
		u32 listID = theDisplayInterpreter.Add(listAddress,stallAddress);
		if (listID)
			GeState = SCE_GE_LIST_STALLING;
        else
			GeState = SCE_GE_LIST_COMPLETED;
		
        (void)callbackId;
        (void)optParamAddr;

		return listID;
	}
	int sceGeSetCallback()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeSetCallback instruction");
		return 0;
	}
	int sceGeListDeQueue()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeListDeQueue instruction");
		return 0;
	}

	int sceGeGetMtx(u32 a0, u32 a1)
	{
		ge_matrix_type type = (ge_matrix_type)a0; // matrix register
		u32 *dest_buffer = Memory::addr< u32 >(a1); // dest data buffer
		u32 *src_buffer = 0;
		if (type > 11)
		{
				return SCE_ERROR_INVALID_INDEX; // out of register index
				errorf(sceGe_user, "SCE_ERROR_INVALID_INDEX in sceGeGetMtx()");
		}
		src_buffer = (u32 *)theRenderer.GetMatrix(type)->mData;
		memcpy(dest_buffer, src_buffer, 16 * 4);
		return 0;
	}

	int sceGeContinue()
	{
		//TODO implement me
		errorf(sceGe_user, "UNIMPLEMENTED sceGeContinue instruction");
		return 0;
	}

    int sceGeSaveContext(u32 a0)
	{
        // TODO : we need a better way to handle it
        memcpy(Memory::addr< void >(a0), &theGeContext, sizeof(ge_Context));
        return 0; 
	}

    int sceGeRestoreContext(u32 a0)
    {
        // TODO : we need a better way to handle it
        memcpy(&theGeContext, Memory::addr< void >(a0), sizeof(ge_Context));
        return 0; 
    }

    int sceGeEdramGetSize()
	{
		return SIZE_VRAM;
	}

    int sceGeListEnQueueHead()
	{
		//TODO implement me
		errorf(sceGe_user,"UNIMPLEMENTED sceGeListEnQueueHead instruction");
		return 0;
	}

	int sceGeUnsetCallback()
	{
		//TODO implement me
		errorf(sceGe_user,"UNIMPLEMENTED sceGeUnsetCallback instruction");
		return 0;
	}

    int sceGeListSync()
	{
		errorf(sceGe_user,"UNIMPLEMENTED sceGeListSync instruction");
		return 0;
	}
}

namespace syscalls
{
	void sceGeGetStack(AlContext &context)                        { V0 = sceGe_user::sceGeGetStack();                     }
	void sceGeEdramGetAddr(AlContext &context)                    { V0 = sceGe_user::sceGeEdramGetAddr();                 }
	void sceGeListUpdateStallAddr(AlContext &context)             { V0 = sceGe_user::sceGeListUpdateStallAddr(A0, A1);    }
	void sceGeGetCmd(AlContext &context)                          { V0 = sceGe_user::sceGeGetCmd();                       }
	void sceGeEdramSetAddrTranslation(AlContext &context)         { V0 = sceGe_user::sceGeEdramSetAddrTranslation();      }
	void sceGeBreak(AlContext &context)                           { V0 = sceGe_user::sceGeBreak();                        }
	void sceGeDrawSync(AlContext &context)                        { V0 = sceGe_user::sceGeDrawSync();                     }
    void sceGeListEnQueue(AlContext &context)                     { V0 = sceGe_user::sceGeListEnQueue(A0, A1, A2, A3);    }
    void sceGeSetCallback(AlContext &context)                     { V0 = sceGe_user::sceGeSetCallback();                  } 
	void sceGeListDeQueue(AlContext &context)                     { V0 = sceGe_user::sceGeListDeQueue();                  }
	void sceGeGetMtx(AlContext &context)                          { V0 = sceGe_user::sceGeGetMtx(A0, A1);                 }
	void sceGeContinue(AlContext &context)                        { V0 = sceGe_user::sceGeContinue();                     }
	void sceGeSaveContext(AlContext &context)                     { V0 = sceGe_user::sceGeSaveContext(A0);                }
    void sceGeRestoreContext(AlContext &context)                  { V0 = sceGe_user::sceGeRestoreContext(A0);             }
	void sceGeEdramGetSize(AlContext &context)                    { V0 = sceGe_user::sceGeEdramGetSize();                 }
	void sceGeListEnQueueHead(AlContext &context)                 { V0 = sceGe_user::sceGeListEnQueueHead();              }
	void sceGeUnsetCallback(AlContext &context)                   { V0 = sceGe_user::sceGeUnsetCallback();                }
	void sceGeListSync(AlContext &context)                        { V0 = sceGe_user::sceGeListSync();                     }
}
