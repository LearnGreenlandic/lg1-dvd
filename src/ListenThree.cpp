#include "ListenThree.hpp"
#include <algorithm>

ListenThree::ListenThree(QDir dataDir) :
curAt(-1)
{
    if (!dataDir.cd("./listening/3/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/listening/3/");
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

    setWindowTitle(tr("Lytteøvelse 1.3: tt eller ts eller t"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Lyt og svar om ordet indeholder 'tt' eller 'ts' eller kun 't'."));
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

    yesTT = new QPushButton(tr("Har tt"));
    connect(yesTT, SIGNAL(clicked()), this, SLOT(checkTT()));
    yesTS = new QPushButton(tr("Har ts"));
    connect(yesTS, SIGNAL(clicked()), this, SLOT(checkTS()));
    yesT = new QPushButton(tr("Har kun t"));
    connect(yesT, SIGNAL(clicked()), this, SLOT(checkT()));
    result = new QLabel;
    qvbl->addWidget(yesTT);
    qvbl->addWidget(yesTS);
    qvbl->addWidget(yesT);
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

void ListenThree::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void ListenThree::showNext() {
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

void ListenThree::checkTT() {
    QFileInfo fi(words.at(curAt));
    QString word = fi.baseName();

    if (word.contains("tt")) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}

void ListenThree::checkTS() {
    QFileInfo fi(words.at(curAt));
    QString word = fi.baseName();

    if (word.contains("ts")) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}

void ListenThree::checkT() {
    QFileInfo fi(words.at(curAt));
    QString word = fi.baseName();

    if (!word.contains("tt") && !word.contains("ts")) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}
