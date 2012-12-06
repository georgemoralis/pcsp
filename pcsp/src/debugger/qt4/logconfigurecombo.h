#ifndef LOGCONFIGURECOMBO_H
#define LOGCONFIGURECOMBO_H

#include <QComboBox>

class logConfigureCombo : public QComboBox
{
	Q_OBJECT

public:
	logConfigureCombo(QWidget *parent);
	~logConfigureCombo();

private slots:
	void SaveConfig();

private:	
};

#endif // LOGCONFIGURECOMBO_H
