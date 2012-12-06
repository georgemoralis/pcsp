#include "stdafx.h"
#include "sceImpose.h"
#include "hle/types.h"
#include "log.h"

namespace sceImpose
{
    static bool sceImpose_ready = false;

    bool Reboot()
    {
        ShutDown();

        languageMode_language = PSP_LANGUAGE_ENGLISH;
        languageMode_button   = PSP_CONFIRM_BUTTON_CROSS;

        sceImpose_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceImpose_ready)
        {
            sceImpose_ready = false;
        }
        return true;
    }

    int languageMode_language;
    int languageMode_button;

    int sceImpose_FF1A2F07()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImpose_FF1A2F07 instruction");
		return 0;
	}
	int sceImpose_FCD44963()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImpose_FCD44963 instruction");
		return 0;
	}
	int sceImposeGetUMDPopup()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeGetUMDPopup instruction");
		return 0;
	}
	int sceImpose_BB3F5DEC()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImpose_BB3F5DEC instruction");
		return 0;
	}
	int sceImpose_A9884B00()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImpose_A9884B00 instruction");
		return 0;
	}
	int sceImpose_9BA61B49()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImpose_9BA61B49 instruction");
		return 0;
	}
	int sceImposeSetBacklightOffTime()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeSetBacklightOffTime instruction");
		return 0;
	}
	int sceImposeGetBacklightOffTime()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeGetBacklightOffTime instruction");
		return 0;
	}
	int sceImposeGetBatteryIconStatus(u32 a0,u32 a1)
	{
		u32 *addrCharging   = Memory::addr< u32 >(a0);
		u32 *addrIconStatus = Memory::addr< u32 >(a1);    
		*addrCharging = 0;//baterry isn't charging
		*addrIconStatus=3;//full icon
		return 0;

	}
	int sceImposeSetUMDPopup()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeSetUMDPopup instruction");
		return 0;
	}
	int sceImposeSetHomePopup()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeSetHomePopup instruction");
		return 0;
	}
	int sceImposeHomeButton()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeHomeButton instruction");
		return 0;
	}
	int sceImposeSetLanguageMode(u32 a0,u32 a1)
	{
		languageMode_language = a0;
		languageMode_button=a1;
		return 0;
	}
	int sceImposeGetLanguageMode(u32 a0,u32 a1)
	{
		int *lang_addr = Memory::addr< int >(a0);
	    int *button_addr = Memory::addr< int >(a1);
		*lang_addr = languageMode_language;
		*button_addr = languageMode_button;
		return 0;
	}
	int sceImposeGetHomePopup()
	{
		//TODO implement me
		errorf(sceImpose,"UNIMPLEMENTED sceImposeGetHomePopup instruction");
		return 0;
	}
}
namespace syscalls
{
	void sceImpose_FF1A2F07(AlContext &context){ V0 = sceImpose::sceImpose_FF1A2F07();};
	void sceImpose_FCD44963(AlContext &context){ V0 = sceImpose::sceImpose_FCD44963();};
	void sceImposeGetUMDPopup(AlContext &context){ V0 = sceImpose::sceImposeGetUMDPopup();};
	void sceImpose_BB3F5DEC(AlContext &context){ V0 = sceImpose::sceImpose_BB3F5DEC();};
	void sceImpose_A9884B00(AlContext &context){ V0 = sceImpose::sceImpose_A9884B00();};
	void sceImpose_9BA61B49(AlContext &context){ V0 = sceImpose::sceImpose_9BA61B49();};
	void sceImposeSetBacklightOffTime(AlContext &context){ V0 = sceImpose::sceImposeSetBacklightOffTime();};
	void sceImposeGetBacklightOffTime(AlContext &context){ V0 = sceImpose::sceImposeGetBacklightOffTime();};
	void sceImposeGetBatteryIconStatus(AlContext &context)   { V0 = sceImpose::sceImposeGetBatteryIconStatus(A0,A1);};
	void sceImposeSetUMDPopup(AlContext &context){ V0 = sceImpose::sceImposeSetUMDPopup();};
	void sceImposeSetHomePopup(AlContext &context){ V0 = sceImpose::sceImposeSetHomePopup();};
	void sceImposeHomeButton(AlContext &context){ V0 = sceImpose::sceImposeHomeButton();};
	void sceImposeSetLanguageMode(AlContext &context)        { V0 = sceImpose::sceImposeSetLanguageMode(A0,A1);};
	void sceImposeGetLanguageMode(AlContext &context)        { V0 = sceImpose::sceImposeGetLanguageMode(A0,A1);};
	void sceImposeGetHomePopup(AlContext &context){ V0 = sceImpose::sceImposeGetHomePopup();};
}
