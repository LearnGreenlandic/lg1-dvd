#include "LecturePlayer.hpp"
#include "HyphenOne.hpp"
#include "DialogOne.hpp"
#include "DialogTwo.hpp"
#include "DialogThree.hpp"
#include "ListenOne.hpp"
#include "ListenTwo.hpp"
#include "ListenThree.hpp"
#include "ListenFour.hpp"
#include "WelcomePlayer.hpp"
#include "WelcomeWords.hpp"
#include "WelcomeOne.hpp"
#include "WelcomeTwo.hpp"
#include "ListenRepeatPlayer.hpp"
#include "PronounceOne.hpp"
#include "PronounceTwo.hpp"
#include "UpdownOne.hpp"
#include "UpdownTwo.hpp"
#include "UpdownThree.hpp"
#include "StructureOne.hpp"
#include "StructureTwo.hpp"
#include "StructureThree.hpp"
#include "XvidTest.hpp"
#include "TaskChooser.hpp"

#include <QtGlobal>

TaskChooser::TaskChooser(QDir dataDir, QTranslator *translator) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dataDir(dataDir),
translator(translator)
{
    setWindowTitle(tr("Gr�nlandsk for voksne"));
    setContentsMargins(5,5,5,5);
    setStyleSheet("margin: 0; padding: 0;");

    QPixmap qpx;
    QLabel *ql = new QLabel;

    QGridLayout *outerGrid = new QGridLayout;
    outerGrid->setContentsMargins(0,0,0,0);


    QHBoxLayout *itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    QVBoxLayout *itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath("./images/welcome.png"));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomePlayer = new QPushButton(tr("Velkomst ved Tikaajaat Kristiansen"));
    welcomePlayer->setFlat(true);
    welcomePlayer->setStyleSheet("font-weight: bold; text-align: left;");
    connect(welcomePlayer, SIGNAL(clicked()), this, SLOT(showWelcomePlayer()));
    itemVBox->addWidget(welcomePlayer, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 1, 0, 1, 3, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./1/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureOne = new QPushButton(tr("Forel�sning 1: De \"s�re\" lyd"));
    lectureOne->setFlat(true);
    lectureOne->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureOne, SIGNAL(clicked()), this, SLOT(showLectureOne()));
    itemVBox->addWidget(lectureOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *pronounceOne = new QPushButton(QString("   - ") + tr("Udtale�velse 1.1: Gentag"));
    pronounceOne->setFlat(true);
    connect(pronounceOne, SIGNAL(clicked()), this, SLOT(showPronounceOne()));
    itemVBox->addWidget(pronounceOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *pronounceTwo = new QPushButton(QString("   - ") + tr("Udtale�velse 1.2: Diktat"));
    pronounceTwo->setFlat(true);
    connect(pronounceTwo, SIGNAL(clicked()), this, SLOT(showPronounceTwo()));
    itemVBox->addWidget(pronounceTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lecturePDF = new QPushButton(QString("   - ") + tr("Forel�sning 1 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureOnePDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 2, 0, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./2/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureTwo = new QPushButton(tr("Forel�sning 2: Typiske danskerfejl"));
    lectureTwo->setFlat(true);
    lectureTwo->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureTwo, SIGNAL(clicked()), this, SLOT(showLectureTwo()));
    itemVBox->addWidget(lectureTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenOne = new QPushButton(QString("   - ") + tr("Lyd�velse 1.1: En eller to konsonanter"));
    listenOne->setFlat(true);
    connect(listenOne, SIGNAL(clicked()), this, SLOT(showListenOne()));
    itemVBox->addWidget(listenOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenTwo = new QPushButton(QString("   - ") + tr("Lyd�velse 1.2: r eller ikke r"));
    listenTwo->setFlat(true);
    connect(listenTwo, SIGNAL(clicked()), this, SLOT(showListenTwo()));
    itemVBox->addWidget(listenTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenThree = new QPushButton(QString("   - ") + tr("Lyd�velse 1.3: tt eller ts eller t"));
    listenThree->setFlat(true);
    connect(listenThree, SIGNAL(clicked()), this, SLOT(showListenThree()));
    itemVBox->addWidget(listenThree, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forel�sning 2 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureTwoPDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 3, 0, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./3/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureThree = new QPushButton(tr("Forel�sning 3: Tonerne og de lange ord"));
    lectureThree->setFlat(true);
    lectureThree->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureThree, SIGNAL(clicked()), this, SLOT(showLectureThree()));
    itemVBox->addWidget(lectureThree, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *hyphenOne = new QPushButton(QString("   - ") + tr("Stavelsesdeling af bynavne"));
    hyphenOne->setFlat(true);
    connect(hyphenOne, SIGNAL(clicked()), this, SLOT(showHyphenOne()));
    itemVBox->addWidget(hyphenOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenFour = new QPushButton(QString("   - ") + tr("Lyd�velse 1.4: Skriv hvad du h�rte"));
    listenFour->setFlat(true);
    connect(listenFour, SIGNAL(clicked()), this, SLOT(showListenFour()));
    itemVBox->addWidget(listenFour, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomeOne = new QPushButton(QString("   - ") + tr("Sk�rmteksts�velse 1.1: Stavelsesdeling"));
    welcomeOne->setFlat(true);
    connect(welcomeOne, SIGNAL(clicked()), this, SLOT(showWelcomeOne()));
    itemVBox->addWidget(welcomeOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomeTwo = new QPushButton(QString("   - ") + tr("Sk�rmteksts�velse 1.2: Udtale"));
    welcomeTwo->setFlat(true);
    connect(welcomeTwo, SIGNAL(clicked()), this, SLOT(showWelcomeTwo()));
    itemVBox->addWidget(welcomeTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forel�sning 3 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureThreePDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 4, 0, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./4/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureFour = new QPushButton(tr("Forel�sning 4: Tr�ning og opsamling"));
    lectureFour->setFlat(true);
    lectureFour->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureFour, SIGNAL(clicked()), this, SLOT(showLectureFour()));
    itemVBox->addWidget(lectureFour, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *dialogOne = new QPushButton(QString("   - ") + tr("Minidialog 1.1: Gentag"));
    dialogOne->setFlat(true);
    connect(dialogOne, SIGNAL(clicked()), this, SLOT(showDialogOne()));
    itemVBox->addWidget(dialogOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *dialogTwo = new QPushButton(QString("   - ") + tr("Minidialog 1.2: Giv respons"));
    dialogTwo->setFlat(true);
    connect(dialogTwo, SIGNAL(clicked()), this, SLOT(showDialogTwo()));
    itemVBox->addWidget(dialogTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *dialogThree = new QPushButton(QString("   - ") + tr("Minidialog 1.3: Stil sp�rgsm�l"));
    dialogThree->setFlat(true);
    connect(dialogThree, SIGNAL(clicked()), this, SLOT(showDialogThree()));
    itemVBox->addWidget(dialogThree, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomeWords = new QPushButton(QString("   - ") + tr("Diktat af Tika's velkomst"));
    welcomeWords->setFlat(true);
    connect(welcomeWords, SIGNAL(clicked()), this, SLOT(showWelcomeWords()));
    itemVBox->addWidget(welcomeWords, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forel�sning 4 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureFourPDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 2, 1, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./5_1/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureFiveOne = new QPushButton(tr("Forel�sning 5.1: Gloserne i lektion 1"));
    lectureFiveOne->setFlat(true);
    lectureFiveOne->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureFiveOne, SIGNAL(clicked()), this, SLOT(showLectureFiveOne()));
    itemVBox->addWidget(lectureFiveOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lrPlayer = new QPushButton(QString("   - ") + tr("Lyt, forst�, gentag"));
    lrPlayer->setFlat(true);
    connect(lrPlayer, SIGNAL(clicked()), this, SLOT(showListenRepeatPlayer()));
    itemVBox->addWidget(lrPlayer, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forel�sning 5 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureFivePDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 3, 1, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./5_2/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureFiveTwo = new QPushButton(tr("Forel�sning 5.2: Grammatikken i lektion 1"));
    lectureFiveTwo->setFlat(true);
    lectureFiveTwo->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureFiveTwo, SIGNAL(clicked()), this, SLOT(showLectureFiveTwo()));
    itemVBox->addWidget(lectureFiveTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureOne = new QPushButton(QString("   - ") + tr("Struktur�velse 1.1: Lydopfattelse"));
    structureOne->setFlat(true);
    connect(structureOne, SIGNAL(clicked()), this, SLOT(showStructureOne()));
    itemVBox->addWidget(structureOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureTwo = new QPushButton(QString("   - ") + tr("Struktur�velse 1.2: Dan nye ord"));
    structureTwo->setFlat(true);
    connect(structureTwo, SIGNAL(clicked()), this, SLOT(showStructureTwo()));
    itemVBox->addWidget(structureTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureThree = new QPushButton(QString("   - ") + tr("Struktur�velse 1.3: Lyt, forst�, dan ord"));
    structureThree->setFlat(true);
    connect(structureThree, SIGNAL(clicked()), this, SLOT(showStructureThree()));
    itemVBox->addWidget(structureThree, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureFour = new QPushButton(QString("   - ") + tr("Struktur�velse 2.1: Dan nye ord"));
    structureFour->setFlat(true);
    connect(structureFour, SIGNAL(clicked()), this, SLOT(showStructureFour()));
    itemVBox->addWidget(structureFour, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureFive = new QPushButton(QString("   - ") + tr("Struktur�velse 2.2: Lyt, forst�, dan ord"));
    structureFive->setFlat(true);
    connect(structureFive, SIGNAL(clicked()), this, SLOT(showStructureFive()));
    itemVBox->addWidget(structureFive, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureSix = new QPushButton(QString("   - ") + tr("Struktur�velse 3.1: Dan nye ord"));
    structureSix->setFlat(true);
    connect(structureSix, SIGNAL(clicked()), this, SLOT(showStructureSix()));
    itemVBox->addWidget(structureSix, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureSeven = new QPushButton(QString("   - ") + tr("Struktur�velse 3.2: Lyt, forst�, dan ord"));
    structureSeven->setFlat(true);
    connect(structureSeven, SIGNAL(clicked()), this, SLOT(showStructureSeven()));
    itemVBox->addWidget(structureSeven, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forel�sning 5 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureFivePDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 4, 1, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./images/updown.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QLabel *updownHeader = new QLabel(tr("�velser i ordbygning:\nForst�, sammenk�d selv, overs�t"));
    updownHeader->setStyleSheet("font-weight: bold; text-align: left;");
    itemVBox->addWidget(updownHeader, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *updownOne = new QPushButton(QString("   - ") + tr("Ordbygning: Reception"));
    updownOne->setFlat(true);
    connect(updownOne, SIGNAL(clicked()), this, SLOT(showUpdownOne()));
    itemVBox->addWidget(updownOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *updownTwo = new QPushButton(QString("   - ") + tr("Ordbygning: Produktion"));
    updownTwo->setFlat(true);
    connect(updownTwo, SIGNAL(clicked()), this, SLOT(showUpdownTwo()));
    itemVBox->addWidget(updownTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *updownThree = new QPushButton(QString("   - ") + tr("Ordbygning: Overs�ttelse"));
    updownThree->setFlat(true);
    connect(updownThree, SIGNAL(clicked()), this, SLOT(showUpdownThree()));
    itemVBox->addWidget(updownThree, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 2, 2, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./images/pdf.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QLabel *appendixHeader = new QLabel(tr("Appendix og andet"));
    appendixHeader->setStyleSheet("font-weight: bold; text-align: left;");
    itemVBox->addWidget(appendixHeader, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *grammatica = new QPushButton(QString("   - ") + tr("Kapitel 3 (manuskriptudgave) af\n'Fors�g til en forbedret\ngr�nlandsk p�dagogisk grammatica'"));
    grammatica->setFlat(true);
    grammatica->setStyleSheet("text-align: left;");
    connect(grammatica, SIGNAL(clicked()), this, SLOT(showGrammaticaPDF()));
    itemVBox->addWidget(grammatica, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *pamphlet = new QPushButton(QString("   - ") + tr("Indstiksh�fte som PDF"));
    pamphlet->setFlat(true);
    connect(pamphlet, SIGNAL(clicked()), this, SLOT(showPamphletPDF()));
    itemVBox->addWidget(pamphlet, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 3, 2, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./images/english.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *toggleLang = new QPushButton(tr("Change language to English"));
    toggleLang->setFlat(true);
    toggleLang->setStyleSheet("font-weight: bold; text-align: left;");
    connect(toggleLang, SIGNAL(clicked()), this, SLOT(toggleLanguage()));
    itemVBox->addWidget(toggleLang, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 4, 2, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    outerGrid->setAlignment(Qt::AlignCenter|Qt::AlignTop);

    setLayout(outerGrid);
}

void TaskChooser::showLectureOne() {
    QSettings settings;
    settings.setValue("done_welcome", true);

    LecturePlayer *lecture = new LecturePlayer(tr("Forel�sning 1: De \"s�re\" lyd"), dataDir, tr("./1/danish/"), *this);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forel�sning 2: Typiske danskerfejl"), dataDir, tr("./2/danish/"), *this);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureThree() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forel�sning 3: Tonerne og de lange ord"), dataDir, tr("./3/danish/"), *this);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFour() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forel�sning 4: Tr�ning og opsamling"), dataDir, tr("./4/danish/"), *this);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveOne() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forel�sning 5.1: Gloserne i lektion 1"), dataDir, tr("./5_1/danish/"), *this);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveTwo() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forel�sning 5.2: Grammatikken i lektion 1"), dataDir, tr("./5_2/danish/"), *this);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureOnePDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./1/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureTwoPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./2/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureThreePDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./3/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureFourPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./4/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureFivePDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./5_1/danish/") + "lecture.pdf")));
}

void TaskChooser::showGrammaticaPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./grammatica/danish.pdf"))));
}

void TaskChooser::showPamphletPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(tr("./pamphlet/danish.pdf"))));
}

void TaskChooser::showHyphenOne() {
    HyphenOne *hyphen = new HyphenOne(dataDir, *this);
    hyphen->show();
    hyphen->raise();
    hyphen->activateWindow();
}

void TaskChooser::showDialogOne() {
    DialogOne *dialog = new DialogOne(dataDir, *this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showDialogTwo() {
    DialogTwo *dialog = new DialogTwo(dataDir, *this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showDialogThree() {
    DialogThree *dialog = new DialogThree(dataDir, *this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showListenOne() {
    ListenOne *listen = new ListenOne(dataDir, *this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenTwo() {
    ListenTwo *listen = new ListenTwo(dataDir, *this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenThree() {
    ListenThree *listen = new ListenThree(dataDir, *this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenFour() {
    ListenFour *listen = new ListenFour(dataDir, *this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showWelcomePlayer() {
    WelcomePlayer *welcome = new WelcomePlayer(dataDir, *this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeWords() {
    WelcomeWords *welcome = new WelcomeWords(dataDir, *this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeOne() {
    WelcomeOne *welcome = new WelcomeOne(dataDir, *this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeTwo() {
    WelcomeTwo *welcome = new WelcomeTwo(dataDir, *this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showListenRepeatPlayer() {
    ListenRepeatPlayer *lrplayer = new ListenRepeatPlayer(dataDir, *this);
    lrplayer->show();
    lrplayer->raise();
    lrplayer->activateWindow();
}

void TaskChooser::showPronounceOne() {
    PronounceOne *pronounce = new PronounceOne(dataDir, *this);
    pronounce->show();
    pronounce->raise();
    pronounce->activateWindow();
}

void TaskChooser::showPronounceTwo() {
    PronounceTwo *pronounce = new PronounceTwo(dataDir, *this);
    pronounce->show();
    pronounce->raise();
    pronounce->activateWindow();
}

void TaskChooser::showUpdownOne() {
    UpdownOne *updown = new UpdownOne(dataDir, *this);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showUpdownTwo() {
    UpdownTwo *updown = new UpdownTwo(dataDir, *this);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showUpdownThree() {
    UpdownThree *updown = new UpdownThree(dataDir, *this);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showStructureOne() {
    StructureOne *structure = new StructureOne(dataDir, "./1/", tr("Struktur�velse 1.1: Lydopfattelse"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureTwo() {
    StructureTwo *structure = new StructureTwo(dataDir, "./1/", tr("Struktur�velse 1.2: Dan nye ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureThree() {
    StructureThree *structure = new StructureThree(dataDir, "./1/", tr("Struktur�velse 1.3: Lyt, forst�, dan ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFour() {
    StructureTwo *structure = new StructureTwo(dataDir, "./2/", tr("Struktur�velse 2.1: Dan nye ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFive() {
    StructureThree *structure = new StructureThree(dataDir, "./2/", tr("Struktur�velse 2.2: Lyt, forst�, dan ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSix() {
    StructureTwo *structure = new StructureTwo(dataDir, "./3/", tr("Struktur�velse 3.1: Dan nye ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSeven() {
    StructureThree *structure = new StructureThree(dataDir, "./3/", tr("Struktur�velse 3.2: Lyt, forst�, dan ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::toggleLanguage() {
    QSettings settings;

    QString lang = settings.value("language").toString();
    if (lang == "english") {
        settings.setValue("language", "danish");
    }
    else {
        settings.setValue("language", "english");
    }

    lang = settings.value("language").toString();
    if (lang == "english") {
        translator->load("texts_en", dataDir.absoluteFilePath("./i18n/"));
    }
    else {
        translator->load("texts_da", dataDir.absoluteFilePath("./i18n/"));
    }

    TaskChooser *tc = new TaskChooser(dataDir, translator);
    tc->show();

    close();
}

void TaskChooser::checkFirstRun() {
    QSettings settings;

    // TODO
    bool hasXvid = settings.value("has_Xvid", false).toBool();
    if (!hasXvid) {
        QMessageBox mbox(QMessageBox::Question, tr("Xvid og MP3?"),
#if defined(Q_WS_WIN)
             tr("Dette program kr�ver at kunne afspille videoer med Xvid og MP3 codecs. Vil du installere Xvid codec?")
#elif defined(Q_WS_MAC)
             tr("Dette program kr�ver at kunne afspille videoer med Xvid og MP3 codecs. Vil du installere DivX codec?")
#else
             tr("Dette program kr�ver at kunne afspille videoer med Xvid og MP3 codecs. Vil du installere Xvid og MP3 codecs?")
#endif
             );
        QPushButton *yes = mbox.addButton(tr("Ja"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, jeg har Xvid eller DivX"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            QMessageBox::information(0, tr("Installer Xvid"), tr("Programmet �bner nu installeren i et nyt vindue og lukker s� dette. Start Learn Greenlandic igen n�r du har installeret Xvid eller DivX."));
            QDesktopServices::openUrl(QUrl::fromLocalFile(dataDir.absoluteFilePath(
#if defined(Q_WS_WIN)
                "../Xvid-1.3.1-20110324.exe"
#elif defined(Q_WS_MAC)
                "../DivXInstaller.dmg"
#else
                QString("../runasroot.sh \"") + QCoreApplication::instance()->applicationDirPath() + "/install-prereq-ubuntu.sh\""
#endif
                    )));
            QCoreApplication::quit();
            return;
        }

        try {
            XvidTest *xt = new XvidTest(this, dataDir);
            xt->exec();
        }
        catch (...) {
            QMessageBox::information(0, tr("Xvid error"), tr("Afspilningen af test filmen fejlede helt. Du b�r installere Xvid eller DivX codecs og s� pr�ve igen. Hvis intet virker, s� kontakt install@learngreenlandic.com eller se http://learngreenlandic.com/ for hj�lp."));
            QCoreApplication::quit();
            return;
        }
    }

    bool doneWelcome = settings.value("done_welcome", false).toBool();
    if (!doneWelcome) {
        showWelcomePlayer();
    }
}
