#include "stdafx.h"
#include "openglwidget.h"
#include "rasterizer.h"

openglWidget::openglWidget(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
 	QGLWidget(parent, shareWidget, f)
{
	mGLInitialized = false;
    setMinimumSize(480, 272);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
 	setFocus();
}

openglWidget::~openglWidget()
{

}

void openglWidget::initializeGL()
{
  	mGLInitialized = true;
}

void openglWidget::paintGL()
{
	render();
}

void openglWidget::glInit()
{
	QGLWidget::glInit();
	theRasterizer.Initialize();
}

void openglWidget::resizeGL(int width, int height)
{

}

void openglWidget::render()
{
	
}