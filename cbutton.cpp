#include "cbutton.h"

CButton::CButton(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
}

void CButton::pressAnimation()
{
    QPropertyAnimation *animation{new QPropertyAnimation{this, "geometry"}};
    animation->setDuration(2);
    animation->setStartValue(QRect{this->x(), this->y(), this->width(), this->height()});
    animation->setEndValue(QRect{this->x() + 2, this->y(), this->width(), this->height()});
    animation->setEasingCurve(QEasingCurve::OutInSine);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CButton::releaseAnimation()
{
    QPropertyAnimation *animation{new QPropertyAnimation{this, "geometry"}};
    animation->setDuration(2);
    animation->setStartValue(QRect{this->x(), this->y(), this->width(), this->height()});
    animation->setEndValue(QRect{this->x() - 2, this->y(), this->width(), this->height()});
    animation->setEasingCurve(QEasingCurve::OutInSine);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
