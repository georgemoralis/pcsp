/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#include "PCSPCommon.h"
#include "Emulator.h"
#include "HLE/kernel/types/SceModule.h"
#include "Memory.h"
#include "Loader.h"
#include <src/src/HLE/modules/SysMemUserForUser.h>

/*TODO*/  // public class Emulator implements Runnable {
/*TODO*/  //
/*TODO*/  //    private static Emulator instance;
/*TODO*/  //    private static Processor processor;
/*TODO*/  //    private static Clock clock;
/*TODO*/  //    private static Scheduler scheduler;
/*TODO*/  //    private boolean moduleLoaded;
/*TODO*/  //    private Thread mainThread;
/*TODO*/  //    public static boolean run = false;
/*TODO*/  //    public static boolean pause = false;
/*TODO*/  //    private static boolean exitCalled = false;
/*TODO*/  //    private static IMainGUI gui;
/*TODO*/  //    private InstructionCounter instructionCounter;
/*TODO*/  //    public static Logger log = Logger.getLogger("emu");
SceModule* _module;
/*TODO*/  //    private int firmwareVersion = 999;
/*TODO*/  //    private String[] bootModuleBlackList = {"Prometheus Loader"};
/*TODO*/  //
/*TODO*/  //    public Emulator(IMainGUI gui) {
/*TODO*/  //        Emulator.gui = gui;
/*TODO*/  //        processor = new Processor();
/*TODO*/  //        clock = new Clock();
/*TODO*/  //        scheduler = Scheduler.getInstance();
/*TODO*/  //
/*TODO*/  //        moduleLoaded = false;
/*TODO*/  //        mainThread = new Thread(this, "Emu");
/*TODO*/  //
/*TODO*/  //        instance = this;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Thread getMainThread() {
/*TODO*/  //        return mainThread;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static boolean exitCalled() {
/*TODO*/  //    	return exitCalled;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static void exit() {
/*TODO*/  //    	exitCalled = true;
/*TODO*/  //
/*TODO*/  //        ProOnlineNetworkAdapter.exit();
/*TODO*/  //        XLinkKaiWlanAdapter.exit();
/*TODO*/  //        Modules.ThreadManForUserModule.exit();
/*TODO*/  //        Modules.sceDisplayModule.exit();
/*TODO*/  //        Modules.IoFileMgrForUserModule.exit();
/*TODO*/  //        VideoEngine.exit();
/*TODO*/  //        Screen.exit();
/*TODO*/  //        if (DurationStatistics.collectStatistics) {
/*TODO*/  //            log.info(TextureCache.getInstance().statistics);
/*TODO*/  //        }
/*TODO*/  //        RendererExecutor.exit();
/*TODO*/  //        VertexCache.getInstance().exit();
/*TODO*/  //        Compiler.exit();
/*TODO*/  //        RuntimeContextLLE.exit();
/*TODO*/  //        RuntimeContext.exit();
/*TODO*/  //        Profiler.exit();
/*TODO*/  //        GEProfiler.exit();
/*TODO*/  //        BaseRenderer.exit();
/*TODO*/  //        BasePrimitiveRenderer.exit();
/*TODO*/  //        ExternalGE.exit();
/*TODO*/  //        if (DurationStatistics.collectStatistics && Modules.ThreadManForUserModule.statistics != null &&
          //        Modules.sceDisplayModule.statistics != null) {
/*TODO*/  //            long totalMillis = getClock().milliTime();
/*TODO*/  //            long displayMillis = Modules.sceDisplayModule.statistics.cumulatedTimeMillis;
/*TODO*/  //            long idleCpuMillis = RuntimeContext.idleDuration.getCpuDurationMillis();
/*TODO*/  //            long compilationCpuMillis = Compiler.compileDuration.getCpuDurationMillis();
/*TODO*/  //            long cpuMillis = Modules.ThreadManForUserModule.statistics.allCpuMillis - compilationCpuMillis -
          //            idleCpuMillis;
/*TODO*/  //            long cpuCycles = Modules.ThreadManForUserModule.statistics.allCycles;
/*TODO*/  //            double totalSecs = totalMillis / 1000.0;
/*TODO*/  //            double displaySecs = displayMillis / 1000.0;
/*TODO*/  //            double cpuSecs = cpuMillis / 1000.0;
/*TODO*/  //            if (totalSecs != 0) {
/*TODO*/  //                log.info("Total execution time: " + String.format("%.3f", totalSecs) + "s");
/*TODO*/  //                log.info("     PSP CPU time: " + String.format("%.3f", cpuSecs) + "s (" +
          //                String.format("%.1f", cpuSecs / totalSecs * 100) + "%)");
/*TODO*/  //                log.info("     Display time: " + String.format("%.3f", displaySecs) + "s (" +
          //                String.format("%.1f", displaySecs / totalSecs * 100) + "%)");
/*TODO*/  //            }
/*TODO*/  //            if (VideoEngine.getStatistics() != null) {
/*TODO*/  //                long videoCalls = VideoEngine.getStatistics().numberCalls;
/*TODO*/  //                if (videoCalls != 0) {
/*TODO*/  //                    log.info("Elapsed time per frame: " + String.format("%.3f", totalSecs / videoCalls) +
          //                    "s:");
/*TODO*/  //                    log.info("    Display time: " + String.format("%.3f", displaySecs / videoCalls));
/*TODO*/  //                    log.info("    PSP CPU time: " + String.format("%.3f", cpuSecs / videoCalls) + " (" +
          //                    (cpuCycles / videoCalls) + " instr)");
/*TODO*/  //                }
/*TODO*/  //                if (totalSecs != 0) {
/*TODO*/  //                    log.info("Display Speed: " + String.format("%.2f", videoCalls / totalSecs) + " FPS");
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            if (cpuSecs != 0) {
/*TODO*/  //                log.info("PSP CPU Speed: " + String.format("%.2f", cpuCycles / cpuSecs / 1000000.0) + "MHz
          //                (" + (long) (cpuCycles / cpuSecs) + " instructions per second)");
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //        SoundChannel.exit();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private boolean isBootModuleBad(String name) {
/*TODO*/  //        for (String moduleName : bootModuleBlackList) {
/*TODO*/  //            if (name.equals(moduleName)) {
/*TODO*/  //                return true;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //        return false;
/*TODO*/  //    }
/*TODO*/  //
SceModule* Emulator::load(const char* pspfilename, std::ifstream& f) 
{ 
    return load(pspfilename, f, false, false, NULL); 
}

u8* Emulator::getLoadAddress() { 
    u32 lowestAddress = 0x8804000; //fake!
    return Memory::getPointer(lowestAddress);
}
    /*TODO*/  //    private TPointer getLoadAddress() {
/*TODO*/  //    	Memory mem = Emulator.getMemory();
/*TODO*/  //        SysMemInfo testInfo = Modules.SysMemUserForUserModule.malloc(USER_PARTITION_ID, "test-LoadAddress",
          //        SysMemUserForUser.PSP_SMEM_Low, 0x100, 0);
/*TODO*/  //        if (testInfo == null) {
/*TODO*/  //        	return new TPointer(mem, MemoryMap.START_USERSPACE + 0x4000);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        int lowestAddress = testInfo.addr;
/*TODO*/  //        Modules.SysMemUserForUserModule.free(testInfo);
/*TODO*/  //
/*TODO*/  //        return new TPointer(mem, lowestAddress);
/*TODO*/  //    }
/*TODO*/  //
SceModule *Emulator::load(const char *pspfilename, std::ifstream &f,bool fromSyscall, bool isSignChecked,u8* key) {
    /*TODO*/  //        initNewPsp(fromSyscall);
/*TODO*/  //
/*TODO*/  //        HLEModuleManager.getInstance().loadAvailableFlash0Modules(fromSyscall);
/*TODO*/  //
        u8* loadAddress = getLoadAddress();

    	_module = Loader::LoadModule(pspfilename, f, loadAddress, USER_PARTITION_ID,USER_PARTITION_ID, false, true, fromSyscall, isSignChecked, key);
/*TODO*/  //
/*TODO*/  //        if ((module.fileFormat & Loader.FORMAT_ELF) != Loader.FORMAT_ELF) {
/*TODO*/  //            throw new GeneralJpcspException("File format not supported!");
/*TODO*/  //        }
/*TODO*/  //        if (isBootModuleBad(module.modname)) {
/*TODO*/  //            JpcspDialogManager.showError(null,
          //            java.util.ResourceBundle.getBundle("jpcsp/languages/jpcsp").getString("Emulator.strPrometheusLoader.text"));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        moduleLoaded = true;
/*TODO*/  //        RuntimeContextLLE.onEmulatorLoad();
/*TODO*/  //        initCpu(fromSyscall);
/*TODO*/  //
/*TODO*/  //        // Delete breakpoints and reset to PC
/*TODO*/  //        if (State.debugger != null) {
/*TODO*/  //            State.debugger.resetDebugger();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Update instruction counter dialog with the new app
/*TODO*/  //        if (instructionCounter != null) {
/*TODO*/  //            instructionCounter.setModule(module);
/*TODO*/  //        }
/*TODO*/  //
        return _module;
    }
/*TODO*/  //
/*TODO*/  //    public boolean isPspOfficialUpdater() {
/*TODO*/  //    	if (module == null) {
/*TODO*/  //    		return false;
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	String discId = module.psf != null ? module.psf.getString("DISC_ID") : State.discId;
/*TODO*/  //    	// The official PSP Update EBOOT has DISC_ID=MSTKUPDATE
/*TODO*/  //        if ("MSTKUPDATE".equals(discId)) {
/*TODO*/  //        	return true;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // PSP Updater 1.50, 1.51 and 1.52 do not have a DISC_ID, check the TITLE
/*TODO*/  //    	if (isMatchingPsfTitle(module, "PSP. Update ver 1\\.5[0-2]")) {
/*TODO*/  //    		return true;
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	return false;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getPspOfficialUpdaterVersion() {
/*TODO*/  //    	if (module == null || module.psf == null) {
/*TODO*/  //    		return -1;
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	String updateVer = module.psf.getString("UPDATER_VER");
/*TODO*/  //    	if (updateVer == null) {
/*TODO*/  //    		return -1;
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	int version = Integer.parseInt(updateVer.replace(".", ""));
/*TODO*/  //
/*TODO*/  //    	// PSP Updater 3.80 has a wrong "UPDATER_VER = 9.99",
/*TODO*/  //    	// extract the correct version from the TITLE.
/*TODO*/  //    	if (version == 999) {
/*TODO*/  //    		String title = module.psf.getString("TITLE");
/*TODO*/  //    		if (title != null) {
/*TODO*/  //    			Pattern p = Pattern.compile("PSP. Update ver ([1-6]\\.[0-9][0-9])");
/*TODO*/  //    			Matcher m = p.matcher(title);
/*TODO*/  //    			if (m.matches()) {
/*TODO*/  //    				version = Integer.parseInt(m.group(1).replace(".", ""));
/*TODO*/  //    			}
/*TODO*/  //    		}
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	return version;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initCpu(boolean fromSyscall) {
/*TODO*/  //    	// The official PSP Update EBOOT requires MMIO to access the Nand
/*TODO*/  //        if (isPspOfficialUpdater()) {
/*TODO*/  //        	RuntimeContextLLE.createMMIO();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        RuntimeContext.update();
/*TODO*/  //
/*TODO*/  //        int entryAddr = module.entry_addr;
/*TODO*/  //        if (Memory.isAddressGood(module.module_start_func)) {
/*TODO*/  //            if (module.module_start_func != entryAddr) {
/*TODO*/  //                log.warn(String.format("Using the module start function as module entry: 0x%08X instead of
          //                0x%08X", module.module_start_func, entryAddr));
/*TODO*/  //                entryAddr = module.module_start_func;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        HLEModuleManager.getInstance().startModules(fromSyscall);
/*TODO*/  //        Modules.ThreadManForUserModule.Initialise(module, entryAddr, module.attribute, module.pspfilename,
          //        module.modid, module.gp_value, fromSyscall);
/*TODO*/  //
/*TODO*/  //        if (State.memoryViewer != null) {
/*TODO*/  //            State.memoryViewer.RefreshMemory();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void initNewPsp(boolean fromSyscall) {
/*TODO*/  //        moduleLoaded = false;
/*TODO*/  //
/*TODO*/  //        Model.init();
/*TODO*/  //        Nand.init();
/*TODO*/  //        HLEModuleManager.getInstance().stopModules();
/*TODO*/  //        NIDMapper.getInstance().unloadAll();
/*TODO*/  //        RuntimeContext.reset();
/*TODO*/  //
/*TODO*/  //        if (!fromSyscall) {
/*TODO*/  //            // Do not reset the profiler if we have been called from sceKernelLoadExec
/*TODO*/  //            Profiler.reset();
/*TODO*/  //            GEProfiler.reset();
/*TODO*/  //            // Do not reset the clock if we have been called from sceKernelLoadExec
/*TODO*/  //            getClock().reset();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        getProcessor().reset();
/*TODO*/  //        getScheduler().reset();
/*TODO*/  //
/*TODO*/  //        Memory mem = Memory.getInstance();
/*TODO*/  //        if (!fromSyscall) {
/*TODO*/  //            // Clear all memory, including VRAM.
/*TODO*/  //            mem.Initialise();
/*TODO*/  //        } else {
/*TODO*/  //            // Clear all memory excepted VRAM.
/*TODO*/  //            // E.g. screen is not cleared when executing syscall sceKernelLoadExec().
/*TODO*/  //            mem.memset(MemoryMap.START_SCRATCHPAD, (byte) 0, MemoryMap.SIZE_SCRATCHPAD);
/*TODO*/  //            mem.memset(MemoryMap.START_RAM, (byte) 0, MemoryMap.SIZE_RAM);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        Battery.initialize();
/*TODO*/  //        Wlan.initialize();
/*TODO*/  //        SceUidManager.reset();
/*TODO*/  //        HLEUidObjectMapping.reset();
/*TODO*/  //        ProOnlineNetworkAdapter.init();
/*TODO*/  //        XLinkKaiWlanAdapter.init();
/*TODO*/  //
/*TODO*/  //        if (State.fileLogger != null) {
/*TODO*/  //            State.fileLogger.resetLogging();
/*TODO*/  //        }
/*TODO*/  //        MemorySections.getInstance().reset();
/*TODO*/  //
/*TODO*/  //        Modules.SysMemUserForUserModule.start();
/*TODO*/  //        HLEUtilities.getInstance().init();
/*TODO*/  //        HLEModuleManager.getInstance().init();
/*TODO*/  //        Managers.reset();
/*TODO*/  //        Modules.SysMemUserForUserModule.setFirmwareVersion(firmwareVersion);
/*TODO*/  //    	Modules.ThreadManForUserModule.start();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void run() {
/*TODO*/  //        RuntimeContext.start();
/*TODO*/  //        RuntimeContextLLE.start();
/*TODO*/  //        GEProfiler.initialise();
/*TODO*/  //
/*TODO*/  //        clock.resume();
/*TODO*/  //
/*TODO*/  //        while (true) {
/*TODO*/  //            if (pause) {
/*TODO*/  //                clock.pause();
/*TODO*/  //                try {
/*TODO*/  //                    synchronized (this) {
/*TODO*/  //                        while (pause) {
/*TODO*/  //                            wait();
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                } catch (InterruptedException e) {
/*TODO*/  //                    // Ignore exception
/*TODO*/  //                }
/*TODO*/  //                clock.resume();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            RuntimeContextLLE.run();
/*TODO*/  //
/*TODO*/  //            if (RuntimeContext.isCompilerEnabled()) {
/*TODO*/  //                RuntimeContext.run();
/*TODO*/  //            } else {
/*TODO*/  //                processor.step();
/*TODO*/  //                Modules.sceGe_userModule.step();
/*TODO*/  //                Modules.ThreadManForUserModule.step();
/*TODO*/  //                scheduler.step();
/*TODO*/  //                Modules.sceDisplayModule.step();
/*TODO*/  //
/*TODO*/  //                if (State.debugger != null) {
/*TODO*/  //                    State.debugger.step();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public synchronized void RunEmu() {
/*TODO*/  //        if (!moduleLoaded) {
/*TODO*/  //            Emulator.log.debug("Nothing loaded, can't run...");
/*TODO*/  //            gui.RefreshButtons();
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (pause) {
/*TODO*/  //            pause = false;
/*TODO*/  //            notifyAll();
/*TODO*/  //        } else if (!run) {
/*TODO*/  //            run = true;
/*TODO*/  //            mainThread.start();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        Modules.sceDisplayModule.setGeDirty(true);
/*TODO*/  //
/*TODO*/  //        gui.RefreshButtons();
/*TODO*/  //        if (State.debugger != null) {
/*TODO*/  //            State.debugger.RefreshButtons();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private static void PauseEmu(boolean hasStatus, int status) {
/*TODO*/  //        if (run && !pause) {
/*TODO*/  //            pause = true;
/*TODO*/  //            Emulator.status = status;
/*TODO*/  //
/*TODO*/  //            if (hasStatus) {
/*TODO*/  //                StepLogger.setStatus(status);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (gui != null) {
/*TODO*/  //            	gui.RefreshButtons();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (State.debugger != null) {
/*TODO*/  //                State.debugger.SafeRefreshDebugger(true);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (State.memoryViewer != null) {
/*TODO*/  //                State.memoryViewer.SafeRefreshMemory();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (State.imageViewer != null) {
/*TODO*/  //                State.imageViewer.SafeRefreshImage();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            StepLogger.flush();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static synchronized void PauseEmu() {
/*TODO*/  //        PauseEmu(false, 0);
/*TODO*/  //    }
/*TODO*/  //    public static final int EMU_STATUS_OK = 0x00;
/*TODO*/  //    public static final int EMU_STATUS_UNKNOWN = 0xFFFFFFFF;
/*TODO*/  //    public static final int EMU_STATUS_WDT_IDLE = 0x01;
/*TODO*/  //    public static final int EMU_STATUS_WDT_HOG = 0x02;
/*TODO*/  //    public static final int EMU_STATUS_WDT_ANY = EMU_STATUS_WDT_IDLE | EMU_STATUS_WDT_HOG;
/*TODO*/  //    public static final int EMU_STATUS_MEM_READ = 0x04;
/*TODO*/  //    public static final int EMU_STATUS_MEM_WRITE = 0x08;
/*TODO*/  //    public static final int EMU_STATUS_MEM_ANY = EMU_STATUS_MEM_READ | EMU_STATUS_MEM_WRITE;
/*TODO*/  //    public static final int EMU_STATUS_BREAKPOINT = 0x10;
/*TODO*/  //    public static final int EMU_STATUS_UNIMPLEMENTED = 0x20;
/*TODO*/  //    public static final int EMU_STATUS_PAUSE = 0x40;
/*TODO*/  //    public static final int EMU_STATUS_JUMPSELF = 0x80;
/*TODO*/  //    public static final int EMU_STATUS_BREAK = 0x100;
/*TODO*/  //    public static final int EMU_STATUS_HALT = 0x200;
/*TODO*/  //    public static final int EMU_STATUS_SHUTDOWN = 0x400;
/*TODO*/  //    public static final int EMU_STATUS_SUSPEND = 0x800;
/*TODO*/  //    public static int status = EMU_STATUS_UNKNOWN;
/*TODO*/  //
/*TODO*/  //    public static synchronized void PauseEmuWithStatus(int status) {
/*TODO*/  //        PauseEmu(true, status);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static void setFpsTitle(String fps) {
/*TODO*/  //        gui.setMainTitle(fps);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Processor getProcessor() {
/*TODO*/  //        return processor;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Processor setProcessor(Processor processor) {
/*TODO*/  //    	Processor previousProcessor = Emulator.processor;
/*TODO*/  //    	Emulator.processor = processor;
/*TODO*/  //
/*TODO*/  //    	return previousProcessor;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Memory getMemory() {
/*TODO*/  //        return Memory.getInstance();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //	public static Memory getMemory(int address) {
/*TODO*/  //		if (!Memory.isAddressGood(address)) {
/*TODO*/  //			Memory mmio = RuntimeContextLLE.getMMIO();
/*TODO*/  //			if (mmio != null) {
/*TODO*/  //				return mmio;
/*TODO*/  //			}
/*TODO*/  //		}
/*TODO*/  //
/*TODO*/  //		return getMemory();
/*TODO*/  //	}
/*TODO*/  //
/*TODO*/  //    public static Clock getClock() {
/*TODO*/  //        return clock;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private static void setClock(Clock clock) {
/*TODO*/  //        Emulator.clock = clock;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Scheduler getScheduler() {
/*TODO*/  //        return scheduler;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static IMainGUI getMainGUI() {
/*TODO*/  //        return gui;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Emulator getInstance() {
/*TODO*/  //        return instance;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setInstructionCounter(InstructionCounter instructionCounter) {
/*TODO*/  //        this.instructionCounter = instructionCounter;
/*TODO*/  //        instructionCounter.setModule(module);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getFirmwareVersion() {
/*TODO*/  //        return firmwareVersion;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * @param firmwareVersion : in this format: ABB, where A = major and B =
/*TODO*/  //     * minor, for example 271
/*TODO*/  //     */
/*TODO*/  //    public void setFirmwareVersion(int firmwareVersion) {
/*TODO*/  //        this.firmwareVersion = firmwareVersion;
/*TODO*/  //
/*TODO*/  //        Modules.SysMemUserForUserModule.setFirmwareVersion(this.firmwareVersion);
/*TODO*/  //        RuntimeContext.setFirmwareVersion(firmwareVersion);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * @param firmwareVersion : in this format: "A.BB", where A = major and B =
/*TODO*/  //     * minor, for example "2.71"
/*TODO*/  //     */
/*TODO*/  //    public void setFirmwareVersion(String firmwareVersion) {
/*TODO*/  //        setFirmwareVersion(HLEModuleManager.psfFirmwareVersionToInt(firmwareVersion));
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static void setVariableSpeedClock(int numerator, int denominator) {
/*TODO*/  //        if (getClock() instanceof VariableSpeedClock) {
/*TODO*/  //            // Update the speed of the current variable speed clock
/*TODO*/  //            ((VariableSpeedClock) getClock()).setSpeed(numerator, denominator);
/*TODO*/  //        } else if (numerator != 1 || denominator != 1) {
/*TODO*/  //            // Change the clock to a variable speed clock with the given speed
/*TODO*/  //            VariableSpeedClock variableSpeedClock = new VariableSpeedClock(clock, numerator, denominator);
/*TODO*/  //            setClock(variableSpeedClock);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setModuleLoaded(boolean moduleLoaded) {
/*TODO*/  //    	this.moduleLoaded = moduleLoaded;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public SceModule getModule() {
/*TODO*/  //    	return module;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void onReboot() {
/*TODO*/  //    	if (log.isDebugEnabled()) {
/*TODO*/  //    		log.debug(String.format("Emulator onReboot"));
/*TODO*/  //    	}
/*TODO*/  //    	module = null;
/*TODO*/  //		RuntimeContext.onReboot();
/*TODO*/  //		reboot.resetThreadManInfo(processor);
/*TODO*/  //    }
/*TODO*/  //}
/*TODO*/  //
