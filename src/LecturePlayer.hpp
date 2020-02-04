#ifndef LECTUREPLAYER_H
#define LECTUREPLAYER_H

#include "ScalingGraphicsView.hpp"
#include "CryptFile.hpp"
#include "TaskChooser.hpp"
#include <QtGui>
#include <stdint.h>

#if defined(Q_OS_WIN)

#include <QAxWidget>
#include <QAxObject>

class LecturePlayer : public QWidget {
    Q_OBJECT

public:
    LecturePlayer(TaskChooser& tc, const QString& lecDir, const QString& title);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick();

private:
    TaskChooser& tc;

    typedef QMap<uint32_t, QString> slides_t;
    slides_t slides;
    QString curSlide;

    QGraphicsScene *scene;
    ScalingGraphicsView *view;
    QGraphicsPixmapItem *slide;

    QAxWidget *video;
    QAxObject *controls;
    QString tmpfile;
};

#else

#include <QtMultimedia>
#include <QVideoWidget>

class LecturePlayer : public QWidget {
    Q_OBJECT

public:
    LecturePlayer(TaskChooser& tc, QString lecDir, QString title);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();

private:
    TaskChooser& tc;

    typedef QMap<uint32_t, QString> slides_t;
    slides_t slides;
    QString curSlide;

    QGraphicsScene *scene;
    ScalingGraphicsView *view;
    QGraphicsPixmapItem *slide;

    QMediaPlayer *media;
    QVideoWidget *video;

    QPushButton *playpause;
    //QMediaPlayer::SeekSlider *seeker;
    QLCDNumber *timeLcd;
    QString tmpfile;
};

#endif // Q_OS_WIN
#endif // LECTUREPLAYER_H
