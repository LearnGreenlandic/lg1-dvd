#include "HyphenOne.hpp"

#include <algorithm>

HyphenOne::HyphenOne(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
curAt(-1)
{
    if (!dataDir.cd("./hyphenate/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/hyphenate/");
        throw(-1);
    }

    QFileInfoList wordFiles = dataDir.entryInfoList(QStringList() << "*.png");
    foreach (QFileInfo wordFile, wordFiles) {
        pngs.push_back(wordFile.canonicalFilePath());
    }

    if (pngs.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::random_shuffle(pngs.begin(), pngs.end());

    QPixmap qpx;
    qpx.load(pngs.front());

    setWindowTitle(tr("Stavelsesdeling af bynavne"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Del ordet med -; brug noderne til hjælp."));
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    qvbl->addSpacing(5);

    label = new QLabel(text);
    label->setWordWrap(true);
    label->setMinimumWidth(700);

    QPushButton *next = new QPushButton(tr("Næste ord"));
    connect(next, SIGNAL(clicked()), this, SLOT(nextWord()));

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
    notes = scene->addPixmap(qpx);
    notes->setTransformationMode(Qt::SmoothTransformation);

    view = new ScalingGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setContentsMargins(0, 0, 0, 0);

    qvbl->addWidget(label);
    qvbl->addWidget(view, 0, Qt::AlignHCenter);

    qvbl->addSpacing(5);
    qvbl->addWidget(next);

    input = new QLineEdit(text);
    connect(input, SIGNAL(textChanged(const QString&)), this, SLOT(preventLoss(const QString&)));
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

    nextWord();
}

void HyphenOne::nextWord() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(pngs.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("Færdig!"), tr("Der er ikke mere i denne øvelse. Vil du fortsætte med næste øvelse?"));
        QPushButton *yes = mbox.addButton(tr("Ja, næste øvelse"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showListenFour();
        }
        close();
        return;
    }

    QFileInfo fi(pngs.at(curAt));
    text = hyphenated = fi.baseName();
    state = text.replace("-", "");

    input->setText(text);

    QPixmap qpx;
    qpx.load(pngs.at(curAt));
    notes->setPixmap(qpx);
    notes->update();
    scene->setSceneRect(scene->itemsBoundingRect());
    view->setMinimumWidth(qpx.width()/2.0);
    view->setMinimumHeight(qpx.height()/2.0);
    view->setMaximumWidth(qpx.width()/2.0);
    view->setMaximumHeight(qpx.height()/2.0);

    result->hide();
    yield->hide();

    adjustSize();
}

void HyphenOne::preventLoss(const QString& current) {
    int tp = input->cursorPosition();
    QString plain = current;
    plain.replace("-", "");
    if (plain != text) {
        input->setText(state);
        input->setCursorPosition(tp);
    }
    state = input->text();
}

void HyphenOne::checkInput() {
    QString plain = input->text();
    if (plain == hyphenated) {
        result->setText(QString("<center><span style='color: darkgreen;'><b>") + tr("Korrekt!") + "</b></span></center>");
        yield->hide();
    }
    else {
        result->setText(QString("<center><span style='color: darkred;'><b>") + tr("Ikke korrekt.\nPrøv igen...") + "</b></span></center>");
        yield->show();
    }
    result->show();
    input->setFocus();
    adjustSize();
}

void HyphenOne::yieldHyphen() {
    QMessageBox::information(this, tr("Hrhm..."), QString("<h1>") + tr("Det korrekte er:") + QString("</h1><br>") + hyphenated);
    nextWord();
}
