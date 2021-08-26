#include "calculator.h"
#include "button.h"


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Calculator");
    setFixedSize(270, 310);
    setStyleSheet("Calculator{background:#F0F0F5;}");

    QFont displayFont_16b("sans", 16, QFont::Bold);
    QFont displayFont_14n("sans", 12, QFont::Light);

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
    m_display->setAlignment(Qt::AlignRight);
    m_displayPrevious->setAlignment(Qt::AlignRight);
    m_operator = "";


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

void Calculator::slotButtonClicked()
{
    QString button_text = ((QPushButton *)sender())->text();
    if(button_text == "C")
    {
        clearAll();
    }
    if(button_text.contains(QRegExp("[0-9]")))
    {
        digitClicked(button_text);
    }
    if(button_text == "+" || button_text == "-" || button_text == "*" || button_text == "/")
    {
        operatorClicked(button_text );
    }
    if(button_text == "=")
    {
        equalClicked();
    }
    if(button_text == ".")
    {
        dotClicked();
    }
    if(button_text == "%")
    {
        percentClicked();
    }
    if(button_text == "<")
    {
        backspaceClicked();
    }
    if(button_text == QChar(177))
    {
        signChangeClicked();
    }
}

void Calculator::digitClicked(QString button_text)
{
    QString text = m_display->text();
    if(text == "+" || text == "-" || text =="*" || text == "/")
    {
        QString operand_1 = m_stack.pop();
        m_stack.push(operand_1);
        m_stack.push(text);
        m_displayPrevious->setText(operand_1 + text);
        m_display->setText(button_text);
    }
    else
    {
     text += button_text;
     m_display->setText(text);
    }
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
    else if(strOperator == "/" && operand_2 != 0)
    {
        result = operand_1 / operand_2;
    }
    QString str_result = QString::number(result, 'g', 10);
    m_displayPrevious->setText(m_displayPrevious->text() + "=" + str_result);
    m_stack.push(str_result);
}


void Calculator::operatorClicked(QString button_text)
{
    QString displayText = m_display->text();
    if(m_stack.isEmpty() && displayText.length() > 0 && displayText != "-")
    {
        m_displayPrevious->setText(displayText);
        m_stack.push(displayText);
        m_display->setText(button_text);
    }
    else if(m_stack.count() == 1)
    {
      m_display->setText(button_text);
    }
    else if(m_stack.count() == 2 && displayText.length() > 0 && displayText != "-")
    {
        if(displayText.toDouble() == 0)
        {
            QString checkOperator = m_stack.pop();
            m_stack.push(checkOperator);
            if(checkOperator == "/")
            return;
        }
        m_displayPrevious->setText(m_displayPrevious->text() + displayText);
        m_stack.push(displayText);
        calculate();
        m_display->setText(button_text);
    }
}

void Calculator::equalClicked()
{

}

void Calculator::dotClicked()
{

}

void Calculator::percentClicked()
{
    QString str = m_display->text();
    double value = str.toDouble();
    if(value == 0 && m_stack.count() == 2)
    {
        m_stack.push(str);
        return;
    }
    else if(m_stack.count() == 3)
    {
        equalClicked();
        return;
    }
    else
    {
        str = QString::number((value / 100), 'g', 15);
        m_display->setText(str);
    }

m_stack.push(str);
}

void Calculator::backspaceClicked()
{

}

void Calculator::signChangeClicked()
{

}

void Calculator::clearAll()
{
    m_stack.clear();
    m_display->setText("");
    m_displayPrevious->setText("");
    return;
}
