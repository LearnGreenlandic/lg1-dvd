#ifndef WELCOMEPLAYER_H
#define WELCOMEPLAYER_H

#include "CryptFile.hpp"
#include "TaskChooser.hpp"

#include <QAxWidget>
#include <QAxObject>
#include <QtGui>

class WelcomePlayer : public QWidget {
    Q_OBJECT

public:
    WelcomePlayer(QDir dataDir, TaskChooser& tc);

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

#endif // WELCOMEPLAYER_H
