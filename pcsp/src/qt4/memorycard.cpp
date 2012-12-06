#include "stdafx.h"
#include "memorycard.h"
#include <QDir>
#include <QFile>
#include <memory>
#include "loaders/pbp.h"
#include "loaders/loaders.h"
#include "settings.h"


memoryCard::memoryCard(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QDir gamedir("ms0/PSP/");
	gamedir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QFileInfoList list = gamedir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
	{
         QFileInfo fileInfo = list.at(i);
		 if(fileInfo.fileName().startsWith("GAME"))
		 {
             ui.gameDirectory->addItem(fileInfo.fileName());
		 }
	}
	if(settings.mMemcardPath.isEmpty())
		settings.mMemcardPath="GAME";
	ui.gameDirectory->setCurrentIndex(ui.gameDirectory->findText(settings.mMemcardPath));
	QString path = "ms0/PSP/" + settings.mMemcardPath +"/";
	RefreshData(path);

}
void memoryCard::RefreshData(QString gamepath)
{
	QVector<QString> programs; //stores eboot.php
	QVector<QString> metaprograms;//stores eboot.php from metadirs
	QVector<QString> gamedir;
	QVector<QString> metadir;
	//clear the previous
	programs.clear();
	metaprograms.clear();
	gamedir.clear();
	metadir.clear();
	recordmap.clear();
	metamap.clear();
	ui.icon0list->clear();
	ui.gameNameEdit->clear();
	ui.ebootPathEdit->clear();
	ui.pic1label->clear();

	QDir path(gamepath);
	if(!path.exists())
	{
		//TODO error message
        return;
	}
	path.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QFileInfoList list = path.entryInfoList();
    for (int i = 0; i < list.size(); ++i) //first scan for kxpoint
	{
         QFileInfo fileInfo = list.at(i);
		 if(fileInfo.fileName().startsWith("%") || fileInfo.fileName().endsWith("%"))//scan all metafiles first
		 {
			 //search if metafile dir has an eboot file
             QString programfile = fileInfo.absoluteFilePath() + "/" + "eboot.pbp";
			 QFile program(programfile);
			 if(program.exists())
			 {
			     QString removepercent = fileInfo.fileName();
				 removepercent.remove(QChar('%'), Qt::CaseInsensitive);
				 metamap.insert(removepercent,fileInfo.fileName());//map the metadir with the dir that should exist without %%

			 }
		 }
	}
	int count=0;
    for (int i = 0; i < list.size(); ++i) //scan normal dirs
	{
		 
         QFileInfo fileInfo = list.at(i);
		 if(!fileInfo.fileName().startsWith("%") && !fileInfo.fileName().endsWith("%"))//ignore kxploit dirs
		 {
		    memRecords &record = recordmap[count];//get a new record
            QMap<QString, QString>::const_iterator i = metamap.find(fileInfo.fileName());//search if filename exists in metamap
            while (i != metamap.end() && i.key() == fileInfo.fileName()) 
			{
				//we found a meta!!
			   record.metafile = gamepath + i.value() + "/eboot.pbp";
			   std::auto_ptr<pbp> pbpfile(new pbp());
			   pbpfile->open (record.metafile.toLatin1().data());
			   if(pbpfile->isValid())
			   {
				 record.icon0offset=pbpfile->pbpheader->offset_icon0_png;
				 record.icon0size=pbpfile->size_icon0_png;
				 record.pic0offset=pbpfile->pbpheader->offset_pic0_png;
				 record.pic0size=pbpfile->size_pic0_png;
				 record.psfoffset=pbpfile->pbpheader->offset_param_sfo;
				 record.psfsize=pbpfile->size_param_sfo;
			   }
			   else //something is wrong with the kxploint pbp file set all zero for sure.
			   {
		         record.icon0offset=0;
				 record.icon0size=0;
				 record.pic0offset=0;
				 record.pic0size=0;
				 record.psfoffset=0;
				 record.psfsize=0;
			   }
			   
			   ++i;
			}
			//open the normal pbp for reading
			record.ebootfile=gamepath + fileInfo.fileName() + "/eboot.pbp";
			std::auto_ptr<pbp> pbpfile1(new pbp());
			pbpfile1->open (record.ebootfile.toLatin1().data());
			if(pbpfile1->isValid() && record.metafile.isEmpty())
			{
				//get the data from eboot.pbp
				 record.icon0offset=pbpfile1->pbpheader->offset_icon0_png;
				 record.icon0size=pbpfile1->size_icon0_png;
				 record.pic0offset=pbpfile1->pbpheader->offset_pic0_png;
				 record.pic0size=pbpfile1->size_pic0_png;
				 record.psfoffset=pbpfile1->pbpheader->offset_param_sfo;
				 record.psfsize=pbpfile1->size_param_sfo;
			}
			else if(record.metafile.isEmpty())//something is wrong with pbp or probably it is an elf..
			{
		         record.icon0offset=0;
				 record.icon0size=0;
				 record.pic0offset=0;
				 record.pic0size=0;
				 record.psfoffset=0;
				 record.psfsize=0;
			}
			count++;
		}
	    
	}
    QMap<u32,memRecords>::const_iterator iter;
	int counter=0;
	for(iter = recordmap.begin(); iter !=recordmap.end(); ++iter) 
	{
         QListWidgetItem *iconslist =new QListWidgetItem(ui.icon0list );
		 iconslist->setIcon(QIcon(":/../../Resources/Resources/icon0.png"));//set all icons to default
		 if(!iter.value().metafile.isEmpty())//if we have a meta dir..
		 {
            FILE *f = fopen(iter.value().metafile.toLatin1().data(),"rb");
			u8 *readptr = new u8[iter.value().icon0size];
			fseek(f,iter.value().icon0offset,SEEK_SET);
			fread(readptr,1,iter.value().icon0size,f);
			fclose(f);
            QImage image;
            image.loadFromData(readptr,iter.value().icon0size);
            iconslist->setIcon(QIcon(QPixmap::fromImage(image)));
			delete[] readptr;
		 }
		 else //read from normal ebootfile
		 {
            if(iter.value().icon0size!=0)//check if there is a icon first!
			{
				 FILE *f = fopen(iter.value().ebootfile.toLatin1().data(),"rb");
				 u8 *readptr = new u8[iter.value().icon0size];
				 fseek(f,iter.value().icon0offset,SEEK_SET);
				 fread(readptr,1,iter.value().icon0size,f);
				 fclose(f);
				 QImage image;
                 image.loadFromData(readptr,iter.value().icon0size);
				 iconslist->setIcon(QIcon(QPixmap::fromImage(image)));
				 delete[] readptr;
			}
		 }
		 iconslist->setData(Qt::UserRole,iter.value().ebootfile);
		 iconslist->setData(Qt::UserRole+1,iter.value().metafile);
		 iconslist->setData(Qt::UserRole+2,iter.value().pic0size);
         iconslist->setData(Qt::UserRole+3,iter.value().pic0offset);
		 iconslist->setData(Qt::UserRole+4,iter.value().psfoffset);
		 iconslist->setData(Qt::UserRole+5,iter.value().psfsize);
		 ui.icon0list->insertItem(counter+1,iconslist);
		 counter++;
	}

}
memoryCard::~memoryCard()
{

}
void memoryCard::gameDirectoryChanged(int index)
{
   
   QString path = "ms0/PSP/" + ui.gameDirectory->itemText(index) +"/";
   RefreshData(path);

}

bool memoryCard::close()
{	
  settings.mMemcardPath=ui.gameDirectory->currentText();
  settings.SaveSettings();
  QWidget::close();
  return true;
}



