#ifndef XVIDTEST_HPP
#define XVIDTEST_HPP

#include <QtWidgets>

#if defined(Q_OS_WIN)

#include <QAxWidget>
#include <QAxObject>

class XvidTest : public QDialog {
    Q_OBJECT

public:
    XvidTest(const QString& avi);

    void closeEvent(QCloseEvent *event);

public slots:
    void finished();

private:
    QAxWidget *video;
    QAxObject *controls;
};

#else

#include <QtMultimedia>
#include <QVideoWidget>

class XvidTest : public QDialog {
    Q_OBJECT

public:
    XvidTest(QString avi);

    void closeEvent(QCloseEvent *event);

public slots:
    void finished();

private:
    QMediaPlayer *media;
    QVideoWidget *video;
};

#endif

#endif // XVIDTEST_HPP
