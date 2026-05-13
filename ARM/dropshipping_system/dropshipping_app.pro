QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    product.cpp \
    order.cpp \
    supplier.cpp \
    datastorage.cpp

HEADERS += \
    mainwindow.h \
    product.h \
    order.h \
    supplier.h \
    datastorage.h

FORMS += \
    mainwindow.ui

TARGET = DropshippingApp
