#ifndef DIALOGTWO_HPP
#define DIALOGTWO_HPP

#include "DialogData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class DialogTwo : public QWidget {
    Q_OBJECT

public:
    DialogTwo(TaskChooser& tc);

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

#endif // DIALOGTWO_HPP
