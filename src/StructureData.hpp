#ifndef STRUCTUREDATA_HPP
#define STRUCTUREDATA_HPP

#include <QtGui>

class StructureData {
public:
    StructureData(QDir dataDir, QString which);

    QDir dataDir;
    QString which;
    QVector<QStringList> pairs;
};

#endif // STRUCTUREDATA_HPP
