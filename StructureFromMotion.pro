QT       += widgets
QT       += xml
CONFIG -= CONSOLE

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_features2d \
        -lopencv_calib3d
CONFIG += c++11

SOURCES += \
    main.cpp \
    FrameData.cpp \
    IO.cpp

HEADERS += \
    FrameData.h \
    IO.h
