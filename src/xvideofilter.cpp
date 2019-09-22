#include <QMutex>
#include <QDebug>

#include "xvideofilter.h"
#include "ximagepro.h"

class CXFilter;

class CXFilter : public XVideoFilter
{
public:
    cv::Mat Filter(cv::Mat mat1, cv::Mat mat2);

    void Add(XTask task)
    {
        tasks.clear();
        mutex.lock();
        tasks.push_back(task);
        mutex.unlock();
    }
    void Clear()
    {
        mutex.lock();
        tasks.clear();
        mutex.unlock();
    }

private:
    QMutex mutex;
    QVector<XTask> tasks;
};

cv::Mat CXFilter::Filter(cv::Mat mat1, cv::Mat mat2)
{
    mutex.lock();
    XImagePro p;
    p.Set(mat1,mat2);
    for(auto &task:tasks)
    {
        switch(task.x_type)
        {
        case TASK_NONE:
            break;
        case TASK_GAIN: //亮度对比度调整
            //qDebug() << "Task Gain";
            p.Gain(task.params[0],task.params[1]);
            break;
        }
    }
    cv::Mat ret = p.Get();
    mutex.unlock();
    return ret;
}



XVideoFilter::XVideoFilter()
{

}

XVideoFilter::~XVideoFilter()
{

}

XVideoFilter *XVideoFilter::Instance()
{
    static CXFilter cx;
    return &cx;
}

