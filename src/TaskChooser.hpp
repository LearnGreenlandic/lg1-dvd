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
    void showLectureThree();
    void showLectureFour();
    void showLectureFiveOne();
    void showLectureFiveTwo();

    void showLectureOne_Eng();
    void showLectureTwo_Eng();
    void showLectureThree_Eng();
    void showLectureFour_Eng();
    void showLectureFiveOne_Eng();
    void showLectureFiveTwo_Eng();

    void showUpdownOne();
    void showUpdownTwo();
    void showUpdownThree();

    void showStructureOne();
    void showStructureTwo();
    void showStructureThree();

private:
    QDir dataDir;
};

#endif // TASKCHOOSER_HPP
