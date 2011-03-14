#include "constants.hpp"
#include "TaskChooser.hpp"
#include <QtGui/QApplication>
#include <ctime>
#include <cstdlib>
#include <stdint.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationDomain("learngreenlandic.com");
    app.setOrganizationName("The Oxen Road Inn");
    app.setApplicationName("Learn Greenlandic");
    app.setQuitOnLastWindowClosed(true);

    uint32_t seed = static_cast<uint32_t>(time(0)) ^ app.applicationPid();
    qsrand(seed);
    srand(seed);

    QDir tDir(app.applicationDirPath());
    while (!tDir.exists("./lessons/1/danish/0.png") && tDir.cdUp()) {
    }

    QDir dataDir(tDir.absolutePath() + "/lessons");
    if (!dataDir.exists() || !dataDir.exists("./1/danish/" LECTURE_FILE) || !dataDir.exists("./1/danish/0.png")) {
        QMessageBox::critical(0, "Missing Data!", "Could not find required files in lessons/1/danish/");
        app.exit(-1);
        return -1;
    }

    TaskChooser tc(dataDir);
    tc.show();

    return app.exec();
}
