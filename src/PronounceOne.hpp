#ifndef PRONOUNCEONE_HPP
#define PRONOUNCEONE_HPP

#include "PronounceData.hpp"
#include "TaskChooser.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class PronounceOne : public QWidget{
    Q_OBJECT

public:
    PronounceOne(QDir dataDir, TaskChooser& tc);

public slots:
    void showNext();
    void playAgain();

private:
    TaskChooser& tc;

    PronounceData data;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *text;
};

#endif // PRONOUNCEONE_HPP
