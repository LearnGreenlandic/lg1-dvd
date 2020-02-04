#include "files.hpp"
#include "common.hpp"
#include "CryptFile.hpp"
#include <QProgressDialog>
#include <QCryptographicHash>
#include <iostream>

QString find_newest(const dirmap_t& dirs, const QString& name) {
    QString file;
    for (const auto& it : dirs) {
        QString str(it.second);
        QDir dir(str);
        if (dir.exists(name)) {
            file = dir.absoluteFilePath(name);
            break;
        }
    }
    return file;
}

size_t read_revision(const QString& name) {
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QVariant s(line);
        return s.toUInt();
    }

    return 0;
}

bool check_files(const dirmap_t& dirs) {
    int z = sizeof(file_list)/sizeof(*file_list);
    QProgressDialog progress("Verifying existence of LG1 data...", "", 0, z);
    progress.setWindowModality(Qt::WindowModal);
    progress.setCancelButton(nullptr);
    progress.show();

    for (int i=0 ; i<z ; ++i) {
        progress.setLabelText(QString("Verifying ") + file_list[i] + " ...");
        progress.setValue(progress.value()+1);
        QString n = find_newest(dirs, file_list[i]);
        if (n.isEmpty()) {
            return false;
        }
    }

    return true;
}

QString decrypt_to_tmp(const QString &file) {
    QCryptographicHash sha1(QCryptographicHash::Sha1);
    sha1.addData(file.toUtf8());
    QDir tmpdir(QDir::tempPath());
    QString tmpfile = tmpdir.absoluteFilePath(QString(sha1.result().toHex()) + "-learngreenlandic.avi");

    if (!tmpdir.exists(tmpfile)) {
        CryptFile input(file);
        QFile output(tmpfile);

        input.open(QIODevice::ReadOnly);
        output.open(QIODevice::WriteOnly);

        QProgressDialog progress("Transcoding for playback...", "", 0, input.size());
        progress.setWindowModality(Qt::WindowModal);
        progress.setCancelButton(nullptr);
        progress.show();

        char buf[32768];
        qint64 r;
        while (!input.atEnd() && (r = input.read(buf, sizeof(buf))) > 0) {
            if (output.write(buf, r) <= 0) {
                std::cerr << "Write failed at offsets " << input.pos() << ", " << output.pos() << std::endl;
                throw(-1);
            }
            progress.setValue(input.pos());
        }
        progress.setValue(input.size());

        output.close();
        input.close();
    }

    return tmpfile;
}
