////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "sceDeflt.h"
#include "hle/types.h"
#include "log.h"

namespace sceDeflt
{
	static bool sceDeflt_ready = false;

	bool Reboot()
	{
		ShutDown();
		sceDeflt_ready = true;
		return true;
	}
	bool ShutDown()
	{
		if (sceDeflt_ready)
		{
			sceDeflt_ready = false;	
		}
		return true;
	}

	int sceZlibIsValid()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceZlibIsValid function");
		return 0;
	}
	int sceZlibGetInfo()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceZlibGetInfo function");
		return 0;
	}
	int sceZlibGetCompressedData()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceZlibGetCompressedData function");
		return 0;
	}
	int sceZlibDecompress()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceZlibDecompress function");
		return 0;
	}
	int sceGzipIsValid()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceGzipIsValid function");
		return 0;
	}
	int sceGzipGetName()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceGzipGetName function");
		return 0;
	}
	int sceGzipGetInfo()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceGzipGetInfo function");
		return 0;
	}
	int sceGzipGetCompressedData()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceGzipGetCompressedData function");
		return 0;
	}
	int sceGzipGetComment()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceGzipGetComment function");
		return 0;
	}
	int sceGzipDecompress()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceGzipDecompress function");
		return 0;
	}
	int sceDeflateDecompress()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceDeflateDecompress function");
		return 0;
	}
	int sceZlibAdler32()
	{
		//TODO implement me
		errorf(sceDeflt,"UNIMPLEMENTED sceZlibAdler32 function");
		return 0;
	}
}
namespace syscalls
{
	void sceZlibIsValid(AlContext &context){ V0 = sceDeflt::sceZlibIsValid();};
	void sceZlibGetInfo(AlContext &context){ V0 = sceDeflt::sceZlibGetInfo();};
	void sceZlibGetCompressedData(AlContext &context){ V0 = sceDeflt::sceZlibGetCompressedData();};
	void sceZlibDecompress(AlContext &context){ V0 = sceDeflt::sceZlibDecompress();};
	void sceGzipIsValid(AlContext &context){ V0 = sceDeflt::sceGzipIsValid();};
	void sceGzipGetName(AlContext &context){ V0 = sceDeflt::sceGzipGetName();};
	void sceGzipGetInfo(AlContext &context){ V0 = sceDeflt::sceGzipGetInfo();};
	void sceGzipGetCompressedData(AlContext &context){ V0 = sceDeflt::sceGzipGetCompressedData();};
	void sceGzipGetComment(AlContext &context){ V0 = sceDeflt::sceGzipGetComment();};
	void sceGzipDecompress(AlContext &context){ V0 = sceDeflt::sceGzipDecompress();};
	void sceDeflateDecompress(AlContext &context){ V0 = sceDeflt::sceDeflateDecompress();};
	void sceZlibAdler32(AlContext &context){ V0 = sceDeflt::sceZlibAdler32();};
}
