#ifndef STRUCTURETWO_HPP
#define STRUCTURETWO_HPP

#include "StructureData.hpp"
#include "TaskChooser.hpp"

#include <QtGui>
#include <stdint.h>

class StructureTwo : public QWidget {
    Q_OBJECT

public:
    StructureTwo(const QString& which, const QString& title, TaskChooser& tc);

public slots:
    void showNext();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    StructureData data;
    uint32_t curAt;

    QLabel *query;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTURETWO_HPP
