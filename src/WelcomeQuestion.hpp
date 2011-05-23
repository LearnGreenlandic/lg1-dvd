#ifndef WELCOMEQUESTION_HPP
#define WELCOMEQUESTION_HPP

#include "TaskChooser.hpp"
#include <QtGui>

class WelcomeQuestion : public QWidget {
    Q_OBJECT

public:
    WelcomeQuestion(QWidget *parent, TaskChooser& tc);

public slots:
    void checkInput(const QString&);
    void whoops();

private:
    TaskChooser& tc;
};

#endif // WELCOMEQUESTION_HPP
