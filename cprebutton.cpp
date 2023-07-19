#include "cprebutton.h"

CPreButton::CPreButton(QWidget *parent)
    : CButton{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setToolTip("上一集");
}

void CPreButton::mousePressEvent(QMouseEvent *event)
{
    emit buttonClicked();
    pressAnimation();
}

void CPreButton::mouseReleaseEvent(QMouseEvent *event)
{
    releaseAnimation();
}

void CPreButton::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setViewport(this->rect());
    painter.setWindow(0, 0, 100, 100);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen {Qt::white};
    pen.setStyle(Qt::SolidLine);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidth(1);
    painter.setPen(pen);
    QBrush brush{Qt::white};
    painter.setBrush(brush);
    painter.drawRect(0, 0, 20, 100);
    QPoint points[3] {{21, 50},{100, 0}, {100, 100}};
    painter.drawConvexPolygon(points, sizeof(points) / sizeof(QPoint));
    QWidget::paintEvent(event);
}
