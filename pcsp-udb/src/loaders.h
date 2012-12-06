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

enum EmuFileType
{
    FILETYPE_ERROR,
    FILETYPE_PSP_PBP,
    FILETYPE_PSP_ELF,
    FILETYPE_PSP_ISO,
    FILETYPE_UNKNOWN
};



namespace loaders
{
    EmuFileType identify_file(const char *filename);
    void load_file(const char *filename);
    void load_image(const char *filename);
    void unload_image();
	extern u8 *icon0;
	extern u8 *psf;
	extern int icon0size;
	extern u8 *pic1;
	extern int pic1size;
    
}