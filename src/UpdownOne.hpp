#ifndef UPDOWNONE_HPP
#define UPDOWNONE_HPP

#include <QtGui>

class UpdownOne : public QWidget {
    Q_OBJECT

public:
    UpdownOne(QDir dataDir);

public slots:

private:
    QDir dataDir;
};

#endif // UPDOWNONE_HPP
