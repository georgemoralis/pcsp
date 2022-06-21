/*
 *  19/06/2022 - synced with jpcsp 18/06/05/2022 - 7bebe7ff
 */
#pragma once

class SceModule;

namespace Emulator 
{

SceModule *load(const char *pspfilename, std::ifstream &f, bool fromSyscall, bool isSignChecked, u8 *key);
SceModule *load(const char *pspfilename, std::ifstream &f);
u32 getLoadAddress();

};
