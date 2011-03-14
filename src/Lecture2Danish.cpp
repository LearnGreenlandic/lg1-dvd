#include "constants.hpp"
#include "Lecture2Danish.hpp"

#include <QGLShaderProgram>

Lecture2Danish::Lecture2Danish(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
    setWindowTitle("Forelæsning 2: Typiske Danskerfejl");
    setMinimumSize(minimumSizeHint());

    if (!dataDir.cd("./2/danish/")) {
        QMessageBox::critical(0, "Missing Data!", "Could not change working folder to lessons/2/danish/!");
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

    media->setCurrentSource(dataDir.absoluteFilePath(LECTURE_FILE));
    media->setTickInterval(1000);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

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
    QGLWidget *opengl = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    if (QGLFormat::hasOpenGL() && opengl->isValid()) {
        view->setViewport(opengl);
    }
    else {
        delete opengl;
    }
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

void Lecture2Danish::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
    event->accept();
}

void Lecture2Danish::show() {
    QWidget::show();
    media->play();
}

void Lecture2Danish::tick(qint64 time) {
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

void Lecture2Danish::togglePlay() {
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

QSize Lecture2Danish::sizeHint() const {
    return QSize(1010, 335);
}

QSize Lecture2Danish::minimumSizeHint() const {
    return QSize(1010, 335);
}
