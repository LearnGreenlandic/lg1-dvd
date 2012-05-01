#ifndef WELCOMEPLAYER_H
#define WELCOMEPLAYER_H

#include "CryptFile.hpp"
#include "TaskChooser.hpp"
#include <QtGui>

#if defined(Q_WS_WIN)

#include <QAxWidget>
#include <QAxObject>

class WelcomePlayer : public QWidget {
    Q_OBJECT

public:
    WelcomePlayer(QDir dataDir, TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void finished(int);

private:
    TaskChooser& tc;

    QAxWidget *video;
    QAxObject *controls;
    QString tmpfile;
};

#else

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>
#include <phonon/effect.h>

class WelcomePlayer : public QWidget {
    Q_OBJECT

public:
    WelcomePlayer(QDir dataDir, TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void finished();
    void togglePlay();

private:
    TaskChooser& tc;

    CryptFile *mediafile;
    Phonon::MediaObject *media;
    Phonon::VideoWidget *video;
    Phonon::AudioOutput *audio;

    QPushButton *playpause;
    Phonon::SeekSlider *seeker;
    QLCDNumber *timeLcd;
};

#endif

#endif // WELCOMEPLAYER_H
