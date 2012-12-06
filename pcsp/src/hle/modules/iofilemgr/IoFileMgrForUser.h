#ifndef IoFileMgrForUser_h__
#define IoFileMgrForUser_h__

#include "kernel/kernel_types.h"

//used for sceIoOpen()
#define SCE_O_RDONLY    0x0001
#define SCE_O_WRONLY    0x0002
#define SCE_O_RDWR      0x0003
#define SCE_O_NBLOCK    0x0010     /*   Reserved: Non-Blocking I/O */
#define SCE_O_APPEND    0x0100     /* append (writes guaranteed at the end) */
#define SCE_O_CREAT     0x0200     /* open with file create */
#define SCE_O_TRUNC     0x0400     /* open with truncation */
#define SCE_O_EXCL	    0x0800	  /* exclusive create */
#define SCE_O_NOBUF     0x4000	  /*   Reserved: no device buffer and console interrupt */
#define SCE_O_NOWAIT    0x8000
#define SCE_O_FDEXCL    0x01000000 /* exclusive access */
#define SCE_O_PWLOCK    0x02000000 /* power control lock */

#define SCE_STM_FDIR 0x1000
#define SCE_STM_FREG 0x2000
#define SCE_STM_FLNK 0x4000


enum
{
	TYPE_DIR=0x10,
	TYPE_FILE=0x20
};

/* Date and time. */
struct ScePspDateTime {
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned int microsecond;
};

struct SceIoStat {
	s32 		    st_mode; //File type (file/dir) and mode (R/W/X)
	unsigned int 	st_attr; //Device-dependent attribute
	s64			    st_size;  /** Size of the file in bytes. */ 
  ScePspDateTime st_ctime_;  // Creation time
  ScePspDateTime st_atime_;  // Access time
  ScePspDateTime st_mtime_;  // Modification time
	unsigned int 	st_private[6];/** Device-specific data. */
};

struct SceIoDirent
{
  SceIoStat d_stat;
  char d_name[256];
  u32 d_private;
};

namespace IoFileMgrForUser
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceIoCloseAsync(); 
	extern int sceIoRemove(); 
	extern int sceIoDclose(); 
	extern int sceIoIoctlAsync(); 
	extern int sceIoCancel(); 
	extern int sceIoDread(); 
	extern int sceIoWaitAsync(); 
	extern int sceIoGetAsyncStat(); 
	extern int sceIoChstat(); 
	extern int sceIoAssign(); 
	extern int sceIoDopen(); 
	extern int sceIoChangeAsyncPriority(); 
	extern int sceIoGetstat(); 
	extern int sceIoSync(); 
	extern int sceIoSetAsyncCallback(); 
	extern int sceIoReadAsync(); 
	extern int sceIoOpenAsync(); 
	extern int sceIoClose(); 
	extern int sceIoRename(); 
	extern int sceIoLseekAsync(); 
	extern int sceIoUnassign(); 
	extern int sceIoRead(); 
	extern int sceIoLseek32(); 
	extern int sceIoIoctl(); 
	extern int sceIoGetFdList(); 
	extern int sceIoChdir(); 
	extern int sceIoDevctl(); 
	extern int sceIoWrite(); 
	extern int sceIoWaitAsyncCB(); 
	extern int sceIoPollAsync(); 
	extern int sceIoLseek(); 
	extern int sceIoLseek32Async(); 
	extern int sceIoRmdir(); 
	extern int sceIoOpen(); 
	extern int sceIoWriteAsync(); 
	extern int sceIoGetDevType(); 
	extern int sceIoMkdir(); 
}
#endif // IoFileMgrForUser_h__
