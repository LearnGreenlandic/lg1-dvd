#include "PronounceData.hpp"
#include <algorithm>
#include <random>

PronounceData::PronounceData(const dirmap_t& dirs) {
    QString f_d = find_newest(dirs, "./pronounce/alla.wav");
    QDir dataDir(f_d.replace("alla.wav", ""));
    if (!dataDir.exists()) {
        QMessageBox::critical(nullptr, "Missing Data Folder!", "Could not change working folder to lessons/pronounce/");
        throw(-1);
    }

    QFileInfoList soundFiles = dataDir.entryInfoList(QStringList() << "*.wav");
    foreach (QFileInfo soundFile, soundFiles) {
        QString key = soundFile.baseName();
        words.push_back(key);
        sounds[key] = soundFile.canonicalFilePath();
    }

    if (words.empty() || sounds.empty()) {
        QMessageBox::critical(nullptr, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));
}
