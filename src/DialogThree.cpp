#include "DialogThree.hpp"

DialogThree::DialogThree(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
data(dataDir, tr("danish.txt")),
curAt(-1)
{
    setWindowTitle(tr("Minidialog 1.3: Stil spørgsmål"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Den sidste øvelse i denne omgang er en simpel husk/oversæt-øvelse. Koncentrer dig om at huske Beatrines sætninger. Formuler dem selv højt, lyt til Beatrine igen og gentag til sidst hendes sætning. Du får Tikas responser serveret som lidt memoteknisk hjælp."));
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

void DialogThree::playAgainQ() {
    mediaQ->stop();
    mediaQ->seek(0);
    mediaQ->play();
}

void DialogThree::playAgainA() {
    mediaA->stop();
    mediaA->seek(0);
    mediaA->play();
}

void DialogThree::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.phrases.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("Færdig!"), tr("Der er ikke mere i denne øvelse. Vil du fortsætte med næste øvelse?"));
        QPushButton *yes = mbox.addButton(tr("Ja, næste øvelse"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showPronounceTwo();
        }
        close();
        return;
    }

    labelQ->setText(QString("<h2>") + data.phrases.at(curAt).at(4) + "</h2>");
    labelQ->setToolTip(QString("<h2>") + data.phrases.at(curAt).at(2));
    mediaQ->setCurrentSource(data.phrases.at(curAt).at(0));

    labelA->setText(QString("<h2>") + data.phrases.at(curAt).at(3) + "</h2>");
    labelA->setToolTip(QString("<h2>") + data.phrases.at(curAt).at(5) + "</h2>");
    mediaA->setCurrentSource(data.phrases.at(curAt).at(1));

    adjustSize();
}
