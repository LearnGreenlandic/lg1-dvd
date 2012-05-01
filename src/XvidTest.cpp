#include "XvidTest.hpp"

#if defined(Q_WS_WIN)

XvidTest::XvidTest(QDir dataDir) :
QDialog(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Xvid test"));

    if (!dataDir.exists("testxvid.avi")) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate testxvid.avi!");
        throw(-1);
    }

    video = new QAxWidget("{6BF52A52-394A-11D3-B153-00C04F79FAA6}");
    controls = video->querySubObject("controls");

    QTimer::singleShot(6000, this, SLOT(finished()));

    video->setMinimumSize(400, 225);
    video->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    video->setContentsMargins(0, 0, 0, 0);
    video->dynamicCall("setUiMode(QString)", "full");
    video->dynamicCall("setEnabled(bool)", true);
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(dataDir.absoluteFilePath("testxvid.avi")));

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->setContentsMargins(0, 0, 0, 0);
    qvbl->addWidget(video);

    setLayout(qvbl);

    setContentsMargins(0, 0, 0, 0);
    controls->dynamicCall("play()");
    adjustSize();
}

void XvidTest::closeEvent(QCloseEvent *event) {
    controls->dynamicCall("stop()");
    controls->clear();
    video->clear();
    event->accept();
}

#else

XvidTest::XvidTest(QDir dataDir) :
QDialog(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::ApplicationModal);
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
    QTimer::singleShot(6000, this, SLOT(finished()));
    //connect(media, SIGNAL(finished()), this, SLOT(finished()));

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
    adjustSize();
}

void XvidTest::closeEvent(QCloseEvent *event) {
    media->stop();
    media->clear();
    event->accept();
}

#endif

void XvidTest::finished() {
    QMessageBox mbox(QMessageBox::Question, tr("Virkede det?"), tr("Kunne du både se billede og høre lyd på testfilmen?"));
    QPushButton *yes = mbox.addButton(tr("Ja, det virkede"), QMessageBox::YesRole);
    mbox.addButton(tr("Nej, noget var galt"), QMessageBox::NoRole);
    mbox.exec();

    if (mbox.clickedButton() == yes) {
        QSettings settings;
        settings.setValue("has_xvid", true);
    }
    close();
}
