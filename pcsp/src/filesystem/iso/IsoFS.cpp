#include "stdafx.h"

#include "IsoFS.h"

#include "../../log.h"

#include <vector>

using namespace std;

void Tokenize(const string &str, vector<string> &tokens, const string& delimiters = " ")
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

//////////////////////////////////////////////////////////////////////////
// IsoDirectory
//////////////////////////////////////////////////////////////////////////

fs_IsoDirectory::fs_IsoDirectory(fs_BlockDevice *r)
{
	byte sector[2048];

	r->ReadBlock(16, sector, 1);

	FileInfo rootDirEntry = MkFileInfo(sector+156, 38);

	Init(r, rootDirEntry);
}

fs_IsoDirectory::fs_IsoDirectory(fs_BlockDevice* r, FileInfo directoryEntry)
{
	Init(r, directoryEntry);
}

void fs_IsoDirectory::Init(fs_BlockDevice* r, FileInfo directoryEntry)
{
	// parse directory sector
	IsoFile dataStream(r, directoryEntry);

	internalReader = r;

	files.clear();

	int remainingSize = directoryEntry.size;

	byte b[257];

	while (remainingSize >= 32) // hm hack :P
	{
		int entrySize = b[0] = dataStream.read<byte>();

		if (entrySize==0)
		{
			//break; // or continue?
			remainingSize--;
			continue;
		}

		remainingSize -= entrySize;

		dataStream.read(b+1, entrySize-1);

		files.push_back(MkFileInfo(b, entrySize));
	}
}

vector<FileInfo> fs_IsoDirectory::GetChilds() const
{
	return files;
}

bool fs_IsoDirectory::GetEntry(std::string fileName, FileInfo *dest)
{
	for (unsigned int i = 0; i < files.size(); i++)
    {
		string file = files[i].name;
		if (strcasecmp(file.c_str(), fileName.c_str()) == 0)
		{
			*dest = files[i];
			return true;
		}
	}

	errorf(isoFileSystem, "Entry '%s' not found in directory.", fileName.c_str());
	return false;
}

bool fs_IsoDirectory::FindFile(string filePath, FileInfo *dest)
{
	FileInfo info;
	fs_IsoDirectory dir = *this;

	vector<string> path;

	Tokenize(filePath, path, "\\/");

	// walk through path ("." and ".." entries are in the directories themselves,
	// so even if the path included . and/or .., it should still work)
	for (u32 i = 0; i < path.size(); i++)
	{
		string pathName = path[i];
		if (!dir.GetEntry(pathName,&info))
        {
            return false;
        }

		if (info.type == FILETYPE_DIRECTORY) // if it's a directory
		{
			dir  = fs_IsoDirectory(internalReader, info);
		}
		else
		{
			if (i==(path.size()-1))
            {
                break;
            }
			
			return false;
		}
	}

	*dest = info;
	return true;
}

bool fs_IsoDirectory::OpenFile(string filePath, IsoFile* dest)
{
	FileInfo info;
	if (!FindFile(filePath,&info))
    {
        return false;
    }

	if (info.type != FILETYPE_NORMAL) // if it's a directory
	{
		errorf(isoFileSystem, "Filename points to a directory.");
		return false;
	}

	dest->Assign(internalReader, info);

	return true;
}

fs_IsoDirectory::~fs_IsoDirectory()
{
}

//////////////////////////////////////////////////////////////////////////
// FileInfo
//////////////////////////////////////////////////////////////////////////

FileInfo MkFileInfo(const byte* data, int length)
{
	FileInfo info;
	info.lba            = *(const int *)(data +  2);
	info.size           = *(const int *)(data + 10);
	info.date.year      = data[18] + 1900;
	info.date.month     = data[19];
	info.date.day       = data[20];
	info.date.hour      = data[21];
	info.date.minute    = data[22];
	info.date.second    = data[23];
	info.date.gmtOffset = data[24];
	info.flags          = data[25];
	info.type           = (info.flags & 2) ? FILETYPE_DIRECTORY : FILETYPE_NORMAL;
	info.access         = 555;

	if ((info.lba < 0) || (length < 0))
	{
		errorf(isoFileSystem, "WTF?! Size or lba < 0?!");
		return FileInfo();
	}

	int fileNameLength = data[32];

	info.name.clear();

	if (fileNameLength == 1)
	{
		char c = *(const char *)(data + 33);

		switch(c)
		{
		case 0:  info.name = ".";  break;
		case 1:  info.name = ".."; break;
		default: info.name.append(1, c);
		}
	}
	else if (fileNameLength>0)
    {
        info.name.append((const char *)(data + 33), fileNameLength);
    }

	return info;
}
