#include "StructureTwo.hpp"

StructureTwo::StructureTwo(QDir dataDir, QString which, QString title) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir, which),
curAt(-1)
{
    setWindowTitle(title);

    QVBoxLayout *qvbl = new QVBoxLayout;

    QString t =
        "S�t tilh�nget N+MIU p� bynavnene, s� du danner ord med betydningen 'indbygger i BYNAVN'.\n"
        "Lad v�re med at lade dig snyde af den retskrivningsdetalje, at et q sidst i ordet STAVES som -r-, n�r der kommer en anden konsonant bagefter."
        " Som du allerede ved det fra forel�sning 2, udtales -r- i denne stilling alligevel ikke som -r-, men som en fordobling af den konsonant, der kommer efter."
        " Tilh�ng s�t�tes altid til entalsfor�men, s� for de 7 byer, hvis navne er f�dt med en fler�tals�en�delse, skal du bruge den en�talsform, du f�r serveret.\n"
        ;

    if (which == "./2/") {
        t = "Brug N+MIU-U{+vu\u014Ba} for at v�nne dig til lyd�ndrin�ger�ne og for at tr�ne brugen af me�get lange ord.\n";
    }
    else if (which == "./3/") {
        t = "Brug N{-mi} for at v�nne dig til lyd�ndrin�ger�ne.\n";
    }

    QLabel *ql = new QLabel(t);
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    query = new QLabel;

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

    QPushButton *nb = new QPushButton("G� til n�ste ord");
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);

    showNext();
}

void StructureTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.pairs.size())) {
        QMessageBox::information(0, "F�rdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }

    QString x;
    if (data.pairs.at(curAt).size() == 3) {
        x = QString(" (") + data.pairs.at(curAt).at(2) + ")";
    }
    query->setText(QString("<font size='+3'>Bynavn: <b>") + data.pairs.at(curAt).at(0) + "</b>" + x + "</font><br>"
        "Skriv 'indbygger i " + data.pairs.at(curAt).at(0) + "' formen:<br>");

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
        result->setText("<center><span style='color: darkyellow;'><b>N�sten korrekt.\nStore og sm� bogstaver g�lder...</b></span></center>");
        yield->show();
    }
    else {
        result->setText("<center><span style='color: darkred;'><b>Ikke korrekt.\nPr�v igen...</b></span></center>");
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
