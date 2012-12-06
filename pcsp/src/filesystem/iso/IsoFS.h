#pragma once

#include <vector>
#include <string>

typedef unsigned char byte;

#include "../genericfilesystem.h"

FileInfo MkFileInfo(const byte *data, int length);

#include "IsoFile.h"

class fs_IsoDirectory 
{
public:
	std::vector<FileInfo> files;

	fs_BlockDevice *internalReader;

protected:
	void Init(fs_BlockDevice *r, FileInfo directoryEntry);

public:

	// Used to load the Root directory from an image
	fs_IsoDirectory(fs_BlockDevice *r);

	// Used to load a specific directory from a file descriptor
	fs_IsoDirectory(fs_BlockDevice *r, FileInfo directoryEntry);

    vector<FileInfo> GetChilds() const;
	bool GetEntry(std::string fileName, FileInfo* dest);

	// Tool. For OpenFile.
	bool FindFile(std::string filePath, FileInfo* dest);

	bool OpenFile(string filePath, IsoFile* dest);

	~fs_IsoDirectory(void);
};
