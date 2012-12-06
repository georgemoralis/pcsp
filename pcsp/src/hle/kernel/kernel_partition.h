#pragma once
#include <set>
#include <map>
#include "kernel_object.h"

struct KernelPartition;
struct KernelPartitionBlock;
struct KernelHeap;
struct KernelHeapBlock;

struct KernelHeapBlock
{
    friend struct KernelPartitionBlock;

    KernelHeap           &m_heap;
    KernelPartitionBlock &m_partition_block;
    u32                   m_address;
    u32				      m_size;

    KernelHeapBlock(KernelHeap &heap, KernelPartitionBlock &memory_block, u32 address, u32 size);

    ~KernelHeapBlock();
};

struct KernelPartitionBlock
:   KernelObject
,   LinkedList< KernelPartitionBlock >::Node
{
    declare_kernel_type(KernelPartitionBlock, KernelObject);

	friend struct KernelPartition;

    KernelPartition &m_partition;
	u32              m_address;
	u32				 m_size;
    KernelHeap      *m_heap;

    typedef std::map< u32, KernelHeapBlock * > HeapUsedBlockMap;
    typedef std::map< u32, u32               > HeapFreeBlockMap;

    HeapUsedBlockMap m_used_blocks;
    HeapFreeBlockMap m_free_blocks;

	KernelPartitionBlock(KernelPartition &partition, u32 address, u32 size, char const *name = 0);

    ~KernelPartitionBlock();

    static inline u32 LowerBound(KernelHeapBlock *block) { return block->m_address; }
    static inline u32 LowerBound(HeapUsedBlockMap::iterator &iter) { return iter->second->m_address; }
    static inline u32 LowerBound(HeapFreeBlockMap::iterator &iter) { return iter->first; }
    static inline u32 LowerBound(HeapFreeBlockMap::reverse_iterator &iter) { return iter->first; }

    static inline u32  UpperBound(KernelHeapBlock *block) { return block->m_address + block->m_size; }
    static inline u32  UpperBound(HeapUsedBlockMap::iterator &iter) { return iter->second->m_address + iter->second->m_size; }
    static inline u32 &UpperBound(HeapFreeBlockMap::iterator &iter) { return iter->second; }
    static inline u32 &UpperBound(HeapFreeBlockMap::reverse_iterator &iter) { return iter->second; }

    static inline u32 Length(KernelHeapBlock *block) { return block->m_size; }
    static inline u32 Length(HeapUsedBlockMap::iterator &iter) { return iter->second->m_size; }
    static inline u32 Length(HeapFreeBlockMap::iterator &iter) { return iter->second - iter->first; }
    static inline u32 Length(HeapFreeBlockMap::reverse_iterator &iter) { return iter->second - iter->first; }

    bool AllocateHeapBlock(KernelHeap &heap, u32 size, u32 alignment, KernelHeapBlock *&that);
    void FreeHeapBlock(KernelHeap &heap, KernelHeapBlock *that);
    bool FreeHeapBlock(KernelHeap &heap, u32 address);
};

struct KernelHeap
:   KernelObject
{
    declare_kernel_type(KernelHeap, KernelObject);

    KernelPartition                       &m_partition;
    u32                                    m_size;
    u32                                    m_type;
    LinkedList< KernelPartitionBlock >     m_partition_blocks;
    KernelPartitionBlock::HeapUsedBlockMap m_heap_blocks;

    KernelHeap(KernelPartition &partition, SceSize size, SceUInt attribute, char const *name);

    ~KernelHeap();

    static KernelHeap *Create(SceUID uid, SceSize size, int attr, const char *name);
    void               Delete();
    u32                AllocMemoryWithOption(SceSize size, SceKernelHeapOptParam *option);
    u32                AllocMemory(SceSize size);
    int                FreeMemory(u32 address);
    SceSize            TotalFreeSize();
};


struct KernelPartition
:   KernelObject
{
    declare_kernel_type(KernelPartition, KernelObject);

	u32 m_base_address;
	u32 m_size;
	u32 m_attributes;
	u32 m_free_size;

	typedef std::map< u32, KernelPartitionBlock * > PartitionUsedBlockMap;
	typedef std::map< u32, u32                    > PartitionFreeBlockMap;

	PartitionUsedBlockMap m_used_blocks;
	PartitionFreeBlockMap m_free_blocks;

	KernelPartition(u32 base_address, u32 size, u32 attributes, char const *name = "");

	~KernelPartition();

    static KernelPartition             *Get(SceUID id);

    static bool                         Initialize();
    static bool                         Terminate();

	static inline u32 LowerBound(KernelPartitionBlock *block) { return block->m_address; }
	static inline u32 LowerBound(PartitionUsedBlockMap::iterator &iter) { return iter->second->m_address; }
	static inline u32 LowerBound(PartitionFreeBlockMap::iterator &iter) { return iter->first; }
	static inline u32 LowerBound(PartitionFreeBlockMap::reverse_iterator &iter) { return iter->first; }

	static inline u32  UpperBound(KernelPartitionBlock *block) { return block->m_address + block->m_size; }
	static inline u32  UpperBound(PartitionUsedBlockMap::iterator &iter) { return iter->second->m_address + iter->second->m_size; }
	static inline u32 &UpperBound(PartitionFreeBlockMap::iterator &iter) { return iter->second; }
	static inline u32 &UpperBound(PartitionFreeBlockMap::reverse_iterator &iter) { return iter->second; }

    static inline u32 Length(KernelPartitionBlock *block) { return block->m_size; }
	static inline u32 Length(PartitionUsedBlockMap::iterator &iter) { return iter->second->m_size; }
	static inline u32 Length(PartitionFreeBlockMap::iterator &iter) { return iter->second - iter->first; }
	static inline u32 Length(PartitionFreeBlockMap::reverse_iterator &iter) { return iter->second - iter->first; }

    bool AllocatePartitionBlock(char const name[32], int type, u32 address, u32 size, KernelPartitionBlock *&that);
    void FreePartitionBlock(KernelPartitionBlock *that);
};
