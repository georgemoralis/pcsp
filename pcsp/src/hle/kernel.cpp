#include "stdafx.h"
#include "kernel.h"
#include "modules.h"
#include "syscalls.h"

#include "../src/wtf/core/psp/hle/sceKernelThread.h"

#include "log.h"

using namespace hle;

KernelObjectPool theKernelObjects;
KernelScheduler theKernelScheduler;
KernelModuleManager theKernelModuleManager;

char const *KernelWaitQueue::m_object_type       = "KernelWaitQueue";
char const *KernelThread::m_object_type          = "KernelThread";
char const *KernelEventFlag::m_object_type       = "KernelEventFlag";
char const *KernelEventHandler::m_object_type    = "KernelThread";
char const *KernelCallback::m_object_type        = "KernelCallback";
char const *KernelSemaphore::m_object_type       = "KernelSemaphore";
char const *KernelMsgBox::m_object_type          = "KernelMsgBox";
char const *KernelMsgPipe::m_object_type         = "KernelMsgPipe";
char const *KernelFpl::m_object_type             = "KernelFpl";
char const *KernelVpl::m_object_type             = "KernelVpl";
char const *KernelTimer::m_object_type           = "KernelTimer";
char const *KernelDelay::m_object_type           = "KernelDelay";
char const *KernelAlarm::m_object_type           = "KernelAlarm";
char const *KernelVTimer::m_object_type          = "KernelVTimer";
char const *KernelPartitionBlock::m_object_type  = "KernelPartitionBlock";
char const *KernelPartition::m_object_type       = "KernelPartition";
char const *KernelHeap::m_object_type            = "KernelHeap";
char const *KernelModule::m_object_type          = "KernelModule";

namespace kernel
{
	static bool kernel_ready = false;

	bool Reboot()
	{
        ShutDown();

        syscalls::Reboot();

        kernel_ready = true;
        return true;
	}

	bool ShutDown()
	{
		if (kernel_ready)
		{
            syscalls::ShutDown();

            int count = theKernelObjects.CountAll();
            if (count)
            {
                theKernelObjects.Dump();
                tracef(kernel, "Shutting down kernel - %i kernel objects alive", count);
                theKernelObjects.ClearAll();
            }

			kernel_ready = false;
		}
        return true;
	}
}
