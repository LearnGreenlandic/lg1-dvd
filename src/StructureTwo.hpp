#ifndef STRUCTURETWO_HPP
#define STRUCTURETWO_HPP

#include "StructureData.hpp"
#include <QtGui>
#include <stdint.h>

class StructureTwo : public QWidget {
    Q_OBJECT

public:
    StructureTwo(QDir dataDir, QString which, QString title);

public slots:
    void showNext();
    void checkInput();
    void yieldWord();

private:
    StructureData data;
    uint32_t curAt;

    QLabel *query;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // STRUCTURETWO_HPP
