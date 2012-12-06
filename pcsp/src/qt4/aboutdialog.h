#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "ui_aboutdialog.h"

class aboutDialog : public QDialog
{
	Q_OBJECT

public:
	aboutDialog(QWidget *parent = 0);
	~aboutDialog();

private:
	Ui::aboutDialogClass ui;
};

#endif // ABOUTDIALOG_H
