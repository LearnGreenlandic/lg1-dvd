#include "ValidateKey.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>

ValidateKey::ValidateKey() :
QDialog(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Validering af licensnøgle"));

    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    QVBoxLayout *qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("Indtast din licensnøgle nedenfor. Du finder den bag på indstikshæftet. Dette check kræver at din computer er online og at du registrerer dig på http://learngreenlandic.com/register/"));
    label->setWordWrap(true);
    qvbl->addWidget(label);

    QPushButton *openlg = new QPushButton(tr("http://learngreenlandic.com/register/"));
    connect(openlg, SIGNAL(clicked()), this, SLOT(openLGRegister()));
    qvbl->addWidget(openlg);

    label = new QLabel(tr("<b>Bemærk:</b> Du må kun bruge din licensnøgle en gang, for en person, på en computer!"));
    qvbl->addWidget(label);

    input = new QLineEdit;
    connect(input, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    qvbl->addWidget(input);

    result = new QLabel;
    qvbl->addWidget(result);

    QPushButton *check = new QPushButton(tr("Valider online"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    qvbl->addWidget(check);

    QPushButton *close = new QPushButton(tr("Afslut program"));
    connect(close, SIGNAL(clicked()), this, SLOT(bailOut()));
    qvbl->addWidget(close);

    setLayout(qvbl);
}

void ValidateKey::checkInput() {
    result->setText(tr("... checker licensnøgle via learngreenlandic.com ..."));

    QNetworkRequest request(QUrl("http://learngreenlandic.com/callback/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QSettings settings;
    settings.setValue("license_key", input->text());

    QUrl params;
    params.addQueryItem("key", input->text());
    params.addQueryItem("language", tr("danish"));

    QByteArray data;
    data.append(params.toString());
    data.remove(0, 1);

    nam->post(request, data);

    adjustSize();
}

void ValidateKey::openLGRegister() {
    QDesktopServices::openUrl(QUrl("http://learngreenlandic.com/register/"));
}

void ValidateKey::bailOut() {
    QSettings settings;
    settings.setValue("license_bailout", true);
    QCoreApplication::quit();
    close();
}

void ValidateKey::finished(QNetworkReply *reply) {
    QString rv = reply->readAll();

    if (rv[0] == 'P') {
        QSettings settings;
        settings.setValue("encryption_key", rv.trimmed());
        close();
        return;
    }

    result->setText(rv);
    adjustSize();
}
