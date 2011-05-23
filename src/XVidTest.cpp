#include "XVidTest.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>

XVidTest::XVidTest(QWidget *parent, QDir dataDir) :
QWidget(parent, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
    setWindowModality(Qt::WindowModal);
    setWindowTitle(tr("XVid test"));

    if (!dataDir.exists("testxvid.avi")) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate testxvid.avi!");
        throw(-1);
    }

    Phonon::MediaObject *media = new Phonon::MediaObject;
    Phonon::VideoWidget *video = new Phonon::VideoWidget;
    Phonon::createPath(media, video);

    Phonon::AudioOutput *audio = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(media, audio);

    media->setCurrentSource(dataDir.absoluteFilePath("testxvid.avi"));
    connect(media, SIGNAL(finished()), this, SLOT(finished()));

    video->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
}

void XVidTest::finished() {

}