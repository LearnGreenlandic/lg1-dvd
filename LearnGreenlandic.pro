QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.4

QT += core gui phonon opengl

TARGET = LearnGreenlandic
TEMPLATE = app

SOURCES += \
    src/LearnGreenlandic.cpp \
    src/TaskChooser.cpp \
    src/ScalingGraphicsView.cpp \
    src/Lecture1Danish.cpp \
    src/Lecture2Danish.cpp \
    src/UpdownData.cpp \
    src/UpdownOne.cpp \
    src/UpdownTwo.cpp \
    src/UpdownThree.cpp \
    src/StructureData.cpp \
    src/StructureOne.cpp \
    src/StructureTwo.cpp \
    src/StructureThree.cpp \
    src/CryptFile.cpp

HEADERS  += \
    src/Constants.hpp \
    src/TaskChooser.hpp \
    src/ScalingGraphicsView.hpp \
    src/Lecture1Danish.hpp \
    src/Lecture2Danish.hpp \
    src/UpdownData.hpp \
    src/UpdownOne.hpp \
    src/UpdownTwo.hpp \
    src/UpdownThree.hpp \
    src/StructureData.hpp \
    src/StructureOne.hpp \
    src/StructureTwo.hpp \
    src/StructureThree.hpp \
    src/CryptFile.hpp

CONFIG -= warn_off
CONFIG += warn_on
QMAKE_CFLAGS   += -Wall -Wextra
QMAKE_CXXFLAGS += -Wall -Wextra
