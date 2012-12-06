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
#ifndef QPcspXmb_H
#define QPcspXmb_H

#include <QtCore>
#include <QtGui>

#include "ui_qpcspxmb.h"

#include "qumdmodel.h"
#include "customfilterproxymodel.h"
class MainWindowThread;
class ProgressCtrl;

class QPcspXmb : public QMainWindow, private Ui::PcspXmbUi
{
    Q_OBJECT

signals:
  void range(int, int);
  void label(const QString &);
  void progress(int);
public:
    QPcspXmb(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~QPcspXmb();
    void refresh();
	void run();
	void runInSeparateThread(QString text);
	QString transformDatabaseName(QString uglyname);
	MainWindowThread *thisThread;
	ProgressCtrl *progressCtrl;
	u32 totalgames;
	u32 gamesInDatabase;
	u32 gamesNotInDatabase;
	QString compDatabaseName;
	

protected:
    QRegion visualRegionForSelection(QItemSelection const &) const { return QRegion(); }
    void closeEvent(QCloseEvent *event);

private slots:
    void onChangeUmdPath();
    void onModelReset();
    void onCurrentChanged(QModelIndex const &index);
    void onDoubleClicked(QModelIndex const &index);
    void onPressedButton();
	void textFilterChanged(QString text);
	void filterRegExpChanged(int column);
	void gameFilterChanged(int status);
	void thisThreadStarted();
	void thisThreadFinished();
	void setStop();
	void startWithDebugger();
	void compatibilityDlg();
	void updateCompatibility();
	void DecryptorCheckBoxChanged(int state);
	


private:
    QString                m_umdisospath;
    QUmdTableModel        *m_sourceModel;
    customFilterProxyModel *m_model;
    QDataWidgetMapper     *m_mapper;
    QItemSelectionModel   *m_selectionModel;
    QSystemTrayIcon       *m_systray;
    QSettings              m_ini;
	bool m_stop;
	bool m_startwithdebugger;
	bool m_enableDecryptor;
};
#include <QThread>
class MainWindowThread : public QThread  
{
  Q_OBJECT
public:
  MainWindowThread(QPcspXmb *mainWindow)
    : mainWindow(mainWindow){};
  virtual ~MainWindowThread(){};
 
  void run() {mainWindow->run();}
protected:
  QPcspXmb *mainWindow;
};

#endif // QPcspXmb_H
