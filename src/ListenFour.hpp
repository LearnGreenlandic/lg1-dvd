#ifndef LISTENFOUR_HPP
#define LISTENFOUR_HPP

#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class ListenFour : public QWidget {
    Q_OBJECT

public:
    ListenFour(TaskChooser& tc);

public slots:
    void showNext();
    void playAgain();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    QVector<QString> words;
    uint32_t curAt;

    QMediaPlayer *media;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // LISTENFOUR_HPP
