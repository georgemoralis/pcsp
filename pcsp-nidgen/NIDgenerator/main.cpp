#include "stdafx.h"
#include "psplibxmlparser.h"
#include "nidgenerator.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NIDgenerator w;
	w.show();
	return a.exec();
}
