#include "DialogData.hpp"
#include <algorithm>
#include <stdint.h>

DialogData::DialogData(QDir dataDir, QString which){
    if (!dataDir.cd("./dialogue/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/dialogue/");
        throw(-1);
    }

    if (!dataDir.exists("greenlandic.txt") || !dataDir.exists(which)) {
        QMessageBox::critical(0, "Missing Data!", "Data files missing from lessons/dialogue/");
        throw(-1);
    }

    QFile fg(dataDir.absoluteFilePath("greenlandic.txt"));
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
            uint32_t w = ls.at(0).toULong()-1;
            phrases.resize(std::max(w+1, (uint32_t)phrases.size()));

            if (!dataDir.exists(ls.at(0) + " Q.wav")) {
                QMessageBox::critical(0, "Missing Data!", QString("Sound file '") + ls.at(0) + " Q.wav' missing from data folder.");
                throw(-1);
            }
            if (!dataDir.exists(ls.at(0) + " A.wav")) {
                QMessageBox::critical(0, "Missing Data!", QString("Sound file '") + ls.at(0) + " A.wav' missing from data folder.");
                throw(-1);
            }
            phrases[w].clear();
            phrases[w].push_back(dataDir.absoluteFilePath(ls.at(0) + " Q.wav"));
            phrases[w].push_back(dataDir.absoluteFilePath(ls.at(0) + " A.wav"));
            ls.pop_front();
            phrases[w] += ls;
        }
    }

    QFile fgw(dataDir.absoluteFilePath(which));
    fgw.open(QIODevice::ReadOnly);
    QTextStream tgw(&fgw);
    tgw.setCodec("UTF-8");

    while (!tgw.atEnd()) {
        QString tmp = tgw.readLine();
        if (tmp.isNull()) {
            break;
        }
        tmp = tmp.trimmed();
        if (!tmp.isEmpty() && tmp.at(0) != '#' && tmp.contains('\t')) {
            QStringList ls = tmp.split('\t');
            uint32_t w = ls.at(0).toULong()-1;
            ls.pop_front();
            phrases[w] += ls;
        }
    }

    if (phrases.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::random_shuffle(phrases.begin(), phrases.end());
}
