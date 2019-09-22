#include "mainwindow.h"
#include "ui_XVideoEditUI.h"
#include "xvideothread.h"
#include "xvideofilter.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    connect(XVideoThread::Instance(),SIGNAL(setImage(cv::Mat)),ui->src_widget,SLOT(updateImage(cv::Mat)));
    startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Open()
{
    QString filename = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("请选择视频文件："));
    if(filename.isEmpty())
    {
        return;
    }
    //char* file = filename.toLocal8Bit().data();
    //QMessageBox::information(this,"",filename);
    if(!XVideoThread::Instance()->open(filename))
    {
        QMessageBox::information(this,"","open failed!" + filename);
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    //qDebug() << XVideoThread::Instance()->getPlayPos();
    if(!sliderPause)
        ui->srcSlider->setValue(XVideoThread::Instance()->getPlayPos()*1000);
}

void MainWindow::sliderMoved(int value)
{
    //qDebug() << value;
    XVideoThread::Instance()->seek(value);
}

void MainWindow::sliderPressed()
{
    //qDebug() << "slider pressed";
    sliderPause = true;
}

void MainWindow::sliderReleased()
{
    //qDebug() << "slider released";
    sliderPause = false;
}

void MainWindow::setFilter()
{
    if(ui->brightSpinBox->value() > 0 || ui->contrastSpinBox->value() > 1)
    {
        XVideoFilter::Instance()->Add(XTask{TASK_GAIN,{(double)ui->brightSpinBox->value(),ui->contrastSpinBox->value()}});
    }
}
