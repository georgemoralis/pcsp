/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once


#ifdef _WIN32
#include "svnrev.h"
#else
#define SVN_REV_UNKNOWN
#endif

#define SFY(x) #x
#define STRFY(x) SFY(x)




#if RELEASE_VERSION
#	define VERSION VERSION_BASE
#else
#	ifdef SVN_REV_UNKNOWN
#		define VERSION  "(svn)"
#	else
#		if SVN_MODS
#			define VERSION "(svn" STRFY(SVN_REV) "+mods)"
#		else
#			define VERSION "(svn" STRFY(SVN_REV) ")"
#		endif
#	endif
#endif

