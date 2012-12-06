#include "stdafx.h"
#include "sceUtility.h"
#include "../module_errorcodes.h"
#include "../iofilemgr/IoFileMgrForUser.h"
#include "sceUtilitySave.h"
#include "hle/types.h"
#include "log.h"
#include "loaders/psf.h"
#ifdef _WIN32
#include <direct.h>
#endif
#include "hardware/memorystick.h"
#include "qt4/settings.h"
namespace hlesceUtiltySave
{
	 QString getBasePath(QString gameName,QString saveName) 
	 {
        QString path = "ms0/PSP/SAVEDATA/" + gameName;
        if (!(saveName=="<>")) 
		{
            path += saveName;
        }
        path += "/";
        return path;
    }
	 u32 bytesToKb(u32 sizebytes)
	 {
        return (u32)((sizebytes + 1023) / 1024);
	 }
	 u32 getFileSize(QString fileName)
	 {
		 QFile file(fileName);
		 if(file.exists())
		 {
           return file.size();
		 }
		 else
		 {
           return 0;
		 }
	 }
	 u32 computeMemoryStickRequiredSpaceKb(u32 sizeByte) 
	 {
        u32 sizeKb = bytesToKb(sizeByte);
		u32 sectorSizeKb = mem_stick::getSectorSizeKb();
        u32 numberSectors = (sizeKb + sectorSizeKb - 1) / sectorSizeKb;
        return numberSectors * sectorSizeKb;
     }
	 u32 getSizekb(QString gameName,QString saveName,QString fileName)
	 {
		 u32 size=0;//calculate size in kb file can't be too big so u32 should be enough
         QString path = getBasePath(gameName,saveName);
		 size+=bytesToKb(getFileSize(path+fileName));
		 size+=bytesToKb(getFileSize(path+"ICON0.PNG"));
		 size+=bytesToKb(getFileSize(path+"ICON1.PNG"));
		 size+=bytesToKb(getFileSize(path+"PIC1.PNG"));
		 size+=bytesToKb(getFileSize(path+"SND0.AT3"));
		 size+=bytesToKb(getFileSize(path+"PARAM.SFO"));
         return size;
	 }
    void statFile(QString filePath,SceUtilitySDFileStat *filestat)
	{
        QFileInfo file(filePath);
		if(file.exists())
		{
			filestat->st_size=file.size();
			filestat->st_mode= 0777;//read/write/execute
			//create time
			QDateTime createdatetime = file.created();
			QDate createday= createdatetime.date();
			filestat->st_ctime.day=createday.day();
			filestat->st_ctime.month=createday.month();
			filestat->st_ctime.year=createday.year();
			QTime createtime=createdatetime.time();
			filestat->st_ctime.hour=createtime.hour();
			filestat->st_ctime.minute=createtime.minute();
			filestat->st_ctime.second=createtime.second();
			filestat->st_ctime.microsecond=createtime.msec()*1000;
			//accessed time
			QDateTime accesseddatetime = file.lastRead();
			QDate accessday= accesseddatetime.date();
			filestat->st_atime.day=accessday.day();
			filestat->st_atime.month=accessday.month();
			filestat->st_atime.year=accessday.year();
			QTime accesstime=accesseddatetime.time();
			filestat->st_atime.hour=accesstime.hour();
			filestat->st_atime.minute=accesstime.minute();
			filestat->st_atime.second=accesstime.second();
			filestat->st_atime.microsecond=accesstime.msec()*1000;
			//modify time
			QDateTime modifydatetime = file.lastModified();
			QDate modifyday= modifydatetime.date();
			filestat->st_mtime.day=modifyday.day();
			filestat->st_mtime.month=modifyday.month();
			filestat->st_mtime.year=modifyday.year();
			QTime modifytime=modifydatetime.time();
			filestat->st_mtime.hour=modifytime.hour();
			filestat->st_mtime.minute=modifytime.minute();
			filestat->st_mtime.second=modifytime.second();
			filestat->st_mtime.microsecond=modifytime.msec()*1000;
		}
	}
    bool isPresent(SceUtilitySavedataParam *param,QString saveName)
    {
	   QString gameName(param->titleId);
	   QString fileName(param->fileName);
	   QString path = getBasePath(gameName,saveName);
	  // When NULL is sent in fileName, it means any file inside the savedata folder.  
	   if(fileName.length() <=0)
	   {
          QDir readfolder("ms0/PSP/SAVEDATA/" + gameName + saveName);
		  readfolder.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
		  QStringList entries = readfolder.entryList();
		  if(entries.size()>0)
		  {
             return true;
		  }
		  else
		  {
             return false;
		  }
	   }
	   else
	   {
          QFile file(path + fileName);
		  if(file.exists())
		  {
             return true;
		  }
		  else
		  {
             return false;
		  }
	   }
    }
    int loadFile(char const *savePath, SceUtilitySDExtFile &data, char const *fileName)
    {
        char saveFileName[256];

        if ((data.pDataBuf==0) || (data.dataBufSize==0))
        {
            return 0;
        }

        sprintf(saveFileName, "%s/%s", savePath, fileName);

        FILE *f = fopen(saveFileName, "rb");
        if (f)
        {
            char *buffer = Memory::addr< char >(data.pDataBuf);
            data.dataFileSize = fread(buffer, 1, data.dataBufSize, f);
            fclose(f);
            return 0;
        }
        return 0;
     }

    int saveFile(char const *savePath, SceUtilitySDExtFile &data, char const * fileName)
    {		
        char saveFileName[256];

        if((data.pDataBuf==0) || (data.dataFileSize==0))
            return 0;

        sprintf(saveFileName, "%s/%s", savePath, fileName);

        FILE *f = fopen(saveFileName, "wb");
        if (f)
        {
            char *buffer = Memory::addr< char >(data.pDataBuf);

            fwrite(buffer, 1, data.dataFileSize, f);
            fclose(f);
            return 0;
        }
        return -1;
    }

    int loadSfo(char const *savePath, SceUtilitySDSystemFileParam &data)
    {
        char saveFileName[256];

        sprintf(saveFileName, "%s/PARAM.SFO", savePath);

        FILE *f = fopen(saveFileName, "rb");
        if (f)
        {
            fseek(f, 0, SEEK_END);
            u32 fptrsize = ftell(f);
            rewind(f);
            u8 *fptr = new u8[fptrsize];

            fread(fptr, 1, fptrsize, f);

            psf_loader *psf = new psf_loader;

            psf->read(fptr);

            QString str1 = psf->getString("SAVEDATA_DETAIL");
            QByteArray detail = str1.toLatin1();
            QString str2 = psf->getString("SAVEDATA_TITLE");
            QByteArray savedataTitle = str2.toLatin1();
            QString str3 = psf->getString("TITLE");
            QByteArray title = str3.toLatin1();
            u32 parentalLevel = psf->getInteger("PARENTAL_LEVEL");

            strcpy(data.detail, detail.data());
            strcpy(data.savedataTitle, savedataTitle.data());
            strcpy(data.title, title.data());
            data.parentalLev = parentalLevel;

            delete psf;
            fclose(f);
            return 0;
        }

        return -1;
    }

    int saveSfo(char const *savePath, SceUtilitySDSystemFileParam &data)
    {
		
        char saveFileName[256];

        sprintf(saveFileName, "%s/PARAM.SFO", savePath);
       /* FILE *f = fopen(saveFileName, "rb");
		if(f)
		{
           //TODO implement the typeWriteRemoveUpdateParam
			errorf(sceUtility,"Reopen psf for writing. typeWriteRemoveUpdateParam should be update");
		}
		fclose(f);*/
        psf_loader *psf = new psf_loader;

        QString str1 = "PARENTAL_LEVEL";
        QString str2 = "TITLE";
        QString str3 = "SAVEDATA_DETAIL";
        QString str4 = "SAVEDATA_TITLE";

		int parentalLevel = (int)data.parentalLev;
        QString title = data.title;
        QString detail = data.detail;
        QString savedataTitle = data.savedataTitle;

        psf->putInteger(str1, parentalLevel);
        psf->putString(str2, title, 128);
        psf->putString(str3, detail, 1024);
        psf->putString(str4, savedataTitle, 128);

        psf->write(saveFileName);
        delete psf;
        return 0;
    }
}
namespace sceUtilitySave
{
  static UtilityState saveState;
  static SceUtilitySavedataParam *param;

  int sceUtilitySavedataInitStart(u32 a0)
  {
      param = Memory::addr< SceUtilitySavedataParam >(a0);
      saveState.status = SCE_UTILITY_STATUS_INITIALIZE;
      return 0;
  }
  int sceUtilitySavedataGetStatus()
  {
        int currentStatus = saveState.status;
        switch (saveState.status)
        {
        case SCE_UTILITY_STATUS_SHUTDOWN: 
            saveState.status = SCE_UTILITY_STATUS_NONE;
            break;
        case SCE_UTILITY_STATUS_INITIALIZE: 
            saveState.status = SCE_UTILITY_STATUS_RUNNING;
            break;
        }
        return currentStatus;
  }
  int sceUtilitySavedataShutdownStart()
  {
        param = 0;
        saveState.status = SCE_UTILITY_STATUS_SHUTDOWN;
        return 0;
  }
  int sceUtilitySavedataUpdate()
  {
        switch (saveState.status)
        {
        case SCE_UTILITY_STATUS_INITIALIZE:
            saveState.status =  SCE_UTILITY_STATUS_RUNNING;
            break;

        case SCE_UTILITY_STATUS_RUNNING:
		    {
			 if (!settings.mDisableMemStick)  
	         {
               hleSavedata(param);
			 }
			 else
			 {
			   hleSaveNoMemStick(param);
			 }
             saveState.status = SCE_UTILITY_STATUS_FINISHED;
		    }
            break;
		
        }
        return 0;
  }
  void hleSaveDataTypeSize(SceUtilitySavedataParam *param) //mode 8
  {
	  //ms free size
	  if(param->pMs)
	  {
		  SceUtilitySavedataMsFreeSize *freesize = Memory::addr< SceUtilitySavedataMsFreeSize >(param->pMs);
		  freesize->msClusterSizeByte=mem_stick::getSectorSize();
		  freesize->msFreeCluster=mem_stick::getFreeSizeKb()/ mem_stick::getSectorSizeKb();
		  freesize->msFreeSizeKB=mem_stick::getFreeSizeKb();
		  QString FreesizeString = mem_stick::getSizeKbString(mem_stick::getFreeSizeKb());
		  strcpy (freesize->msFreeSizeStr, FreesizeString.toLatin1().data());
	  }
	  
	  //ms data size
	  if(param->pMsData)
	  {
		  SceUtilitySavedataMsDataSize *datasize = Memory::addr< SceUtilitySavedataMsDataSize >(param->pMsData);
		  QString gameName(datasize->titleId);
		  QString saveName(datasize->userId);
		  if((gameName.length()==0) || (saveName.length()==0)) 
		  {
              //checked if both are null (air conflicts for example)
			  errorf(sceUtility, "saveMode 8: gameName , saveName are null!!");
		  }
		  else
		  {
			  u32 savedataSizeKb =hlesceUtiltySave::getSizekb(gameName,saveName,QString(param->fileName));
              u32 savedataSize32Kb = mem_stick::getSize32Kb(savedataSizeKb);
			  datasize->cluster= savedataSizeKb / mem_stick::getSectorSizeKb();
			  datasize->sizeKB= savedataSizeKb;
			  strcpy(datasize->sizeStr, mem_stick::getSizeKbString(savedataSizeKb).toLatin1().data());
			  datasize->size32KB = savedataSize32Kb;
			  strcpy(datasize->size32Str,mem_stick::getSizeKbString(savedataSize32Kb).toLatin1().data());	  
		  }
	  }
	  //utility data size
	  if(param->pUtilityData)
	  {
		  SceUtilitySavedataUtilityDataSize *utilsize = Memory::addr< SceUtilitySavedataUtilityDataSize >(param->pUtilityData);
	      u32 memoryStickRequiredSpaceKb = 0;
		  memoryStickRequiredSpaceKb += mem_stick::getSectorSizeKb(); // Assume 1 sector for SFO-Params
		  memoryStickRequiredSpaceKb += hlesceUtiltySave::computeMemoryStickRequiredSpaceKb(param->dataFileSize);
		  memoryStickRequiredSpaceKb += hlesceUtiltySave::computeMemoryStickRequiredSpaceKb(param->icon0.dataFileSize);
		  memoryStickRequiredSpaceKb += hlesceUtiltySave::computeMemoryStickRequiredSpaceKb(param->icon1.dataFileSize);
		  memoryStickRequiredSpaceKb += hlesceUtiltySave::computeMemoryStickRequiredSpaceKb(param->pic1.dataFileSize);
		  memoryStickRequiredSpaceKb += hlesceUtiltySave::computeMemoryStickRequiredSpaceKb(param->snd0.dataFileSize);
   
		  QString memoryStickRequiredSpaceString = mem_stick::getSizeKbString(memoryStickRequiredSpaceKb);
		  u32 memoryStickRequiredSpace32Kb = mem_stick::getSize32Kb(memoryStickRequiredSpaceKb);
		  QString memoryStickRequiredSpace32KbString = mem_stick::getSizeKbString(memoryStickRequiredSpace32Kb);
		  utilsize->cluster = memoryStickRequiredSpaceKb / mem_stick::getSectorSizeKb();
		  utilsize->sizeKB=memoryStickRequiredSpaceKb;
		  strcpy(utilsize->sizeStr,memoryStickRequiredSpaceString.toLatin1().data());
		  utilsize->size32KB=memoryStickRequiredSpace32Kb;
		  strcpy(utilsize->size32Str,memoryStickRequiredSpace32KbString.toLatin1().data());
	  }
 	    // More tests on a PSP revealed that the output depends on the
 	    // overwrite mode. When the overwrite mode is on (1), ERROR_SAVEDATA_SIZES_NO_DATA
        // is output when there're no data to overwrite, but no error is output if
 	    // overwrite mode is off.
 	   // Note: When msDataAddr is set to NULL, this condition is discarded, as the data
       // in the Memory Stick is ignored on purpose
	//  if(param->overWriteMode && (param->pMsData != 0)) //TODO check it again seems it breaks a few games
	//  {
         if(hlesceUtiltySave::isPresent(param,QString(param->userId)))
	     {
		   param->base.result=0;
	     }
	     else
	     {
	       param->base.result=SCE_UTILITY_SAVEDATA_ERROR_SIZES_NO_DATA;
	     }
	//  }
	//  else
	//  {
	//	   param->base.result=0;
	 // }

  }
  void hleSaveDataTypeFileList(SceUtilitySavedataParam *param)
  {
      if(param->pFileList)
	  { 
		  SceUtilitySavedataFileList *filelist = Memory::addr < SceUtilitySavedataFileList > (param->pFileList);
		  QString path = hlesceUtiltySave::getBasePath(QString(param->titleId),QString(param->userId));
	      QDir readfolder(path);
		  readfolder.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
		  QStringList entries = readfolder.entryList();
          //variable used for interator and counting
		  u32 maxNumEntries = 0;
		  if(entries.size()>0)
			  maxNumEntries=entries.size();
          u32 saveFileSecureNumEntries = 0;
          u32 saveFileNumEntries = 0;
          u32 systemFileNumEntries = 0;
		  // List all files in the savedata (normal and/or encrypted).
          for (u32 i = 0; i < maxNumEntries; i++) 
		  {
			  QString filePath = path + entries.at(i).toLocal8Bit().constData();
			  
			   // System files.
               if (filePath.contains(".SFO") || filePath.contains("ICON") || filePath.contains("PIC") || filePath.contains("SND")) 
			   {
                   if(filelist->pSystemFiles)
				   {
					   //get the address for the specific sysfile
                        SceUtilitySDFileStat *sysfile = Memory::addr < SceUtilitySDFileStat > (filelist->pSystemFiles + systemFileNumEntries * 80);
                        hlesceUtiltySave::statFile(filePath,sysfile);
						strcpy (sysfile->fileName, entries.at(i).toLocal8Bit().constData());
                     }
                     systemFileNumEntries++;
                } 
			    else // Write to secure and normal.
				{ 
                   if (filelist->pSecureFiles) 
				   {
					   //get the address for the specific sysfile
                        SceUtilitySDFileStat *securefile = Memory::addr < SceUtilitySDFileStat > (filelist->pSecureFiles + saveFileSecureNumEntries * 80);
                        hlesceUtiltySave::statFile(filePath,securefile);
						strcpy (securefile->fileName, entries.at(i).toLocal8Bit().constData());
                   }
                   saveFileSecureNumEntries++;
				   if (filelist->pNormalFiles) 
				   {
					   SceUtilitySDFileStat *normalfile = Memory::addr < SceUtilitySDFileStat > (filelist->pNormalFiles + saveFileNumEntries * 80);
                       hlesceUtiltySave::statFile(filePath,normalfile); 
					   strcpy (normalfile->fileName, entries.at(i).toLocal8Bit().constData());
				   }
                   saveFileNumEntries++;
                 }//endof if
		  }//endof for()
		  filelist->systemFileNum=systemFileNumEntries;
		  filelist->normalFileNum=saveFileNumEntries;
		  filelist->secureFileNum=saveFileSecureNumEntries;
			  
		  if(entries.size()==0) 
		  {
              param->base.result=SCE_UTILITY_SAVEDATA_ERROR_MC_NO_DATA;
          } 
		  else 
		  {
              param->base.result = 0;
          }

	  }
	  else
	  {
		  errorf(sceUtility, "saveMode FileList: Not a valid pointer to a FileList??");
	  }
  }
  void hleSaveDataTypeLoad(SceUtilitySavedataParam *param,bool readonefile)
  {
      //infof(sceUtility, "Loading. Title: %s Save: %s File: %s", param->titleId, param->userId, param->fileName);
	  QString saveName(param->userId); //get the save name
	  if(!saveName.length())//we need to extract from saveNamelists
	  {
        errorf(sceUtility,"saveName is null");
	  }
	  char savePath[256];
      sprintf(savePath, "ms0/PSP/SAVEDATA/%s%s", param->titleId, param->userId);

	  char saveFileName[256];
      sprintf(saveFileName, "%s/%s", savePath, param->fileName);
      FILE *f = fopen(saveFileName, "rb");
      if (f)
      {
          char *buffer = Memory::addr< char >(param->pDataBuf);
		  param->dataFileSize = fread(buffer, 1, param->dataBufSize, f);
          fclose(f);

          if (param->dataFileSize == 0)
          {
               errorf(sceUtility,"Error loading data. FileSize=0");
          }
          if(!readonefile)
		  {
           hlesceUtiltySave::loadFile(savePath, param->icon0, "ICON0.PNG");
           hlesceUtiltySave::loadFile(savePath, param->icon1, "ICON1.PNG");
           hlesceUtiltySave::loadFile(savePath, param->pic1, "PIC1.PNG");
           hlesceUtiltySave::loadFile(savePath, param->snd0, "SND0.PNG");
           hlesceUtiltySave::loadSfo(savePath, param->systemFile);
		  }
		  param->base.result=0;
	  }
	  else
	  {
	    param->base.result=SCE_UTILITY_SAVEDATA_ERROR_LOAD_NO_DATA;
	  }

  }
  void hleSaveDataTypeSave(SceUtilitySavedataParam *param,bool writeonefile)
  {
      // infof(sceUtility, "Saving. Title: %s Save: %s File: %s", param->titleId, param->userId, param->fileName);
      QString saveName(param->userId); //get the save name
	  if(!saveName.length())//we need to extract from saveNamelists
	  {
        errorf(sceUtility,"saveName is null");
	  }   
       char savePath[256];
       sprintf(savePath, "ms0/PSP/SAVEDATA/%s%s", param->titleId, param->userId);
       // Try to create directories: they will silently fail if already existing.
       QDir().mkpath(savePath);
	   char saveFileName[256];
       sprintf(saveFileName, "%s/%s", savePath, param->fileName);

       FILE *f = fopen(saveFileName, "wb");
       if (f)
       {
		  char *buffer = Memory::addr < char >(param->pDataBuf);
          u32 written = fwrite(buffer, 1, param->dataFileSize, f);
          fclose(f);
          if (written<param->dataFileSize)
          {
              errorf(sceUtility,"Error saving data. Written bytes < dataFileSize");
          }
          if(!writeonefile)
		  {
		    hlesceUtiltySave::saveFile(savePath, param->icon0, "ICON0.PNG");
            hlesceUtiltySave::saveFile(savePath, param->icon1, "ICON1.PNG");
            hlesceUtiltySave::saveFile(savePath, param->pic1, "PIC1.PNG");
            hlesceUtiltySave::saveFile(savePath, param->snd0, "SND0.PNG");
            hlesceUtiltySave::saveSfo(savePath, param->systemFile);
		  }
		  param->base.result=0;
	   }
	   else
	   {
          param->base.result=SCE_UTILITY_SAVEDATA_ERROR_SAVE_ACCESS_ERROR;
	   }
	   
  }
  void hleSaveDataTypeCheckSize(SceUtilitySavedataParam *param)
  {
	  SceUtilitySavedataCheckSize *checksize = Memory::addr < SceUtilitySavedataCheckSize >(param->pCheckSize);
	  u32 totalSizeKb = 0;
	  u32 neededSizeKb = 0;
	  u32 freeSizeKb = mem_stick::getFreeSizeKb();
	  if(checksize->pSecureFiles)
	  {
	    for (u32 i = 0; i < checksize->secureFileNum; i++) 
		{
          SceUtilitySDFileStat2 *securefile = Memory::addr < SceUtilitySDFileStat2 >(checksize->pSecureFiles+i*24);
		  u32 sizeKb = hlesceUtiltySave::bytesToKb(securefile->st_size);
		  QString filename(securefile->fileName);
		  debugf(sceUtility,"Checksize secure filename: %s sizekb = %d",filename.toStdString().c_str(),filename);
		  totalSizeKb += sizeKb;
		}
	  }
	  if(checksize->pNormalFiles)
	  {
		  for (u32 i = 0; i < checksize->normalFileNum; i++) 
		  {
			  SceUtilitySDFileStat2 *normalfile = Memory::addr < SceUtilitySDFileStat2 >(checksize->normalFileNum+i*24);
			  u32 sizeKb = hlesceUtiltySave::bytesToKb(normalfile->st_size);
			  QString filename(normalfile->fileName);
			  debugf(sceUtility,"Checksize filename: %s sizekb = %d",filename.toStdString().c_str(),filename);
			  totalSizeKb += sizeKb;
		  }
	  }
	  // If there's not enough size, we have to write how much size we need.
	  // With enough size, our needed size is always 0.
	  if (totalSizeKb > freeSizeKb) {
		  neededSizeKb = totalSizeKb;
	  }

	  // Free MS size.
	  QString memoryStickFreeSpaceString = mem_stick::getSizeKbString(freeSizeKb);
	  checksize->msClusterSizeByte = mem_stick::getSectorSize();
	  checksize->msFreeCluster= freeSizeKb/mem_stick::getSectorSizeKb();
	  checksize->msFreeSizeKB = freeSizeKb;
	  strcpy(checksize->msFreeSizeStr,memoryStickFreeSpaceString.toLatin1().data());

      // Size needed to write savedata.
	  checksize->createNeedSizeKB=neededSizeKb;
	  strcpy(checksize->createNeedSizeStr,mem_stick::getSizeKbString(neededSizeKb).toLatin1().data());

      // Size needed to overwrite savedata.
	  checksize->overwriteNeedSizeKB=neededSizeKb;
	  strcpy(checksize->overwriteNeedSizeStr,mem_stick::getSizeKbString(neededSizeKb).toLatin1().data());

	  // MODE_GETSIZE also checks if a MemoryStick is inserted and if there're no previous data.
	  if (mem_stick::getState() != SCE_MEMSTICK_INSERTED) 
	  {
		  param->base.result= SCE_UTILITY_SAVEDATA_ERROR_MC_NO_MS;//hmm why not SCE_UTILITY_SAVEDATA_ERROR_SIZES_NO_MS ?
	  } 
	  else if (!hlesceUtiltySave::isPresent(param,QString(param->userId))) 
	  {
		  param->base.result = SCE_UTILITY_SAVEDATA_ERROR_MC_NO_DATA;
	  } 
	  else 
	  {
		  param->base.result = 0;
	  }

  }
  void hleSaveNoMemStick(SceUtilitySavedataParam *param)
  {
	  switch(param->type)
	  {
	   case SCE_UTILITY_SAVEDATA_TYPE_AUTOLOAD: /*mode=0*/
	   case SCE_UTILITY_SAVEDATA_TYPE_LOAD:/*mode=2*/
		   param->base.result=SCE_UTILITY_SAVEDATA_ERROR_LOAD_NO_MS;
		   break;
	   case SCE_UTILITY_SAVEDATA_TYPE_AUTOSAVE: /*mode=1*/
	   case SCE_UTILITY_SAVEDATA_TYPE_SAVE: /*mode=3*/
		  param->base.result=SCE_UTILITY_SAVEDATA_ERROR_SAVE_NO_MS;
		  break;
	  default:
          errorf(sceUtility, "UNIMPLEMENTED sceUtilitySavedataInitStart mode (%i)", param->type);
	      param->base.result=-1;
		  break;
	  }

  }
  void hleSavedata(SceUtilitySavedataParam *param)
  {
	  switch(param->type)
	  {
	  case SCE_UTILITY_SAVEDATA_TYPE_AUTOLOAD: /*mode=0*/
	  case SCE_UTILITY_SAVEDATA_TYPE_LOAD:/*mode=2*/
          infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
          hleSaveDataTypeLoad(param,false);
		  break;
	  case SCE_UTILITY_SAVEDATA_TYPE_AUTOSAVE: /*mode=1*/
	  case SCE_UTILITY_SAVEDATA_TYPE_SAVE: /*mode=3*/
		  infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
		  hleSaveDataTypeSave(param,false);
		  break;
	  case SCE_UTILITY_SAVEDATA_TYPE_LISTLOAD: /*mode=4*/
		  {
		    infof(sceUtility,"sceUtilitySavedataInitStart mode LIST_LOAD");
		    theEmulator.Sc().SavedataLoad(param);  
		    if(param->base.result!=-1) //list load returned either cancel or close button
		    {
             hleSaveDataTypeLoad(param,false);
			 //param->base.result=0;//hmm that is probably not neccesary since Load will return a result
		    }
		    else
		    {
			 errorf(sceUtility,"LISTLOAD canceled.Can't Load");
             param->base.result=SCE_UTILITY_SAVEDATA_ERROR_LOAD_PARAM;
		    } 
		  }
		  break;
     case SCE_UTILITY_SAVEDATA_TYPE_LISTSAVE: /*mode=5*/
		 {
            infof(sceUtility,"sceUtilitySavedataInitStart mode LIST_SAVE");
			theEmulator.Sc().SavedataSave(param);  
		    if(param->base.result!=-1) //list load returned either cancel or close button
		    {
             hleSaveDataTypeSave(param,false);
			 //param->base.result=0;//hmm that is probably not neccesary since Load will return a result
		    }
		    else
		    {
			 errorf(sceUtility,"LISTSAVE canceled.Can't Save");
             param->base.result=SCE_UTILITY_SAVEDATA_ERROR_SAVE_PARAM;
		    } 
		 }
		 break;
	 //case SCE_UTILITY_SAVEDATA_TYPE_LISTDELETE:/*mode=6*/
	 //case SCE_UTILITY_SAVEDATA_TYPE_DELETE:/*mode=7*/
	 case SCE_UTILITY_SAVEDATA_TYPE_SIZES:  //unfinished!
		  infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
          hleSaveDataTypeSize(param);
		  break;
	 //case SCE_UTILITY_SAVEDATA_TYPE_AUTODELETE:/*mode=9*/
	 //case SCE_UTILITY_SAVEDATA_TYPE_SINGLEDELETE:/*mode=10*/
	 //case SCE_UTILITY_SAVEDATA_TYPE_MC_USERIDLIST:/*mode=11*/
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_FILELIST: /*mode=12*/
		  infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
		  hleSaveDataTypeFileList(param);
		  break;
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_CREATEDATA_SECUREFILE:/*mode=13*/
     case SCE_UTILITY_SAVEDATA_TYPE_MC_CREATEDATA_NORMALFILE:/*mode=14*/
		  infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
		  hleSaveDataTypeSave(param,false);
		  break;
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_READ_SECUREFILE:/*mode=15*/
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_READ_NORMALFILE:/*mode=16*/
		  infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
          hleSaveDataTypeLoad(param,true);
		  break;
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_WRITE_SECUREFILE:/*mode=17*/
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_WRITE_NORMALFILE:/*mode=18*/
		  infof(sceUtility,"sceUtilitySavedataInitStart mode (%i)", param->type);
		  hleSaveDataTypeSave(param,true);
		  break;
	 //case SCE_UTILITY_SAVEDATA_TYPE_MC_REMOVE_SECUREFILE:/*mode=19*/
	 //case SCE_UTILITY_SAVEDATA_TYPE_MC_REMOVE_NORMALFILE:/*mode=20*/
	 //case SCE_UTILITY_SAVEDATA_TYPE_MC_DELETEDATA:/*mode=21*/
	 case SCE_UTILITY_SAVEDATA_TYPE_MC_CHECKSIZE:/*mode=22*/
		  infof(sceUtility,"sceUtilitySavedataInitStart mode CHECKSIZE");
		  hleSaveDataTypeCheckSize(param);
		  break;
	 default:
          errorf(sceUtility, "UNIMPLEMENTED sceUtilitySavedataInitStart mode (%i)", param->type);
	      param->base.result=-1;
		  break;
	  }
  }
  

}
