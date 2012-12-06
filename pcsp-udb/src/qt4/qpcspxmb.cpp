/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "qpcspxmb.h"
#include <QtCore>
#include <QtGui>
#include <qtconcurrentrun.h>

#include "types.h"
#include "../loaders.h"
#include <stdio.h>
#include "ProgressCtrl.h"
#include "qumdmodel.h"
#include "compatibilitydialog.h"

QPcspXmb::QPcspXmb(QWidget *parent, Qt::WFlags flags)
:   QMainWindow(parent, flags)
,   Ui::PcspXmbUi()
,   m_selectionModel(0)
,   m_ini("pcsp-udb.ini", QSettings::IniFormat)
,   thisThread(NULL)
,   progressCtrl(NULL)
,   m_stop(false)
,   totalgames(0)
,   gamesInDatabase(0)
,   gamesNotInDatabase(0)
{
    setupUi(this);
	QPoint pos = m_ini.value("pos", QPoint(200, 200)).toPoint();
    QSize size = m_ini.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
    m_startwithdebugger = m_ini.value("/default/settings/startwithdebugger",false).toBool();
	m_enableDecryptor= m_ini.value("/default/settings/enabledecryptor",false).toBool();
	compDatabaseName=m_ini.value("/default/settings/compatibilitydatabase","comp_0_3_0").toString();
	versionCompLabel->setText(transformDatabaseName(compDatabaseName));
	if(m_startwithdebugger)
	{
        actionStart_With_Debugger->setChecked(true);
	}
	if(m_enableDecryptor)
	{
         internalDecryptCheck->setChecked(true);
	}
    m_umdisospath = m_ini.value("/default/games/path").toString();
    m_sourceModel = new QUmdTableModel(m_umdisospath, this);

    m_model = new customFilterProxyModel(this);
    m_model->setSourceModel(m_sourceModel);
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->addMapping(discIdEdit,   1);
    m_mapper->addMapping(regionEdit,   2);
    m_mapper->addMapping(firmwareEdit, 3);
	m_mapper->addMapping(publishEdit,  4);

    m_mapper->toFirst();
    
	m_selectionModel = gameList->selectionModel();

    connect(m_model, SIGNAL(modelReset()), this, SLOT(onModelReset()));

    gameList->setModel(m_model);
    QHeaderView *header = gameList->header();
    header->setStretchLastSection(true);
    header->setResizeMode(QHeaderView::ResizeToContents);

    connect(gameList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoubleClicked(QModelIndex)));
    connect(runButton, SIGNAL(clicked()), this, SLOT(onPressedButton()));


    QMenu *menu = new QMenu(tr("Settings"), this);
    QAction *action1 = new QAction(tr("Change UMD Games folder"), this);
    connect(action1, SIGNAL(triggered()), this, SLOT(onChangeUmdPath()));
    menu->addAction(action1);
    m_systray = new QSystemTrayIcon(QIcon(":/icons/pcsp.ico"), this);
    connect(m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showNormal()));
    m_systray->setContextMenu(menu);
    m_systray->show();

    if (m_umdisospath.isEmpty())
    {
        onChangeUmdPath();
    }
    else
    {
        refresh();
    }
}

QPcspXmb::~QPcspXmb()
{
}
void QPcspXmb::closeEvent(QCloseEvent *)
{
  m_ini.setValue("pos", pos());
  m_ini.setValue("size", size());
  if (thisThread) {
    delete thisThread;
    thisThread = NULL;
  }
  if (progressCtrl) {
    delete progressCtrl;
    progressCtrl = NULL;
  }
}

void QPcspXmb::onModelReset()
{
    if (m_selectionModel)
    {
        delete m_selectionModel;
    }

    m_selectionModel = new QItemSelectionModel(m_model, this);
    gameList->setSelectionModel(m_selectionModel);
	gameList->setColumnWidth(0,250);
    gameList->setColumnWidth(1,80);
	gameList->setColumnWidth(2,60);
    gameList->setColumnWidth(3,40);
	gameList->hideColumn(5);

    connect(m_selectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex)));
}
bool isecrypted;
void QPcspXmb::DecryptorCheckBoxChanged(int state)
{
    if(actionStart_With_Debugger->isChecked())
   {
      m_ini.setValue("/default/settings/enabledecryptor","true");
	  m_enableDecryptor=true;
   }
   else
   {
      m_ini.setValue("/default/settings/enabledecryptor","false");
	  m_enableDecryptor=false;
   }
     if(isecrypted)
	 {
		if(!internalDecryptCheck->isChecked())
		{
         QString decryptedboot = "decrypted/" + discIdEdit->text() + ".bin";
         QFile   decrypt(decryptedboot);
         if (!decrypt.exists()) //no decrypt file found
         {
             runButton->setEnabled(false); 
			 statustext->setText("Decrypted file not found.Game can't run!!");
			 
         }
		 else
		 {
            runButton->setEnabled(true); 
			statustext->setText("Decrypted file available.");
		 }
		}
		else
		{
            runButton->setEnabled(true); 
			statustext->setText("Using internal decryptor");
		}
	 }
}
void QPcspXmb::onCurrentChanged(QModelIndex const &index)
{
     m_mapper->setCurrentModelIndex(index);
	 icon0pic->setPixmap(QPixmap(index.data(Qt::UserRole+1).toString()));
	 coverpic->setPixmap(QPixmap(index.data(Qt::UserRole+2).toString()));
	 coverpicback->setPixmap(QPixmap(index.data(Qt::UserRole+3).toString()));
     previewpic1->setPixmap(QPixmap(index.data(Qt::UserRole+4).toString()));
	 previewpic2->setPixmap(QPixmap(index.data(Qt::UserRole+5).toString()));
     languageEdit->setText(index.data(Qt::UserRole+6).toString());
	 genreEdit->setText(index.data(Qt::UserRole+7).toString());
	 crc32Edit->setText(index.data(Qt::UserRole+8).toString());
	 QString status = index.data(Qt::UserRole+9).toString();
	 statusEdit->setText(status);

	 QString gamesize = index.data(Qt::UserRole+10).toString();
	 bool ok;
	 int sizeinbytes = gamesize.toInt(&ok, 10); 
     float gametoMB = (float)sizeinbytes /1048576;
	 QString floatsize;
	 floatsize.setNum( gametoMB);
	 gameSizeEdit->setText(gamesize +" (" + floatsize + " MB)");

	 QString umdfilename = index.data(Qt::UserRole).toString();
	 QStringList list1 = umdfilename.split("/");
	 QString filename = list1.at(list1.size()-1).toLocal8Bit().constData();
	 umdfilenameEdit->setText(filename);

	 if(status.startsWith("Encrypt")) //game is encrypted
	 {
		 isecrypted=true;
		if(!internalDecryptCheck->isChecked())
		{
         QString decryptedboot = "decrypted/" + discIdEdit->text() + ".bin";
         QFile   decrypt(decryptedboot);
         if (!decrypt.exists()) //no decrypt file found
         {
             runButton->setEnabled(false); 
			 statustext->setText("Decrypted file not found.Game can't run!!");
			 
         }
		 else
		 {
            runButton->setEnabled(true); 
			statustext->setText("Decrypted file available.");
		 }
		}
		else
		{
            runButton->setEnabled(true); 
			statustext->setText("Using internal decryptor");
		}
	 }
	 else
	 {
       
		isecrypted=false;	
        runButton->setEnabled(true); 
		statustext->setText("");
	 }
	 //compatibility tab
	 int game=0;
	 QString gamenotes="There aren't any info for the game on compatibility list";
	  QSqlQuery query;
	 query.exec("SELECT * FROM '" + compDatabaseName + "' where crc32 = '" + crc32Edit->text() + "'");     
	 if(query.first())
	 {
		 game= query.value(2).toInt();
	     gamenotes = query.value(3).toString();
	 }
	 gameNotesEdit->setText(gamenotes);
	 if(game==0) gamestatusCombo->setCurrentIndex(6);
	 if(game==1) gamestatusCombo->setCurrentIndex(5);
	 if(game==2) gamestatusCombo->setCurrentIndex(4);
	 if(game==3) gamestatusCombo->setCurrentIndex(3);
	 if(game==4) gamestatusCombo->setCurrentIndex(2);
	 if(game==5) gamestatusCombo->setCurrentIndex(1);
     if(game==6) gamestatusCombo->setCurrentIndex(0);
}

void QPcspXmb::onDoubleClicked(QModelIndex const &index)
{
    QString umdpath = index.data(Qt::UserRole).toString();
    QString discID  = index.sibling(index.row(), 1).data(Qt::DisplayRole).toString();  
    QProcess launcher(this);
    QStringList arguments;
    arguments << "-umd" << umdpath;
	if(m_startwithdebugger)
	{
	  arguments << "-debug" << "true";
	}
	else
	{
      arguments << "-debug" << "false";
	}
	if(m_enableDecryptor)
	{
	  arguments << "-decrypt" << "true";
	}
	else
	{
      arguments << "-decrypt" << "false";
	}
    if (!launcher.startDetached("pcsp-" + discID, arguments))
    {
        if (!launcher.startDetached("pcsp", arguments))
        {
            QMessageBox::critical(0, tr("PCSP - XMB"), tr("Cannot find an emulator to play %1!").arg(index.sibling(index.row(), 0).data(Qt::DisplayRole).toString()));
        }
    }
}
void QPcspXmb::updateCompatibility()
{
   int gamestatus=0;
   if(gamestatusCombo->currentIndex()==6) gamestatus=0;
   if(gamestatusCombo->currentIndex()==5) gamestatus=1;
   if(gamestatusCombo->currentIndex()==4) gamestatus=2;
   if(gamestatusCombo->currentIndex()==3) gamestatus=3;
   if(gamestatusCombo->currentIndex()==2) gamestatus=4;
   if(gamestatusCombo->currentIndex()==1) gamestatus=5;
   if(gamestatusCombo->currentIndex()==0) gamestatus=6;
   QString gameinfo = gameNotesEdit->toPlainText();
   QString crc = crc32Edit->text();
   QSqlQuery query;
   
   query.prepare("UPDATE '" + compDatabaseName + "' SET status =? ,gamenotes = ? WHERE crc32 = ?");
   query.addBindValue(gamestatus);
   query.addBindValue(gameinfo);
   query.addBindValue(crc);
   query.exec();

    //update model dynamically with the new status
    QModelIndex selection = m_selectionModel->currentIndex();//find which line is selected
    QModelIndex index = m_model->index(selection.row(), 5, QModelIndex());//get the index for column 5
    m_model->setData(index,gamestatus);

}
void QPcspXmb::onPressedButton()
{
    QModelIndex index = m_selectionModel->currentIndex();
    onDoubleClicked(index);
}

void QPcspXmb::refresh()
{
	 if (!thisThread) thisThread = new MainWindowThread(this);
     if(thisThread->isRunning()) return;// false;
     connect(thisThread, SIGNAL(started()), this, SLOT(thisThreadStarted()), Qt::BlockingQueuedConnection);
     connect(thisThread, SIGNAL(finished()), this, SLOT(thisThreadFinished()), Qt::BlockingQueuedConnection);
     connect(thisThread, SIGNAL(terminated()), this, SLOT(thisThreadFinished()), Qt::BlockingQueuedConnection);
     if (!progressCtrl) progressCtrl = new ProgressCtrl(this);
     progressCtrl->show();
	 m_stop = false;
	 
	 thisThread->start();
}
void QPcspXmb::thisThreadStarted()
{

    connect(this, SIGNAL(range(int, int)), progressCtrl->progress(), SLOT(setRange(int, int)), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(progress(int)), progressCtrl->progress(), SLOT(setValue(int)), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(label(const QString &)), progressCtrl->label(), SLOT(setText(const QString &)), Qt::BlockingQueuedConnection);
    connect(progressCtrl->stop(), SIGNAL(clicked()), this, SLOT(setStop()));

}
void QPcspXmb::thisThreadFinished()
{


    disconnect(this, SIGNAL(range(int, int)), progressCtrl->progress(), SLOT(setRange(int, int)));
    disconnect(this, SIGNAL(progress(int)), progressCtrl->progress(), SLOT(setValue(int)));
    disconnect(this, SIGNAL(label(const QString &)), progressCtrl->label(), SLOT(setText(const QString &)));
    disconnect(progressCtrl->stop(), SIGNAL(clicked()), this, SLOT(setStop()));
    progressCtrl->hide(); 
    progressCtrl->progress()->setValue(0);
	gamesNotInDatabase = totalgames - gamesInDatabase;
	QString gamesNotInDatabaseS;
	QString gamesInDatabaseS;
	QString totalgamesS;
	gamesNotInDatabaseS.setNum(gamesNotInDatabase);
	totalgamesS.setNum(totalgames);
	gamesInDatabaseS.setNum(gamesInDatabase);
	QLabel *label = new QLabel(this);
	label->setText("Total Games: " + totalgamesS);
	QLabel *label2 = new QLabel(this);
	label2->setText("In Database : " + gamesInDatabaseS);
	QLabel *label3 = new QLabel(this);
	label3->setText("Not In Database : " + gamesNotInDatabaseS);
	statusbar->addWidget(label,0);
    statusbar->addWidget(label2,0);
    statusbar->addWidget(label3,0);
}
void QPcspXmb::setStop()
{
  m_stop = true;
  if (progressCtrl) progressCtrl->hide();
}
void QPcspXmb::run()
{
	QMutex mutex;
    QMutex mutex2;
    QWaitCondition finishmutex;
    QDir dir(m_umdisospath);
    QFileInfoList entries(dir.entryInfoList(QStringList() << "*.ISO" << "*.CSO", QDir::Files, QDir::Name|QDir::IgnoreCase));
	emit range(0, entries.size()-1);
	int i=0;

	      m_sourceModel->m_infos.clear();
         m_sourceModel->startupdatemodel();
		  QListIterator< QFileInfo > entry(entries);
          if (entry.hasNext())
          {
            while (entry.hasNext())
            {
				
				emit progress(i); 
                QFileInfo fi = entry.next();
                emit label(tr("Loading %1...").arg(fi.baseName()));
				mutex.lock();
                UmdInfos infos(fi,compDatabaseName);
                m_sourceModel->m_infos.push_back(infos);
                if (!m_sourceModel->m_infos.last().id.size())
                {
                    m_sourceModel->m_infos.removeLast();
                }
				i++;
				
				m_sourceModel->endupdatemodel();
				if(infos.isInDatabase)
				{
				   gamesInDatabase++;
				}
				totalgames++;
                if (m_stop) break;
				mutex.unlock();
				
            }
	      }
          m_sourceModel->endupdatemodel();
		 
		  
}

void QPcspXmb::onChangeUmdPath()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString newPath = QFileDialog::getExistingDirectory(0, tr("Select UMD Games folder"), m_umdisospath, options);
    if (newPath.size())
    {
        m_umdisospath = newPath;
        m_ini.setValue("/default/games/path", m_umdisospath);
		QFile cache("cache.dat");
		if(cache.remove())
		{
		}
        refresh();
    }
}

void QPcspXmb::runInSeparateThread(QString text)
{
     QRegExp regExp(text,Qt::CaseInsensitive, QRegExp::PatternSyntax(2));
    m_model->setFilterRegExp(regExp);
}
void QPcspXmb::textFilterChanged(QString text)
{
  QFutureWatcher<void> futureWatcher;
  QFuture<void> future = QtConcurrent::run(this,&QPcspXmb::runInSeparateThread,text);
  futureWatcher.setFuture(future);
  futureWatcher.waitForFinished();

}
void QPcspXmb::filterRegExpChanged(int column)
{ 
     m_model->setGenericFilter(column);
}
void QPcspXmb::gameFilterChanged(int status)
{
   if(status==0) m_model->setGameFilter("10");
   if(status==1) m_model->setGameFilter("6"); //Fully playable
   if(status==2) m_model->setGameFilter("5"); //Playable
   if(status==3) m_model->setGameFilter("4"); //Half Playable
   if(status==4) m_model->setGameFilter("3"); //Intro
   if(status==5) m_model->setGameFilter("2"); //Loadable
   if(status==6) m_model->setGameFilter("1");//Not Loadable
   if(status==7) m_model->setGameFilter("0");//No Info

}
void QPcspXmb::startWithDebugger()
{
   if(actionStart_With_Debugger->isChecked())
   {
      m_ini.setValue("/default/settings/startwithdebugger","true");
	  m_startwithdebugger=true;
   }
   else
   {
      m_ini.setValue("/default/settings/startwithdebugger","false");
	  m_startwithdebugger=false;
   }
}
QString QPcspXmb::transformDatabaseName(QString uglyname)
{
	if(uglyname.startsWith("comp_"))
	{
	 uglyname.replace("comp_","v");
	 uglyname.replace('_',".");
	 return uglyname;
	}
	return "";
}
void QPcspXmb::compatibilityDlg()
{
   compatibilityDialog *dlg = new compatibilityDialog(this,compDatabaseName);
   dlg->exec();
   compDatabaseName=m_ini.value("/default/settings/compatibilitydatabase","comp_0_3_0").toString();
}
