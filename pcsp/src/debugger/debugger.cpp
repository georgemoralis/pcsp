#include "stdafx.h"
#include "debugger.h"
#include "memory.h"


static QFile *getLogFile()
{
    static QFile file("emulator.log");
    if (!file.isOpen())
    {
        file.open(QFile::WriteOnly|QFile::Truncate);
    }
    return &file;
}

static QFile *logfile = getLogFile();

Debugger &Debugger::self()
{
    static Debugger instance;
    return instance;
}

Debugger &debugger = Debugger::self();

Debugger::Debugger()
{
    //QMutexLocker lock(&debugger.mutex);
    if (logfile && logfile->isOpen())
    {
        logfile->close();
    }

    logfile = getLogFile();
}

void Debugger::writeLog(QString text)
{
    QMutexLocker lock(&debugger.mutex);
    if (logfile) logfile->write((text/* + "\n"*/).toLatin1());
}

void Debugger::flushLog()
{
    QMutexLocker lock(&debugger.mutex);
    if (logfile) logfile->flush();
}

Debugger::~Debugger()
{
    //QMutexLocker lock(&debugger.mutex);
    if (logfile) logfile->close();
}

void Debugger::initialize()
{
}

void Debugger::finalize()
{
}
