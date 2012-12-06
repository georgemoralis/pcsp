#ifndef sceImpose_h__
#define sceImpose_h__

#define PSP_LANGUAGE_JAPANESE              0
#define PSP_LANGUAGE_ENGLISH               1
#define PSP_LANGUAGE_FRENCH                2
#define PSP_LANGUAGE_SPANISH               3
#define PSP_LANGUAGE_GERMAN                4
#define PSP_LANGUAGE_ITALIAN               5
#define PSP_LANGUAGE_DUTCH                 6
#define PSP_LANGUAGE_PORTUGUESE            7
#define PSP_LANGUAGE_RUSSIAN               8
#define PSP_LANGUAGE_KOREAN                9
#define PSP_LANGUAGE_TRADITIONAL_CHINESE  10
#define PSP_LANGUAGE_SIMPLIFIED_CHINESE   11 


#define PSP_CONFIRM_BUTTON_CIRCLE  0
#define PSP_CONFIRM_BUTTON_CROSS   1

namespace sceImpose
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceImpose_FF1A2F07(); 
	extern int sceImpose_FCD44963(); 
	extern int sceImposeGetUMDPopup(); 
	extern int sceImpose_BB3F5DEC(); 
	extern int sceImpose_A9884B00(); 
	extern int sceImpose_9BA61B49(); 
	extern int sceImposeSetBacklightOffTime(); 
	extern int sceImposeGetBacklightOffTime(); 
	extern int sceImposeGetBatteryIconStatus(); 
	extern int sceImposeSetUMDPopup(); 
	extern int sceImposeSetHomePopup(); 
	extern int sceImposeHomeButton(); 
	extern int sceImposeSetLanguageMode(); 
	extern int sceImposeGetLanguageMode(); 
	extern int sceImposeGetHomePopup(); 

	//default values 
	//TODO them in GUI.
    extern int languageMode_language;
    extern int languageMode_button;
}

#endif // sceImpose_h__
