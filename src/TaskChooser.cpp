#include "Lecture1Danish.hpp"
#include "Lecture2Danish.hpp"

#include "TaskChooser.hpp"

TaskChooser::TaskChooser(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
dataDir(dataDir)
{
    setWindowTitle("Learn Greenlandic Demo");

    lectureOne = new QPushButton("Forelæsning 1: Introduktion");
    lectureTwo = new QPushButton("Forelæsning 2: Typiske Danskerfejl");

    QVBoxLayout *qvbl = new QVBoxLayout(this);
    qvbl->addWidget(lectureOne);
    qvbl->addWidget(lectureTwo);

    connect(lectureOne, SIGNAL(clicked()), this, SLOT(showLectureOne()));
    connect(lectureTwo, SIGNAL(clicked()), this, SLOT(showLectureTwo()));

    setLayout(qvbl);
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
