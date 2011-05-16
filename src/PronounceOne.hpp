#ifndef PRONOUNCEONE_HPP
#define PRONOUNCEONE_HPP

#include "PronounceData.hpp"
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class PronounceOne : public QWidget{
    Q_OBJECT

public:
    PronounceOne(QDir dataDir);

public slots:
    void show();
    void showNext();
    void playAgain();

private:
    PronounceData data;
    uint32_t curAt;

    QVBoxLayout *curWord;
    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *text;
};

#endif // PRONOUNCEONE_HPP
