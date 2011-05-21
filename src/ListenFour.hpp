#ifndef LISTENFOUR_HPP
#define LISTENFOUR_HPP

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class ListenFour : public QWidget {
    Q_OBJECT

public:
    ListenFour(QDir dataDir);

public slots:
    void showNext();
    void playAgain();
    void checkInput();
    void yieldWord();

private:
    QVector<QString> words;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QLineEdit *input;
    QPushButton *check;
    QPushButton *yield;
};

#endif // LISTENFOUR_HPP
