/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#pragma once

class Elf32;

enum Format { // Format bits
    FORMAT_UNKNOWN = 0x00,
    FORMAT_ELF = 0x01,
    FORMAT_PRX = 0x02,
    FORMAT_PBP = 0x04,
    FORMAT_SCE = 0x08,
    FORMAT_PSP = 0x10
};

namespace Loader 
{
SceModule* LoadModule(std::string pspfilename, std::ifstream& f, u32& baseAddress, int mpidText, int mpidData,
                      bool analyzeOnly, bool allocMem, bool fromSyscall, bool isSignChecked, u8* key);
bool LoadPBP(std::ifstream& f, SceModule* _module, u32& baseAddress, bool analyzeOnly, bool allocMem, bool fromSyscall);
bool LoadELF(std::ifstream& f, SceModule* _module, u32& baseAddress, u32 fileSize,bool analyzeOnly, bool allocMem,
             bool fromSyscall);
void LoadELFProgram(std::ifstream& f, SceModule* _module, u32& baseAddress, Elf32& elf, u32 elfOffset,
                                  u32 fileSize, bool analyzeOnly);
};
