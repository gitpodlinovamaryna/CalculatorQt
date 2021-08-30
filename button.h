#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>


class Button:public QPushButton
{
public:
    Button(const QString &text, QWidget *parent = 0);
    ~Button() override;
};

#endif // BUTTON_H
