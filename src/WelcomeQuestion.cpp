#include "WelcomeQuestion.hpp"

WelcomeQuestion::WelcomeQuestion(TaskChooser& tc) :
QWidget(nullptr, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint),
tc(tc)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Velkommen til Grønlandsk for voksne!"));

    auto *qvbl = new QVBoxLayout;

    QLabel *label = new QLabel("Tikap tikilluaqqusissutaa paasillugu nalunaarutigigakku kalaaliunnguatsiarputit, qallunaat kalaallisut oqallorivissut amerlanngeqisut ilaginngikkukkit. Ilinniutinnguaq manna kalaallisut ilinnialerlaanut sanaajuvoq. Kalaallisut ilittut oqalussinnaareersut pissarsiffigivallaarnavianngilaat. Program qimaannarsinnaavat ataani karseeqqami oqaaseq 'baaj' allakkukku. Pikkorissarneq manna marsilaarniarlugu malinnaaffigerusukkukku karseeqqami allaannassaatit 'ingerlaqqillanga'. Qujanaq soqutiginnillutit ilinniusiarput alakkarakku.");
    label->setWordWrap(true);
    qvbl->addWidget(label);

    auto *text = new QLineEdit;
    connect(text, SIGNAL(textChanged(const QString&)), this, SLOT(checkInput(const QString&)));
    qvbl->addWidget(text);

    QPushButton *ohno = new QPushButton(tr("Ups! Hjælp mig ud!"));
    connect(ohno, SIGNAL(clicked()), this, SLOT(whoops()));
    qvbl->addWidget(ohno);

    setLayout(qvbl);
}

void WelcomeQuestion::checkInput(const QString& nt) {
    if (nt.compare("baaj", Qt::CaseInsensitive) == 0) {
        QCoreApplication::quit();
    }
    else if (nt.compare("ingerlaqqillanga", Qt::CaseInsensitive) == 0) {
        whoops();
    }
}

void WelcomeQuestion::whoops() {
    tc.showLectureOne();
    close();
}
