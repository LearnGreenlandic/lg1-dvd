#include "LecturePlayer.hpp"
#if defined(Q_OS_WIN)

#include <QProgressDialog>
#include <QCryptographicHash>
#include <iostream>

LecturePlayer::LecturePlayer(TaskChooser& tc, QString lecDir, QString title) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    setWindowTitle(title);
    setMinimumSize(minimumSizeHint());

    QString lecfile = find_newest(tc.dirs, lecDir + "/lecture.dat");
    if (lecfile.isEmpty()) {
        QMessageBox::critical(0, "Missing Lecture Data!", "Could not locate lecture.dat!");
        throw(-1);
    }

    QString slide0 = find_newest(tc.dirs, lecDir + "/0.png");
    if (slide0.isEmpty()) {
        QMessageBox::critical(0, "Missing Slides!", "Could not locate slides for lecture!");
        throw(-1);
    }

    QFileInfoList slideFiles = QDir(QFileInfo(slide0).absoluteDir()).entryInfoList(QStringList() << "*.png");
    foreach (QFileInfo slideFile, slideFiles) {
        uint32_t key = slideFile.baseName().toULong();
        slides[key] = slideFile.canonicalFilePath();
    }

    video = new QAxWidget("{6BF52A52-394A-11D3-B153-00C04F79FAA6}");
    controls = video->querySubObject("controls");

    tmpfile = decrypt_to_tmp(lecfile);

    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);
    video->dynamicCall("setUiMode(QString)", "full");
    video->dynamicCall("setEnabled(bool)", true);
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(tmpfile));

    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

    QPixmap qpx;
    curSlide = slides.begin().value();
    qpx.load(curSlide);

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(QColor(0, 51, 102), Qt::SolidPattern));
    slide = scene->addPixmap(qpx);
    slide->setTransformationMode(Qt::SmoothTransformation);

    view = new ScalingGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setContentsMargins(0, 0, 0, 0);

    QGridLayout *qgl = new QGridLayout;
    qgl->addWidget(video, 0, 0);
    qgl->addWidget(view, 0, 1);
    qgl->setColumnStretch(0, 545);
    qgl->setColumnStretch(1, 455);
    qgl->setSpacing(2);
    qgl->setContentsMargins(0, 0, 0, 0);

    setLayout(qgl);
    setContentsMargins(0, 0, 0, 0);
}

void LecturePlayer::closeEvent(QCloseEvent *event) {
    controls->dynamicCall("stop()");
    controls->clear();
    video->clear();
    QFile::remove(tmpfile);
    event->accept();
}

void LecturePlayer::show() {
    QWidget::show();
    controls->dynamicCall("play()");
}

void LecturePlayer::tick() {
    uint32_t i = controls->property("currentPosition").toDouble();

    QString nSlide = curSlide;
    slides_t::const_iterator it = slides.find(i);
    if (it != slides.end()) {
        nSlide = it.value();
    }
    else {
        it = slides.lowerBound(i);
        --it;
        nSlide = it.value();
    }
    if (nSlide != curSlide) {
        curSlide = nSlide;
        QPixmap qp;
        qp.load(curSlide);
        slide->setPixmap(qp);
        slide->update();
    }
}

QSize LecturePlayer::sizeHint() const {
    return QSize(1010, 335);
}

QSize LecturePlayer::minimumSizeHint() const {
    return QSize(1010, 335);
}

#else

LecturePlayer::LecturePlayer(TaskChooser& tc, QString lecDir, QString title) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    setWindowTitle(title);
    setMinimumSize(minimumSizeHint());

    QString lecfile = find_newest(tc.dirs, lecDir + "/lecture.dat");
    if (lecfile.isEmpty()) {
        QMessageBox::critical(0, "Missing Lecture Data!", "Could not locate lecture.dat!");
        throw(-1);
    }

    QString slide0 = find_newest(tc.dirs, lecDir + "/0.png");
    if (slide0.isEmpty()) {
        QMessageBox::critical(0, "Missing Slides!", "Could not locate slides for lecture!");
        throw(-1);
    }

    QFileInfoList slideFiles = QDir(QFileInfo(slide0).absoluteDir()).entryInfoList(QStringList() << "*.png");
    foreach (QFileInfo slideFile, slideFiles) {
        uint32_t key = slideFile.baseName().toULong();
        slides[key] = slideFile.canonicalFilePath();
    }

    media = new QMediaPlayer;
    video = new QVideoWidget;
    media->setVideoOutput(video);

    tmpfile = decrypt_to_tmp(lecfile);
    media->setMedia(QUrl::fromLocalFile(tmpfile));
    media->setNotifyInterval(1000);
    connect(media, SIGNAL(positionChanged(qint64)), this, SLOT(tick(qint64)));

    video->setAspectRatioMode(Qt::KeepAspectRatio);
    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);

    QPixmap qpx;
    curSlide = slides.begin().value();
    qpx.load(curSlide);

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(QColor(0, 51, 102), Qt::SolidPattern));
    slide = scene->addPixmap(qpx);
    slide->setTransformationMode(Qt::SmoothTransformation);

    view = new ScalingGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setContentsMargins(0, 0, 0, 0);

    QGridLayout *qgl = new QGridLayout;
    qgl->addWidget(video, 0, 0);
    qgl->addWidget(view, 0, 1);
    qgl->setColumnStretch(0, 545);
    qgl->setColumnStretch(1, 455);
    qgl->setSpacing(2);
    qgl->setContentsMargins(0, 0, 0, 0);

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

    qgl->addLayout(qhbl, 1, 0, 1, 2);

    setLayout(qgl);
    setContentsMargins(0, 0, 0, 0);
}

void LecturePlayer::closeEvent(QCloseEvent *event) {
    media->stop();
    media->setMedia(QMediaContent());
    QFile::remove(tmpfile);
    event->accept();
}

void LecturePlayer::show() {
    QWidget::show();
    media->play();
}

void LecturePlayer::tick(qint64 time) {
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeLcd->display(displayTime.toString("mm:ss"));

    uint32_t i = time/1000;
    QString nSlide = curSlide;
    slides_t::const_iterator it = slides.find(i);
    if (it != slides.end()) {
        nSlide = it.value();
    }
    else {
        it = slides.lowerBound(time/1000);
        --it;
        nSlide = it.value();
    }
    if (nSlide != curSlide) {
        curSlide = nSlide;
        QPixmap qp;
        qp.load(curSlide);
        slide->setPixmap(qp);
        slide->update();
    }
}

void LecturePlayer::togglePlay() {
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

QSize LecturePlayer::sizeHint() const {
    return QSize(1010, 335);
}

QSize LecturePlayer::minimumSizeHint() const {
    return QSize(1010, 335);
}

#endif
