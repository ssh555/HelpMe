
QT       += core gui sql network
QT       += serialport
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
    drawwave.cpp \
    loginform.cpp \
    main.cpp \
    patient.cpp \
    patientform.cpp \
    serialreceiver.cpp \
    serialsender.cpp \
    showdata.cpp \
    widget.cpp \
    widgetcurrent.cpp \
    widgethistory.cpp \
    clientwidget.cpp \
    historicaldataform.cpp \
    sqlpatientsmgr.cpp \
    widgetselect.cpp

HEADERS += \
    drawwave.h \
    loginform.h \
    patient.h \
    patientform.h \
    serialreceiver.h \
    serialsender.h \
    showdata.h \
    widget.h \
    widgetcurrent.h \
    widgethistory.h \
    clientwidget.h \
    historicaldataform.h \
    sqlpatientsmgr.h \
    widgetselect.h


FORMS += \
    loginform.ui \
    patientform.ui \
    widget.ui \
    clientwidget.ui \
    historicaldataform.ui \
    widgetcurrent.ui \
    widgethistory.ui \
    widgetselect.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

