#ifndef XVIDTEST_HPP
#define XVIDTEST_HPP

#include <QtGui>

class XvidTest : public QDialog {
    Q_OBJECT

public:
    XvidTest(QWidget *parent, QDir dataDir);

public slots:
    void finished();

};

#endif // XVIDTEST_HPP
