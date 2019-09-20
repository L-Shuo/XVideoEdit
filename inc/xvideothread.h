#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>
#include <QMutex>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

static cv::VideoCapture srcVideo;

class XVideoThread : public QThread
{
    Q_OBJECT

public:
    static XVideoThread *Instance()
    {
        static XVideoThread vt;
        return &vt;
    }
    void run();
    bool open(QString filename);
    double getPlayPos();

    ~XVideoThread();

signals:
    void setImage(cv::Mat);

protected:
    XVideoThread();
    QMutex mutex;
    bool is_exit=false;
    double srcFPS;
};

#endif // XVIDEOTHREAD_H
