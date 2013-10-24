#-------------------------------------------------
#
# Project created by QtCreator 2013-08-16T09:35:26
#
#-------------------------------------------------

#QT       += core gui
QT += multimedia multimediawidgets
QT       += core gui xml script
greaterThan(QT_MAJOR_VERSION, 4)
{
 QT += widgets
QT += widgets printsupport
DEFINES += HAVE_QT5
}
#QT += xml

TARGET = ASCUM_ARM
TEMPLATE = app
QMAKE_CXXFLAGS += -mno-ms-bitfields

SOURCES += main.cpp\
        mainwindow.cpp \
    NcFramelessHelper.cpp \
    rotatedlabel.cpp \
    logprocessor.cpp \
    TMIinterpretator.cpp \
    welcomedialog.cpp \
    qtrpt.cpp \
    printform.cpp

HEADERS  += mainwindow.h \
    NcFramelessHelper.h \
    rotatedlabel.h \
    logprocessor.h \
    TMIinterpretator.h \
    welcomedialog.h \
    qtrpt.h \
    printform.h

FORMS    += mainwindow.ui \
    welcomedialog.ui \
    printform.ui

OTHER_FILES += \
    qwt.pri
LIBS+= -LC:\Qt\Qwt-6.0.2\lib -lqwt
INCLUDEPATH+= C:\Qt\qt-creator-2.7.0\bin
#LIBS += libpqdll.lib
INCLUDEPATH+= C:\Qt\Qwt-6.0.2\include
INCLUDEPATH+= C:\Qt\mingw-4.7\i686-w64-mingw32\include   #инклудим все стандартные библиотеки

RESOURCES += \
    breadRes.qrc
