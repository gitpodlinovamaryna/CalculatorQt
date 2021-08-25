#include "button.h"

Button::Button(const QString &text, QString color, QWidget *parent)
       : QPushButton(parent)
{
    setText(text);
    QFont btn_font("SansSerif", 14, QFont::Bold);
    setFont(btn_font);
    setMinimumHeight(40);
    setMinimumWidth(50);
    setStyleSheet(color);
}
