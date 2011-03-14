#ifndef UPDOWNDATA_HPP
#define UPDOWNDATA_HPP

#include <QtGui>

class UpdownData
{
public:
    UpdownData(QDir dataDir);

    QString glossUpper(QString upper);

    QVector< QPair<QString,QString> > updowns;
    QMap<QString,QString> glosses;
};

#endif // UPDOWNDATA_HPP
