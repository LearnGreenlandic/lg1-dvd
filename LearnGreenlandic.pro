QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.4

QT += core gui phonon opengl

TARGET = LearnGreenlandic
TEMPLATE = app

TRANSLATIONS = texts_da.ts texts_en.ts

SOURCES += \
    src/LearnGreenlandic.cpp \
    src/TaskChooser.cpp \
    src/ScalingGraphicsView.cpp \
    src/UpdownData.cpp \
    src/UpdownOne.cpp \
    src/UpdownTwo.cpp \
    src/UpdownThree.cpp \
    src/StructureData.cpp \
    src/StructureOne.cpp \
    src/StructureTwo.cpp \
    src/StructureThree.cpp \
    src/CryptFile.cpp \
    src/LecturePlayer.cpp \
    src/PronounceData.cpp \
    src/PronounceOne.cpp \
    src/PronounceTwo.cpp \
    src/WelcomeOne.cpp \
    src/WelcomeTwo.cpp \
    src/HyphenOne.cpp \
    src/ListenOne.cpp \
    src/ListenTwo.cpp \
    src/ListenThree.cpp

HEADERS  += \
    src/TaskChooser.hpp \
    src/ScalingGraphicsView.hpp \
    src/UpdownData.hpp \
    src/UpdownOne.hpp \
    src/UpdownTwo.hpp \
    src/UpdownThree.hpp \
    src/StructureData.hpp \
    src/StructureOne.hpp \
    src/StructureTwo.hpp \
    src/StructureThree.hpp \
    src/CryptFile.hpp \
    src/LecturePlayer.hpp \
    src/PronounceData.hpp \
    src/PronounceOne.hpp \
    src/PronounceTwo.hpp \
    src/WelcomeOne.hpp \
    src/WelcomeTwo.hpp \
    src/HyphenOne.hpp \
    src/ListenOne.hpp \
    src/ListenTwo.hpp \
    src/ListenThree.hpp

CONFIG -= warn_off
CONFIG += warn_on
QMAKE_CFLAGS   += -Wall -Wextra
QMAKE_CXXFLAGS += -Wall -Wextra
