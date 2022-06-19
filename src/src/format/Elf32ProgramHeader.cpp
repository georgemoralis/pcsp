/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff Completed!
 */
#include "..\PCSPCommon.h"
#include "Elf32ProgramHeader.h"

Elf32ProgramHeader::Elf32ProgramHeader() {}

Elf32ProgramHeader::Elf32ProgramHeader(std::ifstream &f) { read(f); }

Elf32ProgramHeader::~Elf32ProgramHeader() {}

void Elf32ProgramHeader::read(std::ifstream &f) { f.read((char *)&data, sizeof(data)); }

const size_t Elf32ProgramHeader::sizeOf() { return 32; }

std::string Elf32ProgramHeader::toString() const {
    std::string str;
    char tmp[128];

    sprintf(tmp, "p_type   0x%08X\n", data.p_type);
    str.append(tmp);
    sprintf(tmp, "p_offset 0x%08X\n", data.p_offset);
    str.append(tmp);
    sprintf(tmp, "p_vaddr  0x%08X\n", data.p_vaddr);
    str.append(tmp);
    sprintf(tmp, "p_paddr  0x%08X\n", data.p_paddr);
    str.append(tmp);
    sprintf(tmp, "p_filesz 0x%08X\n", data.p_filesz);
    str.append(tmp);
    sprintf(tmp, "p_memsz  0x%08X\n", data.p_memsz);
    str.append(tmp);
    sprintf(tmp, "p_flags  0x%08X\n", data.p_flags);
    str.append(tmp);
    sprintf(tmp, "p_align  0x%08X\n", data.p_align);
    str.append(tmp);

    return str;
}

u32 Elf32ProgramHeader::getP_type() const { return data.p_type; }

u32 Elf32ProgramHeader::getP_offset() const { return data.p_offset; }

u32 Elf32ProgramHeader::getP_vaddr() const { return data.p_vaddr; }

u32 Elf32ProgramHeader::getP_paddr() const { return data.p_paddr; }

u32 Elf32ProgramHeader::getP_filesz() const { return data.p_filesz; }

u32 Elf32ProgramHeader::getP_memsz() const { return data.p_memsz; }

u32 Elf32ProgramHeader::getP_flags() const { return data.p_flags; }

u32 Elf32ProgramHeader::getP_align() const { return data.p_align; }
