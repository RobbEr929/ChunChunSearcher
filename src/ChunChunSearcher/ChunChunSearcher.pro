QT += \
    core gui \
    sql \
    widgets

CONFIG += c++11

SOURCES += \
    admin.cpp \
    easylogging++.cc \
    filehunter.cpp \
    main.cpp \
    mainwindow.cpp \
    sql.cpp

HEADERS += \
    admin.h \
    easylogging++.h \
    filehunter.h \
    global.h \
    mainwindow.h \
    sql.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
