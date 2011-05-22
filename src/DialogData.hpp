#ifndef DIALOGDATA_HPP
#define DIALOGDATA_HPP

#include <QtGui>

class DialogData
{
public:
    DialogData(QDir dataDir, QString which);

    QVector<QStringList> phrases;
};

#endif // DIALOGDATA_HPP
