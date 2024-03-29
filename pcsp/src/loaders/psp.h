typedef struct
{
    u8 signature[4];
    u16 mod_attribute;
    u16 comp_attribute;
    u8 module_ver_lo;
    u8 module_ver_hi;
    char modname[28];
    u8 mod_version;
    u8 nsegments;
    u32 elf_size;
    u32 psp_size;
    u32 boot_entry;
    u32 modinfo_offset;
    u32 bss_size;
    u16 seg_align[4];
    u32 seg_address[4];
    u32 seg_size[4];
    u32 reserved[5];
    u32 devkit_version;
    u8 decrypt_mode;
    u8 padding;
    u16 overlap_size;
    u8 aes_key[0x10];
    u8 cmac_key[0x10];
    u8 cmac_header_hash[0x10];
    u32 comp_size;
    u32 _80;
    u32 unk_B8;
    u32 unk_BC;
    u8 cmac_data_hash[0x10];
    u32 tag;
    u8 scheck[0x58];
    u8 sha1_hash[0x14];
    u8 key_data4[0x10];
} PSP_HEADER;
