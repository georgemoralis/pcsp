#ifndef sceGe_user_h__
#define sceGe_user_h__

namespace sceGe_user
{
    extern bool Reboot();
    extern bool ShutDown();

	extern const u32 START_VRAM;
	extern const u32 END_VRAM;
	extern const u32 SIZE_VRAM;

	extern bool geBufChanged;

	#define SCE_GE_LIST_COMPLETED		0
	#define SCE_GE_LIST_QUEUED			1
	#define SCE_GE_LIST_DRAWING			2
	#define SCE_GE_LIST_STALLING		3
	#define SCE_GE_LIST_PAUSED			4

	extern int sceGeGetStack(); 
	extern int sceGeEdramGetAddr(); 
	extern int sceGeListUpdateStallAddr(); 
	extern int sceGeGetCmd(); 
	extern int sceGeEdramSetAddrTranslation(); 
	extern int sceGeBreak(); 
	extern int sceGeDrawSync(); 
	extern int sceGeListEnQueue(); 
	extern int sceGeSetCallback(); 
	extern int sceGeListDeQueue(); 
	extern int sceGeGetMtx(); 
	extern int sceGeContinue(); 
	extern int sceGeSaveContext(); 
	extern int sceGeEdramGetSize(); 
	extern int sceGeListEnQueueHead(); 
	extern int sceGeRestoreContext(); 
	extern int sceGeUnsetCallback(); 
	extern int sceGeListSync(); 
}

#endif // sceGe_user_h__
