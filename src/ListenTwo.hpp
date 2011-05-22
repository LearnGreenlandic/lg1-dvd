#ifndef LISTENTWO_HPP
#define LISTENTWO_HPP

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class ListenTwo : public QWidget {
    Q_OBJECT

public:
    ListenTwo(QDir dataDir);

public slots:
    void showNext();
    void playAgain();
    void checkNoR();
    void checkYesR();

private:
    QVector<QString> words;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QPushButton *noR;
    QPushButton *yesR;
};

#endif // LISTENTWO_HPP