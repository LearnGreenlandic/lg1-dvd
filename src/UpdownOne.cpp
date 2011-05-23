#include "UpdownOne.hpp"

UpdownOne::UpdownOne(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
data(dataDir),
curAt(0)
{
    setWindowTitle(tr("Ordbygning: Reception"));

    QLabel *ql = new QLabel(tr("Prøv at forstå og at udtale følgende ord:"));

    QVBoxLayout *qvbl = new QVBoxLayout;
    qvbl->addWidget(ql);

    QVBoxLayout *curWord = new QVBoxLayout;
    down = new QLabel(QString("<center><h2>") + data.updowns.at(curAt).first + "</h2></center>");
    up = new QLabel(QString("<center><i>") + data.updowns.at(curAt).second + "</i></center>");
    help = new QPushButton(tr("Vis hjælp"));
    connect(help, SIGNAL(clicked()), this, SLOT(showHelp()));
    curWord->addWidget(down);
    curWord->addSpacing(5);
    curWord->addWidget(help);
    curWord->addWidget(up);
    up->hide();

    QPushButton *nb = new QPushButton(tr("Gå til næste ord"));
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));

    qvbl->addLayout(curWord);
    qvbl->addSpacing(15);
    qvbl->addWidget(nb);

    setLayout(qvbl);
}

void UpdownOne::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.updowns.size())) {
        QMessageBox::information(0, tr("Færdig!"), tr("Der er ikke flere ord...vinduet lukker sig selv nu."));
        close();
        return;
    }
    up->hide();
    help->show();
    down->setText(QString("<center><h2>") + data.updowns.at(curAt).first + "</h2></center>");
    adjustSize();
}

void UpdownOne::showHelp() {
    help->hide();
    up->setText(QString("<center><i>") + data.updowns.at(curAt).second + "</i></center>");
    up->setToolTip(data.glossUpperDetailed(data.updowns.at(curAt).second));
    up->show();
    adjustSize();
}
