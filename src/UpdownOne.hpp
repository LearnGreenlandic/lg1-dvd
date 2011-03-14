#ifndef UPDOWNONE_HPP
#define UPDOWNONE_HPP

#include "UpdownData.hpp"
#include <QtGui>

class UpdownOne : public QWidget {
    Q_OBJECT

public:
    UpdownOne(QDir dataDir);

public slots:

private:
    UpdownData data;
};

#endif // UPDOWNONE_HPP
