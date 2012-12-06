#include "stdafx.h"
#include "logconfigure.h"
#include "settings.h"
#include "log.h"
#include <set>
#include <QComboBox>
logConfigure::logConfigure(QWidget *parent)
: QDialog(parent)
{
    ui.setupUi(this);
    QMapIterator<QString, int> i(settings.logmap);
    while (i.hasNext()) 
    {
        i.next();
        QComboBox *combo = findChild<QComboBox *>(i.key());
        combo->setCurrentIndex(i.value());
    }
}

logConfigure::~logConfigure()
{
}

void logConfigure::SaveLogButton()
{
    settings.SaveSettings();
    Log::Categories &categories = Log::logs();
    for (Log::Categories::iterator i1 = categories.begin(); i1 != categories.end(); ++i1)
    {
        LogCategory *category = const_cast<LogCategory *>(*i1);
        QComboBox *combo = findChild<QComboBox *>(category->getName());
        if (combo)
            category->setLevel((LogCategory::LevelEnum)combo->currentIndex());		 
    }
    close();
}
