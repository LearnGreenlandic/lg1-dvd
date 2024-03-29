QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11

QT += core gui multimedia multimediawidgets network
QT -= opengl

win32 {
    QT += axcontainer
}

TARGET = LearnGreenlandic
TEMPLATE = app

TRANSLATIONS = texts_da.ts texts_en.ts
CODECFORSRC = UTF-8
CODECFORTR = UTF-8

RC_FILE = lg.rc
ICON = icon.icns

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
    src/ListenThree.cpp \
    src/ListenFour.cpp \
    src/DialogData.cpp \
    src/DialogOne.cpp \
    src/DialogTwo.cpp \
    src/DialogThree.cpp \
    src/WelcomePlayer.cpp \
    src/ListenRepeatPlayer.cpp \
    src/WelcomeQuestion.cpp \
    src/XvidTest.cpp \
    src/WelcomeWords.cpp \
    src/ValidateKey.cpp \
    src/common.cpp

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
    src/ListenThree.hpp \
    src/ListenFour.hpp \
    src/DialogData.hpp \
    src/DialogOne.hpp \
    src/DialogTwo.hpp \
    src/DialogThree.hpp \
    src/WelcomePlayer.hpp \
    src/ListenRepeatPlayer.hpp \
    src/WelcomeQuestion.hpp \
    src/XvidTest.hpp \
    src/WelcomeWords.hpp \
    src/ValidateKey.hpp \
    src/common.hpp \
    src/files.hpp

CONFIG -= warn_off
CONFIG += warn_on
