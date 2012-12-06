#include "stdafx.h"
#include "genericfilesystem.h"
#include "memstickfilesystem.h"
#include "log.h"
#include <QObject>
#include <QDir>
#include <QFile>
#include "../hle/modules/iofilemgr/IoFileMgrForUser.h"

fs_MemStickFileSystem::fs_MemStickFileSystem(fs_GenericHandleAllocator *_hAlloc, std::string _basePath) : basePath(_basePath)
{
	hAlloc = _hAlloc;
}
bool fs_MemStickFileSystem::OwnsHandle(u32 handle)
{
	EntryMap::iterator iter = entries.find(handle);
	return (iter != entries.end());
}
u32   fs_MemStickFileSystem::OpenFile(std::string filename, FileAccess access)
{
	filename="ms0/" + filename;
	OpenFileEntry entry; //create a new entry
    char s[4];
    *((u32 *)s) = 0;
	if(access==FILEACCESS_NONE)//just for searching if file exists. Open it for read...
	{
       	s[0] = 'r';
		s[1] = 'b';
	}
    if(access==FILEACCESS_READ)
	{
		s[0] = 'r';
		s[1] = 'b';
	}
	else if(access==FILEACCESS_WRITE)
	{
		s[0] = 'w';
		s[1] = 'b';
	}
	if(access & FILEACCESS_READWRITE)
	{
       if((access & FILEACCESS_CREATE) && (access & FILEACCESS_TRUNC)) //create new file and destroy contexts if exist
	   {
           s[0] = 'w';
		   s[1] = '+';
		   s[2] = 'b';
	   }
	   else //Open a file for read/write	Already Exists=read from start	Does Not Exist=error
	   {
	       s[0] = 'r';
		   s[1] = '+'; 
		   s[2] = 'b';
	   }
	}       
	entry.hFile = fopen(filename.c_str(),s); //TODO handle all cases for reading writing etc..
	if(entry.hFile==NULL)//file can't be opened?
	{
     errorf(cardFileSystem,"OpenFile %s failed!",filename.c_str());
	 return 0;
	}
	else
	{
		u32 newHandle=hAlloc->RequestHandle();
		entries[newHandle]=entry;
		return newHandle;
	}
}
void  fs_MemStickFileSystem::CloseFile(u32 handle)
{
  	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{
		hAlloc->ReleaseHandle(handle);
		fclose((*iter).second.hFile);
		entries.erase(iter);
	}
	else
	{
		errorf(cardFileSystem,"Can't close file with handle = %u",handle);
		DebugBreak();
	}
}
u32   fs_MemStickFileSystem::ReadFile(u32 handle, u8 *pointer, s64 size)
{
	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{
		u32 bytesRead = fread(pointer,1,size,(*iter).second.hFile);
		return bytesRead;
	}
	else
	{
		//This shouldn't happen...
		errorf(cardFileSystem,"Can't read file with handle = %u",handle);
		DebugBreak();
		return 0;
	}
}
u32   fs_MemStickFileSystem::WriteFile(u32 handle, const u8 *pointer, s64 size)
{
	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{

	    return fwrite(pointer,1,size,(*iter).second.hFile);
	}
	else
	{
		errorf(cardFileSystem,"Can't write file with handle = %u",handle);
		DebugBreak();
		return 0;
	}
}
u32   fs_MemStickFileSystem::SeekFile(u32 handle, s64 position, FileMove type)
{
	EntryMap::iterator iter = entries.find(handle);
	if (iter != entries.end())
	{

	    fseek((*iter).second.hFile,position,type);
		return ftell((*iter).second.hFile);
	}
	else
	{
		errorf(cardFileSystem,"Can't seek file with handle = %u",handle);
		DebugBreak();
		return 0;
	}
}
void  fs_MemStickFileSystem::StatFile(u32 structaddress,FileInfo &info)
{
	    info.name.replace(0,5,"ms0/");//when it reaches reaches with ms0:/ replace that!
		SceIoStat *stat = Memory::addr< SceIoStat >(structaddress);
		memset(stat,0,sizeof(SceIoStat)); //reset iostat
		stat->st_size = (s64)info.size;

		int type, attr;
		if (info.type & FILETYPE_DIRECTORY)
			type = SCE_STM_FDIR, attr=TYPE_DIR;
		else
			type = SCE_STM_FREG, attr=TYPE_FILE;

		stat->st_mode = 0777 | type; //set every right to be readable/writeable/executable for all groups
		stat->st_attr = attr; //hmm not sure about that
		stat->st_size = info.size;
		QFileInfo file(info.name.c_str());
		if(file.exists())
		{
			//create time
			QDateTime createdatetime = file.created();
			QDate createday= createdatetime.date();
			stat->st_ctime_.day=createday.day();
			stat->st_ctime_.month=createday.month();
			stat->st_ctime_.year=createday.year();
			QTime createtime=createdatetime.time();
			stat->st_ctime_.hour=createtime.hour();
			stat->st_ctime_.minute=createtime.minute();
			stat->st_ctime_.second=createtime.second();
			stat->st_ctime_.microsecond=createtime.msec()*1000;
			//accessed time
			QDateTime accesseddatetime = file.lastRead();
			QDate accessday= accesseddatetime.date();
			stat->st_atime_.day=accessday.day();
			stat->st_atime_.month=accessday.month();
			stat->st_atime_.year=accessday.year();
			QTime accesstime=accesseddatetime.time();
			stat->st_atime_.hour=accesstime.hour();
			stat->st_atime_.minute=accesstime.minute();
			stat->st_atime_.second=accesstime.second();
			stat->st_atime_.microsecond=accesstime.msec()*1000;
			//modify time
			QDateTime modifydatetime = file.lastModified();
			QDate modifyday= modifydatetime.date();
			stat->st_mtime_.day=modifyday.day();
			stat->st_mtime_.month=modifyday.month();
			stat->st_mtime_.year=modifyday.year();
			QTime modifytime=modifydatetime.time();
			stat->st_mtime_.hour=modifytime.hour();
			stat->st_mtime_.minute=modifytime.minute();
			stat->st_mtime_.second=modifytime.second();
			stat->st_mtime_.microsecond=modifytime.msec()*1000;
		}
}
std::vector<FileInfo> fs_MemStickFileSystem::GetDirListing(std::string path)
{
	path="ms0/" + path;
    std::vector<FileInfo> myVector;
    QDir dirpath(path.c_str());
	if(!dirpath.exists())
	{
		errorf(cardFileSystem,"getdirlisting: path doesn't exist %s",path.c_str());
	}
	dirpath.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QFileInfoList list = dirpath.entryInfoList();
    for (int i = 0; i < list.size(); ++i) 
	{
         QFileInfo fileInfo = list.at(i);
         FileInfo entry;
		 if(fileInfo.isDir())
			 entry.type=FILETYPE_DIRECTORY;
		 else if(fileInfo.isFile())
			 entry.type=FILETYPE_NORMAL;
		 else
			 errorf(cardFileSystem,"getdirlisting: not a dir nor file?");
		 entry.size=fileInfo.size();
		 entry.name=fileInfo.fileName().toStdString();
          myVector.push_back(entry);
	}
	return myVector;
}
FileInfo fs_MemStickFileSystem::GetFileInfo(std::string filename)
{

    filename="ms0/" + filename;
    FileInfo x;
    x.size=0;
	QFileInfo info(filename.c_str());
	x.size=info.size();
	//WARNING do not set the name here!
	if(info.isDir())
		 x.type=FILETYPE_DIRECTORY;
	else if(info.isFile())
		 x.type=FILETYPE_NORMAL;
	return x;
}

