#define SCE_MEMSTICK_INSERTED  1
#define SCE_MEMSTICK_EJECTED   2
#define SCE_MEMSTICK_INSERTING 4

namespace mem_stick
{
    void init();
	static const u32 BASE_FREE_SIZE = 1 * 1024 * 1024 * 1024;     // 1GB      
	static const u32 BASE_SECTOR_SIZE = 32 * 1024;                 // 32KB
	u32 getState();
	void setState(u32 state);
	u32 getFreeSize();
	u32 getFreeSizeKb();
	void setFreeSize(u32 freesize);
	u32 getSectorSize();
	u32 getSectorSizeKb();
	u32 getSize32Kb(u32 sizeKb);
	QString getSizeKbString(u32 sizeKb);

};

