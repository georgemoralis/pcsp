#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <QDialog>
#include "ui_memorycard.h"

#include "common/types.h"

class memoryCard : public QDialog
{
	Q_OBJECT

public:
	memoryCard(QWidget *parent = 0);
	~memoryCard();
	void RefreshData(QString gamepath);
   
private:
	Ui::memoryCardClass ui;
	QMap<QString, QString> metamap;
	struct memRecords
    {
      QString path;
	  QString ebootfile;
	  QString metafile;
	  u32 icon0offset;
	  u32 icon0size;
	  u32 pic0offset;
	  u32 pic0size;
	  u32 psfoffset;
	  u32 psfsize;
     };
	QMap<u32,memRecords> recordmap;
public slots:
	 void gameDirectoryChanged(int index);
	 bool close();
	 
};

#endif // MEMORYCARD_H
