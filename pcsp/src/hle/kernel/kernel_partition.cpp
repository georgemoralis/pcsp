#include "stdafx.h"

#include <cstdio>
#include <cstdlib>

#include "kernel_partition.h"

static KernelPartition *kernel_partitions[11] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

static KernelPartition *MapKernelPartition(u32 lower_bound, u32 upper_bound, u32 attributes, char const *name)
{
    KernelPartition *partition = new KernelPartition(lower_bound, upper_bound - lower_bound, attributes, name);

    if (partition->GetUid() <= 0)
    {
        delete partition;
        partition = 0;
    }

    return partition;
}

bool KernelPartition::Initialize()
{
    // we only consider partitions in GAME mode, not in VSH mode
    kernel_partitions[ 0] = 0;
    kernel_partitions[ 1] = MapKernelPartition(0x88000000, 0x88300000, 0x0C, "Kernel Partition (3MB)");
    kernel_partitions[ 2] = MapKernelPartition(0x08800000, 0x0A000000, 0x0F, "User Partition (24MB)");
    kernel_partitions[ 3] = kernel_partitions[1];
    kernel_partitions[ 4] = MapKernelPartition(0x88300000, 0x88400000, 0x0C, "Other Kernel Partition (1MB)");
    kernel_partitions[ 5] = MapKernelPartition(0x08400000, 0x08800000, 0x0F, "Volatile Partition (4MB)");
    kernel_partitions[ 6] = kernel_partitions[2];
    kernel_partitions[ 7] = 0; 
    kernel_partitions[ 8] = MapKernelPartition(0x8A000000, 0x8BC00000, 0x0C, "UMD Cache Partition (28MB)");
    kernel_partitions[ 9] = 0;         
    kernel_partitions[10] = MapKernelPartition(0x8BC00000, 0x8C000000, 0x0C, "ME Partition (4MB)");

    return true;
}

bool KernelPartition::Terminate()
{
    KernelPartition *partition = 0, *next;

    for (partition = theKernelObjects.Next(partition); partition; partition = next)
    {
        next = theKernelObjects.Next(partition);

        delete partition;
    }

    ::memset(kernel_partitions, 0, sizeof(kernel_partitions));

    return true;
}

/// KernelPartitionBlock ///////////////////////////////////////////////////////

void KernelPartitionBlock::GetQuickInfos(char *data, size_t size)
{
    ::snprintf(data, size, "{ #%d, %08X-%08X }", m_partition.GetUid(), m_address, m_address + m_size);
}

KernelPartitionBlock::KernelPartitionBlock(KernelPartition &partition, u32 address, u32 size, char const *name)
:   KernelObject(name)
,   m_partition(partition)
,   m_address(address)
,   m_size(size)
,   m_heap(0)
{
    m_free_blocks[address] = address + size;
    //connect(this, SIGNAL(destroyed(QObject*)), &m_partition, SLOT(delete_partition_block(QObject*));
    //connect(&m_partition, SIGNAL(destroyed(QObject*)), this, SLOT(delete_partition_block(QObject*));
}

KernelPartitionBlock::~KernelPartitionBlock()
{
    while (m_used_blocks.size())
    {
        delete m_used_blocks.begin()->second;
    }

    if (m_heap)
    {
        m_heap->m_partition_blocks.RemoveFromList();
        m_heap = 0;
    }

    m_partition.FreePartitionBlock(this);
}

bool KernelPartitionBlock::AllocateHeapBlock(KernelHeap &heap, u32 size, u32 alignment, KernelHeapBlock *&that)
{
    if (heap.m_type < 2)
    {
        switch (heap.m_type)
        {
        case 0: // heap-like allocation with alignment
            {
                size = (size + 3) & ~3;

                for (HeapFreeBlockMap::iterator free = m_free_blocks.begin(); free != m_free_blocks.end(); ++free)
                {
                    u32 lb = LowerBound(free);
                    u32 ub = UpperBound(free);

                    u32 address = (lb + alignment) & ~alignment;

                    if ((address < ub) && (address + size <= ub))
                    {
                        m_used_blocks[address] = that = new KernelHeapBlock(heap, *this, address, size);

                        m_free_blocks.erase(free);

                        lb = UpperBound(that);

                        if (lb < ub)
                        {
                            m_free_blocks[lb] = ub; 
                        }

                        heap.m_heap_blocks[address] = that;

                        this->m_heap = &heap;

                        return true; 
                    }
                }
            }
            break;

        case 1: // stack-like allocation with alignment
            {
                size = (size + 3) & ~3;

                for (HeapFreeBlockMap::reverse_iterator free = m_free_blocks.rbegin(); free != m_free_blocks.rend(); ++free)
                {
                    u32 lb = LowerBound(free);
                    u32 ub = UpperBound(free);

                    u32 address = ub & ~alignment;

                    if ((lb < address) && (lb <= address - size))
                    {
                        address -= size;

                        m_used_blocks[address] = that = new KernelHeapBlock(heap, *this, address, size);

                        if (lb == address)
                        {
                            m_free_blocks.erase(lb);
                        }
                        else
                        {
                            UpperBound(free) = address;
                        }

                        heap.m_heap_blocks[address] = that;

                        return true; 
                    }
                }
            }
            break;
        }
    }
    return false;
}

bool KernelPartitionBlock::FreeHeapBlock(KernelHeap &heap, u32 address)
{
    HeapUsedBlockMap::iterator used = m_used_blocks.find(address);

    if (used != m_used_blocks.end())
    {
        HeapFreeBlockMap::iterator next = m_free_blocks.lower_bound(UpperBound(used));
        HeapFreeBlockMap::iterator prev = next;

        if (prev != m_free_blocks.end())
        {
            --prev;
        }

        u32 lb = LowerBound(used);
        u32 ub = UpperBound(used);

        if ((prev != m_free_blocks.end()) && (lb == UpperBound(prev)))
        {
            UpperBound(prev) = ub;

            if ((next != m_free_blocks.end()) && (LowerBound(next) == ub))
            {
                UpperBound(prev) = UpperBound(next);

                m_free_blocks.erase(next);
            }
        }
        else if ((next != m_free_blocks.end()) && (LowerBound(next) == ub))
        {
            m_free_blocks[lb] = UpperBound(next);
            m_free_blocks.erase(next);
        }
        else
        {
            m_free_blocks[lb] = ub;
        }

        heap.m_heap_blocks.erase(lb);

        m_used_blocks.erase(used);

        return true;
    }

    return false;
}

void KernelPartitionBlock::FreeHeapBlock(KernelHeap &heap, KernelHeapBlock *that)
{
    FreeHeapBlock(heap, LowerBound(that));
}

/// KernelPartition /////////////////////////////////////////////////////////

KernelPartition *KernelPartition::Get(SceUID id)
{
    switch (id)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        return kernel_partitions[id];
    }

    KernelPartition *partition;

    if (!theKernelObjects.Get(id, partition))
    {
        return partition;
    }

    return 0;
}

void KernelPartition::GetQuickInfos(char *data, size_t size)
{
    ::snprintf(data, size, "{ %08X-%08X, %d }", m_base_address, m_base_address + m_size, m_free_size);
}

bool KernelPartition::AllocatePartitionBlock(char const name[32], int type, u32 address, u32 size, KernelPartitionBlock *&that)
{
	if ((type < 5) && (size <= m_free_size))
	{
		switch (type)
		{
        case 0: // heap-like allocation
        case 3: // heap-like allocation with alignment
			{
                u32 alignment = (type == 3) ? (address - 1) : 3;

                size = (size + 3) & ~3;

				for (PartitionFreeBlockMap::iterator free = m_free_blocks.begin(); free != m_free_blocks.end(); ++free)
				{
                    u32 lb = LowerBound(free);
                    u32 ub = UpperBound(free);

                    address = (lb + alignment) & ~alignment;

					if ((address < ub) && (address + size <= ub))
					{
						m_used_blocks[address] = that = new KernelPartitionBlock(*this, address, size, name);

						m_free_blocks.erase(free);

						lb = UpperBound(that);

						if (lb < ub)
						{
							m_free_blocks[lb] = ub; 
						}

						m_free_size -= size;

						return true; 
					}
				}
			}
			break;

		case 1: // stack-like allocation
        case 4: // stack-like allocation with alignment
			{
                u32 alignment = (type == 4) ? (address - 1) : 3;

                size = (size + 3) & ~3;

				for (PartitionFreeBlockMap::reverse_iterator free = m_free_blocks.rbegin(); free != m_free_blocks.rend(); ++free)
				{
					u32 lb = LowerBound(free);
					u32 ub = UpperBound(free);

                    address = ub & ~alignment;

					if ((lb < address) && (lb <= address - size))
					{
                        address -= size;

						m_used_blocks[address] = that = new KernelPartitionBlock(*this, address, size, name);

						if (lb == address)
						{
							m_free_blocks.erase(lb);
						}
						else
						{
							UpperBound(free) = address;
						}

						m_free_size -= size;

						return true; 
					}
				}
			}
			break;

		case 2: // specific address allocation
			{
                address &= ~3;
                size = (size + 3) & ~3;

                PartitionFreeBlockMap::iterator free = m_free_blocks.lower_bound(address + size);

                if (--free != m_free_blocks.end())
                {
                    u32 lb = LowerBound(free);
                    u32 ub = UpperBound(free);

                    if ((lb <= address) && (address + size <= ub))
                    {
                        m_used_blocks[address] = that = new KernelPartitionBlock(*this, address, size, name);

                        if (lb < LowerBound(that))
                        {
                            UpperBound(free) = LowerBound(that);
                        }
                        else
                        {
                            m_free_blocks.erase(free);
                        }

                        if (UpperBound(that) < ub)
                        {
                            m_free_blocks[UpperBound(that)] = ub;
                        }

                        m_free_size -= size;

                        return true; 
                    }
				}
			}
		}
	}
	return false;
}

void KernelPartition::FreePartitionBlock(KernelPartitionBlock *that)
{
	PartitionUsedBlockMap::iterator used = m_used_blocks.find(LowerBound(that));

	if (used != m_used_blocks.end())
	{
		m_free_size += Length(used);

		PartitionFreeBlockMap::iterator next = m_free_blocks.lower_bound(UpperBound(used));
		PartitionFreeBlockMap::iterator prev = next;

        if (prev != m_free_blocks.end())
        {
            --prev;
        }

        u32 lb = LowerBound(used);
        u32 ub = UpperBound(used);

		if ((prev != m_free_blocks.end()) && (lb == UpperBound(prev)))
		{
			UpperBound(prev) = ub;

			if ((next != m_free_blocks.end()) && (LowerBound(next) == ub))
			{
				UpperBound(prev) = UpperBound(next);

				m_free_blocks.erase(next);
			}
		}
		else if ((next != m_free_blocks.end()) && (LowerBound(next) == ub))
		{
			m_free_blocks[lb] = UpperBound(next);
			m_free_blocks.erase(next);
		}
		else
		{
			m_free_blocks[lb] = ub;
		}
	}

    m_used_blocks.erase(used);
}

KernelPartition::KernelPartition(u32 base_address, u32 size, u32 attributes, char const *name)
:   KernelObject(name)
,   m_base_address(base_address)
,   m_size(size)
,   m_attributes(attributes)
,   m_free_size(size)
{
	m_free_blocks[base_address] = base_address + size;
}

KernelPartition::~KernelPartition()
{
	while (m_used_blocks.size())
	{
		delete m_used_blocks.begin()->second;
	}
}

/// KernelHeapBlock /////////////////////////////////////////////////////////

KernelHeapBlock::KernelHeapBlock(KernelHeap &heap, KernelPartitionBlock &memory_block, u32 address, u32 size)
:   m_heap(heap)
,   m_partition_block(memory_block)
,   m_address(address)
,   m_size(size)
{
}

KernelHeapBlock::~KernelHeapBlock()
{
    m_partition_block.FreeHeapBlock(m_heap, this);
}

/// KernelHeap //////////////////////////////////////////////////////////////

void KernelHeap::GetQuickInfos(char *data, size_t size)
{
    ::snprintf(data, size, "{ #%d, %d }", m_partition.GetUid(), m_size);
}

KernelHeap::KernelHeap(KernelPartition &partition, SceSize size, SceUInt attribute, char const *name)
:   KernelObject(name)
,   m_partition(partition)
,   m_size((u32)size)
,   m_type((u32)((attribute>>1)&1))
{
    m_partition_blocks.Clear();
}

KernelHeap::~KernelHeap()
{
    KernelPartitionBlock* curr_memory_block = this->m_partition_blocks.First();

    while (curr_memory_block)
    {
        KernelPartitionBlock* next_memory_block = this->m_partition_blocks.Next(curr_memory_block);
        delete curr_memory_block;
        curr_memory_block = next_memory_block;
    }
}

KernelHeap *KernelHeap::Create(SceUID uid, SceSize size, int attr, const char *name)
{
    KernelPartition *partition = KernelPartition::Get(uid);

    if (!partition)
    {
        return 0;
    }

    return new KernelHeap(*partition, size, attr, name);
}

void KernelHeap::Delete()
{
    delete this;
}

u32 KernelHeap::AllocMemoryWithOption(SceSize size, SceKernelHeapOptParam *option)
{
    KernelPartitionBlock *block = m_partition_blocks.First();

    for (;;)
    {
        for (; block; block = m_partition_blocks.Next(block))
        {
            KernelHeapBlock *heap_block = 0;

            if (block->AllocateHeapBlock(*this, size, (option ? option->alignment : 0), heap_block))
            {
                return (u32)heap_block->m_address;
            }
        }

        if (!m_partition.AllocatePartitionBlock(GetName(), m_type, 0, m_size, block))
        {
            break;
        }

        m_partition_blocks.Append(block);
    }

    return 0;
}

u32 KernelHeap::AllocMemory(SceSize size)
{
    return AllocMemoryWithOption(size, 0);
}

int KernelHeap::FreeMemory(u32 address)
{
    KernelPartitionBlock *block = m_partition_blocks.First();

    for (;;)
    {
        for (; block; block = m_partition_blocks.Next(block))
        {
            if (block->FreeHeapBlock(*this, address))
            {
                return 0;
            }
        }
    }

    return SCE_KERNEL_ERROR_ILLEGAL_ADDRESS;
}

SceSize KernelHeap::TotalFreeSize()
{
    u32 max_size = 0;

    KernelPartitionBlock *block = m_partition_blocks.First();

    for (; block; block = m_partition_blocks.Next(block))
    {
        for (KernelPartitionBlock::HeapFreeBlockMap::iterator i = block->m_free_blocks.begin(); i != block->m_free_blocks.end(); ++i)
        {
            max_size += KernelPartitionBlock::Length(i);
        }
    }

    return max_size;
}
