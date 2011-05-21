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

    void showHyphenOne();

    void showListenOne();
    void showListenTwo();
    void showListenThree();

    void showWelcomeOne();
    void showWelcomeTwo();

    void showPronounceOne();
    void showPronounceTwo();

    void showUpdownOne();
    void showUpdownTwo();
    void showUpdownThree();

    void showStructureOne();
    void showStructureTwo();
    void showStructureThree();
    void showStructureFour();
    void showStructureFive();
    void showStructureSix();
    void showStructureSeven();

private:
    QDir dataDir;
};

#endif // TASKCHOOSER_HPP
