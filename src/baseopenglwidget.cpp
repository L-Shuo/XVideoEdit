#include "inc/baseopenglwidget.h"
#include <QDebug>
#include <QPainter>


BaseOpenGLWidget::BaseOpenGLWidget(QWidget *parent) : QOpenGLWidget (parent)
{
    //qDebug() << "BaseOpenGLWidget";
}

void BaseOpenGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),img);
    painter.end();
}

BaseOpenGLWidget::~BaseOpenGLWidget()
{

}


void BaseOpenGLWidget::updateImage(cv::Mat image)
{
    if(img.isNull())
    {
        qDebug() << "create image";
        uchar *buf = new uchar[width()*height()*3];
        //QImage 4字节对齐，要求width与height是4的倍数
        img = QImage(buf,width(),height(),QImage::Format_RGB888);
    }
    Mat _dst;
    cv::resize(image,_dst,Size(img.width(),img.height()));
    cv::cvtColor(_dst,_dst,cv::COLOR_BGR2RGB);
    memcpy(img.bits(),_dst.data,_dst.cols*_dst.rows*_dst.elemSize());
    update();
}
