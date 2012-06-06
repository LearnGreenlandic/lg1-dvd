#ifndef STRUCTUREDATA_HPP
#define STRUCTUREDATA_HPP

#include "common.hpp"
#include <QtGui>

class StructureData {
public:
    StructureData(const dirmap_t& dirs, QString which);

    QDir dataDir;
    QString which;
    QVector<QStringList> pairs;
};

#endif // STRUCTUREDATA_HPP
