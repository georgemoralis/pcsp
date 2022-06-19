/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff Completed!
 */
#pragma once

class Elf32 
{
   public:
    Elf32();
    Elf32(std::ifstream &f);
    ~Elf32();

    u32 getElfOffset() const;
    bool isKernelMode() const;

    Elf32Header &getHeader();
    std::vector<Elf32ProgramHeader> &getProgramHeaderList();
    Elf32ProgramHeader *getProgramHeader(u32 index);
    std::vector<Elf32SectionHeader> &getSectionHeaderList();
    Elf32SectionHeader *getSectionHeader(u32 index);
    Elf32SectionHeader *getSectionHeader(const std::string &name);

    std::string getElfInfo() const;
    std::string getProgInfo() const;
    std::string getSectInfo() const;

   private:
    void loadHeader(std::ifstream &f);
    void loadProgramHeaders(std::ifstream &f);
    void loadSectionHeaders(std::ifstream &f);

    // file offset
    u32 elfOffset;
    bool kernelMode;

    // headers
    Elf32Header header;
    std::vector<Elf32ProgramHeader> programHeaderList;
    std::vector<Elf32SectionHeader> sectionHeaderList;
    std::map<std::string, Elf32SectionHeader> sectionHeaderMap;
    Elf32SectionHeader *shstrtab;

    // debug info
    std::string ElfInfo;  // ELF header
    std::string ProgInfo;  // ELF program headers
    std::string SectInfo;  // ELF section headers
};
