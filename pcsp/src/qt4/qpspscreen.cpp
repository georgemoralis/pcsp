#include "stdafx.h"

#include <QTimer>

#include "qpspscreen.h"

#include <QtGui>
#include <QtGlobal>
#include <QGLContext>
#include <QGLFormat>

#include "loaders/loaders.h"

class QPspScreenFormat
:   public QGLFormat
{
public:
    QPspScreenFormat()
    :   QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer|QGL::Rgba|QGL::AlphaChannel|QGL::StencilBuffer)
    {
        setDoubleBuffer(true);
        setDepthBufferSize(24);
        setAlpha(true);
        setAlphaBufferSize(8);
        setStencilBufferSize(8);
        setSwapInterval(0);
    }
};

QPspScreen *thePspScreen;

QPspScreen::QPspScreen(QWidget *parent) 
:   QGLWidget(QPspScreenFormat(), parent)
,   m_initialized(false)
{
    setupUi(this);
    setAutoBufferSwap(false);
    resize(480, 272);

    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_OpaquePaintEvent);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    thePspScreen = this;
    m_initialized = true;
}

QPspScreen::~QPspScreen()
{
}

void QPspScreen::StartRendering()
{
    //glt.start();
}

void QPspScreen::StopRendering()
{
    //glt.stop();
    //glt.wait();
}

void QPspScreen::resizeEvent(QResizeEvent *event)
{
    //glt.resizeViewport(evt->size());
    QWidget::resizeEvent(event);
}

void QPspScreen::paintEvent(QPaintEvent *)
{
}

void QPspScreen::closeEvent(QCloseEvent *event)
{
    //stopRendering();
    QGLWidget::closeEvent(event);
}

QImage QPspScreen::GrabFrameBuffer()
{
	glReadBuffer(GL_BACK);
	return grabFrameBuffer();
}

void QPspScreen::SaveScreenshot()
{
#ifdef _MSC_VER
    QDir root("");
    root.mkdir("screenshots");
    QDir screendir("screenshots");
    screendir.setFilter(QDir::Files);
    QFileInfoList list = screendir.entryInfoList(QDir::Files, QDir::Unsorted);

    int numb = 0;
	QString discid = loaders::getDiscID();
    QString numbstr;
    numbstr.setNum(numb);
    QString filename = discid + "-Shot-0" + numbstr + ".jpg";

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == filename)
        {
            numb++;
            numbstr.setNum(numb);
            if (numb <= 9)
                numbstr = "0" + numbstr;
            filename = discid + "-" + "Shot" + "-" + numbstr + ".jpg";
        }
    }
    QImage image = GrabFrameBuffer();
    image.save("screenshots\\" + filename, "JPG");
#endif
}