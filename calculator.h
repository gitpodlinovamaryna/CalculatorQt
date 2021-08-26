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
    QLabel *         m_display;
    QLabel *         m_displayPrevious;
    QStack <QString> m_stack;
    QString          m_operator;

public:
    explicit Calculator(QWidget *parent = nullptr);

signals:

public slots:
    void slotButtonClicked();

public:
    Button * createButton(const QString text, QString color );
    void calculate();
    void digitClicked(QString);
    void operatorClicked(QString);
    void equalClicked();
    void dotClicked();
    void percentClicked();
    void backspaceClicked();
    void signChangeClicked();
    void clearAll();
};

#endif // CALCULATOR_H
