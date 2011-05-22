#include "DialogTwo.hpp"

DialogTwo::DialogTwo(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir, tr("danish.txt")),
curAt(-1)
{
    setWindowTitle(tr("Minidialog 1.2: Giv respons"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Anden øvelse er lidt vanskeligere, for nu er der også lidt indhold med i spillet. Du får først Beatrines sætninger som du så skal give et fornuftigt respons på!"));
    label->setWordWrap(true);
    qvbl->addWidget(label);

    qvbl->addSpacing(15);

    mediaQ = new Phonon::MediaObject;
    audioQ = new Phonon::AudioOutput;
    Phonon::createPath(mediaQ, audioQ);

    labelQ = new QLabel;
    QPushButton *againQ = new QPushButton(tr("Hør spørgsmålet"));
    connect(againQ, SIGNAL(clicked()), this, SLOT(playAgainQ()));
    qvbl->addWidget(labelQ);
    qvbl->addWidget(againQ);

    mediaA = new Phonon::MediaObject;
    audioA = new Phonon::AudioOutput;
    Phonon::createPath(mediaA, audioA);

    labelA = new QLabel;
    QPushButton *againA = new QPushButton(tr("Hør svaret"));
    connect(againA, SIGNAL(clicked()), this, SLOT(playAgainA()));
    qvbl->addWidget(labelA);
    qvbl->addWidget(againA);

    qvbl->addSpacing(15);

    QPushButton *next = new QPushButton(tr("Næste dialog"));
    connect(next, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(next);

    setLayout(qvbl);

    setMinimumWidth(250);

    showNext();
}

void DialogTwo::playAgainQ() {
    mediaQ->stop();
    mediaQ->seek(0);
    mediaQ->play();
}

void DialogTwo::playAgainA() {
    mediaA->stop();
    mediaA->seek(0);
    mediaA->play();
}

void DialogTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.phrases.size())) {
        QMessageBox::information(0, tr("Færdig!"), tr("Der er ikke flere fraser...vinduet lukker sig selv nu."));
        close();
        return;
    }

    labelQ->setText(QString("<h2>") + data.phrases.at(curAt).at(2) + "</h2>");
    labelQ->setToolTip(data.phrases.at(curAt).at(4));
    mediaQ->setCurrentSource(data.phrases.at(curAt).at(0));

    labelA->setText(QString("<h2>") + data.phrases.at(curAt).at(5) + "</h2>");
    labelA->setToolTip(data.phrases.at(curAt).at(3));
    mediaA->setCurrentSource(data.phrases.at(curAt).at(1));

    adjustSize();
    playAgainQ();
}
