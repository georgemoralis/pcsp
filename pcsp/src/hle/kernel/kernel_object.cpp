#include "stdafx.h"

#include "kernel_object.h"

#include "log.h"



/// KernelObject ////////////////////////////////////////////////////////////

char const *KernelObject::m_object_type = "KernelObject";

KernelObject::KernelObject(char const *name)
{
	::memset(m_name, 0, 32);
	if (name) ::strncpy(m_name, name, 31);
	theKernelObjects.Attach(this);
}

KernelObject::~KernelObject()
{
	theKernelObjects.Detach(this);
}

void KernelObject::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, "-", size-1);
}

void KernelObjectPool::Dump()
{
    for (int i = 0; i < max_count; ++i)
    {
        if (occupied[i])
        {
            char buffer[1024];
            
            if (pool[i])
            {
                pool[i]->GetQuickInfos(buffer, 1024);
            }
            //TODO find out why it crashes
           // tracef(kernel, "KernelObject %i: %s \"%s\": %s", i + handle_offset, pool[i]->GetType(), pool[i]->GetName(), buffer);
        }
    }
}
