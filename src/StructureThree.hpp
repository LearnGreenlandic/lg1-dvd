#ifndef STRUCTURETHREE_HPP
#define STRUCTURETHREE_HPP

#include "StructureData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class StructureThree : public QWidget {
    Q_OBJECT

public:
    StructureThree(QString which, QString title, TaskChooser& tc);

public slots:
    void show();
    void showNext();
    void playAgain();
    void playCorrectAgain();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    StructureData data;
    uint32_t curAt;

    QMediaPlayer *media;
    QMediaPlayer *cmedia;
    QLabel *query;
    QLabel *result;
    QLineEdit *input;
    QPushButton *cagain;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTURETHREE_HPP
