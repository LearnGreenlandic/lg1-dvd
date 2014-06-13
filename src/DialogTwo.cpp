#include "DialogTwo.hpp"

DialogTwo::DialogTwo(TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
data(tc.dirs, tr("danish.txt")),
curAt(-1)
{
    setWindowTitle(tr("Minidialog 1.2: Giv respons"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Anden øvelse er lidt vanskeligere, for nu er der også lidt indhold med i spillet. Du får først Beatrines sætninger som du så skal give et fornuftigt respons på!"));
    label->setWordWrap(true);
    qvbl->addWidget(label);

    qvbl->addSpacing(15);

    mediaQ = new QMediaPlayer;

    labelQ = new QLabel;
    QPushButton *againQ = new QPushButton(tr("Hør spørgsmålet"));
    connect(againQ, SIGNAL(clicked()), this, SLOT(playAgainQ()));
    qvbl->addWidget(labelQ);
    qvbl->addWidget(againQ);

    mediaA = new QMediaPlayer;

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
    mediaQ->setPosition(0);
    mediaQ->play();
}

void DialogTwo::playAgainA() {
    mediaA->stop();
    mediaA->setPosition(0);
    mediaA->play();
}

void DialogTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.phrases.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("Færdig!"), tr("Der er ikke mere i denne øvelse. Vil du fortsætte med næste øvelse?"));
        QPushButton *yes = mbox.addButton(tr("Ja, næste øvelse"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showDialogThree();
        }
        close();
        return;
    }

    labelQ->setText(QString("<h2>") + data.phrases.at(curAt).at(2) + "</h2>");
    labelQ->setToolTip(QString("<h2>") + data.phrases.at(curAt).at(4) + "</h2>");
    mediaQ->setMedia(QUrl::fromLocalFile(data.phrases.at(curAt).at(0)));

    labelA->setText(QString("<h2>") + data.phrases.at(curAt).at(5) + "</h2>");
    labelA->setToolTip(QString("<h2>") + data.phrases.at(curAt).at(3) + "</h2>");
    mediaA->setMedia(QUrl::fromLocalFile(data.phrases.at(curAt).at(1)));

    adjustSize();
    playAgainQ();
}
