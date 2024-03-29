#include "common.hpp"
#include "ValidateKey.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>

ValidateKey::ValidateKey() :
QDialog(nullptr, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Validering af licensnøgle"));
    setMinimumWidth(500);

    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    auto *qvbl = new QVBoxLayout;

    QLabel *label = new QLabel(tr("xvid text"));
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::LinksAccessibleByKeyboard);
    label->setOpenExternalLinks(true);
    qvbl->addWidget(label);

    QPushButton *xvid = new QPushButton(tr("Installer Xvid / DivX"));
    connect(xvid, SIGNAL(clicked()), this, SLOT(launchXvid()));
    qvbl->addWidget(xvid);

    qvbl->addSpacing(15);

    label = new QLabel(tr("license key text"));
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::LinksAccessibleByKeyboard);
    label->setOpenExternalLinks(true);
    qvbl->addWidget(label);

    qvbl->addSpacing(15);

    email1 = new QLineEdit;
    connect(email1, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    email2 = new QLineEdit;
    connect(email2, SIGNAL(returnPressed()), this, SLOT(checkInput()));
    lkey = new QLineEdit;
    connect(lkey, SIGNAL(returnPressed()), this, SLOT(checkInput()));

    auto *form = new QFormLayout;
    form->addRow(tr("Email"), email1);
    form->addRow(tr("Gentag email"), email2);
    form->addRow(tr("Licensnøgle"), lkey);
    qvbl->addLayout(form);

    result = new QLabel;
    result->setWordWrap(true);
    qvbl->addWidget(result);

    QPushButton *check = new QPushButton(tr("Valider online"));
    connect(check, SIGNAL(clicked()), this, SLOT(checkInput()));
    qvbl->addWidget(check);

    QPushButton *close = new QPushButton(tr("Afslut program"));
    connect(close, SIGNAL(clicked()), this, SLOT(bailOut()));
    qvbl->addWidget(close);

    setLayout(qvbl);
    adjustSize();
}

void ValidateKey::launchXvid() {
    QString torun = QCoreApplication::instance()->applicationDirPath() +
    #if defined(Q_OS_WIN)
        "/../Xvid-1.3.2-20110601.exe"
    #elif defined(Q_OS_MAC)
        "/../DivXInstaller.dmg"
    #else
        "/install-prereq-ubuntu.sh"
    #endif
    ;

    if (!QFileInfo(torun).exists()) {
        QMessageBox::information(nullptr, "Missing Xvid / DivX packages!", QString("Could not locate ") + torun + "\nPlease open the DVD in your file manager and install Xvid / DivX manually, or have your system administrator help you.");
    }

    #if defined(Q_OS_WIN) || defined(Q_OS_MAC)
        QDesktopServices::openUrl(QUrl::fromLocalFile(torun));
    #else
        torun = QString("/usr/bin/xterm -e \"") + torun + "\" &";
        system(torun.toStdString().c_str());
    #endif
}

void ValidateKey::checkInput() {
    if (email1->text().simplified() != email2->text().simplified()) {
        result->setText(tr("Email-addresserne er ikke ens!"));
        return;
    }
    result->setText(tr("... checker licensnøgle via learngreenlandic.com ..."));

    QNetworkRequest request(QUrl("http://learngreenlandic.com/callback/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("app", "LG1");
    params.addQueryItem("revision", QVariant(lg1_revision).toString());
    params.addQueryItem("email", email1->text().simplified());
    params.addQueryItem("key", lkey->text().simplified());
    params.addQueryItem("language", tr("danish"));

#if defined(Q_OS_WIN)
    params.addQueryItem("os", "win");
#elif defined(Q_OS_MAC)
    params.addQueryItem("os", "mac");
#else
    if (sizeof(void*) > 4) {
        params.addQueryItem("os", "linux64");
    }
    else {
        params.addQueryItem("os", "linux32");
    }
#endif

    QByteArray data;
    data.append(params.toString());
    data.remove(0, 1);

    nam->post(request, data);

    adjustSize();
}

void ValidateKey::bailOut() {
    QCoreApplication::quit();
    close();
}

void ValidateKey::finished(QNetworkReply *reply) {
    QNetworkReply::NetworkError e = reply->error();
    if (e != QNetworkReply::NoError) {
        QString es;
        switch (e) {
        case QNetworkReply::ConnectionRefusedError:
            es = "the remote server refused the connection (the server is not accepting requests)";
            break;
        case QNetworkReply::HostNotFoundError:
            es = "the remote host name was not found (invalid hostname)";
            break;
        case QNetworkReply::TimeoutError:
            es = "the connection to the remote server timed out";
            break;
        case QNetworkReply::TemporaryNetworkFailureError:
            es = "the connection was broken due to disconnection from the network, however the system has initiated roaming to another access point. The request should be resubmitted and will be processed as soon as the connection is re-established.";
            break;
        case QNetworkReply::UnknownNetworkError:
            es = "an unknown network-related error was detected";
            break;
        default:
            es = "an unknown error occured with the connection";
            break;
        }
        es = "<b>" + es + "</b>";
        result->setText(es);
        adjustSize();
        return;
    }

    QString rv = reply->readAll();

    if (rv[0] == 'P') {
        QSettings settings;
        settings.setValue("license_key", lkey->text().simplified().replace(QRegExp("\\W+"), "").toUpper());
        settings.setValue("encryption_key", rv.trimmed());
        close();
        return;
    }
    if (rv.indexOf("site_verification")) {
        QSettings settings;
        QStringList rvs = rv.trimmed().split('\n');
        foreach (QString r, rvs) {
            QStringList rv = r.simplified().split('=');
            settings.setValue(rv.at(0), rv.at(1));
        }
        close();
        return;
    }

    result->setText(rv);
    adjustSize();
}
