#include "stdafx.h"
#include "logconfigurecombo.h"
#include "settings.h"

logConfigureCombo::logConfigureCombo(QWidget *parent)
:   QComboBox(parent)
{

}

logConfigureCombo::~logConfigureCombo()
{

}

void logConfigureCombo::SaveConfig()
{
    int index = QComboBox::currentIndex();
    QString name = objectName();
    settings.SaveLogConfig(index, name);
}
