#ifndef VALIDATEKEY_HPP
#define VALIDATEKEY_HPP

#include <QNetworkAccessManager>
#include <QtGui>

class ValidateKey : public QDialog {
    Q_OBJECT

public:
    ValidateKey();

public slots:
    void checkInput();
    void openLGRegister();
    void bailOut();
    void finished(QNetworkReply *reply);

private:
    QNetworkAccessManager *nam;
    QLabel *result;
    QLineEdit *input;
};

#endif // VALIDATEKEY_HPP
