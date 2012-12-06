////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "sceFont.h"
#include "hle/types.h"
#include "log.h"

namespace sceLibFont
{
	static bool sceFont_ready = false;

	bool Reboot()
	{
		ShutDown();
		sceFont_ready = true;
		return true;
	}
	bool ShutDown()
	{
		if (sceFont_ready)
		{
			sceFont_ready = false;		
		}
		return true;
	}

	int sceFontPixelToPointVFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontPixelToPointVFunction function");
		return 0;
	}
	int sceFontPixelToPointHFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontPixelToPointHFunction function");
		return 0;
	}
	int sceFontPointToPixelVFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontPointToPixelVFunction function");
		return 0;
	}
	int sceFontFindFontFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontFindFontFunction function");
		return 0;
	}
	int sceFontOpenUserFileFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontOpenUserFileFunction function");
		return 0;
	}
	int sceFontFlushFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontFlushFunction function");
		return 0;
	}
	int sceFontSetResolutionFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontSetResolutionFunction function");
		return 0;
	}
	int sceFontGetFontInfoByIndexNumberFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetFontInfoByIndexNumberFunction function");
		return 0;
	}
	int sceFontPointToPixelHFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontPointToPixelHFunction function");
		return 0;
	}
	int sceFontGetCharImageRectFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetCharImageRectFunction function");
		return 0;
	}
	int sceFontSetAltCharacterCodeFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontSetAltCharacterCodeFunction function");
		return 0;
	}
	int sceFontOpenUserMemoryFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontOpenUserMemoryFunction function");
		return 0;
	}
	int sceFontGetFontListFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetFontListFunction function");
		return 0;
	}
	int sceFontGetNumFontListFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetNumFontListFunction function");
		return 0;
	}
	int sceFontGetCharGlyphImageFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetCharGlyphImageFunction function");
		return 0;
	}
	int sceFontGetCharInfoFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetCharInfoFunction function");
		return 0;
	}
	int sceFontGetCharGlyphImage_ClipFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetCharGlyphImage_ClipFunction function");
		return 0;
	}
	int sceFontOpenFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontOpenFunction function");
		return 0;
	}
	int sceFontNewLibFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontNewLibFunction function");
		return 0;
	}
	int sceFontDoneLibFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontDoneLibFunction function");
		return 0;
	}
	int sceFontCloseFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontCloseFunction function");
		return 0;
	}
	int sceFontGetFontInfoFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontGetFontInfoFunction function");
		return 0;
	}
	int sceFontFindOptimumFontFunction()
	{
		//TODO implement me
		errorf(sceFont,"UNIMPLEMENTED sceFontFindOptimumFontFunction function");
		return 0;
	}
}
namespace syscalls
{
	void sceFontPixelToPointVFunction(AlContext &context)           { V0 = sceLibFont::sceFontPixelToPointVFunction();};
	void sceFontPixelToPointHFunction(AlContext &context)           { V0 = sceLibFont::sceFontPixelToPointHFunction();};
	void sceFontPointToPixelVFunction(AlContext &context)           { V0 = sceLibFont::sceFontPointToPixelVFunction();};
	void sceFontFindFontFunction(AlContext &context)	            { V0 = sceLibFont::sceFontFindFontFunction();};
	void sceFontOpenUserFileFunction(AlContext &context)            { V0 = sceLibFont::sceFontOpenUserFileFunction();};
	void sceFontFlushFunction(AlContext &context)	                { V0 = sceLibFont::sceFontFlushFunction();};
	void sceFontSetResolutionFunction(AlContext &context)           { V0 = sceLibFont::sceFontSetResolutionFunction();};
	void sceFontGetFontInfoByIndexNumberFunction(AlContext &context){ V0 = sceLibFont::sceFontGetFontInfoByIndexNumberFunction();};
	void sceFontPointToPixelHFunction(AlContext &context)           { V0 = sceLibFont::sceFontPointToPixelHFunction();};
	void sceFontGetCharImageRectFunction(AlContext &context)        { V0 = sceLibFont::sceFontGetCharImageRectFunction();};
	void sceFontSetAltCharacterCodeFunction(AlContext &context)     { V0 = sceLibFont::sceFontSetAltCharacterCodeFunction();};
	void sceFontOpenUserMemoryFunction(AlContext &context)          { V0 = sceLibFont::sceFontOpenUserMemoryFunction();};
	void sceFontGetFontListFunction(AlContext &context)             { V0 = sceLibFont::sceFontGetFontListFunction();};
	void sceFontGetNumFontListFunction(AlContext &context)          { V0 = sceLibFont::sceFontGetNumFontListFunction();};
	void sceFontGetCharGlyphImageFunction(AlContext &context)       { V0 = sceLibFont::sceFontGetCharGlyphImageFunction();};
	void sceFontGetCharInfoFunction(AlContext &context)             { V0 = sceLibFont::sceFontGetCharInfoFunction();};
	void sceFontGetCharGlyphImage_ClipFunction(AlContext &context)  { V0 = sceLibFont::sceFontGetCharGlyphImage_ClipFunction();};
	void sceFontOpenFunction(AlContext &context)                    { V0 = sceLibFont::sceFontOpenFunction();};
	void sceFontNewLibFunction(AlContext &context)                  { V0 = sceLibFont::sceFontNewLibFunction();};
	void sceFontDoneLibFunction(AlContext &context)                 { V0 = sceLibFont::sceFontDoneLibFunction();};
	void sceFontCloseFunction(AlContext &context)                   { V0 = sceLibFont::sceFontCloseFunction();};
	void sceFontGetFontInfoFunction(AlContext &context)             { V0 = sceLibFont::sceFontGetFontInfoFunction();};
	void sceFontFindOptimumFontFunction(AlContext &context)         { V0 = sceLibFont::sceFontFindOptimumFontFunction();};
}
