#include "textticker.h"
#include <QPainter>
#include <QTimer>


TextTicker::TextTicker(QWidget *parent)
    : QLabel(parent)
{
    setMinimumWidth(200);
    setMinimumHeight(40);


    m_curIndex = 0;//当前角码
    m_showText = "This is a textTicker Text!";//显示的文字
    m_charWidth = fontMetrics().width("a");//每个字符的宽度


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TextTicker::updateIndex);
    timer->start(100);
}


TextTicker::~TextTicker()
{


}

void TextTicker::setShowText(QString str){
    m_showText = str;
}

void TextTicker::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    QFont font;
    font.setPointSize(10);
    painter.setFont(font);
    painter.drawText(0, 23, m_showText.mid(m_curIndex));
    painter.drawText(width() - m_charWidth*m_curIndex, 23, m_showText.left(m_curIndex));
}


void TextTicker::updateIndex()
{
    update();
    m_curIndex++;
    if (m_curIndex*m_charWidth > width())
        m_curIndex = 0;
}
