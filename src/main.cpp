#include "constants.hpp"
#include "Lecture1Danish.hpp"
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationDomain("learngreenlandic.com");
    app.setOrganizationName("The Oxen Road Inn");
    app.setApplicationName("Learn Greenlandic");
    app.setQuitOnLastWindowClosed(true);

    QDir tDir(app.applicationDirPath());
    while (!tDir.exists("./lessons/1/danish/0.png") && tDir.cdUp());

    QDir dataDir(tDir.absolutePath() + "/lessons/1/danish/");
    if (!dataDir.exists() || !dataDir.exists(LECTURE_FILE) || !dataDir.exists("0.png")) {
        QMessageBox::critical(0, "Missing Data!", "Could not find required files in lessons/1/danish/");
        app.exit(-1);
        return -1;
    }

    Lecture1Danish l1d(dataDir);
    l1d.show();

    return app.exec();
}
