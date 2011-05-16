#include "PronounceOne.hpp"

PronounceOne::PronounceOne(QDir dataDir) :
data(dataDir),
curAt(0)
{
    setWindowTitle("Udtaleøvelse: Gentag");

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *ql = new QLabel("Lyt og gentag ordet.\n");
    ql->setWordWrap(true);
    qvbl->addWidget(ql);

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    Phonon::createPath(media, audio);

    media->setCurrentSource(data.sounds[data.words.at(curAt)]);

    text = new QLabel(QString("<h2>") + data.words.at(curAt) + "</h2>");
    qvbl->addWidget(text);

    qvbl->addSpacing(5);

    QPushButton *again = new QPushButton("Lyt igen");
    connect(again, SIGNAL(clicked()), this, SLOT(playAgain()));
    qvbl->addWidget(again);

    qvbl->addSpacing(5);

    QPushButton *nb = new QPushButton("Gå til næste ord");
    connect(nb, SIGNAL(clicked()), this, SLOT(showNext()));
    qvbl->addWidget(nb);

    setLayout(qvbl);
}

void PronounceOne::show() {
    QWidget::show();
    media->play();
}

void PronounceOne::playAgain() {
    media->stop();
    media->seek(0);
    media->play();
}

void PronounceOne::showNext() {
    ++curAt;
    if (curAt >= static_cast<uint32_t>(data.words.size())) {
        QMessageBox::information(0, "Færdig!", "Der er ikke flere ord...vinduet lukker sig selv nu.");
        close();
        return;
    }
    media->setCurrentSource(data.sounds[data.words.at(curAt)]);
    text->setText(QString("<h2>") + data.words.at(curAt) + "</h2>");
    adjustSize();
    playAgain();
}
