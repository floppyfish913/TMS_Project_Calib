#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T09:52:29
#
#-------------------------------------------------

QT       += core gui
QT       += serialport printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calib
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uart_handler.cpp \
    device.cpp \
    qcustomplot.cpp \
    calib_table.cpp \
    curve_analyzer.cpp \
    curve.cpp \
    device_info.cpp

HEADERS  += mainwindow.h \
    uart_handler.h \
    device.h \
    qcustomplot.h \
    calib_table.h \
    curve_analyzer.h \
    curve.h \
    device_info.h

FORMS    += mainwindow.ui \
    device_info.ui
