#ifndef XVIDTEST_HPP
#define XVIDTEST_HPP

#include <QtGui>

class XVidTest : public QDialog {
    Q_OBJECT

public:
    XVidTest(QWidget *parent, QDir dataDir);

public slots:
    void finished();

};

#endif // XVIDTEST_HPP
