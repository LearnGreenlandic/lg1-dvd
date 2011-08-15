#ifndef WELCOMEWORDS_H
#define WELCOMEWORDS_H

#include "CryptFile.hpp"
#include "TaskChooser.hpp"

#include <QAxWidget>
#include <QAxObject>
#include <QtGui>
#include <stdint.h>

class WelcomeWords : public QWidget {
    Q_OBJECT

public:
    WelcomeWords(QDir dataDir, TaskChooser& tc);

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

#endif // WELCOMEWORDS_H
