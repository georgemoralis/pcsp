#include "stdafx.h"
#include "memorystick.h"

namespace mem_stick
{
   u32 state;
   u32 freesize;
   u32 sectorsize;

   void init()
   {
	   state=SCE_MEMSTICK_INSERTED;
	   freesize = BASE_FREE_SIZE;
	   sectorsize=BASE_SECTOR_SIZE;
   }

	u32 getState() 
	{
		return state;
	}

	void setState(u32 state) 
	{
		state = state;
	}

	u32 getFreeSize() 
	{
		return freesize;
	}

	u32 getFreeSizeKb() 
	{
		return (u32)((freesize+1023) / 1024);
	}

    void setFreeSize(u32 freesize)
	{
		freesize = freesize;
	}

	u32 getSectorSize() 
	{
		return sectorsize;
	}

	u32 getSectorSizeKb() 
	{
		return ((sectorsize+1023) / 1024);
	}

	u32 getSize32Kb(u32 sizeKb) 
	{
		return ((sizeKb + 31) & ~31);
	}

	QString getSizeKbString(u32 sizeKb) 
	{
		if (sizeKb < 1024) {
			return QString("%1 KB").arg(sizeKb);
		}                  
		sizeKb /= 1024;
		if (sizeKb < 1024) {
			return QString("%1 MB").arg(sizeKb);
		}
		sizeKb /= 1024;
		return QString("%1 GB").arg(sizeKb);
	}

}
