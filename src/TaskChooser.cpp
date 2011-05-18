#include "LecturePlayer.hpp"
#include "WelcomeOne.hpp"
#include "WelcomeTwo.hpp"
#include "PronounceOne.hpp"
#include "PronounceTwo.hpp"
#include "UpdownOne.hpp"
#include "UpdownTwo.hpp"
#include "UpdownThree.hpp"
#include "StructureOne.hpp"
#include "StructureTwo.hpp"
#include "StructureThree.hpp"
#include "TaskChooser.hpp"

TaskChooser::TaskChooser(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dataDir(dataDir)
{
    setWindowTitle("Learn Greenlandic Demo");

    QVBoxLayout *vbox = new QVBoxLayout;

    QLabel *ql = new QLabel(tr("Demo af diverse funktionaliteter som vil være i det færdige produkt."));
    ql->setWordWrap(true);
    vbox->addWidget(ql);
    vbox->addSpacing(5);

    QHBoxLayout *lecHBox = new QHBoxLayout;

    QGroupBox *lecGBox = new QGroupBox(tr("Forelæsninger"));
    QVBoxLayout *lecVBox = new QVBoxLayout;

    QPushButton *lectureOne = new QPushButton(tr("Forelæsning 1: De \"sære\" lyd"));
    QPushButton *lectureTwo = new QPushButton(tr("Forelæsning 2: Typiske danskerfejl"));
    QPushButton *lectureThree = new QPushButton(tr("Forelæsning 3: Tonerne og de lange ord"));
    QPushButton *lectureFour = new QPushButton(tr("Forelæsning 4: Træning og opsamling"));
    QPushButton *lectureFiveOne = new QPushButton(tr("Forelæsning 5.1: Gloserne i lektion 1"));
    QPushButton *lectureFiveTwo = new QPushButton(tr("Forelæsning 5.2: Grammatikken i lektion 1"));
    connect(lectureOne, SIGNAL(clicked()), this, SLOT(showLectureOne()));
    connect(lectureTwo, SIGNAL(clicked()), this, SLOT(showLectureTwo()));
    connect(lectureThree, SIGNAL(clicked()), this, SLOT(showLectureThree()));
    connect(lectureFour, SIGNAL(clicked()), this, SLOT(showLectureFour()));
    connect(lectureFiveOne, SIGNAL(clicked()), this, SLOT(showLectureFiveOne()));
    connect(lectureFiveTwo, SIGNAL(clicked()), this, SLOT(showLectureFiveTwo()));

    lecVBox->addWidget(lectureOne);
    lecVBox->addWidget(lectureTwo);
    lecVBox->addWidget(lectureThree);
    lecVBox->addWidget(lectureFour);
    lecVBox->addWidget(lectureFiveOne);
    lecVBox->addWidget(lectureFiveTwo);

    lecGBox->setLayout(lecVBox);
    lecHBox->addWidget(lecGBox);


    QGroupBox *stGBox = new QGroupBox(tr("Strukturøvelser"));
    QVBoxLayout *stVBox = new QVBoxLayout;

    QPushButton *structureOne = new QPushButton(tr("Struktur 1.1: Lydopfattelse"));
    QPushButton *structureTwo = new QPushButton(tr("Struktur 1.2: Dan nye ord"));
    QPushButton *structureThree = new QPushButton(tr("Struktur 1.3: Lyt, forstå, dan ord"));
    QPushButton *structureFour = new QPushButton(tr("Struktur 2.1: Dan nye ord"));
    QPushButton *structureFive = new QPushButton(tr("Struktur 2.2: Lyt, forstå, dan ord"));
    QPushButton *structureSix = new QPushButton(tr("Struktur 3.1: Dan nye ord"));
    QPushButton *structureSeven = new QPushButton(tr("Struktur 3.2: Lyt, forstå, dan ord"));
    connect(structureOne, SIGNAL(clicked()), this, SLOT(showStructureOne()));
    connect(structureTwo, SIGNAL(clicked()), this, SLOT(showStructureTwo()));
    connect(structureThree, SIGNAL(clicked()), this, SLOT(showStructureThree()));
    connect(structureFour, SIGNAL(clicked()), this, SLOT(showStructureFour()));
    connect(structureFive, SIGNAL(clicked()), this, SLOT(showStructureFive()));
    connect(structureSix, SIGNAL(clicked()), this, SLOT(showStructureSix()));
    connect(structureSeven, SIGNAL(clicked()), this, SLOT(showStructureSeven()));

    stVBox->addWidget(structureOne);
    stVBox->addWidget(structureTwo);
    stVBox->addWidget(structureThree);
    stVBox->addWidget(structureFour);
    stVBox->addWidget(structureFive);
    stVBox->addWidget(structureSix);
    stVBox->addWidget(structureSeven);

    stGBox->setLayout(stVBox);
    lecHBox->addWidget(stGBox);

    vbox->addLayout(lecHBox);


    QGroupBox *wcGBox = new QGroupBox(tr("Velkomstøvelser"));
    QVBoxLayout *wcVBox = new QVBoxLayout;

    QPushButton *welcomeOne = new QPushButton(tr("Velkomst: Stavelsesdeling"));
    QPushButton *welcomeTwo = new QPushButton(tr("Velkomst: Udtale"));
    connect(welcomeOne, SIGNAL(clicked()), this, SLOT(showWelcomeOne()));
    connect(welcomeTwo, SIGNAL(clicked()), this, SLOT(showWelcomeTwo()));

    wcVBox->addWidget(welcomeOne);
    wcVBox->addWidget(welcomeTwo);

    wcGBox->setLayout(wcVBox);
    vbox->addWidget(wcGBox);


    QGroupBox *pnGBox = new QGroupBox(tr("Udtaleøvelser"));
    QVBoxLayout *pnVBox = new QVBoxLayout;

    QPushButton *pronounceOne = new QPushButton(tr("Udtale: Gentag"));
    QPushButton *pronounceTwo = new QPushButton(tr("Udtale: Afskriv"));
    connect(pronounceOne, SIGNAL(clicked()), this, SLOT(showPronounceOne()));
    connect(pronounceTwo, SIGNAL(clicked()), this, SLOT(showPronounceTwo()));

    pnVBox->addWidget(pronounceOne);
    pnVBox->addWidget(pronounceTwo);

    pnGBox->setLayout(pnVBox);
    vbox->addWidget(pnGBox);


    QGroupBox *udGBox = new QGroupBox(tr("Up/Down Øvelser"));
    QVBoxLayout *udVBox = new QVBoxLayout;

    QPushButton *updownOne = new QPushButton(tr("Up/Down: Reception"));
    QPushButton *updownTwo = new QPushButton(tr("Up/Down: Produktion"));
    QPushButton *updownThree = new QPushButton(tr("Up/Down: Oversættelse"));
    connect(updownOne, SIGNAL(clicked()), this, SLOT(showUpdownOne()));
    connect(updownTwo, SIGNAL(clicked()), this, SLOT(showUpdownTwo()));
    connect(updownThree, SIGNAL(clicked()), this, SLOT(showUpdownThree()));

    udVBox->addWidget(updownOne);
    udVBox->addWidget(updownTwo);
    udVBox->addWidget(updownThree);

    udGBox->setLayout(udVBox);
    vbox->addWidget(udGBox);


    setLayout(vbox);
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

void TaskChooser::showLectureOne_Eng() {
    LecturePlayer *lecture = new LecturePlayer("Lecture 1: The New Sounds", dataDir, "./1/english/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo_Eng() {
    LecturePlayer *lecture = new LecturePlayer("Lecture 2: Typical mistakes", dataDir, "./2/english/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureThree_Eng() {
    LecturePlayer *lecture = new LecturePlayer("Lecture 3: Tones and long words", dataDir, "./3/english/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFour_Eng() {
    LecturePlayer *lecture = new LecturePlayer("Lecture 4: Practice and repetition", dataDir, "./4/english/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveOne_Eng() {
    LecturePlayer *lecture = new LecturePlayer("Lecture 5.1: Words and lexicons in lesson one", dataDir, "./5_1/english/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveTwo_Eng() {
    LecturePlayer *lecture = new LecturePlayer("Lecture 5.2: Introduction to grammar", dataDir, "./5_2/english/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
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

void TaskChooser::showPronounceOne() {
    PronounceOne *pronounce = new PronounceOne(dataDir);
    pronounce->show();
    pronounce->raise();
    pronounce->activateWindow();
}

void TaskChooser::showPronounceTwo() {
    PronounceTwo *pronounce = new PronounceTwo(dataDir);
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
    StructureOne *structure = new StructureOne(dataDir, "./1/", tr("Struktur 1.1: Lydopfattelse"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureTwo() {
    StructureTwo *structure = new StructureTwo(dataDir, "./1/", tr("Struktur 1.2: Dan nye ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureThree() {
    StructureThree *structure = new StructureThree(dataDir, "./1/", tr("Struktur 1.3: Lyt, forstå, dan ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFour() {
    StructureTwo *structure = new StructureTwo(dataDir, "./2/", tr("Struktur 2.1: Dan nye ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureFive() {
    StructureThree *structure = new StructureThree(dataDir, "./2/", tr("Struktur 2.2: Lyt, forstå, dan ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSix() {
    StructureTwo *structure = new StructureTwo(dataDir, "./3/", tr("Struktur 3.1: Dan nye ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureSeven() {
    StructureThree *structure = new StructureThree(dataDir, "./3/", tr("Struktur 3.2: Lyt, forstå, dan ord"));
    structure->show();
    structure->raise();
    structure->activateWindow();
}
