#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>
#include <QMutex>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include "CvxText.h"

static cv::VideoCapture srcVideo;
static cv::VideoWriter vw;
static CvxText CV_TEXT("F:\\Code\\XVideoEdit\\XVideoEdit\\res\\simhei.ttf");

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

    //外部设置帧位置的接口
    void seek(int pos);

    //开始保存视频
    bool startSave(QString filename,int width, int height);
    //停止保存视频,写入视频帧的索引
    void stopSave();

    ~XVideoThread();
    cv::Size getSrcSize();


signals:
    void setImage(cv::Mat);
    void setMatImage(cv::Mat);
    void exportStopped();
    void startPlay(bool);

protected slots:
    void play(bool);

private:
    //帧位置移动内部实现
    void seek(double pos);

protected:
    XVideoThread();
    QMutex mutex;
    bool is_exit=false;
    bool start_write = false;
    double srcFPS;
    int sleep_ms = 1;
    bool _play;
    cv::Size srcSize;
};

#endif // XVIDEOTHREAD_H
