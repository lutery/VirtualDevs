QT += quick

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        devservice.cpp \
        main.cpp \
        asyncdevclient.cpp \
        devclient.cpp \
        devicemanager.cpp \
        deviceorder.cpp \
        devicestatus.cpp \
        devinit.cpp \
        printerorder.cpp

HEADERS += \
        MyLog.h \
        asyncdevclient.h \
        devclient.h \
        devicemanager.h \
        deviceorder.h \
        devicestatus.h \
        devinit.h \
        devservice.h \
        printerorder.h

RESOURCES += qml.qrc

include($$PWD/util/util.pri)
include($$PWD/handler/handler.pri)
include ($$PWD/verify/verify.pri)

macx {
    INCLUDEPATH += /Users/lutery/DevelopmentKit/log4cplus/qt/include
    LIBS += -L/Users/lutery/DevelopmentKit/log4cplus/qt/lib -llog4cplus.3.0.0 -L/Users/lutery/DevelopmentKit/log4cplus/qt/lib -llog4cplusqt5debugappender.3.0.0
}

unix:!macx{

}

win32{

}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
