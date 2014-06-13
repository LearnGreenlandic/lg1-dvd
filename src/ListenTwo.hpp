#ifndef LISTENTWO_HPP
#define LISTENTWO_HPP

#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class ListenTwo : public QWidget {
    Q_OBJECT

public:
    ListenTwo(TaskChooser& tc);

public slots:
    void showNext();
    void playAgain();
    void checkNoR();
    void checkYesR();

private:
    TaskChooser& tc;

    QVector<QString> words;
    uint32_t curAt;

    QMediaPlayer *media;
    QLabel *result;
    QPushButton *noR;
    QPushButton *yesR;
};

#endif // LISTENTWO_HPP
