#include "stdafx.h"
#include "genericfilesystem.h"
#include "metafilesystem.h"
#include "log.h"


fs_AbstractFileSystem *fs_MetaFileSystem::GetHandleOwner(u32 handle)
{
	for (unsigned int i=0; i<fileSystems.size(); i++)
	{
		if (fileSystems[i].system->OwnsHandle(handle))
			return fileSystems[i].system; //got it!
	}
	errorf(metaFileSystem,"Can't find an registered filesystem!");
	//none found?
	return 0;
}
void fs_MetaFileSystem::Mount(std::string prefix, fs_AbstractFileSystem *system)
{
	System x;
	x.prefix=prefix;
	x.system=system;
	fileSystems.push_back(x);
}

void fs_MetaFileSystem::Unmount(fs_AbstractFileSystem *system)
{

}
void fs_MetaFileSystem::UnmountAll()
{
	fileSystems.clear();
}
bool fs_MetaFileSystem::MapFilePath(std::string inpath, std::string* outpath, fs_AbstractFileSystem **system)
{
  	for (unsigned int i=0; i<fileSystems.size(); i++)
	{
		int prefLen = fileSystems[i].prefix.size();
		if (fileSystems[i].prefix== inpath.substr(0,prefLen))//this should work on e.g disc0:/
		{
			*outpath = inpath.substr(prefLen);
			*system = fileSystems[i].system;
			return true;
		}
	}
	return false;
}

u32   fs_MetaFileSystem::OpenFile(std::string filename, FileAccess access)
{
	if(filename.find("./") == 0)//the file open starts with "./blablabla"
	{
		
		filename=filename.substr(1,filename.size());//remove the dot
		filename=currentDirectory+filename;
		infof(metaFileSystem,"Openfile:filename starts with ./ Expanding to %s",filename.c_str());
	}
	if(filename.find("/") == 0)//the file open starts with "/blablabla"
	{
		filename=currentDirectory+filename;
		infof(metaFileSystem,"Openfile:filename starts with / Expanding to %s",filename.c_str());
	}
	if(filename.find(":") == string::npos)
	{
        filename=currentDirectory+"/"+filename;
		infof(metaFileSystem,"Openfile:filename PROBABLY using absolute dir Expanding to %s",filename.c_str());
	}
  	fs_AbstractFileSystem *system;
	std::string of;
	if (MapFilePath(filename, &of, &system))
	{
		return system->OpenFile(of, access);
	}
	else
	{
		infof(metaFileSystem,"Openfile:can't map the file to any filesystems %s",filename.c_str());
		return 0;
	}
}
void  fs_MetaFileSystem::CloseFile(u32 handle)
{
	fs_AbstractFileSystem *sys = GetHandleOwner(handle);
	if (sys)
		sys->CloseFile(handle);
	else
		infof(metaFileSystem,"Closefile:can't close handle %u",handle);
}
u32   fs_MetaFileSystem::ReadFile(u32 handle, u8 *pointer, s64 size)
{
   fs_AbstractFileSystem *sys = GetHandleOwner(handle);
	if (sys)
	{
		return sys->ReadFile(handle,pointer,size);
	}
	else
	{
		infof(metaFileSystem,"Readfile:can't read handle %u",handle);
		return 0;
		
	}
}
u32   fs_MetaFileSystem::WriteFile(u32 handle, const u8 *pointer, s64 size)
{
    fs_AbstractFileSystem *sys = GetHandleOwner(handle);
	if (sys)
	{
		return sys->WriteFile(handle,pointer,size);
	}
	else
	{
		infof(metaFileSystem,"writefile:can't write handle %u",handle);
		return 0;
		
	}
}
u32   fs_MetaFileSystem::SeekFile(u32 handle, s64 position, FileMove type)
{
    fs_AbstractFileSystem *sys = GetHandleOwner(handle);
	if (sys)
	{
		return sys->SeekFile(handle,position,type);
	}
	else
	{ 
		infof(metaFileSystem,"seekfile:can't seek handle %u",handle);
		return 0;
		
	}
}
void  fs_MetaFileSystem::StatFile(u32 structaddress,FileInfo &info)
{
	if(info.name.find(":") == string::npos)
	{
        info.name=currentDirectory+"/"+info.name;
		infof(metaFileSystem,"statfile:filename PROBABLY using absolute dir Expanding to %s",info.name.c_str());
	}
 	fs_AbstractFileSystem *system;
	std::string of;
	if (MapFilePath(info.name, &of, &system))
	{
	   system->StatFile(structaddress,info);
	}
	else
	{
		infof(metaFileSystem,"statfile:can't stat file %s",info.name.c_str());
	}
}
std::vector<FileInfo> fs_MetaFileSystem::GetDirListing(std::string path)
{
		std::string of;
	fs_AbstractFileSystem *system;
	if (MapFilePath(path, &of, &system))
	{
		return system->GetDirListing(of);
	}
	else
	{
		std::vector<FileInfo> empty;
		infof(metaFileSystem,"getdirlisting:can't get dir contents %s",path.c_str());
		return empty;
	}

}
FileInfo fs_MetaFileSystem::GetFileInfo(std::string filename)
{
	if(filename.find(":") == string::npos)
	{
        filename=currentDirectory+"/"+filename;
		infof(metaFileSystem,"getdirinfo:filename PROBABLY using absolute dir Expanding to %s",filename.c_str());
	}
	std::string of;
	fs_AbstractFileSystem *system;
	if (MapFilePath(filename, &of, &system))
	{
		return system->GetFileInfo(of);
	}
	else
	{
		FileInfo bogus; // TODO
		infof(metaFileSystem,"getfileinfo:can't get fileinfo %s",filename.c_str());
		return bogus; 
	}
}

void fs_MetaFileSystem::ChangeDirectory(std::string dir)
{
    currentDirectory = dir;
}