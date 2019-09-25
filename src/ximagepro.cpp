#include "ximagepro.h"
#include <QDebug>

XImagePro::XImagePro()
{

}

void XImagePro::Set(cv::Mat src1, cv::Mat src2)
{
    this->src1 = src1;
    this->src2 = src2;
    src1.copyTo(this->dst);
}

void XImagePro::Gain(double bright, double contrast)
{
    if(dst.empty())
        return;
    //qDebug() << bright << contrast;
    this->dst.convertTo(dst,-1,contrast,bright);
}

void XImagePro::Rotate(int direction)
{
    if(dst.empty())
        return;
    //1:90度, 2:180度, 3:270度
    switch (direction)
    {
    case 1:
        cv::rotate(dst,dst,cv::ROTATE_90_CLOCKWISE);
        break;
    case 2:
        cv::rotate(dst,dst,cv::ROTATE_180);
        break;
    case 3:
        cv::rotate(dst,dst,cv::ROTATE_90_COUNTERCLOCKWISE);
        break;
    default:
        break;
    }
}

void XImagePro::Filp(int direction)
{
    if(dst.empty())
        return;
    if(direction == 0)
        return;
    if(direction == 1)
        direction = 0; //X轴
    if(direction == 2)
        direction = 1; //Y轴
    if(direction == 3)
        direction = -1; //XY轴

    cv::flip(dst,dst,direction);
}

void XImagePro::Resize(int x, int y)
{
    if(dst.empty())
        return;
    cv::resize(dst,dst,cv::Size(x,y));
}
