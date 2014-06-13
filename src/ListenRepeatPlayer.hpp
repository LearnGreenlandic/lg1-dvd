#ifndef LISTENREPEATPLAYER_HPP
#define LISTENREPEATPLAYER_HPP

#include "CryptFile.hpp"
#include "TaskChooser.hpp"
#include <QtGui>

#if defined(Q_OS_WIN)

#include <QAxWidget>
#include <QAxObject>

class ListenRepeatPlayer : public QWidget {
    Q_OBJECT

public:
    ListenRepeatPlayer(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void playStateChange(int);
    void playPerAgain();
    void playTikaAgain();

private:
    TaskChooser& tc;

    QDir dataDir;

    QAxWidget *video;
    QAxObject *controls;
    QString tmpfile_per, tmpfile_tik;
    QString current;
};

#else

#include <QtMultimedia>
#include <QVideoWidget>

class ListenRepeatPlayer : public QWidget {
    Q_OBJECT

public:
    ListenRepeatPlayer(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();
    void playPerAgain();
    void playTikaAgain();

private:
    TaskChooser& tc;

    QDir dataDir;

    QMediaPlaylist playlist;
    QMediaPlayer *media;
    QVideoWidget *video;

    QPushButton *playpause;
    //QMediaPlayer::SeekSlider *seeker;
    QLCDNumber *timeLcd;
    QString tmpfile_per, tmpfile_tik;
};

#endif

#endif // LISTENREPEATPLAYER_HPP
