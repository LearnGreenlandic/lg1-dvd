#ifndef PRONOUNCEDATA_HPP
#define PRONOUNCEDATA_HPP

#include "common.hpp"
#include <QtGui>

class PronounceData {
public:
    PronounceData(const dirmap_t& dirs);

    QMap<QString,QString> sounds;
    QVector<QString> words;
};

#endif // PRONOUNCEDATA_HPP
