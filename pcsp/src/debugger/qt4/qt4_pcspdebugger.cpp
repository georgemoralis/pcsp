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
#include "stdafx.h"
#include "types.h"
#include "../debugger.h"
#include "qt4_memorycursor.h"
#include "qt4_pcspdebugger.h"

#include "logconfigure.h"


pcspdebugger::pcspdebugger(QWidget *parent, Qt::WFlags flags)
:   QMainWindow(parent, flags)
{
    ui.setupUi(this);
    tabifyDockWidget(ui.memory_dock, ui.disassembly_dock);
    tabifyDockWidget(ui.stdout_dock, ui.stderr_dock);
    tabifyDockWidget(ui.stderr_dock, ui.logger_dock);
	ui.menuWindow->addAction(ui.memory_dock->toggleViewAction());
    ui.menuWindow->addAction(ui.disassembly_dock->toggleViewAction());
	ui.menuWindow->addSeparator();
	ui.menuWindow->addAction(ui.sysmem_dock->toggleViewAction());
    ui.menuWindow->addSeparator();
	ui.menuWindow->addAction(ui.stdout_dock->toggleViewAction());
	ui.menuWindow->addAction(ui.stderr_dock->toggleViewAction());
	ui.menuWindow->addAction(ui.logger_dock->toggleViewAction());
	
    {
        QMutexLocker lock(&debugger.mutex);
        connect(&debugger, SIGNAL(updateViewsSignal()), ui.memorydockwidget, SLOT(updateMemoryViewer()));
        connect(&debugger, SIGNAL(logSignal(QString const&)), ui.loggerText, SLOT(setPlainText(QString const&)));
        connect(&debugger, SIGNAL(logStdoutSignal(QString const&)), ui.stdoutText, SLOT(appendPlainText(QString const&)));
        connect(&debugger, SIGNAL(logStderrSignal(QString const&)), ui.stderrText, SLOT(appendPlainText(QString const&)));
    }
    debugger.initialize();	
    debugger.updateViews();
}

pcspdebugger::~pcspdebugger()
{
    {
        QMutexLocker lock(&debugger.mutex);
        disconnect(&debugger, SIGNAL(updateViewsSignal()), ui.memorydockwidget, SLOT(updateMemoryViewer()));
        disconnect(&debugger, SIGNAL(logSignal(QString const&)), ui.loggerText, SLOT(appendPlainText(QString const&)));
        disconnect(&debugger, SIGNAL(logStdoutSignal(QString const&)), ui.stdoutText, SLOT(appendPlainText(QString const&)));
        disconnect(&debugger, SIGNAL(logStderrSignal(QString const&)), ui.stdoutText, SLOT(appendPlainText(QString const&)));
    }
    debugger.finalize();
}
void pcspdebugger::menuLogConfigure()
{
   logConfigure *dialog = new logConfigure(this);
   dialog->exec();
}

void Debugger::updateViews()
{
    QMutexLocker lock(&debugger.mutex);
    emit updateViewsSignal(); 
}

static const QColor tbl_color_codes[] = 
{
    Qt::black,
    Qt::red,
    Qt::green,
    Qt::yellow,
    Qt::blue,
    Qt::magenta,
    Qt::cyan,
    Qt::white,
    Qt::gray
};

static QTime &startLogTimer()
{
    static QTime time;
    time.start();
    return time;
}

void Debugger::log(QString const &line)
{
    //writeLog(line);
    QFuture<void> future = QtConcurrent::run(this, &Debugger::writeLog, line);
    //int size;
    static QTime &time = startLogTimer();
    static QStringList lines;
    lines.append(line);
    if (lines.size() > 200)
    {
        lines.removeFirst();
    }
    if (time.elapsed() > 250)
    {
        time.restart();
        QFuture<void> future = QtConcurrent::run(this, &Debugger::displayLog, lines);
        lines.clear();
    }
}

void Debugger::displayLog(QStringList lines)
{
    QMutexLocker lock(&debugger.mutex);
    emit logSignal(lines.join(""));
}

void Debugger::logStdout(QString const &line)
{
    QMutexLocker lock(&debugger.mutex);
    emit logStdoutSignal(line);
}

void Debugger::logStderr(QString const &line)
{
    QMutexLocker lock(&debugger.mutex);
    emit logStderrSignal(line);
}


