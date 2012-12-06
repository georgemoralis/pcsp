#ifndef LOGCONFIGURE_H
#define LOGCONFIGURE_H

#include <QDialog>
#include "ui_logconfigure.h"

class logConfigure : public QDialog
{
	Q_OBJECT

public:
	logConfigure(QWidget *parent = 0);
	~logConfigure();
private slots:
	void SaveLogButton();
private:
	Ui::logConfigureClass ui;
};

#endif // LOGCONFIGURE_H
