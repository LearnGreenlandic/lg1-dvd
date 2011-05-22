#ifndef RICHTEXTPUSHBUTTON_H
#define RICHTEXTPUSHBUTTON_H

#include <QPushButton>
#include <QString>
#include <QStyleOptionButton>

class RichTextPushButton : public QPushButton {
    Q_OBJECT

public:
    explicit RichTextPushButton(QWidget *parent = 0);

    void setHtml(const QString &text);
    void setText(const QString &text);
    QString text() const;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);

private:
    QString htmlText;
    bool isRichText;

    QStyleOptionButton getStyleOption() const;
};

#endif // RICHTEXTPUSHBUTTON_H
