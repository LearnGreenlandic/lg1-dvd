#-------------------------------------------------
#
# Project created by QtCreator 2011-03-11T16:32:24
#
#-------------------------------------------------

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.4

QT       += core gui phonon opengl

TARGET = LearnGreenlandic
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/Lecture1Danish.cpp \
    src/ScalingGraphicsView.cpp \
    src/TaskChooser.cpp \
    src/Lecture2Danish.cpp \
    src/UpdownOne.cpp

HEADERS  += \
    src/Lecture1Danish.hpp \
    src/constants.hpp \
    src/ScalingGraphicsView.hpp \
    src/TaskChooser.hpp \
    src/Lecture2Danish.hpp \
    src/UpdownOne.hpp

CONFIG -= warn_off
CONFIG -= warn_on
QMAKE_CFLAGS   += -Wall -Wextra
QMAKE_CXXFLAGS += -Wall -Wextra
