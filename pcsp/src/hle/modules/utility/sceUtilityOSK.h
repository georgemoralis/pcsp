#ifndef sceUtilityOSK_h__
#define sceUtilityOSK_h__

#include "common_types.h"
#include "types.h"
#include "sceUtility.h"

#define SCE_UTILITY_OSK_MAX_LENGTH (512)
#define SCE_UTILITY_OSK_MAX_LINES (50)

typedef enum SceUtilityOskBoolValue
{
    SCE_UTILITY_OSK_BOOL_VALUE_FALSE = 0,
    SCE_UTILITY_OSK_BOOL_VALUE_TRUE  = 1
} SceUtilityOskBoolValue;

typedef enum SceUtilityOskLocalStatus
{
    SCE_UTILITY_OSK_LOCAL_STATUS_NONE         = 0,
    SCE_UTILITY_OSK_LOCAL_STATUS_INITIALIZING = 1,
    SCE_UTILITY_OSK_LOCAL_STATUS_INITIALIZED  = 2,
    SCE_UTILITY_OSK_LOCAL_STATUS_OPENED       = 3,
    SCE_UTILITY_OSK_LOCAL_STATUS_CLOSING      = 4,
    SCE_UTILITY_OSK_LOCAL_STATUS_CLOSED       = 5
} SceUtilityOskLocalStatus;

typedef enum SceUtilityOskInputFieldResult
{
    SCE_UTILITY_OSK_INPUT_FIELD_RESULT_UNEDITED = 0,
    SCE_UTILITY_OSK_INPUT_FIELD_RESULT_CANCELED = 1,
    SCE_UTILITY_OSK_INPUT_FIELD_RESULT_EDITED   = 2,
} SceUtilityOskInputFieldResult;

typedef struct SceUtilityOskInputFieldInfo
{
    unsigned int                   input_method_type;
    unsigned int                   input_method_attributes;
    unsigned int                   writing_language_type;
    SceUtilityOskBoolValue         hide_mode;
    int                            input_character_type;
    int                            num_lines;
    int                            kinsoku;
    u32 /* unsigned short * */     message;
    u32 /* unsigned short * */     init_text;
    int                            result_text_buffer_size;
    u32 /*unsigned short * */      result_text_buffer;
    SceUtilityOskInputFieldResult  result;
    int                            limit_length;
} SceUtilityOskInputFieldInfo;

typedef struct SceUtilityOskParam
{
    SceUtilityParamBase                    base;
    unsigned int                           num_input_fields;
    u32 /*SceUtilityOskInputFieldInfo * */ input_field_info;
    SceUtilityOskLocalStatus               local_status;
    int                                    error_code;
} SceUtilityOskParam;

namespace sceUtilityOSK
{
    extern int sceUtilityOskInitStart(u32 a0); 
    extern int sceUtilityOskGetStatus(); 
    extern int sceUtilityOskUpdate(); 
    extern int sceUtilityOskShutdownStart(); 
}

#endif // sceUtility_h__
