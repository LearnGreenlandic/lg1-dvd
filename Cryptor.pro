QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11

QT += core gui
QT -= opengl

TARGET = Cryptor
TEMPLATE = app

SOURCES += \
    src/Cryptor.cpp \
    src/CryptFile.cpp

HEADERS  += \
    src/CryptFile.hpp

CONFIG -= warn_off
CONFIG += warn_on
