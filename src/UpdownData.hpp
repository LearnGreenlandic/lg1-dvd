#ifndef UPDOWNDATA_HPP
#define UPDOWNDATA_HPP

#include "common.hpp"
#include <QtWidgets>

class UpdownData
{
public:
    UpdownData(const dirmap_t& dirs);

    QString glossUpperDetailed(const QString& upper);
    QString glossUpperShort(const QString& upper);

    QVector< QPair<QString,QString> > updowns;
    QMap<QString,QString> glosses;
};

#endif // UPDOWNDATA_HPP
