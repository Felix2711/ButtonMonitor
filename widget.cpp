#include "config.h"
#include "widget.h"
#include <QGridLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Widget s &QTimer::timeouttructure
    setWindowTitle("ButtonMonitor");
    resize(300, 100);
    QGridLayout* grid = new QGridLayout(this);
    setLayout(grid);

    // Labels for input pins / buttons
    int column = 0;
    for (auto pin : BUTTONS)
    {
        // pin numbers
        QLabel* label = new QLabel("GPIO " + QString::number(pin), this);
        label->setAlignment(Qt::AlignCenter);
        grid->addWidget(label, 0, column); // links oben (1. Zeile / 1. - 3. Spalte)

        // pin states
        QLabel* state = new QLabel("0", this);
        state->setAlignment(Qt::AlignCenter);
        grid->addWidget(state, 1, column++); // links oben (2. Zeile / 1. - 3. Spalte)
        m_input_display.push_back(state);
    }

    m_cntLabel = new QLabel("cnt: 0", this);
    m_cntLabel->setAlignment(Qt::AlignHCenter);
    grid->addWidget(m_cntLabel, 2, 1);
    m_cnt = 0;

    // initialize hardware
    m_gpio = new gpio();

    m_timer = new QTimer(this);
    // Connect QTimer (Signal) with GUI function (Slot) "update display"
    connect(m_timer, &QTimer::timeout, this, &Widget::updateButtonState);
    m_timer->start(T_UPDATE);
}

Widget::~Widget()
{

}

void Widget::updateButtonState()
{
    int n = 0;
    for (auto pin : BUTTONS)
    {
        int state = !m_gpio->get(pin);

        if(m_gpio->detect_edge(pin, true, n))
        {
            switch (n)
            {
                case 0:
                    m_cnt--;
                    break;
                case 1:
                    m_cnt =0;
                    break;
                case 2:
                    m_cnt++;
                    break;
                default:
                    break;
            }
        }


        m_cntLabel->setText("cnt : " + QString::number(m_cnt));
        m_input_display[n++]->setText(QString::number(state));
    }
}
