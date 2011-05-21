#ifndef STRUCTURETHREE_HPP
#define STRUCTURETHREE_HPP

#include "StructureData.hpp"
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class StructureThree : public QWidget {
    Q_OBJECT

public:
    StructureThree(QDir dataDir, QString which, QString title);

public slots:
    void show();
    void showNext();
    void playAgain();
    void playCorrectAgain();
    void checkInput();
    void yieldWord();

private:
    StructureData data;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    Phonon::MediaObject *cmedia;
    Phonon::AudioOutput *caudio;
    QLabel *query;
    QLabel *result;
    QLineEdit *input;
    QPushButton *cagain;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTURETHREE_HPP
