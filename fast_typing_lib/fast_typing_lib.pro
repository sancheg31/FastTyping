
include(../qmake_target_platform.pri)
include(../qmake_destination_path.pri)

CONFIG += c++17 console qt create_prl
CONFIG -= app_bundle

QT -= gui
QT += core sql

TARGET = fast-typing-lib
TEMPLATE = lib

DEFINES = FAST_TYPING_LIBRARY

HEADERS += \
    source/DatabaseModel.hpp \
    source/ft_lib_global.h

SOURCES += \
    source/DatabaseModel.cpp

LIBS += -L"D:/Projects/Qt/type_list/binaries/windows/gcc/x86/debug" -ltl_lib

INCLUDEPATH += source
INCLUDEPATH += "D:/Projects/Qt/type_list/tl_lib"

DESTDIR = $${PWD}/../binaries/$${DESTINATION_PATH}
UI_DIR = $${PWD}/build/$${DESTINATION_PATH}/.ui
MOC_DIR = $${PWD}/build/$${DESTINATION_PATH}/.moc
OBJECTS_DIR = $${PWD}/build/$${DESTINATION_PATH}/.obj
RCC_DIR = $${PWD}/build/$${DESTINATION_PATH}/.rcc



DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
