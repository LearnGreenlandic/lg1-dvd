#ifndef LECTURE1DANISH_H
#define LECTURE1DANISH_H

#include "ScalingGraphicsView.hpp"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>
#include <phonon/effect.h>
#include <QtGui>
#include <QtOpenGL/QGLWidget>
#include <stdint.h>

class Lecture1Danish : public QWidget {
    Q_OBJECT

public:
    Lecture1Danish(QDir dataDir);
    ~Lecture1Danish();

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();

private:
    QDir dataDir;
    typedef QMap<uint32_t, QString> slides_t;
    slides_t slides;
    QString curSlide;

    QGraphicsScene *scene;
    ScalingGraphicsView *view;
    QGraphicsPixmapItem *slide;

    Phonon::MediaObject *media;
    Phonon::VideoWidget *video;
    Phonon::AudioOutput *audio;

    QPushButton *playpause;
    Phonon::SeekSlider *seeker;
    QLCDNumber *timeLcd;
};

#endif // LECTURE1DANISH_H
