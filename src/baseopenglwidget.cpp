#include "inc/baseopenglwidget.h"
#include <QDebug>
#include <QPainter>


BaseOpenGLWidget::BaseOpenGLWidget(QWidget *parent) : QOpenGLWidget (parent)
{
    play_pause_btn = new QPushButton(this);
    play_pause_btn->setIcon(QIcon(":/style/pause.png"));
    play_pause_btn->hide();
    play_pause_btn->setStyleSheet("background: transparent");
    play_pause_btn->setIconSize(QSize(48,48));
    pause = false;
    setMouseTracking(true);
    connect(play_pause_btn,SIGNAL(clicked()),this,SLOT(pause_play()));
}

void BaseOpenGLWidget::pause_play() //内部事件处理
{
    if(pause)
    {
        qDebug() << "play";
        emit play_pause(true);//发出播放信号
        pause = false;
        return;
    }
    if(!pause)
    {
        qDebug() << "pause";
        emit play_pause(false);//发出暂停信号
        pause = true;
        return;
    }
}

void BaseOpenGLWidget::pause_play(bool play) //接受来自XVideoThread的事件
{
    if(play)
    {
        btn_show = true; //允许按钮显示
        //qDebug() << "###play";
        //emit play_pause(true);//发出播放信号
        pause = false;
        play_pause_btn->setIcon(QIcon(":/style/pause.png"));
        return;
    }
    if(!play)
    {
        //qDebug() << "###pause";
        //emit play_pause(false);//发出暂停信号
        play_pause_btn->setIcon(QIcon(":/style/play.png"));
        pause = true;
        return;
    }
}

void BaseOpenGLWidget::moveBtn()
{
    if(!btn_show)
    {
        return;
    }
    int cx = (this->width()-play_pause_btn->width())/2;
    int cy = (this->height()-play_pause_btn->height())/2;
    play_pause_btn->setGeometry(cx,cy,48,48);
    play_pause_btn->show();
}

void BaseOpenGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),img);
    painter.end();
}

BaseOpenGLWidget::~BaseOpenGLWidget()
{
    qDebug() << "~BaseOpenGLWidget";
}

void BaseOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    moveBtn();
    QRect rect = QRect(20,20,this->width()*0.8,this->height()*0.8);
    if(!rect.contains(event->pos()))
        play_pause_btn->hide();
}


void BaseOpenGLWidget::updateImage(cv::Mat image)
{
    if(image.empty())
        return;
    if(img.isNull())
    {
        //qDebug() << "create image";
        uchar *buf = new uchar[width()*height()*3];
        //QImage 4字节对齐，要求width与height是4的倍数
        img = QImage(buf,width(),height(),QImage::Format_RGB888);
    }
    Mat _dst;

    cv::resize(image,_dst,Size(img.width(),img.height()));
    cv::cvtColor(_dst,_dst,cv::COLOR_BGR2RGB);
    memcpy(img.bits(),_dst.data,_dst.cols*_dst.rows*_dst.elemSize());
    update();
}
