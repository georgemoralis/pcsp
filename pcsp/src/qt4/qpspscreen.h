#ifndef QPSPSCREEN_H
#define QPSPSCREEN_H

#include "ui_qpspscreen.h"

#include <QGLWidget>

class QPspScreen : public QGLWidget, public Ui::QPspScreenClass
{
    Q_OBJECT

public:
    QPspScreen(QWidget *parent = 0);
    ~QPspScreen();

    void   StartRendering();    
    void   StopRendering();
	QImage GrabFrameBuffer();
    void   SaveScreenshot();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

private:
    bool m_initialized;
};

extern QPspScreen *thePspScreen;

#endif // QPSPSCREEN_H
