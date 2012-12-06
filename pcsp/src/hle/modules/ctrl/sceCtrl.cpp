#include "stdafx.h"
#include "sceCtrl.h"
#include "hle/types.h"
#include "log.h"
#include "qt4/qinputsystem.h"

namespace sceCtrl
{
    static bool sceCtrl_ready = false;

    bool Reboot()
    {
        ShutDown();
        sceCtrl_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceCtrl_ready)
        {
            sceCtrl_ready = false;
        }
        return true;
    }

    // predefines
	bool sceCtrlInit();

	bool ctrlInited			= sceCtrlInit();
	bool samplingmode		= SCE_CTRL_MODE_DIGITALONLY;
	u32	 samplingcycle		= 0; 
	u32  HoldThreshold		= 0;
	u32  UnHoldThreshold	= 0;

	bool sceCtrlInit()
	{	
		return true;
	}

	int hleCtrlPeekBuffer(SceCtrlData &data, u32 maxbufs, int mode)
	{
        (void)maxbufs;

		if (ctrlInited)
		{
			static int frame = 0;
			data.TimeStamp = frame++;

			InputController *ctr = theInputSystem->GetController();

			unsigned int buttons = 0;

			if (ctr)
			{
                ctr->Update(buttons, data.Lx, data.Ly, samplingmode);
			}

			data.Buttons = (mode & 1) ? ~buttons : buttons; 

			// there is no lag when emulating so always 1
			return 1;
		}

		return 0;
	}

	//-------------------------------------------------------
	// Arguments:(unsigned int *puiMode)
	// Return: 0 on success
	//-------------------------------------------------------
	int sceCtrlGetSamplingMode(u32 a0)
	{
		u32& retval		=	Memory::mem< u32 >(a0);
		retval			=	samplingmode;
		return 0;
	}
	//-------------------------------------------------------
	// Arguments:(SceCtrlData *pData,int nBufs)
	// Return: number of bufs
	//-------------------------------------------------------
	int sceCtrlPeekBufferNegative(u32 a0, u32 a1)
	{
		return hleCtrlPeekBuffer(Memory::mem< SceCtrlData >(a0), a1, 1);
	}

	int sceCtrlPeekLatch()
	{
		//TODO implement me
		errorf(sceCtrl,"UNIMPLEMENTED sceCtrlPeekLatch instruction");
		return 0;
	}

	int sceCtrl_AF5960F3()
	{
		//TODO implement me
		errorf(sceCtrl,"UNIMPLEMENTED sceCtrl_AF5960F3 instruction");
		return 0;
	}

	//-------------------------------------------------------
	// Arguments:(int iUnHoldThreshold,int iHoldThreshold)
	// Return: 0 on success (negative if failure)
	//-------------------------------------------------------
	int sceCtrlSetIdleCancelThreshold(u32 a0, u32 a1)
	{
		UnHoldThreshold	= a0;
		HoldThreshold	= a1;
		return 0;
	}

	int sceCtrlClearRapidFire()
	{
		//TODO implement me
		errorf(sceCtrl,"UNIMPLEMENTED sceCtrlClearRapidFire instruction");
		return 0;
	}

	//-------------------------------------------------------
	// Arguments:(unsigned int uiCycle)
	// Return: samplingcycle prior to modification
	//-------------------------------------------------------
	int sceCtrlSetSamplingCycle(u32 a0)
	{
		u32 retval		= samplingcycle;
		samplingcycle	= a0;
		return retval;
	}

	//-------------------------------------------------------
	// Arguments:(int *piUnHoldThreshold,int *piHoldThreshold)
	// Return: 0 on success (negative if failure)
	//-------------------------------------------------------
	int sceCtrlGetIdleCancelThreshold(u32 a0,u32 a1)
	{
		u32& ret0	= Memory::mem< u32 >(a0);
		u32& ret1	= Memory::mem< u32 >(a1);
		ret0		= UnHoldThreshold;
		ret1		= HoldThreshold;
		return 0;
	}

	int sceCtrlSetRapidFire()
	{
		//TODO implement me
		errorf(sceCtrl,"UNIMPLEMENTED sceCtrlSetRapidFire instruction");
		return 0;
	}

	//-------------------------------------------------------
	// Arguments:(SceCtrlData *pData,int nBufs)
	// Return: number of bufs
	//-------------------------------------------------------
	int sceCtrlReadBufferNegative(u32 a0, u32 a1)
	{
		// This is not a hack. 
		// Because we don't have a difference between blocking state and non-blocking state in emulation.
		return hleCtrlPeekBuffer(Memory::mem< SceCtrlData >(a0), a1, 3);
	}

	//-------------------------------------------------------
	// Arguments:(SceCtrlData *pData,int nBufs)
	// Return: number of bufs
	//-------------------------------------------------------
	int sceCtrlPeekBufferPositive(u32 a0, u32 a1)
	{
		return hleCtrlPeekBuffer(Memory::mem< SceCtrlData >(a0), a1, 0);
	}

	int sceCtrl_348D99D4()
	{
		//TODO implement me
		errorf(sceCtrl,"UNIMPLEMENTED sceCtrl_348D99D4 instruction");
		return 0;
	}

	//-------------------------------------------------------
	// Arguments:(SceCtrlData *pData,int nBufs)
	// Return: number of bufs
	//-------------------------------------------------------
	int sceCtrlReadBufferPositive(u32 a0, u32 a1)
	{
		// This is not a hack. 
		// Because we don't have a difference between blocking state and non-blocking state in emulation.
		return hleCtrlPeekBuffer(Memory::mem< SceCtrlData >(a0), a1, 2);
	}

	//-------------------------------------------------------
	// Arguments:(unsigned int uiMode)
	// Return: samplingmode prior to modification
	//-------------------------------------------------------
	int sceCtrlSetSamplingMode(u32 a0)
	{
		u32 result = 0;

		if (ctrlInited)
		{
			result = samplingmode;

            samplingmode = a0 ? SCE_CTRL_MODE_DIGITALANALOG : SCE_CTRL_MODE_DIGITALONLY;
		}

		return result;
	}

	int sceCtrlReadLatch()
	{
		//TODO implement me
		errorf(sceCtrl,"UNIMPLEMENTED sceCtrlReadLatch instruction");
		return 0;
	}

	//-------------------------------------------------------
	// Arguments:(unsigned int *puiCycle)
	// Return: 0 on success
	//-------------------------------------------------------
	int sceCtrlGetSamplingCycle(u32 a0)
	{
		u32& retval		=	Memory::mem< u32 >(a0);
		retval			=	samplingcycle;
		return 0;
	}
}

namespace syscalls
{
	void sceCtrlGetSamplingCycle(AlContext &context)				{ V0 = sceCtrl::sceCtrlGetSamplingCycle(A0);            }
	void sceCtrlSetSamplingCycle(AlContext &context)				{ V0 = sceCtrl::sceCtrlSetSamplingCycle(A0);            }
	void sceCtrlGetSamplingMode(AlContext &context)				{ V0 = sceCtrl::sceCtrlGetSamplingMode(A0);             }
	void sceCtrlSetSamplingMode(AlContext &context)				{ V0 = sceCtrl::sceCtrlSetSamplingMode(A0);             }
	void sceCtrlPeekBufferPositive(AlContext &context) 			{ V0 = sceCtrl::sceCtrlPeekBufferPositive(A0, A1);      }
	void sceCtrlReadBufferPositive(AlContext &context) 			{ V0 = sceCtrl::sceCtrlReadBufferPositive(A0, A1);      }
	void sceCtrlPeekBufferNegative(AlContext &context) 			{ V0 = sceCtrl::sceCtrlPeekBufferNegative(A0, A1);      }
	void sceCtrlReadBufferNegative(AlContext &context) 			{ V0 = sceCtrl::sceCtrlReadBufferNegative(A0, A1);      }
	void sceCtrlPeekLatch(AlContext &context)                     { V0 = sceCtrl::sceCtrlPeekLatch();                     }
	void sceCtrl_AF5960F3(AlContext &context)                     { V0 = sceCtrl::sceCtrl_AF5960F3();                     }
	void sceCtrlSetIdleCancelThreshold(AlContext &context) 		{ V0 = sceCtrl::sceCtrlSetIdleCancelThreshold(A0, A1);  }
	void sceCtrlGetIdleCancelThreshold(AlContext &context) 		{ V0 = sceCtrl::sceCtrlGetIdleCancelThreshold(A0 ,A1);  }
	void sceCtrlClearRapidFire(AlContext &context)                { V0 = sceCtrl::sceCtrlClearRapidFire();                }
	void sceCtrlSetRapidFire(AlContext &context)                  { V0 = sceCtrl::sceCtrlSetRapidFire();                  }
	void sceCtrl_348D99D4(AlContext &context)                     { V0 = sceCtrl::sceCtrl_348D99D4();                     }
	void sceCtrlReadLatch(AlContext &context)                     { V0 = sceCtrl::sceCtrlReadLatch();                     }

}
