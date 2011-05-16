#ifndef PRONOUNCEDATA_HPP
#define PRONOUNCEDATA_HPP

#include <QtGui>

class PronounceData {
public:
    PronounceData(QDir dataDir);

    QDir dataDir;
    QMap<QString,QString> sounds;
    QVector<QString> words;
};

#endif // PRONOUNCEDATA_HPP
