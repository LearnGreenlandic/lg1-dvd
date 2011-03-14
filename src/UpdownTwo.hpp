#ifndef UPDOWNTWO_HPP
#define UPDOWNTWO_HPP

#include "UpdownData.hpp"
#include <QtGui>
#include <stdint.h>

class UpdownTwo : public QWidget {
    Q_OBJECT

public:
    UpdownTwo(QDir dataDir);

public slots:
    void showNext();
    void checkInput();
    void yieldWord();

private:
    UpdownData data;
    uint32_t curAt;

    QVBoxLayout *curWord;
    QLabel *up;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // UPDOWNTWO_HPP
