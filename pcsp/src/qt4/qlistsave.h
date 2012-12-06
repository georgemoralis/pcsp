#ifndef QLISTSAVE_H
#define QLISTSAVE_H

#include <QDialog>
#include "ui_qlistsave.h"
#include "modules/utility/sceUtilitySave.h"

class QListSave : public QDialog
{
	Q_OBJECT

public:
	QListSave(QWidget *parent,SceUtilitySavedataParam *param);
	~QListSave();
	bool Show();
	bool save;
  
public slots:
	void displayPic(QListWidgetItem*);
	void displayDesc(QListWidgetItem*);
	void saveAction();
	void cancelAction();
	void reject();
private:
	Ui::QListSaveClass ui;
	SceUtilitySavedataParam *m_param;
	QStringList getFileList(u32 pUserIds);
	QString getFileName(QString gameName,QString saveName, QString fileName);
	QString getBasePath(QString gameName,QString saveName);

};

#endif // QLISTSAVE_H
