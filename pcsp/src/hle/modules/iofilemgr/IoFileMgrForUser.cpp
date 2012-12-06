#include "stdafx.h"
#include "../module_errorcodes.h"
#include "hardware/memorystick.h"
#include "IoFileMgrForUser.h"
#include "memory/memory.h"
#include "emulator.h"
#include "debugger/debugger.h"
#include "log.h"
#include "hle/types.h"
#include "hle/kernel.h"
#include "system.h"
#include "qt4/settings.h"

#include "filesystem/genericfilesystem.h"
namespace IoFileMgrForUser
{
    static bool IoFileMgrForUser_ready = false;

    bool Reboot()
    {
        ShutDown();
        IoFileMgrForUser_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (IoFileMgrForUser_ready)
        {
            IoFileMgrForUser_ready = false;
        }
        return true;
    }

    /////////////////file access IO
    class FileNode : public KernelObject
    {
    public:
        ~FileNode()
        {
            psp::fs.CloseFile(handle);
        }
        const char *GetName() const {return fullpath.c_str();}
        const char *GetType() const {return "OpenFile";}
        std::string fullpath;
        u32 handle;
        u32 asyncResult;
    };

    int sceIoRemove()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoRemove instruction");
        return 0;
    }

    int sceIoIoctlAsync()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoIoctlAsync instruction");
        return 0;
    }
    int sceIoCancel()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoCancel instruction");
        return 0;
    }

    int sceIoWaitAsync()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoWaitAsync instruction");
        return 0;
    }
    int sceIoGetAsyncStat()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoGetAsyncStat instruction");
        return 0;
    }
    int sceIoChstat()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoChstat instruction");
        return 0;
    }
    int sceIoAssign()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoAssign instruction");
        return 0;
    }

    int sceIoChangeAsyncPriority()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoChangeAsyncPriority instruction");
        return 0;
    }
    int sceIoGetstat (u32 a0,u32 a1)
    {
        const char *filename = Memory::addr< const char >(a0);
        u32 structaddr = a1;
        infof(IoFileMgrForUser, "sceIoGetstat(filename = %s, addr = %08x)",filename,structaddr);
		u32 h = psp::fs.OpenFile(filename,FILEACCESS_NONE); 
        if(h==0) //the file can't be open!
        {
			std::vector<FileInfo> listing = psp::fs.GetDirListing(filename);//check if it is directory
			if(!(listing.size()>0))//if there are files then it is not empty
			{
             errorf(IoFileMgrForUser, "sceIoGetstat - file or dir not found");
             return PSP_ERROR_FILE_NOT_FOUND;	
			}
        }
		FileInfo info = psp::fs.GetFileInfo(filename);
		info.name=filename;
		psp::fs.StatFile(structaddr,info);
		return 0;
    }
    int sceIoSync()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoSync instruction");
        return 0;
    }
    int sceIoSetAsyncCallback()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoSetAsyncCallback instruction");
        return 0;
    }


    int sceIoRename()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoRename instruction");
        return 0;
    }

    int sceIoUnassign()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoUnassign instruction");
        return 0;
    }

    int sceIoLseek32()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoLseek32 instruction");
        return 0;
    }
    int sceIoIoctl()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoIoctl instruction");
        return 0;
    }
    int sceIoGetFdList()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoGetFdList instruction");
        return 0;
    }
    int sceIoChdir (u32 a0)
    {
        const char *dir= Memory::addr< const char >(a0);
        psp::fs.ChangeDirectory(dir);
        return 0; 
    }
    int sceIoDevctl (u32 a0,u32 a1,u32 a2,u32 a3,u32 t0,u32 t1)
    {
        const char *name = Memory::addr< const char >(a0);
		QString operation(name);
        int cmd = a1;
        u32 argAddr = a2;
        int argLen = a3;
        u32 bufPtr = t0;
        int bufLen = t1;


		switch(cmd)
		{
		    case 0x02025806: //checks if memstick is inserted
			{
				if(operation=="mscmhc0:")
			   {
				   // 1 = inserted
				   // 0 = not inserted
                   u32 *outdata = Memory::addr< u32 >(bufPtr);
			      if(settings.mDisableMemStick)
					  *outdata=0;
				  else
                      *outdata=1;
				   return 0;
			   }
			   else
			   {
                 errorf(IoFileMgrForUser,"Unsupported device tring to check if memstick is inserted");
				 return PSP_ERROR_UNSUPPORTED_OPERATION;
			   }
			}
			break;
			case 0x02025801: //unknown ms command (check fs type?)
			{
					if(operation=="mscmhc0:")
					{
						// 1 = not inserted
						// 4 = inserted
						u32 *outdata = Memory::addr< u32 >(bufPtr);
						if(settings.mDisableMemStick)
							*outdata=1;
						else
							*outdata=4;
						return 0;
					}
					else
					{
						errorf(IoFileMgrForUser,"Unsupported device tounknown ms command (check fs type?)");
						return PSP_ERROR_UNSUPPORTED_OPERATION;
					}
			}
			break;		            
			case 0x02415821:  // Register memorystick insert/eject callback (fatms0). 
			{   
				if(operation=="fatms0:")
				{
//					u32 *addr = Memory::addr< u32 >(argAddr);
					return 0;
                }
                else
                {
					return -1;
				}
			}
			break;              							        
			case 0x02415822:  // Unregister memorystick insert/eject callback (fatms0).
			{  
				if(operation=="fatms0:")
				{
//					u32 *addr = Memory::addr< u32 >(argAddr);
					return 0;
                }
                else
                {
					return -1;
				}
			}
				break;   
			case 0x02425823: //checks if memstick is inserted for fatms0 now
			{
					if(operation=="fatms0:")
					{
						// 1 = inserted
						// 0 = not inserted
						u32 *outdata = Memory::addr< u32 >(bufPtr);
			            if(settings.mDisableMemStick)
					        *outdata=0;
				        else
                            *outdata=1;
						return 0;
					}
					else
					{
						errorf(IoFileMgrForUser,"Unsupported device tring to check if memstick is inserted");
						return PSP_ERROR_DEVCTL_BAD_PARAMS;
					}
			}
			break;
			case 0x02425818:
				if(settings.mDisableMemStick) {
					return PSP_ERROR_NO_SUCH_DEVICE;
				}
				else if(argLen >= 4)
				{
					u32 sectorSize = 0x200;
					u32 sectorCount = 0x08;
					u32 freeSize = mem_stick::getFreeSize();
					u32 maxClusters = (int)((freeSize * 95L / 100) / (sectorSize * sectorCount));
					u32 freeClusters = maxClusters;
					u32 maxSectors = 512;
					u32 *addr = Memory::addr< u32 >(argAddr);           
                    Memory::memw(*addr) = maxClusters;
                    Memory::memw(*addr + 4) = freeClusters;
                    Memory::memw(*addr + 8) = maxSectors;
                    Memory::memw(*addr + 12) = sectorSize;
					Memory::memw(*addr + 16) = sectorCount;
					debugf(IoFileMgrForUser, "sceIoDevctl refer ms free space");
                    return 0;
				}
				else
				{
                    debugf(IoFileMgrForUser,"sceIoDevctl 0x02425818 bad param address");
                    return -1;
				}
				break;
			default:
				errorf(IoFileMgrForUser," UNIMPEMENT sceIoDevctl(\"%s\", %08x, %08x, %i, %08x, %i)",name, cmd,argAddr,argLen,bufPtr,bufLen);
			    return 0;
				break;
		}
		return 0;

    }

    int sceIoWaitAsyncCB()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoWaitAsyncCB instruction");
        return 0;
    }
    int sceIoPollAsync()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoPollAsync instruction");
        return 0;
    }

    int sceIoLseek32Async()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoLseek32Async instruction");
        return 0;
    }
    int sceIoRmdir()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoRmdir instruction");
        return 0;
    }
    int sceIoWriteAsync()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoWriteAsync instruction");
        return 0;
    }
    int sceIoGetDevType()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoGetDevType instruction");
        return 0;
    }
    int sceIoMkdir()
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"UNIMPLEMENTED sceIoMkdir instruction");
        return 0;
    }
    /////////////////////////////////////////SYNC FILE HANDLE////////////////////////////////////////////////////
    int sceIoOpen (u32 a0,u32 a1,u32 a2)
    {
        const char *filename = Memory::addr< const char >(a0);
        int flag = a1;
        int mode = a2;
        infof(IoFileMgrForUser, "sceIoOpen(%s , flag = %08x , mode = %08x)", filename, flag,mode);

        int access=FILEACCESS_NONE;
        if (flag & SCE_O_RDONLY) access |= FILEACCESS_READ;
        if (flag & SCE_O_WRONLY)  access |= FILEACCESS_WRITE;
        if (flag & SCE_O_RDWR) access |= FILEACCESS_READWRITE;   
        if (flag & SCE_O_NBLOCK) 
        {
            errorf(IoFileMgrForUser,"sceIoOpen: unsupported flag SCE_O_NBLOCK");
        }
        if (flag & SCE_O_APPEND)
        {
            errorf(IoFileMgrForUser,"sceIoOpen: unsupported flag SCE_O_APPEND");
        }
        if (flag & SCE_O_CREAT) access |= FILEACCESS_CREATE;   
        if (flag & SCE_O_TRUNC) access |= FILEACCESS_TRUNC;    
        if (flag & SCE_O_EXCL)
        {
            errorf(IoFileMgrForUser,"sceIoOpen: unsupported flag SCE_O_EXCL");
        }
        if (flag & SCE_O_FDEXCL)
        {
            errorf(IoFileMgrForUser,"sceIoOpen: unsupported flag SCE_O_FDEXCL");
        }
        if (flag & SCE_O_PWLOCK)
        {
            errorf(IoFileMgrForUser,"sceIoOpen: unsupported flag SCE_O_PWLOCK");
        }
        //todo! support the other file access TOO!

        u32 h = psp::fs.OpenFile(filename,(FileAccess)access); 
        if(h==0)//the file can't be open!
        {
            errorf(IoFileMgrForUser, "sceIoOpen(%s , flag = %08x , mode = %08x) - file not found", filename, flag,mode);
            return PSP_ERROR_FILE_NOT_FOUND;		
        }
        FileNode *f = new FileNode;
        SceUID id = f->GetUid();
        f->handle = h;
        f->fullpath = filename;
        f->asyncResult=id;//for async use
        infof(IoFileMgrForUser,"sceIoOpen(UID=%i , filename =%s , flag = %08x , mode = %08x)", id,filename, flag,mode);
        return id;
    }
    int sceIoWrite(u32 a0,u32 a1,u32 a2)
    {
        SceUID id = a0;
        int size = a2;
        if (a0 == 2)
        {
            //stderr!
            char *str = Memory::addr< char >(a1);
            infof(hlestdout,"stderr: %s", str);
            debugger.logStderr(str);
            return size;
        }
        if(a0 == 1)
        {
            //stdout!
            char *str = Memory::addr< char >(a1);
            char temp = str[size];
            str[size]=0;
            infof(hlestdout,"stdout: %s", str);
            debugger.logStdout(str);
            str[size]=temp;
            return size;
        }
        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            u8 *data = Memory::addr< u8 >(a1);
            infof(IoFileMgrForUser, "sceIoWrite(%s, %08x , %08x)", f->GetName(), a1, size);
            u32 byteswrite = psp::fs.WriteFile(f->handle,data,size);
            f->asyncResult=byteswrite;
            return byteswrite;
        }
        else
        {
            errorf(IoFileMgrForUser, "sceIoWrite ERROR: no file open");
            return -1;
        }
    }
    int sceIoLseek (u32 a0,u32 a2,u32 a3,u32 t0)
    {
        SceUID id = a0;
        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            s64 offset = ((s64)a2) | ((s64)a3<<32);
            int whence = t0;
            infof(IoFileMgrForUser, "sceIoLseek(%d,%08x,%i)",id,(int)offset,whence);

            FileMove seek=FILEMOVE_BEGIN;
            switch (whence)
            {
            case 0: break;
            case 1: seek=FILEMOVE_CURRENT;break;
            case 2: seek=FILEMOVE_END;break;
            }
            theEmulator.context->gpr[3]=0;
            u32 newposition = psp::fs.SeekFile(f->handle, offset, seek);
            f->asyncResult=newposition;
            return newposition;
        }
        else
        {
            errorf(IoFileMgrForUser, "sceIoLseek ERROR: no file open");
        }
        return 0;
    }
    int sceIoRead (u32 a0,u32 a1,u32 a2)
    {
        SceUID id = a0;
        if (id == 3)
        {
            infof(IoFileMgrForUser, "sceIoRead STDIN");
            return 0;
        }

        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            if (a1)
            {
                u8 *data = Memory::addr< u8 >(a1);
                int size = a2;
                infof(IoFileMgrForUser, "sceIoRead(%d, %08x , %i)",id,a1,size);
                u32 bytesread = psp::fs.ReadFile(f->handle, data, size);
                f->asyncResult=bytesread;
                return bytesread;
            }
            else
            {
                errorf(IoFileMgrForUser, "sceIoRead Reading into zero pointer");
                return -1;
            }
        }
        else
        {
            errorf(IoFileMgrForUser, "sceIoRead ERROR: no file open");
        }
        return -1;
    }
    int sceIoClose (u32 a0)
    {
        SceUID id = a0;
        infof(IoFileMgrForUser, "sceIoClose(%d)",id);
        theKernelObjects.Release<FileNode>(id);
        return 0;
    }
    /////////////////////ASYNC FILE HANDLE/////////////////////////////////////////////////////
    int sceIoLseekAsync(u32 a0,u32 a2,u32 a3,u32 t0)
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"Dummy sceIoLseekAsync instruction redirected to sceIoLseek()");
        sceIoLseek(a0,a2,a3,t0);
        return 0;
    }
    int sceIoReadAsync(u32 a0,u32 a1,u32 a2)
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"Dummy sceIoReadAsync instruction redirected to sceIoRead()");
        sceIoRead(a0,a1,a2);
        return 0;
    }
    int sceIoOpenAsync(u32 a0,u32 a1,u32 a2)
    {
        //TODO implement me
        errorf(IoFileMgrForUser,"Dummy sceIoOpenAsync instruction redirected to sceIoOpen()");
        return sceIoOpen(a0,a1,a2);
    }
    //the following are copies from the old sceIO. No use to rewrite async with the current threadman
    typedef u32 (*DeferredAction)(SceUID id, int param);
    DeferredAction defAction = 0;
    u32 defParam;

    u32 __IoClose(SceUID id, int param)
    {
        (void)param;
        infof(IoFileMgrForUser,"Deferred IoClose(%d)",id);
        return theKernelObjects.Release<FileNode>(id);
    }

    int sceIoCloseAsync(u32 a0)
    {
        infof(IoFileMgrForUser, "sceIoCloseAsync(%d)",a0);
        defAction = &__IoClose;
        return 0;
    }
    int sceIoGetAsyncStat(u32 a0,u32 a2)
    {
        SceUID id = a0;
        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            u64 *resPtr = Memory::addr< u64 >(a2);
            *resPtr = f->asyncResult;
            infof(IoFileMgrForUser, "%i = sceIoGetAsyncStat(%i,  %08x) (HACK)", (u32)*resPtr, id, a2);
            return 0; //completed
        }
        else
        {
            errorf(IoFileMgrForUser, "ERROR - sceIoGetAsyncStat with invalid id %i", id);
            return -1;
        }
    }
    int sceIoWaitAsync(u32 a0,u32 a1)
    {
        SceUID id = a0;
        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            u64 *resPtr = Memory::addr< u64 >(a1);
            *resPtr = f->asyncResult;
            if (defAction)
            {
                *resPtr = defAction(id, defParam);
                defAction = 0;
            }
            infof(IoFileMgrForUser, "%i = sceIoWaitAsync(%i, %08x) (HACK)", (u32)*resPtr, id, a1);
            return 0; //completed
        }
        else
        {
            errorf(IoFileMgrForUser, " ERROR - sceIoWaitAsync waiting for invalid id %i", id);
            return -1;
        }
    }
    int sceIoWaitAsyncCB(u32 a0,u32 a1)
    {
        SceUID id = a0;
        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            u64 *resPtr = Memory::addr< u64 >(a1);
            *resPtr = f->asyncResult;
            if (defAction)
            {
                *resPtr = defAction(id, defParam);
                defAction = 0;
            }
            infof(IoFileMgrForUser, "%i = sceIoWaitAsyncCB(%i, %08x) (HACK)", (u32)*resPtr, id, a1);
            return 0; //completed
        }
        else
        {
            errorf(IoFileMgrForUser, "ERROR - sceIoWaitAsyncCB waiting for invalid id %i", id);
            return -1;
        }
    }
    int sceIoPollAsync(u32 a0,u32 a1)
    {
        SceUID id = a0;
        u32 error;
        FileNode *f = theKernelObjects.Get<FileNode>(id, error);
        if (f)
        {
            u64 *resPtr = Memory::addr< u64 >(a1);
            *resPtr = f->asyncResult;
            if (defAction)
            {
                *resPtr = defAction(id, defParam);
                defAction = 0;
            }
            infof(IoFileMgrForUser, "%i = sceIoPollAsync(%i, %08x) (HACK)", (u32)*resPtr, id, a1);
            return 0; //completed
        }
        else
        {
            errorf(IoFileMgrForUser, "ERROR - sceIoPollAsync waiting for invalid id %i", id);
            return -1;
        }
    }
    /////////////////////DIRECTORY CALLS///////////////////////////////////////////////////////

    class DirListing : public KernelObject
    {
    public:
        const char *GetName() const {return name.c_str();}
        const char *GetType() const {return "DirListing";}
        std::string name;
        std::vector<FileInfo> listing;
        int index;
    };

    int sceIoDopen (u32 a0)
    {
        const char *path = Memory::addr< const char >(a0);
        infof(IoFileMgrForUser, "sceIoDopen(\"%s\")", path);
        DirListing *dir = new DirListing;
        SceUID id = dir->GetUid();
        dir->listing = psp::fs.GetDirListing(path);
        dir->index = 0;
        dir->name = std::string(path);
        return id;
    }

    int sceIoDclose (u32 a0)
    {
        u32 id = a0;
        infof(IoFileMgrForUser, "sceIoDclose UID = %d",id);
        theKernelObjects.Release<DirListing>(id);
        return 0; 
    }

    int sceIoDread (u32 a0, u32 a1)
    {
        SceUID id = a0;
        u32 error;
        DirListing *dir = theKernelObjects.Get<DirListing>(id, error);
        if (dir)
        {
            if ((size_t)dir->index == dir->listing.size())
            {
                return 0;
            }

            FileInfo &info = dir->listing[dir->index];//get filename		
            SceIoDirent *entry = Memory::addr< SceIoDirent >(a1);
            strncpy(entry->d_name, info.name.c_str(), 255);//copy the directory name before change it for proper stat!
            // This will crash horribly under x64 :(
            // Actually this looks like a bug.
            u32 address = (u32)(u64)&entry->d_stat;			
            std::string filename(dir->name + "/" + info.name + "/"); //construct directory name proper
            info.name=filename;//copy it to info struct
            psp::fs.StatFile(address, info);//stat folder		
            entry->d_private = 0xC0DEBABE;
            infof(IoFileMgrForUser, "sceIoDread( %d %08x ) = %s",a0,a1, entry->d_name);

            dir->index++;
            return dir->listing.size()-dir->index+1;
        }
        else
        {
            errorf(IoFileMgrForUser, "sceIoDread - invalid listing %i, error %08x", id, error);
            return -1;
        }

    }
    /////////////////////END OF DIRECTORY CALLS///////////////////////////////////////////////////////


}
namespace syscalls
{
    void sceIoCloseAsync(AlContext &context)              { V0 = IoFileMgrForUser::sceIoCloseAsync(A0);               };
    void sceIoRemove(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoRemove();                     };
    void sceIoDclose(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoDclose(A0);                   };
    void sceIoIoctlAsync(AlContext &context)              { V0 = IoFileMgrForUser::sceIoIoctlAsync();                 };
    void sceIoCancel(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoCancel();                     };
    void sceIoDread(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoDread(A0,A1);                 };
    void sceIoWaitAsync(AlContext &context)               { V0 = IoFileMgrForUser::sceIoWaitAsync(A0,A1);             };
    void sceIoGetAsyncStat(AlContext &context)            { V0 = IoFileMgrForUser::sceIoGetAsyncStat(A0,A2);          };
    void sceIoChstat(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoChstat();                     };
    void sceIoAssign(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoAssign();                     };
    void sceIoDopen(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoDopen(A0);                    };
    void sceIoChangeAsyncPriority(AlContext &context)     { V0 = IoFileMgrForUser::sceIoChangeAsyncPriority();        };
    void sceIoGetstat(AlContext &context)                 { V0 = IoFileMgrForUser::sceIoGetstat(A0,A1);               };
    void sceIoSync(AlContext &context)                    { V0 = IoFileMgrForUser::sceIoSync();                       };
    void sceIoSetAsyncCallback(AlContext &context)        { V0 = IoFileMgrForUser::sceIoSetAsyncCallback();           };
    void sceIoReadAsync(AlContext &context)               { V0 = IoFileMgrForUser::sceIoReadAsync(A0,A1,A2);          };
    void sceIoOpenAsync(AlContext &context)               { V0 = IoFileMgrForUser::sceIoOpenAsync(A0,A1,A2);          };
    void sceIoClose(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoClose(A0);                    };
    void sceIoRename(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoRename();                     };
    void sceIoLseekAsync(AlContext &context)              { V0 = IoFileMgrForUser::sceIoLseekAsync(A0,A2,A3,T0);      };
    void sceIoUnassign(AlContext &context)                { V0 = IoFileMgrForUser::sceIoUnassign();                   };
    void sceIoRead(AlContext &context)                    { V0 = IoFileMgrForUser::sceIoRead(A0,A1,A2);               };
    void sceIoLseek32(AlContext &context)                 { V0 = IoFileMgrForUser::sceIoLseek32();                    };
    void sceIoIoctl(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoIoctl();                      };
    void sceIoGetFdList(AlContext &context)               { V0 = IoFileMgrForUser::sceIoGetFdList();                  };
    void sceIoChdir(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoChdir(A0);                    };
    void sceIoDevctl(AlContext &context)                  { V0 = IoFileMgrForUser::sceIoDevctl(A0,A1,A2,A3,T0,T1);    };
    void sceIoWrite(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoWrite(A0,A1,A2);              };
    void sceIoWaitAsyncCB(AlContext &context)             { V0 = IoFileMgrForUser::sceIoWaitAsyncCB(A0,A1);           };
    void sceIoPollAsync(AlContext &context)               { V0 = IoFileMgrForUser::sceIoPollAsync(A0,A1);             };
    void sceIoLseek(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoLseek(A0,A2,A3,T0);           };
    void sceIoLseek32Async(AlContext &context)            { V0 = IoFileMgrForUser::sceIoLseek32Async();               };
    void sceIoRmdir(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoRmdir();                      };
    void sceIoOpen(AlContext &context)                    { V0 = IoFileMgrForUser::sceIoOpen(A0,A1,A2);               };
    void sceIoWriteAsync(AlContext &context)              { V0 = IoFileMgrForUser::sceIoWriteAsync();                 };
    void sceIoGetDevType(AlContext &context)              { V0 = IoFileMgrForUser::sceIoGetDevType();                 };
    void sceIoMkdir(AlContext &context)                   { V0 = IoFileMgrForUser::sceIoMkdir();                      };
}
