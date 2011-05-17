#ifndef WELCOMEONE_HPP
#define WELCOMEONE_HPP

#include <QtGui>

class WelcomeOne : public QWidget {
    Q_OBJECT

public:
    WelcomeOne(QDir dataDir);

public slots:
    void preventLoss();
    void checkInput();
    void yieldHyphen();

private:
    QString text, hyphenated, state;
    QTextEdit *input;
    QPushButton *yield;
    QLabel *result;
};

#endif // WELCOMEONE_HPP
