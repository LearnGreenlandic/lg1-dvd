#include "WelcomeWords.hpp"
#include "WelcomeQuestion.hpp"

WelcomeWords::WelcomeWords(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    if (!dataDir.exists("welcome.dat")) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.dat!");
        throw(-1);
    }

    if (!dataDir.exists("welcome.txt")) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.txt!");
        throw(-1);
    }

    setWindowTitle(tr("Diktat af Tika's velkomst"));

    media = new Phonon::MediaObject;
    video = new Phonon::VideoWidget;
    Phonon::createPath(media, video);

    audio = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(media, audio);

    mediafile = new CryptFile(dataDir.absoluteFilePath("welcome.dat"));
    media->setCurrentSource(mediafile);
    media->setTickInterval(1000);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

    video->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *outerHBox = new QHBoxLayout;

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    playpause = new QPushButton(style()->standardIcon(QStyle::SP_MediaPause), "Pause", this);
    playpause->setShortcut(QString("Space"));
    connect(playpause, SIGNAL(clicked()), this, SLOT(togglePlay()));

    seeker = new Phonon::SeekSlider(this);
    seeker->setMediaObject(media);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    QHBoxLayout *qhbl = new QHBoxLayout;
    qhbl->addWidget(playpause, 1);
    qhbl->addWidget(seeker, 96);
    qhbl->addWidget(timeLcd, 1);

    qvbl->addLayout(qhbl);

    outerHBox->addLayout(qvbl);

    qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Aflyt og nedkriv Tika's velkomst."));
    label->setWordWrap(true);

    setLayout(outerHBox);

    setContentsMargins(0, 0, 0, 0);
}

void WelcomeWords::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
    event->accept();
}

void WelcomeWords::show() {
    QWidget::show();
    media->play();
}

void WelcomeWords::tick(qint64 time) {
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void WelcomeWords::togglePlay() {
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

QSize WelcomeWords::sizeHint() const {
    return QSize(1100, 680);
}

QSize WelcomeWords::minimumSizeHint() const {
    return QSize(1100, 680);
}
