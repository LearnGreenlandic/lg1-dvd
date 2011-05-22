#ifndef LISTENONE_HPP
#define LISTENONE_HPP

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <QtGui>
#include <stdint.h>

class ListenOne : public QWidget {
    Q_OBJECT

public:
    ListenOne(QDir dataDir);

public slots:
    void showNext();
    void playAgain();
    void oneConsonant();
    void twoConsonants();

private:
    QVector< QPair<QString,QString> > words;
    uint32_t curAt;

    Phonon::MediaObject *media;
    Phonon::AudioOutput *audio;
    QLabel *result;
    QPushButton *oneC;
    QPushButton *twoC;
};

#endif // LISTENONE_HPP