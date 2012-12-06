#pragma once
#include "kernel_object.h"

#include "common_linked_list.h"
#if 0
#include "kernel_elf.h"
#include "kernel_prx.h"
#endif
struct KernelModule;
struct KernelLibImport;
struct KernelLibExport;

typedef LinkedList< KernelModule    > KernelModuleList;
typedef LinkedList< KernelLibImport > KernelLibImportList;
typedef LinkedList< KernelLibExport > KernelLibExportList;

#if 0
struct KernelLibImport
:   KernelLibImportList::Node      
{
    char            name[PSP_LIB_MAX_NAME];
    u32             addr;
    KernelLibImport stub;
    PrxEntry        funcs[PSP_MAX_F_ENTRIES];
    int             f_count;
    PrxEntry        vars[PSP_MAX_V_ENTRIES];
    int             v_count;
};

struct KernelLibExport
:   KernelLibExportList::Node      
{
    char            name[PSP_LIB_MAX_NAME];
    u32             addr;
    KernelLibExport stub;
    PrxEntry        funcs[PSP_MAX_F_ENTRIES];
    int             f_count;
    PrxEntry        vars[PSP_MAX_V_ENTRIES];
    int             v_count;
};

struct PrxModule
{
    char             name[PSP_MODULE_MAX_NAME+1];
    PrxModuleInfo    info;
    u32              addr;
    KernelLibExport *exp_head;
    KernelLibImport *imp_head;
};

struct KernelModule;
#endif

typedef LinkedList< KernelModule > KernelModuleList;

typedef void SyscallHandler(AlContext &context);

struct KernelSyscall
{
    u32             nid;
    SyscallHandler *handler;
    char const     *name;
    char const     *format;
    LogCategory    *log;
};

struct KernelModule
:   KernelObject
,   KernelModuleList::Node
{
    declare_kernel_type(KernelModule, KernelObject);

    char 			m_nsegment;
    char 			m_reserved[3];
    int 			m_segmentaddr[4];
    int 			m_segmentsize[4];
    unsigned int 	m_entry_addr;
    unsigned int 	m_gp_value;
    unsigned int 	m_text_addr;
    unsigned int 	m_text_size;
    unsigned int 	m_data_size;
    unsigned int 	m_bss_size;
    unsigned short  m_attribute;
    unsigned char   m_version[2];

    bool            m_faked;
    SceUID          m_partition_uid;
    SceUID          m_memblock_uid;

    u32                  m_syscall_count;
    KernelSyscall const *m_syscall_array;
    int                  m_module_idx;

#if 0
    KernelModule();
#endif
    KernelModule(char const *name, u32 gp_value, u16 attribute, u16 version);
    KernelModule(char const *name, KernelSyscall const *syscall_array, int syscall_count);
    ~KernelModule();

    virtual int   Start(SceSize argsize, void *argp, int *status, SceKernelSMOption *option);
    virtual int   Stop(SceSize argsize, void *argp, int *status, SceKernelSMOption *option);
    virtual int   Unload();
    virtual int   QueryModuleInfo(SceKernelModuleInfo *info);

    int                  GetModuleIndex() { return m_module_idx; }
    int                  GetSyscallIndex(u32 nid);
    KernelSyscall const *GetSyscall(u32 nid);
    char const          *GetSyscallName(u32 nid);
    bool                 WriteSyscall(u32 nid, u32 address);

protected:
    int           LoadElf(u32 elf);
    int           LoadRelElf(u32 elf);
};

struct KernelModuleManager
{
    KernelModuleList              m_modules;
    std::vector< KernelModule * > m_modules_per_index;

    KernelModuleManager();
    ~KernelModuleManager();

    SceUID Load(char const *pathname, int flags, SceKernelLMOption *option);
    SceUID Load(char const *pathname, SceUID block, SceOff offset);
    SceUID LoadByID(SceUID file, int flags, SceKernelLMOption *option);
    SceUID LoadByID(SceUID file, SceUID block, SceOff offset);
    SceUID LoadBufferUsbWlan(SceSize bufsize, void *buf, int flags, SceKernelLMOption *option);

    int StopUnloadSelf(SceSize argsize, void *argp, int *result, SceKernelSMOption *option);
    int StopUnloadSelf(int status, SceSize argsize, void *argp, int *result, SceKernelSMOption *option);

    int GetModuleId();
    int GetModuleIdByAddress(u32 addr);
    int GetModuleIdList(SceUID *readbuf, int readbufsize, int *idcount);

    int                  GetModuleIndex(char const *moduleName);
    char const          *GetModuleName(int moduleIndex);
    int                  GetSyscallIndex(int moduleIndex, u32 nid);
    KernelSyscall const *GetSyscall(char const *moduleName, u32 nid);
    char const          *GetSyscallName(int moduleIndex, u32 nid);
    char const          *GetSyscallName(char const *moduleName, u32 nid);
    void                 WriteSyscall(char const *moduleName, u32 nid, u32 address);

    void                 CreateSyscallsModule(char const *moduleName, u16 version, KernelSyscall const *syscall_array, u32 syscall_count);
    void                 DeleteSyscallsModule(char const *moduleName);
    bool                 SyscallsModuleExists(char const *moduleName);
    void                 Clear();
};

extern KernelModuleManager theKernelModuleManager;

