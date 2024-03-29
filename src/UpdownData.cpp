#include "UpdownData.hpp"
#include <algorithm>
#include <random>
#include <cstdint>

UpdownData::UpdownData(const dirmap_t& dirs)
{
    QString f_d = find_newest(dirs, "./updown/updown.txt");
    QDir dataDir(f_d.replace("updown.txt", ""));
    if (!dataDir.exists()) {
        QMessageBox::critical(nullptr, "Missing Data Folder!", "Could not change working folder to lessons/updown/");
        throw(-1);
    }

    QSettings settings;
    QString lang = settings.value("language").toString();

    if (!dataDir.exists(lang + "_gloss.txt") || !dataDir.exists("updown.txt")) {
        QMessageBox::critical(nullptr, "Missing Data!", "Data files missing from lessons/updown/");
        throw(-1);
    }

    QString tmp;

    QFile fg(dataDir.absoluteFilePath(lang + "_gloss.txt"));
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
                updowns.push_back(QPair<QString,QString>(a, b));
            }
        }
    }

    if (glosses.empty() || updowns.empty()) {
        QMessageBox::critical(nullptr, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::shuffle(updowns.begin(), updowns.end(), std::mt19937(std::random_device()()));
}

QString UpdownData::glossUpperDetailed(const QString& upper) {
    QStringList ql;
    QRegExp qr("[-+]");
    int o = 0, n = 0;
    while ((n = qr.indexIn(upper, o)) != -1) {
        if (o) {
            --o;
        }
        QString t = upper.mid(o, n-o);
        if (glosses.find(t) != glosses.end()) {
            ql.push_back(QString("<tr><td>") + t + "</td><td width='20'>&nbsp;</td><td>" + glosses[t] + "</td></tr>");
        }
        else {
            ql.push_back(QString("<tr><td>") + t + "</td><td width='20'>&nbsp;</td><td>" + t + "</td></tr>");
        }
        o = n+1;
    }

    if (o) {
        --o;
    }
    QString t = upper.mid(o);
    if (glosses.find(t) != glosses.end()) {
        ql.push_back(QString("<tr><td>") + t + "</td><td width='20'>&nbsp;</td><td>" + glosses[t] + "</td></tr>");
    }
    else {
        ql.push_back(QString("<tr><td>") + t + "</td><td width='20'>&nbsp;</td><td>" + t + "</td></tr>");
    }

    return QString("<font size='+2'><table>") + ql.join("\n") + "</table></font>";
}

QString UpdownData::glossUpperShort(const QString& upper) {
    QStringList ql;
    QRegExp qr("[-+]");
    int o = 0, n = 0;
    while ((n = qr.indexIn(upper, o)) != -1) {
        if (o) {
            --o;
        }
        QString t = upper.mid(o, n-o);
        if (glosses.find(t) != glosses.end()) {
            ql.push_back(glosses[t]);
        }
        else {
            ql.push_back(t);
        }
        o = n+1;
    }

    if (o) {
        --o;
    }
    QString t = upper.mid(o);
    if (glosses.find(t) != glosses.end()) {
        ql.push_back(glosses[t]);
    }
    else {
        ql.push_back(t);
    }

    return QString("<font size='+2'>") + ql.join(" + ") + "</font>";
}
