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
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "Loaders.h"
#include "UmdImageLoader.h"
#include "isodrv.h"
#include "isolib.h"
#include "psf.h"
//
u8 *loaders::icon0;
int loaders::icon0size;
u8 *loaders::psf;
u8 *loaders::pic1;
int loaders::pic1size;
EmuFileType loaders::identify_file(const char *filename)
{
    FILE *f = ::fopen(filename, "rb");
    if (!f)
    {
        //File does not exists
        return FILETYPE_ERROR;
    }
    if (!!::strstr(filename,".iso") || !!::strstr(filename,".ISO"))
    {
        return FILETYPE_PSP_ISO;
    }
    else if (!!::strstr(filename,".cso") || !!::strstr(filename,".CSO"))
    {
        return FILETYPE_PSP_ISO;
    }
    else
    {
        return FILETYPE_UNKNOWN;
    }
}

void loaders::load_file(const char *filename)
{
    switch (identify_file(filename)) 
    {
    case FILETYPE_PSP_ISO:
        load_image(filename);
        break;
    }
}


void loaders::load_image(const char *filename)
{
    umdimageloader::reboot(filename);
    int f;
    icon0 = new u8[ISOFS_getfilesize("PSP_GAME/ICON0.PNG")];
    f=ISOFS_open("PSP_GAME/ICON0.PNG", 1);
	icon0size =ISOFS_getfilesize("PSP_GAME/ICON0.PNG");
	ISOFS_read(f, (char*)icon0,icon0size );
    ISOFS_close(f);

    pic1 = new u8[ISOFS_getfilesize("PSP_GAME/PIC1.PNG")];
    f=ISOFS_open("PSP_GAME/PIC1.PNG", 1);
	pic1size =ISOFS_getfilesize("PSP_GAME/PIC1.PNG");
	ISOFS_read(f, (char*)pic1,pic1size );
    ISOFS_close(f);	


   
}

void loaders::unload_image()
{
    umdimageloader::shutdown();
}



