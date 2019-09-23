#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void Open();
    void sliderMoved(int);
    void sliderPressed();
    void sliderReleased();
    void setFilter();
    void exportVideo(); //导出视频

private:
    Ui::MainWindow *ui;
    bool sliderPause = false;
    bool isExporting = false;
};

#endif // MAINWINDOW_H
