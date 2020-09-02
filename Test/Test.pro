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
        tst_snakemove.h \
        ../Snake_cpp_qt/constants/constants.h \
        ../Snake_cpp_qt/model/snake.h

SOURCES += \
        main.cpp \
        ../Snake_cpp_qt/model/snake.cpp
