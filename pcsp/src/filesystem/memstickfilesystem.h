#pragma once

#include "filesystem/genericfilesystem.h"

class fs_MemStickFileSystem : public fs_AbstractFileSystem
{
	struct OpenFileEntry
	{
		FILE *hFile;
	};
	
    typedef std::map<u32,OpenFileEntry> EntryMap;
	
    EntryMap                   entries;
	std::string                basePath;
	fs_GenericHandleAllocator *hAlloc;

	
public:
	fs_MemStickFileSystem(fs_GenericHandleAllocator *_hAlloc, std::string _basePath);

    u32                   OpenFile(std::string filename, FileAccess access);
	void                  CloseFile(u32 handle);
	u32                   ReadFile(u32 handle, u8 *pointer, s64 size);
	u32                   WriteFile(u32 handle, const u8 *pointer, s64 size);
	u32                   SeekFile(u32 handle, s64 position, FileMove type);
	void                  StatFile(u32 structaddress,FileInfo &info);
	std::vector<FileInfo> GetDirListing(std::string path);
	bool                  OwnsHandle(u32 handle);
	FileInfo              GetFileInfo(std::string filename);
};
 
