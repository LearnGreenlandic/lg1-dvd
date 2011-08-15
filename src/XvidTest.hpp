#ifndef XVIDTEST_HPP
#define XVIDTEST_HPP

#include <QAxWidget>
#include <QAxObject>
#include <QtGui>

class XvidTest : public QDialog {
    Q_OBJECT

public:
    XvidTest(QDir dataDir);

    void closeEvent(QCloseEvent *event);

public slots:
    void finished();

private:
    QAxWidget *video;
    QAxObject *controls;
};

#endif // XVIDTEST_HPP
