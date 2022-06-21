/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#include "PCSPCommon.h"
#include "Emulator.h"
#include "HLE/kernel/types/SceModule.h"
#include "Memory.h"
#include "Loader.h"
#include "format/Elf32Header.h"
#include "format/Elf32ProgramHeader.h"
#include "format/Elf32SectionHeader.h"
#include "format/Elf32.h"
#include "format/PBP.h"

/*TODO*/  //    private static Loader instance;
/*TODO*/  //    private static Logger log = Logger.getLogger("loader");
/*TODO*/  //
/*TODO*/  //    public final static int SCE_MAGIC = 0x4543537E;
/*TODO*/  //    public final static int PSP_MAGIC = 0x50535000;
/*TODO*/  //    public final static int EDAT_MAGIC = 0x54414445;
/*TODO*/  //    public final static int FIRMWAREVERSION_HOMEBREW = 999; // Simulate version 9.99 instead of 1.50
/*TODO*/  //

/*TODO*/  //
/*TODO*/  //    public static Loader getInstance() {
/*TODO*/  //        if (instance == null)
/*TODO*/  //            instance = new Loader();
/*TODO*/  //        return instance;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private Loader() {
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * @param pspfilename   Example:
/*TODO*/  //     *                      ms0:/PSP/GAME/xxx/EBOOT.PBP
/*TODO*/  //     *                      disc0:/PSP_GAME/SYSDIR/BOOT.BIN
/*TODO*/  //     *                      disc0:/PSP_GAME/SYSDIR/EBOOT.BIN
/*TODO*/  //     *                      xxx:/yyy/zzz.prx
/*TODO*/  //     * @param f             the module file contents
/*TODO*/  //     * @param baseAddress   should be at least 64-byte aligned,
/*TODO*/  //     *                      or how ever much is the default alignment in pspsysmem.
/*TODO*/  //     * @param analyzeOnly   true, if the module is not really loaded, but only
/*TODO*/  //     *                            the SceModule object is returned;
/*TODO*/  //     *                      false, if the module is really loaded in memory.
/*TODO*/  //     * @return              Always a SceModule object, you should check the
/*TODO*/  //     *                      fileFormat member against the FORMAT_* bits.
/*TODO*/  //     *                      Example: (fileFormat & FORMAT_ELF) == FORMAT_ELF
/*TODO*/  //     **/
SceModule* Loader::LoadModule(std::string pspfilename, std::ifstream& f, u32& baseAddress, int mpidText, int mpidData,
    bool analyzeOnly, bool allocMem, bool fromSyscall, bool isSignChecked, u8* key) {
        std::unique_ptr<SceModule> _module(new SceModule(false));

        u32 currentOffset = f.tellg();
        f.seekg(0, std::ios::end);
        u32 size = f.tellg();
        f.seekg(currentOffset);
        /*TODO*/  //        module.fileFormat = FORMAT_UNKNOWN;
/*TODO*/  //        module.pspfilename = pspfilename;
/*TODO*/  //        module.mpidtext = mpidText;
/*TODO*/  //        module.mpiddata = mpidData;
/*TODO*/  //
/*TODO*/  //        // The PSP startup code requires a ":" into the argument passed to the root thread.
/*TODO*/  //        // On Linux, there is no ":" in the file name when loading a .pbp file;
/*TODO*/  //        // on Windows, there is luckily one ":" in "C:/...".
/*TODO*/  //        // Simulate a ":" by prefixing by "ms0:", as this is not really used by an application.
/*TODO*/  //        if (module.pspfilename != null && !module.pspfilename.contains(":")) {
/*TODO*/  //        	module.pspfilename = "ms0:" + module.pspfilename;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (f.capacity() - f.position() == 0) {
/*TODO*/  //            log.error("LoadModule: no data.");
/*TODO*/  //            return module;
/*TODO*/  //        }
/*TODO*/  //
        // chain loaders
        do {
            f.seekg(currentOffset);
            if (LoadPBP(f, _module.get(), baseAddress, analyzeOnly, allocMem, fromSyscall)) {
                // probably kxploit stub
                currentOffset = f.tellg();
                if (currentOffset == size) break;
            }
            else if (!fromSyscall) {
                assert(0);
                /*TODO*/  //                loadPSF(module, analyzeOnly, allocMem, fromSyscall);
            }
/*TODO*/  //
/*TODO*/  //            if (module.psf != null) {
/*TODO*/  //                log.info(String.format("PBP meta data:%s%s", System.lineSeparator(), module.psf));
/*TODO*/  //
/*TODO*/  //                if (!fromSyscall) {
/*TODO*/  //                    // Set firmware version from PSF embedded in PBP
/*TODO*/  //                	if (module.psf.isLikelyHomebrew()) {
/*TODO*/  //                		Emulator.getInstance().setFirmwareVersion(FIRMWAREVERSION_HOMEBREW);
/*TODO*/  //                	} else {
/*TODO*/  //                		Emulator.getInstance().setFirmwareVersion(module.psf.getString("PSP_SYSTEM_VER"));
/*TODO*/  //                	}
/*TODO*/  //                    Modules.SysMemUserForUserModule.setMemory64MB(module.psf.getNumeric("MEMSIZE") == 1);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            f.position(currentOffset);
/*TODO*/  //            if (LoadSPRX(f, module, baseAddress, analyzeOnly, allocMem, fromSyscall, isSignChecked, key)) {
/*TODO*/  //                break;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            f.position(currentOffset);
/*TODO*/  //            if (LoadSCE(f, module, baseAddress, analyzeOnly, allocMem, fromSyscall, isSignChecked, key)) {
/*TODO*/  //                break;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            f.position(currentOffset);
/*TODO*/  //            if (LoadPSP(f, module, baseAddress, analyzeOnly, allocMem, fromSyscall, isSignChecked, key)) {
/*TODO*/  //                break;
/*TODO*/  //            }
/*TODO*/  //
            f.seekg(currentOffset);
            if (LoadELF(f, _module.get(), baseAddress, size,analyzeOnly, allocMem, fromSyscall)) {
/*TODO*/  //            	if (!fromSyscall) {
/*TODO*/  //            		Emulator.getInstance().setFirmwareVersion(FIRMWAREVERSION_HOMEBREW);
/*TODO*/  //            	}
                break;
            }
/*TODO*/  //
/*TODO*/  //            f.position(currentOffset);
/*TODO*/  //            LoadUNK(f, module, baseAddress, analyzeOnly, allocMem, fromSyscall);
        } while (false);
/*TODO*/  //
/*TODO*/  //        if (!analyzeOnly) {
/*TODO*/  //        	patchModule(module);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (analyzeOnly) {
/*TODO*/  //        	module.free();
/*TODO*/  //        }
/*TODO*/  //
        return _module.get();
   }
/*TODO*/  //
/*TODO*/  //    private void loadPSF(SceModule module, boolean analyzeOnly, boolean allocMem, boolean fromSyscall) {
/*TODO*/  //        if (module.psf != null)
/*TODO*/  //            return;
/*TODO*/  //
/*TODO*/  //        String filetoload = module.pspfilename;
/*TODO*/  //        if (filetoload.startsWith("ms0:"))
/*TODO*/  //            filetoload = filetoload.replace("ms0:", "ms0");
/*TODO*/  //
/*TODO*/  //        // PBP doesn't have a PSF included. Check for one in kxploit directories
/*TODO*/  //        File metapbp = null;
/*TODO*/  //        File pbpfile = new File(filetoload);
/*TODO*/  //        if (pbpfile.getParentFile() == null ||
/*TODO*/  //            pbpfile.getParentFile().getParentFile() == null) {
/*TODO*/  //            // probably dynamically loading a prx
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // %__SCE__kxploit
/*TODO*/  //        File metadir = new File(pbpfile.getParentFile().getParentFile().getPath()
/*TODO*/  //                + File.separatorChar + "%" + pbpfile.getParentFile().getName());
/*TODO*/  //        if (metadir.exists()) {
/*TODO*/  //            File[] eboot = metadir.listFiles(new FileFilter() {
/*TODO*/  //                @Override
/*TODO*/  //                public boolean accept(File arg0) {
/*TODO*/  //                    return arg0.getName().equalsIgnoreCase("eboot.pbp");
/*TODO*/  //                }
/*TODO*/  //            });
/*TODO*/  //            if (eboot.length > 0)
/*TODO*/  //                metapbp = eboot[0];
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // kxploit%
/*TODO*/  //        metadir = new File(pbpfile.getParentFile().getParentFile().getPath()
/*TODO*/  //                + File.separatorChar + pbpfile.getParentFile().getName() + "%");
/*TODO*/  //        if (metadir.exists()) {
/*TODO*/  //            File[] eboot = metadir.listFiles(new FileFilter() {
/*TODO*/  //                @Override
/*TODO*/  //                public boolean accept(File arg0) {
/*TODO*/  //                    return arg0.getName().equalsIgnoreCase("eboot.pbp");
/*TODO*/  //                }
/*TODO*/  //            });
/*TODO*/  //            if (eboot.length > 0)
/*TODO*/  //                metapbp = eboot[0];
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (metapbp != null) {
/*TODO*/  //            // Load PSF embedded in PBP
/*TODO*/  //            FileChannel roChannel;
/*TODO*/  //            try {
/*TODO*/  //            	RandomAccessFile raf = new RandomAccessFile(metapbp, "r");
/*TODO*/  //                roChannel = raf.getChannel();
/*TODO*/  //                ByteBuffer readbuffer = roChannel.map(FileChannel.MapMode.READ_ONLY, 0,
          //                (int)roChannel.size());
/*TODO*/  //                PBP meta = new PBP(readbuffer);
/*TODO*/  //                module.psf = meta.readPSF(readbuffer);
/*TODO*/  //                raf.close();
/*TODO*/  //            } catch (FileNotFoundException e) {
/*TODO*/  //                e.printStackTrace();
/*TODO*/  //            } catch (IOException e) {
/*TODO*/  //                e.printStackTrace();
/*TODO*/  //            }
/*TODO*/  //        } else {
/*TODO*/  //            // Load unpacked PSF in the same directory
/*TODO*/  //            File[] psffile = pbpfile.getParentFile().listFiles(new FileFilter() {
/*TODO*/  //                @Override
/*TODO*/  //                public boolean accept(File arg0) {
/*TODO*/  //                    return arg0.getName().equalsIgnoreCase("param.sfo");
/*TODO*/  //                }
/*TODO*/  //            });
/*TODO*/  //            if (psffile != null && psffile.length > 0) {
/*TODO*/  //                try {
/*TODO*/  //                	RandomAccessFile raf = new RandomAccessFile(psffile[0], "r");
/*TODO*/  //                    FileChannel roChannel = raf.getChannel();
/*TODO*/  //                    ByteBuffer readbuffer = roChannel.map(FileChannel.MapMode.READ_ONLY, 0,
          //                    (int)roChannel.size());
/*TODO*/  //                    module.psf = new PSF();
/*TODO*/  //                    module.psf.read(readbuffer);
/*TODO*/  //                    raf.close();
/*TODO*/  //                } catch (IOException e) {
/*TODO*/  //                    e.printStackTrace();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }

/** @return true on success */
bool Loader::LoadPBP(std::ifstream &f, SceModule *_module, u32& baseAddress, bool analyzeOnly,bool allocMem, bool fromSyscall){
       PBP pbp(f);
       if (pbp.isValid()) 
       {
/*TODO*/  //            module.fileFormat |= FORMAT_PBP;
/*TODO*/  //
/*TODO*/  //            // Dump PSF info
/*TODO*/  //            if (pbp.getOffsetParam() > 0) {
/*TODO*/  //                module.psf = pbp.readPSF(f);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // Dump unpacked PBP
/*TODO*/  //            if (Settings.getInstance().readBool("emu.pbpunpack")) {
/*TODO*/  //                PBP.unpackPBP(f);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // Save PBP info for debugger
/*TODO*/  //            ElfHeaderInfo.PbpInfo = pbp.toString();
/*TODO*/  //
            // Setup position for chaining loaders
            f.seekg(pbp.getOffsetPspData());
            return true;
       }
       // Not a valid PBP
       return false;
}
/*TODO*/  //
/*TODO*/  //    /** @return true on success */
/*TODO*/  //    private boolean LoadSPRX(ByteBuffer f, SceModule module, TPointer baseAddress, boolean analyzeOnly,
          //    boolean allocMem, boolean fromSyscall, boolean isSignChecked, byte[] key) throws IOException {
/*TODO*/  //        int magicPSP = Utilities.readWord(f);
/*TODO*/  //        int magicEDAT = Utilities.readWord(f);
/*TODO*/  //        if ((magicPSP == PSP_MAGIC) && (magicEDAT == EDAT_MAGIC)) {
/*TODO*/  //            log.warn("Encrypted file detected! (.PSPEDAT)");
/*TODO*/  //            // Skip the EDAT header and load as a regular ~PSP prx.
/*TODO*/  //            f.position(0x90);
/*TODO*/  //            LoadPSP(f.slice(), module, baseAddress, analyzeOnly, allocMem, fromSyscall, isSignChecked, key);
/*TODO*/  //            return true;
/*TODO*/  //        }
/*TODO*/  //        // Not a valid SPRX
/*TODO*/  //        return false;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /** @return true on success */
/*TODO*/  //    private boolean LoadSCE(ByteBuffer f, SceModule module, TPointer baseAddress, boolean analyzeOnly,
          //    boolean allocMem, boolean fromSyscall, boolean isSignChecked, byte[] key) throws IOException {
/*TODO*/  //        int magic = Utilities.readWord(f);
/*TODO*/  //        if (magic == SCE_MAGIC) {
/*TODO*/  //        	int size = Utilities.readWord(f);
/*TODO*/  //        	f.position(f.position() + size - 8);
/*TODO*/  //        	return LoadPSP(f, module, baseAddress, analyzeOnly, allocMem, fromSyscall, isSignChecked, key);
/*TODO*/  //        }
/*TODO*/  //        // Not a valid PSP
/*TODO*/  //        return false;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /** @return true on success */
/*TODO*/  //    private boolean LoadPSP(ByteBuffer f, SceModule module, TPointer baseAddress, boolean analyzeOnly,
          //    boolean allocMem, boolean fromSyscall, boolean isSignChecked, byte[] key) throws IOException {
/*TODO*/  //    	int position = f.position();
/*TODO*/  //        PSP psp = new PSP(f);
/*TODO*/  //        // Reset the position after reading the header
/*TODO*/  //        f.position(position);
/*TODO*/  //
/*TODO*/  //        if (!psp.isValid()) {
/*TODO*/  //            // Not a valid PSP
/*TODO*/  //        	return false;
/*TODO*/  //        }
/*TODO*/  //        module.fileFormat |= FORMAT_PSP;
/*TODO*/  //
/*TODO*/  //        if (key == null) {
/*TODO*/  //        	key = scePopsMan.readEbootKeys(module.pspfilename);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (module.psf != null) {
/*TODO*/  //        	String updaterVer = module.psf.getString("UPDATER_VER");
/*TODO*/  //        	if (updaterVer != null) {
/*TODO*/  //        		Emulator.getInstance().setFirmwareVersion(updaterVer);
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        long start = System.currentTimeMillis();
/*TODO*/  //    	ByteBuffer decryptedPrx = psp.decrypt(f, isSignChecked, key);
/*TODO*/  //    	long end = System.currentTimeMillis();
/*TODO*/  //
/*TODO*/  //    	if (decryptedPrx == null) {
/*TODO*/  //    		return false;
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	if (log.isDebugEnabled()) {
/*TODO*/  //    		log.debug(String.format("Called crypto engine for PRX (duration=%d ms)", end - start));
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	return LoadELF(decryptedPrx, module, baseAddress, analyzeOnly, allocMem, fromSyscall);
/*TODO*/  //    }
/*TODO*/  //
/** @return true on success */
bool Loader::LoadELF(std::ifstream& f, SceModule* _module, u32& baseAddress, u32 fileSize,bool analyzeOnly,
                     bool allocMem, bool fromSyscall) {
    u32 elfOffset = f.tellg();
    Elf32 elf(f);
    if (elf.getHeader().isValid()) {
/*TODO*/  //            module.fileFormat |= FORMAT_ELF;
/*TODO*/  //
            if (!elf.getHeader().isMIPSExecutable()) {
/*TODO*/  //                log.error("Loader NOT a MIPS executable");
                return false;
            }
            if (elf.isKernelMode()) {
                assert(0);
                /*TODO*/  //                module.mpidtext = SysMemUserForUser.KERNEL_PARTITION_ID;
/*TODO*/  //                module.mpiddata = SysMemUserForUser.KERNEL_PARTITION_ID;
/*TODO*/  //                if (!analyzeOnly && baseAddress.getAddress() == MemoryMap.START_USERSPACE + 0x4000) {
/*TODO*/  //                	baseAddress.setAddress(MemoryMap.START_RAM +
          //                Utilities.alignUp(ThreadManForUser.INTERNAL_THREAD_ADDRESS_SIZE,
          //                SysMemUserForUser.defaultSizeAlignment - 1));
/*TODO*/  //                }
            }
            if (elf.getHeader().isPRXDetected()) {
                assert(0);
                /*TODO*/  //                log.debug("Loader: Relocation required (PRX)");
/*TODO*/  //                module.fileFormat |= FORMAT_PRX;
            } else if (elf.getHeader().requiresRelocation()) {
                assert(0);
                /*TODO*/  //                // Seen in .elf's generated by pspsdk with BUILD_PRX=1 before conversion to .prx
/*TODO*/  //                log.info("Loader: Relocation required (ELF)");
            } else {
/*TODO*/  //                // After the user chooses a game to run and we load it, then
/*TODO*/  //                // we can't load another PBP at the same time. We can only load
/*TODO*/  //                // relocatable modules (PRX's) after the user loaded app.
/*TODO*/  //                if (baseAddress.getAddress() > 0x08900000) {
/*TODO*/  //                    log.warn("Loader: Probably trying to load PBP ELF while another PBP ELF is already
          //                    loaded");
/*TODO*/  //                }
/*TODO*/  //
                baseAddress = 0;
            }
/*TODO*/  //
/*TODO*/  //            module.baseAddress = baseAddress.getAddress();
/*TODO*/  //            if (elf.getHeader().getE_entry() == -1) {
/*TODO*/  //                module.entry_addr = -1;
/*TODO*/  //            } else {
/*TODO*/  //                module.entry_addr = baseAddress.getAddress() + elf.getHeader().getE_entry();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // Note: baseAddress is 0 unless we are loading a PRX
/*TODO*/  //            // Set loadAddressLow to the highest possible address, it will be updated
/*TODO*/  //            // by LoadELFProgram().
/*TODO*/  //            module.loadAddressLow = baseAddress.isNotNull() ? baseAddress.getAddress() :
          //            MemoryMap.END_USERSPACE;
/*TODO*/  //            module.loadAddressHigh = baseAddress.getAddress();
/*TODO*/  //
/*TODO*/  //            // Load into mem
            LoadELFProgram(f, _module, baseAddress, elf, elfOffset, fileSize, analyzeOnly);
            /*TODO*/  //            LoadELFSections(f, module, baseAddress, elf, elfOffset, analyzeOnly);
/*TODO*/  //
/*TODO*/  //            if (module.loadAddressLow > module.loadAddressHigh) {
/*TODO*/  //            	log.error(String.format("Incorrect ELF module address: loadAddressLow=0x%08X,
          //            loadAddressHigh=0x%08X", module.loadAddressLow, module.loadAddressHigh));
/*TODO*/  //            	module.loadAddressHigh = module.loadAddressLow;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (!analyzeOnly) {
/*TODO*/  //	            // Relocate PRX
/*TODO*/  //	            if (elf.getHeader().requiresRelocation()) {
/*TODO*/  //	                relocateFromHeaders(f, module, baseAddress, elf, elfOffset);
/*TODO*/  //	            }
/*TODO*/  //
/*TODO*/  //	            // The following can only be done after relocation
/*TODO*/  //	            // Load .rodata.sceModuleInfo
/*TODO*/  //	            LoadELFModuleInfo(f, module, baseAddress, elf, elfOffset, analyzeOnly);
/*TODO*/  //	            if (allocMem) {
/*TODO*/  //		            // After LoadELFModuleInfo so the we can name the memory allocation after the module
          //name
/*TODO*/  //		            LoadELFReserveMemory(module);
/*TODO*/  //	            }
/*TODO*/  //	            // Save imports
/*TODO*/  //	            LoadELFImports(module, baseAddress);
/*TODO*/  //	            // Save exports
/*TODO*/  //	            LoadELFExports(module, baseAddress);
/*TODO*/  //	            // Try to fixup imports for ALL modules
/*TODO*/  //	            Managers.modules.addModule(module);
/*TODO*/  //	            ProcessUnresolvedImports(module, baseAddress, fromSyscall);
/*TODO*/  //
/*TODO*/  //	            // Debug
/*TODO*/  //	            LoadELFDebuggerInfo(f, module, baseAddress, elf, elfOffset, fromSyscall);
/*TODO*/  //
/*TODO*/  //	            // If no text_addr is available up to now, use the lowest program header address
/*TODO*/  //	            if (module.text_addr == 0) {
/*TODO*/  //	                for (Elf32ProgramHeader phdr : elf.getProgramHeaderList()) {
/*TODO*/  //	                	if (module.text_addr == 0 || phdr.getP_vaddr() < module.text_addr) {
/*TODO*/  //	                		module.text_addr = phdr.getP_vaddr();
/*TODO*/  //	                		// Align the text_addr if an alignment has been specified
/*TODO*/  //	                		if (phdr.getP_align() > 0) {
/*TODO*/  //	                			module.text_addr = Utilities.alignDown(module.text_addr, phdr.getP_align() -
          //1);
/*TODO*/  //	                		}
/*TODO*/  //	                	}
/*TODO*/  //	                }
/*TODO*/  //	            }
/*TODO*/  //
/*TODO*/  //	            // Flush module struct to psp mem
/*TODO*/  //	            if (baseAddress.getMemory() == Emulator.getMemory()) {
/*TODO*/  //	            	module.write(baseAddress.getMemory(), module.address);
/*TODO*/  //	            }
/*TODO*/  //            } else {
/*TODO*/  //	            LoadELFModuleInfo(f, module, baseAddress, elf, elfOffset, analyzeOnly);
/*TODO*/  //	            if (elf.getHeader().requiresRelocation()) {
/*TODO*/  //	            	LoadSDKVersion(f, module, elf, elfOffset);
/*TODO*/  //	            }
/*TODO*/  //            }
/*TODO*/  //            return true;
        }
		// Not a valid ELF
/*TODO*/  //		log.debug("Loader: Not a ELF");
		return false;
}
/*TODO*/  //
/*TODO*/  //    /** Dummy loader for unrecognized file formats, put at the end of a loader chain.
/*TODO*/  //     * @return true on success */
/*TODO*/  //    private boolean LoadUNK(ByteBuffer f, SceModule module, TPointer baseAddress, boolean analyzeOnly,
          //    boolean allocMem, boolean fromSyscall) throws IOException {
/*TODO*/  //
/*TODO*/  //        byte m0 = f.get();
/*TODO*/  //        byte m1 = f.get();
/*TODO*/  //        byte m2 = f.get();
/*TODO*/  //        byte m3 = f.get();
/*TODO*/  //
/*TODO*/  //        // Catch common user errors
/*TODO*/  //        if (m0 == 0x43 && m1 == 0x49 && m2 == 0x53 && m3 == 0x4F) { // CSO
/*TODO*/  //            log.info("This is not an executable file!");
/*TODO*/  //            log.info("Try using the Load UMD menu item");
/*TODO*/  //        } else if ((m0 == 0 && m1 == 0x50 && m2 == 0x53 && m3 == 0x46)) { // PSF
/*TODO*/  //            log.info("This is not an executable file!");
/*TODO*/  //        } else {
/*TODO*/  //            boolean handled = false;
/*TODO*/  //
/*TODO*/  //            // check for ISO
/*TODO*/  //            if (f.limit() >= 16 * 2048 + 6) {
/*TODO*/  //                f.position(16 * 2048);
/*TODO*/  //                byte[] id = new byte[6];
/*TODO*/  //                f.get(id);
/*TODO*/  //                if((((char)id[1])=='C')&&
/*TODO*/  //                   (((char)id[2])=='D')&&
/*TODO*/  //                   (((char)id[3])=='0')&&
/*TODO*/  //                   (((char)id[4])=='0')&&
/*TODO*/  //                   (((char)id[5])=='1'))
/*TODO*/  //                {
/*TODO*/  //                    log.info("This is not an executable file!");
/*TODO*/  //                    log.info("Try using the Load UMD menu item");
/*TODO*/  //                    handled = true;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (!handled) {
/*TODO*/  //                log.info("Unrecognized file format");
/*TODO*/  //                log.info(String.format("File magic %02X %02X %02X %02X", m0, m1, m2, m3));
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                    byte[] buffer = new byte[0x150];
/*TODO*/  //                    buffer[0] = m0;
/*TODO*/  //                    buffer[1] = m1;
/*TODO*/  //                    buffer[2] = m2;
/*TODO*/  //                    buffer[3] = m3;
/*TODO*/  //                    f.get(buffer, 4, buffer.length - 4);
/*TODO*/  //                    log.debug(String.format("File header: %s", Utilities.getMemoryDump(buffer, 0,
          //                    buffer.length)));
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return false;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // ELF Loader
/*TODO*/  //
/** Load some programs into memory */
void Loader::LoadELFProgram(std::ifstream& f, SceModule* _module, u32& baseAddress, Elf32& elf, u32 elfOffset,u32 fileSize, bool analyzeOnly) {
    std::vector<Elf32ProgramHeader>& programHeaderList = elf.getProgramHeaderList();
/*TODO*/  //        module.text_size = 0;
/*TODO*/  //        module.data_size = 0;
/*TODO*/  //        module.bss_size = 0;
/*TODO*/  //
        int i = 0;
    for (auto phdr : programHeaderList){
/*TODO*/  //        	if (log.isTraceEnabled()) {
/*TODO*/  //        		log.trace(String.format("ELF Program Header: %s", phdr.toString()));
/*TODO*/  //        	}
            if (phdr.getP_type() == 0x00000001) {
                    u32 fileOffset = phdr.getP_offset();
                u32 memOffset = baseAddress + phdr.getP_vaddr();
                /*TODO*/  //                if (!Memory.isAddressGood(memOffset)) {
/*TODO*/  //                    memOffset = (int)phdr.getP_vaddr();
/*TODO*/  //                    if (!Memory.isAddressGood(memOffset)) {
/*TODO*/  //                    	log.warn(String.format("Program header has invalid memory offset 0x%08X!",
          //                    memOffset));
/*TODO*/  //                    }
/*TODO*/  //                }
                u32 fileLen = phdr.getP_filesz();
                u32 memLen = phdr.getP_memsz();
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                	log.debug(String.format("PH#%d: loading program 0x%08X-0x%08X", i, memOffset, memOffset
          //                + memLen));
/*TODO*/  //                	log.debug(String.format("PH#%d:\n%s", i, phdr));
/*TODO*/  //                }
/*TODO*/  //
                f.seekg(elfOffset + fileOffset);
                if (((u32)f.tellg() + fileLen) > fileSize) {
                    u32 newLen = fileSize - (u32)f.tellg();
                    /*TODO*/  //                    log.warn(String.format("PH#%d: program overflow clamping len %08X to
                              //                    %08X", i, fileLen,
                              //                    newLen));
                    fileLen = newLen;
                }
                if (!analyzeOnly) {
                	if (memLen > fileLen) {
                        // Clear the memory part not loaded from the file
                            memset(Memory::getPointer(memOffset + fileLen), 0, memLen - fileLen);         		
                	}
                        /*TODO*/  //                        if (((memOffset | fileLen | (u32)f.tellg()) & 3) == 0) {
                            /*TODO*/  //                		ByteOrder order = f.order();
/*TODO*/  //                		f.order(ByteOrder.LITTLE_ENDIAN);
/*TODO*/  //                		IntBuffer intBuffer = f.asIntBuffer();
/*TODO*/  //                		TPointer destAddr = new TPointer(baseAddress.getMemory(), memOffset);
/*TODO*/  //                		// Optimize the most common case
/*TODO*/  //                		if (RuntimeContext.hasMemoryInt(destAddr)) {
/*TODO*/  //                			intBuffer.get(RuntimeContext.getMemoryInt(), (memOffset & addressMask) >> 2,
          //                fileLen >> 2);
/*TODO*/  //                		} else {
/*TODO*/  //                			int[] buffer = new int[fileLen >> 2];
/*TODO*/  //                			intBuffer.get(buffer);
/*TODO*/  //                			writeInt32(destAddr, fileLen, buffer, 0);
/*TODO*/  //                		}
/*TODO*/  //                		f.order(order);
/*TODO*/  //                		f.position(f.position() + fileLen);
/*TODO*/  //                 	} else {
                            f.read((char*)Memory::getPointer(memOffset), fileLen);
/*TODO*/  //                	}
                }
/*TODO*/  //
/*TODO*/  //                // Update memory area consumed by the module
/*TODO*/  //                if (memOffset < module.loadAddressLow) {
/*TODO*/  //                    module.loadAddressLow = memOffset;
/*TODO*/  //                    if (log.isDebugEnabled()) {
/*TODO*/  //                    	log.debug(String.format("PH#%d: new loadAddressLow %08X", i,
          //                    module.loadAddressLow));
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //                if (memOffset + memLen > module.loadAddressHigh) {
/*TODO*/  //                    module.loadAddressHigh = memOffset + memLen;
/*TODO*/  //                    if (log.isTraceEnabled()) {
/*TODO*/  //                    	log.trace(String.format("PH#%d: new loadAddressHigh %08X", i,
          //                    module.loadAddressHigh));
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                module.segmentaddr[module.nsegment] = memOffset;
/*TODO*/  //                module.segmentsize[module.nsegment] = memLen;
/*TODO*/  //                module.nsegment++;
/*TODO*/  //
/*TODO*/  //                /*
/*TODO*/  //                 * If the segment is executable, it contains the .text section.
/*TODO*/  //                 * Otherwise, it contains the .data section.
/*TODO*/  //                 */
/*TODO*/  //                if ((phdr.getP_flags() & PF_X) != 0) {
/*TODO*/  //                	module.text_size += fileLen;
/*TODO*/  //                } else {
/*TODO*/  //                	module.data_size += fileLen;
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                /* Add the "extra" segment bytes to the .bss section. */
/*TODO*/  //                if (fileLen < memLen) {
/*TODO*/  //                	module.bss_size += memLen - fileLen;
/*TODO*/  //                }
            }
            i++;
        }
/*TODO*/  //
/*TODO*/  //        if (log.isDebugEnabled()) {
/*TODO*/  //        	log.debug(String.format("PH alloc consumption %08X (mem %08X)", (module.loadAddressHigh -
          //        module.loadAddressLow), module.bss_size));
/*TODO*/  //        }
}
/*TODO*/  //
/*TODO*/  //    /** Load some sections into memory */
/*TODO*/  //    private void LoadELFSections(ByteBuffer f, SceModule module, TPointer baseAddress, Elf32 elf, int
          //    elfOffset, boolean analyzeOnly) throws IOException {
/*TODO*/  //        List<Elf32SectionHeader> sectionHeaderList = elf.getSectionHeaderList();
/*TODO*/  //        Memory mem = baseAddress.getMemory();
/*TODO*/  //
/*TODO*/  //        module.text_addr = baseAddress.getAddress();
/*TODO*/  //
/*TODO*/  //        for (Elf32SectionHeader shdr : sectionHeaderList) {
/*TODO*/  //        	if (log.isTraceEnabled()) {
/*TODO*/  //        		log.trace(String.format("ELF Section Header: %s", shdr.toString()));
/*TODO*/  //        	}
/*TODO*/  //
/*TODO*/  //            int memOffset = shdr.getSh_addr(baseAddress);
/*TODO*/  //            int len = shdr.getSh_size();
/*TODO*/  //            int flags = shdr.getSh_flags();
/*TODO*/  //
/*TODO*/  //            if (flags != SHF_NONE && Memory.isAddressGood(memOffset)) {
/*TODO*/  //        		boolean read = (flags & SHF_ALLOCATE) != 0;
/*TODO*/  //        		boolean write = (flags & SHF_WRITE) != 0;
/*TODO*/  //        		boolean execute = (flags & SHF_EXECUTE) != 0;
/*TODO*/  //        		MemorySection memorySection = new MemorySection(memOffset, len, read, write, execute);
/*TODO*/  //        		MemorySections.getInstance().addMemorySection(memorySection);
/*TODO*/  //        	}
/*TODO*/  //
/*TODO*/  //        	if ((flags & SHF_ALLOCATE) != 0) {
/*TODO*/  //                switch (shdr.getSh_type()) {
/*TODO*/  //                    case Elf32SectionHeader.SHT_PROGBITS: { // 1
/*TODO*/  //                        // Load this section into memory
/*TODO*/  //                        // now loaded using program header type 1
/*TODO*/  //                        if (len == 0) {
/*TODO*/  //                        	if (log.isDebugEnabled()) {
/*TODO*/  //                        		log.debug(String.format("%s: ignoring zero-length type 1 section %08X",
          //                        shdr.getSh_namez(), memOffset));
/*TODO*/  //                        	}
/*TODO*/  //                        } else if (!Memory.isAddressGood(memOffset)) {
/*TODO*/  //                            log.error(String.format("Section header (type 1) has invalid memory offset
          //                            0x%08X!", memOffset));
/*TODO*/  //                        } else {
/*TODO*/  //	                        // Update memory area consumed by the module
/*TODO*/  //	                        if (memOffset < module.loadAddressLow) {
/*TODO*/  //	                            log.warn(String.format("%s: section allocates more than program %08X -
          //%08X", shdr.getSh_namez(), memOffset, (memOffset + len)));
/*TODO*/  //	                            module.loadAddressLow = memOffset;
/*TODO*/  //	                        }
/*TODO*/  //	                        if (memOffset + len > module.loadAddressHigh) {
/*TODO*/  //	                            log.warn(String.format("%s: section allocates more than program %08X -
          //%08X", shdr.getSh_namez(), memOffset, (memOffset + len)));
/*TODO*/  //	                            module.loadAddressHigh = memOffset + len;
/*TODO*/  //	                        }
/*TODO*/  //
/*TODO*/  //	                        if ((flags & SHF_WRITE) != 0) {
/*TODO*/  //	                        	if (log.isTraceEnabled()) {
/*TODO*/  //	                        		log.trace(String.format("Section Header as data, len=0x%08X,
          //data_size=0x%08X", len, module.data_size));
/*TODO*/  //	                        	}
/*TODO*/  //	                        } else {
/*TODO*/  //	                        	if (log.isTraceEnabled()) {
/*TODO*/  //	                        		log.trace(String.format("Section Header as text, len=0x%08X,
          //text_size=0x%08X", len, module.text_size));
/*TODO*/  //	                        	}
/*TODO*/  //	                        }
/*TODO*/  //                        }
/*TODO*/  //                        break;
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    case Elf32SectionHeader.SHT_NOBITS: { // 8
/*TODO*/  //                        // Zero out this portion of memory
/*TODO*/  //                        if (len == 0) {
/*TODO*/  //                        	if (log.isDebugEnabled()) {
/*TODO*/  //                        		log.debug(String.format("%s: ignoring zero-length type 8 section %08X",
          //                        shdr.getSh_namez(), memOffset));
/*TODO*/  //                        	}
/*TODO*/  //                        } else if (!Memory.isAddressGood(memOffset)) {
/*TODO*/  //                            log.error(String.format("Section header (type 8) has invalid memory offset
          //                            0x%08X!", memOffset));
/*TODO*/  //                        } else {
/*TODO*/  //                        	if (log.isDebugEnabled()) {
/*TODO*/  //                        		log.debug(String.format("%s: clearing section %08X - %08X (len %08X)",
          //                        shdr.getSh_namez(), memOffset, (memOffset + len), len));
/*TODO*/  //                        	}
/*TODO*/  //
/*TODO*/  //                        	if (!analyzeOnly) {
/*TODO*/  //                        		mem.memset(memOffset, (byte) 0x0, len);
/*TODO*/  //                        	}
/*TODO*/  //
/*TODO*/  //                            // Update memory area consumed by the module
/*TODO*/  //                            if (memOffset < module.loadAddressLow) {
/*TODO*/  //                                module.loadAddressLow = memOffset;
/*TODO*/  //                                if (log.isDebugEnabled()) {
/*TODO*/  //                                	log.debug(String.format("%s: new loadAddressLow %08X (+%08X)",
          //                                shdr.getSh_namez(), module.loadAddressLow, len));
/*TODO*/  //                                }
/*TODO*/  //                            }
/*TODO*/  //                            if (memOffset + len > module.loadAddressHigh) {
/*TODO*/  //                                module.loadAddressHigh = memOffset + len;
/*TODO*/  //                                if (log.isDebugEnabled()) {
/*TODO*/  //                                	log.debug(String.format("%s: new loadAddressHigh %08X (+%08X)",
          //                                shdr.getSh_namez(), module.loadAddressHigh, len));
/*TODO*/  //                                }
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //                        break;
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (log.isTraceEnabled()) {
/*TODO*/  //    		log.trace(String.format("Storing module info: text addr 0x%08X, text_size 0x%08X,
          //    data_size 0x%08X, bss_size 0x%08X", module.text_addr, module.text_size, module.data_size,
          //    module.bss_size));
/*TODO*/  //    	}
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void LoadELFReserveMemory(SceModule module) {
/*TODO*/  //        // Mark the area of memory the module loaded into as used
/*TODO*/  //    	if (log.isDebugEnabled()) {
/*TODO*/  //    		log.debug(String.format("Reserving 0x%X bytes at 0x%08X for module '%s'",
          //    module.loadAddressHigh - module.loadAddressLow, module.loadAddressLow, module.pspfilename));
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //        int address = module.loadAddressLow & ~(SysMemUserForUser.defaultSizeAlignment - 1); // Round down
          //        to match sysmem allocations
/*TODO*/  //        int size = module.loadAddressHigh - address;
/*TODO*/  //
/*TODO*/  //        int partition = module.mpidtext > 0 ? module.mpidtext : SysMemUserForUser.USER_PARTITION_ID;
/*TODO*/  //        SysMemInfo info = Modules.SysMemUserForUserModule.malloc(partition, module.modname,
          //        SysMemUserForUser.PSP_SMEM_Addr, size, address);
/*TODO*/  //        if (info == null || info.addr != (address & Memory.addressMask)) {
/*TODO*/  //            log.warn(String.format("Failed to properly reserve memory consumed by module %s at address
          //            0x%08X, size 0x%X: allocated %s", module.modname, address, size, info));
/*TODO*/  //        }
/*TODO*/  //        module.addAllocatedMemory(info);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /** Loads from memory */
/*TODO*/  //    private void LoadELFModuleInfo(ByteBuffer f, SceModule module, TPointer baseAddress, Elf32 elf, int
          //    elfOffset, boolean analyzeOnly) throws IOException {
/*TODO*/  //
/*TODO*/  //        Elf32ProgramHeader phdr = elf.getProgramHeader(0);
/*TODO*/  //        Elf32SectionHeader shdr = elf.getSectionHeader(".rodata.sceModuleInfo");
/*TODO*/  //
/*TODO*/  //        int moduleInfoAddr = 0;
/*TODO*/  //        int moduleInfoFileOffset = -1;
/*TODO*/  //        if (!elf.getHeader().isPRXDetected() && shdr == null) {
/*TODO*/  //        	if (analyzeOnly) {
/*TODO*/  //        		moduleInfoFileOffset = phdr.getP_paddr() & Memory.addressMask;
/*TODO*/  //        	} else {
/*TODO*/  //	            log.warn("ELF is not PRX, but has no section headers!");
/*TODO*/  //	            moduleInfoAddr = phdr.getP_vaddr() + (phdr.getP_paddr() & Memory.addressMask) -
          //phdr.getP_offset();
/*TODO*/  //	            log.warn("Manually locating ModuleInfo at address: 0x" +
          //Integer.toHexString(moduleInfoAddr));
/*TODO*/  //        	}
/*TODO*/  //        } else if (elf.getHeader().isPRXDetected()) {
/*TODO*/  //        	if (analyzeOnly) {
/*TODO*/  //        		moduleInfoFileOffset = phdr.getP_paddr() & Memory.addressMask;
/*TODO*/  //        	} else {
/*TODO*/  //        		moduleInfoAddr = baseAddress.getAddress() + (phdr.getP_paddr() & Memory.addressMask) -
          //        phdr.getP_offset();
/*TODO*/  //        	}
/*TODO*/  //        } else if (shdr != null) {
/*TODO*/  //        	moduleInfoAddr = shdr.getSh_addr(baseAddress);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (moduleInfoAddr != 0) {
/*TODO*/  //            PSPModuleInfo moduleInfo = new PSPModuleInfo();
/*TODO*/  //            moduleInfo.read(baseAddress.getMemory(), moduleInfoAddr);
/*TODO*/  //            module.copy(moduleInfo);
/*TODO*/  //        } else if (moduleInfoFileOffset >= 0) {
/*TODO*/  //            PSPModuleInfo moduleInfo = new PSPModuleInfo();
/*TODO*/  //            f.position(moduleInfoFileOffset);
/*TODO*/  //            moduleInfo.read(f);
/*TODO*/  //            module.copy(moduleInfo);
/*TODO*/  //        } else {
/*TODO*/  //            log.error("ModuleInfo not found!");
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (!analyzeOnly) {
/*TODO*/  //	        if (log.isInfoEnabled()) {
/*TODO*/  //	        	log.info(String.format("Found ModuleInfo at 0x%08X, name:'%s', version: %04X, attr: 0x%08X,
          //gp: 0x%08X", moduleInfoAddr, module.modname, module.version, module.attribute, module.gp_value));
/*TODO*/  //	        }
/*TODO*/  //
/*TODO*/  //	        if ((module.attribute & SceModule.PSP_MODULE_KERNEL) != 0) {
/*TODO*/  //	            log.debug("Kernel mode module detected");
/*TODO*/  //	        }
/*TODO*/  //	        if ((module.attribute & SceModule.PSP_MODULE_VSH) != 0) {
/*TODO*/  //	            log.debug("VSH mode module detected");
/*TODO*/  //	        }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * @param f        The position of this buffer must be at the start of a
/*TODO*/  //     *                 list of Elf32Rel structs.
/*TODO*/  //     * @param RelCount The number of Elf32Rel structs to read and process.
/*TODO*/  //     * @param pspRelocationFormat true if the relocation are in the PSP specific format,
/*TODO*/  //     *                            false if the relocation is in standard ELF format.
/*TODO*/  //     */
/*TODO*/  //    private void relocateFromBuffer(ByteBuffer f, SceModule module, TPointer baseAddress, Elf32 elf, int
          //    RelCount, boolean pspRelocationFormat) throws IOException {
/*TODO*/  //
/*TODO*/  //    	Elf32Relocate rel = new Elf32Relocate();
/*TODO*/  //        int AHL = 0; // (AHI << 16) | (ALO & 0xFFFF)
/*TODO*/  //        List<Integer> deferredHi16 = new LinkedList<Integer>(); // We'll use this to relocate R_MIPS_HI16
          //        when we get a R_MIPS_LO16
/*TODO*/  //
/*TODO*/  //        Memory mem = baseAddress.getMemory();
/*TODO*/  //        for (int i = 0; i < RelCount; i++) {
/*TODO*/  //            rel.read(f);
/*TODO*/  //
/*TODO*/  //            int phOffset;
/*TODO*/  //            int phBaseOffset;
/*TODO*/  //
/*TODO*/  //            int R_OFFSET = rel.getR_offset();
/*TODO*/  //            int R_TYPE = rel.getR_info() & 0xFF;
/*TODO*/  //            if (pspRelocationFormat) {
/*TODO*/  //	            int OFS_BASE  = (rel.getR_info() >>  8) & 0xFF;
/*TODO*/  //	            int ADDR_BASE = (rel.getR_info() >> 16) & 0xFF;
/*TODO*/  //	            if (log.isTraceEnabled()) {
/*TODO*/  //	            	log.trace(String.format("Relocation #%d type=%d, Offset PH#%d, Base Offset PH#%d, Offset
          //0x%08X", i, R_TYPE, OFS_BASE, ADDR_BASE, R_OFFSET));
/*TODO*/  //	            }
/*TODO*/  //
/*TODO*/  //	            phOffset = elf.getProgramHeader(OFS_BASE).getP_vaddr();
/*TODO*/  //	            phBaseOffset = elf.getProgramHeader(ADDR_BASE).getP_vaddr();
/*TODO*/  //            } else {
/*TODO*/  //            	phOffset = 0;
/*TODO*/  //            	phBaseOffset = 0;
/*TODO*/  //	            if (log.isTraceEnabled()) {
/*TODO*/  //	            	log.trace(String.format("Relocation #%d type=%d, Symbol 0x%06X, Offset 0x%08X", i,
          //R_TYPE, rel.getR_info() >> 8, R_OFFSET));
/*TODO*/  //	            }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // Address of data to relocate
/*TODO*/  //            int data_addr = baseAddress.getAddress() + R_OFFSET + phOffset;
/*TODO*/  //            // Value of data to relocate
/*TODO*/  //            int data = readUnaligned32(mem, data_addr);
/*TODO*/  //            long result = 0; // Used to hold the result of relocation, OR this back into data
/*TODO*/  //
/*TODO*/  //            int word32 = data & 0xFFFFFFFF; // <=> data;
/*TODO*/  //            int targ26 = data & 0x03FFFFFF;
/*TODO*/  //            int hi16 = data & 0x0000FFFF;
/*TODO*/  //            int lo16 = data & 0x0000FFFF;
/*TODO*/  //
/*TODO*/  //            int A = 0; // addend
/*TODO*/  //            int S = baseAddress.getAddress() + phBaseOffset;
/*TODO*/  //
/*TODO*/  //            switch (R_TYPE) {
/*TODO*/  //                case 0: //R_MIPS_NONE
/*TODO*/  //                    // Tested on PSP: R_MIPS_NONE is ignored
/*TODO*/  //                    if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_NONE addr=0x%08X", data_addr));
/*TODO*/  //                	}
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case 1: // R_MIPS_16
/*TODO*/  //                	data = (data & 0xFFFF0000) | ((data + S) & 0x0000FFFF);
/*TODO*/  //                	if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_16 addr=0x%08X before=0x%08X after=0x%08X",
          //                data_addr, word32, data));
/*TODO*/  //                    }
/*TODO*/  //                	break;
/*TODO*/  //
/*TODO*/  //                case 2: //R_MIPS_32
/*TODO*/  //                    data += S;
/*TODO*/  //                	if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_32 addr=0x%08X before=0x%08X after=0x%08X",
          //                data_addr, word32, data));
/*TODO*/  //                    }
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case 4: //R_MIPS_26
/*TODO*/  //                    A = targ26;
/*TODO*/  //                    result = ((A << 2) + S) >> 2;
/*TODO*/  //                    data &= ~0x03FFFFFF;
/*TODO*/  //                    data |= (int) (result & 0x03FFFFFF); // truncate
/*TODO*/  //                	if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_26 addr=0x%08X before=0x%08X after=0x%08X",
          //                data_addr, word32, data));
/*TODO*/  //                    }
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case 5: //R_MIPS_HI16
/*TODO*/  //                    A = hi16;
/*TODO*/  //                    AHL = A << 16;
/*TODO*/  //                    deferredHi16.add(data_addr);
/*TODO*/  //                	if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_HI16 addr=0x%08X", data_addr));
/*TODO*/  //                	}
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case 6: //R_MIPS_LO16
/*TODO*/  //                    A = lo16;
/*TODO*/  //                    AHL &= ~0x0000FFFF; // delete lower bits, since many R_MIPS_LO16 can follow one
          //                    R_MIPS_HI16
/*TODO*/  //                    AHL |= A & 0x0000FFFF;
/*TODO*/  //                    result = AHL + S;
/*TODO*/  //                    data &= ~0x0000FFFF;
/*TODO*/  //                    data |= result & 0x0000FFFF; // truncate
/*TODO*/  //                    // Process deferred R_MIPS_HI16
/*TODO*/  //                    for (Iterator<Integer> it = deferredHi16.iterator(); it.hasNext();) {
/*TODO*/  //                        int data_addr2 = it.next();
/*TODO*/  //                        int data2 = readUnaligned32(mem, data_addr2);
/*TODO*/  //                        result = ((data2 & 0x0000FFFF) << 16) + A + S;
/*TODO*/  //                        // The low order 16 bits are always treated as a signed
/*TODO*/  //                        // value. Therefore, a negative value in the low order bits
/*TODO*/  //                        // requires an adjustment in the high order bits. We need
/*TODO*/  //                        // to make this adjustment in two ways: once for the bits we
/*TODO*/  //                        // took from the data, and once for the bits we are putting
/*TODO*/  //                        // back in to the data.
/*TODO*/  //                        if ((A & 0x8000) != 0) {
/*TODO*/  //                            result -= 0x10000;
/*TODO*/  //                        }
/*TODO*/  //                        if ((result & 0x8000) != 0) {
/*TODO*/  //                             result += 0x10000;
/*TODO*/  //                        }
/*TODO*/  //                        data2 &= ~0x0000FFFF;
/*TODO*/  //                        data2 |= (int) ((result >> 16) & 0x0000FFFF);
/*TODO*/  //                    	if (log.isTraceEnabled()) {
/*TODO*/  //                    		log.trace(String.format("R_MIPS_HILO16 addr=0x%08X before=0x%08X
          //                    after=0x%08X", data_addr2, readUnaligned32(mem, data_addr2), data2));
/*TODO*/  //                        }
/*TODO*/  //                    	writeUnaligned32(mem, data_addr2, data2);
/*TODO*/  //                        it.remove();
/*TODO*/  //                    }
/*TODO*/  //                	if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_LO16 addr=0x%08X before=0x%08X after=0x%08X",
          //                data_addr, word32, data));
/*TODO*/  //                	}
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case 7: // R_MIPS_GPREL16
/*TODO*/  //                	// This relocation type is ignored by the PSP
/*TODO*/  //                    if (log.isTraceEnabled()) {
/*TODO*/  //                		log.trace(String.format("R_MIPS_GPREL16 addr=0x%08X before=0x%08X after=0x%08X",
          //                data_addr, word32, data));
/*TODO*/  //                    }
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                default:
/*TODO*/  //                	log.warn(String.format("Unhandled relocation type %d at 0x%08X", R_TYPE, data_addr));
/*TODO*/  //                    break;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            writeUnaligned32(mem, data_addr, data);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private static String getRTypeName(int R_TYPE) {
/*TODO*/  //    	String[] names = {
/*TODO*/  //    			"R_MIPS_NONE",
/*TODO*/  //    			"R_MIPS_16",
/*TODO*/  //    			"R_MIPS_32",
/*TODO*/  //    			"R_MIPS_26",
/*TODO*/  //    			"R_MIPS_HI16",
/*TODO*/  //    			"R_MIPS_LO16",
/*TODO*/  //    			"R_MIPS_J26",
/*TODO*/  //    			"R_MIPS_JAL26"
/*TODO*/  //    	};
/*TODO*/  //    	if (R_TYPE < 0 || R_TYPE >= names.length) {
/*TODO*/  //    		return String.format("%d", R_TYPE);
/*TODO*/  //    	}
/*TODO*/  //    	return names[R_TYPE];
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void relocateFromBufferA1(ByteBuffer f, SceModule module, Elf32 elf, TPointer baseAddress, int
          //    programHeaderNumber, int size) throws IOException {
/*TODO*/  //        Memory mem = baseAddress.getMemory();
/*TODO*/  //
/*TODO*/  //        // Relocation variables.
/*TODO*/  //        int R_OFFSET = 0;
/*TODO*/  //        int R_BASE = 0;
/*TODO*/  //        int OFS_BASE = 0;
/*TODO*/  //
/*TODO*/  //        // Data variables.
/*TODO*/  //        int data_addr;
/*TODO*/  //        int data;
/*TODO*/  //        int lo16 = 0;
/*TODO*/  //        int hi16;
/*TODO*/  //        int phBaseOffset;
/*TODO*/  //        int r = 0;
/*TODO*/  //
/*TODO*/  //        int end = f.position() + size;
/*TODO*/  //
/*TODO*/  //        // Skip 2 unused bytes
/*TODO*/  //        readUByte(f);
/*TODO*/  //        readUByte(f);
/*TODO*/  //
/*TODO*/  //        // Locate and read the flag, type and segment bits.
/*TODO*/  //        int fbits = readUByte(f);
/*TODO*/  //        int flagShift = 0;
/*TODO*/  //        int flagMask = (1 << fbits) - 1;
/*TODO*/  //
/*TODO*/  //        int sbits = programHeaderNumber < 3 ? 1 : 2;
/*TODO*/  //        int segmentShift = fbits;
/*TODO*/  //        int segmentMask = (1 << sbits) - 1;
/*TODO*/  //
/*TODO*/  //        int tbits = readUByte(f);
/*TODO*/  //        int typeShift = fbits + sbits;
/*TODO*/  //        int typeMask = (1 << tbits) - 1;
/*TODO*/  //
/*TODO*/  //        // Locate the flag table.
/*TODO*/  //        int flags[] = new int[readUByte(f)];
/*TODO*/  //        flags[0] = flags.length;
/*TODO*/  //        for (int j = 1; j < flags.length; j++) {
/*TODO*/  //        	flags[j] = readUByte(f);
/*TODO*/  //        	if (log.isTraceEnabled()) {
/*TODO*/  //        		log.trace(String.format("R_FLAG(%d bits) 0x%X -> 0x%X", fbits, j, flags[j]));
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Locate the type table.
/*TODO*/  //        int types[] = new int[readUByte(f)];
/*TODO*/  //        types[0] = types.length;
/*TODO*/  //        for (int j = 1; j < types.length; j++) {
/*TODO*/  //        	types[j] = readUByte(f);
/*TODO*/  //        	if (log.isTraceEnabled()) {
/*TODO*/  //        		log.trace(String.format("R_TYPE(%d bits) 0x%X -> 0x%X", tbits, j, types[j]));
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // loadcore.prx and sysmem.prx are being loaded and relocated by
/*TODO*/  //        // the PSP reboot code. It is using a different type mapping.
/*TODO*/  //        // See https://github.com/uofw/uofw/blob/master/src/reboot/elf.c#L327
/*TODO*/  //    	if ("flash0:/kd/loadcore.prx".equals(module.pspfilename) ||
          //    "flash0:/kd/sysmem.prx".equals(module.pspfilename)) {
/*TODO*/  //    		final int[] rebootTypeRemapping = new int[] { 0, 3, 6, 7, 1, 2, 4, 5 };
/*TODO*/  //    		for (int i = 1; i < types.length; i++) {
/*TODO*/  //    			types[i] = rebootTypeRemapping[types[i]];
/*TODO*/  //    		}
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //        int pos = f.position();
/*TODO*/  //        int R_TYPE_OLD = types.length;
/*TODO*/  //        while (pos < end) {
/*TODO*/  //            // Read the CMD byte.
/*TODO*/  //            int R_CMD = readUHalf(f);
/*TODO*/  //            pos += 2;
/*TODO*/  //
/*TODO*/  //            // Process the relocation flag.
/*TODO*/  //            int flagIndex = (R_CMD >> flagShift) & flagMask;
/*TODO*/  //            int R_FLAG = flags[flagIndex];
/*TODO*/  //
/*TODO*/  //            // Set the segment offset.
/*TODO*/  //            int S = (R_CMD >> segmentShift) & segmentMask;
/*TODO*/  //
/*TODO*/  //            // Process the relocation type.
/*TODO*/  //            int typeIndex = (R_CMD >> typeShift) & typeMask;
/*TODO*/  //            int R_TYPE = types[typeIndex];
/*TODO*/  //
/*TODO*/  //            // Operate on segment offset based on the relocation flag.
/*TODO*/  //            if ((R_FLAG & 0x01) == 0) {
/*TODO*/  //                if (log.isTraceEnabled()) {
/*TODO*/  //                	log.trace(String.format("Relocation 0x%04X, R_FLAG=0x%02X(%d), S=%d, rest=0x%X", R_CMD,
          //                R_FLAG, flagIndex, S, R_CMD >> (fbits + sbits)));
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                OFS_BASE = S;
/*TODO*/  //                if ((R_FLAG & 0x06) == 0) {
/*TODO*/  //                    R_BASE = (R_CMD >> (fbits + sbits));
/*TODO*/  //                } else if ((R_FLAG & 0x06) == 4) {
/*TODO*/  //                    R_BASE = readUWord(f);
/*TODO*/  //                    pos += 4;
/*TODO*/  //                } else {
/*TODO*/  //                    log.warn("PH Relocation type 0x700000A1: Invalid size flag!");
/*TODO*/  //                    R_BASE = 0;
/*TODO*/  //                }
/*TODO*/  //            } else { // Operate on segment address based on the relocation flag.
/*TODO*/  //                if (log.isTraceEnabled()) {
/*TODO*/  //                	log.trace(String.format("Relocation 0x%04X, R_FLAG=0x%02X(%d), S=%d, %s(%d), rest=0x%X",
          //                R_CMD, R_FLAG, flagIndex, S, getRTypeName(R_TYPE), typeIndex, R_CMD >> (fbits + tbits +
          //                sbits)));
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                int ADDR_BASE = S;
/*TODO*/  //                phBaseOffset = baseAddress.getAddress() + elf.getProgramHeader(ADDR_BASE).getP_vaddr();
/*TODO*/  //
/*TODO*/  //                if ((R_FLAG & 0x06) == 0x00) {
/*TODO*/  //                    R_OFFSET = (int) (short) R_CMD; // sign-extend 16 to 32 bits
/*TODO*/  //                    R_OFFSET >>= (fbits + tbits + sbits);
/*TODO*/  //                    R_BASE += R_OFFSET;
/*TODO*/  //                } else if ((R_FLAG & 0x06) == 0x02) {
/*TODO*/  //                    R_OFFSET = (R_CMD << 16) >> (fbits + tbits + sbits);
/*TODO*/  //                    R_OFFSET &= 0xFFFF0000;
/*TODO*/  //                    R_OFFSET |= readUHalf(f);
/*TODO*/  //                    pos += 2;
/*TODO*/  //                    R_BASE += R_OFFSET;
/*TODO*/  //                } else if ((R_FLAG & 0x06) == 0x04) {
/*TODO*/  //                    R_BASE = readUWord(f);
/*TODO*/  //                    pos += 4;
/*TODO*/  //                } else {
/*TODO*/  //                    log.warn("PH Relocation type 0x700000A1: Invalid relocation size flag!");
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                // Process lo16.
/*TODO*/  //                if ((R_FLAG & 0x38) == 0x00) {
/*TODO*/  //                    lo16 = 0;
/*TODO*/  //                } else if ((R_FLAG & 0x38) == 0x08) {
/*TODO*/  //                    if ((R_TYPE_OLD ^ 0x04) != 0x00) {
/*TODO*/  //                        lo16 = 0;
/*TODO*/  //                    }
/*TODO*/  //                } else if ((R_FLAG & 0x38) == 0x10) {
/*TODO*/  //                    lo16 = readUHalf(f);
/*TODO*/  //                    lo16 = (int) (short) lo16; // sign-extend 16 to 32 bits
/*TODO*/  //                    pos += 2;
/*TODO*/  //                } else if ((R_FLAG & 0x38) == 0x18) {
/*TODO*/  //                    log.warn("PH Relocation type 0x700000A1: Invalid lo16 setup!");
/*TODO*/  //                } else {
/*TODO*/  //                    log.warn("PH Relocation type 0x700000A1: Invalid lo16 setup!");
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                // Read the data.
/*TODO*/  //                data_addr = R_BASE + baseAddress.getAddress() + elf.getProgramHeader(OFS_BASE).getP_vaddr();
/*TODO*/  //                data = readUnaligned32(mem, data_addr);
/*TODO*/  //
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                    log.debug(String.format("Relocation #%d type=%d, Offset PH#%d, Base Offset PH#%d, Offset
          //                    0x%08X",
/*TODO*/  //                            r, R_TYPE, OFS_BASE, ADDR_BASE, R_OFFSET));
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                int previousData = data;
/*TODO*/  //                // Apply the changes as requested by the relocation type.
/*TODO*/  //                switch (R_TYPE) {
/*TODO*/  //                    case 0: // R_MIPS_NONE
/*TODO*/  //                    	break;
/*TODO*/  //                    case 2: // R_MIPS_32
/*TODO*/  //                        data += phBaseOffset;
/*TODO*/  //                        break;
/*TODO*/  //                    case 3: // R_MIPS_26
/*TODO*/  //                        data = (data & 0xFC000000) | (((data & 0x03FFFFFF) + (phBaseOffset >>> 2)) &
          //                        0x03FFFFFF);
/*TODO*/  //                        break;
/*TODO*/  //                    case 6: // R_MIPS_J26
/*TODO*/  //                        data = (Opcodes.J << 26) | (((data & 0x03FFFFFF) + (phBaseOffset >>> 2)) &
          //                        0x03FFFFFF);
/*TODO*/  //                        break;
/*TODO*/  //                    case 7: // R_MIPS_JAL26
/*TODO*/  //                        data = (Opcodes.JAL << 26) | (((data & 0x03FFFFFF) + (phBaseOffset >>> 2)) &
          //                        0x03FFFFFF);
/*TODO*/  //                        break;
/*TODO*/  //                    case 4: // R_MIPS_HI16
/*TODO*/  //                        hi16 = ((data << 16) + lo16) + phBaseOffset;
/*TODO*/  //                        if ((hi16 & 0x8000) == 0x8000) {
/*TODO*/  //                            hi16 += 0x00010000;
/*TODO*/  //                        }
/*TODO*/  //                        data = (data & 0xffff0000) | (hi16 >>> 16);
/*TODO*/  //                        break;
/*TODO*/  //                    case 1: // R_MIPS_16
/*TODO*/  //                    case 5: // R_MIPS_LO16
/*TODO*/  //                        data = (data & 0xffff0000) | ((((int) (short) data) + phBaseOffset) & 0xffff);
/*TODO*/  //                        break;
/*TODO*/  //                    default:
/*TODO*/  //                        break;
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (previousData != data) {
/*TODO*/  //	                // Write the data.
/*TODO*/  //	                writeUnaligned32(mem, data_addr, data);
/*TODO*/  //	                if (log.isTraceEnabled()) {
/*TODO*/  //	                	log.trace(String.format("Relocation at 0x%08X: 0x%08X -> 0x%08X", data_addr,
          //previousData, data));
/*TODO*/  //	                }
/*TODO*/  //                }
/*TODO*/  //                r++;
/*TODO*/  //
/*TODO*/  //                R_TYPE_OLD = R_TYPE;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private boolean mustRelocate(Elf32 elf, Elf32SectionHeader shdr) {
/*TODO*/  //    	if (shdr.getSh_type() == Elf32SectionHeader.SHT_PRXREL) {
/*TODO*/  //    		// PSP PRX relocation section
/*TODO*/  //    		return true;
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	if (shdr.getSh_type() == Elf32SectionHeader.SHT_REL) {
/*TODO*/  //    		// Standard ELF relocation section
/*TODO*/  //    		Elf32SectionHeader relatedShdr = elf.getSectionHeader(shdr.getSh_info());
/*TODO*/  //    		// No relocation required for a debug section (sh_flags==SHF_NONE)
/*TODO*/  //    		if (relatedShdr != null && relatedShdr.getSh_flags() != Elf32SectionHeader.SHF_NONE) {
/*TODO*/  //    			return true;
/*TODO*/  //    		}
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	return false;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /** Uses info from the elf program headers and elf section headers to
/*TODO*/  //     * relocate a PRX. */
/*TODO*/  //    private void relocateFromHeaders(ByteBuffer f, SceModule module, TPointer baseAddress, Elf32 elf, int
          //    elfOffset) throws IOException {
/*TODO*/  //
/*TODO*/  //        // Relocate from program headers
/*TODO*/  //        int i = 0;
/*TODO*/  //        for (Elf32ProgramHeader phdr : elf.getProgramHeaderList()) {
/*TODO*/  //            if (phdr.getP_type() == 0x700000A0) {
/*TODO*/  //                int RelCount = phdr.getP_filesz() / Elf32Relocate.sizeof();
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                	log.debug(String.format("PH#%d: relocating %d entries", i, RelCount));
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                f.position(elfOffset + phdr.getP_offset());
/*TODO*/  //                relocateFromBuffer(f, module, baseAddress, elf, RelCount, true);
/*TODO*/  //                return;
/*TODO*/  //            } else if (phdr.getP_type() == 0x700000A1) {
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                	log.debug(String.format("Type 0x700000A1 PH#%d: relocating A1 entries, size=0x%X", i,
          //                phdr.getP_filesz()));
/*TODO*/  //                }
/*TODO*/  //                f.position(elfOffset + phdr.getP_offset());
/*TODO*/  //                relocateFromBufferA1(f, module, elf, baseAddress, i, phdr.getP_filesz());
/*TODO*/  //                return;
/*TODO*/  //            }
/*TODO*/  //            i++;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Relocate from section headers
/*TODO*/  //        for (Elf32SectionHeader shdr : elf.getSectionHeaderList()) {
/*TODO*/  //            if (mustRelocate(elf, shdr)) {
/*TODO*/  //                int RelCount = shdr.getSh_size() / Elf32Relocate.sizeof();
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                	log.debug(shdr.getSh_namez() + ": relocating " + RelCount + " entries");
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                f.position(elfOffset + shdr.getSh_offset());
/*TODO*/  //                relocateFromBuffer(f, module, baseAddress, elf, RelCount, shdr.getSh_type() !=
          //                Elf32SectionHeader.SHT_REL);
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private boolean isPopsLoader(SceModule module) throws IOException {
/*TODO*/  //        // Pops loader from EBOOT.PBP
/*TODO*/  //    	if (module.pspfilename.endsWith(scePopsMan.EBOOT_PBP)) {
/*TODO*/  //	        if ("complex".equals(module.modname) || "simple".equals(module.modname)) {
/*TODO*/  //	        	for (DeferredStub deferredStub : module.unresolvedImports) {
/*TODO*/  //	        		if (deferredStub.getNid() == 0x29B3FB24 &&
          //"scePopsMan".equals(deferredStub.getModuleName())) {
/*TODO*/  //	        			return true;
/*TODO*/  //	        		}
/*TODO*/  //	        	}
/*TODO*/  //	        }
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //        return false;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void ProcessUnresolvedImports(SceModule sourceModule, TPointer baseAddress, boolean fromSyscall)
          //    throws IOException {
/*TODO*/  //        Memory mem = baseAddress.getMemory();
/*TODO*/  //        NIDMapper nidMapper = NIDMapper.getInstance();
/*TODO*/  //        int numberoffailedNIDS = 0;
/*TODO*/  //        int numberofmappedNIDS = 0;
/*TODO*/  //
/*TODO*/  //        if (isPopsLoader(sourceModule)) {
/*TODO*/  //			Modules.scePopsManModule.loadOnDemand(sourceModule);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        for (SceModule module : Managers.modules.values()) {
/*TODO*/  //            module.importFixupAttempts++;
/*TODO*/  //            for (Iterator<DeferredStub> it = module.unresolvedImports.iterator(); it.hasNext(); ) {
/*TODO*/  //                DeferredStub deferredStub = it.next();
/*TODO*/  //                String moduleName = deferredStub.getModuleName();
/*TODO*/  //                int nid           = deferredStub.getNid();
/*TODO*/  //                int importAddress = deferredStub.getImportAddress();
/*TODO*/  //
/*TODO*/  //                // Attempt to fixup stub to point to an already loaded module export
/*TODO*/  //                int exportAddress = nidMapper.getAddressByNid(nid, moduleName);
/*TODO*/  //                if (exportAddress != 0) {
/*TODO*/  //                	deferredStub.resolve(mem, exportAddress);
/*TODO*/  //                    it.remove();
/*TODO*/  //                    sourceModule.resolvedImports.add(deferredStub);
/*TODO*/  //                    numberofmappedNIDS++;
/*TODO*/  //
/*TODO*/  //                    if (log.isDebugEnabled()) {
/*TODO*/  //                    	log.debug(String.format("Mapped import at 0x%08X to export at 0x%08X [0x%08X]
          //                    (attempt %d)",
/*TODO*/  //                    			importAddress, exportAddress, nid, module.importFixupAttempts));
/*TODO*/  //                    }
/*TODO*/  //                } else if (nid == 0) {
/*TODO*/  //                	// Ignore patched nids
/*TODO*/  //                    log.warn(String.format("Ignoring import at 0x%08X [0x%08X] (attempt %d)",
/*TODO*/  //                        importAddress, nid, module.importFixupAttempts));
/*TODO*/  //
/*TODO*/  //                    it.remove();
/*TODO*/  //                    // This is an import to be ignored, implement it with the following
/*TODO*/  //                    // code sequence:
/*TODO*/  //                    //    jr $ra          (already written to memory)
/*TODO*/  //                    //    li $v0, 0
/*TODO*/  //                    // Rem.: "BUST A MOVE GHOST" is testing the return value $v0,
/*TODO*/  //                    //       so it has to be set explicitly to 0.
/*TODO*/  //                    mem.write32(importAddress + 4, AllegrexOpcodes.ADDU | (2 << 11) | (0 << 16) | (0 <<
          //                    21)); // addu $v0, $zr, $zr <=> li $v0, 0
/*TODO*/  //                } else {
/*TODO*/  //                    // Attempt to fixup stub to known syscalls
/*TODO*/  //                    int code = nidMapper.getSyscallByNid(nid, moduleName);
/*TODO*/  //                    if (code >= 0) {
/*TODO*/  //                        // Fixup stub, replacing nop with syscall
/*TODO*/  //                    	int returnInstruction = // jr $ra
/*TODO*/  //                    	    (AllegrexOpcodes.SPECIAL << 26)
/*TODO*/  //                    	    | AllegrexOpcodes.JR
/*TODO*/  //                    	    | ((Common._ra) << 21);
/*TODO*/  //                        int syscallInstruction = // syscall <code>
/*TODO*/  //                            (AllegrexOpcodes.SPECIAL << 26)
/*TODO*/  //                            | AllegrexOpcodes.SYSCALL
/*TODO*/  //                            | ((code & 0x000fffff) << 6);
/*TODO*/  //
/*TODO*/  //                        // Some homebrews do not have a "jr $ra" set before the syscall
/*TODO*/  //                        if (mem.read32(importAddress) == 0) {
/*TODO*/  //                        	mem.write32(importAddress, returnInstruction);
/*TODO*/  //                        }
/*TODO*/  //                        mem.write32(importAddress + 4, syscallInstruction);
/*TODO*/  //                        it.remove();
/*TODO*/  //                        numberofmappedNIDS++;
/*TODO*/  //
/*TODO*/  //                        if (fromSyscall && log.isDebugEnabled()) {
/*TODO*/  //                            log.debug(String.format("Mapped import at 0x%08X to syscall 0x%05X [0x%08X]
          //                            (attempt %d)",
/*TODO*/  //                                importAddress, code, nid, module.importFixupAttempts));
/*TODO*/  //                        }
/*TODO*/  //                    } else if (!nidMapper.isHideAllSyscalls()) {
/*TODO*/  //                        log.warn(String.format("Failed to map import at 0x%08X [0x%08X] Module '%s'(attempt
          //                        %d)",
/*TODO*/  //                            importAddress, nid, moduleName, module.importFixupAttempts));
/*TODO*/  //                        numberoffailedNIDS++;
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        log.info(numberofmappedNIDS + " NIDS mapped");
/*TODO*/  //        if (numberoffailedNIDS > 0) {
/*TODO*/  //            log.info(numberoffailedNIDS + " remaining unmapped NIDS");
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /* Loads from memory */
/*TODO*/  //    private void LoadELFImports(SceModule module, TPointer baseAddress) throws IOException {
/*TODO*/  //        Memory mem = baseAddress.getMemory();
/*TODO*/  //        int stubHeadersAddress = module.stub_top;
/*TODO*/  //        int stubHeadersEndAddress = module.stub_top + module.stub_size;
/*TODO*/  //
/*TODO*/  //        // n modules to import, 1 stub header per module to import.
/*TODO*/  //        String moduleName;
/*TODO*/  //        for (int i = 0; stubHeadersAddress < stubHeadersEndAddress; i++) {
/*TODO*/  //            Elf32StubHeader stubHeader = new Elf32StubHeader(mem, stubHeadersAddress);
/*TODO*/  //
/*TODO*/  //            // Skip 0 sized entries.
/*TODO*/  //            if (stubHeader.getSize() <= 0) {
/*TODO*/  //                log.warn("Skipping dummy entry with size " + stubHeader.getSize());
/*TODO*/  //                stubHeadersAddress += Elf32StubHeader.sizeof() / 2;
/*TODO*/  //            } else {
/*TODO*/  //                if (Memory.isAddressGood((int)stubHeader.getOffsetModuleName())) {
/*TODO*/  //                    moduleName = Utilities.readStringNZ((int) stubHeader.getOffsetModuleName(), 64);
/*TODO*/  //                } else {
/*TODO*/  //                    // Generate a module name.
/*TODO*/  //                    moduleName = module.modname;
/*TODO*/  //                }
/*TODO*/  //                stubHeader.setModuleNamez(moduleName);
/*TODO*/  //
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                	log.debug(String.format("Processing Import #%d: %s", i, stubHeader.toString()));
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (stubHeader.hasVStub()) {
/*TODO*/  //                    if (log.isDebugEnabled()) {
/*TODO*/  //                    	log.debug(String.format("'%s': Header with VStub has size %d: %s",
          //                    stubHeader.getModuleNamez(), stubHeader.getSize(),
          //                    Utilities.getMemoryDump(stubHeadersAddress, stubHeader.getSize() * 4, 4, 16)));
/*TODO*/  //                    }
/*TODO*/  //                	int vStub = (int) stubHeader.getVStub();
/*TODO*/  //                	if (vStub != 0) {
/*TODO*/  //                    	int vStubSize = stubHeader.getVStubSize();
/*TODO*/  //                		if (log.isDebugEnabled()) {
/*TODO*/  //                			log.debug(String.format("VStub has size %d: %s", vStubSize,
          //                Utilities.getMemoryDump(vStub, vStubSize * 8, 4, 16)));
/*TODO*/  //                		}
/*TODO*/  //                		IMemoryReader vstubReader = MemoryReader.getMemoryReader(mem, vStub, vStubSize * 8,
          //                4);
/*TODO*/  //                    	for (int j = 0; j < vStubSize; j++) {
/*TODO*/  //                    		int relocAddr = vstubReader.readNext();
/*TODO*/  //	                    	int nid = vstubReader.readNext();
/*TODO*/  //	                    	// relocAddr points to a list of relocation terminated by a 0
/*TODO*/  //	                    	IMemoryReader relocReader = MemoryReader.getMemoryReader(mem, relocAddr, 4);
/*TODO*/  //	                    	while (true) {
/*TODO*/  //	                    		int reloc = relocReader.readNext();
/*TODO*/  //	                    		if (reloc == 0) {
/*TODO*/  //	                    			// End of relocation list
/*TODO*/  //	                    			break;
/*TODO*/  //	                    		}
/*TODO*/  //	                    		int opcode = reloc >>> 26;
/*TODO*/  //            					int address = (reloc & 0x03FFFFFF) << 2;
/*TODO*/  //            					DeferredStub deferredStub = null;
/*TODO*/  //                    			switch (opcode) {
/*TODO*/  //                    				case AllegrexOpcodes.BNE:
/*TODO*/  //                    					deferredStub = new DeferredVStubHI16(module,
          //                    stubHeader.getModuleNamez(), address, nid);
/*TODO*/  //                    					break;
/*TODO*/  //                    				case AllegrexOpcodes.BLEZ:
/*TODO*/  //                    					deferredStub = new DeferredVstubLO16(module,
          //                    stubHeader.getModuleNamez(), address, nid);
/*TODO*/  //                    					break;
/*TODO*/  //                    				case AllegrexOpcodes.J:
/*TODO*/  //                    					deferredStub = new DeferredVStub32(module,
          //                    stubHeader.getModuleNamez(), address, nid);
/*TODO*/  //                    					break;
/*TODO*/  //                    				default:
/*TODO*/  //        	                    		log.warn(String.format("Unknown Vstub relocation nid 0x%08X,
          //        reloc=0x%08X", nid, reloc));
/*TODO*/  //        	                    		break;
/*TODO*/  //                    			}
/*TODO*/  //
/*TODO*/  //                    			if (deferredStub != null) {
/*TODO*/  //                    				if (log.isDebugEnabled()) {
/*TODO*/  //                    					log.debug(String.format("Vstub reloc %s",
          //                    deferredStub));
/*TODO*/  //                    				}
/*TODO*/  //                    				module.unresolvedImports.add(deferredStub);
/*TODO*/  //                    			}
/*TODO*/  //	                    	}
/*TODO*/  //                    	}
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //                stubHeadersAddress += stubHeader.getSize() * 4;
/*TODO*/  //
/*TODO*/  //                if (!Memory.isAddressGood((int) stubHeader.getOffsetNid()) || !Memory.isAddressGood((int)
          //                stubHeader.getOffsetText())) {
/*TODO*/  //                	log.warn(String.format("Incorrect s_nid or s_text address in StubHeader #%d: %s", i,
          //                stubHeader.toString()));
/*TODO*/  //                } else {
/*TODO*/  //	                // n stubs per module to import
/*TODO*/  //	                IMemoryReader nidReader = MemoryReader.getMemoryReader(mem, (int)
          //stubHeader.getOffsetNid(), stubHeader.getImports() * 4, 4);
/*TODO*/  //	                for (int j = 0; j < stubHeader.getImports(); j++) {
/*TODO*/  //	                	int nid = nidReader.readNext();
/*TODO*/  //	                	int importAddress = (int) (stubHeader.getOffsetText() + j * 8);
/*TODO*/  //	                    DeferredStub deferredStub = new DeferredStub(module, stubHeader.getModuleNamez(),
          //importAddress, nid);
/*TODO*/  //
/*TODO*/  //	                    // Add a 0xfffff syscall so we can detect if an unresolved import is called
/*TODO*/  //	                    deferredStub.unresolve(mem);
/*TODO*/  //	                }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (module.unresolvedImports.size() > 0) {
/*TODO*/  //        	if (log.isInfoEnabled()) {
/*TODO*/  //        		log.info(String.format("Found %d unresolved imports", module.unresolvedImports.size()));
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int getOffsetFromRelocation(ByteBuffer f, Elf32 elf, int elfOffset, int relocationOffset, int
          //    relocationSize, int position) throws IOException {
/*TODO*/  //    	int relocationCount = relocationSize / Elf32Relocate.sizeof();
/*TODO*/  //    	f.position(elfOffset + relocationOffset);
/*TODO*/  //    	Elf32Relocate rel = new Elf32Relocate();
/*TODO*/  //        for (int i = 0; i < relocationCount; i++) {
/*TODO*/  //        	rel.read(f);
/*TODO*/  //            int R_TYPE = rel.getR_info() & 0xFF;
/*TODO*/  //            if (R_TYPE == 2) { //R_MIPS_32
/*TODO*/  //	            int OFS_BASE  = (rel.getR_info() >>  8) & 0xFF;
/*TODO*/  //	            int ADDR_BASE = (rel.getR_info() >> 16) & 0xFF;
/*TODO*/  //	        	int relocationPosition = rel.getR_offset() +
          //elf.getProgramHeader(OFS_BASE).getP_vaddr();
/*TODO*/  //	        	if (relocationPosition == position) {
/*TODO*/  //	        		return elf.getProgramHeader(ADDR_BASE).getP_offset();
/*TODO*/  //	        	}
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return -1;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int getOffsetFromRelocationA1(ByteBuffer f, SceModule module, Elf32 elf, int elfOffset, int
          //    programHeaderNumber, int relocationOffset, int relocationSize, int position) throws IOException {
/*TODO*/  //        // Relocation variables.
/*TODO*/  //        int R_OFFSET = 0;
/*TODO*/  //        int R_BASE = 0;
/*TODO*/  //
/*TODO*/  //        // Buffer position variable.
/*TODO*/  //        int pos = elfOffset + relocationOffset;
/*TODO*/  //        int end = pos + relocationSize;
/*TODO*/  //
/*TODO*/  //        // Locate and read the flag, type and segment bits.
/*TODO*/  //        f.position(pos + 2);
/*TODO*/  //        int fbits = readUByte(f);
/*TODO*/  //        int flagShift = 0;
/*TODO*/  //        int flagMask = (1 << fbits) - 1;
/*TODO*/  //
/*TODO*/  //        int sbits = programHeaderNumber < 3 ? 1 : 2;
/*TODO*/  //        int segmentShift = fbits;
/*TODO*/  //        int segmentMask = (1 << sbits) - 1;
/*TODO*/  //
/*TODO*/  //        int tbits = readUByte(f);
/*TODO*/  //        int typeShift = fbits + sbits;
/*TODO*/  //        int typeMask = (1 << tbits) - 1;
/*TODO*/  //
/*TODO*/  //        // Locate the flag table.
/*TODO*/  //        int flags[] = new int[readUByte(f)];
/*TODO*/  //        flags[0] = flags.length;
/*TODO*/  //        for (int j = 1; j < flags.length; j++) {
/*TODO*/  //        	flags[j] = readUByte(f);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Locate the type table.
/*TODO*/  //        int types[] = new int[readUByte(f)];
/*TODO*/  //        types[0] = types.length;
/*TODO*/  //        for (int j = 1; j < types.length; j++) {
/*TODO*/  //        	types[j] = readUByte(f);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // loadcore.prx and sysmem.prx are being loaded and relocated by
/*TODO*/  //        // the PSP reboot code. It is using a different type mapping.
/*TODO*/  //        // See https://github.com/uofw/uofw/blob/master/src/reboot/elf.c#L327
/*TODO*/  //    	if ("flash0:/kd/loadcore.prx".equals(module.pspfilename) ||
          //    "flash0:/kd/sysmem.prx".equals(module.pspfilename)) {
/*TODO*/  //    		final int[] rebootTypeRemapping = new int[] { 0, 3, 6, 7, 1, 2, 4, 5 };
/*TODO*/  //    		for (int i = 1; i < types.length; i++) {
/*TODO*/  //    			types[i] = rebootTypeRemapping[types[i]];
/*TODO*/  //    		}
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //        // Save the current position.
/*TODO*/  //        pos = f.position();
/*TODO*/  //
/*TODO*/  //        while (pos < end) {
/*TODO*/  //            // Read the CMD byte.
/*TODO*/  //            int R_CMD = readUHalf(f);
/*TODO*/  //            pos += 2;
/*TODO*/  //
/*TODO*/  //            // Process the relocation flag.
/*TODO*/  //            int flagIndex = (R_CMD >> flagShift) & flagMask;
/*TODO*/  //            int R_FLAG = flags[flagIndex];
/*TODO*/  //
/*TODO*/  //            // Set the segment offset.
/*TODO*/  //            int S = (R_CMD >> segmentShift) & segmentMask;
/*TODO*/  //
/*TODO*/  //            // Process the relocation type.
/*TODO*/  //            int typeIndex = (R_CMD >> typeShift) & typeMask;
/*TODO*/  //            int R_TYPE = types[typeIndex];
/*TODO*/  //
/*TODO*/  //            if ((R_FLAG & 0x01) == 0) {
/*TODO*/  //                if ((R_FLAG & 0x06) == 0) {
/*TODO*/  //                    R_BASE = (R_CMD >> (fbits + sbits));
/*TODO*/  //                } else if ((R_FLAG & 0x06) == 4) {
/*TODO*/  //                    R_BASE = readUWord(f);
/*TODO*/  //                    pos += 4;
/*TODO*/  //                } else {
/*TODO*/  //                    R_BASE = 0;
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                int ADDR_BASE = S;
/*TODO*/  //
/*TODO*/  //                if ((R_FLAG & 0x06) == 0x00) {
/*TODO*/  //                    R_OFFSET = (int) (short) R_CMD; // sign-extend 16 to 32 bits
/*TODO*/  //                    R_OFFSET >>= (fbits + tbits + sbits);
/*TODO*/  //                    R_BASE += R_OFFSET;
/*TODO*/  //                } else if ((R_FLAG & 0x06) == 0x02) {
/*TODO*/  //                    R_OFFSET = (R_CMD << 16) >> (fbits + tbits + sbits);
/*TODO*/  //                    R_OFFSET &= 0xFFFF0000;
/*TODO*/  //                    R_OFFSET |= readUHalf(f);
/*TODO*/  //                    pos += 2;
/*TODO*/  //                    R_BASE += R_OFFSET;
/*TODO*/  //                } else if ((R_FLAG & 0x06) == 0x04) {
/*TODO*/  //                    R_BASE = readUWord(f);
/*TODO*/  //                    pos += 4;
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if ((R_FLAG & 0x38) == 0x10) {
/*TODO*/  //                	readUHalf(f);
/*TODO*/  //                    pos += 2;
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (R_TYPE == 2) { // R_MIPS_32
/*TODO*/  //                	if (R_BASE == position) {
/*TODO*/  //                		return elf.getProgramHeader(ADDR_BASE).getP_offset();
/*TODO*/  //                	}
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return -1;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int getOffsetFromRelocation(ByteBuffer f, SceModule module, Elf32 elf, int elfOffset, int
          //    position) throws IOException {
/*TODO*/  //    	int i = 0;
/*TODO*/  //        for (Elf32ProgramHeader phdr : elf.getProgramHeaderList()) {
/*TODO*/  //            if (phdr.getP_type() == 0x700000A0) {
/*TODO*/  //                int offset = getOffsetFromRelocation(f, elf, elfOffset, phdr.getP_offset(),
          //                phdr.getP_filesz(), position);
/*TODO*/  //                if (offset >= 0) {
/*TODO*/  //                	return offset;
/*TODO*/  //                }
/*TODO*/  //            } else if (phdr.getP_type() == 0x700000A1) {
/*TODO*/  //                int offset = getOffsetFromRelocationA1(f, module, elf, elfOffset, i, phdr.getP_offset(),
          //                phdr.getP_filesz(), position);
/*TODO*/  //                if (offset >= 0) {
/*TODO*/  //                	return offset;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            i++;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        for (Elf32SectionHeader shdr : elf.getSectionHeaderList()) {
/*TODO*/  //        	if (shdr.getSh_type() == Elf32SectionHeader.SHT_PRXREL) {
/*TODO*/  //                int offset = getOffsetFromRelocation(f, elf, elfOffset, shdr.getSh_offset(),
          //                shdr.getSh_size(), position);
/*TODO*/  //                if (offset >= 0) {
/*TODO*/  //                	return offset;
/*TODO*/  //                }
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void LoadSDKVersion(ByteBuffer f, SceModule module, Elf32 elf, int elfOffset) throws IOException
          //    {
/*TODO*/  //        int entHeadersOffset = elfOffset + elf.getProgramHeader(0).getP_offset();
/*TODO*/  //        int entHeadersAddress = module.ent_top;
/*TODO*/  //        int entHeadersEndAddress = module.ent_top + module.ent_size;
/*TODO*/  //        while (entHeadersAddress < entHeadersEndAddress) {
/*TODO*/  //            f.position(entHeadersOffset + entHeadersAddress);
/*TODO*/  //        	Elf32EntHeader entHeader = new Elf32EntHeader(f);
/*TODO*/  //
/*TODO*/  //        	if (entHeader.getSize() <= 0) {
/*TODO*/  //                entHeadersAddress += Elf32EntHeader.sizeof() / 2;
/*TODO*/  //        	} else if (entHeader.getSize() > 4) {
/*TODO*/  //                entHeadersAddress += entHeader.getSize() * 4;
/*TODO*/  //            } else {
/*TODO*/  //                entHeadersAddress += Elf32EntHeader.sizeof();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            int functionCount = entHeader.getFunctionCount();
/*TODO*/  //            int variableCount = entHeader.getVariableCount();
/*TODO*/  //            int nidAddr = (int) entHeader.getOffsetResident();
/*TODO*/  //            int exportAddr = nidAddr + (functionCount + variableCount) * 4;
/*TODO*/  //            int variableTableAddr = exportAddr + functionCount * 4;
/*TODO*/  //
/*TODO*/  //            int[] variableNids = new int[variableCount];
/*TODO*/  //            f.position(entHeadersOffset + nidAddr + functionCount * 4);
/*TODO*/  //            for (int j = 0; j < variableCount; j++) {
/*TODO*/  //            	variableNids[j] = readUWord(f);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            int[] variableTable = new int[variableCount];
/*TODO*/  //            for (int j = 0; j < variableCount; j++) {
/*TODO*/  //            	int pos = variableTableAddr + j * 4;
/*TODO*/  //            	int offset = getOffsetFromRelocation(f, module, elf, elfOffset, pos);
/*TODO*/  //            	f.position(entHeadersOffset + pos);
/*TODO*/  //            	variableTable[j] = readUWord(f) + offset;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            for (int j = 0; j < variableCount; j++) {
/*TODO*/  //            	switch (variableNids[j]) {
/*TODO*/  //            		case 0x11B97506: // module_sdk_version
/*TODO*/  //            			f.position(elfOffset + variableTable[j]);
/*TODO*/  //            			module.moduleVersion = readUWord(f);
/*TODO*/  //            			if (log.isDebugEnabled()) {
/*TODO*/  //            				log.debug(String.format("Found sdkVersion=0x%08X",
          //            module.moduleVersion));
/*TODO*/  //            			}
/*TODO*/  //            			break;
/*TODO*/  //            	}
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /* Loads from memory */
/*TODO*/  //    private void LoadELFExports(SceModule module, TPointer baseAddress) throws IOException {
/*TODO*/  //        NIDMapper nidMapper = NIDMapper.getInstance();
/*TODO*/  //        Memory mem = baseAddress.getMemory();
/*TODO*/  //        int entHeadersAddress = module.ent_top;
/*TODO*/  //        int entHeadersEndAddress = module.ent_top + module.ent_size;
/*TODO*/  //        int entCount = 0;
/*TODO*/  //
/*TODO*/  //        // n modules to export, 1 ent header per module to export.
/*TODO*/  //        String moduleName;
/*TODO*/  //        for (int i = 0; entHeadersAddress < entHeadersEndAddress; i++) {
/*TODO*/  //            Elf32EntHeader entHeader = new Elf32EntHeader(mem, entHeadersAddress);
/*TODO*/  //
/*TODO*/  //            if ((entHeader.getSize() <= 0)) {
/*TODO*/  //                // Skip 0 sized entries.
/*TODO*/  //                log.warn("Skipping dummy entry with size " + entHeader.getSize());
/*TODO*/  //                entHeadersAddress += Elf32EntHeader.sizeof() / 2;
/*TODO*/  //            } else {
/*TODO*/  //                if (Memory.isAddressGood((int)entHeader.getOffsetModuleName())) {
/*TODO*/  //                    moduleName = Utilities.readStringNZ((int) entHeader.getOffsetModuleName(), 64);
/*TODO*/  //                } else {
/*TODO*/  //                    // Generate a module name.
/*TODO*/  //                    moduleName = module.modname;
/*TODO*/  //                }
/*TODO*/  //                entHeader.setModuleNamez(moduleName);
/*TODO*/  //
/*TODO*/  //                if (log.isDebugEnabled()) {
/*TODO*/  //                	log.debug(String.format("Processing header #%d at 0x%08X: %s", i, entHeadersAddress,
          //                entHeader.toString()));
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (entHeader.getSize() > 4) {
/*TODO*/  //                    if (log.isDebugEnabled()) {
/*TODO*/  //                    	log.debug(String.format("'%s': Header has size %d: %s",
          //                    entHeader.getModuleNamez(), entHeader.getSize(),
          //                    Utilities.getMemoryDump(entHeadersAddress, entHeader.getSize() * 4, 4, 16)));
/*TODO*/  //                    }
/*TODO*/  //                    entHeadersAddress += entHeader.getSize() * 4;
/*TODO*/  //                } else {
/*TODO*/  //                    entHeadersAddress += Elf32EntHeader.sizeof();
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                // The export section is organized as as sequence of:
/*TODO*/  //                // - 32-bit NID * functionCount
/*TODO*/  //                // - 32-bit NID * variableCount
/*TODO*/  //                // - 32-bit export address * functionCount
/*TODO*/  //                // - 32-bit variable address * variableCount
/*TODO*/  //                //   (each variable address references another structure, depending on its NID)
/*TODO*/  //                //
/*TODO*/  //                int functionCount = entHeader.getFunctionCount();
/*TODO*/  //                int variableCount = entHeader.getVariableCount();
/*TODO*/  //                int nidAddr = (int) entHeader.getOffsetResident();
/*TODO*/  //                IMemoryReader nidReader = MemoryReader.getMemoryReader(mem, nidAddr, (functionCount +
          //                variableCount) * 4, 4);
/*TODO*/  //                int exportAddr = nidAddr + (functionCount + variableCount) * 4;
/*TODO*/  //                IMemoryReader exportReader = MemoryReader.getMemoryReader(mem, exportAddr, functionCount *
          //                4, 4);
/*TODO*/  //                if ((entHeader.getAttr() & 0x8000) == 0) {
/*TODO*/  //	                for (int j = 0; j < functionCount; j++) {
/*TODO*/  //	                    int nid = nidReader.readNext();
/*TODO*/  //	                    int exportAddress = exportReader.readNext();
/*TODO*/  //                        // Only accept exports with valid export addresses and
/*TODO*/  //	                    // from custom modules (attr != 0x4000) unless
/*TODO*/  //	                    // the module is a homebrew (loaded from MemoryStick) or
/*TODO*/  //	                    // this is the EBOOT module.
/*TODO*/  //                        if (Memory.isAddressGood(exportAddress) && ((entHeader.getAttr() & 0x4000) !=
          //                        0x4000) || module.pspfilename.startsWith("ms0:") ||
          //                        module.pspfilename.startsWith("disc0:/PSP_GAME/SYSDIR/EBOOT.") ||
          //                        module.pspfilename.startsWith("flash0:")) {
/*TODO*/  //                            nidMapper.addModuleNid(module, moduleName, nid, exportAddress, false);
/*TODO*/  //                            entCount++;
/*TODO*/  //                            if (log.isDebugEnabled()) {
/*TODO*/  //                                log.debug(String.format("Export found at 0x%08X [0x%08X]", exportAddress,
          //                                nid));
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //	                }
/*TODO*/  //                } else {
/*TODO*/  //	                for (int j = 0; j < functionCount; j++) {
/*TODO*/  //	                    int nid = nidReader.readNext();
/*TODO*/  //	                    int exportAddress = exportReader.readNext();
/*TODO*/  //
/*TODO*/  //	                    switch (nid) {
/*TODO*/  //	                        case 0xD632ACDB: // module_start
/*TODO*/  //	                            module.module_start_func = exportAddress;
/*TODO*/  //	                            if (log.isDebugEnabled()) {
/*TODO*/  //	                                log.debug(String.format("module_start found: nid=0x%08X,
          //function=0x%08X", nid, exportAddress));
/*TODO*/  //	                            }
/*TODO*/  //	                            break;
/*TODO*/  //	                        case 0xCEE8593C: // module_stop
/*TODO*/  //	                            module.module_stop_func = exportAddress;
/*TODO*/  //	                            if (log.isDebugEnabled()) {
/*TODO*/  //	                                log.debug(String.format("module_stop found: nid=0x%08X,
          //function=0x%08X", nid, exportAddress));
/*TODO*/  //	                            }
/*TODO*/  //	                            break;
/*TODO*/  //	                        case 0x2F064FA6: // module_reboot_before
/*TODO*/  //	                            module.module_reboot_before_func = exportAddress;
/*TODO*/  //	                            if (log.isDebugEnabled()) {
/*TODO*/  //	                                log.debug(String.format("module_reboot_before found: nid=0x%08X,
          //function=0x%08X", nid, exportAddress));
/*TODO*/  //	                            }
/*TODO*/  //	                            break;
/*TODO*/  //	                        case 0xADF12745: // module_reboot_phase
/*TODO*/  //	                            module.module_reboot_phase_func = exportAddress;
/*TODO*/  //	                            if (log.isDebugEnabled()) {
/*TODO*/  //	                                log.debug(String.format("module_reboot_phase found: nid=0x%08X,
          //function=0x%08X", nid, exportAddress));
/*TODO*/  //	                            }
/*TODO*/  //	                            break;
/*TODO*/  //	                        case 0xD3744BE0: // module_bootstart
/*TODO*/  //	                            module.module_bootstart_func = exportAddress;
/*TODO*/  //	                            if (log.isDebugEnabled()) {
/*TODO*/  //	                                log.debug(String.format("module_bootstart found: nid=0x%08X,
          //function=0x%08X", nid, exportAddress));
/*TODO*/  //	                            }
/*TODO*/  //	                            break;
/*TODO*/  //	                        default:
/*TODO*/  //	                            // Only accept exports from custom modules (attr != 0x4000) and with valid
          //export addresses.
/*TODO*/  //	                            if (Memory.isAddressGood(exportAddress) && ((entHeader.getAttr() & 0x4000)
          //!= 0x4000)) {
/*TODO*/  //	                                nidMapper.addModuleNid(module, moduleName, nid, exportAddress, false);
/*TODO*/  //	                                entCount++;
/*TODO*/  //	                                if (log.isDebugEnabled()) {
/*TODO*/  //	                                    log.debug(String.format("Export found at 0x%08X [0x%08X]",
          //exportAddress, nid));
/*TODO*/  //	                                }
/*TODO*/  //	                            }
/*TODO*/  //	                            break;
/*TODO*/  //	                    }
/*TODO*/  //	                }
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                int variableTableAddr = exportAddr + functionCount * 4;
/*TODO*/  //                IMemoryReader variableReader = MemoryReader.getMemoryReader(mem, variableTableAddr,
          //                variableCount * 4, 4);
/*TODO*/  //                for (int j = 0; j < variableCount; j++) {
/*TODO*/  //                    int nid = nidReader.readNext();
/*TODO*/  //                    int variableAddr = variableReader.readNext();
/*TODO*/  //
/*TODO*/  //                    switch (nid) {
/*TODO*/  //                        case 0xF01D73A7: // module_info
/*TODO*/  //                            // Seems to be ignored by the PSP
/*TODO*/  //                            if (log.isDebugEnabled()) {
/*TODO*/  //                                log.debug(String.format("module_info found: nid=0x%08X, addr=0x%08X", nid,
          //                                variableAddr));
/*TODO*/  //                            }
/*TODO*/  //                            break;
/*TODO*/  //                        case 0x0F7C276C: // module_start_thread_parameter
/*TODO*/  //                            module.module_start_thread_priority = mem.read32(variableAddr + 4);
/*TODO*/  //                            module.module_start_thread_stacksize = mem.read32(variableAddr + 8);
/*TODO*/  //                            module.module_start_thread_attr = mem.read32(variableAddr + 12);
/*TODO*/  //                            if (log.isDebugEnabled()) {
/*TODO*/  //                                log.debug(String.format("module_start_thread_parameter found: nid=0x%08X,
          //                                priority=%d, stacksize=%d, attr=0x%08X", nid,
          //                                module.module_start_thread_priority, module.module_start_thread_stacksize,
          //                                module.module_start_thread_attr));
/*TODO*/  //                            }
/*TODO*/  //                            break;
/*TODO*/  //                        case 0xCF0CC697: // module_stop_thread_parameter
/*TODO*/  //                            module.module_stop_thread_priority = mem.read32(variableAddr + 4);
/*TODO*/  //                            module.module_stop_thread_stacksize = mem.read32(variableAddr + 8);
/*TODO*/  //                            module.module_stop_thread_attr = mem.read32(variableAddr + 12);
/*TODO*/  //                            if (log.isDebugEnabled()) {
/*TODO*/  //                                log.debug(String.format("module_stop_thread_parameter found: nid=0x%08X,
          //                                priority=%d, stacksize=%d, attr=0x%08X", nid,
          //                                module.module_stop_thread_priority, module.module_stop_thread_stacksize,
          //                                module.module_stop_thread_attr));
/*TODO*/  //                            }
/*TODO*/  //                            break;
/*TODO*/  //                        case 0xF4F4299D: // module_reboot_before_thread_parameter
/*TODO*/  //                            module.module_reboot_before_thread_priority = mem.read32(variableAddr + 4);
/*TODO*/  //                            module.module_reboot_before_thread_stacksize = mem.read32(variableAddr + 8);
/*TODO*/  //                            module.module_reboot_before_thread_attr = mem.read32(variableAddr + 12);
/*TODO*/  //                            if (log.isDebugEnabled()) {
/*TODO*/  //                                log.debug(String.format("module_reboot_before_thread_parameter found:
          //                                nid=0x%08X, priority=%d, stacksize=%d, attr=0x%08X", nid,
          //                                module.module_reboot_before_thread_priority,
          //                                module.module_reboot_before_thread_stacksize,
          //                                module.module_reboot_before_thread_attr));
/*TODO*/  //                            }
/*TODO*/  //                            break;
/*TODO*/  //                        case 0x11B97506: // module_sdk_version
/*TODO*/  //                            module.moduleVersion = mem.read32(variableAddr);
/*TODO*/  //                            if (log.isDebugEnabled()) {
/*TODO*/  //                                log.debug(String.format("module_sdk_version found: nid=0x%08X,
          //                                sdkVersion=0x%08X", nid, module.moduleVersion));
/*TODO*/  //                            }
/*TODO*/  //                            break;
/*TODO*/  //                        default:
/*TODO*/  //                            // Only accept exports from custom modules (attr != 0x4000) and with valid
          //                            export addresses.
/*TODO*/  //                            if (Memory.isAddressGood(variableAddr) && ((entHeader.getAttr() & 0x4000) !=
          //                            0x4000)) {
/*TODO*/  //                                nidMapper.addModuleNid(module, moduleName, nid, variableAddr, true);
/*TODO*/  //                                entCount++;
/*TODO*/  //                                if (log.isDebugEnabled()) {
/*TODO*/  //                                    log.debug(String.format("Export found at 0x%08X [0x%08X]", variableAddr,
          //                                    nid));
/*TODO*/  //                                }
/*TODO*/  //                            } else {
/*TODO*/  //                            	log.warn(String.format("Unknown variable entry found: nid=0x%08X,
          //                            addr=0x%08X", nid, variableAddr));
/*TODO*/  //                            }
/*TODO*/  //                            break;
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (entCount > 0) {
/*TODO*/  //        	if (log.isInfoEnabled()) {
/*TODO*/  //        		log.info(String.format("Found %d exports", entCount));
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void LoadELFDebuggerInfo(ByteBuffer f, SceModule module, TPointer baseAddress, Elf32 elf, int
          //    elfOffset, boolean fromSyscall) throws IOException {
/*TODO*/  //        // Save executable section address/size for the debugger/instruction counter
/*TODO*/  //        Elf32SectionHeader shdr;
/*TODO*/  //
/*TODO*/  //        shdr = elf.getSectionHeader(".init");
/*TODO*/  //        if (shdr != null) {
/*TODO*/  //            module.initsection[0] = shdr.getSh_addr(baseAddress);
/*TODO*/  //            module.initsection[1] = shdr.getSh_size();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        shdr = elf.getSectionHeader(".fini");
/*TODO*/  //        if (shdr != null) {
/*TODO*/  //            module.finisection[0] = shdr.getSh_addr(baseAddress);
/*TODO*/  //            module.finisection[1] = shdr.getSh_size();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        shdr = elf.getSectionHeader(".sceStub.text");
/*TODO*/  //        if (shdr != null) {
/*TODO*/  //            module.stubtextsection[0] = shdr.getSh_addr(baseAddress);
/*TODO*/  //            module.stubtextsection[1] = shdr.getSh_size();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (!fromSyscall) {
/*TODO*/  //            ElfHeaderInfo.ElfInfo = elf.getElfInfo();
/*TODO*/  //            ElfHeaderInfo.ProgInfo = elf.getProgInfo();
/*TODO*/  //            ElfHeaderInfo.SectInfo = elf.getSectInfo();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * Apply patches to some VSH and Kernel modules
/*TODO*/  //     *
/*TODO*/  //     * @param module
/*TODO*/  //     */
/*TODO*/  //    private void patchModule(SceModule module) {
/*TODO*/  //    	Memory mem = Emulator.getMemory();
/*TODO*/  //
/*TODO*/  //    	// Same patches as ProCFW
/*TODO*/  //    	if ("vsh_module".equals(module.modname)) {
/*TODO*/  //    		patch(mem, module, 0x000122B0, 0x506000E0, NOP());
/*TODO*/  //    		patch(mem, module, 0x00012058, 0x1440003B, NOP());
/*TODO*/  //    		patch(mem, module, 0x00012060, 0x14400039, NOP());
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	// Patches to replace "https" with "http" so that the URL calls
/*TODO*/  //    	// can be proxied through the internal HTTP server.
/*TODO*/  //    	if ("sceNpCommerce2".equals(module.modname)) {
/*TODO*/  //    		patch(mem, module, 0x0000A598, 0x00000073, 0x00000000); // replace "https" with "http"
/*TODO*/  //    		patch(mem, module, 0x00003A60, 0x240701BB, 0x24070050); // replace port 443 with 80
/*TODO*/  //    	}
/*TODO*/  //    	if ("sceNpCore".equals(module.modname)) {
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x00000D50, 's'); // replace "https" with "http" in
          //    "https://auth.%s.ac.playstation.net/nav/auth"
/*TODO*/  //    	}
/*TODO*/  //    	if ("sceNpService".equals(module.modname)) {
/*TODO*/  //    		patch(mem, module, 0x0001075C, 0x00000073, 0x00000000); // replace "https" with "http"
          //    for "https://getprof.%s.np.community.playstation.net/basic_view/sec/get_self_profile"
/*TODO*/  //    	}
/*TODO*/  //    	if ("sceVshNpInstaller_Module".equals(module.modname)) {
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x00016F90, 's'); // replace "https" with "http" in
          //    "https://commerce.%s.ac.playstation.net/cap.m"
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x00016FC0, 's'); // replace "https" with "http" in
          //    "https://commerce.%s.ac.playstation.net/cdp.m"
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x00016FF0, 's'); // replace "https" with "http" in
          //    "https://commerce.%s.ac.playstation.net/kdp.m"
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x00017020, 's'); // replace "https" with "http" in
          //    "https://account.%s.ac.playstation.net/ecomm/ingame/startDownloadDRM"
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x00017064, 's'); // replace "https" with "http" in
          //    "https://account.%s.ac.playstation.net/ecomm/ingame/finishDownloadDRM"
/*TODO*/  //    	}
/*TODO*/  //    	if ("marlindownloader".equals(module.modname)) {
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x000046C8, 's'); // replace "https" with "http" in
          //    "https://mds.%s.ac.playstation.net/"
/*TODO*/  //    	}
/*TODO*/  //    	if ("sceVshStoreBrowser_Module".equals(module.modname)) {
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x0005A244, 's'); // replace "https" with "http" in
          //    "https://nsx-e.sec.%s.dl.playstation.net/nsx/sec/..."
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x0005A2D8, 's'); // replace "https" with "http" in
          //    "https://nsx.sec.%s.dl.playstation.net/nsx/sec/..."
/*TODO*/  //    	}
/*TODO*/  //    	if ("sceGameUpdate_Library".equals(module.modname)) {
/*TODO*/  //    		patchRemoveStringChar(mem, module, 0x000030C4, 's'); // replace "https" with "http" in
          //    "https://a0.ww.%s.dl.playstation.net/tpl/..."
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	if ("sceMemlmd".equals(module.modname)) {
/*TODO*/  //    		patch(mem, module, 0x000017EC, 0x0E000000, MOVE(_v0, _zr), 0xFE000000); // replace "jal
          //    sceUtilsBufferCopy(cmd=15)" with "move $v0, $zr"
/*TODO*/  //    		SysMemInfo dummyArea = Modules.SysMemUserForUserModule.malloc(KERNEL_PARTITION_ID,
          //    "patch-sceMemlmd", PSP_SMEM_Low, 256, 0);
/*TODO*/  //    		patch(mem, module, 0x000024C0, 0xBFC00220, dummyArea.addr); // replace hardware register
          //    address with dummy address
/*TODO*/  //    		patch(mem, module, 0x000024D4, 0xBFC00280, dummyArea.addr); // replace hardware register
          //    address with dummy address
/*TODO*/  //    		patch(mem, module, 0x000024D8, 0xBFC00A00, dummyArea.addr); // replace hardware register
          //    address with dummy address
/*TODO*/  //    		patch(mem, module, 0x000024DC, 0xBFC00340, dummyArea.addr); // replace hardware register
          //    address with dummy address
/*TODO*/  //    		// Replace entry of sceUtilsBufferCopyWithRange with "return 0".
/*TODO*/  //    		patch(mem, module, 0x00001CFC, 0x27BDFFE0, JR());
/*TODO*/  //    		patch(mem, module, 0x00001D00, 0x3C020000, MOVE(_v0, _zr), 0xFFFF0000);
/*TODO*/  //    		// Patch memlmd_9D36A439 with "return 1"
/*TODO*/  //    		patch(mem, module, 0x00001414, 0x0044102B, ADDIU(_v0, _zr, 1)); // replace "sltu $v0,
          //    $v0, $a0" with "li $v0, 1"
/*TODO*/  //    		// Patch memlmd_F26A33C3
/*TODO*/  //    		patch(mem, module, 0x000012D8, 0x90430000, ADDIU(_v1, _zr, 1)); // replace "lbu $v1,
          //    0($v0)" with "li $v1, 1"
/*TODO*/  //    		patch(mem, module, 0x00001324, 0x90460000, ADDIU(_a2, _zr, 0)); // replace "lbu $a2,
          //    0($v0)" with "li $a2, 0"
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	if ("sceModuleManager".equals(module.modname)) {
/*TODO*/  //    		patch(mem, module, 0x000030CC, 0x24030020, 0x24030010); // replace "li $v1, 32" with "li
          //    $v1, 16" (this will be stored at SceLoadCoreExecFileInfo.apiType)
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	if ("sceLoaderCore".equals(module.modname)) {
/*TODO*/  //    		patch(mem, module, 0x0000469C, 0x15C0FFA0, NOP()); // Allow loading of privileged
          //    modules being not encrypted (https://github.com/uofw/uofw/blob/master/src/loadcore/loadelf.c#L339)
/*TODO*/  //    		patch(mem, module, 0x00004548, 0x7C0F6244, NOP()); // Allow loading of privileged
          //    modules being not encrypted (take SceLoadCoreExecFileInfo.modInfoAttribute from the ELF module info,
          //    https://github.com/uofw/uofw/blob/master/src/loadcore/loadelf.c#L351)
/*TODO*/  //    		patch(mem, module, 0x00004550, 0x14E0002C, 0x1000002C); // Allow loading of privileged
          //    modules being not encrypted (https://github.com/uofw/uofw/blob/master/src/loadcore/loadelf.c#L352)
/*TODO*/  //    		patch(mem, module, 0x00003D58, 0x10C0FFBE, NOP()); // Allow linking user stub to kernel
          //    lib
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	Modules.scePopsManModule.patchModule(mem, module);
/*TODO*/  //    }
