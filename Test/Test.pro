include(../defaults.pri)

GOOGLETEST_DIR = $$PWD/Google_tests/lib
$${GOOGLETEST_DIR}
include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../Snake_cpp_qt/constants/constants.h \
        ../Snake_cpp_qt/model/snake.h \
        ../Snake_cpp_qt/model/food.h \
        ../Snake_cpp_qt/helper/helper.h \
        tst_helper.h \
        tst_snake.h

SOURCES += \
        main.cpp \
        ../Snake_cpp_qt/model/snake.cpp \
        ../Snake_cpp_qt/helper/helper.cpp
