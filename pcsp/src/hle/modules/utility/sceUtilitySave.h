#ifndef sceUtilitySave_h__
#define sceUtilitySave_h__

#include "kernel/kernel_types.h"
#include "modules/iofilemgr/IoFileMgrForUser.h"
#include "modules/utility/sceUtility.h"

#ifdef st_atime
#undef st_atime
#undef st_ctime
#undef st_mtime
#endif

typedef enum
{
	SCE_UTILITY_SAVEDATA_TYPE_AUTOLOAD = 0,
	SCE_UTILITY_SAVEDATA_TYPE_AUTOSAVE,
	SCE_UTILITY_SAVEDATA_TYPE_LOAD,
	SCE_UTILITY_SAVEDATA_TYPE_SAVE,
	SCE_UTILITY_SAVEDATA_TYPE_LISTLOAD,
	SCE_UTILITY_SAVEDATA_TYPE_LISTSAVE,
	SCE_UTILITY_SAVEDATA_TYPE_LISTDELETE,
	SCE_UTILITY_SAVEDATA_TYPE_DELETE,
	SCE_UTILITY_SAVEDATA_TYPE_SIZES,
	SCE_UTILITY_SAVEDATA_TYPE_AUTODELETE,
	SCE_UTILITY_SAVEDATA_TYPE_SINGLEDELETE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_USERIDLIST,
	SCE_UTILITY_SAVEDATA_TYPE_MC_FILELIST,
	SCE_UTILITY_SAVEDATA_TYPE_MC_CREATEDATA_SECUREFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_CREATEDATA_NORMALFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_READ_SECUREFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_READ_NORMALFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_WRITE_SECUREFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_WRITE_NORMALFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_REMOVE_SECUREFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_REMOVE_NORMALFILE,
	SCE_UTILITY_SAVEDATA_TYPE_MC_DELETEDATA,
	SCE_UTILITY_SAVEDATA_TYPE_MC_CHECKSIZE
} SceUtilitySavedataType;

typedef enum
{
	SCE_UTILITY_SD_TITLEID_SIZE = 13,
	SCE_UTILITY_SD_USERID_SIZE = 20,
	SCE_UTILITY_SD_FILENAME_SIZE = 13,
	SCE_UTILITY_SD_LISTITEM_MAX = 1024,
	SCE_UTILITY_SD_SIZESTR_SIZE = 8,
	SCE_UTILITY_SD_SECUREFILEID_SIZE = 16,
	SCE_UTILITY_SD_SYSTEMFILELIST_MAX = 5,
	SCE_UTILITY_SD_SECUREFILELIST_MAX = 99,
	SCE_UTILITY_SD_NORMALFILELIST_MAX = 8192,
	SCE_UTILITY_SD_USERIDLIST_MAX = 2048
} SceUtilitySavedataSize;

typedef enum
{
	SCE_UTILITY_SD_SYSF_TITLE_SIZE = 128,
	SCE_UTILITY_SD_SYSF_SD_TITLE_SIZE = 128,
	SCE_UTILITY_SD_SYSF_DETAIL_SIZE = 1024
} SceUtilitySavedataSystemFileParamSize;

typedef enum
{
	SCE_UTILITY_SAVEDATA_INITFOCUS_USERID = 0,
	SCE_UTILITY_SAVEDATA_INITFOCUS_LISTFIRST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_LISTLAST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_DATALATEST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_DATAOLDEST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_DATAFIRST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_DATALAST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_EMPTYFIRST,
	SCE_UTILITY_SAVEDATA_INITFOCUS_EMPTYLAST
} SceUtilitySavedataInitFocus;

typedef enum
{
	SCE_UTILITY_SAVEDATA_VERSION_CURRENT = 0,
	SCE_UTILITY_SAVEDATA_VERSION_0,
	SCE_UTILITY_SAVEDATA_VERSION_1,
	SCE_UTILITY_SAVEDATA_VERSION_2
} SceUtilitySavedataVersion;

typedef enum
{
	SCE_UTILITY_SAVEDATA_MC_STATUS_SINGLE = 0,
	SCE_UTILITY_SAVEDATA_MC_STATUS_START,
	SCE_UTILITY_SAVEDATA_MC_STATUS_RELAY,
	SCE_UTILITY_SAVEDATA_MC_STATUS_END
} SceUtilitySavedataMultiCallStatus;

#define SCE_UTILITY_SAVEDATA_BIND_UNUSED (0)
#define SCE_UTILITY_SAVEDATA_BIND_OK (1)
#define SCE_UTILITY_SAVEDATA_BIND_ERROR (2)
#define SCE_UTILITY_SAVEDATA_BIND_UNSUPPORTED (3)
#define SCE_UTILITY_SAVEDATA_BIND_MYPSP_MASK (0x3)

#define SCE_UTILITY_SAVEDATA_OVERWRITEMODE_OFF (0)
#define SCE_UTILITY_SAVEDATA_OVERWRITEMODE_ON (1)

#define SCE_UTILITY_SAVEDATA_USERID_NULL "<>"

#define SCE_UTILITY_SAVEDATA_UPDATE_TITLE       (1 << 0)
#define SCE_UTILITY_SAVEDATA_UPDATE_SDTITLE     (1 << 1)
#define SCE_UTILITY_SAVEDATA_UPDATE_DETAIL      (1 << 2)
#define SCE_UTILITY_SAVEDATA_UPDATE_PARENTALLEV (1 << 3)

typedef struct SceUtilitySDExtFile
{
	u32/*void **/pDataBuf;
	u32 dataBufSize;
	u32 dataFileSize;
	char *reserved;
} SceUtilitySDExtFile;

typedef struct SceUtilitySDSystemFileParam
{
	char title[SCE_UTILITY_SD_SYSF_TITLE_SIZE];
	char savedataTitle[SCE_UTILITY_SD_SYSF_SD_TITLE_SIZE];
	char detail[SCE_UTILITY_SD_SYSF_DETAIL_SIZE];
	unsigned char parentalLev;
	unsigned char typeWriteRemoveUpdateParam;
	unsigned char reserved[2];
} SceUtilitySDSystemFileParam;

typedef struct SceUtilitySavedataListSaveNewData
{
	SceUtilitySDExtFile icon0;
	char *pTitle;
} SceUtilitySavedataListSaveNewData;

typedef struct SceUtilitySavedataMsFreeSize
{
	unsigned int msClusterSizeByte;
	unsigned int msFreeCluster;
	unsigned int msFreeSizeKB;
	char msFreeSizeStr[SCE_UTILITY_SD_SIZESTR_SIZE];
} SceUtilitySavedataMsFreeSize;

typedef struct SceUtilitySavedataMsDataSize
{
	char titleId[SCE_UTILITY_SD_TITLEID_SIZE];
	char reserved[3];
	char userId[SCE_UTILITY_SD_USERID_SIZE];
	unsigned int cluster;
	unsigned int sizeKB;
	char sizeStr[SCE_UTILITY_SD_SIZESTR_SIZE];
	unsigned int size32KB;
	char size32Str[SCE_UTILITY_SD_SIZESTR_SIZE];
} SceUtilitySavedataMsDataSize;

typedef struct SceUtilitySavedataUtilityDataSize
{
	unsigned int cluster;
	unsigned int sizeKB;
	char sizeStr[SCE_UTILITY_SD_SIZESTR_SIZE];
	unsigned int size32KB;
	char size32Str[SCE_UTILITY_SD_SIZESTR_SIZE];
} SceUtilitySavedataUtilityDataSize;

typedef struct SceUtilitySDUserIdStat
{
	SceMode st_mode;
	ScePspDateTime st_ctime;
	ScePspDateTime st_atime;
	ScePspDateTime st_mtime;
	char userId[SCE_UTILITY_SD_USERID_SIZE];
} SceUtilitySDUserIdStat;

typedef struct SceUtilitySavedataUserIdList
{
	unsigned int userIdMax;
	unsigned int userIdNum;
	SceUtilitySDUserIdStat *pUserIds;
} SceUtilitySavedataUserIdList;

typedef struct SceUtilitySDFileStat
{
	SceMode st_mode;
	SceOff st_size;
	ScePspDateTime st_ctime;
	ScePspDateTime st_atime;
	ScePspDateTime st_mtime;
	char fileName[SCE_UTILITY_SD_FILENAME_SIZE];
	char reserved[3];
} SceUtilitySDFileStat;

typedef struct SceUtilitySavedataFileList
{
	u32 secureFileMax;
	u32 normalFileMax;
	u32 systemFileMax;
	u32 secureFileNum;
	u32 normalFileNum;
	u32 systemFileNum;
	u32/*SceUtilitySDFileStat **/pSecureFiles;
	u32/*SceUtilitySDFileStat **/pNormalFiles;
	u32/*SceUtilitySDFileStat **/pSystemFiles;
} SceUtilitySavedataFileList;

typedef struct SceUtilitySDFileStat2
{
	SceOff st_size;
	char fileName[SCE_UTILITY_SD_FILENAME_SIZE];
	char reserved[3];
} SceUtilitySDFileStat2;

typedef struct SceUtilitySavedataCheckSize
{
	unsigned int secureFileNum;
	unsigned int normalFileNum;
	u32 /*SceUtilitySDFileStat2 **/pSecureFiles;
	u32/*SceUtilitySDFileStat2 **/ pNormalFiles;
	unsigned int msClusterSizeByte;
	unsigned int msFreeCluster;
	unsigned int msFreeSizeKB;
	char msFreeSizeStr[SCE_UTILITY_SD_SIZESTR_SIZE];
	unsigned int createNeedSizeKB;
	char createNeedSizeStr[SCE_UTILITY_SD_SIZESTR_SIZE];
	unsigned int overwriteNeedSizeKB;
	char overwriteNeedSizeStr[SCE_UTILITY_SD_SIZESTR_SIZE];
} SceUtilitySavedataCheckSize;

typedef struct SceUtilitySavedataParam
{
	SceUtilityParamBase base;
	int type;
	unsigned int bind;
	unsigned int overWriteMode;
	char titleId[SCE_UTILITY_SD_TITLEID_SIZE];
	char reserved[3];
	char userId[SCE_UTILITY_SD_USERID_SIZE];
	u32 pUserIds;/*char (*pUserIds)[SCE_UTILITY_SD_USERID_SIZE];*/
	char fileName[SCE_UTILITY_SD_FILENAME_SIZE];
	char reserved1[3];
	u32 /*void **/pDataBuf;
	u32 dataBufSize;
	u32 dataFileSize;
	SceUtilitySDSystemFileParam systemFile;
	SceUtilitySDExtFile icon0;
	SceUtilitySDExtFile icon1;
	SceUtilitySDExtFile pic1;
	SceUtilitySDExtFile snd0;
	u32 /*SceUtilitySavedataListSaveNewData*/ pNewData;
	unsigned int initFocus;
	int abortedStatus;
	u32 /*SceUtilitySavedataMsFreeSize*/  pMs;
	u32 /*SceUtilitySavedataMsDataSize*/  pMsData;
	u32 /*SceUtilitySavedataUtilityDataSize */ pUtilityData;
	unsigned char secureFileId[SCE_UTILITY_SD_SECUREFILEID_SIZE];
	SceUtilitySavedataVersion dataVersion;
	SceUtilitySavedataMultiCallStatus mcStatus;
	SceUtilitySavedataUserIdList* pUserIdList;
	u32 /*SceUtilitySavedataFileList**/  pFileList;
	u32 /*SceUtilitySavedataCheckSize*/  pCheckSize;
} SceUtilitySavedataParam;

namespace sceUtilitySave
{

  extern int sceUtilitySavedataUpdate();
  extern int sceUtilitySavedataShutdownStart(); 
  extern int sceUtilitySavedataGetStatus(); 
  extern int sceUtilitySavedataInitStart(u32 a0); 
  void hleSavedata(SceUtilitySavedataParam *param);
  void hleSaveNoMemStick(SceUtilitySavedataParam *param);
}

#endif
