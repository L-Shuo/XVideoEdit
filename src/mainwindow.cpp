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
    connect(XVideoThread::Instance(),SIGNAL(setMatImage(cv::Mat)),ui->mat_widget,SLOT(updateImage(cv::Mat)));
    connect(XVideoThread::Instance(),SIGNAL(exportStopped()),this,SLOT(exportStopped()));
    connect(XVideoThread::Instance(),SIGNAL(startPlay(bool)),ui->src_widget,SLOT(pause_play(bool)));
    connect(ui->src_widget,SIGNAL(play_pause(bool)),XVideoThread::Instance(),SLOT(play(bool)));
    ui->resize_widthEdit->setValidator(new QIntValidator(50,3000,this));
    ui->resize_heightEdit->setValidator(new QIntValidator(50,3000,this));
    startTimer(500);
}

MainWindow::~MainWindow()
{
    qDebug() << "~MainWindow";
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

void MainWindow::setFilter() //设置按钮触发
{
    XVideoFilter::Instance()->Clear();
    if(ui->brightSpinBox->value() >= 0 && ui->contrastSpinBox->value() >= 1)
    {
        XVideoFilter::Instance()->Add(XTask{TASK_GAIN,{(double)ui->brightSpinBox->value(),ui->contrastSpinBox->value()}});
    }
    XVideoFilter::Instance()->Add(XTask{TASK_ROTATE,{(double)ui->rotateBox->currentIndex()}});
    XVideoFilter::Instance()->Add(XTask{TASK_FLIP,{(double)ui->flipBox->currentIndex()}});
    if(ui->resize_widthEdit->text().toDouble() >0 && ui->resize_heightEdit->text().toDouble()>0)
    {
        XVideoFilter::Instance()->Add(XTask{TASK_RESIZE,
                                            {ui->resize_widthEdit->text().toDouble(),
                                            ui->resize_heightEdit->text().toDouble()}});
    }

}

void MainWindow::exportVideo()
{
    if(isExporting)
    {
        isExporting = false;
        XVideoThread::Instance()->stopSave();
        ui->exportButton->setText(tr("开始导出"));
        return;
    }
    QString name = QFileDialog::getSaveFileName(this,"save","out1.avi");
    if(name.isEmpty())
        return;
    int __width = ui->resize_widthEdit->text().toInt();
    int __height = ui->resize_heightEdit->text().toInt();
    if(XVideoThread::Instance()->startSave(name,__width,__height)); //注意这里要传递宽高，否则导出的尺寸不对将无法播放
    {
        isExporting = true;
        ui->exportButton->setText(tr("停止导出"));
    }
}

void MainWindow::exportStopped()
{
    isExporting = false;
    //XVideoThread::Instance()->stopSave();
    ui->exportButton->setText(tr("开始导出"));
}
