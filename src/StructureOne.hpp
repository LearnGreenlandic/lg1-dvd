#ifndef STRUCTUREONE_HPP
#define STRUCTUREONE_HPP

#include "StructureData.hpp"
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class StructureOne : public QWidget {
    Q_OBJECT

public:
    StructureOne(QDir dataDir);

public slots:
    void show();
    void showNext();
    void playAgain();
    void checkInput();
    void yieldWord();

private:
    StructureData data;
    uint32_t curAt;

    QVBoxLayout *curWord;
    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTUREONE_HPP
