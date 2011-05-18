#include "StructureThree.hpp"

StructureThree::StructureThree(QDir dataDir, QString which, QString title) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir, which),
curAt(0)
{
    setWindowTitle(title);

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(
        "Denne �velse er identisk med �velse 1-2, men denne gang f�r du ingen hj�lp af teksten. Du m� klare dig med dine �rer.<br/>"
        "S�t tilh�nget N+MIU p� bynavnene, s� du danner ord med betydningen 'indbygger i BYNAVN'."
        " Udtal det nye ord h�jt og lyt derefter til Tikas indtaling af det samme ord."
        " Klik 'n�ste' n�r du er tilfreds med din egen udtale.<br/>"
        "Hvis du slet ikke kan f� ordet dannet inde i hovedet, m� du som en sidste udvej vende tilbage til �velse 1-2 for at forst�, hvad det er der foreg�r netop her.<br/>"
        );
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    media->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(0)) + ".wav");
    QPushButton *again = new QPushButton("Lyt igen");
    connect(again, SIGNAL(clicked()), this, SLOT(playAgain()));

    cmedia = new Phonon::MediaObject;
    caudio = new Phonon::AudioOutput;
    Phonon::createPath(cmedia, caudio);
    cmedia->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(1)) + ".wav");

    qvbl->addSpacing(5);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    check = new QPushButton("Check");
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton("Giv op...");
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    cagain = new QPushButton("H�r den korrekte udtale");
    connect(cagain, SIGNAL(clicked()), this, SLOT(playCorrectAgain()));
    qvbl->addWidget(new QLabel("Skriv 'indbygger i bynavn' formen:"));
    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(cagain);
    qvbl->addWidget(yield);
    result->hide();
    cagain->hide();
    yield->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton("G� til n�ste ord");
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);
}

void StructureThree::show() {
    QWidget::show();
    media->play();
}

void StructureThree::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void StructureThree::playCorrectAgain() {
    cmedia->stop();
    cmedia->seek(0);
    cmedia->play();
}

void StructureThree::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.pairs.size())) {
        QMessageBox::information(0, "F�rdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }

    media->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(0)) + ".wav");
    cmedia->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(1)) + ".wav");

    result->hide();
    cagain->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    adjustSize();
    playAgain();
}

void StructureThree::checkInput() {
    if (input->text() == data.pairs.at(curAt).at(1)) {
        result->setText("<center><span style='color: darkgreen;'><b>Korrekt!</b></span><br>Pr�v nu selv at udtale ordet inden du h�rer den korrekte udtale.</center>");
        cagain->show();
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

void StructureThree::yieldWord() {
    QMessageBox::information(0, "Hrhm...", QString("Det korrekte ord var:\n") + data.pairs.at(curAt).at(1));
    showNext();
}
