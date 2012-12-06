#include "elftypes.h"

class elf
{
protected:
	u8 *m_pElf;
	u32 m_iElfSize;
	void FreeMemory();//function to free all memory 
	/* Holds the elf header information */
	ElfHeader m_elfHeader;
	/* Pointer to the program headers */
	ElfProgram *m_pElfPrograms;
	/* Number of elf program headers */
	int m_iPHCount;
	/* List of sections */
	ElfSection *m_pElfSections;
	/* Number of elf section headers */
	int m_iSHCount;
	/* Pointer to the string table section */
	ElfSection *m_pElfStrtab;
	/* List of symbols */
	ElfSymbol *m_pElfSymbols;
	/* Number of symbols */
	int m_iSymCount;

	/* address to load*/
	u32 loadAddress;
	bool FillSection(ElfSection& elfSect, const Elf_Shdr *pSection);
	const char *GetSymbolName(u32 name, u32 shndx);
 public:
	/** Default constructor */
	elf();
	/** Virtual destructor */
	virtual ~elf();
	/** Load an ELF from a memory place */
	bool LoadFromMemory(const u8 *ptr,u32 size,u32 AddressToLoad);
	bool ElfValidateHeader();
	bool LoadPrograms();
	bool LoadSections();
	bool LoadSymbols();

		/** Find an elf section based on its name */
	ElfSection *ElfFindSection(const char* szName);
   //dump functions
	void ElfDumpHeader();
	void ElfDumpProgramHeader();
	void ElfDumpSections();
	void ElfDumpSymbols();
};

/* Do a safe alloc which should work on vc6 or latest gcc etc */
/* If alloc fails will always return NULL */
#ifdef _WIN32
#define SAFE_ALLOC(p, t) try { (p) = new t; } catch(...) { (p) = NULL; }
#else
#define SAFE_ALLOC(p, t) (p) = new t;
#endif
