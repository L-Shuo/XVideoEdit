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

#if 0 //字体调用显示示例
    cv::Mat image = cv::imread("F:\\Code\\XVideoEdit\\XVideoEdit\\1.png");
    CvxText text("F:\\Code\\XVideoEdit\\XVideoEdit\\res\\simhei.ttf");
    QString my_msg("123:你好,avdssdww");
    const char *msg = my_msg.toLocal8Bit().data();
    float p = 0.5;
    cv::Scalar size1{ 30, 0.1, 0.1, 0 };
    text.setFont(NULL, &size1, NULL, &p);  //透明处理
    text.putText(image, msg, cv::Point(50, 50), CV_RGB(255,255,255));
    cv::Mat mat(image);
    imwrite( "pro.png", mat );
#endif

    QApplication a(argc, argv);
    QFile qss(":/style/style.css");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());

    MainWindow w;
    w.show();

    return a.exec();
}
