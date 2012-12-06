#ifndef sceUtility_h__
#define sceUtility_h__



#define SCE_UTILITY_STATUS_NONE 		0
#define SCE_UTILITY_STATUS_INITIALIZE	1
#define SCE_UTILITY_STATUS_RUNNING 		2
#define SCE_UTILITY_STATUS_FINISHED 	3
#define SCE_UTILITY_STATUS_SHUTDOWN 	4

#define SCE_UTILITY_RESULT_OK		    0
#define SCE_UTILITY_RESULT_CANCELED  	1
#define SCE_UTILITY_RESULT_ABORTED 		2


#define PSP_SYSTEMPARAM_ID_STRING_NICKNAME  1

	typedef struct SceUtilityParamBase
	{
       unsigned int size;
	   int message_lang;
	   int ctrl_assign;
	   int main_thread_priority;
	   int sub_thread_priority;
	   int font_thread_priority;
	   int sound_thread_priority;
	   int result;
	   int reserved1;
	   int reserved2;
	   int reserved3;
	   int reserved4;
    } SceUtilityParamBase;

	struct UtilityState
	{
		int status;
	};

namespace sceUtility
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceUtility_F9E0008C(); 
	extern int sceUtilityNetconfShutdownStart(); 
	extern int sceUtilityUnloadAvModule(); 
	extern int sceUtilityUnloadUsbModule(); 
	extern int sceUtilityHtmlViewerShutdownStart(); 
	extern int sceUtility_F3FBC572(); 
	extern int sceUtilityGameSharingShutdownStart(); 
	extern int sceUtility_EF3582B2(); 
	extern int sceUtility_ED0FAD38(); 
	extern int sceUtility_ECE1D3E5(); 
	extern int sceUtility_E7B778D8(); 
	extern int sceUtilityUnloadModule(); 
	extern int sceUtility_E19C97D6(); 
	extern int sceUtility_DDE5389D(); 
	extern int sceUtility_DA97F1AA(); 
	extern int sceUtility_D852CDCE(); 
	extern int sceUtility_D81957B7(); 
	extern int sceUtility_D17A0573(); 
	extern int sceUtilityHtmlViewerInitStart(); 
	extern int sceUtilityLoadAvModule(); 
	extern int sceUtilityGameSharingInitStart(); 
	extern int sceUtilityInstallGetStatus(); 
	extern int sceUtilityHtmlViewerGetStatus(); 
	extern int sceNetplayDialogShutdownStart(); 
	extern int sceUtility_B8592D5F(); 
	extern int sceNetplayDialogGetStatus(); 
	extern int sceUtility_B62A4061(); 
	extern int sceUtility_B0FB7FF5(); 
	extern int sceUtility_AB083EA9(); 
	extern int sceUtilityGetSystemParamInt(); 
	extern int sceUtility_A50E5B30(); 
	extern int sceUtility_A084E056(); 
	extern int sceUtilityInstallUpdate(); 
	extern int sceUtilityGameSharingGetStatus(); 
	extern int sceUtility_943CBA46(); 
	extern int sceUtilityNetconfUpdate(); 
	extern int sceUtility_89317C8F(); 
	extern int sceUtility_88BC7406(); 
	extern int sceUtility_86ABDB1B(); 
	extern int sceUtility_86A03A27(); 
	extern int sceUtility_8326AB05(); 
	extern int sceUtility_81C44706(); 
	extern int sceUtilityGameSharingUpdate(); 
	extern int sceUtility_70267ADF(); 
	extern int sceUtility_6F56F9CF(); 
	extern int sceUtilityUnloadNetModule(); 
	extern int sceUtilityNetconfGetStatus(); 
	extern int sceUtilityInstallShutdownStart(); 
	extern int sceUtilityCheckNetParam(); 
	extern int sceUtility_54A5C62F(); 
	extern int sceUtilityGetNetParamLatestID(); 
	extern int sceUtilityNetconfInitStart(); 
	extern int sceUtility_4B0A8FE5(); 
	extern int sceUtility_4A833BA4(); 
	extern int sceUtilitySetSystemParamInt(); 
	extern int sceUtilityGetNetParam(); 
	extern int sceUtility_42071A83(); 
	extern int sceUtilitySetSystemParamString(); 
	extern int sceNetplayDialogUpdate(); 
	extern int sceNetplayDialogInitStart(); 
	extern int sceUtility_3AAD51DC(); 
	extern int sceUtilityGetSystemParamString(); 
	extern int sceUtility_2B96173B();  
	extern int sceUtilityLoadModule(); 
	extern int sceUtility_2995D020(); 
	extern int sceUtility_28D35634(); 
	extern int sceUtility_16D02AF0(); 
	extern int sceUtility_16A1A8D8(); 
	extern int sceUtilityLoadNetModule(); 
	extern int sceUtility_149A7895(); 
	extern int sceUtility_147F7C85(); 
	extern int sceUtilityInstallInitStart(); 
	extern int sceUtility_0F3EEAAC(); 
	extern int sceUtilityLoadUsbModule(); 
	extern int sceUtility_06A48659(); 
	extern int sceUtilityHtmlViewerUpdate(); 
	extern int sceUtility_0251B134(); 

}
#endif // sceUtility_h__
