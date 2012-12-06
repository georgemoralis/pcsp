
#ifndef __ELF_TYPES_H__
#define __ELF_TYPES_H__

/* Structure to hold elf header data, in native format */
struct ElfHeader
{
	u32 iMagic;
	u32 iClass;
	u32 iData;
	u32 iIdver;
	u32 iType; 
	u32 iMachine; 
	u32 iVersion; 
	u32 iEntry; 
	u32 iPhoff; 
	u32 iShoff; 
	u32 iFlags; 
	u32 iEhsize;
	u32 iPhentsize; 
	u32 iPhnum; 
	u32 iShentsize; 
	u32 iShnum; 
	u32 iShstrndx; 
};
struct ElfProgram
{
	u32 iType;
	u32 iOffset;
	u32 iVaddr;
	u32 iPaddr;
	u32 iFilesz;
	u32 iMemsz;
	u32 iFlags;
	u32 iAlign;

	/* Aliased pointer to the data (in the original Elf)*/
	u8  *pData;
};


/* ELF file header */
typedef struct { 
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
}  Elf_Ehdr;

typedef struct { 
	u32 p_type; 
	u32 p_offset; 
	u32 p_vaddr; 
	u32 p_paddr; 
	u32 p_filesz; 
	u32 p_memsz; 
	u32 p_flags; 
	u32 p_align; 
} Elf_Phdr;

#define ELF_MAGIC	0x464C457F
#define ELF_SECT_MAX_NAME 128

/* Structure defining a single elf section */
struct ElfSection
{
	/* Name index */
	u32 iName;
	/* Type of section */
	u32 iType;
	/* Section flags */
	u32 iFlags;
	/* Addr of section when loaded */
	u32 iAddr;
	/* Offset of the section in the elf */
	u32 iOffset;
	/* Size of the sections data */
	u32 iSize;
	/* Link info */
	u32 iLink;
	/* Info */
	u32 iInfo;
	/* Address alignment */
	u32 iAddralign;
	/* Entry size */
	u32 iEntsize;
	/* Aliased pointer to the data (in the original Elf) */
	u8 *pData;
	/* Name of the section */
	char szName[ELF_SECT_MAX_NAME];
	/* Pointer to the head of the relocs (if any) */
	struct ElfReloc *pRelocs;
	/* Number of relocs for this section */
	u32 iRelocCount;
};

/* ELF section header */
typedef struct { 
	u32 sh_name; 
	u32 sh_type; 
	u32 sh_flags; 
	u32 sh_addr; 
	u32 sh_offset; 
	u32 sh_size; 
	u32 sh_link; 
	u32 sh_info; 
	u32 sh_addralign; 
	u32 sh_entsize; 
}  Elf_Shdr;

#define ELF_MIPS_TYPE 0x0002
#define ELF_PRX_TYPE  0xFFA0

#define SHT_NULL 0 
#define SHT_PROGBITS 1 
#define SHT_SYMTAB 2 
#define SHT_STRTAB 3 
#define SHT_RELA 4 
#define SHT_HASH 5 
#define SHT_DYNAMIC 6 
#define SHT_NOTE 7 
#define SHT_NOBITS 8 
#define SHT_REL 9 
#define SHT_SHLIB 10 
#define SHT_DYNSYM 11 
#define SHT_LOPROC 0x70000000 
//#define SHT_HIPROC 0x7fffffff 
//#define SHT_LOUSER 0x80000000 
//#define SHT_HIUSER 0xffffffff

struct ElfSymbol
{
	const char *symname;
	u32 name;
	u32 value;
	u32 size;
	u32 info;
	u32 other;
	u32 shndx;
};
typedef struct { 
	u32 st_name; 
	u32 st_value; 
	u32 st_size; 
	unsigned char st_info; 
	unsigned char st_other; 
	u16 st_shndx; 
} Elf_Sym;

#if 0


struct ElfReloc
{
	/* Pointer to the section name */
	const char* secname;
	/* Base address */
	u32 base;
	/* Type */
	u32 type;
	/* Symbol (if known) */
	u32 symbol;
	/* Offset into the file */
	u32 offset;
	/* New Address for the relocation (to do with what you will) */
	u32 info;
	u32 addr;
};



/* Define ELF types */
typedef u32 Elf32_Addr; 
typedef u16 Elf32_Half;
typedef u32 Elf32_Off;
typedef s32 Elf32_Sword;
typedef u32 Elf32_Word;





#define SHT_PRXRELOC (SHT_LOPROC | 0xA0)

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

#define PT_PRXRELOC             0x700000A0
#define PT_PRXRELOC2            0x700000A1







#define ELF32_R_SYM(i) ((i)>>8) 
#define ELF32_R_TYPE(i) ((u8)(i&0xFF))

typedef struct { 
	Elf32_Addr r_offset; 
	Elf32_Word r_info; 
} Elf32_Rel;

#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define STT_FILE 4
#define STT_LOPROC 13
#define STT_HIPROC 15


#endif
#endif
