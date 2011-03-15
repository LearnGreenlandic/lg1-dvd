#include "StructureOne.hpp"

StructureOne::StructureOne(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir),
curAt(0)
{
    setWindowTitle("Struktur: Lydopfattelse");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(
        "Nu hører du først Tika udtale navnene på de 18 gamle grønlandske kommuner. Lyt og prøv at skrive det navn, du hører."
        " Lad være med at forsøge at springe over hvor gærdet er lavest ved at skrive af efter en liste eller et atlas; det lærer du ikke noget af!"
        " Husk at navne skrives med stort begyndelsesbogstav.\n");
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    media->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(0)) + ".wav");
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

void StructureOne::show() {
    QWidget::show();
    media->play();
}

void StructureOne::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void StructureOne::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.pairs.size())) {
        QMessageBox::information(0, "Færdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }
    media->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(0)) + ".wav");
    result->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    adjustSize();
    playAgain();
}

void StructureOne::checkInput() {
    if (input->text() == data.pairs.at(curAt).at(0)) {
        result->setText("<center><span style='color: darkgreen;'><b>Korrekt!</b></span></center>");
        yield->hide();
    }
    else if (input->text().compare(data.pairs.at(curAt).at(0), Qt::CaseInsensitive) == 0) {
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

void StructureOne::yieldWord() {
    QMessageBox::information(0, "Hrhm...", QString("Det korrekte ord var:\n") + data.pairs.at(curAt).at(0));
    showNext();
}
