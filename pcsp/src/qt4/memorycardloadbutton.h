#ifndef MEMORYCARDLOADBUTTON_H
#define MEMORYCARDLOADBUTTON_H

#include <QPushButton>
#include<QListWidgetItem>

class memoryCardLoadButton : public QPushButton
{
	Q_OBJECT

public:
	memoryCardLoadButton(QWidget *parent);
	~memoryCardLoadButton();
	QListWidgetItem* templist;
public slots:
	void enableLoadButton(QListWidgetItem* list);
	void click();
private:
	
};

#endif // MEMORYCARDLOADBUTTON_H
