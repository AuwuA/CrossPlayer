#ifndef CBUTTON_H
#define CBUTTON_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QEnterEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPropertyAnimation>

class CButton : public QWidget
{
    Q_OBJECT
public:
    explicit CButton(QWidget *parent = nullptr);
protected:
    void pressAnimation();
    void releaseAnimation();
signals:
    void buttonClicked();
protected:
};

#endif // CBUTTON_H
