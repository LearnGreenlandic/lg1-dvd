#ifndef DIALOGONE_HPP
#define DIALOGONE_HPP

#include "DialogData.hpp"
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class DialogOne : public QWidget {
    Q_OBJECT

public:
    DialogOne(QDir dataDir);

public slots:
    void playAgainQ();
    void playAgainA();
    void showNext();

private:
    DialogData data;
    uint32_t curAt;

    QLabel *labelQ;
    Phonon::MediaObject *mediaQ;
    Phonon::AudioOutput *audioQ;
    QLabel *labelA;
    Phonon::MediaObject *mediaA;
    Phonon::AudioOutput *audioA;
};

#endif // DIALOGONE_HPP
