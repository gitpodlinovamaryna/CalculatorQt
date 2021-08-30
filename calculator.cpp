#include "calculator.h"



Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Calculator");
    setFixedSize(270/* height */, 310);
    setStyleSheet("Calculator{background:#F0F0F5;}");

    QFont displayFont_16b("sans", 16, QFont::Bold);
    QFont displayFont_14n("sans", 12, QFont::Light);

    m_display = new QLabel("");
    m_displayPrevious = new QLabel("");
    m_display->setMinimumSize(150,50);
    m_displayPrevious->setMinimumSize(150,50);
    m_display->setFont(displayFont_16b);
    m_displayPrevious->setFont(displayFont_14n);
    m_display->setAlignment(Qt::AlignRight);
    m_displayPrevious->setAlignment(Qt::AlignRight);
    m_operator = "";
    m_error = false;

    const int rowQuantity = 5;
    const int columnQuantity = 4;

   // Button layout

    QChar buttonsBox [rowQuantity][columnQuantity] = {
        {'C', '<', '%', '/'},
        {'7', '8', '9', '*'},
        {'4', '5', '6', '-'},
        {'1', '2', '3', '+'},
        {177, '0', '.', '='} //177 ascii +/-
    };

    QGridLayout * mainLayout = new QGridLayout();
    mainLayout->addWidget(m_displayPrevious, 0, 0, 1, 4);
    mainLayout->addWidget(m_display, 1, 0, 1, 4);

    // Сreating and placing buttons

    for (int btnRow = 0; btnRow < rowQuantity; ++btnRow)
    {
        for (int btnColumn = 0; btnColumn < columnQuantity; ++btnColumn)
        {
             mainLayout->addWidget(createButton(buttonsBox[btnRow][btnColumn]), btnRow + 2, btnColumn);
        }
    }
    setLayout(mainLayout);
}

Calculator::~Calculator() = default;

Button * Calculator::createButton(const QString text)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return button;
}

void Calculator::slotButtonClicked()
{
    error();
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
    if(button_text == QChar(177))// ascii +/-
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
        if(text == "0")
        {
            text = "";
        }
        if(m_stack.count() == 1 && text == "")
        {
            m_displayPrevious->clear();
            m_stack.pop();
        }
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
    else if(strOperator == "/")
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
    if(m_stack.count() == 0 && displayText.length() > 0 && displayText != "-")
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
        if(displayText.toDouble() == 0 && isDivideNull())
        {
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
    QString displayText = m_display->text();
    if(m_stack.count() == 2 && displayText.length() > 0 && displayText != "-")
    {
        if(displayText.toDouble() == 0 && isDivideNull())
        {
            return;
        }
        m_displayPrevious->setText(m_displayPrevious->text() + displayText);
        m_stack.push(displayText);
        calculate();
        m_display->setText("");
    }
}

bool Calculator::isDivideNull()
{
     QString checkOperator = m_stack.pop();
     m_stack.push(checkOperator);
     if(checkOperator == "/")
     {
        m_displayPrevious->setText("Division by zero");
        m_display->setText("is not possible");
        m_error = true;
        return true;
     }
     else
         return false;
}

void Calculator::dotClicked()
{
    QString text = m_display->text();

    if(!text.contains("."))
    {
        if( text == "")
        {
            if(m_stack.count() == 1)
            {
                m_stack.pop();
                m_displayPrevious->setText("");
            }
           m_display->setText("0.");
        }
        else if( text == "+" || text == "-" || text == "*" || text == "/")
        {
            if(m_stack.count() == 1)
            {
                QString operand_1 = m_stack.pop();
                m_stack.push(operand_1);
                m_stack.push(text);
                m_display->setText("0.");
                m_displayPrevious->setText(operand_1 + text);
             }
        }
        else
        {
            m_display->setText(m_display->text() + ".");
        }
    }
}

void Calculator::percentClicked()
{
    QString text = m_display->text();
    double result = 0;
    if(m_stack.count() == 0 && text.length() > 0 && text != "-")
    {
        result = (text.toDouble()) / 100;
        m_displayPrevious->setText(QString::number(result, 'g', 15));
        m_stack.push((QString::number(result, 'g',15)));
    }
    else if(m_stack.count() == 2 && text.length() > 0 && text != "-")
    {
        QString operatorSign = m_stack.pop();
        QString operand_1 = m_stack.pop();
        QString operand_2 = text;
        result = ((operand_1.toDouble()) / 100) * (operand_2.toDouble());
        m_stack.push(operand_1);
        m_stack.push(operatorSign);
        m_stack.push((QString::number(result, 'g',15)));
        calculate();
        operand_2 = m_stack.pop();
        m_stack.push(operand_2);
        m_displayPrevious->setText(operand_1 + operatorSign + text + "%" + "=" + operand_2);
     }
    m_display->setText("");
}

void Calculator::backspaceClicked()
{
    QString text = m_display->text();
    if(text != "")
    {
        text.chop(1);
        if(text.isEmpty())
        {
             text = "";
        }
        m_display->setText(text);
    }
    if(text.isEmpty() && m_stack.count() == 2)
    {
        text = m_stack.pop();
        m_display->setText(text);
        text = m_displayPrevious->text();
        text.chop(1);
        m_displayPrevious->setText(text);
    }
}

void Calculator::signChangeClicked()
{
    QString displayText = m_display->text();
    double result = displayText.toDouble();
    if(result > 0.0)
    {
        displayText.prepend("-");
    }
    else if(result < 0.0)
    {
        displayText.remove(0, 1);
    }
    m_display->setText(displayText);
}

void Calculator::error()
{
    if(m_error)
    {
        m_displayPrevious->setText("");
        m_display->setText("");
        m_stack.clear();
        m_error = false;
    }
}
void Calculator::clearAll()
{
    m_stack.clear();
    m_display->setText("");
    m_displayPrevious->setText("");
    return;
}
