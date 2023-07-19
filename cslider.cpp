#include "cslider.h"

CSlider::CSlider(QWidget *parent)
    : QWidget{parent}
{
    this->setMouseTracking(true);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

// 设置之不发射信号, 输入视频时长
void CSlider::setValue(quint64 value)
{
    if (value > m_maxValue || value < m_minValue) {
        return;
    }
    m_curValue = value;
    repaint();
}

void CSlider::enterEvent(QEnterEvent *event)
{
    m_isSlideMe = true;
}

void CSlider::leaveEvent(QEvent *event)
{
    m_isSlideMe = false;
}

void CSlider::setMaxValue(quint64 value)
{
    if (value < m_minValue) {
        return;
    }
    m_maxValue = value;
    repaint();
}

void CSlider::setMinValue(quint64 value)
{
    if (value < m_minValue) {
        return;
    }
    m_minValue = value;
}

void CSlider::setValueRange(quint64 valueMin, quint64 valueMax)
{
    if (valueMin > valueMax) {
        return;
    }
    m_maxValue = valueMax;
    m_minValue = valueMin;
    repaint();
}

bool CSlider::getEnterState()
{
    return m_isSlideMe;
}

quint64 CSlider::getValue()
{
    return m_curValue;
}


// 手动操作进度条要发射信号
void CSlider::mouseMoveEvent(QMouseEvent *event)
{
    // 值改变，进度条位置改变,不发射信号
    if (event->buttons() & Qt::LeftButton) {
        quint64 tmpValue { static_cast<quint64>(event->pos().x() / (this->width() * 1.0 / m_maxValue))};
        if (tmpValue >= m_minValue && tmpValue <= m_maxValue) {
            m_curValue = tmpValue;
            repaint();
            emit valueChanged(m_curValue);
        }
    }
    QWidget::mouseMoveEvent(event);
}

void CSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        quint64 tmpValue {static_cast<quint64>(event->pos().x() / (this->width() * 1.0 / m_maxValue))};
        if (tmpValue >= m_minValue && tmpValue <= m_maxValue) {
            m_curValue = tmpValue;
            repaint();
            emit valueChanged(m_curValue);
        }
    }
    QWidget::mousePressEvent(event);
}

void CSlider::mouseReleaseEvent(QMouseEvent *event)
{
    emit valueChanged(m_curValue);
    QWidget::mouseReleaseEvent(event);
}

void CSlider::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rectView{0, this->height() / 4, this->width(), static_cast<int>((this->height() * 1.0 / 4) * 2)};
    painter.setViewport(rectView);
    painter.setWindow(0, 0, static_cast<int>(m_maxValue), static_cast<int>(m_maxValue));
    QPen pen{Qt::white};
    pen.setStyle(Qt::SolidLine);
    pen.setJoinStyle(Qt::BevelJoin);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(1);
    QBrush brush{Qt::white};
    painter.setBrush(brush);
    painter.drawRect(0, 0, static_cast<int>(m_maxValue), static_cast<int>(m_maxValue));

    pen.setColor(Qt::blue);
    brush.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(0, 0, m_curValue, static_cast<int>(m_maxValue));

    pen.setColor(Qt::red);
    brush.setColor(Qt::red);
    painter.setPen(pen);
    painter.setBrush(brush);

    int side {this->width() < this->height() ? this ->width() : this->height()};
    painter.setViewport(static_cast<int>(m_curValue * 1.0 * (this->width() * 1.0 / m_maxValue) - side * 1.0 / 2), 0, side, side);
    painter.setWindow(0, 0, side, side);
    painter.drawEllipse(QPoint(side/2, side/2), side / 2, side / 2);
    QWidget::paintEvent(event);
}
