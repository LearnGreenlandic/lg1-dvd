#include "WelcomeWords.hpp"
#include <QProgressDialog>
#include <QCryptographicHash>
#include <iostream>

#if defined(Q_OS_WIN)

WelcomeWords::WelcomeWords(TaskChooser& tc) :
QWidget(nullptr, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
curAt(-1)
{
    QString f_dat = find_newest(tc.dirs, "welcome.dat");
    if (f_dat.isEmpty()) {
        QMessageBox::critical(nullptr, "Missing Welcome Data!", "Could not locate welcome.dat!");
        throw(-1);
    }

    QString f_txt = find_newest(tc.dirs, "welcome.txt");
    if (f_txt.isEmpty()) {
        QMessageBox::critical(nullptr, "Missing Welcome Data!", "Could not locate welcome.txt!");
        throw(-1);
    }

    QFile input_f(f_txt);
    if (!input_f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "Read Error!", "Could not open welcome.txt from data folder!");
        throw(-1);
    }
    QTextStream input_t(&input_f);
    input_t.setCodec("UTF-8");
    QString input_s = input_t.readAll().trimmed();
    words = input_s.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    setWindowTitle(tr("Diktat af Tika's velkomst"));

    video = new QAxWidget("{6BF52A52-394A-11D3-B153-00C04F79FAA6}");
    controls = video->querySubObject("controls");

    tmpfile = decrypt_to_tmp(f_dat);

    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);
    video->dynamicCall("setUiMode(QString)", "full");
    video->dynamicCall("setEnabled(bool)", true);
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(tmpfile));

    auto *outerHBox = new QHBoxLayout;

    auto *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    outerHBox->addLayout(qvbl);

    qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Aflyt og nedkriv Tika's velkomst ord for ord."));
    //label->setWordWrap(true);
    qvbl->addWidget(label);

    qvbl->addSpacing(10);

    sum = new QLabel;
    sum->setWordWrap(true);
    qvbl->addWidget(sum);

    qvbl->addSpacing(10);

    query = new QLabel;
    qvbl->addWidget(query);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    QPushButton *check = new QPushButton(tr("Check"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton(tr("Giv op..."));
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(yield);
    result->hide();
    yield->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton(tr("Gå til næste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    qvbl->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    outerHBox->addLayout(qvbl);

    setLayout(outerHBox);

    setContentsMargins(0, 0, 0, 0);

    showNext();
}

void WelcomeWords::closeEvent(QCloseEvent *event) {
    controls->dynamicCall("stop()");
    controls->clear();
    video->clear();
    QFile::remove(tmpfile);
    event->accept();
}

void WelcomeWords::show() {
    QWidget::show();
    controls->dynamicCall("play()");
}

#else

WelcomeWords::WelcomeWords(TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
curAt(-1)
{
    QString f_dat = find_newest(tc.dirs, "welcome.dat");
    if (f_dat.isEmpty()) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.dat!");
        throw(-1);
    }

    QString f_txt = find_newest(tc.dirs, "welcome.txt");
    if (f_txt.isEmpty()) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate welcome.txt!");
        throw(-1);
    }

    QFile input_f(f_txt);
    if (!input_f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, "Read Error!", "Could not open welcome.txt from data folder!");
        throw(-1);
    }
    QTextStream input_t(&input_f);
    input_t.setCodec("UTF-8");
    QString input_s = input_t.readAll().trimmed();
    words = input_s.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    setWindowTitle(tr("Diktat af Tika's velkomst"));

    media = new QMediaPlayer;
    video = new QVideoWidget;
    media->setVideoOutput(video);

    tmpfile = decrypt_to_tmp(f_dat);
    media->setMedia(QUrl::fromLocalFile(tmpfile));
    media->setNotifyInterval(1000);
    connect(media, SIGNAL(positionChanged(qint64)), this, SLOT(tick(qint64)));

    video->setAspectRatioMode(Qt::KeepAspectRatio);
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

    outerHBox->addLayout(qvbl);

    qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Aflyt og nedkriv Tika's velkomst ord for ord."));
    //label->setWordWrap(true);
    qvbl->addWidget(label);

    qvbl->addSpacing(10);

    sum = new QLabel;
    sum->setWordWrap(true);
    qvbl->addWidget(sum);

    qvbl->addSpacing(10);

    query = new QLabel;
    qvbl->addWidget(query);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    QPushButton *check = new QPushButton(tr("Check"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton(tr("Giv op..."));
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(yield);
    result->hide();
    yield->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton(tr("Gå til næste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    qvbl->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    outerHBox->addLayout(qvbl);

    setLayout(outerHBox);

    setContentsMargins(0, 0, 0, 0);

    showNext();
}

void WelcomeWords::closeEvent(QCloseEvent *event) {
    media->stop();
    media->setMedia(QMediaContent());
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

#endif

void WelcomeWords::showNext() {
    ++curAt;

    QString sumtext = "<i>";
    for (uint32_t i=0 ; i<curAt ; ++i) {
        sumtext += words.at(i) + " ";
    }
    sumtext += " ...</i>";
    sum->setText(sumtext);

    if (curAt >= static_cast<uint32_t>(words.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("Færdig!"), tr("Der er ikke mere i denne øvelse. Vil du læse forelæsningen som PDF?"));
        QPushButton *yes = mbox.addButton(tr("Ja, åben PDF"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showLectureFourPDF();
        }
        close();
        return;
    }

    query->setText(tr("Skriv ord nummer %1:").arg(curAt+1));

    input->setFocus();
    input->setText("");

    result->hide();
    yield->hide();

    adjustSize();
}

void WelcomeWords::checkInput() {
    QString text = input->text();
    text.replace(QRegExp("\\W+"), "");

    QString correct = words.at(curAt);
    correct.replace(QRegExp("\\W+"), "");

    if (text == correct) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + "</b></span></center>");
        yield->hide();
    }
    else if (text.compare(correct, Qt::CaseInsensitive) == 0) {
        result->setText(QString("<center><span style='color: darkyellow;'><b>") + tr("Næsten korrekt.\nStore og små bogstaver gælder...") + "</b></span></center>");
        yield->show();
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    input->selectAll();
    adjustSize();
}

void WelcomeWords::yieldWord() {
    QMessageBox::information(nullptr, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte ord var:") + QString("</h1><br>") + words.at(curAt));
    showNext();
}

QSize WelcomeWords::sizeHint() const {
    return {1010, 335};
}

QSize WelcomeWords::minimumSizeHint() const {
    return {1010, 335};
}
