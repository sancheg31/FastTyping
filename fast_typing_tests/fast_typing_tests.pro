
include(../qmake_target_platform.pri)
include(../qmake_destination_path.pri)
include(gtest_dependency.pri)


CONFIG += depend_includepath c++17 console qt testcase
CONFIG -= app_bundle

TARGET = fast-typing-tests
TEMPLATE = app

QT += testlib core

INCLUDEPATH += source

HEADERS += \
        source/tst_testcase1.hpp

SOURCES += \
        source/main.cpp

LIBS += -L$${PWD}/../binaries/$${DESTINATION_PATH} -lfast-typing-lib

DESTDIR = $${PWD}/../binaries/$${DESTINATION_PATH}
UI_DIR = $${PWD}/build/$${DESTINATION_PATH}/.ui
MOC_DIR = $${PWD}/build/$${DESTINATION_PATH}/.moc
OBJECTS_DIR = $${PWD}/build/$${DESTINATION_PATH}/.obj
RCC_DIR = $${PWD}/build/$${DESTINATION_PATH}/.rcc
