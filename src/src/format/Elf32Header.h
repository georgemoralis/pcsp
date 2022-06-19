/*
*  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff Completed!
*/
#pragma once

#define ELF_MAGIC 0x464C457F;

enum Elf32HeaderMachine {
	E_MACHINE_SPARC   = 0x0002,
	E_MACHINE_x86     = 0x0003,
	E_MACHINE_MIPS    = 0x0008,
	E_MACHINE_PowerPC = 0x0014,
	E_MACHINE_ARM     = 0x0028,
	E_MACHINE_SuperH  = 0x002A,
	E_MACHINE_IA_64   = 0x0032,
	E_MACHINE_x86_64  = 0x003E,
	E_MACHINE_AArch64 = 0x00B7
};

enum Elf32HeaderType { ET_SCE_PRX = 0xFFA0 };

class Elf32Header
{
   public:
    Elf32Header();
    Elf32Header(std::ifstream &f);
    ~Elf32Header();

    void read(std::ifstream &f);

    static const size_t sizeOf();
    bool isValid() const;
    bool isMIPSExecutable() const;
    bool isPRXDetected() const;
    bool requiresRelocation() const;

    std::string toString() const;

    u32 getE_magic() const;
    u8 getE_class() const;
    u8 getE_data() const;
    u8 getE_idver() const;
    std::vector<u8> getE_pad() const;
    u16 getE_type() const;
    u16 getE_machine() const;
    u32 getE_version() const;
    u32 getE_entry() const;
    u32 getE_phoff() const;
    u32 getE_shoff() const;
    u32 getE_flags() const;
    u16 getE_ehsize() const;
    u16 getE_phentsize() const;
    u16 getE_phnum() const;
    u16 getE_shentsize();
    u16 getE_shnum() const;
    u16 getE_shstrndx() const;
   private:
    struct {
        u32 e_magic;
        u8 e_class;
        u8 e_data;
        u8 e_idver;
        u8 e_pad[9];
        u16 e_type;
        u16 e_machine;
        u32 e_version;
        u32 e_entry;
        u32 e_phoff;
        u32 e_shoff;
        u32 e_flags;
        u16 e_ehsize;
        u16 e_phentsize;
        u16 e_phnum;
        u16 e_shentsize;
        u16 e_shnum;
        u16 e_shstrndx;
    } data;
};

