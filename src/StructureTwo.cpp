#include "StructureTwo.hpp"

StructureTwo::StructureTwo(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir),
curAt(0)
{
    setWindowTitle("Struktur: Dan nye ord");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(
        "Sæt tilhænget N+MIU på bynavnene, så du danner ord med betydningen 'indbygger i BYNAVN'.\n"
        "Lad være med at lade dig snyde af den retskrivningsdetalje, at et q sidst i ordet STAVES som -r-, når der kommer en anden konsonant bagefter."
        " Som du allerede ved det fra forelæsning X (ToDo), udtales -r- i denne stilling alligevel ikke som -r-, men som en fordobling af den konsonant, der kommer efter."
        " Tilhæng sæt­tes altid til entalsfor­men, så for de 7 byer, hvis navne er født med en fler­tals­en­delse, skal du bruge den en­talsform, du får serveret.\n"
        );
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    QString x, t = data.pairs.at(curAt).at(0);
    if (data.pairs.at(curAt).size() == 3) {
        t = data.pairs.at(curAt).at(2);
        x = QString(" (") + data.pairs.at(curAt).at(2) + ")";
    }
    query = new QLabel(QString("<font size='+3'>Bynavn: <b>") + data.pairs.at(curAt).at(0) + "</b>" + x + "</font><br>"
        "Skriv 'indbygger i " + t + "' formen:<br>");

    qvbl->addWidget(query);
    qvbl->addSpacing(5);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    check = new QPushButton("Check");
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton("Giv op...");
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
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

void StructureTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.pairs.size())) {
        QMessageBox::information(0, "Færdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }

    QString x, t = data.pairs.at(curAt).at(0);
    if (data.pairs.at(curAt).size() == 3) {
        t = data.pairs.at(curAt).at(2);
        x = QString(" (") + data.pairs.at(curAt).at(2) + ")";
    }
    query->setText(QString("<font size='+3'>Bynavn: <b>") + data.pairs.at(curAt).at(0) + "</b>" + x + "</font><br>"
        "Skriv 'indbygger i " + t + "' formen:<br>");

    result->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    adjustSize();
}

void StructureTwo::checkInput() {
    if (input->text() == data.pairs.at(curAt).at(1)) {
        result->setText("<center><span style='color: darkgreen;'><b>Korrekt!</b></span></center>");
        yield->hide();
    }
    else if (input->text().compare(data.pairs.at(curAt).at(1), Qt::CaseInsensitive) == 0) {
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

void StructureTwo::yieldWord() {
    QMessageBox::information(0, "Hrhm...", QString("Det korrekte ord var:\n") + data.pairs.at(curAt).at(1));
    showNext();
}
