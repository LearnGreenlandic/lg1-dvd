#include "ListenTwo.hpp"
#include <algorithm>
#include <random>

ListenTwo::ListenTwo(TaskChooser& tc) :
QWidget(nullptr, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
curAt(-1)
{
    QString f_d = find_newest(tc.dirs, "./listening/2/alla.wav");
    QDir dataDir(f_d.replace("alla.wav", ""));
    if (!dataDir.exists()) {
        QMessageBox::critical(nullptr, "Missing Data Folder!", "Could not change working folder to lessons/listening/2/");
        throw(-1);
    }

    QFileInfoList wordFiles = dataDir.entryInfoList(QStringList() << "*.wav");
    foreach (QFileInfo wordFile, wordFiles) {
        words.push_back(wordFile.canonicalFilePath());
    }

    if (words.empty()) {
        QMessageBox::critical(nullptr, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));

    setWindowTitle(tr("Lydøvelse  1.2: r eller ikke r"));

    auto *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Lyt og svar om ordet indeholder 'r' eller ej."));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);
    qvbl->addSpacing(5);

    media = new QMediaPlayer;

    QPushButton *again = new QPushButton(tr("Lyt igen"));
    connect(again, SIGNAL(clicked()), this, SLOT(playAgain()));
    qvbl->addWidget(again);

    qvbl->addSpacing(5);

    noR = new QPushButton(tr("Har ikke r"));
    connect(noR, SIGNAL(clicked()), this, SLOT(checkNoR()));
    yesR = new QPushButton(tr("Har r"));
    connect(yesR, SIGNAL(clicked()), this, SLOT(checkYesR()));
    result = new QLabel;
    qvbl->addWidget(noR);
    qvbl->addWidget(yesR);
    qvbl->addWidget(result);
    result->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton(tr("Gå til næste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);

    setMinimumWidth(230);

    showNext();
}

void ListenTwo::playAgain() {
    media->stop();
    media->setPosition(0);
    media->play();
}

void ListenTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(words.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("Færdig!"), tr("Der er ikke mere i denne øvelse. Vil du fortsætte med næste øvelse?"));
        QPushButton *yes = mbox.addButton(tr("Ja, næste øvelse"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showListenThree();
        }
        close();
        return;
    }

    media->setMedia(QUrl::fromLocalFile(words.at(curAt)));
    result->hide();

    adjustSize();
    playAgain();
}

void ListenTwo::checkNoR() {
    QFileInfo fi(words.at(curAt));
    QString word = fi.baseName();

    if (!word.contains("r")) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}

void ListenTwo::checkYesR() {
    QFileInfo fi(words.at(curAt));
    QString word = fi.baseName();

    if (word.contains("r")) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}
