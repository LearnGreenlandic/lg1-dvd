#include "StructureThree.hpp"

StructureThree::StructureThree(QDir dataDir, QString which, QString title) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir, which),
curAt(0)
{
    setWindowTitle(title);

    QVBoxLayout *qvbl = new QVBoxLayout;

#if 0
    tr("structure 3 ./1/");
    tr("structure 3 ./2/");
    tr("structure 3 ./3/");
#endif

    QLabel *ql = new QLabel(tr(QString(QString("structure 3 ") + which).toStdString().c_str()));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);
    qvbl->addSpacing(5);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    media->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(0)) + ".wav");
    QPushButton *again = new QPushButton(tr("Lyt igen"));
    connect(again, SIGNAL(clicked()), this, SLOT(playAgain()));

    cmedia = new Phonon::MediaObject;
    caudio = new Phonon::AudioOutput;
    Phonon::createPath(cmedia, caudio);
    cmedia->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(1)) + ".wav");

    qvbl->addWidget(again);
    qvbl->addSpacing(5);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    check = new QPushButton(tr("Check"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton(tr("Giv op..."));
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    cagain = new QPushButton(tr("Hør den korrekte udtale"));
    connect(cagain, SIGNAL(clicked()), this, SLOT(playCorrectAgain()));

#if 0
    tr("structure 3.form ./1/");
    tr("structure 3.form ./2/");
    tr("structure 3.form ./3/");
#endif
    //qvbl->addWidget(new QLabel("Skriv 'indbygger i bynavn' formen:"));
    qvbl->addWidget(new QLabel(tr(QString(QString("structure 3.form ") + which).toStdString().c_str())));
    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(cagain);
    qvbl->addWidget(yield);
    result->hide();
    cagain->hide();
    yield->hide();

    qvbl->addSpacing(15);

    QPushButton *nb = new QPushButton(tr("Gå til næste ord"));
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
        QMessageBox::information(0, tr("Færdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
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
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + QString("</b></span><br>") + tr("Prøv nu selv at udtale ordet inden du hører den korrekte udtale.") + "</center>");
        cagain->show();
        yield->hide();
    }
    else if (input->text().compare(data.pairs.at(curAt).at(1), Qt::CaseInsensitive) == 0) {
        result->setText(QString("<center><span style='color: darkyellow;'><b>") + tr("Næsten korrekt.\nStore og små bogstaver gælder...") + "</b></span></center>");
        yield->show();
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

void StructureThree::yieldWord() {
    QMessageBox::information(0, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte ord var:") + QString("</h1><br>") + data.pairs.at(curAt).at(1));
    showNext();
}
