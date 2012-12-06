#ifndef CONTROLLERGETBUTTON_H
#define CONTROLLERGETBUTTON_H

#include <QDialog>
#include <QTimer>
#include "ui_controllergetbutton.h"

class controllerGetButton : public QDialog
{
	Q_OBJECT

public:
    controllerGetButton(int button, QWidget *parent = 0);
    controllerGetButton(int button, int axis, QWidget *parent = 0);
	~controllerGetButton();

protected:
	void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

private:
	Ui::GetControllerButton ui;
    int m_button, m_mask;
    int m_axis;
    QTimer m_timer;
};

#endif // CONTROLLERGETBUTTON_H
