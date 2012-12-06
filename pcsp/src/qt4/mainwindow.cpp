#include "stdafx.h"
#include "hle/modules/utility/sceUtility.h"
#include "hle/modules/iofilemgr/IoFileMgrForUser.h"
#include "hle/modules/utility/sceUtilitySave.h"
#include "qt4/mainwindow.h"
#include "qt4/openglwidget.h"
#include "qt4/graphicscene.h"
#include <QtGui>

#include "emulator.h"
#include "settings.h"
#include "memorycard.h"
#include "aboutdialog.h"
#include "controllerconfigure.h"
#include "renderer.h"
#include "qinputsystem.h"
#include "settingsdialog.h"

#include "qoskdialog.h"
#include "qlistsave.h"
#include "qlistload.h"
#include "hle/modules/utility/sceUtilityMsgDialog.h"


#ifndef DISABLE_DEBUGGER
#include "debugger/qt4/qt4_pcspdebugger.h"
#endif

mainWindow::mainWindow(QWidget *parent, Qt::WFlags flags)
:   QMainWindow(parent, flags)
{
	ui.setupUi(this);

    theInputSystem = new QInputSystem;
    
    settings.LoadSettings();
	
    if (settings.mVsyncLimiter)
    {
        ui.actionVSYNC_Limiter->setChecked(true);
        menuVSYNC();
    }

    if (settings.mEnableShaders)
    {
        ui.actionUse_OPENGL_Shaders->setChecked(true);
        menuUseShaders();
    }

	if (settings.mMuteSound)
	{
		ui.actionMute_Sound->setChecked(true);
		menuMuteSound();
	}

	if (settings.mAlwaysOnTop)
	{
        ui.actionAlwaysOnTop->setChecked(true);
		menuAlwaysOnTop();
	}

	if (!settings.mSoundBufferCount)
    {
		settings.mSoundBufferCount = 0;
    }

	if (settings.mHackDisableAudioFunctions)
    {
		settings.mHackDisableAudioFunctions = true;
    }

    if (settings.mEnableDecryptor)
	{
		settings.mEnableDecryptor = true;
	}

    if (settings.mFullscreen)
    {
        ui.actionVSYNC_Limiter->setChecked(true);
        menuFullscreen();
    }

    LoadedEvent *loadEvent = new LoadedEvent();
	QApplication::sendEvent(this, loadEvent);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateFPS()));
	timer->start(1000);

    theEmulator.RegisterGuiReceiver(this);	
}

mainWindow::~mainWindow()
{
	settings.SaveSettings();	
	safe_delete(theInputSystem);
}

void mainWindow::resizeEvent(QResizeEvent* e)
{
}

void mainWindow::keyPressEvent(QKeyEvent *event)
{
	theInputSystem->WriteBufferKeyDown(event->key());
}

void mainWindow::keyReleaseEvent(QKeyEvent *event)
{
	theInputSystem->WriteBufferKeyUp(event->key());
}

void mainWindow::updateFPS()
{
    QString fps_string = "FPS: " + QString::number(theRenderer.GetCurrentFps()) + " W: " + QString::number(thePspScreen->width()) + " H: " + QString::number(thePspScreen->height());
	ui.statusbar->showMessage(fps_string, 0);
}

void mainWindow::center()
{
	int x, y;
	int screenWidth;
	int screenHeight;
	int width, height;
	QSize windowSize;

	QDesktopWidget *desktop = QApplication::desktop();

    int screen = desktop->primaryScreen();
    QRect rect(desktop->availableGeometry(screen));

    width = frameGeometry().width();
	height = frameGeometry().height();  

	screenWidth = rect.width();
	screenHeight = rect.height();

	x = (screenWidth - width) / 2;
	y = (screenHeight - height) / 2;

	move(x, y);
}
void mainWindow::menuOpenUMD()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a UMD iso"), settings.mLastOpenUMD, tr("UMD Files (*.iso;*.cso);;iso Files(*.iso);;cso Files(*.cso)"));

	if (!fileName.isEmpty())
    {
        settings.mLastOpenUMD = fileName;
        settings.SaveSettings();
        ui.actionOpen->setEnabled(false);
        ui.actionOpen_MemCard->setEnabled(false);
        ui.actionOpen_UMD->setEnabled(false);
        theEmulator.SetNewGame(fileName);
    }
}
void mainWindow::menuOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a file to open"), settings.mLastOpenFile, tr("PSP Files (*.pbp;*.elf;*.prx);;PBP Files (*.pbp);;Elf Files(*.elf);;Prx Files(*.prx)"));

	if (!fileName.isEmpty())
    {
        settings.mLastOpenFile= fileName;
        settings.SaveSettings();
        ui.actionOpen->setEnabled(false);
        ui.actionOpen_MemCard->setEnabled(false);
        ui.actionOpen_UMD->setEnabled(false);
        theEmulator.SetNewGame(fileName);
    }
}
void mainWindow::menuOpenMemCard()
{
    memoryCard* memcard = new memoryCard(this);
    memcard->exec();
    ui.actionOpen->setEnabled(false);
    ui.actionOpen_MemCard->setEnabled(false);
    ui.actionOpen_UMD->setEnabled(false);
}

void mainWindow::closeEvent(QCloseEvent *event)
{
	theEmulator.ShutDown();
}

void mainWindow::menuExit()
{
	theEmulator.ShutDown();
	qApp->exit(0);
}

void mainWindow::menuRun()
{
    theEmulator.StartGame();
}

void mainWindow::menuPause()
{
    theEmulator.PauseGame();
}

void mainWindow::menuReset()
{
    QMessageBox::warning(this, "PCSP - Reset", "This is an obsolete action. You should restart this emulator.");
}

extern volatile int vsync_limiter;
void mainWindow::menuVSYNC()
{
    if (ui.actionVSYNC_Limiter->isChecked())
    {
        settings.mVsyncLimiter = true;
        vsync_limiter = 1;
        settings.SaveSettings();
    }
    else
    {
        settings.mVsyncLimiter = false;
        vsync_limiter = 0;
        settings.SaveSettings();
    }
}

void mainWindow::menuUseShaders()
{
    if (ui.actionUse_OPENGL_Shaders->isChecked())
    {
        settings.mEnableShaders = true;
        settings.SaveSettings();
    }
    else
    {
        settings.mEnableShaders = false;
        settings.SaveSettings();
    }
}
void mainWindow::menuMuteSound()
{
    if (ui.actionMute_Sound->isChecked())
    {
		settings.mMuteSound= true;
        settings.SaveSettings();
    }
    else
    {
        settings.mMuteSound = false;
        settings.SaveSettings();
    }
}
void mainWindow::menuAlwaysOnTop()
{
    Qt::WindowFlags flags = 0;
	flags = this->windowFlags(); //get the previous flags
	if(ui.actionAlwaysOnTop->isChecked())
	{
       settings.mAlwaysOnTop=true;
       flags |= Qt::WindowStaysOnTopHint;
	   settings.SaveSettings();
	}
	else
	{
      settings.mAlwaysOnTop=false;
      flags = flags & ~Qt::WindowStaysOnTopHint;
	  settings.SaveSettings();
	}
   this->setWindowFlags(flags);
   this->show();

}
void mainWindow::openDebugger()
{
   emit menuOpenDebugger();
}
void mainWindow::menuOpenDebugger()
{
#ifndef DISABLE_DEBUGGER
    pcspdebugger *debugger = new pcspdebugger();
	debugger->show();
#endif
}
void mainWindow::menuConfigureController()
{
	controllerConfigure *config = new controllerConfigure(this);
	config->exec();
}
void mainWindow::menuAbout()
{
	aboutDialog *about = new aboutDialog(this);
	about->exec();
}
void mainWindow::menuSettings()
{
	settingsDialog* settings = new settingsDialog(this);
	settings->exec();
}
void mainWindow::menuScreenshot()
{
	theRenderer.SaveScreenshot = true;
}

void mainWindow::menuFullscreen()
{
    settings.mFullscreen = !settings.mFullscreen;
    if (settings.mFullscreen)
    {
        showFullScreen();
    }
    else
    {
        showNormal();
    }
    settings.SaveSettings();
}

bool mainWindow::event(QEvent *event)
{
	if (event->type() == QEvent::User+1)
	{
         LoadedEvent *loadEvent = static_cast<LoadedEvent *>(event);
		 return loadEvent->allLoaded();       
	}
	return QMainWindow::event(event);//return the default event handler
}

void mainWindow::onCritical(QString const &caption, QString const &message)
{
    QMessageBox::critical(this, caption, message);
}

void mainWindow::onWarning(QString const &caption, QString const &message)
{
    QMessageBox::warning(this, caption, message);
}

void mainWindow::onOsk(SceUtilityOskParam *param)
{
    QOskDialog dialog(this->centralWidget(), param);
    dialog.Show();
}

class QNoVisibleEscapeButton
:   public QAbstractButton
{
public:
    QNoVisibleEscapeButton() {}
    void paintEvent(QPaintEvent *) {}
};

void mainWindow::onMsgDialog(SceUtilityMsgDialogParam *param)
{
    QMessageBox msgBox(this->centralWidget());

    int buttons = 0;
    QString message, enter, back; 

    if (param->type == SCE_UTILITY_MSGDIALOG_TYPE_NUMBER)
    {
        message = QString("Internal error : 0x%1").arg(param->errorNum, 8, 16, QLatin1Char('0'));
    }
    else if (param->type == SCE_UTILITY_MSGDIALOG_TYPE_STRING)
    {
        message = QString::fromUtf8(param->msgString);
        if (param->optionType == SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_NONE)
        {
            if (param->enterString)
            {
                enter = QString::fromUtf8(param->enterString);
            }
            if (param->backString)
            {
                back = QString::fromUtf8(param->backString);
            }
        }
    }

    msgBox.setText(message);

    if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_SE_TYPE_NORMAL)
    {
        if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO)
        {
            msgBox.setIcon(QMessageBox::Question);
        }
    }
    else
    {
        msgBox.setIcon(QMessageBox::Critical);        
    }

    if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO)
    {
        buttons = QMessageBox::Yes|QMessageBox::No;

        if (!back.size())
        {
            QAbstractButton *escape = new QNoVisibleEscapeButton;
            msgBox.addButton(escape, QMessageBox::RejectRole);
            msgBox.setEscapeButton(escape);
        }
    }
    else if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_OK)
    {
        if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_DISABLE_CANCEL_ON)
        {
            buttons = QMessageBox::Ok;
            if (!back.size())
            {
                QAbstractButton *escape = new QNoVisibleEscapeButton;
                msgBox.addButton(escape, QMessageBox::RejectRole);
                msgBox.setEscapeButton(escape);
            }
        }
        else
        {
            buttons = QMessageBox::Ok|QMessageBox::Cancel;
        }
    }
    else if (!back.size())
    {
        QAbstractButton *escape = new QNoVisibleEscapeButton;
        msgBox.addButton(escape, QMessageBox::RejectRole);
        msgBox.setEscapeButton(escape);
    }

    if (enter.size())
    {
        buttons &= ~QMessageBox::Ok|~QMessageBox::Yes|~QMessageBox::No;
        msgBox.setDefaultButton(msgBox.addButton(enter, QMessageBox::AcceptRole));
    }
    else if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_DEFAULT_CURSOR_NO)
    {
        msgBox.setDefaultButton(QMessageBox::No);
    }
    else
    {
        if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO)
        {
            msgBox.setDefaultButton(QMessageBox::Yes);
        }
        else if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_OK)
        {
            msgBox.setDefaultButton(QMessageBox::Ok);
        }
    }

    if (back.size())
    {
        buttons &= ~QMessageBox::Cancel;
        msgBox.setEscapeButton(msgBox.addButton(back, QMessageBox::RejectRole));
    }

    msgBox.setStandardButtons(QMessageBox::StandardButtons(buttons));

    switch (msgBox.exec())
    {
    case QMessageBox::Ok:
        param->buttonResult = SCE_UTILITY_MSGDIALOG_BUTTON_INVALID;
        param->result       = SCE_UTILITY_RESULT_OK;
        break;

    case QMessageBox::Yes:
        param->buttonResult = SCE_UTILITY_MSGDIALOG_BUTTON_YES;
        param->result       = SCE_UTILITY_RESULT_OK;
        break;

    case QMessageBox::No:
        param->buttonResult = SCE_UTILITY_MSGDIALOG_BUTTON_NO;
        param->result       = SCE_UTILITY_RESULT_OK;
        break;

    case QMessageBox::Cancel:
        param->buttonResult = SCE_UTILITY_MSGDIALOG_BUTTON_INVALID;
        param->result       = SCE_UTILITY_RESULT_CANCELED;
        break;

    default:
        if (msgBox.clickedButton() == msgBox.defaultButton())
        {
            param->result = SCE_UTILITY_RESULT_OK;
            if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO)
            {
                param->buttonResult =  SCE_UTILITY_MSGDIALOG_BUTTON_OK;
            }
            else
            {
                param->buttonResult = SCE_UTILITY_MSGDIALOG_BUTTON_INVALID;
            }
        }
        else if (msgBox.clickedButton() == msgBox.escapeButton())
        {
            if (param->optionType & SCE_UTILITY_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO)
            {
                param->result = SCE_UTILITY_RESULT_OK;
                param->buttonResult =  SCE_UTILITY_MSGDIALOG_BUTTON_ESCAPE;
            }
            else
            {
                param->result = SCE_UTILITY_RESULT_CANCELED;
                param->buttonResult = SCE_UTILITY_MSGDIALOG_BUTTON_INVALID;
            }
        }
    }
}

void mainWindow::onSavedataSave(SceUtilitySavedataParam *param)
{
    QListSave dialog(this->centralWidget(), param);
    dialog.Show();
}

void mainWindow::onSavedataLoad(SceUtilitySavedataParam *param)
{
    QListLoad dialog(this->centralWidget(), param);
    dialog.Show();
}
