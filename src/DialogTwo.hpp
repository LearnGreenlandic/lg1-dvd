#ifndef DIALOGTWO_HPP
#define DIALOGTWO_HPP

#include "DialogData.hpp"
#include "TaskChooser.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class DialogTwo : public QWidget {
    Q_OBJECT

public:
    DialogTwo(TaskChooser& tc);

public slots:
    void playAgainQ();
    void playAgainA();
    void showNext();

private:
    TaskChooser& tc;

    DialogData data;
    uint32_t curAt;

    QLabel *labelQ;
    Phonon::MediaObject *mediaQ;
    Phonon::AudioOutput *audioQ;
    QLabel *labelA;
    Phonon::MediaObject *mediaA;
    Phonon::AudioOutput *audioA;
};

#endif // DIALOGTWO_HPP
