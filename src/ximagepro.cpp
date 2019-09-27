#include "ximagepro.h"
#include "CvxText.h"
#include <QDebug>

static CvxText CV_TEXT("F:\\Code\\XVideoEdit\\XVideoEdit\\res\\simhei.ttf");

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

void XImagePro::Clip(int x, int y, int width, int height)
{
    if(dst.empty())
        return;
    cv::Size size = dst.size();
    if(x >= 0 && y >= 0 && width < size.width && height < size.height)
        dst = dst(cv::Rect(x,y,width,height));
}

void XImagePro::PutText(QPoint pos, const char *msg,QColor color, int fontsize=9)
{
    if(dst.empty())
        return;
    float p = 0.5;
    cv::Scalar font_size{ (double)fontsize, 0.5, 0.5, 0 };
    CV_TEXT.setFont(nullptr, &font_size, nullptr, &p);  //透明处理
    cv::Point _pos;
    _pos.x = pos.x();
    _pos.y = pos.y();
    CV_TEXT.putText(dst, msg, _pos, CV_RGB(color.red(),color.green(),color.blue()));
}

void XImagePro::Gray(int gray)
{
    if(dst.empty())
        return;
    if(gray == 1)
        cv::cvtColor(dst,dst,cv::COLOR_RGB2GRAY);
}
