#ifndef XVIDEOFILTER_H
#define XVIDEOFILTER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <QVector>

enum XTastType {
    TASK_GAIN,
    TASK_ROTATE,
    TASK_FLIP,
    TASK_NONE
};

struct XTask
{
    XTastType x_type;
    QVector<double> params;
};

class XVideoFilter
{
public:
    XVideoFilter();
    static XVideoFilter *Instance();

    virtual cv::Mat Filter(cv::Mat mat1, cv::Mat mat2) = 0;
    virtual void Add(XTask task) = 0;
    virtual void Clear() = 0;

    virtual ~XVideoFilter(); //虚析构函数，保证继承类的析构函数被调用
};

#endif // XVIDEOFILTER_H
