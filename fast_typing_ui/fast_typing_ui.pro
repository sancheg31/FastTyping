
include(../qmake_target_platform.pri)
include(../qmake_destination_path.pri)

CONFIG += c++17 qt link_prl
QT += sql core gui widgets charts


TEMPLATE = app
TARGET = fast_typing_ui

INCLUDEPATH += source
INCLUDEPATH += ../fast_typing_lib/source

SOURCES += \
    source/ExerciseTypePieChart.cpp \
    source/AccountWindow.cpp \
    source/HorizontalInputBox.cpp \
    source/InputBox.cpp \
    source/LoginWindow.cpp \
    source/MainWindow.cpp \
    source/RegistrationWindow.cpp \
    source/SettingsWindow.cpp \
    source/StatisticsWindow.cpp \
    source/VerticalInputBox.cpp \
    source/WindowFactory.cpp \
    source/main.cpp

HEADERS += \
    source/ExerciseTypePieChart.hpp \
    source/AccountWindow.hpp \
    source/HorizontalInputBox.hpp \
    source/InputBox.hpp \
    source/LoginWindow.hpp \
    source/MainWindow.hpp \
    source/RegistrationWindow.hpp \
    source/SettingsWindow.hpp \
    source/StatisticsWindow.hpp \
    source/VerticalInputBox.hpp \
    source/WindowFactory.hpp

TRANSLATIONS += \
    fast_typing_ui_en_US.ts


LIBS += -L$${PWD}/../binaries/$${DESTINATION_PATH} -lfast-typing-lib

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
