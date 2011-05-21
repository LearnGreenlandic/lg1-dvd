#include "ListenOne.hpp"
#include <algorithm>

ListenOne::ListenOne(QDir dataDir) :
curAt(-1)
{
    if (!dataDir.cd("./listening/1/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/listening/1/");
        throw(-1);
    }

    if (!dataDir.exists("words.txt")) {
        QMessageBox::critical(0, "Missing Data!", "Could not find words.txt!");
        throw(-1);
    }

    QFile list(dataDir.absoluteFilePath("words.txt"));
    if (!list.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, "Bad Data!", "Could not open words.txt for reading!");
        throw(-1);
    }

    QTextStream text(&list);
    while (!text.atEnd()) {
        QString line = text.readLine();
        if (line.length()) {
            QStringList sp = line.split("\t");
            QStringList wds = sp.at(1).split(" ");
            foreach (line, wds) {
                if (!dataDir.exists(line + ".wav")) {
                    QMessageBox::critical(0, "Bad Data!", QString("Missing audio file ") + line + ".wav!");
                    throw(-1);
                }
                words.push_back(qMakePair(dataDir.absoluteFilePath(line + ".wav"), sp.at(0)));
            }
        }
    }

    if (words.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::random_shuffle(words.begin(), words.end());

    setWindowTitle(tr("Lytte�velse 1.1: En eller to konsonanter"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Lyt og svar om der er to konsonanter."));
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

    oneC = new QPushButton(tr("Ikke to konsonanter"));
    connect(oneC, SIGNAL(clicked()), this, SLOT(oneConsonant()));
    twoC = new QPushButton(tr("To konsonanter"));
    connect(twoC, SIGNAL(clicked()), this, SLOT(twoConsonants()));
    result = new QLabel;
    qvbl->addWidget(oneC);
    qvbl->addWidget(twoC);
    qvbl->addWidget(result);
    result->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton(tr("G� til n�ste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);

    setMinimumWidth(230);

    showNext();
}

void ListenOne::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void ListenOne::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(words.size())) {
        QMessageBox::information(0, tr("F�rdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
        close();
        return;
    }

    media->setCurrentSource(words.at(curAt).first);
    result->hide();

    QString tmp = QString("Nej, har ikke ") + words.at(curAt).second + words.at(curAt).second;
    oneC->setText(tr(tmp.toStdString().c_str()));

    tmp = QString("Jo, har ") + words.at(curAt).second + words.at(curAt).second;
    twoC->setText(tr(tmp.toStdString().c_str()));

    adjustSize();
    playAgain();
}

void ListenOne::oneConsonant() {
    QFileInfo fi(words.at(curAt).first);
    QString word = fi.baseName();

    if (!word.contains(words.at(curAt).second + words.at(curAt).second)) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPr�v igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}

void ListenOne::twoConsonants() {
    QFileInfo fi(words.at(curAt).first);
    QString word = fi.baseName();

    if (word.contains(words.at(curAt).second + words.at(curAt).second)) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!\nOrdet var: ") + word + "</b></span></center>");
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPr�v igen...") + "</b></span></center>");
    }
    result->show();

    adjustSize();
}
