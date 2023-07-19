#include "cnextbutton.h"

CNextButton::CNextButton(QWidget *parent)
    : CButton{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setToolTip("下一集");
}

void CNextButton::mousePressEvent(QMouseEvent *event)
{
    emit buttonClicked();
    pressAnimation();
}

void CNextButton::mouseReleaseEvent(QMouseEvent *event)
{
    releaseAnimation();
}

void CNextButton::paintEvent(QPaintEvent *event)
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
    painter.drawRect(81, 0, 20, 100);
    QPoint points[3] {{0, 0},{0, 100}, {80, 50}};
    painter.drawConvexPolygon(points, sizeof(points) / sizeof(QPoint));
    QWidget::paintEvent(event);
}
