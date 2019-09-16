#ifndef BASEOPENGLWIDGET_H
#define BASEOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class BaseOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit BaseOpenGLWidget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // BASEOPENGLWIDGET_H
