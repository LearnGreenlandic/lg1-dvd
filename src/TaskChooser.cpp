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


    QGroupBox *lecGBox = new QGroupBox("Forelæsninger");
    QVBoxLayout *lecVBox = new QVBoxLayout;

    QLabel *ql = new QLabel("Demo af diverse funktionaliteter som vil være i det færdige produkt.\n");
    ql->setWordWrap(true);
    vbox->addWidget(ql);

    QPushButton *lectureOne = new QPushButton("Forelæsning 1: Introduktion");
    QPushButton *lectureTwo = new QPushButton("Forelæsning 2: Typiske Danskerfejl");
    connect(lectureOne, SIGNAL(clicked()), this, SLOT(showLectureOne()));
    connect(lectureTwo, SIGNAL(clicked()), this, SLOT(showLectureTwo()));

    lecVBox->addWidget(lectureOne);
    lecVBox->addWidget(lectureTwo);

    lecGBox->setLayout(lecVBox);
    vbox->addWidget(lecGBox);


    QGroupBox *udGBox = new QGroupBox("Up/Down Øvelser");
    QVBoxLayout *udVBox = new QVBoxLayout;

    QPushButton *updownOne = new QPushButton("Up/Down: Reception");
    QPushButton *updownTwo = new QPushButton("Up/Down: Produktion");
    QPushButton *updownThree = new QPushButton("Up/Down: Oversættelse");
    connect(updownOne, SIGNAL(clicked()), this, SLOT(showUpdownOne()));
    connect(updownTwo, SIGNAL(clicked()), this, SLOT(showUpdownTwo()));
    connect(updownThree, SIGNAL(clicked()), this, SLOT(showUpdownThree()));

    udVBox->addWidget(updownOne);
    udVBox->addWidget(updownTwo);
    udVBox->addWidget(updownThree);

    udGBox->setLayout(udVBox);
    vbox->addWidget(udGBox);


    QGroupBox *stGBox = new QGroupBox("Strukturøvelser");
    QVBoxLayout *stVBox = new QVBoxLayout;

    QPushButton *structureOne = new QPushButton("Struktur: Lydopfattelse");
    QPushButton *structureTwo = new QPushButton("Struktur: Dan nye ord");
    QPushButton *structureThree = new QPushButton("Struktur: Lyt, forstå, dan ord");
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
    LecturePlayer *lecture = new LecturePlayer("Forelæsning 1: Introduktion", dataDir, "./1/danish/");
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo() {
    LecturePlayer *lecture = new LecturePlayer("Forelæsning 2: Typiske Danskerfejl", dataDir, "./2/danish/");
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
