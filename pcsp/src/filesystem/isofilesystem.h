#pragma once
#include "filesystem/genericfilesystem.h"

#include "filesystem/iso/IsoFS.h"

class fs_ISOFileSystem : public fs_AbstractFileSystem
{
    typedef std::map<u32,IsoFile> EntryMap;

    fs_IsoDirectory         rootDir;
	fs_BlockDevice         *source;
	EntryMap                entries;
	std::string             basePath;
	fs_GenericHandleAllocator *hAlloc;

public:
	fs_ISOFileSystem(fs_GenericHandleAllocator *_hAlloc, fs_BlockDevice* _source);
	~fs_ISOFileSystem(void);

	u32                   OpenFile(std::string filename, FileAccess access);
	void                  CloseFile(u32 handle);
	u32                   ReadFile(u32 handle, u8 *pointer, s64 size);
	u32                   WriteFile(u32 handle, const u8 *pointer, s64 size);
	u32                   SeekFile(u32 handle, s64 position, FileMove type);
	void                  StatFile(u32 structaddress,FileInfo &info);
	std::vector<FileInfo> GetDirListing(std::string path);
	bool                  OwnsHandle(u32 handle);
	FileInfo              GetFileInfo(std::string filename);

    void                  PrintTree();

protected:
    void                  RecursivePrint(const fs_IsoDirectory &directory, int indent);
};
