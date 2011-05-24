#ifndef XVIDTEST_HPP
#define XVIDTEST_HPP

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <QtGui>

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

#endif // XVIDTEST_HPP
