QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+ = "C:\Program Files\IVI Foundation\VISA\Win64\Include"

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../../../../Program Files/IVI Foundation/VISA/Win64/Include/visa.h \
    ../../../../../Program Files/IVI Foundation/VISA/Win64/Include/visatype.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

win32: LIBS += "C:\Program Files\IVI Foundation\VISA\Win64\Lib_x64\msc\visa32.lib"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
