#ifndef sceUtilityMsgDialog_h__
#define sceUtilityMsgDialog_h__

#include "sceUtility.h"

#define SCE_UTILITY_MSGDIALOG_STRING_SIZE	            (512)
#define SCE_UTILITY_MSGDIALOG_BTN_NAVI_STRING_SIZE	    (64)

// New MSGDIALOG TYPE macros (replace SceUtilityMsgDialogOptionType in new firms).
#define SCE_UTILITY_MSGDIALOG_TYPE_SE_TYPE_ERROR        (0<<0)
#define SCE_UTILITY_MSGDIALOG_TYPE_SE_TYPE_NORMAL       (1<<0)

#define SCE_UTILITY_MSGDIALOG_TYPE_SE_MUTE_OFF          (0<<1)
#define SCE_UTILITY_MSGDIALOG_TYPE_SE_MUTE_ON           (1<<1)

#define SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_NONE     (0<<4)
#define SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO    (1<<4)
#define SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_OK       (2<<4)

#define SCE_UTILITY_MSGDIALOG_TYPE_DISABLE_CANCEL_OFF   (0<<7)
#define SCE_UTILITY_MSGDIALOG_TYPE_DISABLE_CANCEL_ON    (1<<7)

#define SCE_UTILITY_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE  (0<<8)
#define SCE_UTILITY_MSGDIALOG_TYPE_DEFAULT_CURSOR_YES   (0<<8)
#define SCE_UTILITY_MSGDIALOG_TYPE_DEFAULT_CURSOR_NO    (1<<8)
#define SCE_UTILITY_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK    (0<<8)

typedef enum SceUtilityMsgDialogType
{
	SCE_UTILITY_MSGDIALOG_TYPE_NUMBER		= 0,
	SCE_UTILITY_MSGDIALOG_TYPE_STRING		= 1
} SceUtilityMsgDialogType;

typedef enum SceUtilityMsgDialogStatus
{
	SCE_UTILITY_MSGDIALOG_LOCAL_STATUS_NONE		= 0, 
	SCE_UTILITY_MSGDIALOG_LOCAL_STATUS_INITIALIZING,
	SCE_UTILITY_MSGDIALOG_LOCAL_STATUS_INITIALIZED,
	SCE_UTILITY_MSGDIALOG_LOCAL_STATUS_OPENED,
	SCE_UTILITY_MSGDIALOG_LOCAL_STATUS_CLOSING,
	SCE_UTILITY_MSGDIALOG_LOCAL_STATUS_CLOSED
} SceUtilityMsgDialogStatus;

typedef enum SceUtilityMsgDialogOptionType
{
	SCE_UTILITY_MSGDIALOG_DIALOG_TYPE_ERROR	    = 0x00000000,
	SCE_UTILITY_MSGDIALOG_DIALOG_TYPE_NORMAL    = 0x00000001,	
	SCE_UTILITY_MSGDIALOG_BUTTON_TYPE_NONE	    = 0x00000000,
	SCE_UTILITY_MSGDIALOG_BUTTON_TYPE_YESNO	    = 0x00000010,
	SCE_UTILITY_MSGDIALOG_DEFAULT_CURSOR_YES    = 0x00000000,
	SCE_UTILITY_MSGDIALOG_DEFAULT_CURSOR_NO     = 0x00000100
} SceUtilityMsgDialogOptionType;

typedef enum SceUtilityMsgDialogButtonType
{
	SCE_UTILITY_MSGDIALOG_BUTTON_INVALID = 0,
	SCE_UTILITY_MSGDIALOG_BUTTON_YES     = 1,
	SCE_UTILITY_MSGDIALOG_BUTTON_OK      = 1,
	SCE_UTILITY_MSGDIALOG_BUTTON_NO      = 2,
	SCE_UTILITY_MSGDIALOG_BUTTON_ESCAPE  = 3
} SceUtilityMsgDialogButtonType;

typedef struct SceUtilityMsgDialogParam
{
	SceUtilityParamBase	base;
	int					result;
	int					type;
	unsigned int		errorNum;
	char				msgString[SCE_UTILITY_MSGDIALOG_STRING_SIZE];
	int					optionType;
	int					buttonResult;
	char				enterString[SCE_UTILITY_MSGDIALOG_BTN_NAVI_STRING_SIZE];
	char				backString[SCE_UTILITY_MSGDIALOG_BTN_NAVI_STRING_SIZE];
} SceUtilityMsgDialogParam;

namespace sceUtilityMsgDialog
{
	extern int sceUtilityMsgDialogInitStart(u32 a0);
	extern int sceUtilityMsgDialogGetStatus(); 
	extern int sceUtilityMsgDialogUpdate(); 
	extern int sceUtilityMsgDialogShutdownStart(); 
	extern int sceUtilityMsgDialogAbort();   
}

#endif  // sceUtility_h__