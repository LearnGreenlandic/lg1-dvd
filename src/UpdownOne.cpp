#include "UpdownOne.hpp"

UpdownOne::UpdownOne(QDir dataDir) :
QWidget(0, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
data(dataDir)
{
    setWindowTitle("Up/Down: Reception");
}
