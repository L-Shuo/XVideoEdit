#include <QMutex>
#include <QDebug>

#include "xvideofilter.h"
#include "ximagepro.h"

class CXFilter : public XVideoFilter
{
public:
    cv::Mat Filter(cv::Mat mat1, cv::Mat mat2);
    ~CXFilter()
    {
        qDebug() << "~CXFilter";
    }
    void Add(XTask task)
    {
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
        case TASK_ROTATE:
            p.Rotate((int)task.params[0]);
            break;
        case TASK_FLIP:
            p.Filp((int)task.params[0]);
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
    qDebug() << "~XVideoFilter";
}

XVideoFilter *XVideoFilter::Instance()
{
    static CXFilter cx;
    return &cx;
}

