#ifndef TASKCHOOSER_HPP
#define TASKCHOOSER_HPP

#include <QtGui>
#include <QWidget>

class TaskChooser : public QWidget {
    Q_OBJECT

public:
    TaskChooser(QDir dataDir);

public slots:
    void showLectureOne();
    void showLectureTwo();
    void showUpdownOne();
    void showUpdownTwo();
    void showUpdownThree();

private:
    QDir dataDir;

    QPushButton *lectureOne;
    QPushButton *lectureTwo;

    QPushButton *updownOne;
    QPushButton *updownTwo;
    QPushButton *updownThree;
};

#endif // TASKCHOOSER_HPP
