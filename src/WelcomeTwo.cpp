#include "WelcomeTwo.hpp"

WelcomeTwo::WelcomeTwo(QDir dataDir, TaskChooser& tc) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
tc(tc),
curAt(-1)
{
    if (!dataDir.cd("./welcome/")) {
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
    text = input_t.readAll();

    QFileInfoList wordFiles = dataDir.entryInfoList(QStringList() << "*.png");
    foreach (QFileInfo wordFile, wordFiles) {
        pngs.push_back(wordFile.canonicalFilePath());
    }

    if (pngs.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    QPixmap qpx;
    qpx.load(pngs.front());

    setWindowTitle(tr("Skærmtekstsøvelse 1.2: Udtale"));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Læs teksten op ord for ord og væn dig til de skiftende tonehøjder. Tryk <Næste ord> efter hvert ord, når du føler, at din udtale er ved at være korrekt. Så får du ordet i fonetisk skrift i vores lille nodesystem, så du har noget at kontrollere din udtale på. Du finder en oversættelse i indstikshæftet."));
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

    setLayout(qvbl);

    nextWord();
}

void WelcomeTwo::nextWord() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(pngs.size())) {
        QMessageBox mbox(QMessageBox::Question, tr("Færdig!"), tr("Der er ikke mere i denne øvelse. Vil du læse forelæsningen som PDF?"));
        QPushButton *yes = mbox.addButton(tr("Ja, åben PDF"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, tilbage til menuen"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            tc.showLectureThreePDF();
        }
        close();
        return;
    }

    QPixmap qpx;
    qpx.load(pngs.at(curAt));
    notes->setPixmap(qpx);
    notes->update();
    scene->setSceneRect(scene->itemsBoundingRect());
    view->setMinimumWidth(qpx.width()/2.0);
    view->setMinimumHeight(qpx.height()/2.0);
    view->setMaximumWidth(qpx.width()/2.0);
    view->setMaximumHeight(qpx.height()/2.0);

    QStringList words = text.split(' ');
    words[curAt] = QString("<font color='blue'><b>") + words.at(curAt) + "</b></font>";
    label->setText(QString("<font size='+2'>") + words.join(" ") + "</font>");

    adjustSize();
}
