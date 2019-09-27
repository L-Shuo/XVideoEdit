#ifndef XIMAGEPRO_H
#define XIMAGEPRO_H

#include <QObject>
#include <QPoint>
#include <QColor>

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

    //图像旋转
    void Rotate(int rotate = 0);

    //图像镜像
    //0:X轴,1:Y轴,-1:Both
    void Filp(int direction);

    //调整图像尺寸
    void Resize(int x,int y);

    //裁剪
    void Clip(int x,int y, int width, int height);

    //文字贴图
    void PutText(QPoint pos,const char *msg,QColor color,int fontsize);

    cv::Mat Get()
    {
        return dst;
    }

private:
    cv::Mat dst;
    cv::Mat src1,src2;
};

#endif // XIMAGEPRO_H
