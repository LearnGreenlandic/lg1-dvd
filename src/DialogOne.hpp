#ifndef DIALOGONE_HPP
#define DIALOGONE_HPP

#include "DialogData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class DialogOne : public QWidget {
    Q_OBJECT

public:
    DialogOne(TaskChooser& tc);

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

#endif // DIALOGONE_HPP
