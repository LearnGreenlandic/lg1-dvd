#ifndef DIALOGDATA_HPP
#define DIALOGDATA_HPP

#include "common.hpp"
#include <QtWidgets>

class DialogData
{
public:
    DialogData(const dirmap_t& dirs, QString which);

    QVector<QStringList> phrases;
};

#endif // DIALOGDATA_HPP
