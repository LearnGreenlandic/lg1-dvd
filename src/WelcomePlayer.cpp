#include "WelcomePlayer.hpp"
#include "WelcomeQuestion.hpp"

WelcomePlayer::WelcomePlayer(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
tc(tc)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Velkommen til Gr�nlandsk for voksne!"));

    if (!dataDir.exists("welcome.dat")) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.dat!");
        throw(-1);
    }

    media = new Phonon::MediaObject;
    video = new Phonon::VideoWidget;
    Phonon::createPath(media, video);

    audio = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(media, audio);

    mediafile = new CryptFile(dataDir.absoluteFilePath("welcome.dat"));
    media->setCurrentSource(mediafile);
    media->setTickInterval(1000);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(media, SIGNAL(finished()), this, SLOT(finished()));

    video->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);

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

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
}

void WelcomePlayer::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
    event->accept();
}

void WelcomePlayer::show() {
    QWidget::show();
    media->play();
}

void WelcomePlayer::tick(qint64 time) {
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void WelcomePlayer::togglePlay() {
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

void WelcomePlayer::finished() {
    QMessageBox mbox(QMessageBox::Question, tr("Forst�et?"), tr("Forstod du alt hvad Tikaajaat sagde i velkomstfilmen?"));
    QPushButton *yes = mbox.addButton(tr("Ja, selvf�lgelig"), QMessageBox::YesRole);
    mbox.addButton(tr("Nej, l�r mig det"), QMessageBox::NoRole);
    mbox.exec();

    if (mbox.clickedButton() == yes) {
        WelcomeQuestion *wc = new WelcomeQuestion(tc);
        wc->show();
        close();
        return;
    }

    tc.showLectureOne();
    close();
}

QSize WelcomePlayer::sizeHint() const {
    return QSize(1100, 680);
}

QSize WelcomePlayer::minimumSizeHint() const {
    return QSize(1100, 680);
}
