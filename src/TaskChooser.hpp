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

private:
    QDir dataDir;

    QPushButton *lectureOne;
    QPushButton *lectureTwo;
};

#endif // TASKCHOOSER_HPP
