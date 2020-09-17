QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../defaults.pri)

SOURCES += \
    gui/dialog_highscore.cpp \
    gui/dialog_new_highscore.cpp \
    helper/helper.cpp \
    main.cpp \
    gamewindow.cpp \
    model/food.cpp \
    model/snake.cpp

HEADERS += \
    constants/constants.h \
    gamewindow.h \
    gui/dialog_highscore.h \
    gui/dialog_new_highscore.h \
    helper/helper.h \
    model/food.h \
    model/snake.h

FORMS += \
    gamewindow.ui \
    gui/dialog_highscore.ui \
    gui/dialog_new_highscore.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources/resources.qrc
