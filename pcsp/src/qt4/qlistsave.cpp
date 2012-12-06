#include "stdafx.h"
#include "hle/modules/utility/sceUtility.h"
#include "hle/modules/iofilemgr/IoFileMgrForUser.h"
#include "hle/modules/utility/sceUtilitySave.h"
#include "qlistsave.h"
#include "loaders/psf.h"

QListSave::QListSave(QWidget *parent,SceUtilitySavedataParam *param)
	: QDialog(parent)
{
	ui.setupUi(this);
	save=false;
	m_param=param;
    QStringList saveNameList = getFileList(param->pUserIds);
	for (int i=0; i< saveNameList.size(); i++)
	{
		QListWidgetItem *iconslist =new QListWidgetItem(ui.icon0List );
		iconslist->setIcon(QIcon(":/../../Resources/Resources/icon0.png"));//set all icons to default
		QFile icon0(getFileName(QString(param->titleId),saveNameList.at(i),"ICON0.PNG"));
		if(icon0.exists())
		{
            iconslist->setIcon(QIcon(getFileName(QString(param->titleId),saveNameList.at(i),"ICON0.PNG")));
		}
		else if(m_param->pNewData)//check if there is an icon there
		{
#if 0 //TODO!
            SceUtilitySavedataListSaveNewData *newdata = Memory::addr < SceUtilitySavedataListSaveNewData > (m_param->pNewData);
#endif
		}
		FILE *f = fopen(getFileName(QString(param->titleId),saveNameList.at(i),"PARAM.SFO").toLatin1(), "rb");
		QString description="Empty";
        if (f)
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
		iconslist->setData(Qt::UserRole+1,getFileName(QString(param->titleId),saveNameList.at(i),"PIC1.PNG"));
		iconslist->setData(Qt::UserRole+2,saveNameList.at(i));
	}

}

QListSave::~QListSave()
{

}
bool QListSave::Show()
{
  bool result = exec() == QDialog::Accepted;
  return result;
}
QStringList QListSave::getFileList(u32 pUserIds)
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
QString QListSave::getFileName(QString gameName,QString saveName, QString fileName) 
{
     return getBasePath(gameName,saveName) + fileName;
}
QString QListSave::getBasePath(QString gameName,QString saveName) 
{
   QString path = "ms0/PSP/SAVEDATA/" + gameName;
   if (!(saveName=="<>")) 
   {
      path += saveName;
   }
   path += "/";
   return path;
}
void QListSave::displayPic(QListWidgetItem* list)
{
	QString pic1path = list->data(Qt::UserRole+1).toString();
	QFile pic(pic1path);
	if(pic.exists())
	{
      ui.pic1Label->setPixmap(QPixmap(pic1path));
	}
	else
	{
		ui.pic1Label->setPixmap(QPixmap(QString::fromUtf8(":/../../Resources/Resources/pic1.png")));
	}
}
void QListSave::displayDesc(QListWidgetItem* list)
{
	ui.descLabel->setText(list->data(Qt::UserRole).toString());
	ui.saveButton->setEnabled(true);
}
void QListSave::saveAction()
{
	 QListWidgetItem *current = ui.icon0List->currentItem();
	 if(current->data(Qt::UserRole).toString()!="Empty")//if it is not a new slot and it overwrites a previous
	 {
		 QMessageBox::StandardButton reply;
		 reply = QMessageBox::question(this, "Save Already Exists in slot",
			 "Overwrite Existing data?",QMessageBox::Yes | QMessageBox::No);
		 if (reply == QMessageBox::Yes)
		 {
			 QString currentSave = current->data(Qt::UserRole+2).toString();
			 strcpy (m_param->userId, currentSave.toLocal8Bit().constData());
			 save=true;
			 close();
		 } 
		 else if (reply == QMessageBox::No)
		 {
              //do nothing
		 }		 
		 else
		 { 
             //do nothing
		 }
			 
	 }
	 else //create a new slot
	 {
		 QString currentSave = current->data(Qt::UserRole+2).toString();
		 strcpy (m_param->userId, currentSave.toLocal8Bit().constData());
		 save=true;
		 close();
	 }

}
void QListSave::cancelAction()
{
	m_param->base.result=-1;//fake result
    close();
}
void QListSave::reject()
{
	if(!save)
	{
     m_param->base.result=-1;
	}
    QDialog::reject();
}
