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
#include "ValidateKey.hpp"
#include "TaskChooser.hpp"

#include <QtGlobal>

TaskChooser::TaskChooser(const dirmap_t& dirs, QTranslator *translator) :
QWidget(nullptr, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dirs(dirs),
translator(translator)
{
    setWindowTitle(tr("Grønlandsk for voksne"));
    setContentsMargins(5,5,5,5);
    setStyleSheet("margin: 0; padding: 0; text-align: left;");

    QPixmap qpx;
    QLabel *ql = new QLabel;

    auto *outerHBox = new QHBoxLayout;
    outerHBox->setContentsMargins(0,0,0,0);

    auto *outerVBox = new QVBoxLayout;
    outerVBox->setContentsMargins(0,0,0,0);


    auto *itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    auto *itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, "./images/welcome.png"));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *welcomePlayer = new QPushButton(tr("Velkomst ved Tikaajaat Kristiansen"));
    welcomePlayer->setFlat(true);
    welcomePlayer->setStyleSheet("font-weight: bold; text-align: left;");
    connect(welcomePlayer, SIGNAL(clicked()), this, SLOT(showWelcomePlayer()));
    itemVBox->addWidget(welcomePlayer, 0, Qt::AlignLeft|Qt::AlignTop);

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./1/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureOne = new QPushButton(tr("Forelæsning 1: De \"sære\" lyd"));
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

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./2/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureTwo = new QPushButton(tr("Forelæsning 2: Typiske danskerfejl"));
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

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./3/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureThree = new QPushButton(tr("Forelæsning 3: Tonerne og de lange ord"));
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

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    outerVBox->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    outerHBox->addLayout(outerVBox);
    outerVBox = new QVBoxLayout;
    outerVBox->setContentsMargins(0,0,0,0);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./4/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureFour = new QPushButton(tr("Forelæsning 4: Træning og opsamling"));
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

    QPushButton *welcomeWords = new QPushButton(QString("   - ") + tr("Diktat af Tika's velkomst"));
    welcomeWords->setFlat(true);
    connect(welcomeWords, SIGNAL(clicked()), this, SLOT(showWelcomeWords()));
    itemVBox->addWidget(welcomeWords, 0, Qt::AlignLeft|Qt::AlignTop);

    lecturePDF = new QPushButton(QString("   - ") + tr("Forelæsning 4 som PDF"));
    lecturePDF->setFlat(true);
    connect(lecturePDF, SIGNAL(clicked()), this, SLOT(showLectureFourPDF()));
    itemVBox->addWidget(lecturePDF, 0, Qt::AlignLeft|Qt::AlignTop);

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./5_1/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureFiveOne = new QPushButton(tr("Forelæsning 5.1: Gloserne i lektion 1"));
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

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./5_2/danish/0.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *lectureFiveTwo = new QPushButton(tr("Forelæsning 5.2: Grammatikken i lektion 1"));
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

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    outerVBox->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    outerHBox->addLayout(outerVBox);
    outerVBox = new QVBoxLayout;
    outerVBox->setContentsMargins(0,0,0,0);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./images/updown.png")));
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

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./images/pdf.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QLabel *appendixHeader = new QLabel(tr("Appendix og andet"));
    appendixHeader->setStyleSheet("font-weight: bold; text-align: left;");
    itemVBox->addWidget(appendixHeader, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *grammatica = new QPushButton(QString("   - ") + tr("Kapitel 3 (manuskriptudgave) af\n'Forsøg til en forbedret\ngrønlandsk pædagogisk grammatica'"));
    grammatica->setFlat(true);
    grammatica->setStyleSheet("text-align: left;");
    connect(grammatica, SIGNAL(clicked()), this, SLOT(showGrammaticaPDF()));
    itemVBox->addWidget(grammatica, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *pamphlet = new QPushButton(QString("   - ") + tr("Indstikshæfte som PDF"));
    pamphlet->setFlat(true);
    connect(pamphlet, SIGNAL(clicked()), this, SLOT(showPamphletPDF()));
    itemVBox->addWidget(pamphlet, 0, Qt::AlignLeft|Qt::AlignTop);

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);


    itemHBox = new QHBoxLayout;
    itemHBox->setContentsMargins(0,0,0,0);

    itemVBox = new QVBoxLayout;
    itemVBox->setContentsMargins(0,0,0,0);

    ql = new QLabel;
    qpx.load(find_newest(dirs, tr("./images/english.png")));
    qpx = qpx.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ql->setPixmap(qpx);
    itemHBox->addWidget(ql, 0, Qt::AlignLeft|Qt::AlignTop);

    QPushButton *toggleLang = new QPushButton(tr("Change language to English"));
    toggleLang->setFlat(true);
    toggleLang->setStyleSheet("font-weight: bold; text-align: left;");
    connect(toggleLang, SIGNAL(clicked()), this, SLOT(toggleLanguage()));
    itemVBox->addWidget(toggleLang, 0, Qt::AlignLeft|Qt::AlignTop);

    itemVBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    itemHBox->addLayout(itemVBox);
    itemHBox->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    outerVBox->addLayout(itemHBox);

    QSettings settings;
    if (!settings.value("site_title").toString().isEmpty()) {
        QString labeltxt = QString(tr("Denne licens tilhører %1 og vil kræve fornyelse efter %2")).arg(settings.value("site_title").toString()).arg(settings.value("site_expire").toString());
        QLabel *label = new QLabel(QString("<i>") + labeltxt + "</i>");
        label->setWordWrap(true);
        outerVBox->addSpacing(15);
        outerVBox->addWidget(label);
    }


    outerVBox->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    outerHBox->addLayout(outerVBox);
    outerHBox->setAlignment(Qt::AlignCenter|Qt::AlignTop);

    setLayout(outerHBox);
}

void TaskChooser::showLectureOne() {
    QSettings settings;
    settings.setValue("done_welcome", true);

    LecturePlayer *lecture = new LecturePlayer(*this, tr("./1/danish/"), tr("Forelæsning 1: De \"sære\" lyd"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo() {
    LecturePlayer *lecture = new LecturePlayer(*this, tr("./2/danish/"), tr("Forelæsning 2: Typiske danskerfejl"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureThree() {
    LecturePlayer *lecture = new LecturePlayer(*this, tr("./3/danish/"), tr("Forelæsning 3: Tonerne og de lange ord"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFour() {
    LecturePlayer *lecture = new LecturePlayer(*this, tr("./4/danish/"), tr("Forelæsning 4: Træning og opsamling"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveOne() {
    LecturePlayer *lecture = new LecturePlayer(*this, tr("./5_1/danish/"), tr("Forelæsning 5.1: Gloserne i lektion 1"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveTwo() {
    LecturePlayer *lecture = new LecturePlayer(*this, tr("./5_2/danish/"), tr("Forelæsning 5.2: Grammatikken i lektion 1"));
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureOnePDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./1/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureTwoPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./2/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureThreePDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./3/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureFourPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./4/danish/") + "lecture.pdf")));
}

void TaskChooser::showLectureFivePDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./5_1/danish/") + "lecture.pdf")));
}

void TaskChooser::showGrammaticaPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./grammatica/danish.pdf"))));
}

void TaskChooser::showPamphletPDF() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(find_newest(dirs, tr("./pamphlet/danish.pdf"))));
}

void TaskChooser::showHyphenOne() {
    auto *hyphen = new HyphenOne(*this);
    hyphen->show();
    hyphen->raise();
    hyphen->activateWindow();
}

void TaskChooser::showDialogOne() {
    auto *dialog = new DialogOne(*this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showDialogTwo() {
    auto *dialog = new DialogTwo(*this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showDialogThree() {
    auto *dialog = new DialogThree(*this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void TaskChooser::showListenOne() {
    auto *listen = new ListenOne(*this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenTwo() {
    auto *listen = new ListenTwo(*this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenThree() {
    auto *listen = new ListenThree(*this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showListenFour() {
    auto *listen = new ListenFour(*this);
    listen->show();
    listen->raise();
    listen->activateWindow();
}

void TaskChooser::showWelcomePlayer() {
    auto *welcome = new WelcomePlayer(*this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeWords() {
    auto *welcome = new WelcomeWords(*this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeOne() {
    auto *welcome = new WelcomeOne(*this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showWelcomeTwo() {
    auto *welcome = new WelcomeTwo(*this);
    welcome->show();
    welcome->raise();
    welcome->activateWindow();
}

void TaskChooser::showListenRepeatPlayer() {
    auto *lrplayer = new ListenRepeatPlayer(*this);
    lrplayer->show();
    lrplayer->raise();
    lrplayer->activateWindow();
}

void TaskChooser::showPronounceOne() {
    auto *pronounce = new PronounceOne(*this);
    pronounce->show();
    pronounce->raise();
    pronounce->activateWindow();
}

void TaskChooser::showPronounceTwo() {
    auto *pronounce = new PronounceTwo(*this);
    pronounce->show();
    pronounce->raise();
    pronounce->activateWindow();
}

void TaskChooser::showUpdownOne() {
    auto *updown = new UpdownOne(*this);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showUpdownTwo() {
    auto *updown = new UpdownTwo(*this);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showUpdownThree() {
    auto *updown = new UpdownThree(*this);
    updown->show();
    updown->raise();
    updown->activateWindow();
}

void TaskChooser::showStructureOne() {
    StructureOne *structure = new StructureOne("./1/", tr("Strukturøvelse 1.1: Lydopfattelse"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureTwo() {
    StructureTwo *structure = new StructureTwo("./1/", tr("Strukturøvelse 1.2: Dan nye ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureThree() {
    StructureThree *structure = new StructureThree("./1/", tr("Strukturøvelse 1.3: Lyt, forstå, dan ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFour() {
    StructureTwo *structure = new StructureTwo("./2/", tr("Strukturøvelse 2.1: Dan nye ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFive() {
    StructureThree *structure = new StructureThree("./2/", tr("Strukturøvelse 2.2: Lyt, forstå, dan ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSix() {
    StructureTwo *structure = new StructureTwo("./3/", tr("Strukturøvelse 3.1: Dan nye ord"), *this);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSeven() {
    StructureThree *structure = new StructureThree("./3/", tr("Strukturøvelse 3.2: Lyt, forstå, dan ord"), *this);
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
        translator->load(find_newest(dirs, "i18n/texts_en.qm"));
    }
    else {
        translator->load(find_newest(dirs, "i18n/texts_da.qm"));
    }

    auto *tc = new TaskChooser(dirs, translator);
    tc->show();

    close();
}

void TaskChooser::checkFirstRun() {
    QSettings settings;

    bool hasXvid = settings.value("has_xvid", false).toBool();
    while (!hasXvid) {
        QMessageBox mbox(QMessageBox::Question, tr("Xvid og MP3?"),
#if defined(Q_OS_WIN)
             tr("Dette program kræver at kunne afspille videoer med Xvid og MP3 codecs. Vil du installere Xvid codec?")
#elif defined(Q_OS_MAC)
             tr("Dette program kræver at kunne afspille videoer med Xvid og MP3 codecs. Vil du installere DivX codec?")
#else
             tr("Dette program kræver at kunne afspille videoer med Xvid og MP3 codecs. Vil du installere Xvid og MP3 codecs?")
#endif
             );
        QPushButton *yes = mbox.addButton(tr("Ja"), QMessageBox::YesRole);
        mbox.addButton(tr("Nej, jeg har Xvid eller DivX"), QMessageBox::NoRole);
        mbox.exec();

        if (mbox.clickedButton() == yes) {
            QMessageBox::information(nullptr, tr("Installer Xvid"), tr("Programmet åbner nu installeren i et nyt vindue og lukker så dette. Start Learn Greenlandic igen når du har installeret Xvid eller DivX."));
            QString torun = find_newest(dirs,
            #if defined(Q_OS_WIN)
                "../Xvid-1.3.2-20110601.exe"
            #elif defined(Q_OS_MAC)
                "../DivXInstaller.dmg"
            #else
                "../autorun.sh"
            #endif
                    )
            ;

            #if defined(Q_OS_WIN) || defined(Q_OS_MAC)
                QDesktopServices::openUrl(QUrl::fromLocalFile(torun));
            #else
                torun = QString("/usr/bin/xterm -e \"") + QCoreApplication::instance()->applicationDirPath() + "/install-prereq-ubuntu.sh\" &";
                system(torun.toStdString().c_str());
            #endif

            QCoreApplication::quit();
            return;
        }

        try {
            XvidTest *xt = new XvidTest(find_newest(dirs, "testxvid.avi"));
            xt->exec();
        }
        catch (...) {
            QMessageBox::information(nullptr, tr("Xvid error"), tr("Afspilningen af test filmen fejlede helt. Du bør installere Xvid eller DivX codecs og så prøve igen. Hvis intet virker, så kontakt install@learngreenlandic.com eller se http://learngreenlandic.com/ for hjælp."));
            QCoreApplication::quit();
            return;
        }
        hasXvid = settings.value("has_xvid", false).toBool();
    }

    if (!settings.value("license_key", "").toString().isEmpty() && settings.value("license_key", "").toString().at(0) == 'V') {
        QCryptographicHash sha1(QCryptographicHash::Sha1);
        sha1.addData(settings.value("license_key").toString().toUtf8());
        sha1.addData(settings.value("site_title").toString().toUtf8());
        sha1.addData(settings.value("site_expire").toString().toUtf8());
        sha1.addData("Keeping honest people honest.");
        sha1.addData(settings.value("encryption_key").toString().toUtf8());
        if (sha1.result().toHex() != settings.value("site_verification").toString().toUtf8()) {
            settings.remove("site_expire");
        }

        QDate now = QDate::currentDate();
        QDate expires = settings.value("site_expire").toDate();
        if (!expires.isValid() || now > expires) {
            settings.remove("license_key");
            settings.remove("site_title");
            settings.remove("site_expire");
            settings.remove("site_verification");
            settings.remove("encryption_key");
        }
    }

    if (settings.value("license_key", "").toString().isEmpty() || settings.value("encryption_key", "").toString().isEmpty() || settings.value("encryption_key", "").toString().at(0) != 'P') {
        auto *vk = new ValidateKey;
        vk->show();
        vk->raise();
        vk->activateWindow();
    }
}
