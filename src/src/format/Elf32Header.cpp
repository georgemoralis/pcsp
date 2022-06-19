/*
*  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff Completed!
*/
#include "..\PCSPCommon.h"
#include "Elf32Header.h"


Elf32Header::Elf32Header() { }

Elf32Header::Elf32Header(std::ifstream &f) { read(f); }

Elf32Header::~Elf32Header() {}

void Elf32Header::read(std::ifstream &f) {
    if (!(f.peek() == std::ifstream::traits_type::eof())) {  // if not empty
        f.read((char *)&data, sizeof(data));
    }
}

const size_t Elf32Header::sizeOf() { return sizeof(data); }

bool Elf32Header::isValid() const { return data.e_magic == ELF_MAGIC; }

bool Elf32Header::isMIPSExecutable() const { return data.e_machine == E_MACHINE_MIPS; }
bool Elf32Header::isPRXDetected() const { return data.e_type == ET_SCE_PRX; }

bool Elf32Header::requiresRelocation() const { return isPRXDetected() || getE_entry() < MemoryMap::START_RAM; }

std::string Elf32Header::toString() const {
    std::string str = "--------ELF HEADER--------\n";
    char tmp[128];

    sprintf(tmp, "e_magic     0x%08X\n", data.e_magic);
    str.append(tmp);
    sprintf(tmp, "e_class     0x%02X\n", data.e_class);
    str.append(tmp);
    sprintf(tmp, "e_data      0x%02X\n", data.e_data);
    str.append(tmp);
    sprintf(tmp, "e_idver     0x%02X\n", data.e_idver);
    str.append(tmp);
    sprintf(tmp, "e_type      0x%04X\n", data.e_type);
    str.append(tmp);
    sprintf(tmp, "e_machine   0x%04X\n", data.e_machine);
    str.append(tmp);
    sprintf(tmp, "e_version   0x%08X\n", data.e_version);
    str.append(tmp);
    sprintf(tmp, "e_entry     0x%08X\n", data.e_entry);
    str.append(tmp);
    sprintf(tmp, "e_phoff     0x%08X\n", data.e_phoff);
    str.append(tmp);
    sprintf(tmp, "e_shoff     0x%08X\n", data.e_shoff);
    str.append(tmp);
    sprintf(tmp, "e_flags     0x%08X\n", data.e_flags);
    str.append(tmp);
    sprintf(tmp, "e_ehsize    0x%04X\n", data.e_ehsize);
    str.append(tmp);
    sprintf(tmp, "e_phentsize 0x%04X\n", data.e_phentsize);
    str.append(tmp);
    sprintf(tmp, "e_phnum     0x%04X\n", data.e_phnum);
    str.append(tmp);
    sprintf(tmp, "e_shentsize 0x%04X\n", data.e_shentsize);
    str.append(tmp);
    sprintf(tmp, "e_shnum     0x%04X\n", data.e_shnum);
    str.append(tmp);
    sprintf(tmp, "e_shstrndx  0x%04X\n", data.e_shstrndx);
    str.append(tmp);

    return str;
}

u32 Elf32Header::getE_magic() const { return data.e_magic; }

u8 Elf32Header::getE_class() const { return data.e_class; }

u8 Elf32Header::getE_data() const { return data.e_data; }

u8 Elf32Header::getE_idver() const { return data.e_idver; }

std::vector<u8> Elf32Header::getE_pad() const {
    std::vector<u8> pad(9);
    memcpy(&pad[0], &data.e_pad[0], 9);
    return pad;
}

u16 Elf32Header::getE_type() const { return data.e_type; }

u16 Elf32Header::getE_machine() const { return data.e_machine; }

u32 Elf32Header::getE_version() const { return data.e_version; }

u32 Elf32Header::getE_entry() const { return data.e_entry; }

u32 Elf32Header::getE_phoff() const { return data.e_phoff; }

u32 Elf32Header::getE_shoff() const { return data.e_shoff; }

u32 Elf32Header::getE_flags() const { return data.e_flags; }

u16 Elf32Header::getE_ehsize() const { return data.e_ehsize; }

u16 Elf32Header::getE_phentsize() const { return data.e_phentsize; }

u16 Elf32Header::getE_phnum() const { return data.e_phnum; }

u16 Elf32Header::getE_shentsize() { return data.e_shentsize; }

u16 Elf32Header::getE_shnum() const { return data.e_shnum; }

u16 Elf32Header::getE_shstrndx() const { return data.e_shstrndx; }

