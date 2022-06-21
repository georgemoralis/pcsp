/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff  - Small TODO requires
 */
#include "..\PCSPCommon.h"
#include "Elf32SectionHeader.h"

const size_t Elf32SectionHeader::sizeOf() { return 40; }

Elf32SectionHeader::Elf32SectionHeader() {}

Elf32SectionHeader::Elf32SectionHeader(std::ifstream &f) { f.read((char *)&data, sizeof(data)); }

Elf32SectionHeader::~Elf32SectionHeader() {}

std::string Elf32SectionHeader::toString() const {
    std::string str;
    char tmp[128];

    sprintf(tmp, "sh_name      %08X\n", data.sh_name);
    str.append(tmp);
    /*TODO*/  //        if (sh_namez != null && sh_namez.length() > 0) {
    /*TODO*/  //        	str.append("sh_namez \t '" + sh_namez + "'\n");
    /*TODO*/  //        }
    sprintf(tmp, "sh_type      %08X\n", data.sh_type);
    str.append(tmp);
    sprintf(tmp, "sh_flags     %08X\n", data.sh_flags);
    str.append(tmp);
    sprintf(tmp, "sh_addr      %08X\n", data.sh_addr);
    str.append(tmp);
    sprintf(tmp, "sh_offset    %08X\n", data.sh_offset);
    str.append(tmp);
    sprintf(tmp, "sh_size      %08X\n", data.sh_size);
    str.append(tmp);
    sprintf(tmp, "sh_link      %08X\n", data.sh_link);
    str.append(tmp);
    sprintf(tmp, "sh_info      %08X\n", data.sh_info);
    str.append(tmp);
    sprintf(tmp, "sh_addralign %08X\n", data.sh_addralign);
    str.append(tmp);
    sprintf(tmp, "sh_entsize   %08X\n", data.sh_entsize);
    str.append(tmp);

    return str;
}

std::string Elf32SectionHeader::getSh_namez() const { return sh_namez; }

void Elf32SectionHeader::setSh_namez(const std::string &namez) { sh_namez = namez; }

u32 Elf32SectionHeader::getSh_name() const { return data.sh_name; }

u32 Elf32SectionHeader::getSh_type() const { return data.sh_type; }

u32 Elf32SectionHeader::getSh_flags() const { return data.sh_flags; }

u32 Elf32SectionHeader::getSh_addr() const { return data.sh_addr; }

/*TODO*/  //
/*TODO*/  //    public int getSh_addr(TPointer baseAddress) {
/*TODO*/  //    	return getSh_addr(baseAddress.getAddress());
/*TODO*/  //    }
/*TODO*/  //
u32 Elf32SectionHeader::getSh_addr(u32 baseAddress) const {
    /*TODO*/  //    	if (Memory.isAddressGood(getSh_addr()) && getSh_addr() >= baseAddress) {
/*TODO*/  //    		return getSh_addr();
/*TODO*/  //    	}
    	return baseAddress + getSh_addr();
}

u32 Elf32SectionHeader::getSh_offset() const { return data.sh_offset; }

u32 Elf32SectionHeader::getSh_size() const { return data.sh_size; }

u32 Elf32SectionHeader::getSh_link() const { return data.sh_link; }

u32 Elf32SectionHeader::getSh_info() const { return data.sh_info; }

u32 Elf32SectionHeader::getSh_addralign() const { return data.sh_addralign; }

u32 Elf32SectionHeader::getSh_entsize() const { return data.sh_entsize; }

