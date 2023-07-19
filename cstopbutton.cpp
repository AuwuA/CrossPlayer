#include "cstopbutton.h"

CStopButton::CStopButton(QWidget *parent)
    : CButton{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setToolTip("停止");
}

void CStopButton::mousePressEvent(QMouseEvent *event)
{
    emit buttonClicked();
    pressAnimation();
}

void CStopButton::mouseReleaseEvent(QMouseEvent *event)
{
    releaseAnimation();
}

void CStopButton::paintEvent(QPaintEvent *event)
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
    QPoint points[4] {{0, 0}, {100, 0}, {100, 100}, {0, 100}};
    painter.drawConvexPolygon(points, sizeof(points)/sizeof(QPoint));
    QWidget::paintEvent(event);
}
