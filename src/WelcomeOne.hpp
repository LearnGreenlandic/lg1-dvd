#ifndef WELCOMEONE_HPP
#define WELCOMEONE_HPP

#include "TaskChooser.hpp"

#include <QtGui>

class WelcomeOne : public QWidget {
    Q_OBJECT

public:
    WelcomeOne(QDir dataDir, TaskChooser& tc);

public slots:
    void preventLoss();
    void checkInput();
    void yieldHyphen();

private:
    TaskChooser& tc;

    QString text, hyphenated, state;
    QTextEdit *input;
    QPushButton *yield;
    QLabel *result;
};

#endif // WELCOMEONE_HPP
