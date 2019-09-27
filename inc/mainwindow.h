#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CvxText.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void Open();
    void sliderMoved(int);
    void sliderPressed();
    void sliderReleased();
    void setFilter();
    void exportVideo(); //导出视频
    void exportStopped();

private:
    Ui::MainWindow *ui;
    bool sliderPause = false;
    bool isExporting = false;
    bool _dragging = false;
    bool _cliped = false;
    QPoint _startPosition;
    QPoint _framePosition;
};

#endif // MAINWINDOW_H
