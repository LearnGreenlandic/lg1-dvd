#include "Lecture1Danish.hpp"
#include "Lecture2Danish.hpp"

#include "TaskChooser.hpp"
#include "UpdownOne.hpp"
#include "UpdownTwo.hpp"
#include "UpdownThree.hpp"

TaskChooser::TaskChooser(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dataDir(dataDir)
{
    setWindowTitle("Learn Greenlandic Demo");


    lectureOne = new QPushButton("Forelæsning 1: Introduktion");
    // lectureOne->setToolTip("Waffles"); // catch enter() event, call QToolTip::showText()
    lectureTwo = new QPushButton("Forelæsning 2: Typiske Danskerfejl");
    connect(lectureOne, SIGNAL(clicked()), this, SLOT(showLectureOne()));
    connect(lectureTwo, SIGNAL(clicked()), this, SLOT(showLectureTwo()));

    QVBoxLayout *lecVBox = new QVBoxLayout;
    lecVBox->addWidget(lectureOne);
    lecVBox->addWidget(lectureTwo);

    QGroupBox *lecGBox = new QGroupBox("Forelæsninger");
    lecGBox->setLayout(lecVBox);


    updownOne = new QPushButton("Up/Down: Reception");
    updownTwo = new QPushButton("Up/Down: Produktion");
    updownThree = new QPushButton("Up/Down: Oversættelse");
    connect(updownOne, SIGNAL(clicked()), this, SLOT(showUpdownOne()));
    connect(updownTwo, SIGNAL(clicked()), this, SLOT(showUpdownTwo()));
    connect(updownThree, SIGNAL(clicked()), this, SLOT(showUpdownThree()));

    QVBoxLayout *udVBox = new QVBoxLayout;
    udVBox->addWidget(updownOne);
    udVBox->addWidget(updownTwo);
    udVBox->addWidget(updownThree);

    QGroupBox *udGBox = new QGroupBox("Up/Down Øvelser");
    udGBox->setLayout(udVBox);


    QLabel *ql = new QLabel("Demo af diverse funktionaliteter som vil være i det færdige produkt.\n");
    ql->setWordWrap(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(ql);
    vbox->addWidget(lecGBox);
    vbox->addWidget(udGBox);

    setLayout(vbox);
}

void TaskChooser::showLectureOne() {
    Lecture1Danish *lecture = new Lecture1Danish(dataDir);
    lecture->show();
    lecture->raise();
    lecture->activateWindow();
}

void TaskChooser::showLectureTwo() {
    Lecture2Danish *lecture = new Lecture2Danish(dataDir);
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
