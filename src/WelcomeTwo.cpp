#include "WelcomeTwo.hpp"

#include <QtOpenGL/QGLWidget>

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

    setWindowTitle("Velkomst�velse: Udtale");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel(
        "L�s teksten op ord for ord og v�n dig til de skiftende toneh�jder."
        " Tryk <N�ste ord> efter hvert ord, n�r du f�ler, at din udtale er ved at v�re korrekt."
        " S� f�r du ordet i fonetisk skrift i vores lille nodesystem, s� du har noget at kontrollere din udtale p�."
        " Du finder en overs�ttelse i indstiksh�ftet."
        );
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    qvbl->addSpacing(5);

    label = new QLabel(text);
    label->setWordWrap(true);
    label->setMinimumWidth(700);

    QPushButton *next = new QPushButton("N�ste ord");
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

    setLayout(qvbl);

    nextWord();
}

void WelcomeTwo::nextWord() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(pngs.size())) {
        QMessageBox::information(0, "F�rdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
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
