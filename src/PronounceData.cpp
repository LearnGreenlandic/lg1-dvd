#include "PronounceData.hpp"
#include <algorithm>

PronounceData::PronounceData(QDir dataDir) :
dataDir(dataDir)
{
    if (!dataDir.cd("./pronounce/")) {
        QMessageBox::critical(0, "Missing Data Folder!", "Could not change working folder to lessons/pronounce/");
        throw(-1);
    }

    QFileInfoList soundFiles = dataDir.entryInfoList(QStringList() << "*.wav");
    foreach (QFileInfo soundFile, soundFiles) {
        QString key = soundFile.baseName();
        words.push_back(key);
        sounds[key] = soundFile.canonicalFilePath();
    }

    if (words.empty() || sounds.empty()) {
        QMessageBox::critical(0, "Data Error!", "Failed to read data files!");
        throw(-1);
    }

    std::random_shuffle(words.begin(), words.end());
}
