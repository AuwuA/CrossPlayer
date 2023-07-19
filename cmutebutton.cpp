#include "cmutebutton.h"

CMuteButton::CMuteButton(QWidget *parent) : CButton{parent}
{
    this->setMouseTracking(true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setToolTip("静音");
}

void CMuteButton::setMuteState(bool mute)
{
    m_isMute = mute;
}

void CMuteButton::mousePressEvent(QMouseEvent *event)
{
    pressAnimation();
    repaint();
    m_isMute = (m_isMute == true ? false : true);
    emit isNeedMute(m_isMute);
    QWidget::mousePressEvent(event);
}

void CMuteButton::mouseReleaseEvent(QMouseEvent *event)
{
    releaseAnimation();
}

void CMuteButton::paintEvent(QPaintEvent *event)
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
    QPoint points[6] {{0, 25}, {25, 25}, {50, 0}, {50, 100}, {25, 75}, {0, 75}};
    painter.drawConvexPolygon(points, sizeof(points) / sizeof(QPoint));
    pen.setWidth(2);
    painter.setPen(pen);
    if (m_isMute) {
        painter.drawLine(60, 25, 85, 75);
        painter.drawLine(60, 75, 85, 25);
    } else {
//        从（10.0, 20.0）画矩形，以矩形最劲的两个点画弧
//        QRectF rectangle{10.0, 20.0, 80.0, 60.0};
//        弧度画好后逆时针旋转60度(整个旋转而不是绕着一点旋转)
//        int startAngle = -60 * 16;
//        户型的圆形叫为120°
//        int spanAngle = 120 * 16;
//        painter.drawArc(rectangle, startAngle, spanAngle);
        painter.setPen(pen);
        QRectF rectangleOne{30.0, 35.0, 30.0, 30.0};
        int startAngleOne { -35 * 16 };
        int spanAngleOne {70 * 16};
        painter.drawArc(rectangleOne, startAngleOne, spanAngleOne);

        QRectF rectangleTwo{20.0, 25.0, 50.0, 50.0};
        int startAngleTwo { -40 * 16 };
        int spanAngleTwo {80 * 16};
        painter.drawArc(rectangleTwo, startAngleTwo, spanAngleTwo);

        QRectF rectangleThree{10.0, 15.0, 70.0, 70.0};
        int startAngleThree { -45 * 16 };
        int spanAngleThree {90 * 16};
        painter.drawArc(rectangleThree, startAngleThree, spanAngleThree);
    }
}
