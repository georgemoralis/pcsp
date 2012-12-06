#include "stdafx.h"
#include "sysmem.h"
#include "memory/memory.h"
#include "emulator.h"
#include "log.h"

#include "hle/types.h"
#include "hle/kernel/kernel_object.h"
#include "hle/kernel/kernel_partition.h"

LogSubCategory Log::sceKernelMaxFreeMemSize       (Log::SysMemUserForUser, "sceKernelMaxFreeMemSize");
LogSubCategory Log::sceKernelTotalFreeMemSize     (Log::SysMemUserForUser, "sceKernelTotalFreeMemSize");
LogSubCategory Log::sceKernelAllocPartitionMemory (Log::SysMemUserForUser, "sceKernelAllocPartitionMemory");
LogSubCategory Log::sceKernelFreePartitionMemory  (Log::SysMemUserForUser, "sceKernelFreePartitionMemory");
LogSubCategory Log::sceKernelGetBlockHeadAddr     (Log::SysMemUserForUser, "sceKernelGetBlockHeadAddr");
LogSubCategory Log::sceKernelPrintf               (Log::SysMemUserForUser, "sceKernelPrintf");
LogSubCategory Log::sceKernelDevkitVersion        (Log::SysMemUserForUser, "sceKernelDevkitVersion");
LogSubCategory Log::sceKernelSetCompilerVersion   (Log::SysMemUserForUser, "sceKernelSetCompilerVersion");
LogSubCategory Log::sceKernelSetCompiledSdkVersion(Log::SysMemUserForUser, "sceKernelSetCompiledSdkVersion");

///////////////////////////////////////////////////////////////////

namespace sysmem
{
    static bool sysmem_ready = false;

	KernelPartition *hleKernelGetPartition(SceUID id)
	{
        return KernelPartition::Get(id);
	}

	u32 hleKernelMaxFreeMemSize(SceUID id)
	{
		u32 max_size = 0;

		int state = sceKernelCpuSuspendIntr();

		KernelPartition *partition = hleKernelGetPartition(id);

		if (!partition->m_free_blocks.empty())
		{
			for (KernelPartition::PartitionFreeBlockMap::iterator i = partition->m_free_blocks.begin(); i != partition->m_free_blocks.end(); ++i)
			{
				u32 size = i->second - i->first;

				if (size > max_size)
				{
					max_size = size;
				}
			}
		}

		sceKernelCpuResumeIntr(state);

		return max_size;
	}

	u32 hleKernelTotalFreeMemSize(SceUID id)
	{
		u32 size = 0;

		int state = sceKernelCpuSuspendIntr();

		KernelPartition *partition = hleKernelGetPartition(id);

		if (partition)
		{
			for (KernelPartition::PartitionFreeBlockMap::iterator i = partition->m_free_blocks.begin(); i != partition->m_free_blocks.end(); ++i)
			{
				size += i->second - i->first;
			}
		}

		sceKernelCpuResumeIntr(state);

		return size;
	}

	int hleKernelQueryMemoryPartitionInfo(SceUID id, PspSysmemPartitionInfo *info)
	{
		int result = 0;

		KernelPartition *partition = hleKernelGetPartition(id);

		if (partition)
		{
			int state = sceKernelCpuSuspendIntr();

			if (info->size == sizeof(PspSysmemPartitionInfo))
			{
				info->startaddr = partition->m_base_address;
				info->memsize = partition->m_size;
				info->attr = partition->m_attributes & 0xF;
			}
			else
			{
				result = 0x800200D2;
			}

			sceKernelCpuResumeIntr(state);
		}
		else
		{
			result = 0x800200D6;
		}

		return result;
	}

    SceUID hleKernelAllocPartitionMemory(KernelPartition &partition, const char *name, int type, u32 size, u32 addr, KernelPartitionBlock *&that)
    {
        int result;

        if (partition.AllocatePartitionBlock(name, type, addr, size, that))
        {
            result = (SceUID)that->m_uid;
        }
        else
        {
            result = 0x800200D9;
        }

        return result;
    }

	SceUID hleKernelAllocPartitionMemory(SceUID id, const char *name, int type, u32 size, u32 addr)
	{
		int result;

		if (type < 5)
		{
			int state = sceKernelCpuSuspendIntr();

			KernelPartition *partition = hleKernelGetPartition(id);

            KernelPartitionBlock *that;

            if (partition)
            {
                result = hleKernelAllocPartitionMemory(*partition, name, type, size, addr, that);
            }
            else
            {
                result = 0x800200D6;
            }

			sceKernelCpuResumeIntr(state);
		}
		else
		{
			result = 0x800200D8;
		}

		return (SceUID)result;
	}

	int hleKernelFreePartitionMemory(SceUID uid)
	{
		int state = sceKernelCpuSuspendIntr();

		KernelPartitionBlock *object;

		int result = theKernelObjects.Get< KernelPartitionBlock >(uid, object);

		if (!result)
		{
			delete object;
		}

		sceKernelCpuResumeIntr(state);

		return result;
	}

	int hleKernelGetBlockHeadAddr(SceUID uid)
	{
		int state = sceKernelCpuSuspendIntr();

		KernelPartitionBlock *object;

		int result = theKernelObjects.Get(uid, object);

		if (!result)
		{
			result = (int)object->m_address;
		}

		sceKernelCpuResumeIntr(state);

		return result;
	}

    SceUID hleKernelCreateHeap(SceUID uid, SceSize size, int attr, const char *name)
    {
        int result = 0;
        int state = sceKernelCpuSuspendIntr();

        KernelHeap *heap = KernelHeap::Create(uid, size, attr, name);

        result = heap->GetUid();

        if (result <= 0)
        {
            delete heap;
        }

        sceKernelCpuResumeIntr(state);

        return result;
    }

    int hleKernelDeleteHeap(SceUID uid)
    {
        int state = sceKernelCpuSuspendIntr();

        KernelHeap *heap;

        int result = theKernelObjects.Get(uid, heap);

        if (!result)
        {
            heap->Delete();
        }

        sceKernelCpuResumeIntr(state);

        return result;
    }
    
    u32 hleKernelAllocHeapMemoryWithOption(SceUID uid, SceSize size, SceKernelHeapOptParam *option)
    {
        u32 result = 0;

        int state = sceKernelCpuSuspendIntr();

        KernelHeap *heap;

        if (!theKernelObjects.Get(uid, heap))
        {
            result = heap->AllocMemoryWithOption(size, option);
        }

        sceKernelCpuResumeIntr(state);

        return result;
    }
    
    u32 hleKernelAllocHeapMemory(SceUID uid, SceSize size)
    {
        return hleKernelAllocHeapMemoryWithOption(uid, size, 0);
    }
    
    int hleKernelFreeHeapMemory(SceUID uid, u32 address)
    {
        int state = sceKernelCpuSuspendIntr();

        KernelHeap *heap;

        int result = theKernelObjects.Get(uid, heap);

        if (!result)
        {
            heap->FreeMemory(address);
        }

        sceKernelCpuResumeIntr(state);

        return result;
    }

    SceSize hleKernelHeapTotalFreeSize(SceUID uid)
    {
		u32 max_size = 0;

        int state = sceKernelCpuSuspendIntr();

        KernelHeap *heap;

        int result = theKernelObjects.Get(uid, heap);

        if (!result)
        {
            max_size = heap->TotalFreeSize();
        }

        sceKernelCpuResumeIntr(state);

        return max_size;
    }
}



///////////////////////////////////////////////////////////////////

namespace SysMemUserForUser
{
	using namespace sysmem;

    bool Reboot()
    {
        ShutDown();

        if (KernelPartition::Initialize())
        {
            tracef(SysMemUserForUser, "Partitions Table :");

            KernelPartition *partition = 0;

            for (int i = 1; (partition = theKernelObjects.Next(partition)); ++i)
            {
                char tmp[512];

                partition->GetQuickInfos(tmp, 512);

                tracef(SysMemUserForUser, "#%d %s", i, tmp);
            }

            sysmem_ready = true;
        }

        return true;
    }

    bool ShutDown()
    {
        if (sysmem_ready)
        {
            sysmem_ready = KernelPartition::Terminate();
        }
        return true;
    }

	int sceKernelMaxFreeMemSize()
	{
		return hleKernelMaxFreeMemSize(2);
	}
	
	int sceKernelTotalFreeMemSize()
	{
		return hleKernelTotalFreeMemSize(2);
	}

	int sceKernelAllocPartitionMemory(int a0, int a1, int a2, int a3, int t0)
	{
		PspSysmemPartitionInfo data;
		
		SceUID      id        = (SceUID)a0;
        const char *name      = Memory::addr< const char >(a1);
        int         type      = (int)a2;
		u32         size      = (u32)a3;
		u32         addr      = (u32)t0;

		data.size = sizeof(data);
		
		int result = hleKernelQueryMemoryPartitionInfo(id, &data);

		if (result >=  0)
		{
			if (data.attr & 2)
			{
                return hleKernelAllocPartitionMemory(id, (name ? name : "BlockForUser"), type, size, addr);
			}

			result = 0x80020001;
		}

		return result;
	}

	int sceKernelFreePartitionMemory(int a0)
	{
		return hleKernelFreePartitionMemory((SceUID)a0);
	}

	int sceKernelGetBlockHeadAddr(int a0)
	{
		return hleKernelGetBlockHeadAddr((SceUID)a0);
	}

	int sceKernelPrintf()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED sceKernelPrintf");
		return 0;
	}

	int sceKernelDevkitVersion()
	{
		return SCE_FIRMWARE_500;
	}

	static int _sceKernelSetCompilerVersion = 0;

	int sceKernelSetCompilerVersion(int a0)
	{
		_sceKernelSetCompilerVersion = a0;

		return 0;
	}

	static int _sceKernelSetCompiledSdkVersion = 0;

	int sceKernelSetCompiledSdkVersion(int a0)
	{
		_sceKernelSetCompiledSdkVersion = a0;

		return 0;
	}

	int sceKernelGetCompiledSdkVersion(int a0)
	{
        (void)a0;
		return _sceKernelSetCompiledSdkVersion;
	}
	int SysMemUserForUser_057E7380()
	{
        errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_057E7380");
		return 0;
	}
	int sceKernelQueryMemoryInfo()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED sceKernelQueryMemoryInfo");
		return 0;
	}
	int SysMemUserForUser_315AD3A0()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_315AD3A0");
		return 0;
	}
	int SysMemUserForUser_342061E5()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_342061E5");
		return 0;
	}
	int SysMemUserForUser_50F61D8A()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_50F61D8A");
		return 0;
	}
	int SysMemUserForUser_91DE343C()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_91DE343C");
		return 0;
	}
	int SysMemUserForUser_A6848DF8()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_A6848DF8");
		return 0;
	}
	int SysMemUserForUser_ACBD88CA()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_ACBD88CA");
		return 0;
	}
	int SysMemUserForUser_D8DE5C1E()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_D8DE5C1E");
		return 0;
	}
	int SysMemUserForUser_DB83A952()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_DB83A952");
		return 0;
	}
	int SysMemUserForUser_EBD5C3E6()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_EBD5C3E6");
		return 0;
	}
	int SysMemUserForUser_FE707FDF()
	{
		errorf(SysMemUserForUser,"UNSUPPORTED SysMemUserForUser_FE707FDF");
		return 0;
	}
}



///////////////////////////////////////////////////////////////////

namespace syscalls
{
    void sceKernelMaxFreeMemSize(AlContext &context)        { V0 = SysMemUserForUser::sceKernelMaxFreeMemSize(); }
    void sceKernelTotalFreeMemSize(AlContext &context)      { V0 = SysMemUserForUser::sceKernelTotalFreeMemSize(); }
    void sceKernelAllocPartitionMemory(AlContext &context)  { V0 = SysMemUserForUser::sceKernelAllocPartitionMemory(A0, A1, A2, A3, T0); }
    void sceKernelFreePartitionMemory(AlContext &context)   { V0 = SysMemUserForUser::sceKernelFreePartitionMemory(A0); }
    void sceKernelGetBlockHeadAddr(AlContext &context)      { V0 = SysMemUserForUser::sceKernelGetBlockHeadAddr(A0); }
    void sceKernelPrintf(AlContext &context)                { V0 = SysMemUserForUser::sceKernelPrintf(); }
    void sceKernelDevkitVersion(AlContext &context)         { V0 = SysMemUserForUser::sceKernelDevkitVersion(); }
    void sceKernelSetCompilerVersion(AlContext &context)    { V0 = SysMemUserForUser::sceKernelSetCompilerVersion(A0); }
    void sceKernelSetCompiledSdkVersion(AlContext &context) { V0 = SysMemUserForUser::sceKernelSetCompiledSdkVersion(A0); }
	void SysMemUserForUser_057E7380(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_057E7380(); }
	void sceKernelQueryMemoryInfo(AlContext &context)       { V0 = SysMemUserForUser::sceKernelQueryMemoryInfo(); }
	void SysMemUserForUser_315AD3A0(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_315AD3A0(); }
	void SysMemUserForUser_342061E5(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_342061E5(); }
	void SysMemUserForUser_50F61D8A(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_50F61D8A(); }
	void SysMemUserForUser_91DE343C(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_91DE343C(); }
	void SysMemUserForUser_A6848DF8(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_A6848DF8(); }
	void SysMemUserForUser_ACBD88CA(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_ACBD88CA(); }
	void SysMemUserForUser_D8DE5C1E(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_D8DE5C1E(); }
	void SysMemUserForUser_DB83A952(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_DB83A952(); }
	void SysMemUserForUser_EBD5C3E6(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_EBD5C3E6(); }
	void sceKernelGetCompiledSdkVersion(AlContext &context) { V0 = SysMemUserForUser::sceKernelGetCompiledSdkVersion(A0); }
	void SysMemUserForUser_FE707FDF(AlContext &context)     { V0 = SysMemUserForUser::SysMemUserForUser_FE707FDF(); }
}




