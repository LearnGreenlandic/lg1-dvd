#include "UpdownThree.hpp"

UpdownThree::UpdownThree(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir),
curAt(0)
{
    setWindowTitle("Up/Down: Oversættelse");

    QLabel *ql = new QLabel("Oversæt følgende glossering til et ord i færdig form:\n");

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->addWidget(ql);

    curWord = new QVBoxLayout;
    up = new QLabel(QString("<center><h2>") + data.glossUpperShort(data.updowns.at(curAt).second) + "</h2></center>");
    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    check = new QPushButton("Check");
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton("Giv op...");
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldWord()));
    result = new QLabel;
    curWord->addWidget(up);
    curWord->addSpacing(5);
    curWord->addWidget(input);
    curWord->addWidget(check);
    curWord->addWidget(result);
    curWord->addWidget(yield);
    result->hide();
    yield->hide();

    QPushButton *nb = new QPushButton("Gå til næste ord");
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));

    qvbl->addLayout(curWord);
    qvbl->addSpacing(15);
    qvbl->addWidget(nb);

    setLayout(qvbl);
}

void UpdownThree::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.updowns.size())) {
        QMessageBox::information(0, "Færdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }
    result->hide();
    yield->hide();
    input->setText("");
    input->setFocus();
    up->setText(QString("<center><h2>") + data.glossUpperShort(data.updowns.at(curAt).second) + "</h2></center>");
    adjustSize();
}

void UpdownThree::checkInput() {
    if (input->text() == data.updowns.at(curAt).first) {
        result->setText("<center><span style='color: darkgreen;'><b>Korrekt!</b></span></center>");
        yield->hide();
    }
    else if (input->text().compare(data.updowns.at(curAt).first, Qt::CaseInsensitive) == 0) {
        result->setText("<center><span style='color: darkyellow;'><b>Næsten korrekt.\nStore og små bogstaver gælder...</b></span></center>");
        yield->show();
    }
    else {
        result->setText("<center><span style='color: darkred;'><b>Ikke korrekt.\nPrøv igen...</b></span></center>");
        yield->show();
    }
    result->show();
    yield->show();
    input->setFocus();
    input->selectAll();
    adjustSize();
}

void UpdownThree::yieldWord() {
    QMessageBox::information(0, "Hrhm...", QString("Det korrekte færdige ord var:\n") + data.updowns.at(curAt).first);
    showNext();
}
