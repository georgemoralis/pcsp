/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#pragma once

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
SceModule* LoadModule(std::string pspfilename, std::ifstream& f, u8* baseAddress, int mpidText, int mpidData,
                      bool analyzeOnly, bool allocMem, bool fromSyscall, bool isSignChecked, u8* key);

};
