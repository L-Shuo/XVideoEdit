#include "xvideothread.h"
#include "xvideofilter.h"
#include <QDebug>

XVideoThread::XVideoThread()
{
    //CV_TEXT.putText(image, msg, cv::Point(50, 50), CV_RGB(255,255,255));
    start();
}

void XVideoThread::run()
{
    cv::Mat src;
    cv::Mat blend;
    cv::Mat mat;

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
        if(!_play) //暂停
        {
            mutex.unlock();
            msleep(5);
            continue;
        }
        if(srcBlend.isOpened())
        {
            if(!this->start_write && srcBlend.read(blend) && !blend.empty())
                emit setBlendImage(blend);
            if(this->start_write)
                srcBlend.read(blend);
        }
        if(!srcVideo.read(src) || src.empty())
        {
            if(this->start_write)
            {
                this->start_write = false;
                emit exportStopped();
                vw.release();
            }
            emit startPlay(!_play);//更新播放按钮
            mutex.unlock();
            msleep(100);
            continue;
        }
        if(!this->start_write)
            emit setImage(src);

//        if(this->_needBlend)
//        {
//            //qDebug() << "_needBlend";
//            mat = XVideoFilter::Instance()->Filter(src,blend,&Mask);
//        }
//        else
//        {
//            //qDebug() << "not _needBlend";
        mat = XVideoFilter::Instance()->Filter(src,blend,&Mask);
        //}

        if(!this->start_write)
        {
            emit setMatImage(mat);
        }

        if(vw.isOpened() && this->start_write)
        {
            sleep_ms = 2; //加快导出速度
            vw.write(mat);
        }
        mutex.unlock();
        msleep(sleep_ms);
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
    srcSize.width = srcVideo.get(cv::CAP_PROP_FRAME_WIDTH);
    srcSize.height = srcVideo.get(cv::CAP_PROP_FRAME_HEIGHT);
    sleep_ms = 1000/srcFPS;
    //qDebug() << FPS << 1000/FPS;
    if(srcFPS <= 0)
    {
        srcFPS = 30;
    }
    _play = true;
    emit startPlay(_play);//更新播放按钮
    return true;
}

bool XVideoThread::openBlend(QString filename)
{
    qDebug() << "openBlend" << filename.toLocal8Bit().data();
    if(srcBlend.isOpened())
    {
        srcBlend.release();
    }
    if(!srcBlend.open(filename.toLocal8Bit().data()))
    {
        return false;
    }
    srcFPS = srcBlend.get(cv::CAP_PROP_FPS);
    src2Size.width = srcBlend.get(cv::CAP_PROP_FRAME_WIDTH);
    src2Size.height = srcBlend.get(cv::CAP_PROP_FRAME_HEIGHT);
    sleep_ms = 1000/srcFPS;
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
    qDebug() << "~XVideoThread";
}

bool XVideoThread::startSave(QString filename,int width, int height,bool is_color)
{
    qDebug() << "start saving";
    int _width = width;
    int _height = height;
    mutex.lock();
    if(!srcVideo.isOpened())
    {
        mutex.unlock();
        return false;
    }
    if(width == 0)
        _width = srcVideo.get(cv::CAP_PROP_FRAME_WIDTH);
    if(height == 0)
        _height = srcVideo.get(cv::CAP_PROP_FRAME_HEIGHT);
    if(vw.open(filename.toLocal8Bit().data(),vw.fourcc('H', '2', '6', '4'),srcFPS,cv::Size(_width,_height),is_color))
    {
        srcVideo.set(cv::CAP_PROP_POS_FRAMES,0);//回到第一帧,开始导出
        this->start_write = true;
    }
    mutex.unlock();
    return true;
}

void XVideoThread::stopSave()
{
    qDebug() << "stop saving";
    mutex.lock();
    sleep_ms = 1000/srcFPS;
    this->start_write = false;
    vw.release();
    mutex.unlock();
}

void XVideoThread::play(bool play_pause)
{
    qDebug() << play_pause;
    emit startPlay(play_pause);//更新播放按钮
    _play = play_pause;
}

cv::Size XVideoThread::getSrcSize()
{
    return srcSize;
}

cv::Size XVideoThread::getSrc2Size()
{
    return src2Size;
}

void XVideoThread::setMask(QString filename)
{
    mutex.lock();
    Mask = cv::imread(filename.toLocal8Bit().data());
    mutex.unlock();
}

void XVideoThread::startBlend(bool start)
{
    mutex.lock();
    _needBlend = start;
    mutex.unlock();
}
