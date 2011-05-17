#ifndef LECTUREPLAYER_H
#define LECTUREPLAYER_H

#include "ScalingGraphicsView.hpp"
#include "CryptFile.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>
#include <phonon/effect.h>
#include <QtGui>
#include <stdint.h>

class LecturePlayer : public QWidget {
    Q_OBJECT

public:
    LecturePlayer(QString title, QDir dataDir, QString lecDir);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();

private:
    typedef QMap<uint32_t, QString> slides_t;
    slides_t slides;
    QString curSlide;

    QGraphicsScene *scene;
    ScalingGraphicsView *view;
    QGraphicsPixmapItem *slide;

    CryptFile *mediafile;
    Phonon::MediaObject *media;
    Phonon::VideoWidget *video;
    Phonon::AudioOutput *audio;

    QPushButton *playpause;
    Phonon::SeekSlider *seeker;
    QLCDNumber *timeLcd;
};

#endif // LECTUREPLAYER_H
