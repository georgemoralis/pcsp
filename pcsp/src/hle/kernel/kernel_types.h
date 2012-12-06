#ifndef kernel_types_h__
#define kernel_types_h__

#include "common_types.h"
#include "types.h"

typedef enum SceKernelDevkitVersion
{
    SCE_FIRMWARE_100 = 0x01000300,
    SCE_FIRMWARE_150 = 0x01050001,
    SCE_FIRMWARE_151 = 0x01050100,
    SCE_FIRMWARE_152 = 0x01050200,
    SCE_FIRMWARE_200 = 0x02000010,
    SCE_FIRMWARE_201 = 0x02000010, // Same as 2.00
    SCE_FIRMWARE_250 = 0x02050010,
    SCE_FIRMWARE_260 = 0x02060010,
    SCE_FIRMWARE_270 = 0x02070010,
    SCE_FIRMWARE_271 = 0x02070110,
    SCE_FIRMWARE_280 = 0x02080010,
    SCE_FIRMWARE_300 = 0x03000010,
    SCE_FIRMWARE_310 = 0x03010010,
    SCE_FIRMWARE_330 = 0x03030010,
    SCE_FIRMWARE_340 = 0x03040010,
    SCE_FIRMWARE_350 = 0x03050010,
    SCE_FIRMWARE_370 = 0x03070010,
    SCE_FIRMWARE_395 = 0x03090510,
    SCE_FIRMWARE_450 = 0x04050010,
    SCE_FIRMWARE_500 = 0x05000010,
    SCE_FIRMWARE_550 = 0x05050010
} SceKernelDevkitVersion;

typedef enum SceKernelErrorCode
{
    SCE_KERNEL_ERROR_OK = 0,
    SCE_KERNEL_ERROR_ERROR = 0x80020001,
    SCE_KERNEL_ERROR_NOTIMP = 0x80020002,
    SCE_KERNEL_ERROR_ILLEGAL_EXPCODE = 0x80020032,
    SCE_KERNEL_ERROR_EXPHANDLER_NOUSE = 0x80020033,
    SCE_KERNEL_ERROR_EXPHANDLER_USED = 0x80020034,
    SCE_KERNEL_ERROR_SYCALLTABLE_NOUSED = 0x80020035,
    SCE_KERNEL_ERROR_SYCALLTABLE_USED = 0x80020036,
    SCE_KERNEL_ERROR_ILLEGAL_SYSCALLTABLE = 0x80020037,
    SCE_KERNEL_ERROR_ILLEGAL_PRIMARY_SYSCALL_NUMBER = 0x80020038,
    SCE_KERNEL_ERROR_PRIMARY_SYSCALL_NUMBER_INUSE = 0x80020039,
    SCE_KERNEL_ERROR_ILLEGAL_CONTEXT = 0x80020064,
    SCE_KERNEL_ERROR_ILLEGAL_INTRCODE = 0x80020065,
    SCE_KERNEL_ERROR_CPUDI = 0x80020066,
    SCE_KERNEL_ERROR_FOUND_HANDLER = 0x80020067,
    SCE_KERNEL_ERROR_NOTFOUND_HANDLER = 0x80020068,
    SCE_KERNEL_ERROR_ILLEGAL_INTRLEVEL = 0x80020069,
    SCE_KERNEL_ERROR_ILLEGAL_ADDRESS = 0x8002006a,
    SCE_KERNEL_ERROR_ILLEGAL_INTRPARAM = 0x8002006b,
    SCE_KERNEL_ERROR_ILLEGAL_STACK_ADDRESS = 0x8002006c,
    SCE_KERNEL_ERROR_ALREADY_STACK_SET = 0x8002006d,
    SCE_KERNEL_ERROR_NO_TIMER = 0x80020096,
    SCE_KERNEL_ERROR_ILLEGAL_TIMERID = 0x80020097,
    SCE_KERNEL_ERROR_ILLEGAL_SOURCE = 0x80020098,
    SCE_KERNEL_ERROR_ILLEGAL_PRESCALE = 0x80020099,
    SCE_KERNEL_ERROR_TIMER_BUSY = 0x8002009a,
    SCE_KERNEL_ERROR_TIMER_NOT_SETUP = 0x8002009b,
    SCE_KERNEL_ERROR_TIMER_NOT_INUSE = 0x8002009c,
    SCE_KERNEL_ERROR_UNIT_USED = 0x800200a0,
    SCE_KERNEL_ERROR_UNIT_NOUSE = 0x800200a1,
    SCE_KERNEL_ERROR_NO_ROMDIR = 0x800200a2,
    SCE_KERNEL_ERROR_IDTYPE_EXIST = 0x800200c8,
    SCE_KERNEL_ERROR_IDTYPE_NOT_EXIST = 0x800200c9,
    SCE_KERNEL_ERROR_IDTYPE_NOT_EMPTY = 0x800200ca,
    SCE_KERNEL_ERROR_UNKNOWN_UID = 0x800200cb,
    SCE_KERNEL_ERROR_UNMATCH_UID_TYPE = 0x800200cc,
    SCE_KERNEL_ERROR_ID_NOT_EXIST = 0x800200cd,
    SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC = 0x800200ce,
    SCE_KERNEL_ERROR_UID_ALREADY_HOLDER = 0x800200cf,
    SCE_KERNEL_ERROR_UID_NOT_HOLDER = 0x800200d0,
    SCE_KERNEL_ERROR_ILLEGAL_PERM = 0x800200d1,
    SCE_KERNEL_ERROR_ILLEGAL_ARGUMENT = 0x800200d2,
    SCE_KERNEL_ERROR_ILLEGAL_ADDR = 0x800200d3,
    SCE_KERNEL_ERROR_OUT_OF_RANGE = 0x800200d4,
    SCE_KERNEL_ERROR_MEM_RANGE_OVERLAP = 0x800200d5,
    SCE_KERNEL_ERROR_ILLEGAL_PARTITION = 0x800200d6,
    SCE_KERNEL_ERROR_PARTITION_INUSE = 0x800200d7,
    SCE_KERNEL_ERROR_ILLEGAL_MEMBLOCKTYPE = 0x800200d8,
    SCE_KERNEL_ERROR_MEMBLOCK_ALLOC_FAILED = 0x800200d9,
    SCE_KERNEL_ERROR_MEMBLOCK_RESIZE_LOCKED = 0x800200da,
    SCE_KERNEL_ERROR_MEMBLOCK_RESIZE_FAILED = 0x800200db,
    SCE_KERNEL_ERROR_HEAPBLOCK_ALLOC_FAILED = 0x800200dc,
    SCE_KERNEL_ERROR_HEAP_ALLOC_FAILED = 0x800200dd,
    SCE_KERNEL_ERROR_ILLEGAL_CHUNK_ID = 0x800200de,
    SCE_KERNEL_ERROR_NOCHUNK = 0x800200df,
    SCE_KERNEL_ERROR_NO_FREECHUNK = 0x800200e0,
    SCE_KERNEL_ERROR_LINKERR = 0x8002012c,
    SCE_KERNEL_ERROR_ILLEGAL_OBJECT = 0x8002012d,
    SCE_KERNEL_ERROR_UNKNOWN_MODULE = 0x8002012e,
    SCE_KERNEL_ERROR_NOFILE = 0x8002012f,
    SCE_KERNEL_ERROR_FILEERR = 0x80020130,
    SCE_KERNEL_ERROR_MEMINUSE = 0x80020131,
    SCE_KERNEL_ERROR_PARTITION_MISMATCH = 0x80020132,
    SCE_KERNEL_ERROR_ALREADY_STARTED = 0x80020133,
    SCE_KERNEL_ERROR_NOT_STARTED = 0x80020134,
    SCE_KERNEL_ERROR_ALREADY_STOPPED = 0x80020135,
    SCE_KERNEL_ERROR_CAN_NOT_STOP = 0x80020136,
    SCE_KERNEL_ERROR_NOT_STOPPED = 0x80020137,
    SCE_KERNEL_ERROR_NOT_REMOVABLE = 0x80020138,
    SCE_KERNEL_ERROR_EXCLUSIVE_LOAD = 0x80020139,
    SCE_KERNEL_ERROR_LIBRARY_NOT_YET_LINKED = 0x8002013a,
    SCE_KERNEL_ERROR_LIBRARY_FOUND = 0x8002013b,
    SCE_KERNEL_ERROR_LIBRARY_NOTFOUND = 0x8002013c,
    SCE_KERNEL_ERROR_ILLEGAL_LIBRARY = 0x8002013d,
    SCE_KERNEL_ERROR_LIBRARY_INUSE = 0x8002013e,
    SCE_KERNEL_ERROR_ALREADY_STOPPING = 0x8002013f,
    SCE_KERNEL_ERROR_ILLEGAL_OFFSET = 0x80020140,
    SCE_KERNEL_ERROR_ILLEGAL_POSITION = 0x80020141,
    SCE_KERNEL_ERROR_ILLEGAL_ACCESS = 0x80020142,
    SCE_KERNEL_ERROR_MODULE_MGR_BUSY = 0x80020143,
    SCE_KERNEL_ERROR_ILLEGAL_FLAG = 0x80020144,
    SCE_KERNEL_ERROR_CANNOT_GET_MODULELIST = 0x80020145,
    SCE_KERNEL_ERROR_PROHIBIT_LOADMODULE_DEVICE = 0x80020146,
    SCE_KERNEL_ERROR_PROHIBIT_LOADEXEC_DEVICE = 0x80020147,
    SCE_KERNEL_ERROR_UNSUPPORTED_PRX_TYPE = 0x80020148,
    SCE_KERNEL_ERROR_ILLEGAL_PERM_CALL = 0x80020149,
    SCE_KERNEL_ERROR_CANNOT_GET_MODULE_INFORMATION = 0x8002014a,
    SCE_KERNEL_ERROR_ILLEGAL_LOADEXEC_BUFFER = 0x8002014b,
    SCE_KERNEL_ERROR_ILLEGAL_LOADEXEC_FILENAME = 0x8002014c,
    SCE_KERNEL_ERROR_NO_EXIT_CALLBACK = 0x8002014d,
    SCE_KERNEL_ERROR_NO_MEMORY = 0x80020190,
    SCE_KERNEL_ERROR_ILLEGAL_ATTR = 0x80020191,
    SCE_KERNEL_ERROR_ILLEGAL_ENTRY = 0x80020192,
    SCE_KERNEL_ERROR_ILLEGAL_PRIORITY = 0x80020193,
    SCE_KERNEL_ERROR_ILLEGAL_STACK_SIZE = 0x80020194,
    SCE_KERNEL_ERROR_ILLEGAL_MODE = 0x80020195,
    SCE_KERNEL_ERROR_ILLEGAL_MASK = 0x80020196,
    SCE_KERNEL_ERROR_ILLEGAL_THID = 0x80020197,
    SCE_KERNEL_ERROR_UNKNOWN_THID = 0x80020198,
    SCE_KERNEL_ERROR_UNKNOWN_SEMID = 0x80020199,
    SCE_KERNEL_ERROR_UNKNOWN_EVFID = 0x8002019a,
    SCE_KERNEL_ERROR_UNKNOWN_MBXID = 0x8002019b,
    SCE_KERNEL_ERROR_UNKNOWN_VPLID = 0x8002019c,
    SCE_KERNEL_ERROR_UNKNOWN_FPLID = 0x8002019d,
    SCE_KERNEL_ERROR_UNKNOWN_MPPID = 0x8002019e,
    SCE_KERNEL_ERROR_UNKNOWN_ALMID = 0x8002019f,
    SCE_KERNEL_ERROR_UNKNOWN_TEID = 0x800201a0,
    SCE_KERNEL_ERROR_UNKNOWN_CBID = 0x800201a1,
    SCE_KERNEL_ERROR_DORMANT = 0x800201a2,
    SCE_KERNEL_ERROR_SUSPEND = 0x800201a3,
    SCE_KERNEL_ERROR_NOT_DORMANT = 0x800201a4,
    SCE_KERNEL_ERROR_NOT_SUSPEND = 0x800201a5,
    SCE_KERNEL_ERROR_NOT_WAIT = 0x800201a6,
    SCE_KERNEL_ERROR_CAN_NOT_WAIT = 0x800201a7,
    SCE_KERNEL_ERROR_WAIT_TIMEOUT = 0x800201a8,
    SCE_KERNEL_ERROR_WAIT_CANCEL = 0x800201a9,
    SCE_KERNEL_ERROR_RELEASE_WAIT = 0x800201aa,
    SCE_KERNEL_ERROR_NOTIFY_CALLBACK = 0x800201ab,
    SCE_KERNEL_ERROR_THREAD_TERMINATED = 0x800201ac,
    SCE_KERNEL_ERROR_SEMA_ZERO = 0x800201ad,
    SCE_KERNEL_ERROR_SEMA_OVF = 0x800201ae,
    SCE_KERNEL_ERROR_EVF_COND = 0x800201af,
    SCE_KERNEL_ERROR_EVF_MULTI = 0x800201b0,
    SCE_KERNEL_ERROR_EVF_ILPAT = 0x800201b1,
    SCE_KERNEL_ERROR_MBOX_NOMSG = 0x800201b2,
    SCE_KERNEL_ERROR_MPP_FULL = 0x800201b3,
    SCE_KERNEL_ERROR_MPP_EMPTY = 0x800201b4,
    SCE_KERNEL_ERROR_WAIT_DELETE = 0x800201b5,
    SCE_KERNEL_ERROR_ILLEGAL_MEMBLOCK = 0x800201b6,
    SCE_KERNEL_ERROR_ILLEGAL_MEMSIZE = 0x800201b7,
    SCE_KERNEL_ERROR_ILLEGAL_SPADADDR = 0x800201b8,
    SCE_KERNEL_ERROR_SPAD_INUSE = 0x800201b9,
    SCE_KERNEL_ERROR_SPAD_NOT_INUSE = 0x800201ba,
    SCE_KERNEL_ERROR_ILLEGAL_TYPE = 0x800201bb,
    SCE_KERNEL_ERROR_ILLEGAL_SIZE = 0x800201bc,
    SCE_KERNEL_ERROR_ILLEGAL_COUNT = 0x800201bd,
    SCE_KERNEL_ERROR_UNKNOWN_VTID = 0x800201be,
    SCE_KERNEL_ERROR_ILLEGAL_VTID = 0x800201bf,
    SCE_KERNEL_ERROR_ILLEGAL_KTLSID = 0x800201c0,
    SCE_KERNEL_ERROR_KTLS_FULL = 0x800201c1,
    SCE_KERNEL_ERROR_KTLS_BUSY = 0x800201c2,
    SCE_KERNEL_ERROR_PM_INVALID_PRIORITY = 0x80020258,
    SCE_KERNEL_ERROR_PM_INVALID_DEVNAME = 0x80020259,
    SCE_KERNEL_ERROR_PM_UNKNOWN_DEVNAME = 0x8002025a,
    SCE_KERNEL_ERROR_PM_PMINFO_REGISTERED = 0x8002025b,
    SCE_KERNEL_ERROR_PM_PMINFO_UNREGISTERED = 0x8002025c,
    SCE_KERNEL_ERROR_PM_INVALID_MAJOR_STATE = 0x8002025d,
    SCE_KERNEL_ERROR_PM_INVALID_REQUEST = 0x8002025e,
    SCE_KERNEL_ERROR_PM_UNKNOWN_REQUEST = 0x8002025f,
    SCE_KERNEL_ERROR_PM_INVALID_UNIT = 0x80020260,
    SCE_KERNEL_ERROR_PM_CANNOT_CANCEL = 0x80020261,
    SCE_KERNEL_ERROR_PM_INVALID_PMINFO = 0x80020262,
    SCE_KERNEL_ERROR_PM_INVALID_ARGUMENT = 0x80020263,
    SCE_KERNEL_ERROR_PM_ALREADY_TARGET_PWRSTATE = 0x80020264,
    SCE_KERNEL_ERROR_PM_CHANGE_PWRSTATE_FAILED = 0x80020265,
    SCE_KERNEL_ERROR_PM_CANNOT_CHANGE_DEVPWR_STATE = 0x80020266,
    SCE_KERNEL_ERROR_PM_NO_SUPPORT_DEVPWR_STATE = 0x80020267,
    SCE_KERNEL_ERROR_DMAC_REQUEST_FAILED = 0x800202bc,
    SCE_KERNEL_ERROR_DMAC_REQUEST_DENIED = 0x800202bd,
    SCE_KERNEL_ERROR_DMAC_OP_QUEUED = 0x800202be,
    SCE_KERNEL_ERROR_DMAC_OP_NOT_QUEUED = 0x800202bf,
    SCE_KERNEL_ERROR_DMAC_OP_RUNNING = 0x800202c0,
    SCE_KERNEL_ERROR_DMAC_OP_NOT_ASSIGNED = 0x800202c1,
    SCE_KERNEL_ERROR_DMAC_OP_TIMEOUT = 0x800202c2,
    SCE_KERNEL_ERROR_DMAC_OP_FREED = 0x800202c3,
    SCE_KERNEL_ERROR_DMAC_OP_USED = 0x800202c4,
    SCE_KERNEL_ERROR_DMAC_OP_EMPTY = 0x800202c5,
    SCE_KERNEL_ERROR_DMAC_OP_ABORTED = 0x800202c6,
    SCE_KERNEL_ERROR_DMAC_OP_ERROR = 0x800202c7,
    SCE_KERNEL_ERROR_DMAC_CHANNEL_RESERVED = 0x800202c8,
    SCE_KERNEL_ERROR_DMAC_CHANNEL_EXCLUDED = 0x800202c9,
    SCE_KERNEL_ERROR_DMAC_PRIVILEGE_ADDRESS = 0x800202ca,
    SCE_KERNEL_ERROR_DMAC_NO_ENOUGHSPACE = 0x800202cb,
    SCE_KERNEL_ERROR_DMAC_CHANNEL_NOT_ASSIGNED = 0x800202cc,
    SCE_KERNEL_ERROR_DMAC_CHILD_OPERATION = 0x800202cd,
    SCE_KERNEL_ERROR_DMAC_TOO_MUCH_SIZE = 0x800202ce,
    SCE_KERNEL_ERROR_DMAC_INVALID_ARGUMENT = 0x800202cf,
    SCE_KERNEL_ERROR_MFILE = 0x80020320,
    SCE_KERNEL_ERROR_NODEV = 0x80020321,
    SCE_KERNEL_ERROR_XDEV = 0x80020322,
    SCE_KERNEL_ERROR_BADF = 0x80020323,
    SCE_KERNEL_ERROR_INVAL = 0x80020324,
    SCE_KERNEL_ERROR_UNSUP = 0x80020325,
    SCE_KERNEL_ERROR_ALIAS_USED = 0x80020326,
    SCE_KERNEL_ERROR_CANNOT_MOUNT = 0x80020327,
    SCE_KERNEL_ERROR_DRIVER_DELETED = 0x80020328,
    SCE_KERNEL_ERROR_ASYNC_BUSY = 0x80020329,
    SCE_KERNEL_ERROR_NOASYNC = 0x8002032a,
    SCE_KERNEL_ERROR_REGDEV = 0x8002032b,
    SCE_KERNEL_ERROR_NOCWD = 0x8002032c,
    SCE_KERNEL_ERROR_NAMETOOLONG = 0x8002032d,
    SCE_KERNEL_ERROR_NXIO = 0x800203e8,
    SCE_KERNEL_ERROR_IO = 0x800203e9,
    SCE_KERNEL_ERROR_NOMEM = 0x800203ea,
    SCE_KERNEL_ERROR_STDIO_NOT_OPENED = 0x800203eb,
    SCE_KERNEL_ERROR_CACHE_ALIGNMENT = 0x8002044c,
    SCE_KERNEL_ERROR_ERRORMAX = 0x8002044d
} SceKernelErrorCode;

typedef enum SceErrorCode
{
    SCE_OK = 0,
} SceErrorCode;

typedef enum SceArgumentErrorCode
{
    SCE_ERROR_INVALID_ID = 0x80000100,
    SCE_ERROR_INVALID_NAME = 0x80000101,
    SCE_ERROR_INVALID_INDEX = 0x80000102,
    SCE_ERROR_INVALID_POINTER = 0x80000103,
    SCE_ERROR_INVALID_SIZE = 0x80000104,
    SCE_ERROR_INVALID_FLAG = 0x80000105,
    SCE_ERROR_INVALID_COMMAND = 0x80000106,
    SCE_ERROR_INVALID_MODE = 0x80000107,
    SCE_ERROR_INVALID_FORMAT = 0x80000108,
    SCE_ERROR_INVALID_VALUE = 0x800001FE,
    SCE_ERROR_INVALID_ARG = 0x800001FF
} SceArgumentErrorCode;

typedef s32                             SceUID;
typedef u32                             SceSize;
typedef u8                              SceUChar;
typedef u32                             SceUInt;
typedef s32                             SceSSize;
typedef s32                             SceMode;
typedef s64                             SceOff;
typedef s64                             SceIores;

typedef enum SceThreadAttributes
{
    SCE_KERNEL_THREAD_ATTR_VFPU         = 0x00004000,
    SCE_KERNEL_THREAD_ATTR_SCRATCH_SRAM = 0x00008000,
    SCE_KERNEL_THREAD_ATTR_NO_FILLSTACK = 0x00100000,
    SCE_KERNEL_THREAD_ATTR_CLEAR_STACK  = 0x00200000,
    SCE_KERNEL_THREAD_ATTR_SUSPENDED    = 0x08000000,
    SCE_KERNEL_THREAD_ATTR_USER         = 0x80000000,
    SCE_KERNEL_THREAD_ATTR_USBWLAN      = 0xA0000000,
    SCE_KERNEL_THREAD_ATTR_VSH          = 0xC0000000
} SceThreadAttributes;

typedef enum SceKernelThreadEventId
{
    SCE_KERNEL_THREAD_EVENTID_ALL     = 0xFFFFFFFF,
    SCE_KERNEL_THREAD_EVENTID_KERNEL  = 0xFFFFFFF8,
    SCE_KERNEL_THREAD_EVENTID_USER    = 0xFFFFFFF0,
    SCE_KERNEL_THREAD_EVENTID_CURRENT = 0
} SceKernelThreadEventId;

typedef enum SceKernelThreadEvent
{
    SCE_KERNEL_THREAD_EVENT_CREATE = 1,
    SCE_KERNEL_THREAD_EVENT_START  = 2,
    SCE_KERNEL_THREAD_EVENT_EXIT   = 4,
    SCE_KERNEL_THREAD_EVENT_DELETE = 8,
    SCE_KERNEL_THREAD_EVENT_ALL    = SCE_KERNEL_THREAD_EVENT_CREATE|SCE_KERNEL_THREAD_EVENT_START|SCE_KERNEL_THREAD_EVENT_EXIT|SCE_KERNEL_THREAD_EVENT_DELETE,
} SceKernelThreadEvent;

typedef class SceKernelThreadEntry
{
public:
    SceKernelThreadEntry(u32 entry = 0) : m_entry(entry) {}
    SceKernelThreadEntry(SceKernelThreadEntry const &entry) : m_entry(entry.m_entry) {}

    operator u32() const { return m_entry; }

    //int operator()(SceSize args, void *argp) { return *(Memory::addr< int (SceSize, void *) >(m_entry))(args, Memory::addr< void >(argp)); }

private:
    u32 m_entry;
} SceKernelThreadEntry;

typedef struct SceThreadStack
{
    SceUID                              thread_id;
    int                                 unk_4;
    int                                 unk_8;
    int                                 unk_C;
    int                                *value;
} SceThreadStack;

typedef struct SceSyscallStackInfo
{
    SceSyscallStackInfo                *next;
    SceThreadStack                     *stack;
    SceUInt                             stack_size;
} SceSyscallStackInfo;

typedef struct SceKernelSysClock
{
    SceUInt                             low;
    SceUInt                             hi;

    SceKernelSysClock() {}
    SceKernelSysClock(u64 value) : low(value&0xFFFFFFFF), hi(value>>32) {}

    operator u64() const { return (u64)low + ((u64)hi << 32); }

    SceKernelSysClock &operator =  (u64 value) { low = value&0xFFFFFFFF; hi = value>>32; return *this; }

    SceKernelSysClock &operator += (u64 value) { return *this = u64(*this) + value; }
    SceKernelSysClock &operator -= (u64 value) { return *this = u64(*this) - value; }
    SceKernelSysClock &operator *= (u64 value) { return *this = u64(*this) * value; }
    SceKernelSysClock &operator /= (u64 value) { return *this = u64(*this) / value; }

    SceKernelSysClock operator + (u64 value) { return SceKernelSysClock(u64(*this) + value); }
    SceKernelSysClock operator - (u64 value) { return SceKernelSysClock(u64(*this) - value); }
    SceKernelSysClock operator * (u64 value) { return SceKernelSysClock(u64(*this) * value); }
    SceKernelSysClock operator / (u64 value) { return SceKernelSysClock(u64(*this) / value); }
} SceKernelSysClock;


typedef struct SceKernelMsgPacket
{
    struct SceKernelMsgPacket          *next;
    SceUChar                            msg_priority;
    SceUChar                            reserved[3];
} SceKernelMsgPacket;


typedef struct SceKernelStructureSize
{
    SceSize                             size;
} SceKernelStructureSize;

typedef struct SceKernelStructureName
{
    char                                name[31 /*SceUID_NAME_MAX*/ + 1];
} SceKernelStructureName;

typedef struct SceKernelStructureAttr
{
    SceUInt                             attributes;
} SceKernelStructureAttr;

typedef struct SceKernelHeapOptParam
:   SceKernelStructureSize
{
    int                                 alignment;
} SceKernelHeapOptParam;

typedef class SceKernelCallbackFunction
{
public:
    SceKernelCallbackFunction(u32 entry = 0) : m_entry(entry) {}
    SceKernelCallbackFunction(SceKernelCallbackFunction const &entry) : m_entry(entry.m_entry) {}

    operator u32() const { return m_entry; }

    //int operator()(int a0, int a1, void *a2) { return *(Memory::addr< int (int, int, void *) >(m_entry))(a0, a1, Memory::addr< void >(a2)); }

private:
    u32 m_entry;
} SceKernelCallbackFunction;


typedef struct SceKernelCallbackInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    SceUID                              thread_id;
    SceKernelCallbackFunction           callback;
    u32                                 cookie;
    int                                 notify_count;
    int                                 notify_arg;
} SceKernelCallbackInfo;


typedef struct SceKernelEventFlagInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    SceUInt                             initial_pattern;
    SceUInt                             current_pattern;
    int                                 waiting_threads;
} SceKernelEventFlagInfo;

typedef struct SceKernelEventFlagOptParam
:   SceKernelStructureSize
{
} SceKernelEventFlagOptParam;


typedef struct SceKernelFplInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    int                                 block_size;
    int                                 pool_blocks;
    int                                 free_blocks;
    int                                 waiting_threads;
} SceKernelFplInfo;

typedef struct SceKernelFplOptParam
:   SceKernelStructureSize
{
    SceSize                             alignment;
} SceKernelFplOptParam;


typedef struct SceKernelVplInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    int                                 pool_size;
    int                                 free_size;
    int                                 waiting_threads;
} SceKernelVplInfo;

typedef struct SceKernelVplOptParam
:   SceKernelStructureSize
{
} SceKernelVplOptParam;


typedef struct SceKernelMbxInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    int                                 waiting_threads;
    int                                 total_messages;
    SceKernelMsgPacket                 *top_packet;
} SceKernelMbxInfo;

typedef struct SceKernelMbxOptParam
:   SceKernelStructureSize
{
} SceKernelMbxOptParam;


typedef struct SceKernelMppInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    int                                 buffer_size;
    int                                 free_size;
    int                                 send_waiting_threads;
    int                                 recv_waiting_threads;
} SceKernelMppInfo;

typedef struct SceKernelMppOptParam
:   SceKernelStructureSize
{
} SceKernelMppOptParam;


typedef struct SceKernelSemaInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    int                                 initial_count;
    int                                 current_count;
    int                                 maximum_count;
    int                                 waiting_threads;
} SceKernelSemaInfo;

typedef struct SceKernelSemaOptParam
:   SceKernelStructureSize
{
} SceKernelSemaOptParam;


typedef struct SceKernelThreadInfo
:   SceKernelStructureSize
,   SceKernelStructureName
,   SceKernelStructureAttr
{
    int                                 status;
    void                               *entry;
    void                               *stack_base;
    int                                 stack_size;
    void                               *gp_reg;
    int                                 initial_priority;
    int                                 current_priority;
    int                                 wait_type;
    SceUID                              wait_id;
    int                                 wakeup_count;
    int                                 exit_status;
    SceKernelSysClock                   run_clocks;
    SceUInt                             intr_preempt_count;
    SceUInt                             thread_preempt_count;
    SceUInt                             release_count;
    int                                 notify_callback;
} SceKernelThreadInfo;

typedef struct SceKernelThreadOptParam
:   SceKernelStructureSize
{
} SceKernelThreadOptParam;

typedef struct SceKernelThreadRunStatus
:   SceKernelStructureSize
{
    int                                 status;
    int                                 current_priority;
    int                                 wait_type;
    int                                 wait_id;
    int                                 wakeup_count;
    SceKernelSysClock                   run_clocks;
    SceUInt                             intr_preempt_count;
    SceUInt                             thread_preempt_count;
    SceUInt                             release_count;
    int                                 notify_callback;
} SceKernelThreadRunStatus;


typedef SceUInt (*SceKernelAlarmHandler)(void *cookie);

typedef struct SceKernelAlarmInfo
:   SceKernelStructureSize
{
    SceKernelSysClock                   schedule;
    SceKernelAlarmHandler               handler;
    void                               *cookie;
} SceKernelAlarmInfo;

typedef SceUInt (*SceKernelVTimerHandler)(SceUID uid, SceKernelSysClock *base, SceKernelSysClock *current, void *cookie); 

typedef struct SceKernelVTimerInfo
:   SceKernelStructureSize
,   SceKernelStructureName
{
    int                                 active;
    SceKernelSysClock                   base;
    SceKernelSysClock                   current;
    SceKernelSysClock                   schedule;
    SceKernelVTimerHandler              handler;
    void                               *cookie;
} SceKernelVTimerInfo;

typedef struct SceKernelVTimerOptParam
:   SceKernelStructureSize
{
} SceKernelVTimerOptParam;

typedef struct SceKernelModuleInfo
:   SceKernelStructureSize
{
    char                                nsegment;
    char                                reserved[3];
    int                                 segmentaddr[4];
    int                                 segmentsize[4];
    unsigned int                        entry_addr;
    unsigned int                        gp_value;
    unsigned int                        text_addr;
    unsigned int                        text_size;
    unsigned int                        data_size;
    unsigned int                        bss_size;
    unsigned short                      attribute;
    unsigned char                       version[2];
    char                                name[27];
    char                                terminal;
} SceKernelModuleInfo;

typedef struct SceKernelLMOption
:   SceKernelStructureSize
{
    SceUID 	                            mpidtext;
    SceUID 	                            mpiddata;
    unsigned int 	                    flags;
    char 	                            position;
    char 	                            access;
    char 	                            creserved[2];
} SceKernelLMOption;

typedef struct SceKernelSMOption
:   SceKernelStructureSize
{
    SceUID 	                            mpidstack;
    SceSize 	                        stacksize;
    int                                 priority;
    unsigned int                        attribute;
} SceKernelSMOption;

typedef struct SceThreadContext
{
	unsigned int						type;
	unsigned int						gpr[31];
	unsigned int						fpr[32];
	unsigned int						fc31;
	unsigned int						hi; 
	unsigned int						lo;
	unsigned int						SR;
	unsigned int						EPC;
	unsigned int						field_114;
	unsigned int						field_118;
} SceThreadContext; 

typedef struct SceSCContext
{
	unsigned int						status;
	unsigned int						epc;
	unsigned int						sp;
	unsigned int						ra;
	unsigned int						k1;
	unsigned int						unk[3];
} SceSCContext;

typedef struct SceKernelLoadExecParam
:   SceKernelStructureSize
{
    SceUInt                             args;
    void                               *argp;
    char const                         *key;
} SceKernelLoadExecParam;

static inline int sceKernelCpuSuspendIntr() { return 0; }
static inline void sceKernelCpuResumeIntr(int) {}
static inline int sceKernelIsIntrContext() { return 0; }

#endif // kernel_types_h__
