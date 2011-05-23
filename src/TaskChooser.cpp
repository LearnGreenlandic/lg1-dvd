#include "RichTextPushButton.hpp"
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
#include "TaskChooser.hpp"

TaskChooser::TaskChooser(QDir dataDir, QTranslator *translator) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dataDir(dataDir),
translator(translator)
{
    setWindowTitle(tr("Grønlandsk for voksne"));
    setContentsMargins(10,10,10,10);
    //setStyleSheet("background-color: white;");
    setStyleSheet("margin: 0; padding: 0;");

    QVBoxLayout *topVBox = new QVBoxLayout;
    topVBox->setContentsMargins(0,0,0,0);

    QPixmap qpx;
    QLabel *ql = new QLabel;
    /*
    qpx.load(dataDir.absoluteFilePath("./images/header.png"));
    qpx = qpx.scaled(185, 85, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ql->setPixmap(qpx);
    topVBox->addWidget(ql, Qt::AlignCenter|Qt::AlignTop);

    topVBox->addSpacing(10);
    //*/

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

    QPushButton *lectureOne = new QPushButton(tr("Forelæsning 1:\nDe \"sære\" lyd"));
    //lectureOne->setHtml(QString("<h3>") + tr("Forelæsning 1: De \"sære\" lyd") + "</h3>");
    lectureOne->setFlat(true);
    lectureOne->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureOne, SIGNAL(clicked()), this, SLOT(showLectureOne()));
    itemVBox->addWidget(lectureOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *pronounceOne = new QPushButton(QString("   - ") + tr("Udtaleøvelse 1.1: Gentag"));
    pronounceOne->setFlat(true);
    connect(pronounceOne, SIGNAL(clicked()), this, SLOT(showPronounceOne()));
    itemVBox->addWidget(pronounceOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *pronounceTwo = new QPushButton(QString("   - ") + tr("Udtaleøvelse 1.2: Diktat"));
    pronounceTwo->setFlat(true);
    connect(pronounceTwo, SIGNAL(clicked()), this, SLOT(showPronounceTwo()));
    itemVBox->addWidget(pronounceTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 1 som PDF"));
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

    QPushButton *lectureTwo = new QPushButton(tr("Forelæsning 2:\nTypiske danskerfejl"));
    lectureTwo->setFlat(true);
    lectureTwo->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureTwo, SIGNAL(clicked()), this, SLOT(showLectureTwo()));
    itemVBox->addWidget(lectureTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenOne = new QPushButton(QString("   - ") + tr("Lydøvelse 1.1: En eller to konsonanter"));
    listenOne->setFlat(true);
    connect(listenOne, SIGNAL(clicked()), this, SLOT(showListenOne()));
    itemVBox->addWidget(listenOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenTwo = new QPushButton(QString("   - ") + tr("Lydøvelse 1.2: r eller ikke r"));
    listenTwo->setFlat(true);
    connect(listenTwo, SIGNAL(clicked()), this, SLOT(showListenTwo()));
    itemVBox->addWidget(listenTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenThree = new QPushButton(QString("   - ") + tr("Lydøvelse 1.3: tt eller ts eller t"));
    listenThree->setFlat(true);
    connect(listenThree, SIGNAL(clicked()), this, SLOT(showListenThree()));
    itemVBox->addWidget(listenThree, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 2 som PDF"));
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

    QPushButton *lectureThree = new QPushButton(tr("Forelæsning 3:\nTonerne og de lange ord"));
    lectureThree->setFlat(true);
    lectureThree->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureThree, SIGNAL(clicked()), this, SLOT(showLectureThree()));
    itemVBox->addWidget(lectureThree, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *hyphenOne = new QPushButton(QString("   - ") + tr("Stavelsesdeling af bynavne"));
    hyphenOne->setFlat(true);
    connect(hyphenOne, SIGNAL(clicked()), this, SLOT(showHyphenOne()));
    itemVBox->addWidget(hyphenOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *listenFour = new QPushButton(QString("   - ") + tr("Lydøvelse 1.4: Skriv hvad du hørte"));
    listenFour->setFlat(true);
    connect(listenFour, SIGNAL(clicked()), this, SLOT(showListenFour()));
    itemVBox->addWidget(listenFour, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomeOne = new QPushButton(QString("   - ") + tr("Skærmtekstsøvelse 1.1: Stavelsesdeling"));
    welcomeOne->setFlat(true);
    connect(welcomeOne, SIGNAL(clicked()), this, SLOT(showWelcomeOne()));
    itemVBox->addWidget(welcomeOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomeTwo = new QPushButton(QString("   - ") + tr("Skærmtekstsøvelse 1.2: Udtale"));
    welcomeTwo->setFlat(true);
    connect(welcomeTwo, SIGNAL(clicked()), this, SLOT(showWelcomeTwo()));
    itemVBox->addWidget(welcomeTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 3 som PDF"));
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

    QPushButton *lectureFour = new QPushButton(tr("Forelæsning 4:\nTræning og opsamling"));
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

    QPushButton *dialogThree = new QPushButton(QString("   - ") + tr("Minidialog 1.3: Stil spørgsmål"));
    dialogThree->setFlat(true);
    connect(dialogThree, SIGNAL(clicked()), this, SLOT(showDialogThree()));
    itemVBox->addWidget(dialogThree, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("TODO: Diktat af Tika's tale"));
    lecturePDF->setFlat(true);
    //connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showPronounceTwo())); // TODO
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 4 som PDF"));
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

    QPushButton *lectureFiveOne = new QPushButton(tr("Forelæsning 5.1:\nGloserne i lektion 1"));
    lectureFiveOne->setFlat(true);
    lectureFiveOne->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureFiveOne, SIGNAL(clicked()), this, SLOT(showLectureFiveOne()));
    itemVBox->addWidget(lectureFiveOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lrPlayer = new QPushButton(QString("   - ") + tr("Lyt, forstå, gentag"));
    lrPlayer->setFlat(true);
    connect(lrPlayer, SIGNAL(clicked()), this, SLOT(showListenRepeatPlayer()));
    itemVBox->addWidget(lrPlayer, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 5 som PDF"));
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

    QPushButton *lectureFiveTwo = new QPushButton(tr("Forelæsning 5.2:\nGrammatikken i lektion 1"));
    lectureFiveTwo->setFlat(true);
    lectureFiveTwo->setStyleSheet("font-weight: bold; text-align: left;");
    connect(lectureFiveTwo, SIGNAL(clicked()), this, SLOT(showLectureFiveTwo()));
    itemVBox->addWidget(lectureFiveTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureOne = new QPushButton(QString("   - ") + tr("Strukturøvelse 1.1: Lydopfattelse"));
    structureOne->setFlat(true);
    connect(structureOne, SIGNAL(clicked()), this, SLOT(showStructureOne()));
    itemVBox->addWidget(structureOne, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureTwo = new QPushButton(QString("   - ") + tr("Strukturøvelse 1.2: Dan nye ord"));
    structureTwo->setFlat(true);
    connect(structureTwo, SIGNAL(clicked()), this, SLOT(showStructureTwo()));
    itemVBox->addWidget(structureTwo, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureThree = new QPushButton(QString("   - ") + tr("Strukturøvelse 1.3: Lyt, forstå, dan ord"));
    structureThree->setFlat(true);
    connect(structureThree, SIGNAL(clicked()), this, SLOT(showStructureThree()));
    itemVBox->addWidget(structureThree, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureFour = new QPushButton(QString("   - ") + tr("Strukturøvelse 2.1: Dan nye ord"));
    structureFour->setFlat(true);
    connect(structureFour, SIGNAL(clicked()), this, SLOT(showStructureFour()));
    itemVBox->addWidget(structureFour, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureFive = new QPushButton(QString("   - ") + tr("Strukturøvelse 2.2: Lyt, forstå, dan ord"));
    structureFive->setFlat(true);
    connect(structureFive, SIGNAL(clicked()), this, SLOT(showStructureFive()));
    itemVBox->addWidget(structureFive, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureSix = new QPushButton(QString("   - ") + tr("Strukturøvelse 3.1: Dan nye ord"));
    structureSix->setFlat(true);
    connect(structureSix, SIGNAL(clicked()), this, SLOT(showStructureSix()));
    itemVBox->addWidget(structureSix, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *structureSeven = new QPushButton(QString("   - ") + tr("Strukturøvelse 3.2: Lyt, forstå, dan ord"));
    structureSeven->setFlat(true);
    connect(structureSeven, SIGNAL(clicked()), this, SLOT(showStructureSeven()));
    itemVBox->addWidget(structureSeven, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 5 som PDF"));
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
    qpx.load(dataDir.absoluteFilePath(tr("./5_1/danish/0.png"))); // TODO
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QLabel *updownHeader = new QLabel(tr("Øvelser i ordbygning:\nForstå, sammenkæd selv, oversæt"));
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

    QPushButton *updownThree = new QPushButton(QString("   - ") + tr("Ordbygning: Oversættelse"));
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
    qpx.load(dataDir.absoluteFilePath(tr("./5_2/danish/0.png"))); // TODO
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *appendix = new QPushButton(tr("Appendix:\nKapitel 3 (manuskriptudgave) af\n'Forsøg til en forbedret\ngrønlandsk pædagogisk grammatica'"));
    appendix->setFlat(true);
    appendix->setStyleSheet("font-weight: bold; text-align: left;");
    //connect(appendix, SIGNAL(clicked()), this, SLOT(showLectureFiveTwo())); // TODO
    itemVBox->addWidget(appendix, 0, Qt::AlignLeft|Qt::AlignTop);

    itemHBox->addLayout(itemVBox);
    outerGrid->addLayout(itemHBox, 3, 2, 1, 1, Qt::AlignLeft|Qt::AlignTop);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(dataDir.absoluteFilePath(tr("./5_2/danish/0.png"))); // TODO
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
    topVBox->addLayout(outerGrid);
    topVBox->setAlignment(Qt::AlignCenter|Qt::AlignTop);

    //topVBox->addSpacing(10);

    setLayout(topVBox);
}

void TaskChooser::showLectureOne() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forelæsning 1: De \"sære\" lyd"), dataDir, tr("./1/danish/"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forelæsning 2: Typiske danskerfejl"), dataDir, tr("./2/danish/"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureThree() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forelæsning 3: Tonerne og de lange ord"), dataDir, tr("./3/danish/"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFour() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forelæsning 4: Træning og opsamling"), dataDir, tr("./4/danish/"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveOne() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forelæsning 5.1: Gloserne i lektion 1"), dataDir, tr("./5_1/danish/"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveTwo() {
    LecturePlayer *lecture = new LecturePlayer(tr("Forelæsning 5.2: Grammatikken i lektion 1"), dataDir, tr("./5_2/danish/"));
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

void TaskChooser::showHyphenOne() {
    HyphenOne *hyphen = new HyphenOne(dataDir);
    hyphen->show();
    hyphen->raise();
    hyphen->activateWindow();
}

void TaskChooser::showDialogOne() {
    DialogOne *dialog = new DialogOne(dataDir);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showDialogTwo() {
    DialogTwo *dialog = new DialogTwo(dataDir);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showDialogThree() {
    DialogThree *dialog = new DialogThree(dataDir);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showListenOne() {
    ListenOne *listen = new ListenOne(dataDir);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenTwo() {
    ListenTwo *listen = new ListenTwo(dataDir);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenThree() {
    ListenThree *listen = new ListenThree(dataDir);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenFour() {
    ListenFour *listen = new ListenFour(dataDir);
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

void TaskChooser::showWelcomeOne() {
    WelcomeOne *welcome = new WelcomeOne(dataDir);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeTwo() {
    WelcomeTwo *welcome = new WelcomeTwo(dataDir);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showListenRepeatPlayer() {
    ListenRepeatPlayer *lrplayer = new ListenRepeatPlayer(dataDir);
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
    UpdownOne *updown = new UpdownOne(dataDir);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showUpdownTwo() {
    UpdownTwo *updown = new UpdownTwo(dataDir);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showUpdownThree() {
    UpdownThree *updown = new UpdownThree(dataDir);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showStructureOne() {
    StructureOne *structure = new StructureOne(dataDir, "./1/", tr("Strukturøvelse 1.1: Lydopfattelse"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureTwo() {
    StructureTwo *structure = new StructureTwo(dataDir, "./1/", tr("Strukturøvelse 1.2: Dan nye ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureThree() {
    StructureThree *structure = new StructureThree(dataDir, "./1/", tr("Strukturøvelse 1.3: Lyt, forstå, dan ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFour() {
    StructureTwo *structure = new StructureTwo(dataDir, "./2/", tr("Strukturøvelse 2.1: Dan nye ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFive() {
    StructureThree *structure = new StructureThree(dataDir, "./2/", tr("Strukturøvelse 2.2: Lyt, forstå, dan ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSix() {
    StructureTwo *structure = new StructureTwo(dataDir, "./3/", tr("Strukturøvelse 3.1: Dan nye ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSeven() {
    StructureThree *structure = new StructureThree(dataDir, "./3/", tr("Strukturøvelse 3.2: Lyt, forstå, dan ord"));
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
