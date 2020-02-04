#include "StructureData.hpp"
#include <algorithm>
#include <random>
#include <cstdint>

StructureData::StructureData(const dirmap_t& dirs, const QString& which):
which(which)
{
    QString f_d = find_newest(dirs, QString("./structure/") + which + "pairs.txt");
    dataDir = QDir(f_d.replace("pairs.txt", ""));
    if (!dataDir.exists()) {
        QMessageBox::critical(nullptr, "Missing Data Folder!", QString("Could not change working folder to lessons/structure/") + which);
        throw(-1);
    }

    if (!dataDir.exists("pairs.txt")) {
        QMessageBox::critical(nullptr, "Missing Data!", "Data files missing from lessons/structure/");
        throw(-1);
    }

    QFile fg(dataDir.absoluteFilePath("pairs.txt"));
    fg.open(QIODevice::ReadOnly);
    QTextStream tg(&fg);
    tg.setCodec("UTF-8");

    while (!tg.atEnd()) {
        QString tmp = tg.readLine();
        if (tmp.isNull()) {
            break;
        }
        tmp = tmp.trimmed();
        if (!tmp.isEmpty() && tmp.at(0) != '#' && tmp.contains('\t')) {
            QStringList ls = tmp.split('\t');
            if (!dataDir.exists(ls.at(0) + ".wav")) {
                QMessageBox::critical(nullptr, "Missing Data!", QString("Sound file ") + ls.at(0) + ".wav missing from data folder.");
                throw(-1);
            }
            if (!dataDir.exists(ls.at(1) + ".wav")) {
                QMessageBox::critical(nullptr, "Missing Data!", QString("Sound file ") + ls.at(1) + ".wav missing from data folder.");
                throw(-1);
            }
            pairs.push_back(ls);
        }
    }

    if (pairs.empty()) {
        QMessageBox::critical(nullptr, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::shuffle(pairs.begin(), pairs.end(), std::mt19937(std::random_device()()));
}
