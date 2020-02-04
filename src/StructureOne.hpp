#ifndef STRUCTUREONE_HPP
#define STRUCTUREONE_HPP

#include "StructureData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class StructureOne : public QWidget {
    Q_OBJECT

public:
    StructureOne(const QString& which, const QString& title, TaskChooser& tc);

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

    QMediaPlayer *media;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTUREONE_HPP
