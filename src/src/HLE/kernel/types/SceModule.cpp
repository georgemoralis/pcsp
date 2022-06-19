/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#include "SceModule.h"

/*TODO*/  // public class SceModule {
/*TODO*/  //
/*TODO*/  //    public static final int PSP_MODULE_VSH = 0x0800;
/*TODO*/  //    public static final int PSP_MODULE_KERNEL = 0x1000;
/*TODO*/  //    // PSP info
/*TODO*/  //    public int next; // should be handled by a manager
/*TODO*/  //    public short attribute;
/*TODO*/  //    public int version;
/*TODO*/  //    public String modname; // 27 printable chars
/*TODO*/  //    public final byte terminal = (byte) 0;
/*TODO*/  //    public int status;  // 2 bytes for status + 2 bytes of padding
/*TODO*/  //    public int unk1;
/*TODO*/  //    public int modid;
/*TODO*/  //    public int usermod_thid;
/*TODO*/  //    public int memid;
/*TODO*/  //    public int mpidtext;
/*TODO*/  //    public int mpiddata;
/*TODO*/  //    public int ent_top;
/*TODO*/  //    public int ent_size; // we'll use bytes (instead of number of entries)
/*TODO*/  //    public int stub_top;
/*TODO*/  //    public int stub_size; // we'll use bytes (instead of number of entries)
/*TODO*/  //    public int module_start_func;
/*TODO*/  //    public int module_stop_func;
/*TODO*/  //    public int module_bootstart_func;
/*TODO*/  //    public int module_reboot_before_func;
/*TODO*/  //    public int module_reboot_phase_func;
/*TODO*/  //    public int entry_addr;
/*TODO*/  //    public int gp_value;
/*TODO*/  //    public int text_addr;
/*TODO*/  //    public int text_size;
/*TODO*/  //    public int data_size;
/*TODO*/  //    public int bss_size;
/*TODO*/  //    private final List<SysMemInfo> allocatedMemory = new LinkedList<SysMemInfo>();
/*TODO*/  //    public int nsegment; // usually just 1 segment
/*TODO*/  //    public int[] segmentaddr = new int[4]; // static memory footprint of the module
/*TODO*/  //    public int[] segmentsize = new int[4]; // static memory footprint of the module
/*TODO*/  //    public int module_start_thread_priority;
/*TODO*/  //    public int module_start_thread_stacksize;
/*TODO*/  //    public int module_start_thread_attr;
/*TODO*/  //    public int module_stop_thread_priority;
/*TODO*/  //    public int module_stop_thread_stacksize;
/*TODO*/  //    public int module_stop_thread_attr;
/*TODO*/  //    public int module_reboot_before_thread_priority;
/*TODO*/  //    public int module_reboot_before_thread_stacksize;
/*TODO*/  //    public int module_reboot_before_thread_attr;
/*TODO*/  //
/*TODO*/  //    // internal info
/*TODO*/  //    public int address;
/*TODO*/  //    public final boolean isFlashModule;
/*TODO*/  //    public boolean isLoaded;
/*TODO*/  //    public boolean isStarted;
/*TODO*/  //    public boolean isStopped;
/*TODO*/  //    private static SceModule previousModule; // The last module to be loaded, should be fixed up if that
          //    module gets unloaded
/*TODO*/  //
/*TODO*/  //    // loader stuff
/*TODO*/  //    public int fileFormat; // See Loader class for valid formats
/*TODO*/  //    public String pspfilename; // boot path, for thread argument
/*TODO*/  //    public PSF psf; // for xmb title, etc
/*TODO*/  //    public int moduleVersion;
/*TODO*/  //
/*TODO*/  //    // The space consumed by the program image
/*TODO*/  //    public int loadAddressLow, loadAddressHigh;
/*TODO*/  //    public int baseAddress; // should in theory be the same as loadAddressLow
/*TODO*/  //
/*TODO*/  //    // address/size pairs, used by the debugger/instruction counter
/*TODO*/  //    //public int[] textsection; // see text_addr/text_size
/*TODO*/  //    public int[] initsection;
/*TODO*/  //    public int[] finisection;
/*TODO*/  //    public int[] stubtextsection;
/*TODO*/  //
/*TODO*/  //    // deferred import resolving
/*TODO*/  //    public List<DeferredStub> unresolvedImports;
/*TODO*/  //    public int importFixupAttempts;
/*TODO*/  //    public List<DeferredStub> resolvedImports;
/*TODO*/  //    private List<String> moduleNames = new LinkedList<String>();
/*TODO*/  //
/*TODO*/  //    public SceModule(boolean isFlashModule) {
/*TODO*/  //        this.isFlashModule = isFlashModule;
/*TODO*/  //
/*TODO*/  //        modid = SceUidManager.getNewUid("SceModule");
/*TODO*/  //
/*TODO*/  //        SysMemInfo sysMemInfo =
          //        Modules.SysMemUserForUserModule.malloc(SysMemUserForUser.KERNEL_PARTITION_ID,
          //        String.format("SceModule-0x%X", modid), SysMemUserForUser.PSP_SMEM_HighAligned, sizeOf(), 255);
/*TODO*/  //        addAllocatedMemory(sysMemInfo);
/*TODO*/  //        address = sysMemInfo.addr;
/*TODO*/  //
/*TODO*/  //        // Link SceModule structs together
/*TODO*/  //        if (previousModule != null) {
/*TODO*/  //            previousModule.next = address;
/*TODO*/  //        }
/*TODO*/  //        previousModule = this;
/*TODO*/  //
/*TODO*/  //        // Internal context
/*TODO*/  //        fileFormat = Loader.FORMAT_UNKNOWN;
/*TODO*/  //        //textsection = new int[2];
/*TODO*/  //        initsection = new int[2];
/*TODO*/  //        finisection = new int[2];
/*TODO*/  //        stubtextsection = new int[2];
/*TODO*/  //        unresolvedImports = new LinkedList<DeferredStub>();
/*TODO*/  //        importFixupAttempts = 0;
/*TODO*/  //        resolvedImports = new LinkedList<DeferredStub>();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void addModuleName(String moduleName) {
/*TODO*/  //        if (!moduleNames.contains(moduleName)) {
/*TODO*/  //            moduleNames.add(moduleName);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // State control methods.
/*TODO*/  //    public void load() {
/*TODO*/  //        isLoaded = true;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void unload() {
/*TODO*/  //        // Unresolve all the stubs resolved by an entry in this module
/*TODO*/  //        if (!resolvedImports.isEmpty()) {
/*TODO*/  //            Memory mem = Memory.getInstance();
/*TODO*/  //            for (DeferredStub deferredStub : resolvedImports) {
/*TODO*/  //                deferredStub.unresolve(mem);
/*TODO*/  //            }
/*TODO*/  //            resolvedImports.clear();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Remove all the NID's mapped from this module
/*TODO*/  //        NIDMapper.getInstance().removeModuleNids(modname);
/*TODO*/  //        for (String moduleName : moduleNames) {
/*TODO*/  //            NIDMapper.getInstance().removeModuleNids(moduleName);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        isLoaded = false;
/*TODO*/  //        free();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void start() {
/*TODO*/  //        isStarted = true;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void stop() {
/*TODO*/  //        isStopped = true;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public boolean isModuleLoaded() {
/*TODO*/  //        return isLoaded;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public boolean isModuleStarted() {
/*TODO*/  //        return isStarted;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public boolean isModuleStopped() {
/*TODO*/  //        return isStopped;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * For use when unloading modules.
/*TODO*/  //     */
/*TODO*/  //    public void free() {
/*TODO*/  //        if (!allocatedMemory.isEmpty()) {
/*TODO*/  //            for (SysMemInfo sysMemInfo : allocatedMemory) {
/*TODO*/  //                // Overwrite the allocated memory so that its code can be invalidated
/*TODO*/  //                Memory.getInstance().memset(sysMemInfo.addr, (byte) -1, sysMemInfo.size);
/*TODO*/  //
/*TODO*/  //                Modules.SysMemUserForUserModule.free(sysMemInfo);
/*TODO*/  //            }
/*TODO*/  //            allocatedMemory.clear();
/*TODO*/  //
/*TODO*/  //            HLEModuleManager.getInstance().UnloadFlash0Module(this);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        address = 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void addAllocatedMemory(SysMemInfo sysMemInfo) {
/*TODO*/  //        if (sysMemInfo != null) {
/*TODO*/  //            allocatedMemory.add(sysMemInfo);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void write(Memory mem, int address) {
/*TODO*/  //        mem.write32(address, next);
/*TODO*/  //        mem.write16(address + 4, attribute);
/*TODO*/  //        mem.write16(address + 6, (short) version);
/*TODO*/  //        Utilities.writeStringNZ(mem, address + 8, 28, modname);
/*TODO*/  //        mem.write32(address + 36, status);
/*TODO*/  //        mem.write32(address + 40, unk1);
/*TODO*/  //        mem.write32(address + 44, modid);
/*TODO*/  //        mem.write32(address + 48, usermod_thid);
/*TODO*/  //        mem.write32(address + 52, memid);
/*TODO*/  //        mem.write32(address + 56, mpidtext);
/*TODO*/  //        mem.write32(address + 60, mpiddata);
/*TODO*/  //        mem.write32(address + 64, ent_top);
/*TODO*/  //        mem.write32(address + 68, ent_size);
/*TODO*/  //        mem.write32(address + 72, stub_top);
/*TODO*/  //        mem.write32(address + 76, stub_size);
/*TODO*/  //        mem.write32(address + 80, module_start_func);
/*TODO*/  //        mem.write32(address + 84, module_stop_func);
/*TODO*/  //        mem.write32(address + 88, module_bootstart_func);
/*TODO*/  //        mem.write32(address + 92, module_reboot_before_func);
/*TODO*/  //        mem.write32(address + 96, module_reboot_phase_func);
/*TODO*/  //        mem.write32(address + 100, entry_addr);
/*TODO*/  //        mem.write32(address + 104, gp_value);
/*TODO*/  //        mem.write32(address + 108, text_addr);
/*TODO*/  //        mem.write32(address + 112, text_size);
/*TODO*/  //        mem.write32(address + 116, data_size);
/*TODO*/  //        mem.write32(address + 120, bss_size);
/*TODO*/  //        mem.write32(address + 124, nsegment);
/*TODO*/  //        mem.write32(address + 128, segmentaddr[0]);
/*TODO*/  //        mem.write32(address + 132, segmentaddr[1]);
/*TODO*/  //        mem.write32(address + 136, segmentaddr[2]);
/*TODO*/  //        mem.write32(address + 140, segmentaddr[3]);
/*TODO*/  //        mem.write32(address + 144, segmentsize[0]);
/*TODO*/  //        mem.write32(address + 148, segmentsize[1]);
/*TODO*/  //        mem.write32(address + 152, segmentsize[2]);
/*TODO*/  //        mem.write32(address + 156, segmentsize[3]);
/*TODO*/  //        mem.write32(address + 160, module_start_thread_priority);
/*TODO*/  //        mem.write32(address + 164, module_start_thread_stacksize);
/*TODO*/  //        mem.write32(address + 168, module_start_thread_attr);
/*TODO*/  //        mem.write32(address + 172, module_stop_thread_priority);
/*TODO*/  //        mem.write32(address + 176, module_stop_thread_stacksize);
/*TODO*/  //        mem.write32(address + 180, module_stop_thread_attr);
/*TODO*/  //        mem.write32(address + 184, module_reboot_before_thread_priority);
/*TODO*/  //        mem.write32(address + 188, module_reboot_before_thread_stacksize);
/*TODO*/  //        mem.write32(address + 192, module_reboot_before_thread_attr);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void read(Memory mem, int address) {
/*TODO*/  //        next = mem.read32(address);
/*TODO*/  //        attribute = (short) mem.read16(address + 4);
/*TODO*/  //        version = mem.read16(address + 6);
/*TODO*/  //        modname = Utilities.readStringNZ(mem, address + 8, 28);
/*TODO*/  //        status = mem.read32(address + 36);
/*TODO*/  //        unk1 = mem.read32(address + 40);
/*TODO*/  //        modid = mem.read32(address + 44);
/*TODO*/  //        usermod_thid = mem.read32(address + 48);
/*TODO*/  //        memid = mem.read32(address + 52);
/*TODO*/  //        mpidtext = mem.read32(address + 56);
/*TODO*/  //        mpiddata = mem.read32(address + 60);
/*TODO*/  //        ent_top = mem.read32(address + 64);
/*TODO*/  //        ent_size = mem.read32(address + 68);
/*TODO*/  //        stub_top = mem.read32(address + 72);
/*TODO*/  //        stub_size = mem.read32(address + 76);
/*TODO*/  //        module_start_func = mem.read32(address + 80);
/*TODO*/  //        module_stop_func = mem.read32(address + 84);
/*TODO*/  //        module_bootstart_func = mem.read32(address + 88);
/*TODO*/  //        module_reboot_before_func = mem.read32(address + 92);
/*TODO*/  //        module_reboot_phase_func = mem.read32(address + 96);
/*TODO*/  //        entry_addr = mem.read32(address + 100);
/*TODO*/  //        gp_value = mem.read32(address + 104);
/*TODO*/  //        text_addr = mem.read32(address + 108);
/*TODO*/  //        text_size = mem.read32(address + 112);
/*TODO*/  //        data_size = mem.read32(address + 116);
/*TODO*/  //        bss_size = mem.read32(address + 120);
/*TODO*/  //        nsegment = mem.read32(address + 124);
/*TODO*/  //        segmentaddr[0] = mem.read32(address + 128);
/*TODO*/  //        segmentaddr[1] = mem.read32(address + 132);
/*TODO*/  //        segmentaddr[2] = mem.read32(address + 136);
/*TODO*/  //        segmentaddr[3] = mem.read32(address + 140);
/*TODO*/  //        segmentsize[0] = mem.read32(address + 144);
/*TODO*/  //        segmentsize[1] = mem.read32(address + 148);
/*TODO*/  //        segmentsize[2] = mem.read32(address + 152);
/*TODO*/  //        segmentsize[3] = mem.read32(address + 156);
/*TODO*/  //        module_start_thread_priority = mem.read32(address + 160);
/*TODO*/  //        module_start_thread_stacksize = mem.read32(address + 164);
/*TODO*/  //        module_start_thread_attr = mem.read32(address + 168);
/*TODO*/  //        module_stop_thread_priority = mem.read32(address + 172);
/*TODO*/  //        module_stop_thread_stacksize = mem.read32(address + 176);
/*TODO*/  //        module_stop_thread_attr = mem.read32(address + 180);
/*TODO*/  //        module_reboot_before_thread_priority = mem.read32(address + 184);
/*TODO*/  //        module_reboot_before_thread_stacksize = mem.read32(address + 188);
/*TODO*/  //        module_reboot_before_thread_attr = mem.read32(address + 192);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * initialise ourself from a PSPModuleInfo object. PSPModuleInfo object
/*TODO*/  //     * comes from the loader/ELF.
/*TODO*/  //     */
/*TODO*/  //    public void copy(PSPModuleInfo moduleInfo) {
/*TODO*/  //        attribute = (short) (moduleInfo.getM_attr() & 0xFFFF);
/*TODO*/  //        version = moduleInfo.getM_version();
/*TODO*/  //        modname = moduleInfo.getM_namez();
/*TODO*/  //        gp_value = (int) (moduleInfo.getM_gp() & 0xFFFFFFFFL);
/*TODO*/  //        ent_top = (int) moduleInfo.getM_exports();
/*TODO*/  //        ent_size = (int) moduleInfo.getM_exp_end() - ent_top;
/*TODO*/  //        stub_top = (int) moduleInfo.getM_imports();
/*TODO*/  //        stub_size = (int) moduleInfo.getM_imp_end() - stub_top;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int sizeOf() {
/*TODO*/  //        return 196;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public String toString() {
/*TODO*/  //        StringBuilder s = new StringBuilder("SceModule ");
/*TODO*/  //        if (modname != null) {
/*TODO*/  //            s.append(String.format("'%s'", modname));
/*TODO*/  //        } else if (pspfilename != null) {
/*TODO*/  //            s.append(String.format("'%s'", pspfilename));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return s.toString();
/*TODO*/  //    }
/*TODO*/  //}
