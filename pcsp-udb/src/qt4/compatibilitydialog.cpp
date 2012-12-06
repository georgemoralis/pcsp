#include <QtCore>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "compatibilitydialog.h"

compatibilityDialog::compatibilityDialog(QWidget *parent,QString compDataName)
	: QDialog(parent)
{
	ui.setupUi(this);

	QSqlQuery query;
	query.exec("SELECT name FROM sqlite_master WHERE type IN ('table','view') AND name NOT LIKE 'sqlite_%' UNION ALL SELECT name FROM sqlite_temp_master WHERE type IN ('table','view') ORDER BY 1");
    while(query.next())
	{
       ui.compCombo->addItem(transformDatabaseName(query.value(0).toString()));
	}
	//current item
	ui.compCombo->setCurrentIndex(ui.compCombo->findText(transformDatabaseName(compDataName)));
}

compatibilityDialog::~compatibilityDialog()
{

}
QString compatibilityDialog::transformDatabaseName(QString uglyname)
{
	if(uglyname.startsWith("comp_"))
	{
	 uglyname.replace("comp_","v");
	 uglyname.replace('_',".");
	 return uglyname;
	}
	return "";
}
void compatibilityDialog::createTable()
{
	 bool ok;
     QString inputext = QInputDialog::getText(this, tr("Create a New table"),
		                                  tr("Table Name:"), QLineEdit::Normal,
                                          "v0.", &ok);
	 if(inputext.startsWith("v0."))
	 {
        inputext.replace("v","comp_");
		inputext.replace('.','_');
	 }

     QSqlQuery query;
     query.exec("create table if not exists '" + inputext + "' (id INTEGER PRIMARY KEY, "
               "crc32 varchar(40),"
			   "status int,"
               "gamenotes varchar(256))");
	 //put the new database to combobox
	ui.compCombo->clear();
	query.exec("SELECT name FROM sqlite_master WHERE type IN ('table','view') AND name NOT LIKE 'sqlite_%' UNION ALL SELECT name FROM sqlite_temp_master WHERE type IN ('table','view') ORDER BY 1");
    while(query.next())
	{
       ui.compCombo->addItem(transformDatabaseName(query.value(0).toString()));
	}
	//current item
	ui.compCombo->setCurrentIndex(ui.compCombo->findText(transformDatabaseName(inputext)));

}
void compatibilityDialog::cancelButton()
{
   this->close();
}
void compatibilityDialog::saveButton()
{
   QSettings m_ini("pcsp-udb.ini", QSettings::IniFormat);

   QString currentText = ui.compCombo->currentText();
	 if(currentText.startsWith("v0."))
	 {
        currentText.replace("v","comp_");
		currentText.replace('.','_');
	 }
	 m_ini.setValue("/default/settings/compatibilitydatabase",currentText);
	 QMessageBox::information(this, tr("Remember"), "Remember you should restart pcsp-udb if you changed compatibility version or created a new one");
	 this->close();
}