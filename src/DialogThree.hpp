#ifndef DIALOGTHREE_HPP
#define DIALOGTHREE_HPP

#include "DialogData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class DialogThree : public QWidget {
    Q_OBJECT

public:
    DialogThree(TaskChooser& tc);

public slots:
    void playAgainQ();
    void playAgainA();
    void showNext();

private:
    TaskChooser& tc;

    DialogData data;
    uint32_t curAt;

    QLabel *labelQ;
    QMediaPlayer *mediaQ;
    QLabel *labelA;
    QMediaPlayer *mediaA;
};

#endif // DIALOGTHREE_HPP
