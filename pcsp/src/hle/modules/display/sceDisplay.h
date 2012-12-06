#ifndef sceDisplay_h__
#define sceDisplay_h__

namespace sceDisplay
{
    extern bool Reboot();
    extern bool ShutDown();

	extern void Initialize();

    extern int sceDisplaySetMode(u32 a0, u32 a1, u32 a3); 
    extern int sceDisplayGetMode(u32 a0, u32 a1, u32 a3); 
    extern int sceDisplaySetHoldMode(u32 a0); 
    extern int sceDisplaySetResumeMode(); 
    extern int sceDisplayGetResumeMode(); 

    extern int sceDisplaySetFrameBuf(u32 a0, u32 a1, u32 a3); 
    extern int sceDisplayGetFrameBuf(); 
	extern f32 sceDisplayGetFramePerSec(); 
	extern int sceDisplayIsForeground(); 

    extern int sceDisplayGetVcount(); 
    extern int sceDisplayIsVsync(); 
    extern int sceDisplayIsVblank(); 
    extern int sceDisplayWaitVblank(); 
    extern int sceDisplayWaitVblankCB(); 
	extern int sceDisplayWaitVblankStart(); 
    extern int sceDisplayWaitVblankStartCB(); 
	extern int sceDisplayGetVblankRest(); 
    extern int sceDisplay_77ED8B3A(); 
	extern int sceDisplay_40F1469C(); 

    extern int sceDisplayGetCurrentHcount(); 
    extern int sceDisplayGetAccumulatedHcount(); 
    extern int sceDisplayAdjustAccumulatedHcount(); 

    extern int sceDisplayGetBrightness(); 

}
#endif // sceDisplay_h__
