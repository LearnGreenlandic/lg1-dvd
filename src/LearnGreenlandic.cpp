#include "TaskChooser.hpp"
#include "common.hpp"
#include <QApplication>
#include <QtWidgets>
#include <ctime>
#include <cstdlib>
#include <cstdint>

#ifdef Q_OS_WIN
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <Windows.h>
#endif

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QApplication::setOrganizationDomain("learngreenlandic.com");
    QApplication::setOrganizationName("LearnGreenlandic");
    QApplication::setApplicationName("Learn Greenlandic");
    QApplication::setQuitOnLastWindowClosed(true);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings settings;

    if (!settings.isWritable()) {
        QMessageBox::critical(nullptr, "Settings Not Writable!", "Unable to store user-specific settings. Cannot continue...");
        QApplication::exit(-1);
        return -1;
    }


    auto seed = static_cast<uint32_t>(static_cast<uint32_t>(time(nullptr)) ^ QApplication::applicationPid());
    qsrand(seed);
    srand(seed);

    dirmap_t dirs;

    if (settings.contains("paths")) {
        int z = settings.beginReadArray("paths");
        for (int i=0 ; i<z ; ++i) {
            settings.setArrayIndex(i);
            size_t rev = settings.value("revision").toUInt();
            QString path = settings.value("path").toString();
            dirs.insert(std::make_pair(rev,path));
        }
        settings.endArray();
    }

    if (dirs.empty() || dirs.begin()->first < lg1_revision || !check_files(dirs)) {
        QDir tDir(QApplication::applicationDirPath());
        do {
            size_t rev = 0;
            if (tDir.exists("./lessons/revision.txt")) {
                if ((rev = read_revision(tDir.absoluteFilePath("./lessons/revision.txt"))) != 0) {
                    dirs.insert(std::make_pair(rev, tDir.absoluteFilePath("lessons")));
                }
            }
            else if (tDir.exists("./lessons/welcome.txt")) {
                dirs.insert(std::make_pair(1, tDir.absoluteFilePath("lessons")));
            }

            if (tDir.exists("./demo/lessons/revision.txt")) {
                if ((rev = read_revision(tDir.absoluteFilePath("./demo/lessons/revision.txt"))) != 0) {
                    dirs.insert(std::make_pair(rev, tDir.absoluteFilePath("demo/lessons")));
                }
            }
            else if (tDir.exists("./demo/lessons/welcome.txt")) {
                dirs.insert(std::make_pair(1, tDir.absoluteFilePath("demo/lessons")));
            }
        } while (tDir.cdUp());

        {
            QProgressDialog progress("Checking all drives for LG1 data...", "", 0, 26);
            progress.setWindowModality(Qt::WindowModal);
            progress.setCancelButton(nullptr);
            progress.show();
            QFileInfoList drives = QDir::drives();
            drives.append(QDir("/mnt/").entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot));
            drives.append(QDir("/media/").entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot));
            drives.append(QDir("/Volumes/").entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot));
            progress.setMaximum(drives.size());

            foreach (QFileInfo drive, drives) {
                #if defined(Q_OS_WIN)
                if (GetDriveTypeA(drive.absolutePath().toStdString().c_str()) == DRIVE_REMOTE) {
                    continue;
                }
                #endif
                size_t rev = 0;
                QFileInfo f(drive.absoluteFilePath() + "/lessons/revision.txt");
                progress.setLabelText(QString("Trying to read ") + f.absoluteFilePath() + " ...");
                if (f.exists() && (rev = read_revision(f.absoluteFilePath()))) {
                    dirs.insert(std::make_pair(rev, f.absoluteDir().absolutePath()));
                }
                else {
                    QFileInfo f(drive.absoluteFilePath() + "/lessons/welcome.txt");
                    progress.setLabelText(QString("Trying to read ") + f.absoluteFilePath() + " ...");
                    if (f.exists() && f.size() == 531) {
                        dirs.insert(std::make_pair(1, f.absoluteDir().absolutePath()));
                    }
                }
                progress.setValue(progress.value()+1);
            }
            progress.setValue(drives.size());
        }

        if (dirs.empty() || (find_newest(dirs, "./revision.txt").isEmpty() && find_newest(dirs, "./welcome.txt").isEmpty()) || !check_files(dirs)) {
            QMessageBox::information(nullptr, "Missing Data / Manglende Data!",
                                     "English: Could not find a suitable lessons folder. Maybe you forgot to insert the DVD or mount a network share? You will now be asked to find the revisions.txt file from the lessons folder.\n\n"
                                     "Dansk: Kunne ikke finde en passende lessons mappe. Måske har du glemt at indsætte DVD'en eller forbinde til netværket? Du vil nu blive bedt om at finde revision.txt fra lessons mappen.");
            QFileInfo revfile = QFileDialog::getOpenFileName(nullptr, "Find lessons/revision.txt", QString(), "revision.txt (*.txt)");
            size_t rev = read_revision(revfile.absoluteFilePath());
            dirs.insert(std::make_pair(rev, revfile.absoluteDir().absolutePath()));

            if (dirs.empty() || (find_newest(dirs, "./revision.txt").isEmpty() && find_newest(dirs, "./welcome.txt").isEmpty()) || !check_files(dirs)) {
                QMessageBox::critical(nullptr, "Missing Data / Manglende Data!",
                                         "English: Could not find a suitable lessons folder. Maybe you forgot to insert the DVD or mount a network share?\n\n"
                                         "Dansk: Kunne ikke finde en passende lessons mappe. Måske har du glemt at indsætte DVD'en eller forbinde til netværket?");
                QApplication::exit(-1);
                return -1;
            }
        }
    }

    if (settings.value("revision", uint(0)).toUInt() > lg1_revision) {
        QMessageBox runoldq(QMessageBox::Warning,
                          "Old version / Gammel version",
                          "English: You have previously run a newer version of LG1 on this machine.\n"
                          "Are you sure you want to run this older version instead?\n\n"
                          "Dansk: Du har tidligere brugt en nyere version af LG1 på denne maskine.\n"
                          "Er du sikker på at du vil køre denne ældre version i stedet?"
                          );
        QPushButton *yes = runoldq.addButton("Run old / Kør gammel", QMessageBox::YesRole);
        runoldq.addButton("Exit / Afslut", QMessageBox::NoRole);

        runoldq.exec();
        if (runoldq.clickedButton() != yes) {
            QApplication::quit();
            return 0;
        }
    }
    else {
        settings.setValue("revision", lg1_revision);
    }

    if (!dirs.empty()) {
        int z = static_cast<int>(dirs.size()), i = 0;
        settings.beginWriteArray("paths", z);
        for (auto it = dirs.begin() ; it != dirs.end() ; ++it, ++i) {
            settings.setArrayIndex(i);
            settings.setValue("revision", uint(it->first));
            settings.setValue("path", it->second);
        }
        settings.endArray();
    }

    QTranslator xtl;
    xtl.load(find_newest(dirs, "i18n/texts_da.qm"));
    QApplication::installTranslator(&xtl);

    QString lang = settings.value("language").toString();
    if (lang != "english" && lang != "danish") {
        QMessageBox langq(QMessageBox::Question,
                          "English / Dansk...",
                          "Do you prefer English or Danish?\n"
                          "You can change language later from the main menu.\n\n"
                          "Foretrækker du engelsk eller dansk?\n"
                          "Du kan skife sprog senere fra hovedmenuen.");
        QPushButton *lang_eng = langq.addButton("I prefer English", QMessageBox::YesRole);
        langq.addButton("Jeg foretrækker dansk", QMessageBox::NoRole);

        langq.exec();
        if (langq.clickedButton() == lang_eng) {
            settings.setValue("language", "english");
        }
        else {
            settings.setValue("language", "danish");
        }
    }

    lang = settings.value("language").toString();
    QTranslator translator;
    if (lang == "english") {
        translator.load(find_newest(dirs, "i18n/texts_en.qm"));
    }
    else {
        translator.load(find_newest(dirs, "i18n/texts_da.qm"));
    }
    QApplication::installTranslator(&translator);

    TaskChooser tc(dirs, &translator);
    tc.show();
    tc.raise();
    tc.activateWindow();

    QTimer::singleShot(1000, &tc, SLOT(checkFirstRun()));

    return QApplication::exec();
}
