#include "stdafx.h"
#include "../module_errorcodes.h"
#include "sceUtility.h"
#include "hle/types.h"
#include "log.h"
#include "../iofilemgr/IoFileMgrForUser.h"
#include "sceUtilitySave.h"
#include "sceUtilityOSK.h"
#include "sceUtilityMsgDialog.h"
#include "loaders/psf.h"
#ifdef _WIN32
#include <direct.h>
#endif
#include "qt4/settings.h"


namespace sceUtility
{
    static bool sceUtility_ready = false;
    QHash<int,QString> loadModules;
	void fillhash()
	{
		loadModules.insert(0x0100,"NET_COMMON"); 
		loadModules.insert(0x0101,"NET_ADHOC");
		loadModules.insert(0x0102,"NET_INET");
		loadModules.insert(0x0103,"NET_PARSE_URI");
		loadModules.insert(0x0104,"NET_PARSE_HTTP");
		loadModules.insert(0x0105,"NET_HTTP");
		loadModules.insert(0x0106,"NET_SSL");
		loadModules.insert(0x0200,"USB_PSPCM");
		loadModules.insert(0x0201,"USB_MIC");
		loadModules.insert(0x0202,"USB_CAM");
		loadModules.insert(0x0203,"USB_GPS");
		loadModules.insert(0x0300,"AV_AVCODEC");
		loadModules.insert(0x0301,"AV_SASCORE");
		loadModules.insert(0x0302,"AV_LIBATRAC3PLUS");
		loadModules.insert(0x0303,"AV_MPEG");
		loadModules.insert(0x0304,"AV_LIBMP3");
		loadModules.insert(0x0305,"AV_VAUDIO");
		loadModules.insert(0x0306,"AV_LIBAAC");
		loadModules.insert(0x0307,"AV_LIBG729");
	}
    bool Reboot()
    {
        ShutDown();
		fillhash();
        sceUtility_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceUtility_ready)
        {
            sceUtility_ready = false;
        }
        return true;
    }
    int sceUtilityGetSystemParamInt()//TODO implement it better!
    {
        int defaultValues[16] = 
        {
            0,
            0,
            0,
            0,//date notation
            0,//time notation
            0,//timezone offset in minutes
            0,//daylight savings
            1,//language (0=jap 1=eng)
            0,
        };
        Memory::memw(HLE_PARAM(1)) = defaultValues[HLE_PARAM(0)];
        return 0;
    }

    int sceUtilityGetSystemParamString(u32 a0, u32 a1, u32 a2)
    {
        u32 id       = a0;
        u32 str_addr = a1;
        u32 len      = a2;
        
        switch (id) 
        {
        case PSP_SYSTEMPARAM_ID_STRING_NICKNAME:
            ::strncpy(Memory::addr< char >(str_addr), "pcsp", len);
            return 0;

        default:
            errorf(sceUtility, "UNIMPLEMENTED sceUtilityGetSystemParamString id=%u", id);
            return -1;
        }
        return 0;
    }

	

	int sceUtility_F9E0008C()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_F9E0008C instruction");
		return 0;
	}
	int sceUtilityNetconfShutdownStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityNetconfShutdownStart instruction");
		return 0;
	}
	int sceUtilityUnloadAvModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityUnloadAvModule instruction");
		return 0;
	}
	int sceUtilityUnloadUsbModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityUnloadUsbModule instruction");
		return 0;
	}

	int sceUtilityHtmlViewerShutdownStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityHtmlViewerShutdownStart instruction");
		return 0;
	}
	int sceUtility_F3FBC572()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_F3FBC572 instruction");
		return 0;
	}

	int sceUtilityGameSharingShutdownStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityGameSharingShutdownStart instruction");
		return 0;
	}
	int sceUtility_EF3582B2()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_EF3582B2 instruction");
		return 0;
	}
	int sceUtility_ED0FAD38()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_ED0FAD38 instruction");
		return 0;
	}
	int sceUtility_ECE1D3E5()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_ECE1D3E5 instruction");
		return 0;
	}
	int sceUtility_E7B778D8()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_E7B778D8 instruction");
		return 0;
	}
	int sceUtilityUnloadModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityUnloadModule instruction");
		return 0;
	}
	int sceUtility_E19C97D6()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_E19C97D6 instruction");
		return 0;
	}
	int sceUtility_DDE5389D()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_DDE5389D instruction");
		return 0;
	}
	int sceUtility_DA97F1AA()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_DA97F1AA instruction");
		return 0;
	}
	int sceUtility_D852CDCE()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_D852CDCE instruction");
		return 0;
	}
	int sceUtility_D81957B7()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_D81957B7 instruction");
		return 0;
	}
    int sceUtility_D17A0573()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_D17A0573 instruction");
		return 0;
	}
	int sceUtilityHtmlViewerInitStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityHtmlViewerInitStart instruction");
		return 0;
	}
	int sceUtilityLoadAvModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityLoadAvModule instruction");
		return 0;
	}
	int sceUtilityGameSharingInitStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityGameSharingInitStart instruction");
		return 0;
	}
	int sceUtilityInstallGetStatus()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityInstallGetStatus instruction");
		return 0;
	}
	int sceUtilityHtmlViewerGetStatus()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityHtmlViewerGetStatus instruction");
		return 0;
	}
	int sceNetplayDialogShutdownStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceNetplayDialogShutdownStart instruction");
		return 0;
	}
	int sceUtility_B8592D5F()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_B8592D5F instruction");
		return 0;
	}
	int sceNetplayDialogGetStatus()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceNetplayDialogGetStatus instruction");
		return 0;
	}
	int sceUtility_B62A4061()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_B62A4061 instruction");
		return 0;
	}
	int sceUtility_B0FB7FF5()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_B0FB7FF5 instruction");
		return 0;
	}
	int sceUtility_AB083EA9()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_AB083EA9 instruction");
		return 0;
	}

    int sceUtility_A50E5B30()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_A50E5B30 instruction");
		return 0;
	}
	int sceUtility_A084E056()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_A084E056 instruction");
		return 0;
	}
	int sceUtilityInstallUpdate()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityInstallUpdate instruction");
		return 0;
	}
	int sceUtilityGameSharingGetStatus()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityGameSharingGetStatus instruction");
		return 0;
	}
	int sceUtility_943CBA46()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_943CBA46 instruction");
		return 0;
	}
	int sceUtilityNetconfUpdate()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityNetconfUpdate instruction");
		return 0;
	}
	int sceUtility_89317C8F()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_89317C8F instruction");
		return 0;
	}
	int sceUtility_88BC7406()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_88BC7406 instruction");
		return 0;
	}

	int sceUtility_86ABDB1B()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_86ABDB1B instruction");
		return 0;
	}
	int sceUtility_86A03A27()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_86A03A27 instruction");
		return 0;
	}
	int sceUtility_8326AB05()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_8326AB05 instruction");
		return 0;
	}
	int sceUtility_81C44706()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_81C44706 instruction");
		return 0;
	}
	int sceUtilityGameSharingUpdate()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityGameSharingUpdate instruction");
		return 0;
	}
	int sceUtility_70267ADF()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_70267ADF instruction");
		return 0;
	}
	int sceUtility_6F56F9CF()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_6F56F9CF instruction");
		return 0;
	}
	int sceUtilityUnloadNetModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityUnloadNetModule instruction");
		return 0;
	}
	int sceUtilityNetconfGetStatus()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityNetconfGetStatus instruction");
		return 0;
	}
	int sceUtilityInstallShutdownStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityInstallShutdownStart instruction");
		return 0;
	}
	int sceUtilityCheckNetParam()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityCheckNetParam instruction");
		return 0;
	}
	int sceUtility_54A5C62F()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_54A5C62F instruction");
		return 0;
	}
	int sceUtilityGetNetParamLatestID()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityGetNetParamLatestID instruction");
		return 0;
	}
	int sceUtilityNetconfInitStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityNetconfInitStart instruction");
		return 0;
	}

	int sceUtility_4B0A8FE5()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_4B0A8FE5 instruction");
		return 0;
	}
	int sceUtility_4A833BA4()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_4A833BA4 instruction");
		return 0;
	}
	int sceUtilitySetSystemParamInt()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilitySetSystemParamInt instruction");
		return 0;
	}
	int sceUtilityGetNetParam()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityGetNetParam instruction");
		return 0;
	}
	int sceUtility_42071A83()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_42071A83 instruction");
		return 0;
	}
	int sceUtilitySetSystemParamString()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilitySetSystemParamString instruction");
		return 0;
	}
	int sceNetplayDialogUpdate()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceNetplayDialogUpdate instruction");
		return 0;
	}

	int sceNetplayDialogInitStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceNetplayDialogInitStart instruction");
		return 0;
	}
	int sceUtility_3AAD51DC()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_3AAD51DC instruction");
		return 0;
	}
	int sceUtility_2B96173B()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_2B96173B instruction");
		return 0;
	}
	int sceUtilityLoadModule(u32 a0)
	{
		//TODO implement me
		u32 module = a0;
		if(loadModules.contains(a0))
		{
          errorf(sceUtility,"UNIMPLEMENTED sceUtilityLoadModule instruction module = %s",loadModules.value(a0).toStdString().c_str());
		}
		else
		{
           errorf(sceUtility,"UNIMPLEMENTED sceUtilityLoadModule instruction unknown module 0x%x",module);
		}
		
		return 0;
	}
	int sceUtility_2995D020()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_2995D020 instruction");
		return 0;
	}
	int sceUtility_28D35634()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_28D35634 instruction");
		return 0;
	}
	int sceUtility_16D02AF0()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_16D02AF0 instruction");
		return 0;
	}
	int sceUtility_16A1A8D8()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_16A1A8D8 instruction");
		return 0;
	}
	int sceUtilityLoadNetModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityLoadNetModule instruction");
		return 0;
	}
	int sceUtility_149A7895()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_149A7895 instruction");
		return 0;
	}
	int sceUtility_147F7C85()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_147F7C85 instruction");
		return 0;
	}
	int sceUtilityInstallInitStart()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityInstallInitStart instruction");
		return 0;
	}
	int sceUtility_0F3EEAAC()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_0F3EEAAC instruction");
		return 0;
	}
	int sceUtilityLoadUsbModule()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityLoadUsbModule instruction");
		return 0;
	}
	int sceUtility_06A48659()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_06A48659 instruction");
		return 0;
	}
	int sceUtilityHtmlViewerUpdate()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtilityHtmlViewerUpdate instruction");
		return 0;
	}
	int sceUtility_0251B134()
	{
		//TODO implement me
		errorf(sceUtility,"UNIMPLEMENTED sceUtility_0251B134 instruction");
		return 0;
	}
}
namespace syscalls
{
    void sceUtility_F9E0008C(AlContext &context){ V0 = sceUtility::sceUtility_F9E0008C();};
	void sceUtilityNetconfShutdownStart(AlContext &context){ V0 = sceUtility::sceUtilityNetconfShutdownStart();};
	void sceUtilityUnloadAvModule(AlContext &context){ V0 = sceUtility::sceUtilityUnloadAvModule();};
	void sceUtilityUnloadUsbModule(AlContext &context){ V0 = sceUtility::sceUtilityUnloadUsbModule();};
	void sceUtilityHtmlViewerShutdownStart(AlContext &context){ V0 = sceUtility::sceUtilityHtmlViewerShutdownStart();};
	void sceUtility_F3FBC572(AlContext &context){ V0 = sceUtility::sceUtility_F3FBC572();};
	void sceUtilityGameSharingShutdownStart(AlContext &context){ V0 = sceUtility::sceUtilityGameSharingShutdownStart();};
	void sceUtility_EF3582B2(AlContext &context){ V0 = sceUtility::sceUtility_EF3582B2();};
	void sceUtility_ED0FAD38(AlContext &context){ V0 = sceUtility::sceUtility_ED0FAD38();};
	void sceUtility_ECE1D3E5(AlContext &context){ V0 = sceUtility::sceUtility_ECE1D3E5();};
	void sceUtility_E7B778D8(AlContext &context){ V0 = sceUtility::sceUtility_E7B778D8();};
	void sceUtilityUnloadModule(AlContext &context){ V0 = sceUtility::sceUtilityUnloadModule();};
	void sceUtility_E19C97D6(AlContext &context){ V0 = sceUtility::sceUtility_E19C97D6();};
	void sceUtility_DDE5389D(AlContext &context){ V0 = sceUtility::sceUtility_DDE5389D();};
	void sceUtility_DA97F1AA(AlContext &context){ V0 = sceUtility::sceUtility_DA97F1AA();};
	void sceUtility_D852CDCE(AlContext &context){ V0 = sceUtility::sceUtility_D852CDCE();};
	void sceUtility_D81957B7(AlContext &context){ V0 = sceUtility::sceUtility_D81957B7();};
	void sceUtility_D17A0573(AlContext &context){ V0 = sceUtility::sceUtility_D17A0573();};
	void sceUtilityHtmlViewerInitStart(AlContext &context){ V0 = sceUtility::sceUtilityHtmlViewerInitStart();};
	void sceUtilityLoadAvModule(AlContext &context){ V0 = sceUtility::sceUtilityLoadAvModule();};
	void sceUtilityGameSharingInitStart(AlContext &context){ V0 = sceUtility::sceUtilityGameSharingInitStart();};
	void sceUtilityInstallGetStatus(AlContext &context){ V0 = sceUtility::sceUtilityInstallGetStatus();};
	void sceUtilityHtmlViewerGetStatus(AlContext &context){ V0 = sceUtility::sceUtilityHtmlViewerGetStatus();};
	void sceNetplayDialogShutdownStart(AlContext &context){ V0 = sceUtility::sceNetplayDialogShutdownStart();};
	void sceUtility_B8592D5F(AlContext &context){ V0 = sceUtility::sceUtility_B8592D5F();};
	void sceNetplayDialogGetStatus(AlContext &context){ V0 = sceUtility::sceNetplayDialogGetStatus();};
	void sceUtility_B62A4061(AlContext &context){ V0 = sceUtility::sceUtility_B62A4061();};
	void sceUtility_B0FB7FF5(AlContext &context){ V0 = sceUtility::sceUtility_B0FB7FF5();};
	void sceUtility_AB083EA9(AlContext &context){ V0 = sceUtility::sceUtility_AB083EA9();};
	void sceUtilityGetSystemParamInt(AlContext &context){ V0 = sceUtility::sceUtilityGetSystemParamInt();};
	void sceUtility_A50E5B30(AlContext &context){ V0 = sceUtility::sceUtility_A50E5B30();};
	void sceUtility_A084E056(AlContext &context){ V0 = sceUtility::sceUtility_A084E056();};
	void sceUtilityInstallUpdate(AlContext &context){ V0 = sceUtility::sceUtilityInstallUpdate();};
	void sceUtilityGameSharingGetStatus(AlContext &context){ V0 = sceUtility::sceUtilityGameSharingGetStatus();};
	void sceUtility_943CBA46(AlContext &context){ V0 = sceUtility::sceUtility_943CBA46();};
	void sceUtilityNetconfUpdate(AlContext &context){ V0 = sceUtility::sceUtilityNetconfUpdate();};
	void sceUtility_89317C8F(AlContext &context){ V0 = sceUtility::sceUtility_89317C8F();};
	void sceUtility_88BC7406(AlContext &context){ V0 = sceUtility::sceUtility_88BC7406();};
	void sceUtility_86ABDB1B(AlContext &context){ V0 = sceUtility::sceUtility_86ABDB1B();};
	void sceUtility_86A03A27(AlContext &context){ V0 = sceUtility::sceUtility_86A03A27();};
	void sceUtility_8326AB05(AlContext &context){ V0 = sceUtility::sceUtility_8326AB05();};
	void sceUtility_81C44706(AlContext &context){ V0 = sceUtility::sceUtility_81C44706();};
	void sceUtilityGameSharingUpdate(AlContext &context){ V0 = sceUtility::sceUtilityGameSharingUpdate();};
	void sceUtility_70267ADF(AlContext &context){ V0 = sceUtility::sceUtility_70267ADF();};
	void sceUtility_6F56F9CF(AlContext &context){ V0 = sceUtility::sceUtility_6F56F9CF();};
	void sceUtilityUnloadNetModule(AlContext &context){ V0 = sceUtility::sceUtilityUnloadNetModule();};
	void sceUtilityNetconfGetStatus(AlContext &context){ V0 = sceUtility::sceUtilityNetconfGetStatus();};
	void sceUtilityInstallShutdownStart(AlContext &context){ V0 = sceUtility::sceUtilityInstallShutdownStart();};
	void sceUtilityCheckNetParam(AlContext &context){ V0 = sceUtility::sceUtilityCheckNetParam();};
	void sceUtility_54A5C62F(AlContext &context){ V0 = sceUtility::sceUtility_54A5C62F();};
	void sceUtilityGetNetParamLatestID(AlContext &context){ V0 = sceUtility::sceUtilityGetNetParamLatestID();};
	void sceUtilityNetconfInitStart(AlContext &context){ V0 = sceUtility::sceUtilityNetconfInitStart();};
	void sceUtility_4B0A8FE5(AlContext &context){ V0 = sceUtility::sceUtility_4B0A8FE5();};
	void sceUtility_4A833BA4(AlContext &context){ V0 = sceUtility::sceUtility_4A833BA4();};
	void sceUtilitySetSystemParamInt(AlContext &context){ V0 = sceUtility::sceUtilitySetSystemParamInt();};
	void sceUtilityGetNetParam(AlContext &context){ V0 = sceUtility::sceUtilityGetNetParam();};
	void sceUtility_42071A83(AlContext &context){ V0 = sceUtility::sceUtility_42071A83();};
	void sceUtilitySetSystemParamString(AlContext &context){ V0 = sceUtility::sceUtilitySetSystemParamString();};
	void sceNetplayDialogUpdate(AlContext &context){ V0 = sceUtility::sceNetplayDialogUpdate();};
	void sceNetplayDialogInitStart(AlContext &context){ V0 = sceUtility::sceNetplayDialogInitStart();};
	void sceUtility_3AAD51DC(AlContext &context){ V0 = sceUtility::sceUtility_3AAD51DC();};
    void sceUtilityGetSystemParamString(AlContext &context){ V0 = sceUtility::sceUtilityGetSystemParamString(A0,A1,A2);};
	void sceUtility_2B96173B(AlContext &context){ V0 = sceUtility::sceUtility_2B96173B();};
	void sceUtilityLoadModule(AlContext &context){ V0 = sceUtility::sceUtilityLoadModule(A0);};
	void sceUtility_2995D020(AlContext &context){ V0 = sceUtility::sceUtility_2995D020();};
	void sceUtility_28D35634(AlContext &context){ V0 = sceUtility::sceUtility_28D35634();};
	void sceUtility_16D02AF0(AlContext &context){ V0 = sceUtility::sceUtility_16D02AF0();};
	void sceUtility_16A1A8D8(AlContext &context){ V0 = sceUtility::sceUtility_16A1A8D8();};
	void sceUtilityLoadNetModule(AlContext &context){ V0 = sceUtility::sceUtilityLoadNetModule();};
	void sceUtility_149A7895(AlContext &context){ V0 = sceUtility::sceUtility_149A7895();};
	void sceUtility_147F7C85(AlContext &context){ V0 = sceUtility::sceUtility_147F7C85();};
	void sceUtilityInstallInitStart(AlContext &context){ V0 = sceUtility::sceUtilityInstallInitStart();};
	void sceUtility_0F3EEAAC(AlContext &context){ V0 = sceUtility::sceUtility_0F3EEAAC();};
	void sceUtilityLoadUsbModule(AlContext &context){ V0 = sceUtility::sceUtilityLoadUsbModule();};
	void sceUtility_06A48659(AlContext &context){ V0 = sceUtility::sceUtility_06A48659();};
	void sceUtilityHtmlViewerUpdate(AlContext &context){ V0 = sceUtility::sceUtilityHtmlViewerUpdate();};
	void sceUtility_0251B134(AlContext &context){ V0 = sceUtility::sceUtility_0251B134();};

	//OSK functions in sceUtilityOSK.cpp
	void sceUtilityOskInitStart(AlContext &context)    { V0 = sceUtilityOSK::sceUtilityOskInitStart(A0);};
    void sceUtilityOskGetStatus(AlContext &context)    { V0 = sceUtilityOSK::sceUtilityOskGetStatus();};
	void sceUtilityOskUpdate(AlContext &context)       { V0 = sceUtilityOSK::sceUtilityOskUpdate();};
    void sceUtilityOskShutdownStart(AlContext &context){ V0 = sceUtilityOSK::sceUtilityOskShutdownStart();};
    //MsgDialog functions in sceUtilityMsgDialog.cpp
	void sceUtilityMsgDialogInitStart(AlContext &context)    { V0 = sceUtilityMsgDialog::sceUtilityMsgDialogInitStart(A0);};
	void sceUtilityMsgDialogGetStatus(AlContext &context)    { V0 = sceUtilityMsgDialog::sceUtilityMsgDialogGetStatus();};
	void sceUtilityMsgDialogUpdate(AlContext &context)       { V0 = sceUtilityMsgDialog::sceUtilityMsgDialogUpdate();};
    void sceUtilityMsgDialogShutdownStart(AlContext &context){ V0 = sceUtilityMsgDialog::sceUtilityMsgDialogShutdownStart();};
    void sceUtilityMsgDialogAbort(AlContext &context)        { V0 = sceUtilityMsgDialog::sceUtilityMsgDialogAbort();};
    //Save functions in sceUtilitySave.cpp
    void sceUtilitySavedataUpdate(AlContext &context)        { V0 = sceUtilitySave::sceUtilitySavedataUpdate();};
    void sceUtilitySavedataShutdownStart(AlContext &context) { V0 = sceUtilitySave::sceUtilitySavedataShutdownStart();};
    void sceUtilitySavedataGetStatus(AlContext &context)     { V0 = sceUtilitySave::sceUtilitySavedataGetStatus();};
    void sceUtilitySavedataInitStart(AlContext &context)     { V0 = sceUtilitySave::sceUtilitySavedataInitStart(A0);};

}
