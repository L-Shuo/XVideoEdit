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
