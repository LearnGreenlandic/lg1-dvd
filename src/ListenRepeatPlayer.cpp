#include "ListenRepeatPlayer.hpp"
#include <QProgressDialog>
#include <QCryptographicHash>
#include <iostream>

#if defined(Q_WS_WIN)

ListenRepeatPlayer::ListenRepeatPlayer(TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    QString f_d = find_newest(tc.dirs, "./repeat/per.dat");
    dataDir = QDir(f_d.replace("per.dat", ""));
    if (!dataDir.exists()) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/repeat/");
        throw(-1);
    }

    if (!dataDir.exists("per.dat") || !dataDir.exists("tikaajaat.dat")) {
        QMessageBox::critical(0, "Missing Data!", "Data files missing from lessons/repeat/");
        throw(-1);
    }

    setWindowTitle(tr("Lyt, forstå, gentag"));

    video = new QAxWidget("{6BF52A52-394A-11D3-B153-00C04F79FAA6}");
    controls = video->querySubObject("controls");

    QDir tmpdir(QDir::tempPath());

    QCryptographicHash sha1(QCryptographicHash::Sha1);
    sha1.addData(dataDir.absoluteFilePath("per.dat").toUtf8());
    tmpfile_per = tmpdir.absoluteFilePath(QString(sha1.result().toHex()) + "-per.avi");

    sha1.reset();
    sha1.addData(dataDir.absoluteFilePath("tikaajaat.dat").toUtf8());
    tmpfile_tik = tmpdir.absoluteFilePath(QString(sha1.result().toHex()) + "-tikaajaat.avi");

    if (!tmpdir.exists(tmpfile_per)) {
        CryptFile input(dataDir.absoluteFilePath("per.dat"));
        QFile output(tmpfile_per);

        input.open(QIODevice::ReadOnly);
        output.open(QIODevice::WriteOnly);

        QProgressDialog progress("Transcoding for Windows Media Player...", "", 0, input.size(), this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setCancelButton(0);

        char buf[32768];
        qint64 r;
        while (!input.atEnd() && (r = input.read(buf, sizeof(buf))) > 0) {
            if (output.write(buf, r) <= 0) {
                std::cerr << "Write failed at offsets " << input.pos() << ", " << output.pos() << std::endl;
                throw(-1);
            }
            progress.setValue(input.pos());
        }
        progress.setValue(input.size());

        output.close();
        input.close();
    }

    if (!tmpdir.exists(tmpfile_tik)) {
        CryptFile input(dataDir.absoluteFilePath("tikaajaat.dat"));
        QFile output(tmpfile_tik);

        input.open(QIODevice::ReadOnly);
        output.open(QIODevice::WriteOnly);

        QProgressDialog progress("Transcoding for Windows Media Player...", "", 0, input.size(), this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setCancelButton(0);

        char buf[32768];
        qint64 r;
        while (!input.atEnd() && (r = input.read(buf, sizeof(buf))) > 0) {
            if (output.write(buf, r) <= 0) {
                std::cerr << "Write failed at offsets " << input.pos() << ", " << output.pos() << std::endl;
                throw(-1);
            }
            progress.setValue(input.pos());
        }
        progress.setValue(input.size());

        output.close();
        input.close();
    }

    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);
    video->dynamicCall("setUiMode(QString)", "full");
    video->dynamicCall("setEnabled(bool)", true);
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(tmpfile_per));
    current = tmpfile_per;
    connect(video, SIGNAL(PlayStateChange(int)), this, SLOT(playStateChange(int)));

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    QHBoxLayout *qhbl = new QHBoxLayout;

    QPushButton *perAgain = new QPushButton(tr("Se Per igen"));
    connect(perAgain, SIGNAL(clicked()), this, SLOT(playPerAgain()));
    qhbl->addWidget(perAgain);

    QPushButton *tikaAgain = new QPushButton(tr("Se Tikaajaat igen"));
    connect(tikaAgain, SIGNAL(clicked()), this, SLOT(playTikaAgain()));
    qhbl->addWidget(tikaAgain);

    QLabel *exp = new QLabel(tr("<b>Bemærk</b>: Tikaajaat bruger en form du ikke har lært endnu. I sidste ord siger hun <i>najugaqarlunga</i> i stedet for <i>najugaqarpunga</i>. På dette sted betyder de to ord præcis det samme, så lad være med at tænke for meget over det."));
    exp->setWordWrap(true);
    qhbl->addWidget(exp);
    qhbl->addSpacing(5);

    qvbl->addLayout(qhbl);

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
}

void ListenRepeatPlayer::closeEvent(QCloseEvent *event) {
    controls->dynamicCall("stop()");
    controls->clear();
    video->clear();
    QFile::remove(tmpfile_per);
    QFile::remove(tmpfile_tik);
    event->accept();
}

void ListenRepeatPlayer::show() {
    QWidget::show();
    controls->dynamicCall("play()");
}

void ListenRepeatPlayer::playStateChange(int state) {
    if (state == 8 && current == tmpfile_per) {
        QTimer::singleShot(250, this, SLOT(playTikaAgain()));
    }
}

void ListenRepeatPlayer::playPerAgain() {
    controls->dynamicCall("stop()");
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(tmpfile_per));
    controls->dynamicCall("play()");
}

void ListenRepeatPlayer::playTikaAgain() {
    controls->dynamicCall("stop()");
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(tmpfile_tik));
    current = tmpfile_tik;
    controls->dynamicCall("play()");
}

QSize ListenRepeatPlayer::sizeHint() const {
    return QSize(1100, 680);
}

QSize ListenRepeatPlayer::minimumSizeHint() const {
    return QSize(1100, 680);
}

#else

ListenRepeatPlayer::ListenRepeatPlayer(TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
{
    QString f_d = find_newest(tc.dirs, "./repeat/per.dat");
    dataDir = QDir(f_d.replace("per.dat", ""));
    if (!dataDir.exists()) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/repeat/");
        throw(-1);
    }

    if (!dataDir.exists("per.dat") || !dataDir.exists("tikaajaat.dat")) {
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
    mediafile = new CryptFile(dataDir.absoluteFilePath("tikaajaat.dat"));
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

    QPushButton *tikaAgain = new QPushButton(tr("Se Tikaajaat igen"));
    connect(tikaAgain, SIGNAL(clicked()), this, SLOT(playTikaAgain()));
    qhbl->addWidget(tikaAgain);

    QLabel *exp = new QLabel(tr("<b>Bemærk</b>: Tikaajaat bruger en form du ikke har lært endnu. I sidste ord siger hun <i>najugaqarlunga</i> i stedet for <i>najugaqarpunga</i>. På dette sted betyder de to ord præcis det samme, så lad være med at tænke for meget over det."));
    exp->setWordWrap(true);
    qhbl->addWidget(exp);
    qhbl->addSpacing(5);

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
    CryptFile *mediafile = new CryptFile(dataDir.absoluteFilePath("tikaajaat.dat"));
    media->setCurrentSource(mediafile);
    media->play();
}

QSize ListenRepeatPlayer::sizeHint() const {
    return QSize(1100, 680);
}

QSize ListenRepeatPlayer::minimumSizeHint() const {
    return QSize(1100, 680);
}

#endif
