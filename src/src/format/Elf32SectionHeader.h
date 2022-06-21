/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff  - Small TODO requires
 */
#pragma once

enum Elf32SectionFlags {
	SHF_NONE = 0x00000000,
	SHF_WRITE = 0x00000001,
	SHF_ALLOCATE = 0x00000002,
	SHF_EXECUTE = 0x00000004
};

enum Elf32SectionTypes {
	SHT_NULL = 0x00000000,
	SHT_PROGBITS = 0x00000001,
	SHT_SYMTAB = 0x00000002,
	SHT_STRTAB = 0x00000003,
	SHT_RELA = 0x00000004,
	SHT_HASH = 0x00000005,
	SHT_DYNAMIC = 0x00000006,
	SHT_NOTE = 0x00000007,
	SHT_NOBITS = 0x00000008,
	SHT_REL = 0x00000009,
	SHT_SHLIB = 0x0000000A,
	SHT_DYNSYM = 0x0000000B,
	SHT_PRXREL = 0x700000A0
};
class Elf32SectionHeader
{
   public:
    Elf32SectionHeader();
    Elf32SectionHeader(std::ifstream &f);
    ~Elf32SectionHeader();

    static const size_t sizeOf();
    std::string toString() const;

    std::string getSh_namez() const;
    void setSh_namez(const std::string &namez);
    
	u32 getSh_name() const;
    u32 getSh_type() const;
    u32 getSh_flags() const;
    u32 getSh_addr() const;
    u32 getSh_offset() const;
    u32 getSh_size() const;
    u32 getSh_link() const;
    u32 getSh_info() const;
    u32 getSh_addralign() const;
    u32 getSh_entsize() const;
    u32 getSh_addr(u32 baseAddress) const;

   private:
	std::string sh_namez;
	struct {
		u32 sh_name;
		u32 sh_type;
		u32 sh_flags;
		u32 sh_addr;
		u32 sh_offset;
		u32 sh_size;
		u32	sh_link;
		u32 sh_info;
		u32 sh_addralign;
		u32 sh_entsize;
	} data;
};
