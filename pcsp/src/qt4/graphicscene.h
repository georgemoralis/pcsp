#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H
#include "openglwidget.h"
#include <QtGui/QGraphicsView>

class QGraphicsProxyWidget;

class graphicScene  : public QGraphicsView
{
	Q_OBJECT

public:
	graphicScene(openglWidget* w, QWidget* parent = 0);
	~graphicScene();
	QWidget* createWindow(const QString& title);
	QGraphicsProxyWidget* addWidget(QWidget* w);

private:
	class Scene;
	
	openglWidget* mGLWidget;
};
class graphicScene::Scene : public QGraphicsScene
{
 	public:
   Scene(openglWidget* w);
   void drawBackground(QPainter* painter, const QRectF& rect);
   
protected:
   openglWidget* mGLWidget;

};

extern graphicScene* theScene;

#endif // GRAPHICSCENE_H
