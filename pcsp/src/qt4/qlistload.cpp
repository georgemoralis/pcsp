#include "stdafx.h"
#include "hle/modules/utility/sceUtility.h"
#include "hle/modules/iofilemgr/IoFileMgrForUser.h"
#include "hle/modules/utility/sceUtilitySave.h"
#include "qlistload.h"
#include "loaders/psf.h"

QListLoad::QListLoad(QWidget *parent,SceUtilitySavedataParam *param)
	: QDialog(parent)
{
	ui.setupUi(this);
	load=false;
    m_param=param;
	QStringList saveNameList = getFileList(param->pUserIds);
	// Search for valid saves.
	QStringList validNames= QStringList();
	for (int i = 0; i < saveNameList.size(); i++) 
	{
	   if (isPresent(param,saveNameList.at(i))) 
	   {
            validNames.append(saveNameList.at(i));
         }
    }
	for (int i=0; i< validNames.size(); i++)
	{
		QListWidgetItem *iconslist =new QListWidgetItem(ui.icon0List );
		iconslist->setIcon(QIcon(":/../../Resources/Resources/icon0.png"));//set all icons to default
		QFile icon0(getFileName(QString(param->titleId),validNames.at(i),"ICON0.PNG"));
		if(icon0.exists())
		{
          iconslist->setIcon(QIcon(getFileName(QString(param->titleId),validNames.at(i),"ICON0.PNG")));
		}
		FILE *f = fopen(getFileName(QString(param->titleId),validNames.at(i),"PARAM.SFO").toLatin1(), "rb");
		QString description="Not Present";
		if(f)
		{
            fseek(f, 0, SEEK_END);
            u32 fptrsize = ftell(f);
            rewind(f);
            u8 *fptr = new u8[fptrsize];

            fread(fptr, 1, fptrsize, f);

            psf_loader *psf = new psf_loader;

            psf->read(fptr);

            QString str1 = psf->getPrintableString("SAVEDATA_DETAIL");
            QString str2 = psf->getPrintableString("SAVEDATA_TITLE");       
            QString str3 = psf->getPrintableString("TITLE");
			description = str3 + "\n" + str2 + "\n" + str1;        
			delete psf;
            fclose(f);
		}
		iconslist->setData(Qt::UserRole,description);
		iconslist->setData(Qt::UserRole+1,getFileName(QString(param->titleId),validNames.at(i),"PIC1.PNG"));
		iconslist->setData(Qt::UserRole+2,validNames.at(i));
		
	}
}

QListLoad::~QListLoad()
{

}
bool QListLoad::Show()
{
  bool result = exec() == QDialog::Accepted;
  return result;
}
void QListLoad::loadButton()
{
     QListWidgetItem *current = ui.icon0List->currentItem();
	 QString currentSave = current->data(Qt::UserRole+2).toString();
	 strcpy (m_param->userId, currentSave.toLocal8Bit().constData());
	 load=true;
	 close();
}
void QListLoad::cancelButton()
{
	m_param->base.result=-1;//fake result
  close();
}
void QListLoad::displayPic1(QListWidgetItem* list)
{
	QString pic1path = list->data(Qt::UserRole+1).toString();
	QFile pic(pic1path);
	if(pic.exists())
	{
      ui.pic1Label->setPixmap(QPixmap(pic1path));
	}
}
void QListLoad::displayDesc(QListWidgetItem* list)
{
    ui.descriptionLabel->setText(list->data(Qt::UserRole).toString());
	ui.selectBut->setEnabled(true);
}
QStringList QListLoad::getFileList(u32 pUserIds)
{
	QStringList saveNameList = QStringList();
	bool endOfList = false;
    for (int i = 0; !endOfList; i += 20) 
	{
           QString saveNameItem = QString::fromLocal8Bit(Memory::addrb(pUserIds+i));
           if (saveNameItem.length() == 0) 
		   {
                endOfList = true;
           } 
		   else 
		   {
                saveNameList.append(saveNameItem);
           }
     }
	 return saveNameList;
}
QString QListLoad::getBasePath(QString gameName,QString saveName) 
{
   QString path = "ms0/PSP/SAVEDATA/" + gameName;
   if (!(saveName=="<>")) 
   {
      path += saveName;
   }
   path += "/";
   return path;
}
bool QListLoad::isPresent(SceUtilitySavedataParam *param,QString saveName)
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
QString QListLoad::getFileName(QString gameName,QString saveName, QString fileName) 
{
     return getBasePath(gameName,saveName) + fileName;
}
void QListLoad::reject()
{
	if(!load)
	{
      m_param->base.result=-1;
	}
   QDialog::reject();
}
