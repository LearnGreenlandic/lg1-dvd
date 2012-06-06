#ifndef UPDOWNTHREE_HPP
#define UPDOWNTHREE_HPP

#include "UpdownData.hpp"
#include "TaskChooser.hpp"

#include <QtGui>
#include <stdint.h>

class UpdownThree : public QWidget {
    Q_OBJECT

public:
    UpdownThree(TaskChooser& tc);

public slots:
    void showNext();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    UpdownData data;
    uint32_t curAt;

    QLabel *up;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // UPDOWNTHREE_HPP
