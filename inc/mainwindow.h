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

private:
    Ui::MainWindow *ui;
    bool sliderPause = false;
};

#endif // MAINWINDOW_H
