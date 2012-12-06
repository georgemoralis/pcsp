#include "stdafx.h"
#include <QtDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include "graphicscene.h"
#include "emulator.h"

graphicScene* theScene = NULL;

graphicScene::graphicScene(openglWidget* w, QWidget* parent) : QGraphicsView(parent)
{
	theScene = this;

	mGLWidget = w;
 	if (!mGLWidget->glInitialized()) 
	{
 	  qDebug() << "Initing glWidget";
 	  mGLWidget->glInit();
 	  
	  if (!mGLWidget->glInitialized()) 
	  {
 		qCritical() << "GLWidget failed to init!";
 	  }
 	}
	
	if (w->isVisible())
 		show();
 	
 	setViewport(mGLWidget);
 	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
 	
	// Default to no frame, i.e. same as GLWidget
 	setFrameStyle(QFrame::NoFrame);

 	
 	// Create scene
 	setScene(new Scene(w));
 	
 	// Copy some properties from GL widget
	setMinimumSize(w->minimumSize());
 	setMaximumSize(w->maximumSize());
 	setSizePolicy(w->sizePolicy());

	
}

graphicScene::~graphicScene()
{

}

QWidget* graphicScene::createWindow(const QString& title)
{
 	QDialog* d = new QDialog(0, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
 	
	d->setWindowOpacity(0.8);
 	d->setWindowTitle(title);
 	d->setLayout(new QVBoxLayout);
 	
 	return d;
}

QGraphicsProxyWidget* graphicScene::addWidget(QWidget* w)
{
 	QGraphicsProxyWidget* item = scene()->addWidget(w);
 	item->setFlag(QGraphicsItem::ItemIsMovable);
 	item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
 	
	return item;
}

graphicScene::Scene::Scene(openglWidget *w) : QGraphicsScene()
{
 	 mGLWidget = w;
 	 setSceneRect(QRect(QPoint(0, 0), mGLWidget->size()));
}

void graphicScene::Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
	
}