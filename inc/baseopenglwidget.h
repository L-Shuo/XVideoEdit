#ifndef BASEOPENGLWIDGET_H
#define BASEOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <QPushButton>
#include <QMouseEvent>

using namespace cv;

class BaseOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit BaseOpenGLWidget(QWidget *parent = nullptr);
    ~BaseOpenGLWidget();
    virtual void paintEvent(QPaintEvent *event);
    void moveBtn();
    void mouseMoveEvent (QMouseEvent * event);
signals:
    void play_pause(bool);

public slots:
    void updateImage(cv::Mat image);
    void pause_play();
    void pause_play(bool play);

private:
    QPushButton *play_pause_btn;
    QImage img;
    bool pause = false;
    bool btn_show = false;
};

#endif // BASEOPENGLWIDGET_H
