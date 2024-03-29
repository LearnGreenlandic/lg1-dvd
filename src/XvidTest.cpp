#include "XvidTest.hpp"

#if defined(Q_OS_WIN)

XvidTest::XvidTest(const QString& avi) :
QDialog(nullptr, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Xvid test"));

    if (avi.isEmpty()) {
        QMessageBox::critical(nullptr, "Missing Welcome Data!", "Could not locate testxvid.avi!");
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
    video->dynamicCall("SetURL(QString)", QUrl::fromLocalFile(avi));

    auto *qvbl = new QVBoxLayout;
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

XvidTest::XvidTest(QString avi) :
QDialog(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Xvid test"));

    if (avi.isEmpty()) {
        QMessageBox::critical(0, "Missing Welcome Data!", "Could not locate testxvid.avi!");
        throw(-1);
    }

    media = new QMediaPlayer;
    video = new QVideoWidget;
    media->setVideoOutput(video);

    media->setMedia(QUrl::fromLocalFile(avi));
    QTimer::singleShot(6000, this, SLOT(finished()));

    video->setAspectRatioMode(Qt::KeepAspectRatio);
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
    media->setMedia(QMediaContent());
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
