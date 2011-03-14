#include "UpdownData.hpp"

UpdownData::UpdownData(QDir dataDir)
{
    if (!dataDir.cd("./updown/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/updown/!");
        throw(-1);
    }

    if (!dataDir.exists("gloss.txt") || !dataDir.exists("updown.txt")) {
        QMessageBox::critical(0, "Missing Data!", "Data files missing from lessons/updown/!");
        throw(-1);
    }

    QString tmp;

    QFile fg(dataDir.absoluteFilePath("gloss.txt"));
    fg.open(QIODevice::ReadOnly);
    QTextStream tg(&fg);
    tg.setCodec("UTF-8");

    while (!tg.atEnd()) {
        tmp = tg.readLine();
        if (tmp.isNull()) {
            break;
        }
        tmp = tmp.trimmed();
        if (!tmp.isEmpty() && tmp.at(0) != '#' && tmp.contains('\t')) {
            QStringList ls = tmp.split('\t');
            if (ls.size() == 2) {
                QString a = ls.at(0).trimmed();
                QString b = ls.at(1).trimmed();
                glosses[a] = b;
            }
        }
    }

    QFile fu(dataDir.absoluteFilePath("updown.txt"));
    fu.open(QIODevice::ReadOnly);
    QTextStream tu(&fu);
    tu.setCodec("UTF-8");

    while (!tu.atEnd()) {
        tmp = tu.readLine();
        if (tmp.isNull()) {
            break;
        }
        tmp = tmp.trimmed();
        if (!tmp.isEmpty() && tmp.at(0) != '#' && tmp.contains('\t')) {
            QStringList ls = tmp.split('\t');
            if (ls.size() == 2) {
                QString a = ls.at(0).trimmed();
                QString b = ls.at(1).trimmed();
                updowns[a] = b;
            }
        }
    }

    if (glosses.empty() || updowns.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }
}
