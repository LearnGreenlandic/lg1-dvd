#ifndef HYPHENONE_HPP
#define HYPHENONE_HPP

#include "ScalingGraphicsView.hpp"
#include "TaskChooser.hpp"

#include <QtGui>
#include <stdint.h>

class HyphenOne : public QWidget {
    Q_OBJECT

public:
    HyphenOne(QDir dataDir, TaskChooser& tc);

public slots:
    void nextWord();
    void preventLoss(const QString& current);
    void checkInput();
    void yieldHyphen();

private:
    TaskChooser& tc;

    QString text, hyphenated, state;
    QLineEdit *input;
    QPushButton *yield;
    QLabel *result;
    QVector<QString> pngs;
    uint32_t curAt;
    QLabel *label;

    QGraphicsScene *scene;
    ScalingGraphicsView *view;
    QGraphicsPixmapItem *notes;
};

#endif // HYPHENONE_HPP
