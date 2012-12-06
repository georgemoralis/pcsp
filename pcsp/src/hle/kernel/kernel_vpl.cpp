#include "stdafx.h"

#include "kernel_vpl.h"
#include "hle/modules/sysmem/sysmem.h"

void KernelVpl::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelVpl::KernelVpl(SceUID heap_uid, SceUInt attributes, SceSize size, SceKernelVplOptParam *opt_param, char const *name)
:   KernelWaitQueue(name, attributes)
,   m_pool_size(size)
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

KernelVpl::~KernelVpl()
{
    sysmem::hleKernelDeleteHeap(m_heap_uid);
}

int KernelVpl::TryAllocate(SceSize size, u32 *addr)
{
    int result;

    if (!addr)
    {
        result = 0x800200d3;
    }
    else
    {
        if (size == 0 || (SceSize)this->m_pool_size < size)
        {
            result = 0x800201b7;
        }
        else
        {
            *addr = sysmem::hleKernelAllocHeapMemory(this->m_heap_uid, size);
        }
    }
    return result;
}

int KernelVpl::Allocate(SceSize size, u32 *addr, SceUInt *timeout)
{
    (void)timeout;
    return TryAllocate(size, addr);
}

int KernelVpl::AllocateCB(SceSize size, u32 *addr, SceUInt *timeout)
{
    (void)timeout;
    return TryAllocate(size, addr);
}

int KernelVpl::Free(u32 addr)
{
    int result;

    if (!addr)
    {
        result = 0x800200d3;
    }
    else
    {
        result = sysmem::hleKernelFreeHeapMemory(m_heap_uid, addr);
    }
    return result;
}

int KernelVpl::Cancel(int *waiting_threads)
{
    if (waiting_threads)
    {
        *waiting_threads = this->m_waiters_count;
    }
    return 0;
}

int KernelVpl::ReferStatus(SceKernelVplInfo *info)
{
    int intr = sceKernelCpuSuspendIntr();

    int size = info->size < sizeof(SceKernelVplInfo) ? info->size : sizeof(SceKernelVplInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelVplInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attr;

                if (size >= sizeof(SceKernelVplInfo))
                {
                    info->pool_size       = this->m_pool_size;
                    info->free_size       = sysmem::hleKernelHeapTotalFreeSize(this->m_heap_uid);
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    sceKernelCpuResumeIntr(intr);

    return 0;
}
