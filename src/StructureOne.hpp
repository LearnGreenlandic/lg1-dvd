#ifndef STRUCTUREONE_HPP
#define STRUCTUREONE_HPP

#include "StructureData.hpp"
#include "TaskChooser.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class StructureOne : public QWidget {
    Q_OBJECT

public:
    StructureOne(QString which, QString title, TaskChooser& tc);

public slots:
    void show();
    void showNext();
    void playAgain();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    StructureData data;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTUREONE_HPP
