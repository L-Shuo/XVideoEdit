#include "xvideothread.h"
#include <QDebug>

XVideoThread::XVideoThread()
{

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
        mutex.unlock();
        msleep(40);
    }
}

bool XVideoThread::open(QString filename)
{
    qDebug() << filename.toLocal8Bit().data();
    if(!srcVideo.open(filename.toLocal8Bit().data()))
    {
        return false;
    }
    start();
    return true;
}

XVideoThread::~XVideoThread()
{
    mutex.lock();
    is_exit = true;
    mutex.unlock();
    wait();
    deleteLater();
}
