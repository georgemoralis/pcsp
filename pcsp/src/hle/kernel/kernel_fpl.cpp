#include "stdafx.h"

#include "kernel_fpl.h"
#include "hle/modules/sysmem/sysmem.h"


void KernelFpl::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelFpl::KernelFpl(SceUID heap_uid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam *opt_param, char const *name)
:   KernelWaitQueue(name, attributes)
,   m_pool_blocks(block_count)
,   m_free_blocks(block_count)
,   m_block_size(block_size)
,   m_heap_uid(heap_uid)
{
    if (opt_param)
    {
        m_opt_param = *opt_param;
    }
    else
    {
        memset(&m_opt_param, 0, sizeof(m_opt_param));
    }
}

KernelFpl::~KernelFpl()
{
    sysmem::hleKernelDeleteHeap(m_heap_uid);
}

int KernelFpl::TryAllocate(u32 *addr)
{
    int result;

    if (!addr)
    {
        result = 0x800200d3;
    }
    else
    {
        *addr = sysmem::hleKernelAllocHeapMemory(m_heap_uid, m_block_size);

        if (*addr)
        {
            if (this->m_free_blocks-- == 0)
            {
                this->m_free_blocks += this->m_pool_blocks;
            }
        }
    }
    return result;
}

int KernelFpl::Allocate(u32 *addr, SceUInt * /*timeout*/)
{
    return TryAllocate(addr);
}

int KernelFpl::AllocateCB(u32 *addr, SceUInt * /*timeout*/)
{
    return TryAllocate(addr);
}

int KernelFpl::Free(u32 addr)
{
    int result;

    if (!addr)
    {
        result = 0x800200d3;
    }
    else
    {
        result = sysmem::hleKernelFreeHeapMemory(m_heap_uid, addr);

        if (!result) this->m_free_blocks++;
    }
    return result;
}

int KernelFpl::Cancel(int *waiting_threads)
{
    if (waiting_threads)
    {
        *waiting_threads = this->m_waiters_count;
    }
    return 0;
}

int KernelFpl::ReferStatus(SceKernelFplInfo *info)
{
    int intr = sceKernelCpuSuspendIntr();

    int size = info->size < sizeof(SceKernelFplInfo) ? info->size : sizeof(SceKernelFplInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelFplInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attr;

                if (size >= sizeof(SceKernelFplInfo))
                {
                    info->block_size      = this->m_block_size;
                    info->pool_blocks     = this->m_pool_blocks;
                    info->free_blocks     = this->m_free_blocks;
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    sceKernelCpuResumeIntr(intr);

    return 0;
}
