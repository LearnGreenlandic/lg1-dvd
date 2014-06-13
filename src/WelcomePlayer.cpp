#include "WelcomePlayer.hpp"
#include "WelcomeQuestion.hpp"
#include <QProgressDialog>
#include <QCryptographicHash>
#include <iostream>

#if defined(Q_OS_WIN)

WelcomePlayer::WelcomePlayer(TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Velkommen til Grønlandsk for voksne!"));

    QString f_w = find_newest(tc.dirs, "welcome.dat");
    if (f_w.isEmpty()) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.dat!");
        throw(-1);
    }

    video = new QAxWidget("{6BF52A52-394A-11D3-B153-00C04F79FAA6}");
    controls = video->querySubObject("controls");

    tmpfile = decrypt_to_tmp(f_w);

    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);
    video->dynamicCall("setUiMode(QString)", "none");
    video->dynamicCall("setEnabled(bool)", true);
    video->dynamicCall("setEnableContextMenu(bool)", false);
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(tmpfile));
    connect(video, SIGNAL(PlayStateChange(int)), this, SLOT(finished(int)));

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
}

void WelcomePlayer::closeEvent(QCloseEvent *event) {    
    controls->dynamicCall("stop()");
    controls->clear();
    video->clear();
    QFile::remove(tmpfile);
    event->accept();
}

void WelcomePlayer::show() {
    QWidget::show();
    controls->dynamicCall("play()");
}

void WelcomePlayer::finished(int state) {
    if (state != 8) {
        return;
    }

    QMessageBox mbox(QMessageBox::Question, tr("Forstået?"), tr("Forstod du alt hvad Tikaajaat sagde i velkomstfilmen?"));
    QPushButton *yes = mbox.addButton(tr("Ja, selvfølgelig"), QMessageBox::YesRole);
    mbox.addButton(tr("Nej, lær mig det"), QMessageBox::NoRole);
    mbox.exec();

    if (mbox.clickedButton() == yes) {
        WelcomeQuestion *wc = new WelcomeQuestion(tc);
        wc->show();
        QTimer::singleShot(1000, this, SLOT(close()));
        return;
    }

    QTimer::singleShot(500, this, SLOT(close()));
    QTimer::singleShot(1000, &tc, SLOT(showLectureOne()));
}

#else

WelcomePlayer::WelcomePlayer(TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Velkommen til Grønlandsk for voksne!"));

    QString f_w = find_newest(tc.dirs, "welcome.dat");
    if (f_w.isEmpty()) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.dat!");
        throw(-1);
    }

    media = new QMediaPlayer;
    video = new QVideoWidget;
    media->setVideoOutput(video);

    tmpfile = decrypt_to_tmp(f_w);
    media->setMedia(QUrl::fromLocalFile(tmpfile));
    media->setNotifyInterval(1000);
    connect(media, SIGNAL(positionChanged(qint64)), this, SLOT(tick(qint64)));
    connect(media, SIGNAL(finished()), this, SLOT(finished()));

    video->setAspectRatioMode(Qt::KeepAspectRatio);
    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    playpause = new QPushButton(style()->standardIcon(QStyle::SP_MediaPause), "Pause", this);
    playpause->setShortcut(QString("Space"));
    connect(playpause, SIGNAL(clicked()), this, SLOT(togglePlay()));

    //seeker = new QMediaPlayer::SeekSlider(this);
    //seeker->setMediaObject(media);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    QHBoxLayout *qhbl = new QHBoxLayout;
    qhbl->addWidget(playpause, 1);
    //qhbl->addWidget(seeker, 96);
    qhbl->addWidget(timeLcd, 1);

    qvbl->addLayout(qhbl);

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
}

void WelcomePlayer::closeEvent(QCloseEvent *event) {
    media->stop();
    media->setMedia(QMediaContent());
    QFile::remove(tmpfile);
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
    if (media->state() == QMediaPlayer::PlayingState) {
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
    QMessageBox mbox(QMessageBox::Question, tr("Forstået?"), tr("Forstod du alt hvad Tikaajaat sagde i velkomstfilmen?"));
    QPushButton *yes = mbox.addButton(tr("Ja, selvfølgelig"), QMessageBox::YesRole);
    mbox.addButton(tr("Nej, lær mig det"), QMessageBox::NoRole);
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

#endif

QSize WelcomePlayer::sizeHint() const {
    return QSize(1100, 680);
}

QSize WelcomePlayer::minimumSizeHint() const {
    return QSize(1100, 680);
}
