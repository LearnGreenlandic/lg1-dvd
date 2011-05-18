#include "StructureTwo.hpp"

StructureTwo::StructureTwo(QDir dataDir, QString which, QString title) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir, which),
curAt(-1)
{
    setWindowTitle(title);

    QVBoxLayout *qvbl = new QVBoxLayout;

#if 0
    tr("structure 2 ./1/");
    tr("structure 2 ./2/");
    tr("structure 2 ./3/");
#endif

    QLabel *ql = new QLabel(tr(QString(QString("structure 2 ") + which).toStdString().c_str()));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);
    qvbl->addSpacing(5);

    query = new QLabel;

    qvbl->addWidget(query);
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

    QPushButton *nb = new QPushButton(tr("G� til n�ste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);

    showNext();
}

void StructureTwo::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.pairs.size())) {
        QMessageBox::information(0, tr("F�rdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
        close();
        return;
    }

    QString x;
    if (data.pairs.at(curAt).size() == 3) {
        x = QString(" (") + data.pairs.at(curAt).at(2) + ")";
    }

#if 0
    tr("structure 2.form ./1/");
    tr("structure 2.form ./2/");
    tr("structure 2.form ./3/");
#endif

    query->setText(QString("<font size='+3'>") + tr("Bynavn:") + " <b>" + data.pairs.at(curAt).at(0) + "</b>" + x + "</font><br>"
        + tr(QString(QString("structure 2.form ") + data.which).toStdString().c_str()).arg(data.pairs.at(curAt).at(0)) + "<br>");

    result->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    adjustSize();
}

void StructureTwo::checkInput() {
    if (input->text() == data.pairs.at(curAt).at(1)) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + "</b></span></center>");
        yield->hide();
    }
    else if (input->text().compare(data.pairs.at(curAt).at(1), Qt::CaseInsensitive) == 0) {
        result->setText(QString("<center><span style='color: darkyellow;'><b>") + tr("N�sten korrekt.\nStore og sm� bogstaver g�lder...") + "</b></span></center>");
        yield->show();
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPr�v igen...") + "</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    input->selectAll();
    adjustSize();
}

void StructureTwo::yieldWord() {
    QMessageBox::information(0, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte ord var:") + QString("</h1><br>") + data.pairs.at(curAt).at(1));
    showNext();
}
