#ifndef PRONOUNCETWO_HPP
#define PRONOUNCETWO_HPP

#include "PronounceData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class PronounceTwo : public QWidget {
    Q_OBJECT

public:
    PronounceTwo(TaskChooser& tc);

public slots:
    void showNext();
    void playAgain();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    PronounceData data;
    uint32_t curAt;

    QMediaPlayer *media;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // PRONOUNCETWO_HPP
