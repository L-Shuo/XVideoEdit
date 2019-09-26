#include "inc/mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <QFile>
#include "CvxText.h"

//中文字体格式转换
static int ToWchar(const char* &src, wchar_t* &dest, const char *locale = "zh_CN.utf8")
{
    if (src == NULL) {
        dest = NULL;
        return 0;
    }

    // 根据环境变量设置locale
    setlocale(LC_CTYPE, locale);

    // 得到转化为需要的宽字符大小
    int w_size = mbstowcs(NULL, src, 0) + 1;

    // 非法字符检查
    if (w_size == 0) {
        dest = NULL;
        return -1;
    }

    dest = new wchar_t[w_size];
    if (!dest) {
        return -1;
    }

    int ret = mbstowcs(dest, src, strlen(src)+1);
    if (ret <= 0) {
        return -1;
    }
    return 0;
}

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
