#ifndef NIDGENERATOR_H
#define NIDGENERATOR_H
#include <QDomDocument>
#include <QtGui/QMainWindow>
#include "ui_nidgenerator.h"
#include "psplibxmlparser.h"
class NIDgenerator : public QMainWindow
{
	Q_OBJECT

public:
	NIDgenerator(QWidget *parent = 0, Qt::WFlags flags = 0);
	~NIDgenerator();
	int ReadXML(QString filename);
	void WriteModuleFileheader(QString modulename);
	void WriteModuleFile(QString modulename);
	void WriteSyscallsheader(QList<QString> modules);
	void WriteNIDmapper(QList<QString> modules);
    QString version;

	public slots:
	void ChooseXML();
	void CreateFiles();
	
 
private:
	Ui::NIDgeneratorClass ui;
	psplibxmlparser handler;
};

#endif // NIDGENERATOR_H
