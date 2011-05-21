#include "HyphenOne.hpp"

#include <algorithm>
#include <QtOpenGL/QGLWidget>

HyphenOne::HyphenOne(QDir dataDir) :
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

    setWindowTitle("Orddelingsøvelse");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel("Del ordet med -; brug noderne til hjælp.");
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    qvbl->addSpacing(5);

    label = new QLabel(text);
    label->setWordWrap(true);
    label->setMinimumWidth(700);

    QPushButton *next = new QPushButton("Næste ord");
    connect(next, SIGNAL(clicked()), this, SLOT(nextWord()));

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
    notes = scene->addPixmap(qpx);
    notes->setTransformationMode(Qt::SmoothTransformation);

    view = new ScalingGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QGLWidget *opengl = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    if (QGLFormat::hasOpenGL() && opengl->isValid()) {
        view->setViewport(opengl);
    }
    else {
        delete opengl;
    }
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setContentsMargins(0, 0, 0, 0);

    qvbl->addWidget(label);
    qvbl->addWidget(view, 0, Qt::AlignHCenter);

    qvbl->addSpacing(5);
    qvbl->addWidget(next);

    input = new QLineEdit(text);
    connect(input, SIGNAL(textChanged(const QString&)), this, SLOT(preventLoss(const QString&)));
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

    nextWord();
}

void HyphenOne::nextWord() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(pngs.size())) {
        QMessageBox::information(0, "Færdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
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

void HyphenOne::yieldHyphen() {
    QMessageBox::information(this, "Hrhm...", QString("<h1>Det korrekte er:</h1>\n\n") + hyphenated);
    nextWord();
}
