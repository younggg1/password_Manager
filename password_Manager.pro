QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createpassword.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwindow.cpp

HEADERS += \
    createpassword.h \
    loginwindow.h \
    mainwindow.h \
    registerwindow.h

FORMS += \
    createpassword.ui \
    loginwindow.ui \
    mainwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
