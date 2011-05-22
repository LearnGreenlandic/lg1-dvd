#include "ListenFour.hpp"
#include <algorithm>

ListenFour::ListenFour(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
curAt(-1)
{
    if (!dataDir.cd("./listening/4/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/listening/4/");
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

    setWindowTitle(tr("Lydøvelse  1.4: Skriv hvad du hørte"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Skriv hvad du hører."));
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

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    check = new QPushButton(tr("Check"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton(tr("Giv op..."));
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(yield);
    result->hide();
    yield->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton(tr("Gå til næste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);

    showNext();
}

void ListenFour::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void ListenFour::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(words.size())) {
        QMessageBox::information(0, tr("Færdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
        close();
        return;
    }
    media->setCurrentSource(words.at(curAt));
    result->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    adjustSize();
    playAgain();
}

void ListenFour::checkInput() {
    QFileInfo fi(words.at(curAt));
    QString tmp = fi.baseName();

    if (input->text().compare(tmp, Qt::CaseInsensitive) == 0) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + "</b></span></center>");
        yield->hide();
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    input->selectAll();
    adjustSize();
}

void ListenFour::yieldWord() {
    QFileInfo fi(words.at(curAt));
    QString tmp = fi.baseName();

    QMessageBox::information(0, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte ord var:") + QString("</h1><br>") + tmp);
    showNext();
}
