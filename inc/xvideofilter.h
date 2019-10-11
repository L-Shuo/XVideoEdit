#ifndef XVIDEOFILTER_H
#define XVIDEOFILTER_H

#include <QObject>
#include <QVector>
#include <QColor>
#include <QPoint>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


enum XTastType {
    TASK_GAIN,
    TASK_ROTATE,
    TASK_FLIP,
    TASK_RESIZE,
    TASK_CLIP,
    TASK_TEXT,
    TASK_GRAY,
    TASK_MASK,
    TASK_BLEND,
    TASK_NONE
};

struct XTask
{
    XTastType x_type;
    QVector<double> params;
};

struct TEXT
{
    uint font_size;
    QString text;
    QPoint p;
    QColor color;
};

static struct TEXT TEXT_WRAP;

class XVideoFilter
{
public:
    XVideoFilter();
    static XVideoFilter *Instance();
    void setText(QString str,QPoint pos,QColor color, int font_size);

    virtual cv::Mat Filter(cv::Mat mat1, cv::Mat mat2, cv::Mat *mask) = 0;
    virtual void Add(XTask task) = 0;
    virtual void Clear() = 0;

    virtual ~XVideoFilter(); //虚析构函数，保证继承类的析构函数被调用

private:
    bool isMask;
};

#endif // XVIDEOFILTER_H
