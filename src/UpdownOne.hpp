#ifndef UPDOWNONE_HPP
#define UPDOWNONE_HPP

#include "UpdownData.hpp"
#include <QtGui>
#include <stdint.h>

class UpdownOne : public QWidget {
    Q_OBJECT

public:
    UpdownOne(QDir dataDir);

public slots:
    void showNext();
    void showHelp();

private:
    UpdownData data;
    uint32_t curAt;

    QVBoxLayout *curWord;
    QLabel *up;
    QLabel *down;
    QPushButton *help;
};

#endif // UPDOWNONE_HPP
