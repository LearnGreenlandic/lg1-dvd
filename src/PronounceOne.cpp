#include "PronounceOne.hpp"

PronounceOne::PronounceOne(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
data(dataDir),
curAt(-1)
{
    setWindowTitle(tr("Udtale�velse 1.1: Gentag"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Lyt og gentag ordet."));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    text = new QLabel;
    qvbl->addWidget(text);

    qvbl->addSpacing(5);

    QPushButton *again = new QPushButton(tr("Lyt igen"));
    connect(again, SIGNAL(clicked()), this, SLOT(playAgain()));
    qvbl->addWidget(again);

    qvbl->addSpacing(5);

    QPushButton *nb = new QPushButton(tr("G� til n�ste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);

    showNext();
}

void PronounceOne::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void PronounceOne::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.words.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("F�rdig!"), tr("Der er ikke mere i denne �velse. Vil du forts�tte med n�ste �velse?"));
        QPushButton *yes = mbox.addButton(tr("Ja, n�ste �velse"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showPronounceTwo();
        }
        close();
        return;
    }
    media->setCurrentSource(data.sounds[data.words.at(curAt)]);
    text->setText(QString("<h2>") + data.words.at(curAt) + "</h2>");
    adjustSize();
    playAgain();
}
