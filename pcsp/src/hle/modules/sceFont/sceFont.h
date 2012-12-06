////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#ifndef sceFont_h__
#define sceFont_h__

namespace sceLibFont
{
	extern bool Reboot();
	extern bool ShutDown();

	extern int sceFontPixelToPointVFunction(); 
	extern int sceFontPixelToPointHFunction(); 
	extern int sceFontPointToPixelVFunction(); 
	extern int sceFontFindFontFunction(); 
	extern int sceFontOpenUserFileFunction(); 
	extern int sceFontFlushFunction(); 
	extern int sceFontSetResolutionFunction(); 
	extern int sceFontGetFontInfoByIndexNumberFunction(); 
	extern int sceFontPointToPixelHFunction(); 
	extern int sceFontGetCharImageRectFunction(); 
	extern int sceFontSetAltCharacterCodeFunction(); 
	extern int sceFontOpenUserMemoryFunction(); 
	extern int sceFontGetFontListFunction(); 
	extern int sceFontGetNumFontListFunction(); 
	extern int sceFontGetCharGlyphImageFunction(); 
	extern int sceFontGetCharInfoFunction(); 
	extern int sceFontGetCharGlyphImage_ClipFunction(); 
	extern int sceFontOpenFunction(); 
	extern int sceFontNewLibFunction(); 
	extern int sceFontDoneLibFunction(); 
	extern int sceFontCloseFunction(); 
	extern int sceFontGetFontInfoFunction(); 
	extern int sceFontFindOptimumFontFunction(); 
}

#endif