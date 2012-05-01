#ifndef XVIDTEST_HPP
#define XVIDTEST_HPP

#include <QtGui>

#if defined(Q_WS_WIN)

#include <QAxWidget>
#include <QAxObject>

class XvidTest : public QDialog {
    Q_OBJECT

public:
    XvidTest(QDir dataDir);

    void closeEvent(QCloseEvent *event);

public slots:
    void finished();

private:
    QAxWidget *video;
    QAxObject *controls;
};

#else

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>

class XvidTest : public QDialog {
    Q_OBJECT

public:
    XvidTest(QDir dataDir);

    void closeEvent(QCloseEvent *event);

public slots:
    void finished();

private:
    Phonon::MediaObject *media;
    Phonon::VideoWidget *video;
    Phonon::AudioOutput *audio;
};

#endif

#endif // XVIDTEST_HPP
