#include "stdafx.h"
#include "memory/memory.h"

static u32             display_start = 0;
static u32             display_end   = 0;
static bool            display_dirty = false;
//static CriticalSection display_lock;
template< typename T > bool __inrange(T a, T x, T b) { return a <= x && x < b; }
bool Memory::Initialize()
{
	if (Memory::Reserve() == 0)
	{
		Memory::Terminate();
		return false;
	}

	return true;
}

void Memory::Terminate()
{
	if (Memory::pointer)
	{
		Memory::Release();
	}
}

void Memory::Reset()
{
    ::memset((void*)Memory::mram, 0, MRAM_SIZE);
    ::memset((void*)Memory::vram, 0, VRAM_SIZE);
    ::memset((void*)Memory::sram, 0, SRAM_SIZE);
}

#define PAGE64K_ALIGN(x) ((x + 65535) & ~65535)

void *Memory::pointer = 0;

#if defined(__win32__) && !defined(__cygwin__)
static HANDLE psp_memory_handle = INVALID_HANDLE_VALUE;
#else
static int psp_memory_handle = -1;
#endif

/// mapping/unmapping a view

static __forceinline void *map_view(u32 address, u32 offset, u32 size)
{
#if defined(__win32__) && !defined(__cygwin__)
    return ::MapViewOfFileEx(psp_memory_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, offset, size, (LPVOID)(reinterpret_cast< u32 >(Memory::pointer) + address));
#else
    return ::mmap((void *)(reinterpret_cast< char* >(Memory::pointer) + address), size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_FIXED, psp_memory_handle, offset);
#endif
}

static __forceinline void unmap_view(u32 address, u32 offset, u32 size)
{
#if defined(__win32__) && !defined(__cygwin__)
    (void)size;
    (void)offset;
    ::UnmapViewOfFile((LPVOID)(reinterpret_cast< u32 >(Memory::pointer) + address));
#else
    ::munmap((void *)(reinterpret_cast< char* >(Memory::pointer) + address), size);
#endif
}

/// grabbing a virtual memory space

static __forceinline void *grab_view(unsigned int size)
{
    void *base = 0;
#if defined(__win32__) && !defined(__cygwin__)
    psp_memory_handle = ::CreateFileMappingA(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE + ECTX_SIZE + GARB_SIZE - 1), 0);
    if (psp_memory_handle == INVALID_HANDLE_VALUE)
    {
        return 0;
    }
    base = ::VirtualAlloc((LPVOID)0, size, MEM_RESERVE, PAGE_NOACCESS);
    if (base)
    {
        ::VirtualFree(base, 0, MEM_RELEASE);
    }
    else
    {
        ::CloseHandle(psp_memory_handle);
        psp_memory_handle = INVALID_HANDLE_VALUE;
    }
#else
    psp_memory_handle = ::shm_open("/psp-memory", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (psp_memory_handle != -1)
    {
        ::ftruncate(psp_memory_handle, size);
        base = ::mmap(0, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, 0, 0);
        if (base == MAP_FAILED)
        {
            base = 0;
            ::shm_unlink((const char *)psp_memory_handle);
            psp_memory_handle = -1;
        }
        else
        {
            ::munmap(base, size);
        }
    }
#endif
    return base;
}

/// mapping/unmapping a segment

static bool mapped_segment(u32 address, u32 times, u32 offset, u32 size, bool watch_changes = false)
{
    if (!(size & -65536)) // geez! windows has a pretty annoying restriction about the size of a virtual page
    {
        u32 total = times * size;
        size = 65536;
        times = (total + 65535) / 65536;
    }

    void *buffer = map_view(address, offset, size);

    if (!buffer)
    {
        return false;
    }

    if (watch_changes)
    {
        Memory::WatchDirtyPages(address, address + size);
    }

    for (unsigned int i = 1; i < times; ++i)
    {
        if (!map_view((address += size), offset, size))
        {
            return false;
        }

        if (watch_changes)
        {
            Memory::WatchDirtyPages(address, address + size);
        }
    }

    return true;
}

static bool unused_segment(u32 start, u32 end)
{
    // map a mirror of 64KB pages to eat read/write in "unmapped" memory instead of raising an exception
    u32 address = PAGE64K_ALIGN(start);
    u32 times = (end - address + 65535) / 65536;
    if (mapped_segment(address, times, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE), 65536))
    {
        Memory::GuardPages(address, address + 65536 * times);
        return true;
    }
    return false;
}

static __forceinline void unmap_segment(u32 address, u32 times, u32 offset, u32 size)
{
    if (!(size & -65536)) // geez! windows has a pretty annoying restriction about the size of a virtual page
    {
        u32 total = times * size;
        size = 65536;
        times = (total + 65535) / 65536;
    }

    unmap_view(address, offset, size);

    for (unsigned int i = 1; i < times; ++i)
    {
        unmap_view((address += size), offset, size);
    }
}

static __forceinline void unmap_segment(u32 start, u32 end)
{
    // unmap a mirror of 64KB pages in "unmapped" memory
    u32 address = PAGE64K_ALIGN(start);
    u32 times = (end - address + 65535) / 65536;
    unmap_segment(address, times, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE), 65536);
}



void *Memory::Reserve()
{
    Memory::EnableExceptions(true);

    // we need to allocate thrice the necessary virtual space
    // because we need to free it before mapping our segments in it
    // and another thread can try to steal a chunk of it
    Memory::pointer = grab_view(VMEM_SIZE*3);

    if (!Memory::pointer)
    {
        return 0;
    }

    // we want to map in the middle of the ex-allocated virtual space
    // in case of another thread tries to steal a chunk of our virtual space
    // in the beginning or in the end
    Memory::pointer = (void *)((char*)Memory::pointer + VMEM_SIZE/2);

    //      0×00010000      0×00004000 (16 KiB)     Scratch pad
    //      0×04000000      0×00200000 (2 MiB)      Lower video ram
    //      0×04200000      0×00200000 (2 MiB)      Upper video ram (SLIM only) NOT MAPPED HERE FOR COMPATIBILITY SAFETY
    //      0×08000000      0×02000000 (32 MiB)     Lower main ram
    //      0×0A000000      0×02000000 (32 MiB)     Upper main ram (SLIM only)
    if
        (
        true
        && unused_segment(0x00000000, 0x00010000                               )
        && mapped_segment(0x00010000, 1, MRAM_SIZE + VRAM_SIZE, SRAM_SIZE      )
        && unused_segment(0x00014000, 0x04000000                               )
        && mapped_segment(0x04000000, 4, MRAM_SIZE            , VRAM_SIZE      )
        && mapped_segment(0x04800000, 4, MRAM_SIZE            , VRAM_SIZE      )
        && unused_segment(0x05000000, 0x08000000                               )
        && mapped_segment(0x08000000, 1, 0                    , MRAM_SIZE      )
        && unused_segment(0x0C000000, 0x10000000                               )

        && unused_segment(0x10000000, 0x10010000                               )
        && mapped_segment(0x10010000, 1, MRAM_SIZE + VRAM_SIZE, SRAM_SIZE      )
        && unused_segment(0x10014000, 0x14000000                               )
        && mapped_segment(0x14000000, 4, MRAM_SIZE            , VRAM_SIZE      )
        && mapped_segment(0x14800000, 4, MRAM_SIZE            , VRAM_SIZE      )
        && unused_segment(0x15000000, 0x18000000                               )
        && mapped_segment(0x18000000, 1, 0                    , MRAM_SIZE      )
        && unused_segment(0x1C000000, 0x20000000                               )
        )
    {
        return Memory::pointer;
    }

    return 0;
}

void Memory::Release()
{
    if (Memory::pointer)
    {
        Memory::EnableExceptions(false);

        unmap_segment(0x00000000, 0x00010000);
        unmap_segment(0x00010000, 1, MRAM_SIZE + VRAM_SIZE, SRAM_SIZE);
        unmap_segment(0x00014000, 0x04000000                         );
        unmap_segment(0x04000000, 4, MRAM_SIZE            , VRAM_SIZE);
        unmap_segment(0x04800000, 4, MRAM_SIZE            , VRAM_SIZE);
        unmap_segment(0x08000000, 1, 0                    , MRAM_SIZE);
        unmap_segment(0x0C000000, 0x10000000                         );

#if defined(__win32__) && !defined(__cygwin__)
        if (psp_memory_handle != INVALID_HANDLE_VALUE)
        {
            ::CloseHandle(psp_memory_handle);
            psp_memory_handle = INVALID_HANDLE_VALUE;
        }
#else
        if (psp_memory_handle != -1)
        {
            ::shm_unlink((const char*)psp_memory_handle);
            psp_memory_handle = -1;
        }
#endif
    }
}

#if defined(__win32__) && !defined(__cygwin__) && (defined(__arch_x86_32__) || defined(__arch_x86_64__))

static PVOID veh_handler = 0;

static long CALLBACK veh_watch_changes(PEXCEPTION_POINTERS exc)
{
    static LPVOID invalid_address = 0;

    switch (exc->ExceptionRecord->ExceptionCode)
    {
    case STATUS_SINGLE_STEP: // exc->ContextRecord->EFlags |= 0x100; --> catch the next instruction !
        // entered here only when in Release, so just ignore this exception !

        if (invalid_address)
        {
            DWORD old_flags;
            ::VirtualProtect(LPVOID(u32(invalid_address) & -4096), 4096, PAGE_GUARD|PAGE_READWRITE, &old_flags);

            invalid_address = 0;
        }

        return EXCEPTION_CONTINUE_EXECUTION;

    case STATUS_GUARD_PAGE_VIOLATION:
        {
            LPVOID address = LPVOID(exc->ExceptionRecord->ExceptionInformation[1]);
            u32 offset = u32(address) - u32(Memory::pointer);
            if (offset < VMEM_SIZE)
            {
                // in Debug, single step at the next instruction so you can see what issued this exception
                exc->ContextRecord->EFlags |= 0x100;

                if (__inrange(0x00000000U, offset, 0x00010000U) &&
                    __inrange(0x00014000U, offset, 0x04000000U) &&
                    __inrange(0x05000000U, offset, 0x08000000U) &&
                    __inrange(0x0C000000U, offset, 0x10000000U))
                {
                    invalid_address = address;

                    exc->ContextRecord->EFlags |= 1; // CF = 1 --> IsAddressValid returns false 

                    forcef(memory, "Invalid address at psp address 0x%08X.", offset);
                }
                else
                {
                    forcef(memory, "Mirrored address at psp address 0x%08X.", offset);
                }

                return EXCEPTION_CONTINUE_EXECUTION;
            }
        }
        break;

    case STATUS_ACCESS_VIOLATION:
        {
            LPVOID address = LPVOID(exc->ExceptionRecord->ExceptionInformation[1]);
            u32 offset = u32(address) - u32(Memory::pointer);
            if (offset < VMEM_SIZE)
            {
                DWORD old_flags;
                ::VirtualProtect(LPVOID(u32(address) & -4096), 4096, PAGE_READWRITE, &old_flags);

                if (exc->ExceptionRecord->ExceptionInformation[0] & 1) // write access
                {
                    if (!Memory::IsExceptionInDisplayFrameBuffer(offset))
                    {
                        errorf(memory, "Write Access Violation in psp memory at 0x%08X.", offset);
                        // in Debug, single step at the next instruction so you can see what issued this exception
                        exc->ContextRecord->EFlags |= 0x100;
                    }
                }
                else
                {
                    errorf(memory, "Read Access Violation in psp memory at 0x%08X.", offset);
                }

                return EXCEPTION_CONTINUE_EXECUTION;
            }
        }
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

void Memory::EnableExceptions(bool enable)
{
    if (enable && !veh_handler)
    {
        veh_handler = ::AddVectoredExceptionHandler(false, PVECTORED_EXCEPTION_HANDLER(&veh_watch_changes));
    }
    else if (veh_handler)
    {
        ::RemoveVectoredExceptionHandler(veh_handler);
    }
}

#else

void Memory::EnableExceptions(bool enable)
{
}

#endif

void Memory::GuardPages(u32 start, u32 end)
{
#if defined(__win32__) && !defined(__cygwin__)
    DWORD old_flags;
    ::VirtualProtect(Memory::xaddr< void >(start), end - start, PAGE_GUARD|PAGE_READWRITE, &old_flags);
#else
#endif
}

void Memory::WatchDirtyPages(u32 start, u32 end, bool enabled /*= true*/)
{
#if defined(__win32__) && !defined(__cygwin__)
    DWORD old_flags;
    ::VirtualProtect(Memory::xaddr< void >(start), end - start, (enabled?PAGE_READONLY:PAGE_READWRITE), &old_flags);
#else
#endif
}

void Memory::SetDisplayFrameBuffer(u32 start, u32 end)
{
//    CriticalSectionScope lock(display_lock);

    if (display_start && display_end)
    {
        Memory::WatchDirtyPages(display_start, display_end, false);
    }

    display_start = start;
    display_end   = end;
    display_dirty = false;

    if (Memory::IsAddressValid(start) && Memory::IsAddressValid(end - 1))
    {
        Memory::WatchDirtyPages(start, end);
    }
}

void Memory::ClearDisplayFrameBuffer()
{
  //  CriticalSectionScope lock(display_lock);

    if (display_start && display_end)
    {
        Memory::WatchDirtyPages(display_start, display_end, false);
        display_start = 0;
        display_end   = 0;
        display_dirty = false;
    }
}

void Memory::GetDisplayFrameBuffer(u32 &start, u32 &end)
{
//    CriticalSectionScope lock(display_lock);

    start = display_start;
    end   = display_end;
}

bool Memory::IsExceptionInDisplayFrameBuffer(u32 address)
{
 //   CriticalSectionScope lock(display_lock);

    if (__inrange(display_start, address, display_end))
    {
        display_dirty = true;
        return true;
    }
    return false;
}

bool Memory::IsDisplayFrameBufferDirty(bool reset /*= true*/)
{
//    CriticalSectionScope lock(display_lock);

    bool dirty = display_dirty;

    if (reset && dirty)
    {
        if (display_start && display_end)
        {
            display_dirty = false;
            Memory::WatchDirtyPages(display_start, display_end, true);
        }
    }

    return dirty;
}

#if defined(__msvc__) && defined(__arch_x86_32__)
static bool __declspec(naked) IsAddressValid__msvc_x86_32_(u8 *p)
{
    __asm xor   eax, eax;         // EAX = 0 --> also clear CF (carry flag in EFLAG)
    __asm mov   al, byte ptr [p]; // read a byte at 'p' address (CF is untouched by this instruction in successful execution)
    __asm setnc al;               // return CF == 0 (CF is set to 1 if an invalid address is detected by our own VEH handler)
}
#endif

bool Memory::IsAddressValid(u32 address)
{
    bool result = !!address && ((u32)(xaddrbu(address) - xaddrbu(VMEM_START)) < VMEM_SIZE);
#if 0 && defined(__msvc__) && defined(__arch_x86_32__)
    return result ? IsAddressValid__msvc_x86_32_(xaddrbu(address)) : false;
#else
    return result;
#endif
}
