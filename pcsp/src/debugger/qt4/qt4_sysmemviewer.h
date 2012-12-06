#ifndef QT4_SYSMEMVIEWER_H
#define QT4_SYSMEMVIEWER_H

#include <QWidget>
#include "ui_qt4_sysmemviewer.h"

class qt4_SysmemViewer : public QWidget
{
	Q_OBJECT

public:
	qt4_SysmemViewer(QWidget *parent = 0);
	~qt4_SysmemViewer();
	void updateViewer();

private:
	Ui::qt4_SysmemViewerClass ui;
};

#endif // QT4_SYSMEMVIEWER_H
