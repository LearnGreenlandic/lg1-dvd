#ifndef TASKCHOOSER_HPP
#define TASKCHOOSER_HPP

#include <QtGui>

class TaskChooser : public QWidget {
    Q_OBJECT

public:
    TaskChooser(QDir dataDir, QTranslator *translator);

public slots:
    void showLectureOne();
    void showLectureTwo();
    void showLectureThree();
    void showLectureFour();
    void showLectureFiveOne();
    void showLectureFiveTwo();

    void showLectureOnePDF();
    void showLectureTwoPDF();
    void showLectureThreePDF();
    void showLectureFourPDF();
    void showLectureFivePDF();

    void showHyphenOne();

    void showDialogOne();
    void showDialogTwo();
    void showDialogThree();

    void showListenOne();
    void showListenTwo();
    void showListenThree();
    void showListenFour();

    void showWelcomePlayer();
    void showWelcomeOne();
    void showWelcomeTwo();

    void showListenRepeatPlayer();

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

    void toggleLanguage();

    void checkFirstRun();

private:
    QDir dataDir;
    QTranslator *translator;
};

#endif // TASKCHOOSER_HPP
