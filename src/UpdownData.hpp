#ifndef UPDOWNDATA_HPP
#define UPDOWNDATA_HPP

#include <QtGui>

class UpdownData
{
public:
    UpdownData(QDir dataDir);

    QMap<QString,QString> updowns;
    QMap<QString,QString> glosses;
};

#endif // UPDOWNDATA_HPP
