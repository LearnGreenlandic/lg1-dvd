#include "LecturePlayer.hpp"

LecturePlayer::LecturePlayer(QString title, QDir dataDir, QString lecDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
{
    setWindowTitle(title);
    setMinimumSize(minimumSizeHint());

    if (!dataDir.cd(lecDir)) {
        QMessageBox::critical(0, "Missing Data!", QString("Could not change working folder to ") + dataDir.absoluteFilePath(lecDir) + "!");
        throw(-1);
    }

    if (!dataDir.exists("lecture.dat")) {
        QMessageBox::critical(0, "Missing Lecture Data!", "Could not locate lecture.dat!");
        throw(-1);
    }

    QFileInfoList slideFiles = dataDir.entryInfoList(QStringList() << "*.png");
    foreach (QFileInfo slideFile, slideFiles) {
        uint32_t key = slideFile.baseName().toULong();
        slides[key] = slideFile.canonicalFilePath();
    }

    media = new Phonon::MediaObject;
    video = new Phonon::VideoWidget;
    Phonon::createPath(media, video);

    audio = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(media, audio);

    mediafile = new CryptFile(dataDir.absoluteFilePath("lecture.dat"));
    media->setCurrentSource(mediafile);
    media->setTickInterval(1000);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(media, SIGNAL(finished()), this, SLOT(finished()));

    video->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
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

    qgl->addLayout(qhbl, 1, 0, 1, 2);

    setLayout(qgl);
    setContentsMargins(0, 0, 0, 0);
}

void LecturePlayer::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
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

void LecturePlayer::finished() {

}

QSize LecturePlayer::sizeHint() const {
    return QSize(1010, 335);
}

QSize LecturePlayer::minimumSizeHint() const {
    return QSize(1010, 335);
}
