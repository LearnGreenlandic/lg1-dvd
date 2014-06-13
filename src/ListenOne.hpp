#ifndef LISTENONE_HPP
#define LISTENONE_HPP

#include "TaskChooser.hpp"

#include <QtMultimedia>
#include <QtGui>
#include <stdint.h>

class ListenOne : public QWidget {
    Q_OBJECT

public:
    ListenOne(TaskChooser& tc);

public slots:
    void showNext();
    void playAgain();
    void oneConsonant();
    void twoConsonants();

private:
    TaskChooser& tc;

    QVector< QPair<QString,QString> > words;
    uint32_t curAt;

    QMediaPlayer *media;
    QLabel *result;
    QPushButton *oneC;
    QPushButton *twoC;
};

#endif // LISTENONE_HPP
