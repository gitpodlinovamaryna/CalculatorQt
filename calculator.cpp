#include "calculator.h"
#include "button.h"


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Calculator");
    resize(230,200);
    setFixedSize(300, 250);

    QFont displayFont("Times", 16, QFont::Bold);
    QString btn_orange = "QPushButton{background:#FF6600;}";
    QString btn_white = "QPushButton{background:#FFFFFF;}";
    QString btn_red = "QPushButton{background:#CC0000;}";
    QString btn_gray = "QPushButton{background:#B1CECE;}";
    QString color;
    m_display = new QLabel("");
    m_display->setMinimumSize(150,50);

    QChar buttonsBox [5][4] = {
        {'C', '<', '%', '='},
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'0', 177, '.', '+'}
    };

    QGridLayout * mainLayout = new QGridLayout();
    mainLayout->addWidget(m_display,0,0,1,4);

    for (int i = 0; i < 5; ++i) {
     for (int j = 0; j < 4; ++j) {
         if(j == 3)
             color = btn_orange;
         if(i == 0 && j == 0)
             color = btn_red;
         if((i == 4 && j == 1) || (i == 4 && j == 2))
             color = btn_gray;
         else
             color = btn_white;

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

void Calculator::slotButtonClicked(){

}
