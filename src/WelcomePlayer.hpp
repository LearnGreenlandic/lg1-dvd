#ifndef WELCOMEPLAYER_H
#define WELCOMEPLAYER_H

#include "CryptFile.hpp"
#include "TaskChooser.hpp"
#include <QtGui>

#if defined(Q_OS_WIN)

#include <QAxWidget>
#include <QAxObject>

class WelcomePlayer : public QWidget {
    Q_OBJECT

public:
    WelcomePlayer(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void finished(int);

private:
    TaskChooser& tc;

    QAxWidget *video;
    QAxObject *controls;
    QString tmpfile;
};

#else

#include <QtMultimedia>
#include <QVideoWidget>

class WelcomePlayer : public QWidget {
    Q_OBJECT

public:
    WelcomePlayer(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void finished();
    void togglePlay();

private:
    TaskChooser& tc;

    QMediaPlayer *media;
    QVideoWidget *video;

    QPushButton *playpause;
    //QMediaPlayer::SeekSlider *seeker;
    QLCDNumber *timeLcd;
    QString tmpfile;
};

#endif

#endif // WELCOMEPLAYER_H
