#include "PCSPCommon.h"
#include "MemoryMap.h"
#include "Memory.h"

/*TODO*/  // Log Memory::log;

u8 *Memory::scratchPad = NULL;
u8 *Memory::videoMemory = NULL;
u8 *Memory::mainMemory = NULL;
bool Memory::wasException;

static u8 *guardMemory = NULL;
static u8 **pageTable = NULL;

static bool guardEnabled = false;
static bool exceptionsEnabled = false;

static void makePageTable() {
    using namespace Memory;

    u32 page, i;

    for (i = 0; i < PageCount; ++i) pageTable[i] = guardMemory;

    page = MemoryMap::START_SCRATCHPAD >> PageShift;
    for (i = 0; i < (MemoryMap::SIZE_SCRATCHPAD >> PageShift); ++i) {
        u8 *addr = scratchPad + (i << PageShift);
        pageTable[Mirror0 + page + i] = addr;
        pageTable[Mirror1 + page + i] = addr;
        pageTable[Mirror2 + page + i] = addr;
    }

    page = MemoryMap::START_VRAM >> PageShift;
    for (i = 0; i < (MemoryMap::SIZE_VRAM >> PageShift); ++i) {
        u8 *addr = videoMemory + (i << PageShift);
        pageTable[Mirror0 + page + i] = addr;
        pageTable[Mirror1 + page + i] = addr;
        pageTable[Mirror2 + page + i] = addr;
    }

    page = MemoryMap::START_RAM >> PageShift;
    for (i = 0; i < (MemoryMap::SIZE_RAM >> PageShift); ++i) {
        u8 *addr = mainMemory + (i << PageShift);
        pageTable[Mirror0 + page + i] = addr;
        pageTable[Mirror1 + page + i] = addr;
        pageTable[Mirror2 + page + i] = addr;
    }
}

static PVOID guardHandler = NULL;

static LONG WINAPI memoryGuard(EXCEPTION_POINTERS *ExceptionInfo) {
    using namespace Memory;

    if (exceptionsEnabled) return EXCEPTION_CONTINUE_SEARCH;

    if (ExceptionInfo->ExceptionRecord->ExceptionCode != EXCEPTION_ACCESS_VIOLATION) return EXCEPTION_CONTINUE_SEARCH;

    uintptr_t addr = ExceptionInfo->ExceptionRecord->ExceptionInformation[1];
    intptr_t tmp;

    // PageTable miss
    tmp = addr - (uintptr_t)guardMemory;
    if (tmp >= 0 && tmp < (PageSize * 2)) goto psp_err;

    // Invalid page cross in ScratchPad area
    tmp = addr - (uintptr_t)(scratchPad + MemoryMap::SIZE_SCRATCHPAD);
    if (tmp >= 0 && tmp < PageSize) goto psp_err;

    // Invalid page cross in VideoMemory area
    tmp = addr - (uintptr_t)(videoMemory + MemoryMap::SIZE_VRAM);
    if (tmp >= 0 && tmp < PageSize) goto psp_err;

    // Invalid page cross in MainMemory area
    tmp = addr - (uintptr_t)(mainMemory + MemoryMap::SIZE_RAM);
    if (tmp >= 0 && tmp < PageSize) goto psp_err;

    return EXCEPTION_CONTINUE_SEARCH;

psp_err:
/*TODO*/  //    Error::clear();
    enableGuard(false);
    wasException = true;
    return EXCEPTION_CONTINUE_EXECUTION;
}

static void *VAlloc(u32 size) { return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); }

static void translator(u32 u, EXCEPTION_POINTERS *exp) {
    if (exp->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) throw std::exception("Access violation");
}

bool Memory::initialize() {
    assert(scratchPad == NULL);
/*TODO*/  //    log = Log("Memory");

    scratchPad = (u8 *)VAlloc(MemoryMap::SIZE_SCRATCHPAD + PageSize);
    if (scratchPad == NULL) goto out_of_mem;

    videoMemory = (u8 *)VAlloc(MemoryMap::SIZE_VRAM + PageSize);
    if (videoMemory == NULL) goto out_of_mem;

    mainMemory = (u8 *)VAlloc(MemoryMap::SIZE_RAM + PageSize);
    if (mainMemory == NULL) goto out_of_mem;

    guardMemory = (u8 *)VAlloc(PageSize * 2);
    if (guardMemory == NULL) goto out_of_mem;

    pageTable = (u8 **)VAlloc(sizeof(u8 *) * PageCount);
    if (pageTable == NULL) goto out_of_mem;

    guardHandler = AddVectoredExceptionHandler(0, memoryGuard);
    if (guardHandler == NULL) {
        Memory::finalize();
/*TODO*/  //        Error::set("Failed to add vectored exception handler!");
        return false;
    }

    if (!enableGuard(true)) {
        Memory::finalize();
        return false;
    }

    _set_se_translator(translator);

    exceptionsEnabled = true;
    wasException = false;

    makePageTable();
    return true;

out_of_mem:
    Memory::finalize();
/*TODO*/  //    Error::set("Out of memory!");
    return false;
}

void Memory::finalize() {
    if (scratchPad) {
        VirtualFree(scratchPad, 0, MEM_RELEASE);
        scratchPad = NULL;
    }
    if (videoMemory) {
        VirtualFree(videoMemory, 0, MEM_RELEASE);
        videoMemory = NULL;
    }
    if (mainMemory) {
        VirtualFree(mainMemory, 0, MEM_RELEASE);
        mainMemory = NULL;
    }
    if (guardMemory) {
        VirtualFree(guardMemory, 0, MEM_RELEASE);
        guardMemory = NULL;
    }
    if (pageTable) {
        VirtualFree(pageTable, 0, MEM_RELEASE);
        pageTable = NULL;
    }
    if (guardHandler) {
        RemoveVectoredExceptionHandler(guardHandler);
        guardHandler = NULL;
    }
}

bool Memory::enableGuard(bool enable) {
    if (guardEnabled == enable) return true;

    DWORD dwOldProtect;
    BOOL status;

    status = VirtualProtect(guardMemory, PageSize * 2, enable ? PAGE_NOACCESS : PAGE_READWRITE, &dwOldProtect);
    if (status == FALSE) goto error;

    status = VirtualProtect(scratchPad + MemoryMap::START_SCRATCHPAD, PageSize, enable ? PAGE_NOACCESS : PAGE_READWRITE,
                            &dwOldProtect);
    if (status == FALSE) goto error;

    status = VirtualProtect(videoMemory + MemoryMap::SIZE_VRAM, PageSize, enable ? PAGE_NOACCESS : PAGE_READWRITE,
                            &dwOldProtect);
    if (status == FALSE) goto error;

    status = VirtualProtect(mainMemory + MemoryMap::SIZE_RAM, PageSize, enable ? PAGE_NOACCESS : PAGE_READWRITE,
                            &dwOldProtect);
    if (status == FALSE) goto error;

    guardEnabled = enable;
    return true;

error:
/*TODO*/  // Error::set("Failed to change page protection status!");
    return false;
}

void Memory::enableExceptions(bool enable) { exceptionsEnabled = enable; }

void Memory::reset() {
    assert(scratchPad != NULL);

    memset(scratchPad, 0, MemoryMap::START_SCRATCHPAD);
    memset(videoMemory, 0, MemoryMap::SIZE_VRAM);
    memset(mainMemory, 0, MemoryMap::SIZE_VRAM);

    wasException = false;
}

u8 *Memory::getPointer(u32 addr) { return &(pageTable[addr >> PageShift][addr & PageMask]); }

bool Memory::isValid(u32 addr) { return pageTable[addr >> PageShift] != guardMemory; }

u8 Memory::read8(u32 addr) { return pageTable[addr >> PageShift][addr & PageMask]; }

u16 Memory::read16(u32 addr) { return *(u16 *)&(pageTable[addr >> PageShift][addr & PageMask]); }

u32 Memory::read32(u32 addr) { return *(u32 *)&(pageTable[addr >> PageShift][addr & PageMask]); }

void Memory::write8(u32 addr, u8 value) { pageTable[addr >> PageShift][addr & PageMask] = value; }

void Memory::write16(u32 addr, u16 value) { *(u16 *)&(pageTable[addr >> PageShift][addr & PageMask]) = value; }

void Memory::write32(u32 addr, u32 value) { *(u32 *)&(pageTable[addr >> PageShift][addr & PageMask]) = value; }
