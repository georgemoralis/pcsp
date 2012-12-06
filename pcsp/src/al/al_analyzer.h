#ifndef __allegrex_analyzer_h__
#define __allegrex_analyzer_h__

#undef IDEF
#define IDEF(nam, fmt, msk, sig, inf) u64 AllegrexInstructionTemplate< sig, msk >::Infos() { using namespace Allegrex; return inf; }
#include "al.def"

#endif // __allegrex_analyzer_h__
