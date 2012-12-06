#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL/QGLWidget>

class openglWidget : public QGLWidget
{
	Q_OBJECT

public:
	openglWidget(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
	~openglWidget();

 	bool glInitialized() const { return mGLInitialized; }

	 void initializeGL();
	 void paintGL();
 	 void glInit();
	 void resizeGL(int width, int height);
 	 void render();

private:
	bool mGLInitialized;
};

#endif // OPENGLWIDGET_H
