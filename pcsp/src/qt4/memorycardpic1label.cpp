#include "stdafx.h"
#include "memorycardpic1label.h"

memorycardPic1Label::memorycardPic1Label(QWidget *parent)
	: QLabel(parent)
{

}

memorycardPic1Label::~memorycardPic1Label()
{

}
void memorycardPic1Label::displayPic(QListWidgetItem* list)
{
  QLabel::setPixmap(QPixmap(QString::fromUtf8(":/../../Resources/Resources/pic1.png")));//default for every demo
  QString ebootfile = list->data(Qt::UserRole).toString();
  QString metafile = list->data(Qt::UserRole+1).toString();
  u32 pic0size   = list->data(Qt::UserRole+2).toInt();
  u32 pic0offset = list->data(Qt::UserRole+3).toInt();
  if(!metafile.isEmpty())
  {
    if(pic0size!=0)
	{
			FILE *f = fopen(metafile.toLatin1().data(),"rb");
			u8 *readptr = new u8[pic0size];
			fseek(f,pic0offset,SEEK_SET);
			fread(readptr,1,pic0size,f);
			fclose(f);
			QImage image;
            image.loadFromData(readptr,pic0size);
			QLabel::setPixmap(QPixmap::fromImage(image));
			delete[] readptr;
	}
  }
  else
  {
    if(pic0size!=0)
	{
			FILE *f = fopen(ebootfile.toLatin1().data(),"rb");
			u8 *readptr = new u8[pic0size];
			fseek(f,pic0offset,SEEK_SET);
			fread(readptr,1,pic0size,f);
			fclose(f);
			QImage image;
            image.loadFromData(readptr,pic0size);
			QLabel::setPixmap(QPixmap::fromImage(image));
			delete[] readptr;
	}
  }

  //TODO i didn't have time to finish it  
}
