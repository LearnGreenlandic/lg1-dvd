#ifndef LISTENREPEATPLAYER_HPP
#define LISTENREPEATPLAYER_HPP

#include "CryptFile.hpp"
#include "TaskChooser.hpp"

#include <QAxWidget>
#include <QAxObject>
#include <QtGui>

class ListenRepeatPlayer : public QWidget {
    Q_OBJECT

public:
    ListenRepeatPlayer(QDir dataDir, TaskChooser& tc);

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

#endif // LISTENREPEATPLAYER_HPP
