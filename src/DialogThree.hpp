#ifndef DIALOGTHREE_HPP
#define DIALOGTHREE_HPP

#include "DialogData.hpp"
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class DialogThree : public QWidget {
    Q_OBJECT

public:
    DialogThree(QDir dataDir);

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

#endif // DIALOGTHREE_HPP
