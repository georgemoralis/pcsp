/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff - Small TODO requires
 */
#include "..\PCSPCommon.h"
#include "Elf32Header.h"
#include "Elf32ProgramHeader.h"
#include "Elf32SectionHeader.h"
#include "Elf32.h"

Elf32::Elf32() : shstrtab(NULL) {}

Elf32::Elf32(std::ifstream &f) : shstrtab(NULL) {
    elfOffset = f.tellg();
    kernelMode = false;
    loadHeader(f);
    if (header.isValid()) {
        loadProgramHeaders(f);
        loadSectionHeaders(f);
    }
}

Elf32::~Elf32() {}

void Elf32::loadHeader(std::ifstream &f) {
    header = Elf32Header(f);
    ElfInfo = header.toString();
}

void Elf32::loadProgramHeaders(std::ifstream &f) {
    programHeaderList.clear();
    ProgInfo.clear();

    for (u16 i = 0; i < header.getE_phnum(); ++i) {
        f.seekg(elfOffset + header.getE_phoff() + (i * header.getE_phentsize()));
        Elf32ProgramHeader phdr(f);

        // save loaded header
        programHeaderList.push_back(phdr);

        // construct ELF program header info for debugger
        char tmp[128];
        sprintf(tmp, "-----PROGRAM HEADER #%02d-----\n", i);
        ProgInfo.append(tmp);
        ProgInfo.append(phdr.toString());

        // yapspd: If the PRX file is a kernel module then the most significant
        // bit must be set in the physical address of the first program header.
        if (i == 0 && (phdr.getP_paddr() & 0x80000000) != 0) {
            kernelMode = true;
/*TODO*/  //           Emulator::log.debug("Kernel mode PRX detected");
        }
    }
}

void Elf32::loadSectionHeaders(std::ifstream &f) {
    sectionHeaderList.clear();
    sectionHeaderMap.clear();

    // 1st pass
    // - save headers
    // - find .shstrtab
    for (u16 i = 0; i < header.getE_shnum(); ++i) {
        f.seekg(elfOffset + header.getE_shoff() + (i * header.getE_shentsize()));
        Elf32SectionHeader shdr(f);

        // save loaded header
        sectionHeaderList.push_back(shdr);

        // find the .shstrtab section
        if (shdr.getSh_type() == SHT_STRTAB &&  // 0x00000003
            shstrtab == NULL &&
            // Some programs have 2 STRTAB headers,
            // the header with size 1 has to be ignored.
            shdr.getSh_size() > 1) {
            shstrtab = &sectionHeaderList[i];
        }
    }
    if (shstrtab == NULL) {
/*TODO*/  //        Emulator::log.warn(".shstrtab section not found");
        return;
    }
    // 2nd pass
    // - Construct ELF section header info for debugger
    for (int i = 0; i < sectionHeaderList.size(); ++i) {
        Elf32SectionHeader &shdr = sectionHeaderList[i];
        f.seekg(elfOffset + shstrtab->getSh_offset() + shdr.getSh_name());

        // number the section
        char tmp[128];
        sprintf(tmp, "-----SECTION HEADER #%02d-----\n", i);
        SectInfo.append(tmp);

        std::string SectionName;
        char c;
        f.read(&c, 1);
        while (c != 0) {
            SectionName.append(&c, 0, 1);
            f.read(&c, 1);
        }

        if (SectionName.length() > 0) {
            shdr.setSh_namez(SectionName);
            SectInfo.append(SectionName);
            SectInfo.append("\n");
            sectionHeaderMap[SectionName] = shdr;
        }

        // add this section header's info
        SectInfo.append(shdr.toString());
    }
}
/** @return The elf was loaded from some kind of file or buffer. The elf
 * offset is an offset into this buffer where the elf actually starts. If
 * the returned offset is non-zero this is typically due to the elf being
 * embedded inside a pbp. */
u32 Elf32::getElfOffset() const { return elfOffset; }

Elf32Header &Elf32::getHeader() { return header; }

std::vector<Elf32ProgramHeader> &Elf32::getProgramHeaderList() { return programHeaderList; }

Elf32ProgramHeader *Elf32::getProgramHeader(u32 index) {
    if (index < 0 || index >= programHeaderList.size())
        return NULL;
    else
        return &programHeaderList[index];
}

std::vector<Elf32SectionHeader> &Elf32::getSectionHeaderList() { return sectionHeaderList; }

Elf32SectionHeader *Elf32::getSectionHeader(u32 index) {
    if (index < 0 || index >= sectionHeaderList.size())
        return NULL;
    else
        return &sectionHeaderList[index];
}

Elf32SectionHeader *Elf32::getSectionHeader(const std::string &name) {
    std::map<std::string, Elf32SectionHeader>::iterator it = sectionHeaderMap.find(name);
    if (it == sectionHeaderMap.end())
        return NULL;
    else
        return &it->second;
}

 std::string Elf32::getElfInfo() const { return ElfInfo; }

 std::string Elf32::getProgInfo() const { return ProgInfo; }

 std::string Elf32::getSectInfo() const { return SectInfo; }

 bool Elf32::isKernelMode() const { return kernelMode; }

