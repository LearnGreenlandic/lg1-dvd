#include "LecturePlayer.hpp"
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


    QGroupBox *lecGBox = new QGroupBox("Forel�sninger");
    QVBoxLayout *lecVBox = new QVBoxLayout;

    QLabel *ql = new QLabel("Demo af diverse funktionaliteter som vil v�re i det f�rdige produkt.\n");
    ql->setWordWrap(true);
    vbox->addWidget(ql);

    QPushButton *lectureOne = new QPushButton("Forel�sning 1: De \"s�re\" lyd");
    QPushButton *lectureTwo = new QPushButton("Forel�sning 2: Typiske danskerfejl");
    QPushButton *lectureThree = new QPushButton("Forel�sning 3: Tonerne og de lange ord");
    QPushButton *lectureFour = new QPushButton("Forel�sning 4: Tr�ning og opsamling");
    QPushButton *lectureFiveOne = new QPushButton("Forel�sning 5.1: Gloserne i lektion 1");
    QPushButton *lectureFiveTwo = new QPushButton("Forel�sning 5.2: Grammatikken i lektion 1");
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

    lecGBox->setLayout(lecVBox);
    vbox->addWidget(lecGBox);


    QGroupBox *udGBox = new QGroupBox("Up/Down �velser");
    QVBoxLayout *udVBox = new QVBoxLayout;

    QPushButton *updownOne = new QPushButton("Up/Down: Reception");
    QPushButton *updownTwo = new QPushButton("Up/Down: Produktion");
    QPushButton *updownThree = new QPushButton("Up/Down: Overs�ttelse");
    connect(updownOne, SIGNAL(clicked()), this, SLOT(showUpdownOne()));
    connect(updownTwo, SIGNAL(clicked()), this, SLOT(showUpdownTwo()));
    connect(updownThree, SIGNAL(clicked()), this, SLOT(showUpdownThree()));

    udVBox->addWidget(updownOne);
    udVBox->addWidget(updownTwo);
    udVBox->addWidget(updownThree);

    udGBox->setLayout(udVBox);
    vbox->addWidget(udGBox);


    QGroupBox *stGBox = new QGroupBox("Struktur�velser");
    QVBoxLayout *stVBox = new QVBoxLayout;

    QPushButton *structureOne = new QPushButton("Struktur: Lydopfattelse");
    QPushButton *structureTwo = new QPushButton("Struktur: Dan nye ord");
    QPushButton *structureThree = new QPushButton("Struktur: Lyt, forst�, dan ord");
    connect(structureOne, SIGNAL(clicked()), this, SLOT(showStructureOne()));
    connect(structureTwo, SIGNAL(clicked()), this, SLOT(showStructureTwo()));
    connect(structureThree, SIGNAL(clicked()), this, SLOT(showStructureThree()));

    stVBox->addWidget(structureOne);
    stVBox->addWidget(structureTwo);
    stVBox->addWidget(structureThree);

    stGBox->setLayout(stVBox);
    vbox->addWidget(stGBox);

    setLayout(vbox);
}

void TaskChooser::showLectureOne() {
    LecturePlayer *lecture = new LecturePlayer("Forel�sning 1: De \"s�re\" lyd", dataDir, "./1/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo() {
    LecturePlayer *lecture = new LecturePlayer("Forel�sning 2: Typiske danskerfejl", dataDir, "./2/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureThree() {
    LecturePlayer *lecture = new LecturePlayer("Forel�sning 3: Tonerne og de lange ord", dataDir, "./3/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFour() {
    LecturePlayer *lecture = new LecturePlayer("Forel�sning 4: Tr�ning og opsamling", dataDir, "./4/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveOne() {
    LecturePlayer *lecture = new LecturePlayer("Forel�sning 5.1: Gloserne i lektion 1", dataDir, "./5_1/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureFiveTwo() {
    LecturePlayer *lecture = new LecturePlayer("Forel�sning 5.2: Grammatikken i lektion 1", dataDir, "./5_2/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
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
    StructureOne *structure = new StructureOne(dataDir);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureTwo() {
    StructureTwo *structure = new StructureTwo(dataDir);
    structure->show();
    structure->raise();
    structure->activateWindow();
}

void TaskChooser::showStructureThree() {
    StructureThree *structure = new StructureThree(dataDir);
    structure->show();
    structure->raise();
    structure->activateWindow();
}
