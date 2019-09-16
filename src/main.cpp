#include "inc/mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/style.css");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());

    MainWindow w;
    w.show();

    return a.exec();
}
