#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>


class Button:public QPushButton
{
public:
    Button(const QString &text, QString color, QWidget *parent = 0);
};

#endif // BUTTON_H
