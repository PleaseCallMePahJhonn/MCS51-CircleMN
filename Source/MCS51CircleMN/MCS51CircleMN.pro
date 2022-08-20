QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    aboutauthordialog.cpp \
    aboutsoftwaredialog.cpp \
    baudwrongdialog.cpp \
    copysuccessfuldialog.cpp \
    fileexistdialog.cpp \
    genfinishdialog.cpp \
    main.cpp \
    t1canceldialog.cpp \
    timecopieddialog.cpp \
    timewrongdialog.cpp \
    timwrongdialog.cpp \
    uartcanceldialog.cpp \
    widget.cpp

HEADERS += \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    aboutauthordialog.h \
    aboutsoftwaredialog.h \
    baudwrongdialog.h \
    copysuccessfuldialog.h \
    fileexistdialog.h \
    genfinishdialog.h \
    t1canceldialog.h \
    timecopieddialog.h \
    timewrongdialog.h \
    timwrongdialog.h \
    uartcanceldialog.h \
    widget.h

FORMS += \
    aboutauthordialog.ui \
    aboutsoftwaredialog.ui \
    baudwrongdialog.ui \
    copysuccessfuldialog.ui \
    fileexistdialog.ui \
    genfinishdialog.ui \
    t1canceldialog.ui \
    timecopieddialog.ui \
    timewrongdialog.ui \
    timwrongdialog.ui \
    uartcanceldialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = logo.ico

