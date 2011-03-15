#ifndef STRUCTUREDATA_HPP
#define STRUCTUREDATA_HPP

#include <QtGui>

class StructureData {
public:
    StructureData(QDir dataDir);

    QDir dataDir;
    QVector<QStringList> pairs;
};

#endif // STRUCTUREDATA_HPP
