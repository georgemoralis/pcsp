#ifndef WIN32
#include "stdafx.h"
#include "memory/memory.h"

void *Memory::pointer = 0;

static int psp_memory_handle;

void *Memory::reserve()
{
    Memory::pointer = malloc(VMEM_SIZE);
/*
    psp_memory_handle = ::CreateFileMapping
        (
        INVALID_HANDLE_VALUE,
        0,
        PAGE_READWRITE,
        0, ((SRAM_SIZE + VRAM_SIZE + MRAM_SIZE + (65536*3) - 1) & -65536),
        0
        );

    if (psp_memory_handle == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    Memory::pointer = ::VirtualAlloc
        (
        (void *)0,
        VMEM_SIZE,
        MEM_RESERVE,
        PAGE_NOACCESS
        );

    if (!Memory::pointer)
    {
        return 0;
    }

    ::VirtualFree(Memory::pointer, 0, MEM_RELEASE);


    if (mapped_buffer(0, 1, ((SRAM_SIZE + VRAM_SIZE + MRAM_SIZE + (65536*3) - 1) & -65536) - 65536, 65536))
    {
        Memory::pointer = (void *)((char *)Memory::pointer + 65536);

        //      0x00010000      0x00004000 (16 KiB)     Scratchpad
        //      0x04000000      0x00200000 (2 MiB)      Lower video ram
        //      0x04200000      0x00200000 (2 MiB)      Upper video ram (SLIM only)
        //      0x08000000      0x02000000 (32 MiB)     Lower main ram
        //      0x0A000000      0x02000000 (32 MiB)     Upper main ram (SLIM only)

        if
            (
            true
            && unused_buffer(0x00000000, 0x00010000)
            && mapped_buffer(0x00010000, 1, MRAM_SIZE + VRAM_SIZE, 65536) // SRAM_SIZE
            && unused_buffer(0x00020000, 0x04000000) // 0x00014000 is not aligned on 64KB-boundary
            && mapped_buffer(0x04000000, 1, MRAM_SIZE, VRAM_SIZE)
            && unused_buffer(0x04400000, 0x08000000)
            && mapped_buffer(0x08000000, 1, 0, MRAM_SIZE)
            && unused_buffer(0x0C000000, 0x10000000)
            )
        {
            return Memory::pointer;
        }
    } */

    return Memory::pointer;
}

void Memory::release()
{
/*
    if (Memory::pointer)
    {
        char *pointer = reinterpret_cast< char * >(Memory::pointer) - 65536;

        ::UnmapViewOfFile(reinterpret_cast< char * >(pointer));
    }

    if (psp_memory_handle != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(psp_memory_handle);
    }*/
    free(Memory::pointer);
}
#endif
