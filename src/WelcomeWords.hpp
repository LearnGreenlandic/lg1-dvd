#ifndef WELCOMEWORDS_H
#define WELCOMEWORDS_H

#include "CryptFile.hpp"
#include "TaskChooser.hpp"
#include <QtGui>
#include <stdint.h>

#if defined(Q_OS_WIN)

#include <QAxWidget>
#include <QAxObject>

class WelcomeWords : public QWidget {
    Q_OBJECT

public:
    WelcomeWords(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void showNext();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    QStringList words;
    uint32_t curAt;

    QAxWidget *video;
    QAxObject *controls;
    QString tmpfile;

    QLabel *sum;
    QLabel *query;
    QLineEdit *input;
    QLabel *result;
    QPushButton *yield;
};

#else

#include <QtMultimedia>
#include <QVideoWidget>

class WelcomeWords : public QWidget {
    Q_OBJECT

public:
    WelcomeWords(TaskChooser& tc);

    void closeEvent(QCloseEvent *event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void show();
    void tick(qint64 time);
    void togglePlay();
    void showNext();
    void checkInput();
    void yieldWord();

private:
    TaskChooser& tc;

    QStringList words;
    uint32_t curAt;

    QMediaPlayer *media;
    QVideoWidget *video;

    QPushButton *playpause;
    //QMediaPlayer::SeekSlider *seeker;
    QLCDNumber *timeLcd;
    QString tmpfile;

    QLabel *sum;
    QLabel *query;
    QLineEdit *input;
    QLabel *result;
    QPushButton *yield;
};

#endif

#endif // WELCOMEWORDS_H
