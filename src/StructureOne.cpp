#include "StructureOne.hpp"

StructureOne::StructureOne(QDir dataDir, QString which, QString title, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
data(dataDir, which),
curAt(0)
{
    setWindowTitle(title);

    QVBoxLayout *qvbl = new QVBoxLayout;

#if 0
    tr("structure 1 ./1/");
    tr("structure 1 ./2/");
    tr("structure 1 ./3/");
#endif

    QLabel *ql = new QLabel(tr(QString(QString("structure 1 ") + which).toStdString().c_str()));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);
    qvbl->addSpacing(5);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    media->setCurrentSource(data.dataDir.absoluteFilePath(data.pairs.at(curAt).at(0)) + ".wav");
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
    qvbl->addWidget(new QLabel(tr("Skriv hvad du hørte:")));
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
        QMessageBox::information(0, tr("Færdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
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
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + "</b></span></center>");
        yield->hide();
    }
    else if (input->text().compare(data.pairs.at(curAt).at(0), Qt::CaseInsensitive) == 0) {
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

void StructureOne::yieldWord() {
    QMessageBox::information(0, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte ord var:") + QString("</h1><br>") + data.pairs.at(curAt).at(0));
    showNext();
}
