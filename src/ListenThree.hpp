#ifndef LISTENTHREE_HPP
#define LISTENTHREE_HPP

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class ListenThree : public QWidget {
    Q_OBJECT

public:
    ListenThree(QDir dataDir);

public slots:
    void showNext();
    void playAgain();
    void checkTT();
    void checkTS();
    void checkT();

private:
    QVector<QString> words;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QPushButton *yesTT;
    QPushButton *yesTS;
    QPushButton *yesT;
};

#endif // LISTENTHREE_HPP