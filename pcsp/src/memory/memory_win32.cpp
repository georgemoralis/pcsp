#include "stdafx.h"
#include "memory/memory.h"

#define PAGE64K_ALIGN(x) ((x + 65535) & ~65535)

void *Memory::pointer = 0;

static void* psp_memory_handle;

__forceinline void *map_view(unsigned int address, unsigned int offset, unsigned int size)
{
    return ::MapViewOfFileEx(psp_memory_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, offset, size, (LPVOID)(reinterpret_cast< unsigned int >(Memory::pointer) + address));
}

__forceinline void *map_view(unsigned int size)
{
    return ::VirtualAlloc((LPVOID)0, size, MEM_RESERVE, PAGE_NOACCESS);
}

__forceinline void unmap_view()
{
    ::VirtualFree((LPVOID)Memory::pointer, 0, MEM_RELEASE);
}

static bool mapped_buffer(unsigned int address, unsigned int times, unsigned int offset, unsigned int size)
{
    if (!(size & -65536)) // geez! windows has a pretty annoying restriction about the size of a virtual page
    {
        unsigned int total = times * size;
        size = 65536;
        times = (total + 65535) / 65536;
    }

    void *buffer = map_view(address, offset, size);

	if (!buffer)
	{
		return false;
	}

	for (unsigned int i = 1; i < times; ++i)
	{
		if (!map_view((address += size), offset, size))
		{
			return false;
		}
	}

	return true;
}


static bool unused_buffer(unsigned int start, unsigned int end)
{
	// map a mirror of 64KB pages to eat read/write in "unmapped" memory instead of raising an exception
	u32 address = PAGE64K_ALIGN(start);
	u32 times = (end - address + 65535) / 65536;
	return mapped_buffer(address, times, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE), 65536);
}

void *Memory::reserve()
{
    psp_memory_handle = ::CreateFileMappingA(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE + ECTX_SIZE + GARB_SIZE - 1), "pcsp-memory");

	if (psp_memory_handle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

    // we need to allocate twice the necessary virtual space
	Memory::pointer = map_view(VMEM_SIZE*2);

	if (!Memory::pointer)
	{
		return 0;
	}

    // because we need to free it before mapping our segments in it
    // and another thread can try to steal a chunk of it
	unmap_view();

    // we want to map in the middle of the ex-allocated virtual space
    // in case of another thread tries to steal a chunk of our virtual space
    // in the beginning or in the end
    Memory::pointer = (void *)((u32)Memory::pointer + VMEM_SIZE/2);

    //      0×00010000      0×00004000 (16 KiB)     Scratch pad
    //      0×04000000      0×00200000 (2 MiB)      Lower video ram
    //      0×04200000      0×00200000 (2 MiB)      Upper video ram (SLIM only)
    //      0×08000000      0×02000000 (32 MiB)     Lower main ram
    //      0×0A000000      0×02000000 (32 MiB)     Upper main ram (SLIM only)

    if
        (
        true
        && unused_buffer(0x00000000, 0x00010000)
        && mapped_buffer(0x00010000, 1, MRAM_SIZE + VRAM_SIZE, SRAM_SIZE)
        && unused_buffer(0x00014000, 0x04000000)
        && mapped_buffer(0x04000000, 4, MRAM_SIZE            , VRAM_SIZE)
        && mapped_buffer(0x04800000, 4, MRAM_SIZE            , VRAM_SIZE)
        && mapped_buffer(0x08000000, 1, 0                    , MRAM_SIZE)
        && unused_buffer(0x0C000000, 0x10000000)
        )
    {
        return Memory::pointer;
    }

	return 0;
}

void Memory::release()
{
	if (Memory::pointer)
	{
		::UnmapViewOfFile(Memory::pointer);
	}

	if (psp_memory_handle != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(psp_memory_handle);
	}
}

