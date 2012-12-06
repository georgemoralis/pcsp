#ifndef COMPATIBILITYDIALOG_H
#define COMPATIBILITYDIALOG_H

#include <QDialog>
#include "ui_compatibilitydialog.h"

class compatibilityDialog : public QDialog
{
	Q_OBJECT

public:
	compatibilityDialog(QWidget *parent = 0,QString compDataName="");
	~compatibilityDialog();
	QString transformDatabaseName(QString uglyname);

	private slots:
		void createTable();
		void cancelButton();
		void saveButton();
private:
	Ui::compatibilityDialogClass ui;
};

#endif // COMPATIBILITYDIALOG_H
