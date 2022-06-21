/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#pragma once 

struct SceModule_t {
    u32 next;  // should be handled by a manager
    u16 attribute;
    u16 version;
    char modname[28];  // 27 printable chars
    u32 status;// 2 bytes for status + 2 bytes of padding
    u32 unk1;
    u32 modid;
    u32 usermod_thid; 
    u32 memid;
    u32 mpidtext; 
    u32 mpiddata;
    u32 ent_top;  // we'll use bytes (instead of number of entries)
    u32 ent_size;
    u32 stub_top;
    u32 stub_size;  // we'll use bytes (instead of number of entries)
    u32 module_start_func;
    u32 module_stop_func;
    u32 module_bootstart_func;
    u32 module_reboot_before_func;
    u32 module_reboot_phase_func;
    u32 entry_addr;
    u32 gp_value;
    u32 text_addr;
    u32 text_size;
    u32 data_size;
    u32 bss_size;
    u32 nsegment;        // ? maybe init/text/sceStub.text/fini
    u32 segmentaddr[4];  // ?
    u32 segmentsize[4];  // ?
    u32 module_start_thread_priority;
    u32 module_start_thread_stacksize;
    u32 module_start_thread_attr;
    u32 module_stop_thread_priority;
    u32 module_stop_thread_stacksize;
    u32 module_stop_thread_attr;
    u32 module_reboot_before_thread_priority;
    u32 module_reboot_before_thread_stacksize;
    u32 module_reboot_before_thread_attr;
};

class SceModule : public SceModule_t {
  public:
    SceModule();
    SceModule(bool isFlashModule);
    ~SceModule();

    // loader stuff
    u32 fileFormat;// see Loader class for valid formats
    std::string pspfilename;  // boot path, for thread argument
    int moduleVersion;

    /// The space consumed by the program image
    u32 loadAddressLow, loadAddressHigh;
    u32 baseAddress; // should in theory be the same as loadAddressLow
};
