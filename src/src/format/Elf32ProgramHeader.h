/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff Completed!
 */
#pragma once

enum Elf32ProgramFlags {
    PF_X = (1 << 0), /* Segment is executable */
    PF_W = (1 << 1), /* Segment is writable */
    PF_R = (1 << 2) /* Segment is readable */
};

class Elf32ProgramHeader 
{
   public:
    Elf32ProgramHeader();
    Elf32ProgramHeader(std::ifstream &f);
    ~Elf32ProgramHeader();

    void read(std::ifstream &f);

    static const size_t sizeOf();
    std::string toString() const;

    u32 getP_type() const;
    u32 getP_offset() const;
    u32 getP_vaddr() const;
    u32 getP_paddr() const;
    u32 getP_filesz() const;
    u32 getP_memsz() const;
    u32 getP_flags() const;
    u32 getP_align() const;
   private:
    struct {
        u32 p_type;
        u32 p_offset;
        u32 p_vaddr;
        u32 p_paddr;
        u32 p_filesz;
        u32 p_memsz;
        // Bits:
        // 0x1 = executable
        // 0x2 = writable
        // 0x4 = readable
        // demo PRX's were found to be not writable
        u32 p_flags;
        u32 p_align;
    } data;

};
