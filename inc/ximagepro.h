#ifndef XIMAGEPRO_H
#define XIMAGEPRO_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

class XImagePro
{
public:
    XImagePro();
    //设置转换源
    void Set(cv::Mat src1, cv::Mat src2);

    //设置亮度与对比度
    void Gain(double bright, double contrast);

    cv::Mat Get()
    {
        return dst;
    }

private:
    cv::Mat dst;
    cv::Mat src1,src2;
};

#endif // XIMAGEPRO_H
