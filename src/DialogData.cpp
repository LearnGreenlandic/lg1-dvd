#include "DialogData.hpp"
#include <algorithm>
#include <random>
#include <cstdint>

DialogData::DialogData(const dirmap_t& dirs, const QString& which){
    QString f_kal = find_newest(dirs, "./dialogue/greenlandic.txt");
    if (f_kal.isEmpty()) {
        QMessageBox::critical(nullptr, "Missing Data!", "Could not find ./dialogue/greenlandic.txt");
        throw(-1);
    }

    QString f_which = find_newest(dirs, QString("./dialogue/") + which);
    if (f_which.isEmpty()) {
        QMessageBox::critical(nullptr, "Missing Data!", QString("Could not find ./dialogue/") + which);
        throw(-1);
    }

    QFile fg(f_kal);
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
            phrases.resize(std::max(w+1, static_cast<uint32_t>(phrases.size())));

            QString f_q = find_newest(dirs, QString("./dialogue/") + ls.at(0) + " Q.wav");
            if (f_q.isEmpty()) {
                QMessageBox::critical(nullptr, "Missing Data!", QString("Sound file '") + ls.at(0) + " Q.wav' missing from data folder.");
                throw(-1);
            }
            QString f_a = find_newest(dirs, QString("./dialogue/") + ls.at(0) + " A.wav");
            if (f_a.isEmpty()) {
                QMessageBox::critical(nullptr, "Missing Data!", QString("Sound file '") + ls.at(0) + " A.wav' missing from data folder.");
                throw(-1);
            }
            phrases[w].clear();
            phrases[w].push_back(f_q);
            phrases[w].push_back(f_a);
            ls.pop_front();
            phrases[w] += ls;
        }
    }

    QFile fgw(f_which);
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
        QMessageBox::critical(nullptr, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::shuffle(phrases.begin(), phrases.end(), std::mt19937(std::random_device()()));
}
