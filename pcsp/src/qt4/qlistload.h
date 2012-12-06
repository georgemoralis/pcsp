#ifndef QLISTLOAD_H
#define QLISTLOAD_H

#include <QDialog>
#include "ui_qlistload.h"
#include "modules/utility/sceUtilitySave.h"

class QListLoad : public QDialog
{
	Q_OBJECT

public:
	QListLoad(QWidget *parent,SceUtilitySavedataParam *param);
	~QListLoad();
	bool Show();
	bool load;
public slots:
	void displayPic1(QListWidgetItem*);
	void displayDesc(QListWidgetItem*);
	void loadButton();
	void cancelButton();
	void reject();

private:
	Ui::QListLoadClass ui;
	SceUtilitySavedataParam *m_param;
	bool isPresent(SceUtilitySavedataParam *param,QString saveName);
	QString getBasePath(QString gameName,QString saveName);
	QStringList getFileList(u32 pUserIds);
	QString getFileName(QString gameName,QString saveName, QString fileName); 
};

#endif // QLISTLOAD_H
