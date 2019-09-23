#include "xvideothread.h"
#include "xvideofilter.h"
#include <QDebug>

XVideoThread::XVideoThread()
{
    start();
}

void XVideoThread::run()
{
    cv::Mat src;
    for(;;)
    {
        mutex.lock();
        if(is_exit)
        {
            mutex.unlock();
            break;
        }
        if(!srcVideo.isOpened())
        {
            mutex.unlock();
            msleep(5);
            continue;
        }
        if(!srcVideo.read(src) || src.empty())
        {
            mutex.unlock();
            continue;
        }
        emit setImage(src);
        cv::Mat mat = XVideoFilter::Instance()->Filter(src,/*ununsed*/cv::Mat());
        emit setMatImage(mat);
        mutex.unlock();
        msleep(1000/srcFPS);
    }
}

bool XVideoThread::open(QString filename)
{
    qDebug() << filename.toLocal8Bit().data();
    if(srcVideo.isOpened())
    {
        srcVideo.release();
    }
    if(!srcVideo.open(filename.toLocal8Bit().data()))
    {
        return false;
    }
    srcFPS = srcVideo.get(cv::CAP_PROP_FPS);
    //qDebug() << FPS << 1000/FPS;
    if(srcFPS <= 0)
    {
        srcFPS = 30;
    }
    return true;
}

double XVideoThread::getPlayPos()
{
    mutex.lock();
    if(srcVideo.isOpened())
    {
        double curPos = srcVideo.get(cv::CAP_PROP_POS_FRAMES);
        double total_count = srcVideo.get(cv::CAP_PROP_FRAME_COUNT);
        mutex.unlock();
        //qDebug() << curPos << total_count;
        if(total_count > 0.001)
            return curPos/total_count;
    }
    mutex.unlock();
    return 0;
}

void XVideoThread::seek(int pos)
{
    double total_count = srcVideo.get(cv::CAP_PROP_FRAME_COUNT);
    //qDebug() << curPos;
    seek(pos/1000.0 * total_count);
}

void XVideoThread::seek(double pos)
{
    mutex.lock();
    if(!srcVideo.isOpened())
    {
        mutex.unlock();
        return;
    }
    srcVideo.set(cv::CAP_PROP_POS_FRAMES,pos);
    mutex.unlock();
}

XVideoThread::~XVideoThread()
{
    mutex.lock();
    is_exit = true;
    mutex.unlock();
    wait();
    deleteLater();
}

bool XVideoThread::startSave(QString filename,int width, int height)
{
    qDebug() << "start saving";
    return true;
}

void XVideoThread::stopSave()
{
    qDebug() << "stop saving";
}
