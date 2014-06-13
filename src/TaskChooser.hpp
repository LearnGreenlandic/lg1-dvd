#ifndef TASKCHOOSER_HPP
#define TASKCHOOSER_HPP

#include "common.hpp"
#include <QtWidgets>
#include <QtGui>

class TaskChooser : public QWidget {
    Q_OBJECT

public:
    TaskChooser(const dirmap_t& dirs, QTranslator *translator);

    QDir dataDir;
    dirmap_t dirs;

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

    void showGrammaticaPDF();

    void showPamphletPDF();

    void showHyphenOne();

    void showDialogOne();
    void showDialogTwo();
    void showDialogThree();

    void showListenOne();
    void showListenTwo();
    void showListenThree();
    void showListenFour();

    void showWelcomePlayer();
    void showWelcomeWords();
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
    QTranslator *translator;
};

#endif // TASKCHOOSER_HPP
