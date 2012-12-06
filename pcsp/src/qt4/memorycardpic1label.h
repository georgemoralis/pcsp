#ifndef MEMORYCARDPIC1LABEL_H
#define MEMORYCARDPIC1LABEL_H

#include <QLabel>
#include<QListWidgetItem>

class memorycardPic1Label : public QLabel
{
	Q_OBJECT

public:
	memorycardPic1Label(QWidget *parent);
	~memorycardPic1Label();
	public slots:
		void displayPic(QListWidgetItem*);
private:
	
};

#endif // MEMORYCARDPIC1LABEL_H
