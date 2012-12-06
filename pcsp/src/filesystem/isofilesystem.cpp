#include "stdafx.h"
#include <stdio.h>
#include "isofilesystem.h"
#include "log.h"
#include "../hle/modules/iofilemgr/IoFileMgrForUser.h"

fs_ISOFileSystem::fs_ISOFileSystem(fs_GenericHandleAllocator *_hAlloc, fs_BlockDevice* _source)
	: rootDir(_source)
{
	hAlloc = _hAlloc;
	source = _source;
}

fs_ISOFileSystem::~fs_ISOFileSystem(void)
{
}

u32   fs_ISOFileSystem::OpenFile(std::string filename, FileAccess access)
{
	IsoFile file; //create a new entry

/*	if(access != FILEACCESS_READ)
	{
		errorf(isoFileSystem,"Unsupported access mode for iso fs!");
		return 0;
	}*/

    if (filename.size()==0)
	{
		// make up a fake entry
		FileInfo desc;
		desc.lba = 0;
        desc.size = source->GetBlockCount() * source->GetBlockSize();
        file = IsoFile(source, desc);
	}
	else
	{
		if(filename.at(0) == '/')
			filename=filename.substr(1);

		if(!rootDir.OpenFile(filename,&file))
		{
			if(filename.substr(0,7) == "sce_lbn")
			{
				string::size_type idx0 = 7;
				string::size_type idx1 = filename.find_first_of('_',7);
				if(filename.substr(idx1,5) == "_size")
				{
					string::size_type idx2 = idx1+5;
					int lba  = strtoul(filename.c_str()+idx0,NULL,16);
					int size = strtoul(filename.c_str()+idx2,NULL,16);

					// make up a fake entry
					FileInfo desc;
					desc.lba = lba;
					desc.size = size;
					file = IsoFile(source,desc);
					goto file_open;
				}
			}

			errorf(isoFileSystem,"OpenFile %s failed!",filename.c_str());
			return 0;
		}
	}
file_open:

	u32 newHandle=hAlloc->RequestHandle();
	entries[newHandle].Assign(source,file.getEntry());
	return newHandle;
}

void  fs_ISOFileSystem::CloseFile(u32 handle)
{
	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{
		hAlloc->ReleaseHandle(handle);
		entries.erase(iter);
	}
	else
	{
		errorf(isoFileSystem,"Can't close file with handle = %u",handle);
		DebugBreak();
	}
}

bool fs_ISOFileSystem::OwnsHandle(u32 handle)
{
	EntryMap::iterator iter = entries.find(handle);
	return (iter != entries.end());
}

u32   fs_ISOFileSystem::ReadFile(u32 handle, u8 *pointer, s64 size)
{
	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{
		u32 bytesRead = iter->second.read(pointer, size);
		return bytesRead;
	}
	else
	{
		//This shouldn't happen...
		errorf(isoFileSystem,"Can't read file with handle = %u",handle);
		DebugBreak();
		return 0;
	}
}

u32   fs_ISOFileSystem::WriteFile(u32 handle, const u8 *pointer, s64 size)
{
	errorf(isoFileSystem,"Can't write to file with handle = %u",handle);
	DebugBreak();
	return 0;
}

u32   fs_ISOFileSystem::SeekFile(u32 handle, s64 position, FileMove type)
{
	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{
		iter->second.seek(position,type);
		return iter->second.getFilePointer();
	}
	else
	{
		errorf(isoFileSystem,"Can't seek file with handle = %u",handle);
		DebugBreak();
		return 0;
	}
}

void  fs_ISOFileSystem::StatFile(u32 structaddress,FileInfo &info)
{
	SceIoStat *stat = Memory::addr< SceIoStat >(structaddress);
	memset(stat,0,sizeof(SceIoStat)); //reset iostat

	int type, attr;
	if (info.type & FILETYPE_DIRECTORY)
		type = SCE_STM_FDIR, attr=TYPE_DIR;
	else
		type = SCE_STM_FREG, attr=TYPE_FILE;

	stat->st_mode = 0555 | type; //set every right to be readable/writeable/executable for all groups
	stat->st_attr = attr; //hmm not sure about that
	stat->st_size = info.size;
	stat->st_private[0]=info.lba;
	stat->st_atime_.year = info.date.year;
	stat->st_atime_.month = info.date.month;
	stat->st_atime_.day = info.date.day;
	stat->st_atime_.hour = info.date.hour;
	stat->st_atime_.minute = info.date.minute;
	stat->st_atime_.second = info.date.second;
	stat->st_atime_.microsecond = 0;

	//TODO time ?
}

std::vector<FileInfo> fs_ISOFileSystem::GetDirListing(std::string path)
{
	FileInfo directoryDesc;

	if(path=="/")
		path="."; // needed for it to work

    if (!rootDir.FindFile(path, &directoryDesc))
	{
		errorf(isoFileSystem,"getdirlisting: path doesn't exist %s",path.c_str());
	}

	fs_IsoDirectory dir(source, directoryDesc);

	// Let's do like memcard fs and ignore "." and ".." entries.
	vector<FileInfo> childs;
	vector<FileInfo> list = dir.GetChilds();
	for (u32 i=0;i<list.size();i++)
	{
		if((list[i].name != ".")&&(list[i].name != ".."))
			childs.push_back(list[i]);
	}

	return childs;
}

FileInfo fs_ISOFileSystem::GetFileInfo(std::string filename)
{
	FileInfo desc;

	if(!rootDir.FindFile(filename,&desc))
	{
		desc.size=0;
        desc.exists = false;
        return desc;
	}

	desc.name="";	//WARNING do not set the name here!

	return desc;
}

void fs_ISOFileSystem::PrintTree()
{
    fprintf(stderr, "Tree!\n");
    RecursivePrint(rootDir, 0);
}

void fs_ISOFileSystem::RecursivePrint(const fs_IsoDirectory &directory, int indent)
{
	vector<FileInfo> list = directory.GetChilds();
	for (size_t i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < indent; j++)
		{
			fputs(" ", stderr);
		}
		fprintf(stderr, "%s - %i\n", list[i].name.c_str(), (int)list[i].size);
		if (list[i].type == FILETYPE_DIRECTORY && list[i].name != "." && list[i].name != ".." && list[i].name.size() != 0)
		{
			fs_IsoDirectory dir(source, list[i]);
			RecursivePrint(dir, indent + 2);
		}
	}
}
