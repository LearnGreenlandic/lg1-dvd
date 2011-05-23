#ifndef WELCOMEWORDS_H
#define WELCOMEWORDS_H

#include "CryptFile.hpp"
#include "TaskChooser.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>
#include <phonon/effect.h>
#include <QtGui>
#include <stdint.h>

class WelcomeWords : public QWidget {
    Q_OBJECT

public:
    WelcomeWords(QDir dataDir, TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();

private:
    TaskChooser& tc;

    QStringList words;
    uint32_t curAt;

    CryptFile *mediafile;
    Phonon::MediaObject *media;
    Phonon::VideoWidget *video;
    Phonon::AudioOutput *audio;

    QPushButton *playpause;
    Phonon::SeekSlider *seeker;
    QLCDNumber *timeLcd;

    QLabel *sum;
    QLabel *current;
    QLineEdit *input;
    QPushButton *check;
    QLabel *result;
    QPushButton *yield;
};

#endif // WELCOMEWORDS_H
