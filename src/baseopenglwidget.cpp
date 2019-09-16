#include "inc/baseopenglwidget.h"
#include <QDebug>
#include <QPainter>


BaseOpenGLWidget::BaseOpenGLWidget(QWidget *parent) : QOpenGLWidget (parent)
{
    qDebug() << "BaseOpenGLWidget";
}

void BaseOpenGLWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "PainterEvent";
    Mat src = imread("1.jpg");
    QImage img(src.data,src.cols,src.rows,QImage::Format_RGB888);//BGR
    cvtColor(src,src,COLOR_BGR2RGB);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),img);
    qDebug() << "MatView::paintEvent";
}

