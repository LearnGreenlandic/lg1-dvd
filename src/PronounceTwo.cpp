#include "PronounceTwo.hpp"

PronounceTwo::PronounceTwo(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir),
curAt(0)
{
    setWindowTitle("Udtaleøvelse: Afskriv");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel("Skriv hvad du hører.\n");
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    media->setCurrentSource(data.sounds[data.words.at(curAt)]);
    QPushButton *again = new QPushButton("Lyt igen");
    connect(again, SIGNAL(clicked()), this, SLOT(playAgain()));
    qvbl->addWidget(again);

    qvbl->addSpacing(5);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    check = new QPushButton("Check");
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton("Giv op...");
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    qvbl->addWidget(new QLabel("Skriv hvad du hørte:"));
    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(yield);
    result->hide();
    yield->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton("Gå til næste ord");
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);
}

void PronounceTwo::show() {
    QWidget::show();
    media->play();
}

void PronounceTwo::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void PronounceTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.words.size())) {
        QMessageBox::information(0, "Færdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }
    media->setCurrentSource(data.sounds[data.words.at(curAt)]);
    result->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    adjustSize();
    playAgain();
}

void PronounceTwo::checkInput() {
    if (input->text() == data.words.at(curAt)) {
        result->setText("<center><span style='color: darkgreen;'><b>Korrekt!</b></span></center>");
        yield->hide();
    }
    else if (input->text().compare(data.words.at(curAt), Qt::CaseInsensitive) == 0) {
        result->setText("<center><span style='color: darkyellow;'><b>Næsten korrekt.\nStore og små bogstaver gælder...</b></span></center>");
        yield->show();
    }
    else {
        result->setText("<center><span style='color: darkred;'><b>Ikke korrekt.\nPrøv igen...</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    input->selectAll();
    adjustSize();
}

void PronounceTwo::yieldWord() {
    QMessageBox::information(0, "Hrhm...", QString("Det korrekte ord var:\n") + data.words.at(curAt));
    showNext();
}
