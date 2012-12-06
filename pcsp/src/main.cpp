#include "stdafx.h"
#include "qt4/mainwindow.h"
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include "version.h"
#include "al/host.h"
#include "settings.h"
#include <QGLFormat>

extern void	generate_allegrex();

int main(int argc, char *argv[])
{
    bool openWithDebugger = false;
    bool enableDecryptor  = false;
    bool isCommandLine    = false;

    QApplication application(argc, argv);

    QStringList args(QCoreApplication::arguments());

    Log::init();

    //application.setStyle("plastique");

    //generate_allegrex();

    mainWindow MainWindow;
#ifndef BUILDING_SPECIFIC_GAME_EMULATOR
    MainWindow.setWindowTitle("PCSP v" VERSION);
#else
    MainWindow.setWindowTitle("PCSP-specific");
#endif
    MainWindow.center();
    MainWindow.show();   

    QString umdpath;

    for (int i = 1; i < args.count(); i++)
    {
        if (args[i] == "-umd")
        {
            umdpath = args[i+1];
        }
        if (args[i] == "-debug")
        {
            if (args[i+1] == "true")
            {
                openWithDebugger = true;
            }
        }
        if (args[i] == "-decrypt")
        {
            if (args[i+1] == "true")
            {
                enableDecryptor = true;
                isCommandLine = true;
            }
        }
    }

    if (!umdpath.isEmpty())
    {
        theEmulator.SetNewGame(umdpath);
        theEmulator.StartGame();
    }
    if (openWithDebugger)
    {
        MainWindow.openDebugger();
    }
    if (isCommandLine)
    {
        settings.LoadSettings();
        if (enableDecryptor)
        {

            settings.mEnableDecryptor=true;
            settings.SaveSettings();
        }
        else
        { 
            settings.mEnableDecryptor=false;
            settings.SaveSettings();
        }
    }

    if (__host_cpu_info.has_SSE && __host_cpu_info.has_SSE2)
    {
        return application.exec();
    }

    QMessageBox::critical(&MainWindow, "PCSP - Invalid CPU", "Sorry, this emulator needs a CPU which can run SSE/SSE2 instructions.");

    return 0;
}
