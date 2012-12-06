#include "stdafx.h"

#include <string.h>
#include <memory>

#include "loaders.h"
#include "emulator.h"
#include "log.h"
#include "pbp.h"
#include "system.h"

#include "wtf/core/psp/hle/sceKernelModule.h"

#include <QtCore>
#include <QtGui>

#include "filesystem/memstickfilesystem.h"
#include "filesystem/isofilesystem.h"
#include "settings.h"
#include "hardware/crypto/PrxDec.h"

fs_MemStickFileSystem *memstick;
fs_ISOFileSystem *umdiso;
psf_loader *psffile;
std::string bootpath("disc0:/PSP_GAME/SYSDIR/BOOT.BIN");
std::string ebootpath("disc0:/PSP_GAME/SYSDIR/EBOOT.BIN");
std::string isoname;
fs_BlockDevice *constructBlockDevice(QString const &filename)
{
    if (filename.endsWith(".cso", Qt::CaseInsensitive))
	{
		return new fs_CSOFileBlockDevice(filename.toStdString());
	}
	else
	{
		return new fs_ISOFileBlockDevice(filename.toStdString());
	}
}

std::string loaders::getBootPath() {
	return bootpath;
}
std::string loaders::getEbootPath() {
	return ebootpath;
}

void loaders::setBootPath(char const *path)
{
	bootpath = std::string(path);
}

void loaders::setEbootPath(char const *path)
{
	ebootpath = std::string(path);
}
void loaders::setIsoName(std::string path)
{
	isoname=path;
}
std::string loaders::getIsoName()
{
	return isoname;
}
EmuFileType loaders::IdentifyFile(QString const &filename)
{
	//check if file is from umd disc . That happends when a game calls KernelLoadExec
	if(filename.startsWith("disc0"))
	{
       return FILETYPE_PSP_INTERNAL_ELF;
	}
    QFile file(filename);

    if (!file.exists())
	{
        return FILETYPE_NO_FILE;
    }
    if (file.open(QFile::ReadOnly))
    {
        u32 id;
        if (file.read((char *)&id, 4) == 4)
        {
            file.close();

            // TODO: Get rid of these nasty multi-char constants.
            if (id == 'FLE\x7F')
            {
                return FILETYPE_PSP_ELF;
            }
			else if (id == 'PSP\x7E')
            {
                return FILETYPE_ENCRYPTED;
            }
            else if (id == 'PBP\x00')
            {
                return FILETYPE_PSP_PBP;
            }
            else
            {
                if (filename.contains(QRegExp("^([^\\.]*\\.)+[ci]so$", Qt::CaseInsensitive)))
                {
                    return FILETYPE_PSP_ISO;
                }
            }

            printf("Unknown filetype: %s", filename.toStdString().c_str());
            return FILETYPE_UNKNOWN;
        }

        file.close();
    }
    
    return FILETYPE_ERROR;
}

EmuFileType loaders::LoadFile(QString const &filename)
{
    EmuFileType result = IdentifyFile(filename);
    switch (result) 
    {
    case FILETYPE_PSP_PBP:
        return LoadPBP(filename);
    case FILETYPE_PSP_ELF:
        return LoadELF(filename);
    case FILETYPE_PSP_ISO:
        return LoadISO(filename);
	case FILETYPE_PSP_INTERNAL_ELF:
		return LoadInternalELF(filename);
    default:
        fprintf(stderr, "IdentifyFile error");
    }
    return result;
}

QString loaders::getDiscID()
{
  if (psffile!=NULL)
  {
	  return psffile->getString("DISC_ID");
  }
  else
  {
	  return "";
  }
}
EmuFileType loaders::LoadISO(QString const &filename)
{
	umdiso = new fs_ISOFileSystem(&psp::fs, constructBlockDevice(filename));
    psp::fs.Mount("disc0:", umdiso);
	psp::fs.Mount("umd0:",  umdiso);
    psp::fs.Mount("umd1:",  umdiso);
	psp::fs.Mount("DISC0:", umdiso);
	psp::fs.Mount("host0:", umdiso);
    setIsoName(filename.toUtf8().constData());
	memstick = new fs_MemStickFileSystem(&psp::fs,"");
	psp::fs.Mount("ms0:/",memstick);

    Log::reset();

    std::string psf_file("disc0:/PSP_GAME/PARAM.SFO");

	FileInfo info = psp::fs.GetFileInfo(psf_file);
	
    s64 psfsize = (s64)info.size;
    if (!psfsize)
    {
        fprintf(stderr, "PSF error, skipping\n");
    }
    else
    {
        u32 handle = psp::fs.OpenFile(psf_file, FILEACCESS_READ);
        u8 *psf = new u8[(int)psfsize];
        psp::fs.ReadFile(handle, psf, psfsize);
		psffile = new psf_loader();
		psffile->read(psf);
		psffile->printpsf();
        psp::fs.CloseFile(handle);
    }

    umdiso->PrintTree();

    infof(loader, "Loading %s...", bootpath.c_str());
	FileInfo bootinfo = psp::fs.GetFileInfo(bootpath);
	s64 bootsize      = (s64)bootinfo.size;
    if (bootsize)
    {
        u32 handle = psp::fs.OpenFile(bootpath, FILEACCESS_READ);
        u8 *data   = new u8[(int)bootsize];
        psp::fs.ReadFile(handle, data, bootsize);
        psp::fs.CloseFile(handle);

        switch (*(u32 *)data)
        {
        case 0x464C457F:
            {
                hle::__KernelLoadExec(data, bootpath.c_str());
                delete[] data;
                return FILETYPE_PSP_ISO;
            }

        case 0x5053507E:
        case 0x4543537E:
			{
				if(settings.mEnableDecryptor)
				{
					// Internal decryption (KIRK emulation).
					infof(loader, "Encrypted boot file detected!");					
					u8 *inBuf   = new u8[(int)bootsize];
					u8 *outBuf   = new u8[(int)bootsize];
					
					infof(loader, "Calling Decrypt PRX version 1.");
					inBuf = data;		
					int retsize = prx_decrypter::DecryptPRX1(inBuf, outBuf, bootsize, *(u32 *)&inBuf[0xD0]);

					if (retsize <= 0) {
						infof(loader, "Decrypt PRX version 1 failed! Calling Decrypt PRX version 2.");
						inBuf = data;
						retsize = prx_decrypter::DecryptPRX2(inBuf, outBuf, bootsize, *(u32 *)&inBuf[0xD0]);
					}

					data = outBuf;
					hle::__KernelLoadExec(data, bootpath.c_str());
					delete[] data;
					return FILETYPE_PSP_ISO;
				} 
				else  //try the old way...
				{
					infof(loader, "Internal Decrypter disabled. Searching for external decrypted BOOT.BIN.");
					delete[] data; 
					QString decryptedboot = "decrypted/" + getDiscID() + ".bin"; 
					QFile   decrypt(decryptedboot); 
					if (!decrypt.exists() || !decrypt.open(QFile::ReadOnly))  
					{ 
						return FILETYPE_ENCRYPTED; 
					} 
					data = decrypt.map(0, (u32)decrypt.size()); 
					hle::__KernelLoadExec(data, bootpath.c_str()); 
					decrypt.unmap(data); 
					decrypt.close(); 
					return FILETYPE_PSP_ISO; 
				}
			}
        case 0x00000000:
            delete[] data;
            break;

        default:
            delete[] data;
            return FILETYPE_UNKNOWN;
        }

    }

	infof(loader, "Loading %s...", ebootpath.c_str());
    FileInfo ebootinfo = psp::fs.GetFileInfo(ebootpath);
	s64 ebootsize      = (s64)ebootinfo.size;
    if (ebootsize)
    {
        u8 *data   = new u8[(int)ebootsize];       
        u32 handle = psp::fs.OpenFile(ebootpath, FILEACCESS_READ);
        psp::fs.ReadFile(handle, data, ebootsize);
        psp::fs.CloseFile(handle);
		
        switch (*(u32 *)data)
        {
        case 0x464C457F:
            {
                hle::__KernelLoadExec(data, ebootpath.c_str());
                delete[] data;
                return FILETYPE_PSP_ISO;
            }

        case 0x5053507E:
        case 0x4543537E:
			{
				if(settings.mEnableDecryptor)
				{
					// Internal decryption (KIRK emulation).
					infof(loader, "Encrypted boot file detected!");					
					u8 *inBuf   = new u8[(int)ebootsize];
					u8 *outBuf   = new u8[(int)ebootsize];
					
					infof(loader, "Calling Decrypt PRX version 1.");
					inBuf = data;		
					int retsize = prx_decrypter::DecryptPRX1(inBuf, outBuf, ebootsize, *(u32 *)&inBuf[0xD0]);

					if (retsize <= 0) {
						infof(loader, "Decrypt PRX version 1 failed! Calling Decrypt PRX version 2.");
						inBuf = data;
						retsize = prx_decrypter::DecryptPRX2(inBuf, outBuf, ebootsize, *(u32 *)&inBuf[0xD0]);
					}

					data = outBuf;
					hle::__KernelLoadExec(data, ebootpath.c_str());
					delete[] data;
					return FILETYPE_PSP_ISO;
				} 
				else  //try the old way...
				{
					infof(loader, "Internal Decrypter disabled. Searching for external decrypted EBOOT.BIN.");
					delete[] data; 
					QString decryptedboot = "decrypted/" + getDiscID() + ".bin"; 
					QFile   decrypt(decryptedboot); 
					if (!decrypt.exists() || !decrypt.open(QFile::ReadOnly))  
					{ 
						return FILETYPE_ENCRYPTED; 
					} 
					data = decrypt.map(0, (u32)decrypt.size()); 
					hle::__KernelLoadExec(data, ebootpath.c_str()); 
					decrypt.unmap(data); 
					decrypt.close(); 
					return FILETYPE_PSP_ISO; 
				}
			}

        case 0x00000000:
        default:
            delete[] data;
            return FILETYPE_UNKNOWN;
        }
	}

    return FILETYPE_UNKNOWN;
}

EmuFileType loaders::LoadInternalELF( QString const &filename )
{
	umdiso = new fs_ISOFileSystem(&psp::fs, constructBlockDevice(QString::fromUtf8(getIsoName().c_str())));//get the iso
    psp::fs.Mount("disc0:", umdiso);
	psp::fs.Mount("umd0:",  umdiso);
    psp::fs.Mount("umd1:",  umdiso);
	psp::fs.Mount("DISC0:", umdiso);
	psp::fs.Mount("host0:", umdiso);
    
	memstick = new fs_MemStickFileSystem(&psp::fs,"");
	psp::fs.Mount("ms0:/",memstick);

	std::string filen = filename.toUtf8().constData();
	FileInfo file = psp::fs.GetFileInfo(filen);
	s64 filesize      = (s64)file.size;
    if (filesize)
    {
        u32 handle = psp::fs.OpenFile(filen, FILEACCESS_READ);
        u8 *data   = new u8[(int)filesize];
        psp::fs.ReadFile(handle, data, filesize);
        psp::fs.CloseFile(handle);
		hle::__KernelLoadExec(data, filen.c_str());
        delete[] data;
        return FILETYPE_PSP_INTERNAL_ELF;
	}
	return FILETYPE_ERROR;

           
}
EmuFileType loaders::LoadELF( QString const &filename )
{
    QFile file(filename);

    if (file.exists() && file.open(QFile::ReadOnly)) 
    {
        u8 *data = file.map(0, (u32)file.size());

        QString path = QFileInfo(file).canonicalPath();

        if (path.startsWith("ms0/"))
        {
            memstick = new fs_MemStickFileSystem(&psp::fs, QDir::toNativeSeparators(path).toStdString());
            psp::fs.Mount("ms0:/", memstick);
            path.insert(3, QChar(':'));
        }

        hle::__KernelLoadExec(data, path.toStdString().c_str());

        file.unmap(data);
        file.close();

        return FILETYPE_PSP_ELF;
    }

    return FILETYPE_ERROR;
}

EmuFileType loaders::LoadPBP( QString const &filename )
{
	std::auto_ptr<pbp> pbpfile(new pbp());

	if (!pbpfile->open(filename.toStdString().c_str()))
    {
        errorf(loader, "Unable to open pbp %s!", filename.toStdString().c_str());
        return FILETYPE_ERROR;
    }

    if (!pbpfile->isValid())
    {
        errorf(loader, "The pbp you are trying to load is not valid!");
        return FILETYPE_ERROR;
    }

    QFile file(filename);

    if (file.exists() && file.open(QFile::ReadOnly)) 
    {
        u8 *data = file.map((u32)pbpfile->pbpheader->offset_psp_data, (u32)pbpfile->size_psp_data);

        QString path = QFileInfo(file).canonicalPath();

        if (path.startsWith("ms0/"))
        {
            memstick = new fs_MemStickFileSystem(&psp::fs, QDir::toNativeSeparators(path).toStdString());
            psp::fs.Mount("ms0:/", memstick);
            path.insert(3, QChar(':'));
        }

        hle::__KernelLoadExec(data, path.toStdString().c_str());

        file.unmap(data);
        file.close();

        return FILETYPE_PSP_PBP;
    }

    return FILETYPE_ERROR;
}

void loaders::UnloadImage()
{
    // Log::reset();
    psp::fs.UnmountAll();
    safe_delete(memstick);
    safe_delete(umdiso);
	safe_delete(psffile);
    hle::__KernelUnLoadModule();
}


void loaders::UnloadFile()
{
    // TODO: add all unload system
    UnloadImage();		
}

