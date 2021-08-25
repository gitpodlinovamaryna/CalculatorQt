#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <button.h>


class Calculator : public QWidget
{
    Q_OBJECT

private:
    QLabel * m_display;
    QLabel * m_displayPrevious;
    QStack <QString> m_stack;

public:
    explicit Calculator(QWidget *parent = nullptr);
    Button * createButton(const QString text, QString color );
    void calculate();

signals:

public slots:
    void slotButtonClicked();
};

#endif // CALCULATOR_H
