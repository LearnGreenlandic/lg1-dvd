#include "WelcomeOne.hpp"

WelcomeOne::WelcomeOne(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
    if (!dataDir.cd("./welcome/") || !dataDir.exists("input.txt")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/welcome/");
        throw(-1);
    }

    QFile input_f(dataDir.absoluteFilePath("input.txt"));
    if (!input_f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, "Read Error!", "Could not open input.txt from data folder!");
        throw(-1);
    }
    QTextStream input_t(&input_f);
    input_t.setCodec("UTF-8");
    state = text = input_t.readAll();

    QFile hyphen_f(dataDir.absoluteFilePath("hyphenated.txt"));
    if (!hyphen_f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, "Read Error!", "Could not open hyphenated.txt from data folder!");
        throw(-1);
    }
    QTextStream hyphen_t(&hyphen_f);
    hyphen_t.setCodec("UTF-8");
    hyphenated = hyphen_t.readAll();

    setWindowTitle("Velkomstøvelse: Stavelsesdeling");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(
        "Her er igen den tekst, der stod på skærmen lige efter velkomsten."
        " Stavelsesdel den efter de tre regler, du netop har lært."
        " Du finder facitlisten og en oversættelse i indstikshæftet, men brug den først, når du har prøvet så godt du kan selv.\n"
        );
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    qvbl->addSpacing(5);

    input = new QTextEdit(text);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    input->setFont(font);
    connect(input, SIGNAL(textChanged()), this, SLOT(preventLoss()));
    QPushButton *check = new QPushButton("Check");
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton("Giv op...");
    connect(yield, SIGNAL(clicked()), this, SLOT(yieldHyphen()));
    result = new QLabel;

    qvbl->addWidget(input);
    qvbl->addWidget(check);
    qvbl->addWidget(result);
    qvbl->addWidget(yield);

    result->hide();
    yield->hide();

    setLayout(qvbl);
}

void WelcomeOne::preventLoss() {
    int tp = input->textCursor().position();
    QString plain = input->toPlainText();
    plain.replace("-", "");
    if (plain != text) {
        input->setPlainText(state);
        QTextCursor tc = input->textCursor();
        tc.setPosition(tp);
        input->setTextCursor(tc);
    }
    state = input->toPlainText();
}

void WelcomeOne::checkInput() {
    QString plain = input->toPlainText();
    if (plain == hyphenated) {
        result->setText("<center><span style='color: darkgreen;'><b>Korrekt!</b></span></center>");
        yield->hide();
    }
    else if (plain.compare(hyphenated, Qt::CaseInsensitive) == 0) {
        result->setText("<center><span style='color: darkyellow;'><b>Næsten korrekt.\nStore og små bogstaver gælder...</b></span></center>");
        yield->show();
    }
    else {
        result->setText("<center><span style='color: darkred;'><b>Ikke korrekt.\nPrøv igen...</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    adjustSize();
}

void WelcomeOne::yieldHyphen() {
    QMessageBox::information(this, "Facit", QString("<h1>Det korrekte er:</h1>\n\n") + hyphenated);
}
