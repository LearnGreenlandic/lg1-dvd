#include "RichTextPushButton.hpp"

#include <QPainter>
#include <QPixmap>
#include <QTextDocument>
#include <QIcon>
#include <QSize>
#include <QMenu>
#include <QStylePainter>

RichTextPushButton::RichTextPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void RichTextPushButton::setHtml(const QString &text)
{
    htmlText = text;
    isRichText = true;

    QPalette palette;
    palette.setBrush(QPalette::ButtonText, Qt::transparent);
    setPalette(palette);
}

void RichTextPushButton::setText(const QString &text)
{
    isRichText = false;
    QPushButton::setText(text);
}


QString RichTextPushButton::text() const
{
    if (isRichText) {
        QTextDocument richText;
        richText.setHtml(htmlText);
        return richText.toPlainText();
    } else
        return QPushButton::text();
}

void RichTextPushButton::paintEvent(QPaintEvent *event)
{
    if (isRichText) {
        QStylePainter p(this);

        QRect buttonRect = rect();
        QPoint point;

        QTextDocument richTextLabel;
        richTextLabel.setHtml(htmlText);

        QPixmap richTextPixmap(richTextLabel.size().width(), richTextLabel.size().height());
        richTextPixmap.fill(Qt::transparent);
        QPainter richTextPainter(&richTextPixmap);
        richTextLabel.drawContents(&richTextPainter, richTextPixmap.rect());

        if (!icon().isNull())
            point = QPoint(buttonRect.x() + buttonRect.width() / 2 + iconSize().width() / 2 + 2, buttonRect.y() + buttonRect.height() / 2);
        else
            point = QPoint(buttonRect.x() + buttonRect.width() / 2 - 1, buttonRect.y() + buttonRect.height() / 2);

        buttonRect.translate(point.x() - richTextPixmap.width() / 2, point.y() - richTextPixmap.height() / 2);

        p.drawControl(QStyle::CE_PushButton, getStyleOption());
        p.drawPixmap(buttonRect.left(), buttonRect.top(), richTextPixmap.width(), richTextPixmap.height(),richTextPixmap);
    } else
        QPushButton::paintEvent(event);
}

QStyleOptionButton RichTextPushButton::getStyleOption() const
{
    QStyleOptionButton opt;
    opt.initFrom(this);
    opt.features = QStyleOptionButton::None;
    if (isFlat())
        opt.features |= QStyleOptionButton::Flat;
    if (menu())
        opt.features |= QStyleOptionButton::HasMenu;
    if (autoDefault() || isDefault())
        opt.features |= QStyleOptionButton::AutoDefaultButton;
    if (isDefault())
        opt.features |= QStyleOptionButton::DefaultButton;
    if (isDown() || (menu() && menu()->isVisible()))
        opt.state |= QStyle::State_Sunken;
    if (isChecked())
        opt.state |= QStyle::State_On;
    if (!isFlat() && !isDown())
        opt.state |= QStyle::State_Raised;
    opt.text = text();
    opt.icon = icon();
    opt.iconSize = iconSize();
    return opt;
}
