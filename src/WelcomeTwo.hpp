#ifndef WELCOMETWO_HPP
#define WELCOMETWO_HPP

#include "ScalingGraphicsView.hpp"
#include "TaskChooser.hpp"

#include <QtGui>
#include <stdint.h>

class WelcomeTwo : public QWidget {
    Q_OBJECT

public:
    WelcomeTwo(TaskChooser& tc);

public slots:
    void nextWord();

private:
    TaskChooser& tc;

    QString text;
    QStringList pngs;
    uint32_t curAt;
    QLabel *label;

    QGraphicsScene *scene;
    ScalingGraphicsView *view;
    QGraphicsPixmapItem *notes;
};

#endif // WELCOMETWO_HPP
