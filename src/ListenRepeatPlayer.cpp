#include "ListenRepeatPlayer.hpp"

ListenRepeatPlayer::ListenRepeatPlayer(QDir _dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dataDir(_dataDir)
{
    if (!dataDir.cd("./repeat/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/repeat/");
        throw(-1);
    }

    if (!dataDir.exists("per.dat") || !dataDir.exists("tikkaajat.dat")) {
        QMessageBox::critical(0, "Missing Data!", "Data files missing from lessons/repeat/");
        throw(-1);
    }

    setWindowTitle(tr("Lyt, forstå, gentag"));

    media = new Phonon::MediaObject;
    video = new Phonon::VideoWidget;
    Phonon::createPath(media, video);

    audio = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(media, audio);

    CryptFile *mediafile = new CryptFile(dataDir.absoluteFilePath("per.dat"));
    media->setCurrentSource(mediafile);
    mediafile = new CryptFile(dataDir.absoluteFilePath("tikkaajat.dat"));
    media->enqueue(mediafile);
    media->setTickInterval(1000);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

    video->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    QHBoxLayout *qhbl = new QHBoxLayout;
    QPushButton *perAgain = new QPushButton(tr("Se Per igen"));
    connect(perAgain, SIGNAL(clicked()), this, SLOT(playPerAgain()));
    qhbl->addWidget(perAgain);

    QPushButton *tikaAgain = new QPushButton(tr("Se Tikkaajat igen"));
    connect(tikaAgain, SIGNAL(clicked()), this, SLOT(playTikaAgain()));
    qhbl->addWidget(tikaAgain);

    qvbl->addLayout(qhbl);

    playpause = new QPushButton(style()->standardIcon(QStyle::SP_MediaPause), "Pause", this);
    playpause->setShortcut(QString("Space"));
    connect(playpause, SIGNAL(clicked()), this, SLOT(togglePlay()));

    seeker = new Phonon::SeekSlider(this);
    seeker->setMediaObject(media);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    qhbl = new QHBoxLayout;
    qhbl->addWidget(playpause, 1);
    qhbl->addWidget(seeker, 96);
    qhbl->addWidget(timeLcd, 1);

    qvbl->addLayout(qhbl);

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
}

void ListenRepeatPlayer::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
    event->accept();
}

void ListenRepeatPlayer::show() {
    QWidget::show();
    media->play();
}

void ListenRepeatPlayer::tick(qint64 time) {
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void ListenRepeatPlayer::togglePlay() {
    if (media->state() == Phonon::PlayingState) {
        playpause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playpause->setText("Play");
        media->pause();
    }
    else {
        playpause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playpause->setText("Pause");
        media->play();
    }
}

void ListenRepeatPlayer::playPerAgain() {
    media->stop();
    media->clear();
    CryptFile *mediafile = new CryptFile(dataDir.absoluteFilePath("per.dat"));
    media->setCurrentSource(mediafile);
    media->play();
}

void ListenRepeatPlayer::playTikaAgain() {
    media->stop();
    media->clear();
    CryptFile *mediafile = new CryptFile(dataDir.absoluteFilePath("tikkaajat.dat"));
    media->setCurrentSource(mediafile);
    media->play();
}

QSize ListenRepeatPlayer::sizeHint() const {
    return QSize(1100, 680);
}

QSize ListenRepeatPlayer::minimumSizeHint() const {
    return QSize(1100, 680);
}
