#ifndef kernel_elf_h__
#define kernel_elf_h__

/* Define ELF types */
typedef u32 Elf32_Addr; 
typedef u16 Elf32_Half;
typedef u32 Elf32_Off;
typedef s32 Elf32_Sword;
typedef u32 Elf32_Word;

#define ELF_MAGIC       0x464C457F

#define ELF_MIPS_TYPE   0x0002
#define ELF_PRX_TYPE    0xFFA0

#define SHT_NULL        0 
#define SHT_PROGBITS    1 
#define SHT_SYMTAB      2 
#define SHT_STRTAB      3 
#define SHT_RELA        4 
#define SHT_HASH        5 
#define SHT_DYNAMIC     6 
#define SHT_NOTE        7 
#define SHT_NOBITS      8 
#define SHT_REL         9 
#define SHT_SHLIB       10 
#define SHT_DYNSYM      11 
#define SHT_LOPROC      0x70000000 
#define SHT_HIPROC      0x7fffffff 
#define SHT_LOUSER      0x80000000 
#define SHT_HIUSER      0xffffffff

#define SHT_PRXRELOC    (SHT_LOPROC | 0xA0)

// MIPS Reloc Entry Types
#define R_MIPS_NONE     0
#define R_MIPS_16       1
#define R_MIPS_32       2
#define R_MIPS_26       4
#define R_MIPS_HI16     5
#define R_MIPS_LO16     6

/* Unsupported for PRXes (loadcore.prx ignores them) */
#define R_MIPS_REL32    3
#define R_MIPS_GPREL16  7
#define R_MIPS_LITERAL  8
#define R_MIPS_GOT16    9
#define R_MIPS_PC16     10
#define R_MIPS_CALL16   11
#define R_MIPS_GPREL32  12

/* For the new relocation type */
#define R_MIPS_X_HI16   13
#define R_MIPS_X_J26    14
#define R_MIPS_X_JAL26  15


#define SHF_WRITE 		1
#define SHF_ALLOC 		2
#define SHF_EXECINSTR 	4

#define PT_NULL 		0
#define PT_LOAD 		1
#define PT_DYNAMIC 		2
#define PT_INTERP 		3
#define PT_NOTE 		4
#define PT_SHLIB 		5
#define PT_PHDR 		6
#define PT_LOPROC 		0x70000000
#define PT_HIPROC 		0x7fffffff

#define PT_PRXRELOC     0x700000A0
#define PT_PRXRELOC2    0x700000A1

#define ELF32_R_SYM(i)      ((i)>>8) 
#define ELF32_R_TYPE(i)     ((u8)(i&0xFF))

#define ELF32_ST_BIND(i)    ((i)>>4)
#define ELF32_ST_TYPE(i)    ((i)&0xf)
#define ELF32_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))

#define STT_NOTYPE      0
#define STT_OBJECT      1
#define STT_FUNC        2
#define STT_SECTION     3
#define STT_FILE        4
#define STT_LOPROC      13
#define STT_HIPROC      15


#ifndef __GNUC__
#pragma pack(push, 1)
#define PACKED_STRUCT(c) c
#else
#define PACKED_STRUCT(c) __attribute__((packed)) c
#endif

/* ELF file header */
typedef struct
{
    Elf32_Word          e_magic;
    u8                  e_class;
    u8                  e_data;
    u8                  e_idver;
    u8                  e_pad[9];
    Elf32_Half          e_type; 
    Elf32_Half          e_machine; 
    Elf32_Word          e_version; 
    Elf32_Addr          e_entry; 
    Elf32_Off           e_phoff; 
    Elf32_Off           e_shoff; 
    Elf32_Word          e_flags; 
    Elf32_Half          e_ehsize; 
    Elf32_Half          e_phentsize; 
    Elf32_Half          e_phnum; 
    Elf32_Half          e_shentsize; 
    Elf32_Half          e_shnum; 
    Elf32_Half          e_shstrndx; 
} PACKED_STRUCT(Elf32_Ehdr);

/* ELF section header */
typedef struct
{ 
    Elf32_Word          sh_name; 
    Elf32_Word          sh_type; 
    Elf32_Word          sh_flags; 
    Elf32_Addr          sh_addr; 
    Elf32_Off           sh_offset; 
    Elf32_Word          sh_size; 
    Elf32_Word          sh_link; 
    Elf32_Word          sh_info; 
    Elf32_Word          sh_addralign; 
    Elf32_Word          sh_entsize; 
} PACKED_STRUCT(Elf32_Shdr);

typedef struct
{ 
    Elf32_Word          p_type; 
    Elf32_Off           p_offset; 
    Elf32_Addr          p_vaddr; 
    Elf32_Addr          p_paddr; 
    Elf32_Word          p_filesz; 
    Elf32_Word          p_memsz; 
    Elf32_Word          p_flags; 
    Elf32_Word          p_align; 
} PACKED_STRUCT(Elf32_Phdr);

typedef struct
{ 
    Elf32_Addr          r_offset; 
    Elf32_Word          r_info; 
} PACKED_STRUCT(Elf32_Rel);

typedef struct
{ 
    Elf32_Word          st_name; 
    Elf32_Addr          st_value; 
    Elf32_Word          st_size; 
    u8                  st_info; 
    u8                  st_other; 
    Elf32_Half          st_shndx; 
} PACKED_STRUCT(Elf32_Sym);

#ifndef __GNUC__
#pragma pack(pop)
#endif
#undef PACKED_STRUCT

#endif // kernel_elf_h__
