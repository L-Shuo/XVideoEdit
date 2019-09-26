#-------------------------------------------------
#
# Project created by QtCreator 2019-09-16T08:26:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XVideoEdit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/CvxText.cpp \
        src/baseopenglwidget.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/ximagepro.cpp \
        src/xvideofilter.cpp \
        src/xvideothread.cpp

HEADERS += \
    inc/CvxText.h \
    inc/mainwindow.h \
    inc/baseopenglwidget.h \
    inc/xvideothread.h \
    inc/ximagepro.h \
    inc/xvideofilter.h

FORMS += \
    ui/XVideoEditUI.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/libs/opencv411 \
-lopencv_calib3d411 \
-lopencv_features2d411 \
-lopencv_highgui411 \
-lopencv_ml411 \
-lopencv_stitching411 \
-lopencv_core411 \
-lopencv_flann411 \
-lopencv_imgcodecs411 \
-lopencv_objdetect411 \
-lopencv_video411 \
-lopencv_dnn411 \
-lopencv_gapi411 \
-lopencv_imgproc411 \
-lopencv_photo411 \
-lopencv_videoio411

LIBS += -L$$PWD/libs/freetype2.10.1 -lfreetype

RESOURCES += \
    res/res.qrc

INCLUDEPATH += $$PWD/inc/
#DEPENDPATH += D:/workspace/opencv-4.1.1/build/install/include

