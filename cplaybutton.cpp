#include "cplaybutton.h"

CPlayButton::CPlayButton(QWidget *parent)
    : CButton{parent}
{
    this->setMouseTracking(true);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

void CPlayButton::setPlayState(bool play)
{
    m_isPlaying = play;
    repaint();
}

void CPlayButton::enterEvent(QEnterEvent *event)
{
    if (m_isPlaying) {
        this->setToolTip("暂停");
    } else {
        this->setToolTip("播放");
    }
    QWidget::enterEvent(event);
}

void CPlayButton::mousePressEvent(QMouseEvent *event)
{
    pressAnimation();
    repaint();
    m_isPlaying = (m_isPlaying == true ? false : true);
    emit playingState(m_isPlaying);
    QWidget::mousePressEvent(event);
}

void CPlayButton::mouseReleaseEvent(QMouseEvent *event)
{
    releaseAnimation();
}

void CPlayButton::paintEvent(QPaintEvent *event)
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
    if (m_isPlaying) {
        painter.drawRect(20, 0, 20, 100);
        painter.drawRect(60, 0, 20, 100);
    } else {
        QPoint points[3] {{0, 0},{0, 100}, {100, 50}};
        painter.drawConvexPolygon(points, sizeof(points) / sizeof(QPoint));
    }
    QWidget::paintEvent(event);
}
