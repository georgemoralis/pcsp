#include "stdafx.h"

#include "kernel_module.h"
#include "kernel_thread.h"

/// KernelModule /////////////////////////////////////////////////////////

void KernelModule::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size - 1);
}

// TODO
#if 0
KernelModule::KernelModule()
{
}
#endif
KernelModule::KernelModule(char const *name, u32 gp_value, u16 attribute, u16 version)
:   KernelObject(name)
,   m_nsegment(0)
,   m_entry_addr(0)
,   m_gp_value(gp_value)
,   m_text_addr(0)
,   m_text_size(0)
,   m_data_size(0)
,   m_bss_size(0)
,   m_attribute(attribute)
,   m_faked(false)
,   m_syscall_array(0)
,   m_syscall_count(0)
{
    ::memset(m_segmentaddr, 0, sizeof(m_segmentaddr));
    ::memset(m_segmentsize, 0, sizeof(m_segmentsize));
    *((u16 *)m_version) = version;
    m_module_idx = theKernelModuleManager.m_modules_per_index.size();
    theKernelModuleManager.m_modules.Append(this);
    theKernelModuleManager.m_modules_per_index.push_back(this);
}

KernelModule::KernelModule(char const *name, KernelSyscall const *syscall_array, int syscall_count)
:   KernelObject(name)
,   m_nsegment(0)
,   m_entry_addr(0)
,   m_gp_value(0)
,   m_text_addr(0)
,   m_text_size(0)
,   m_data_size(0)
,   m_bss_size(0)
,   m_attribute(0)
,   m_faked(true)
,   m_syscall_array(syscall_array)
,   m_syscall_count(syscall_count)
{
    ::memset(m_segmentaddr, 0, sizeof(m_segmentaddr));
    ::memset(m_segmentsize, 0, sizeof(m_segmentsize));
    *((u16 *)m_version) = 0x7FFF;
    m_module_idx = theKernelModuleManager.m_modules_per_index.size();
    theKernelModuleManager.m_modules.Append(this);
    theKernelModuleManager.m_modules_per_index.push_back(this);
}

KernelModule::~KernelModule()
{
    theKernelModuleManager.m_modules_per_index[this->m_module_idx] = 0;
    this->RemoveFromList();
}

// TODO
int KernelModule::Start(SceSize UNUSED(argsize), void *UNUSED(argp), int *UNUSED(status), SceKernelSMOption *UNUSED(option))
{
    return 0x80020001;
}

// TODO
int KernelModule::Stop(SceSize UNUSED(argsize), void *UNUSED(argp), int *UNUSED(status), SceKernelSMOption *UNUSED(option))
{
    return 0x80020001;
}

// TODO
int KernelModule::Unload()
{
    return 0x80020001;
}

// TODO
int KernelModule::QueryModuleInfo(SceKernelModuleInfo *UNUSED(info))
{
    return 0x80020001;
}


int KernelModule::GetSyscallIndex(u32 nid)
{
    for (u32 i = 0; i < m_syscall_count; ++i)
    {
        if (m_syscall_array[i].nid == nid)
        {
            return i;
        }
    }
    return -1;
}

KernelSyscall const *KernelModule::GetSyscall(u32 nid)
{
    for (u32 i = 0; i < m_syscall_count; ++i)
    {
        if (m_syscall_array[i].nid == nid)
        {
            return &m_syscall_array[i];
        }
    }
    return 0;
}

char const *KernelModule::GetSyscallName(u32 nid)
{
    KernelSyscall const *syscall = GetSyscall(nid);
    if (syscall)
    {
        return syscall->name;
    }
    return "[UNK]";
}

bool KernelModule::WriteSyscall(u32 nid, u32 address)
{
    int handlerIndex = GetSyscallIndex(nid);
    if (handlerIndex < 0)
    {
        Memory::memw(address + 0) = 0x03E00008; // JR $RA
        Memory::memw(address + 4) = 0x0003FFCC | (m_module_idx << 18); //invalid syscall
        return false;
    }
    Memory::memw(address + 0) = 0x03E00008; // JR $RA
    Memory::memw(address + 4) = 0x0000000C | (m_module_idx << 18) | (handlerIndex << 6);
    return true;
}


/// SyscallModule ////////////////////////////////////////////////////////

/// KernelModuleManager //////////////////////////////////////////////////

KernelModuleManager::KernelModuleManager()
{
    m_modules.Clear();
}

KernelModuleManager::~KernelModuleManager()
{
    Clear();
}

void KernelModuleManager::Clear()
{
    KernelModule *module = m_modules.First();

    while (module)
    {
        KernelModule *next = m_modules.Next(module);

        delete module;

        module = next;
    }

    m_modules_per_index.clear();
}

SceUID KernelModuleManager::Load(char const *UNUSED(pathname), int UNUSED(flags), SceKernelLMOption *UNUSED(option))
{
    return 0x80020001;
}

SceUID KernelModuleManager::Load(char const *UNUSED(pathname), SceUID UNUSED(block), SceOff UNUSED(offset))
{
    return 0x80020001;
}

SceUID KernelModuleManager::LoadByID(SceUID UNUSED(file), int UNUSED(flags), SceKernelLMOption *UNUSED(option))
{
    return 0x80020001;
}

SceUID KernelModuleManager::LoadByID(SceUID UNUSED(file), SceUID UNUSED(block), SceOff UNUSED(offset))
{
    return 0x80020001;
}

SceUID KernelModuleManager::LoadBufferUsbWlan(SceSize UNUSED(bufsize), void *UNUSED(buf), int UNUSED(flags), SceKernelLMOption *UNUSED(option))
{
    return 0x80020001;
}

int KernelModuleManager::StopUnloadSelf(SceSize UNUSED(argsize), void *UNUSED(argp), int *UNUSED(result), SceKernelSMOption *UNUSED(option))
{
    return 0x80020001;
}

int KernelModuleManager::StopUnloadSelf(int UNUSED(status), SceSize UNUSED(argsize), void *UNUSED(argp), int *UNUSED(result), SceKernelSMOption *UNUSED(option))
{
    return 0x80020001;
}


int KernelModuleManager::GetModuleId()
{
#ifdef USE_NEW_THREADMAN
    KernelThread *thread = GetCurrentThread();

    if (thread)
    {
        return thread->GetApiModuleId();
    }
#endif
    return 0x80020001;
}

int KernelModuleManager::GetModuleIdByAddress(u32 addr)
{
    KernelModule *module = m_modules.First();

    while (module)
    {
        // TODO : what addr is really ?
        (void)addr;

        module = m_modules.Next(module);
    }

    return 0x800200D3;
}

int KernelModuleManager::GetModuleIdList(SceUID *readbuf, int readbufsize, int *idcount)
{
    KernelModule *module = m_modules.First();

    (void)idcount;

    while (readbufsize && module)
    {
        *readbuf = module->GetUid();
        readbufsize--;
        readbuf++;

        module = m_modules.Next(module);
    }

    return 0;
}

int KernelModuleManager::GetModuleIndex(char const *moduleName)
{
    KernelModule *module = m_modules.First();

    while (module)
    {
        if (::strcmp(moduleName, module->m_name) == 0)
        {
            return module->m_module_idx;
        }

        module = m_modules.Next(module);
    }

    return -1;
}

int KernelModuleManager::GetSyscallIndex(int moduleIndex, u32 nid)
{
    KernelModule *module = m_modules_per_index[moduleIndex];

    for (u32 i = 0; i < module->m_syscall_count; ++i)
    {
        if (module->m_syscall_array[i].nid == nid)
        {
            return i;
        }
    }
    return -1;
}

KernelSyscall const *KernelModuleManager::GetSyscall(char const *moduleName, u32 nid)
{
    int moduleIndex = GetModuleIndex(moduleName);
    if (moduleIndex >= 0)
    {
        KernelModule *module = m_modules_per_index[moduleIndex];

        for (u32 i = 0; i < module->m_syscall_count; ++i)
        {
            if (module->m_syscall_array[i].nid == nid)
            {
                return &module->m_syscall_array[i];
            }
        }
    }
    return 0;
}

char const *KernelModuleManager::GetSyscallName(int moduleIndex, u32 nid)
{
    if ((u32)moduleIndex < m_modules_per_index.size())
    {
        KernelModule *module = m_modules_per_index[moduleIndex];
        if (module)
        {
            return module->GetSyscallName(nid);
        }
    }
    return "[UNK]";
}

char const *KernelModuleManager::GetSyscallName(char const *moduleName, u32 nid)
{
    KernelSyscall const *syscall = GetSyscall(moduleName, nid);
    if (syscall)
    {
        return syscall->name;

    }
    return "[UNK]";
}

char const *KernelModuleManager::GetModuleName(int moduleIndex)
{
    return m_modules_per_index[moduleIndex]->m_name;
}

void KernelModuleManager::WriteSyscall(char const *moduleName, u32 nid, u32 address)
{
    if (nid == 0)
    {
        Memory::memw(address + 0) = 0x03E00008; // JR $RA
        Memory::memw(address + 4) = 0x00000000; // NOP
        return;
    }

    int moduleIndex = GetModuleIndex(moduleName);
    if (moduleIndex >= 0)
    {
        if (!m_modules_per_index[moduleIndex]->WriteSyscall(nid, address))
        {
            errorf(hlemisc, "Unknown nid in module '%s' : nid = 0x%08X, address = 0x%08X", moduleName, nid, address);
        }
    }
    else
    {
        errorf(hlemisc, "Unknown module '%s' : nid = 0x%08X, address = 0x%08X", moduleName, nid, address);
        Memory::memw(address + 0) = 0x03E00008; // JR $RA
        Memory::memw(address + 4) = 0x0003FFCC; // invalid syscall
    }
}

void KernelModuleManager::CreateSyscallsModule(char const *moduleName, u16 version, KernelSyscall const *syscall_array, u32 syscall_count)
{
    (void)version;

    if (GetModuleIndex(moduleName) == -1)
    {
        new KernelModule(moduleName, syscall_array, syscall_count);
    }
}

void KernelModuleManager::DeleteSyscallsModule(char const *moduleName)
{
    int index = GetModuleIndex(moduleName);
    if (index != -1)
    {
        delete this->m_modules_per_index[index];
    }
}

bool KernelModuleManager::SyscallsModuleExists(char const *moduleName)
{
    return GetModuleIndex(moduleName) != -1;
}

#if 0
struct PspModuleInfo
{
    // 0, 0, 1, 1 ?
    u16 moduleAttrs; //0x0000 User Mode, 0x1000 Kernel Mode
    u16 moduleVersion;
    // 28 bytes of module name, packed with 0's.
    char name[28];
    u32 gp;           // ptr to MIPS GOT data  (global offset table)
    u32 libent;       // ptr to .lib.ent section 
    u32 libentend;    // ptr to end of .lib.ent section 
    u32 libstub;      // ptr to .lib.stub section 
    u32 libstubend;   // ptr to end of .lib.stub section 
};

struct PspLibStubEntry
{
    // pointer to module name (will be in .rodata.sceResident section)
    unsigned long moduleNameSymbol;
    // mod version??
    unsigned short version;
    unsigned short val1;
    unsigned char val2; // 0x5
    unsigned char val3;
    // number of function symbols
    unsigned short numFuncs;
    // each symbol has an associated nid; nidData is a pointer
    // (in .rodata.sceNid section) to an array of longs, one
    // for each function, which identifies the function whose
    // address is to be inserted.
    //
    // The hash is the first 4 bytes of a SHA-1 hash of the function
    // name.  (Represented as a little-endian long, so the order
    // of the bytes is reversed.)
    unsigned long nidData;
    // the address of the function stubs where the function address jumps
    // should be filled in
    unsigned long firstSymAddr;
};

KernelModule *__KernelLoadELFFromPtr(u8 const *elfImage, u32 loadAddress)
{
    if (*(u32*)elfImage != 0x464c457f)
    {
        DebugBreak();
    }

    ElfReader *reader = new ElfReader((void *)elfImage);

    if (!reader->LoadInto(loadAddress))
    {
        DebugBreak();
    }

    struct libent
    {
        u32 exportName; //default 0
        u16 bcdVersion;
        u16 moduleAttributes;
        u8  exportEntrySize;
        u8  numVariables;
        u16 numFunctions;
        unsigned long __entrytableAddr;
    };

    SectionID entSection  = reader->GetSectionByName(".lib.ent");
    SectionID textSection = reader->GetSectionByName(".text");
    SectionID dataSection = reader->GetSectionByName(".data");
    SectionID bssSection  = reader->GetSectionByName(".bss");

    u32 sceResidentAddr = 0;
    u32 moduleInfoAddr  = 0;

    u32 textStart = reader->GetSectionAddr(textSection);
    u32 textSize  = reader->GetSectionSize(textSection);
    u32 dataSize  = reader->GetSectionSize(dataSection);
    u32 bssSize   = reader->GetSectionSize(bssSection);

    SectionID sceResidentSection   = reader->GetSectionByName(".rodata.sceResident");
    SectionID sceModuleInfoSection = reader->GetSectionByName(".rodata.sceModuleInfo");

    bool hasSymbols = false;
    bool dontadd    = false;

    sceResidentAddr = reader->GetSectionAddr(sceResidentSection);
    moduleInfoAddr  = reader->GetSectionAddr(sceModuleInfoSection);

    struct PspResidentData 
    {
        unsigned long l1;             // unknown 0xd632acdb
        unsigned long l2;             // unknown 0xf01d73a7
        unsigned long startAddress;   // address of _start
        unsigned long moduleInfoAddr; // address of sceModuleInfo struct
    };

    Log::loader.info("Resident data addr: %08X", sceResidentAddr);

    PspModuleInfo *modinfo = Memory::addr< PspModuleInfo >(moduleInfoAddr);

    KernelModule *module = new KernelModule(modinfo->name, modinfo->gp, modinfo->moduleAttrs, modinfo->moduleVersion);

    module->m_text_addr = textStart;
    module->m_text_size = textSize;
    module->m_data_size = dataSize;
    module->m_bss_size  = bssSize;

    Log::loader.info("Module %s: %08x %08x %08x", modinfo->name, modinfo->gp, modinfo->libent, modinfo->libstub);

    int numModules = (modinfo->libstubend - modinfo->libstub)/sizeof(PspLibStubEntry);

    Log::loader.info("# Modules: %i", numModules);
    Log::loader.info("===================================================");

    PspLibStubEntry *entry = Memory::addr< PspLibStubEntry >(modinfo->libstub);

    int numSyms = 0;
    for (int m = 0; m < numModules; m++)
    {
        char *modulename = Memory::addr< char >(entry[m].moduleNameSymbol);
        u32  *nidDataPtr = Memory::addr< u32  >(entry[m].nidData);
        u32  *stubs      = Memory::addr< u32  >(entry[m].firstSymAddr);

        Log::loader.info("Importing Module %s, stubs at %08x", modulename, entry[m].firstSymAddr);

        for (int i = 0; i < entry[m].numFuncs; i++)
        {
            u32 addrToWriteSyscall = entry[m].firstSymAddr + i*8;
            Log::loader.info("%s : %08x", hle::GetFuncName(modulename, nidDataPtr[i]), addrToWriteSyscall);
            
            //write a syscall here
            hle::WriteSyscall(modulename, nidDataPtr[i], addrToWriteSyscall);
            if (!dontadd)
            {
                char temp[256];
                _snprintf(temp,255,"zz_%s", hle::GetFuncName(modulename, nidDataPtr[i]));
            }
            numSyms++;
        }
        Log::loader.info("-------------------------------------------------------------");
    }

    return new KernelModule(modinfo->name, reader->GetEntryPoint(), modinfo->gp, textStart, textSize,);
}
#endif

#if 0
int KernelModule::LoadElf(u32 elf)
{
    int i, j, n, minaddr, maxaddr;

    Elf32_Ehdr *ehdr = Memory::addr< Elf32_Ehdr >(elf);
    Elf32_Phdr *phdr = Memory::addr< Elf32_Phdr >(elf + ehdr->e_phoff);

    for (i = n = ehdr->e_phnum; i > 0; --i)
    {
        if (phdr[n - i].p_type == PT_LOAD)
        {
            break;
        }
    }

    this->m_segmentaddr[0] = execFileInfo->unk_24;
    this->m_segmentsize[0] = phdr[n - i].p_filesz;
    
    j = 1;
    
    if (i > 1 && phdr[n - i + 1].p_type == PT_LOAD)
    {
        for (; j < i && phdr[n - i + j].p_type == PT_LOAD; ++j)
        {
            this->m_segmentaddr[j] = execFileInfo->unk_24 + phdr[n - i + j].p_vaddr;
            this->m_segmentsize[j] = phdr[n - i + j].p_filesz;
        }
    }

    this->m_nsegment = j;

    minaddr = -1;
    maxaddr = 0;
    
    for (j = 0; j < n; ++j)
    {
        if(phdr[j].p_type == PT_LOAD)
        {
            if (minaddr == -1)
            {
                minaddr = phdr[j].p_vaddr;
            }

            maxaddr = phdr[j].p_vaddr + phdr[j].p_memsz;
        }
    }

    SceUID memuid = sysmem::hleKernelAllocPartitionMemory(this->m_partition_uid, "SceLoadElfBlock", 2, ((maxaddr + 255) & -256) - (minaddr & -256), (minaddr & -256));
    
    this->m_memblock_uid = memuid;

    if (memuid < 0)
    {
        return memuid;
    }

    //sysmem::hleKernelGetBlockHeadAddr(memuid);

    for (j = 0; j < n; ++j)
    {
        if (phdr[j].p_type == PT_LOAD)
        {
            if (phdr[j].p_vaddr != elf + phdr[j].p_offset)
            {
                memcpy(Memory::addr< u8 >(phdr[j].p_vaddr), Memory::addr< u8 >(elf) + phdr[j].p_offset, phdr[j].p_filesz);
            }

            if (phdr[j].p_filesz < phdr[j].p_memsz)
            {
                memset(Memory::addr< u8 >(phdr[j].p_vaddr) + phdr[j].p_filesz, 0, phdr[j].p_memsz - phdr[j].p_filesz);
            }
        }
    }

    return 0;
}

int KernelModule::LoadRelElf(u32 elf)
{
}

#endif

