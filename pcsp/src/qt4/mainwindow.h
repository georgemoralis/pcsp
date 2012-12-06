#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include <QtGui/QMainWindow>
#include <QObject>
#include "graphicscene.h"

#include "ui_emuwindow.h"
// #include "ui_mainwindow.h"
#include "qinputsystem.h"

#include "emulator.h"
#include "renderer.h"

struct SceUtilityOskParam;
struct SceUtilityMsgDialogParam;

class mainWindow  : public QMainWindow
{
	Q_OBJECT

public:
	mainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainWindow();

	void center();

private:
	Ui::MainWindow ui;
	QInputSystem *theInputSystem;
	
	bool event(QEvent *event);

public slots:
    void onCritical(QString const &caption, QString const &message);
    void onWarning(QString const &caption, QString const &message);
    
    void onOsk(SceUtilityOskParam *param);
    void onMsgDialog(SceUtilityMsgDialogParam *param);
    void onSavedataSave(SceUtilitySavedataParam *param);
	void onSavedataLoad(SceUtilitySavedataParam *param);

	void openDebugger();

private slots:
	void menuOpen();
	void menuExit();
	void menuRun();
	void menuPause();
	void menuReset();
	void updateFPS();
	void menuVSYNC();
    void menuUseShaders();
	void menuConfigureController();
    void menuOpenMemCard();
	void menuAbout();
	void menuOpenUMD();
	void menuOpenDebugger();
	void menuAlwaysOnTop();
	void menuSettings();
	void menuScreenshot();
	void menuMuteSound();
    void menuFullscreen();

protected:
	void resizeEvent(QResizeEvent* e);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent * event);
	void closeEvent(QCloseEvent *event);
};

class LoadedEvent : public QEvent
{
public:
    LoadedEvent() : QEvent(Type(QEvent::User +1)) {}

    bool allLoaded() { return theEmulator.StartUp(); }
};

#endif // MAINWINDOW_H
