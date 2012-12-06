#include "stdafx.h"
#include "memorycardpsflineedit.h"
#include "loaders/psf.h"

memorycardPsfLineEdit::memorycardPsfLineEdit(QWidget *parent)
	: QLineEdit(parent)
{

}

memorycardPsfLineEdit::~memorycardPsfLineEdit()
{

}
void memorycardPsfLineEdit::setpsfInfo(QListWidgetItem* list)
{
  QLineEdit::clear();
  QString ebootfile = list->data(Qt::UserRole).toString();
  QString metafile  = list->data(Qt::UserRole+1).toString();
  u32 psfoffset     = list->data(Qt::UserRole+4).toInt();
  u32 psfsize       = list->data(Qt::UserRole+5).toInt();
  if(!metafile.isEmpty())
  {
    if(psfsize!=0)
	{
		FILE *f = fopen(metafile.toLatin1().data(),"rb");
		u8 *readptr = new u8[psfsize];
		fseek(f,psfoffset,SEEK_SET);
		fread(readptr,1,psfsize,f);
		fclose(f);
		psf_loader *psffile = new psf_loader();
		psffile->read(readptr);
		if(objectName()=="gameNameEdit")
		{
			QLineEdit::setText(psffile->getPrintableString("TITLE"));
		}
        delete psffile;
		delete[] readptr;

	}
  }
  else
  {
    if(psfsize!=0)
	{
		FILE *f = fopen(ebootfile.toLatin1().data(),"rb");
		u8 *readptr = new u8[psfsize];
		fseek(f,psfoffset,SEEK_SET);
		fread(readptr,1,psfsize,f);
		fclose(f);
		psf_loader *psffile = new psf_loader();
		psffile->read(readptr);
		if(objectName()=="gameNameEdit")
		{
			QLineEdit::setText(psffile->getPrintableString("TITLE"));
		}
        delete psffile;
		delete[] readptr;

	}
  }
  if(objectName()=="ebootPathEdit")
  {
			QLineEdit::setText(ebootfile);
  }
}