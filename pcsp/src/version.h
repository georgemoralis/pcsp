#pragma once

#ifndef BUILDING_SPECIFIC_GAME_EMULATOR
//#ifdef _WIN32
//#include "svnrev.h"
//#else
#define SVN_REV_UNKNOWN
//#endif

#define SFY(x) #x
#define STRFY(x) SFY(x)

#define VERSION_BASE "0.5.5"
#define RELEASE_VERSION 1

#if RELEASE_VERSION
#	define VERSION VERSION_BASE
#else
#	ifdef SVN_REV_UNKNOWN
#		define VERSION VERSION_BASE "(svn)"
#	else
#		if SVN_MODS
#			define VERSION VERSION_BASE "(svn" STRFY(SVN_REV) "+mods)"
#		else
#			define VERSION VERSION_BASE "(svn" STRFY(SVN_REV) ")"
#		endif
#	endif
#endif
#endif
