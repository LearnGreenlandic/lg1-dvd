#ifndef PRONOUNCEONE_HPP
#define PRONOUNCEONE_HPP

#include "PronounceData.hpp"
#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class PronounceOne : public QWidget{
    Q_OBJECT

public:
    PronounceOne(TaskChooser& tc);

public slots:
    void showNext();
    void playAgain();

private:
    TaskChooser& tc;

    PronounceData data;
    uint32_t curAt;

    QMediaPlayer *media;
    QLabel *text;
};

#endif // PRONOUNCEONE_HPP
