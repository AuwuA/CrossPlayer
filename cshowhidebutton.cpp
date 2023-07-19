#include "cshowhidebutton.h"


CShowHideButton::CShowHideButton(QWidget *parent) : CButton{parent}
{
}

void CShowHideButton::mousePressEvent(QMouseEvent *event)
{
    pressAnimation();
    QWidget::mousePressEvent(event);
}

void CShowHideButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_isShowing = (m_isShowing == true ? false : true);
    emit isNeedShow(m_isShowing);
    releaseAnimation();
}

void CShowHideButton::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setViewport(this->rect());
    painter.setWindow(0, 0, 100, 100);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen {Qt::white};
    pen.setStyle(Qt::SolidLine);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidth(20);
    painter.setPen(pen);
    painter.drawLine(0,10,100,10);
    painter.drawLine(0,50,100,50);
    painter.drawLine(0,90,100,90);

    QWidget::paintEvent(event);
}

void CShowHideButton::enterEvent(QEnterEvent *event)
{
    if (m_isShowing) {
        this->setToolTip("隐藏播放列表");
    } else {
        this->setToolTip("显示播放列表");
    }
}
