////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#ifndef sceDeflt_h__
#define sceDeflt_h__

namespace sceDeflt
{
	extern bool Reboot();
	extern bool ShutDown();

	extern int sceZlibIsValid(); 
	extern int sceZlibGetInfo(); 
	extern int sceZlibGetCompressedData(); 
	extern int sceZlibDecompress(); 
	extern int sceGzipIsValid(); 
	extern int sceGzipGetName(); 
	extern int sceGzipGetInfo(); 
	extern int sceGzipGetCompressedData(); 
	extern int sceGzipGetComment(); 
	extern int sceGzipDecompress(); 
	extern int sceDeflateDecompress(); 
	extern int sceZlibAdler32(); 
}

#endif