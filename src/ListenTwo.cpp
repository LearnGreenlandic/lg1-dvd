#include "ListenTwo.hpp"
#include <algorithm>

ListenTwo::ListenTwo(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
curAt(-1)
{
    if (!dataDir.cd("./listening/2/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/listening/2/");
        throw(-1);
    }

    QFileInfoList wordFiles = dataDir.entryInfoList(QStringList() << "*.wav");
    foreach (QFileInfo wordFile, wordFiles) {
        words.push_back(wordFile.canonicalFilePath());
    }

    if (words.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::random_shuffle(words.begin(), words.end());

    setWindowTitle(tr("Lytteøvelse 1.2: r eller ikke r"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Lyt og svar om ordet indeholder 'r' eller ej."));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);
    qvbl->addSpacing(5);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

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
    media->seek(0);
    media->play();
}

void ListenTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(words.size())) {
        QMessageBox::information(0, tr("Færdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
        close();
        return;
    }

    media->setCurrentSource(words.at(curAt));
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
