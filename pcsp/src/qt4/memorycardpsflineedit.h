#ifndef MEMORYCARDPSFLINEEDIT_H
#define MEMORYCARDPSFLINEEDIT_H

#include <QLineEdit>
#include<QListWidgetItem>

class memorycardPsfLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	memorycardPsfLineEdit(QWidget *parent);
	~memorycardPsfLineEdit();
public slots:
	void setpsfInfo(QListWidgetItem*);
private:
	
};

#endif // MEMORYCARDPSFLINEEDIT_H
