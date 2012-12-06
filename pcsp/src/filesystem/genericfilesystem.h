#pragma once 

#include "common_base.h"

enum FileAccess
{
	FILEACCESS_NONE=0,
	FILEACCESS_READ=1,
	FILEACCESS_WRITE=2,
	FILEACCESS_READWRITE=3,
	FILEACCESS_APPEND=4,
	FILEACCESS_TRUNC=5,
	FILEACCESS_CREATE=8

};

enum FileMove
{
	FILEMOVE_BEGIN=0,
	FILEMOVE_CURRENT=1,
	FILEMOVE_END=2
};

enum FileType
{
	FILETYPE_NORMAL=1,
	FILETYPE_DIRECTORY=2
};

struct TimeStamp
{
	int  year;
	u8   month;
	u8   day;
	u8   hour;
	u8   minute;
	u8   second;
	u8   gmtOffset; // Offset from Greenwich Mean Time in number of 15 min intervals from -48 (West) to + 52 (East)

	TimeStamp() { year=0; month=0; day=0; hour=0; minute=0; second=0; gmtOffset=0; }
};

struct FileInfo
{
	std::string name; //[128+1];

	TimeStamp date;

	u32 lba; // for UMD
	u32 flags; // for UMD

	u32 access; //unix 777

	s64 size;

	FileType type;

    bool exists;

    FileInfo() {name="";size=0;access=0;type=FILETYPE_NORMAL;lba=0;flags=0;exists=true;}
};


class fs_GenericHandleAllocator 
{
public:
	virtual u32  RequestHandle()           = 0;
	virtual void ReleaseHandle(u32 handle) = 0;
};


//abstract class for filesystems
class fs_AbstractFileSystem
{
public:
	virtual u32                   OpenFile(std::string filename, FileAccess access)  = 0;
	virtual void                  CloseFile(u32 handle)                              = 0;
	virtual u32                   ReadFile(u32 handle, u8 *pointer, s64 size)        = 0;
	virtual u32                   WriteFile(u32 handle, const u8 *pointer, s64 size) = 0;
	virtual u32                   SeekFile(u32 handle, s64 position, FileMove type)  = 0;
	virtual void                  StatFile(u32 structaddress, FileInfo &info)        = 0;
	virtual bool                  OwnsHandle(u32 handle)                             = 0;
	virtual std::vector<FileInfo> GetDirListing(std::string path)                    = 0;
	virtual FileInfo              GetFileInfo(std::string filename)                  = 0;
};
