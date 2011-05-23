#include "XvidTest.hpp"

XvidTest::XvidTest(QWidget *parent, QDir dataDir) :
QDialog(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::WindowModal);
    setWindowTitle(tr("Xvid test"));

    if (!dataDir.exists("testxvid.avi")) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate testxvid.avi!");
        throw(-1);
    }

    media = new Phonon::MediaObject;
    video = new Phonon::VideoWidget;
    Phonon::createPath(media, video);

    audio = new Phonon::AudioOutput(Phonon::VideoCategory);
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
    media->play();
}

void XvidTest::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
    event->accept();
}

void XvidTest::finished() {

}