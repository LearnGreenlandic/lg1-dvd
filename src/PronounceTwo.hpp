#ifndef PRONOUNCETWO_HPP
#define PRONOUNCETWO_HPP

#include "PronounceData.hpp"
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class PronounceTwo : public QWidget {
    Q_OBJECT

public:
    PronounceTwo(QDir dataDir);

public slots:
    void show();
    void showNext();
    void playAgain();
    void checkInput();
    void yieldWord();

private:
    PronounceData data;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // PRONOUNCETWO_HPP
