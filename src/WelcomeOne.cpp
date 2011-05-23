#include "WelcomeOne.hpp"

WelcomeOne::WelcomeOne(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc)
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

    setWindowTitle(tr("Sk�rmteksts�velse 1.1: Stavelsesdeling"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Her er igen den tekst, der stod p� sk�rmen lige efter velkomsten. Stavelsesdel den efter de tre regler, du netop har l�rt. Du finder facitlisten og en overs�ttelse i indstiksh�ftet, men brug den f�rst, n�r du har pr�vet s� godt du kan selv."));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    qvbl->addSpacing(5);

    input = new QTextEdit(text);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    input->setFont(font);
    connect(input, SIGNAL(textChanged()), this, SLOT(preventLoss()));
    QPushButton *check = new QPushButton(tr("Check"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    yield = new QPushButton(tr("Giv op..."));
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
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + "</b></span></center>");
        yield->hide();

        QMessageBox mbox(QMessageBox::Question, tr("Korrekt!"), tr("Korrekt! Det var alt for denne �velse. Vil du g� videre til n�ste �velse?"));
        QPushButton *yes = mbox.addButton(tr("Ja, n�ste �velse"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showWelcomeTwo();
        }
        close();
        return;
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPr�v igen...") + "</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    adjustSize();
}

void WelcomeOne::yieldHyphen() {
    QMessageBox::information(this, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte er:") + QString("</h1><br>") + hyphenated);
}
