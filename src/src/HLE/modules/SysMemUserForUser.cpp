/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#include "SysMemUserForUser.h"

/*TODO*/  // public class SysMemUserForUser extends HLEModule {
/*TODO*/  //
/*TODO*/  //    public static Logger log = Modules.getLogger("SysMemUserForUser");
/*TODO*/  //    protected static Logger stdout = Logger.getLogger("stdout");
/*TODO*/  //    protected static HashMap<Integer, SysMemInfo> blockList;
/*TODO*/  //    protected static MemoryChunkList[] freeMemoryChunks;
/*TODO*/  //    protected int firmwareVersion = 150;
/*TODO*/  //    public static final int defaultSizeAlignment = 256;
/*TODO*/  //
/*TODO*/  //    // PspSysMemBlockTypes
/*TODO*/  //    public static final int PSP_SMEM_Low = 0;
/*TODO*/  //    public static final int PSP_SMEM_High = 1;
/*TODO*/  //    public static final int PSP_SMEM_Addr = 2;
/*TODO*/  //    public static final int PSP_SMEM_LowAligned = 3;
/*TODO*/  //    public static final int PSP_SMEM_HighAligned = 4;
/*TODO*/  //
/*TODO*/  //    protected boolean started = false;
/*TODO*/  //    private int compiledSdkVersion;
/*TODO*/  //    private int compilerVersion;
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void load() {
/*TODO*/  //        reset();
/*TODO*/  //
/*TODO*/  //        super.load();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void start() {
/*TODO*/  //        if (!started) {
/*TODO*/  //            reset();
/*TODO*/  //            started = true;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        compiledSdkVersion = 0;
/*TODO*/  //        compilerVersion = 0;
/*TODO*/  //
/*TODO*/  //        super.start();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void stop() {
/*TODO*/  //        started = false;
/*TODO*/  //
/*TODO*/  //        super.stop();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private MemoryChunkList createMemoryChunkList(int startAddr, int endAddr) {
/*TODO*/  //        startAddr &= Memory.addressMask;
/*TODO*/  //        endAddr &= Memory.addressMask;
/*TODO*/  //
/*TODO*/  //        MemoryChunk initialMemory = new MemoryChunk(startAddr, endAddr - startAddr + 1);
/*TODO*/  //
/*TODO*/  //        return new MemoryChunkList(initialMemory);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void reset() {
/*TODO*/  //        reset(false);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void reset(boolean preserveKernelMemory) {
/*TODO*/  //        if (blockList == null || freeMemoryChunks == null) {
/*TODO*/  //            preserveKernelMemory = false;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (preserveKernelMemory) {
/*TODO*/  //            List<SysMemInfo> toBeFreed = new LinkedList<SysMemInfo>();
/*TODO*/  //            for (SysMemInfo sysMemInfo : blockList.values()) {
/*TODO*/  //                if (sysMemInfo.partitionid == USER_PARTITION_ID) {
/*TODO*/  //                    toBeFreed.add(sysMemInfo);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            for (SysMemInfo sysMemInfo : toBeFreed) {
/*TODO*/  //                sysMemInfo.free();
/*TODO*/  //            }
/*TODO*/  //        } else {
/*TODO*/  //            blockList = new HashMap<Integer, SysMemInfo>();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (!preserveKernelMemory) {
/*TODO*/  //            // free memory chunks for each partition
/*TODO*/  //            freeMemoryChunks = new MemoryChunkList[6];
/*TODO*/  //            freeMemoryChunks[KERNEL_PARTITION_ID] = createMemoryChunkList(MemoryMap.START_KERNEL,
          //            KERNEL_VOLATILE_MEM_START - 1);
/*TODO*/  //            freeMemoryChunks[VSHELL_PARTITION_ID] = createMemoryChunkList(KERNEL_VOLATILE_MEM_START,
          //            KERNEL_VOLATILE_MEM_START + KERNEL_VOLATILE_MEM_SIZE - 1);
/*TODO*/  //            sceMpeg.allocateEsBuffers();
/*TODO*/  //        }
/*TODO*/  //        freeMemoryChunks[USER_PARTITION_ID] = createMemoryChunkList(MemoryMap.START_USERSPACE,
          //        MemoryMap.END_USERSPACE);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setMemory64MB(boolean isMemory64MB) {
/*TODO*/  //        if (isMemory64MB) {
/*TODO*/  //            setMemorySize(MemoryMap.END_RAM_64MB - MemoryMap.START_RAM + 1); // 64 MB
/*TODO*/  //        } else {
/*TODO*/  //            setMemorySize(MemoryMap.END_RAM_32MB - MemoryMap.START_RAM + 1); // 32 MB
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setMemorySize(int memorySize) {
/*TODO*/  //        if (MemoryMap.SIZE_RAM != memorySize) {
/*TODO*/  //            int kernelSize = MemoryMap.END_KERNEL - MemoryMap.START_KERNEL + 1;
/*TODO*/  //            int kernelSize32 = kernelSize >> 2;
/*TODO*/  //            int[] savedKernelMemory = new int[kernelSize32];
/*TODO*/  //            IMemoryReader memoryReader = MemoryReader.getMemoryReader(MemoryMap.START_KERNEL, kernelSize,
          //            4);
/*TODO*/  //            for (int i = 0; i < kernelSize32; i++) {
/*TODO*/  //                savedKernelMemory[i] = memoryReader.readNext();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            int previousMemorySize = MemoryMap.SIZE_RAM;
/*TODO*/  //            MemoryMap.END_RAM = MemoryMap.START_RAM + memorySize - 1;
/*TODO*/  //            MemoryMap.END_USERSPACE = MemoryMap.END_RAM;
/*TODO*/  //            MemoryMap.SIZE_RAM = MemoryMap.END_RAM - MemoryMap.START_RAM + 1;
/*TODO*/  //
/*TODO*/  //            if (!Memory.getInstance().allocate()) {
/*TODO*/  //                log.error(String.format("Failed to resize the PSP memory from 0x%X to 0x%X",
          //                previousMemorySize, memorySize));
/*TODO*/  //                Emulator.PauseEmuWithStatus(Emulator.EMU_STATUS_MEM_ANY);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            IMemoryWriter memoryWriter = MemoryWriter.getMemoryWriter(MemoryMap.START_KERNEL, kernelSize,
          //            4);
/*TODO*/  //            for (int i = 0; i < kernelSize32; i++) {
/*TODO*/  //                memoryWriter.writeNext(savedKernelMemory[i]);
/*TODO*/  //            }
/*TODO*/  //            memoryWriter.flush();
/*TODO*/  //
/*TODO*/  //            reset(true);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static class SysMemInfo implements Comparable<SysMemInfo> {
/*TODO*/  //
/*TODO*/  //        public final int uid;
/*TODO*/  //        public final int partitionid;
/*TODO*/  //        public final String name;
/*TODO*/  //        public final int type;
/*TODO*/  //        public int size;
/*TODO*/  //        public int allocatedSize;
/*TODO*/  //        public int addr;
/*TODO*/  //
/*TODO*/  //        public SysMemInfo(int partitionid, String name, int type, int size, int allocatedSize, int addr) {
/*TODO*/  //            this.partitionid = partitionid;
/*TODO*/  //            this.name = name;
/*TODO*/  //            this.type = type;
/*TODO*/  //            this.size = size;
/*TODO*/  //            this.allocatedSize = allocatedSize;
/*TODO*/  //            this.addr = addr;
/*TODO*/  //
/*TODO*/  //            uid = SceUidManager.getNewUid("SysMem");
/*TODO*/  //            blockList.put(uid, this);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String toString() {
/*TODO*/  //            return String.format("SysMemInfo[addr=0x%08X-0x%08X, uid=0x%X, partition=%d, name='%s', type=%s,
          //            size=0x%X (allocated=0x%X)]", addr, addr + allocatedSize, uid, partitionid, name,
          //            getTypeName(type), size, allocatedSize);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public void free() {
/*TODO*/  //            blockList.remove(uid);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public int compareTo(SysMemInfo o) {
/*TODO*/  //            if (addr == o.addr) {
/*TODO*/  //                log.warn("Set invariant broken for SysMemInfo " + this);
/*TODO*/  //                return 0;
/*TODO*/  //            }
/*TODO*/  //            return addr < o.addr ? -1 : 1;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    static protected String getTypeName(int type) {
/*TODO*/  //        String typeName;
/*TODO*/  //
/*TODO*/  //        switch (type) {
/*TODO*/  //            case PSP_SMEM_Low:
/*TODO*/  //                typeName = "PSP_SMEM_Low";
/*TODO*/  //                break;
/*TODO*/  //            case PSP_SMEM_High:
/*TODO*/  //                typeName = "PSP_SMEM_High";
/*TODO*/  //                break;
/*TODO*/  //            case PSP_SMEM_Addr:
/*TODO*/  //                typeName = "PSP_SMEM_Addr";
/*TODO*/  //                break;
/*TODO*/  //            case PSP_SMEM_LowAligned:
/*TODO*/  //                typeName = "PSP_SMEM_LowAligned";
/*TODO*/  //                break;
/*TODO*/  //            case PSP_SMEM_HighAligned:
/*TODO*/  //                typeName = "PSP_SMEM_HighAligned";
/*TODO*/  //                break;
/*TODO*/  //            default:
/*TODO*/  //                typeName = "UNHANDLED " + type;
/*TODO*/  //                break;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return typeName;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private boolean isValidPartitionId(int partitionid) {
/*TODO*/  //        return partitionid >= 0 && partitionid < freeMemoryChunks.length && freeMemoryChunks[partitionid] !=
          //        null;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // Allocates to 256-byte alignment
/*TODO*/  //    public SysMemInfo malloc(int partitionid, String name, int type, int size, int addr) {
/*TODO*/  //        if (freeMemoryChunks == null) {
/*TODO*/  //            return null;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        MemoryChunk allocatedMemoryChunk = null;
/*TODO*/  //        int allocatedSize = 0;
/*TODO*/  //
/*TODO*/  //        if (isValidPartitionId(partitionid)) {
/*TODO*/  //            MemoryChunkList freeMemoryChunk = freeMemoryChunks[partitionid];
/*TODO*/  //            int alignment = defaultSizeAlignment - 1;
/*TODO*/  //
/*TODO*/  //            // The allocated size has not to be aligned to the requested alignment
/*TODO*/  //            // (for PSP_SMEM_LowAligned or PSP_SMEM_HighAligned),
/*TODO*/  //            // it is only aligned to the default size alignment.
/*TODO*/  //            allocatedSize = Utilities.alignUp(size, alignment);
/*TODO*/  //
/*TODO*/  //            if (type == PSP_SMEM_LowAligned || type == PSP_SMEM_HighAligned) {
/*TODO*/  //                // Use the alignment provided in the addr parameter
/*TODO*/  //                alignment = addr - 1;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            switch (type) {
/*TODO*/  //                case PSP_SMEM_Low:
/*TODO*/  //                case PSP_SMEM_LowAligned:
/*TODO*/  //                    allocatedMemoryChunk = freeMemoryChunk.allocLow(allocatedSize, alignment);
/*TODO*/  //                    break;
/*TODO*/  //                case PSP_SMEM_High:
/*TODO*/  //                case PSP_SMEM_HighAligned:
/*TODO*/  //                    allocatedMemoryChunk = freeMemoryChunk.allocHigh(allocatedSize, alignment);
/*TODO*/  //                    break;
/*TODO*/  //                case PSP_SMEM_Addr:
/*TODO*/  //                    allocatedMemoryChunk = freeMemoryChunk.alloc(addr & Memory.addressMask, allocatedSize);
/*TODO*/  //                    break;
/*TODO*/  //                default:
/*TODO*/  //                    log.warn(String.format("malloc: unknown type %s", getTypeName(type)));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        SysMemInfo sysMemInfo;
/*TODO*/  //        if (allocatedMemoryChunk == null) {
/*TODO*/  //            log.warn(String.format("malloc cannot allocate partition=%d, name='%s', type=%s, size=0x%X,
          //            addr=0x%08X, maxFreeMem=0x%X, totalFreeMem=0x%X", partitionid, name, getTypeName(type), size,
          //            addr, maxFreeMemSize(partitionid), totalFreeMemSize(partitionid)));
/*TODO*/  //            if (log.isDebugEnabled()) {
/*TODO*/  //                log.debug("Free list: " + getDebugFreeMem());
/*TODO*/  //                log.debug("Allocated blocks:\n" + getDebugAllocatedMem() + "\n");
/*TODO*/  //            }
/*TODO*/  //            sysMemInfo = null;
/*TODO*/  //        } else {
/*TODO*/  //            sysMemInfo = new SysMemInfo(partitionid, name, type, size, allocatedMemoryChunk.size,
          //            allocatedMemoryChunk.addr);
/*TODO*/  //
/*TODO*/  //            if (log.isDebugEnabled()) {
/*TODO*/  //                log.debug(String.format("malloc partition=%d, name='%s', type=%s, size=0x%X, addr=0x%08X:
          //                returns 0x%08X", partitionid, name, getTypeName(type), size, addr,
          //                allocatedMemoryChunk.addr));
/*TODO*/  //                if (log.isTraceEnabled()) {
/*TODO*/  //                    log.trace("Free list after malloc:\n" + getDebugFreeMem() + "\n");
/*TODO*/  //                    log.trace("Allocated blocks after malloc:\n" + getDebugAllocatedMem() + "\n");
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return sysMemInfo;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getDebugFreeMem() {
/*TODO*/  //        StringBuilder s = new StringBuilder();
/*TODO*/  //        s.append(String.format("partition=%d: ", KERNEL_PARTITION_ID));
/*TODO*/  //        s.append(freeMemoryChunks[KERNEL_PARTITION_ID].toString());
/*TODO*/  //        if (freeMemoryChunks[USER_PARTITION_ID] != null) {
/*TODO*/  //            s.append("\n");
/*TODO*/  //            s.append(String.format("partition=%d: ", USER_PARTITION_ID));
/*TODO*/  //            s.append(freeMemoryChunks[USER_PARTITION_ID].toString());
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return s.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getDebugAllocatedMem() {
/*TODO*/  //        StringBuilder result = new StringBuilder();
/*TODO*/  //
/*TODO*/  //        // Sort allocated blocks by address
/*TODO*/  //        List<SysMemInfo> sortedBlockList = Collections.list(Collections.enumeration(blockList.values()));
/*TODO*/  //        Collections.sort(sortedBlockList);
/*TODO*/  //
/*TODO*/  //        for (SysMemInfo sysMemInfo : sortedBlockList) {
/*TODO*/  //            if (result.length() > 0) {
/*TODO*/  //                result.append("\n");
/*TODO*/  //            }
/*TODO*/  //            result.append(sysMemInfo.toString());
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return result.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void free(int partitionId, int addr, int size) {
/*TODO*/  //        MemoryChunk memoryChunk = new MemoryChunk(addr, size);
/*TODO*/  //        freeMemoryChunks[partitionId].add(memoryChunk);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int alloc(int partitionId, int addr, int size) {
/*TODO*/  //        MemoryChunk allocatedMemoryChunk = freeMemoryChunks[partitionId].alloc(addr, size);
/*TODO*/  //        if (allocatedMemoryChunk == null) {
/*TODO*/  //            return 0;
/*TODO*/  //        }
/*TODO*/  //        return allocatedMemoryChunk.addr;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void free(SysMemInfo info) {
/*TODO*/  //        if (info != null) {
/*TODO*/  //            info.free();
/*TODO*/  //            free(info.partitionid, info.addr, info.allocatedSize);
/*TODO*/  //
/*TODO*/  //            if (log.isDebugEnabled()) {
/*TODO*/  //                log.debug(String.format("free %s", info.toString()));
/*TODO*/  //                if (log.isTraceEnabled()) {
/*TODO*/  //                    log.trace("Free list after free: " + getDebugFreeMem());
/*TODO*/  //                    log.trace("Allocated blocks after free:\n" + getDebugAllocatedMem() + "\n");
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int maxFreeMemSize(int partitionid) {
/*TODO*/  //        int maxFreeMemSize = 0;
/*TODO*/  //        if (isValidPartitionId(partitionid)) {
/*TODO*/  //            for (MemoryChunk memoryChunk = freeMemoryChunks[partitionid].getLowMemoryChunk(); memoryChunk !=
          //            null; memoryChunk = memoryChunk.next) {
/*TODO*/  //                if (memoryChunk.size > maxFreeMemSize) {
/*TODO*/  //                    maxFreeMemSize = memoryChunk.size;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //        return maxFreeMemSize;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int totalFreeMemSize(int partitionid) {
/*TODO*/  //        int totalFreeMemSize = 0;
/*TODO*/  //        if (isValidPartitionId(partitionid)) {
/*TODO*/  //            for (MemoryChunk memoryChunk = freeMemoryChunks[partitionid].getLowMemoryChunk(); memoryChunk !=
          //            null; memoryChunk = memoryChunk.next) {
/*TODO*/  //                totalFreeMemSize += memoryChunk.size;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return totalFreeMemSize;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public SysMemInfo getSysMemInfo(int uid) {
/*TODO*/  //        return blockList.get(uid);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public SysMemInfo getSysMemInfoByAddress(int address) {
/*TODO*/  //        for (SysMemInfo info : blockList.values()) {
/*TODO*/  //            if (address >= info.addr && address < info.addr + info.size) {
/*TODO*/  //                return info;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return null;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public SysMemInfo separateMemoryBlock(SysMemInfo info, int size) {
/*TODO*/  //        int newAddr = info.addr + size;
/*TODO*/  //        int newSize = info.size - size;
/*TODO*/  //        int newAllocatedSize = info.allocatedSize - size;
/*TODO*/  //
/*TODO*/  //        // Create a new memory block
/*TODO*/  //        SysMemInfo newSysMemInfo = new SysMemInfo(info.partitionid, info.name, info.type, newSize,
          //        newAllocatedSize, newAddr);
/*TODO*/  //
/*TODO*/  //        // Resize the previous memory block
/*TODO*/  //        info.size -= newSize;
/*TODO*/  //        info.allocatedSize -= newAllocatedSize;
/*TODO*/  //
/*TODO*/  //        return newSysMemInfo;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public boolean resizeMemoryBlock(SysMemInfo info, int leftShift, int rightShift) {
/*TODO*/  //        if (rightShift < 0) {
/*TODO*/  //            int sizeToFree = -rightShift;
/*TODO*/  //            free(info.partitionid, info.addr + info.allocatedSize - sizeToFree, sizeToFree);
/*TODO*/  //            info.allocatedSize -= sizeToFree;
/*TODO*/  //            info.size -= sizeToFree;
/*TODO*/  //        } else if (rightShift > 0) {
/*TODO*/  //            int sizeToExtend = rightShift;
/*TODO*/  //            int extendAddr = alloc(info.partitionid, info.addr + info.allocatedSize, sizeToExtend);
/*TODO*/  //            if (extendAddr == 0) {
/*TODO*/  //                return false;
/*TODO*/  //            }
/*TODO*/  //            info.allocatedSize += sizeToExtend;
/*TODO*/  //            info.size += sizeToExtend;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (leftShift < 0) {
/*TODO*/  //            int sizeToFree = -leftShift;
/*TODO*/  //            free(info.partitionid, info.addr, sizeToFree);
/*TODO*/  //            info.addr += sizeToFree;
/*TODO*/  //            info.size -= sizeToFree;
/*TODO*/  //            info.allocatedSize -= sizeToFree;
/*TODO*/  //        } else if (leftShift > 0) {
/*TODO*/  //            int sizeToExtend = leftShift;
/*TODO*/  //            int extendAddr = alloc(info.partitionid, info.addr - sizeToExtend, sizeToExtend);
/*TODO*/  //            if (extendAddr == 0) {
/*TODO*/  //                return false;
/*TODO*/  //            }
/*TODO*/  //            info.addr -= sizeToExtend;
/*TODO*/  //            info.allocatedSize += sizeToExtend;
/*TODO*/  //            info.size += sizeToExtend;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return true;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * @param firmwareVersion : in this format: ABB, where A = major and B =
/*TODO*/  //     * minor, for example 271
/*TODO*/  //     */
/*TODO*/  //    public void setFirmwareVersion(int firmwareVersion) {
/*TODO*/  //        this.firmwareVersion = firmwareVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getFirmwareVersion() {
/*TODO*/  //        return firmwareVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // note: we're only looking at user memory, so 0x08800000 - 0x0A000000
/*TODO*/  //    // this is mainly to make it fit on one console line
/*TODO*/  //    public void dumpSysMemInfo() {
/*TODO*/  //        final int MEMORY_SIZE = 0x1800000;
/*TODO*/  //        final int SLOT_COUNT = 64; // 0x60000
/*TODO*/  //        final int SLOT_SIZE = MEMORY_SIZE / SLOT_COUNT; // 0x60000
/*TODO*/  //        boolean[] allocated = new boolean[SLOT_COUNT];
/*TODO*/  //        boolean[] fragmented = new boolean[SLOT_COUNT];
/*TODO*/  //        int allocatedSize = 0;
/*TODO*/  //        int fragmentedSize = 0;
/*TODO*/  //
/*TODO*/  //        for (Iterator<SysMemInfo> it = blockList.values().iterator(); it.hasNext();) {
/*TODO*/  //            SysMemInfo info = it.next();
/*TODO*/  //            for (int i = info.addr; i < info.addr + info.size; i += SLOT_SIZE) {
/*TODO*/  //                if (i >= 0x08800000 && i < 0x0A000000) {
/*TODO*/  //                    allocated[(i - 0x08800000) / SLOT_SIZE] = true;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            allocatedSize += info.size;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        for (MemoryChunk memoryChunk = freeMemoryChunks[USER_PARTITION_ID].getLowMemoryChunk(); memoryChunk
          //        != null; memoryChunk = memoryChunk.next) {
/*TODO*/  //            for (int i = memoryChunk.addr; i < memoryChunk.addr + memoryChunk.size; i += SLOT_SIZE) {
/*TODO*/  //                if (i >= 0x08800000 && i < 0x0A000000) {
/*TODO*/  //                    fragmented[(i - 0x08800000) / SLOT_SIZE] = true;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            fragmentedSize += memoryChunk.size;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        StringBuilder allocatedDiagram = new StringBuilder();
/*TODO*/  //        allocatedDiagram.append("[");
/*TODO*/  //        for (int i = 0; i < SLOT_COUNT; i++) {
/*TODO*/  //            allocatedDiagram.append(allocated[i] ? "X" : " ");
/*TODO*/  //        }
/*TODO*/  //        allocatedDiagram.append("]");
/*TODO*/  //
/*TODO*/  //        StringBuilder fragmentedDiagram = new StringBuilder();
/*TODO*/  //        fragmentedDiagram.append("[");
/*TODO*/  //        for (int i = 0; i < SLOT_COUNT; i++) {
/*TODO*/  //            fragmentedDiagram.append(fragmented[i] ? "X" : " ");
/*TODO*/  //        }
/*TODO*/  //        fragmentedDiagram.append("]");
/*TODO*/  //
/*TODO*/  //        DumpDebugState.log("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
/*TODO*/  //        DumpDebugState.log(String.format("Allocated memory:  %08X %d bytes", allocatedSize, allocatedSize));
/*TODO*/  //        DumpDebugState.log(allocatedDiagram.toString());
/*TODO*/  //        DumpDebugState.log(String.format("Fragmented memory: %08X %d bytes", fragmentedSize,
          //        fragmentedSize));
/*TODO*/  //        DumpDebugState.log(fragmentedDiagram.toString());
/*TODO*/  //
/*TODO*/  //        DumpDebugState.log("Free list: " + getDebugFreeMem());
/*TODO*/  //        DumpDebugState.log("Allocated blocks:\n" + getDebugAllocatedMem() + "\n");
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String hleKernelSprintf(CpuState cpu, String format, Object[] formatParameters) {
/*TODO*/  //        String formattedMsg = format;
/*TODO*/  //        try {
/*TODO*/  //            // Translate the C-like format string to a Java format string:
/*TODO*/  //            // - %u or %i -> %d
/*TODO*/  //            // - %4u -> %4d
/*TODO*/  //            // - %lld or %ld -> %d
/*TODO*/  //            // - %llx or %lx -> %x
/*TODO*/  //            // - %p -> %08X
/*TODO*/  //            String javaMsg = format;
/*TODO*/  //            javaMsg = javaMsg.replaceAll("\\%(\\d*)l?l?[uid]", "%$1d");
/*TODO*/  //            javaMsg = javaMsg.replaceAll("\\%(\\d*)l?l?([xX])", "%$1$2");
/*TODO*/  //            javaMsg = javaMsg.replaceAll("\\%p", "%08X");
/*TODO*/  //
/*TODO*/  //            // Support for "%s" (at any place and can occur multiple times)
/*TODO*/  //            int index = -1;
/*TODO*/  //            for (int parameterIndex = 0; parameterIndex < formatParameters.length; parameterIndex++) {
/*TODO*/  //                index = javaMsg.indexOf('%', index + 1);
/*TODO*/  //                if (index < 0) {
/*TODO*/  //                    break;
/*TODO*/  //                }
/*TODO*/  //                String parameterFormat = javaMsg.substring(index);
/*TODO*/  //                if (parameterFormat.startsWith("%s")) {
/*TODO*/  //                    // Convert an integer address to a String by reading
/*TODO*/  //                    // the String at the given address
/*TODO*/  //                    int address = ((Integer) formatParameters[parameterIndex]).intValue();
/*TODO*/  //                    if (address == 0) {
/*TODO*/  //                        formatParameters[parameterIndex] = "(null)";
/*TODO*/  //                    } else {
/*TODO*/  //                        formatParameters[parameterIndex] = Utilities.readStringZ(address);
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // String.format: If there are more arguments than format specifiers, the extra arguments are
          //            ignored.
/*TODO*/  //            formattedMsg = String.format(javaMsg, formatParameters);
/*TODO*/  //        } catch (Exception e) {
/*TODO*/  //            // Ignore formatting exception
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return formattedMsg;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String hleKernelSprintf(CpuState cpu, String format, int firstRegister) {
/*TODO*/  //        // For now, use only the 7 register parameters: $a1-$a3, $t0-$t3
/*TODO*/  //        // Further parameters are retrieved from the stack (assume max. 10 stack parameters).
/*TODO*/  //        int registerParameters = _t3 - firstRegister + 1;
/*TODO*/  //        Object[] formatParameters = new Object[registerParameters + 10];
/*TODO*/  //        for (int i = 0; i < registerParameters; i++) {
/*TODO*/  //            formatParameters[i] = cpu.getRegister(firstRegister + i);
/*TODO*/  //        }
/*TODO*/  //        Memory mem = Memory.getInstance();
/*TODO*/  //        for (int i = registerParameters; i < formatParameters.length; i++) {
/*TODO*/  //            formatParameters[i] = mem.read32(cpu._sp + ((i - registerParameters) << 2));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return hleKernelSprintf(cpu, format, formatParameters);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int hleKernelPrintf(CpuState cpu, PspString formatString, Logger logger) {
/*TODO*/  //        // Format and print the message to the logger
/*TODO*/  //        if (logger.isInfoEnabled()) {
/*TODO*/  //            String formattedMsg = hleKernelSprintf(cpu, formatString.getString(), _a1);
/*TODO*/  //            logger.info(formattedMsg);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int hleKernelGetCompiledSdkVersion() {
/*TODO*/  //        return compiledSdkVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void hleSetCompiledSdkVersion(int sdkVersion) {
/*TODO*/  //        compiledSdkVersion = sdkVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int hleKernelGetCompilerVersion() {
/*TODO*/  //        return compilerVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xA291F107, version = 150)
/*TODO*/  //    public int sceKernelMaxFreeMemSize() {
/*TODO*/  //        int maxFreeMemSize = maxFreeMemSize(USER_PARTITION_ID);
/*TODO*/  //
/*TODO*/  //        // Some games expect size to be rounded down in 16 bytes block
/*TODO*/  //        maxFreeMemSize &= ~15;
/*TODO*/  //
/*TODO*/  //        if (log.isDebugEnabled()) {
/*TODO*/  //            log.debug(String.format("sceKernelMaxFreeMemSize returning %d(hex=0x%1$X)", maxFreeMemSize));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return maxFreeMemSize;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xF919F628, version = 150)
/*TODO*/  //    public int sceKernelTotalFreeMemSize() {
/*TODO*/  //        int totalFreeMemSize = totalFreeMemSize(USER_PARTITION_ID);
/*TODO*/  //        if (log.isDebugEnabled()) {
/*TODO*/  //            log.debug(String.format("sceKernelTotalFreeMemSize returning %d(hex=0x%1$X)",
          //            totalFreeMemSize));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return totalFreeMemSize;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0x237DBD4F, version = 150)
/*TODO*/  //    @HLEFunction(nid = 0x7158CE7E, version = 660)
/*TODO*/  //    public int sceKernelAllocPartitionMemory(int partitionid, String name, int type, int size, int addr) {
/*TODO*/  //        addr &= Memory.addressMask;
/*TODO*/  //
/*TODO*/  //        if (type < PSP_SMEM_Low || type > PSP_SMEM_HighAligned) {
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_ILLEGAL_MEMBLOCK_ALLOC_TYPE;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        SysMemInfo info = malloc(partitionid, name, type, size, addr);
/*TODO*/  //        if (info == null) {
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_FAILED_ALLOC_MEMBLOCK;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return info.uid;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xB6D61D02, version = 150)
/*TODO*/  //    @HLEFunction(nid = 0xC1A26C6F, version = 660)
/*TODO*/  //    public int sceKernelFreePartitionMemory(int uid) {
/*TODO*/  //        SceUidManager.checkUidPurpose(uid, "SysMem", true);
/*TODO*/  //
/*TODO*/  //        SysMemInfo info = blockList.remove(uid);
/*TODO*/  //        if (info == null) {
/*TODO*/  //            log.warn(String.format("sceKernelFreePartitionMemory unknown uid=0x%X", uid));
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_ILLEGAL_CHUNK_ID;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        free(info);
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0x9D9A5BA1, version = 150)
/*TODO*/  //    @HLEFunction(nid = 0xF12A62F7, version = 660)
/*TODO*/  //    public int sceKernelGetBlockHeadAddr(int uid) {
/*TODO*/  //        SceUidManager.checkUidPurpose(uid, "SysMem", true);
/*TODO*/  //
/*TODO*/  //        SysMemInfo info = blockList.get(uid);
/*TODO*/  //        if (info == null) {
/*TODO*/  //            log.warn(String.format("sceKernelGetBlockHeadAddr unknown uid=0x%X", uid));
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_ILLEGAL_CHUNK_ID;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return info.addr;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0x13A5ABEF, version = 150)
/*TODO*/  //    public int sceKernelPrintf(CpuState cpu, PspString formatString) {
/*TODO*/  //        return hleKernelPrintf(cpu, formatString, stdout);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0x3FC9AE6A, version = 150)
/*TODO*/  //    @HLEFunction(nid = 0xC886B169, version = 660)
/*TODO*/  //    public int sceKernelDevkitVersion() {
/*TODO*/  //        int major = firmwareVersion / 100;
/*TODO*/  //        int minor = (firmwareVersion / 10) % 10;
/*TODO*/  //        int revision = firmwareVersion % 10;
/*TODO*/  //        int devkitVersion = (major << 24) | (minor << 16) | (revision << 8) | 0x10;
/*TODO*/  //        if (log.isDebugEnabled()) {
/*TODO*/  //            log.debug(String.format("sceKernelDevkitVersion returning 0x%08X", devkitVersion));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return devkitVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xD8DE5C1E, version = 150)
/*TODO*/  //    public int SysMemUserForUser_D8DE5C1E() {
/*TODO*/  //        // Seems to always return 0...
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xFC114573, version = 200)
/*TODO*/  //    @HLEFunction(nid = 0xB4F00CB5, version = 660)
/*TODO*/  //    public int sceKernelGetCompiledSdkVersion() {
/*TODO*/  //        if (log.isDebugEnabled()) {
/*TODO*/  //            log.debug(String.format("sceKernelGetCompiledSdkVersion returning 0x%08X", compiledSdkVersion));
/*TODO*/  //        }
/*TODO*/  //        return compiledSdkVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0x7591C7DB, version = 200)
/*TODO*/  //    @HLEFunction(nid = 0x342061E5, version = 370)
/*TODO*/  //    @HLEFunction(nid = 0x315AD3A0, version = 380)
/*TODO*/  //    @HLEFunction(nid = 0xEBD5C3E6, version = 395)
/*TODO*/  //    @HLEFunction(nid = 0x91DE343C, version = 500)
/*TODO*/  //    @HLEFunction(nid = 0x7893F79A, version = 507)
/*TODO*/  //    @HLEFunction(nid = 0x35669D4C, version = 600)
/*TODO*/  //    @HLEFunction(nid = 0x1B4217BC, version = 603)
/*TODO*/  //    @HLEFunction(nid = 0x358CA1BB, version = 606)
/*TODO*/  //    public int sceKernelSetCompiledSdkVersion(int sdkVersion) {
/*TODO*/  //        hleSetCompiledSdkVersion(sdkVersion);
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xF77D77CB, version = 200)
/*TODO*/  //    public int sceKernelSetCompilerVersion(int compilerVersion) {
/*TODO*/  //        this.compilerVersion = compilerVersion;
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEUnimplemented
/*TODO*/  //    @HLEFunction(nid = 0xA6848DF8, version = 200)
/*TODO*/  //    public int SysMemUserForUser_A6848DF8() {
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0x2A3E5280, version = 280)
/*TODO*/  //    public int sceKernelQueryMemoryInfo(int address, @CanBeNull @BufferInfo(usage = Usage.out) TPointer32
          //    partitionId, @CanBeNull @BufferInfo(usage = Usage.out) TPointer32 memoryBlockId) {
/*TODO*/  //        int result = SceKernelErrors.ERROR_KERNEL_ILLEGAL_ADDR;
/*TODO*/  //
/*TODO*/  //        for (Integer key : blockList.keySet()) {
/*TODO*/  //            SysMemInfo info = blockList.get(key);
/*TODO*/  //            if (info != null && info.addr <= address && address < info.addr + info.size) {
/*TODO*/  //                partitionId.setValue(info.partitionid);
/*TODO*/  //                memoryBlockId.setValue(info.uid);
/*TODO*/  //                result = 0;
/*TODO*/  //                break;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return result;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEUnimplemented
/*TODO*/  //    @HLEFunction(nid = 0x39F49610, version = 280)
/*TODO*/  //    public int sceKernelGetPTRIG() {
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEUnimplemented
/*TODO*/  //    @HLEFunction(nid = 0x6231A71D, version = 280)
/*TODO*/  //    public int sceKernelSetPTRIG() {
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // sceKernelFreeMemoryBlock (internal name)
/*TODO*/  //    @HLEFunction(nid = 0x50F61D8A, version = 352)
/*TODO*/  //    public int SysMemUserForUser_50F61D8A(int uid) {
/*TODO*/  //        SysMemInfo info = blockList.remove(uid);
/*TODO*/  //        if (info == null) {
/*TODO*/  //            log.warn("SysMemUserForUser_50F61D8A(uid=0x" + Integer.toHexString(uid) + ") unknown uid");
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_UNKNOWN_UID;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        free(info);
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @HLEFunction(nid = 0xACBD88CA, version = 352)
/*TODO*/  //    public int sceKernelTotalMemSize() {
/*TODO*/  //        return MemoryMap.SIZE_RAM;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // sceKernelGetMemoryBlockAddr (internal name)
/*TODO*/  //    @HLEFunction(nid = 0xDB83A952, version = 352)
/*TODO*/  //    public int SysMemUserForUser_DB83A952(int uid, TPointer32 addr) {
/*TODO*/  //        SysMemInfo info = blockList.get(uid);
/*TODO*/  //        if (info == null) {
/*TODO*/  //            log.warn(String.format("SysMemUserForUser_DB83A952 uid=0x%X, addr=%s: unknown uid", uid, addr));
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_UNKNOWN_UID;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        addr.setValue(info.addr);
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // sceKernelAllocMemoryBlock (internal name)
/*TODO*/  //    @HLEFunction(nid = 0xFE707FDF, version = 352)
/*TODO*/  //    public int SysMemUserForUser_FE707FDF(@StringInfo(maxLength = 32) PspString name, int type, int size,
          //    @CanBeNull TPointer paramsAddr) {
/*TODO*/  //        if (paramsAddr.isNotNull()) {
/*TODO*/  //            int length = paramsAddr.getValue32();
/*TODO*/  //            if (length != 4) {
/*TODO*/  //                log.warn(String.format("SysMemUserForUser_FE707FDF: unknown parameters with length=%d",
          //                length));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (type < PSP_SMEM_Low || type > PSP_SMEM_High) {
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_ILLEGAL_MEMBLOCK_ALLOC_TYPE;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Always allocate memory in user area (partitionid == 2).
/*TODO*/  //        SysMemInfo info = malloc(SysMemUserForUser.USER_PARTITION_ID, name.getString(), type, size, 0);
/*TODO*/  //        if (info == null) {
/*TODO*/  //            return SceKernelErrors.ERROR_KERNEL_FAILED_ALLOC_MEMBLOCK;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return info.uid;
/*TODO*/  //    }
/*TODO*/  //}
/*TODO*/  //
