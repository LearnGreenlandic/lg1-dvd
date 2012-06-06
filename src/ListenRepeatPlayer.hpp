#ifndef LISTENREPEATPLAYER_HPP
#define LISTENREPEATPLAYER_HPP

#include "CryptFile.hpp"
#include "TaskChooser.hpp"
#include <QtGui>

#if defined(Q_WS_WIN)

#include <QAxWidget>
#include <QAxObject>

class ListenRepeatPlayer : public QWidget {
    Q_OBJECT

public:
    ListenRepeatPlayer(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void playStateChange(int);
    void playPerAgain();
    void playTikaAgain();

private:
    TaskChooser& tc;

    QDir dataDir;

    QAxWidget *video;
    QAxObject *controls;
    QString tmpfile_per, tmpfile_tik;
    QString current;
};

#else

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>
#include <phonon/effect.h>

class ListenRepeatPlayer : public QWidget {
    Q_OBJECT

public:
    ListenRepeatPlayer(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();
    void playPerAgain();
    void playTikaAgain();

private:
    TaskChooser& tc;

    QDir dataDir;

    Phonon::MediaObject *media;
    Phonon::VideoWidget *video;
    Phonon::AudioOutput *audio;

    QPushButton *playpause;
    Phonon::SeekSlider *seeker;
    QLCDNumber *timeLcd;
};

#endif

#endif // LISTENREPEATPLAYER_HPP
