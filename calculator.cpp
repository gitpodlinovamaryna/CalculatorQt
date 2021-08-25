#include "calculator.h"
#include "button.h"


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Calculator");
    setFixedSize(270, 310);
    setStyleSheet("Calculator{background:#F0F0F5;}");

    QFont displayFont_16b("sans", 16, QFont::Bold);
    QFont displayFont_14n("sans", 14, QFont::Medium);

    QString btn_orange = "QPushButton{background:#FF6600;}";
    QString btn_white = "QPushButton{background:#FFFFFF;}";
    QString btn_red = "QPushButton{background:#CC0000;}";
    QString btn_gray = "QPushButton{background:#B1CECE;}";
    QString color;

    m_display = new QLabel("");
    m_displayPrevious = new QLabel("");
    m_display->setMinimumSize(150,50);
    m_displayPrevious->setMinimumSize(150,50);
    m_display->setFont(displayFont_16b);
    m_displayPrevious->setFont(displayFont_14n);


    QChar buttonsBox [5][4] = {
        {'C', '<', '%', '='},
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {177, '0', '.', '+'}
    };

    QGridLayout * mainLayout = new QGridLayout();
    mainLayout->addWidget(m_displayPrevious, 0, 0, 1, 4);
    mainLayout->addWidget(m_display, 1, 0, 1, 4);

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
         if((i == 4 && j == 0) || (i == 4 && j == 2) ||
            (i == 0 && j == 1) || (i == 0 && j == 2))
             color = btn_gray;
         else
             color = btn_white;
         if(j == 3)
             color = btn_orange;
         if(i == 0 && j == 0)
             color = btn_red;
         mainLayout->addWidget(createButton(buttonsBox[i][j], color), i + 2, j);
        }

    }

    setLayout(mainLayout);

}


Button * Calculator::createButton(const QString text, QString color )
{
    Button *button = new Button(text, color);
    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return button;
}

void Calculator::calculate()
{
    double operand_2 = m_stack.pop().toDouble();
    QString strOperator = m_stack.pop();
    double operand_1 = m_stack.pop().toDouble();
    double result = 0;

    if(strOperator == "+")
    {
        result = operand_1 + operand_2;
    }
    else if(strOperator == "-")
    {
        result = operand_1 - operand_2;
    }
    else if(strOperator == "*")
    {
        result = operand_1 * operand_2;
    }
    else if(strOperator == "/")
    {
        result = operand_1 / operand_2;
    }
    m_display->setText(QString::number(result, 'g',15));
}

void Calculator::slotButtonClicked()
{
    QString button_text = ((QPushButton *)sender())->text();
    if(button_text == "C")
    {
        m_stack.clear();
        m_display->setText("0");
        return;
    }

    QString display_text = m_display->text();




}
