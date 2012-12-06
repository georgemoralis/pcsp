#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ui_settingsdialog.h"

class settingsDialog : public QDialog
{
	Q_OBJECT

public:
	settingsDialog(QWidget *parent = 0);
	~settingsDialog();
public slots:
     void changePage(QListWidgetItem *current, QListWidgetItem *previous);
	 void SaveAction();
	 void CancelAction();
	 void soundBufferDefault();
private:
	Ui::settingsDialogClass ui;
};

#endif // SETTINGSDIALOG_H
