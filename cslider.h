#ifndef CSLIDER_H
#define CSLIDER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QLabel>
#include <QTime>

class CSlider : public QWidget
{
    Q_OBJECT
public:
    explicit CSlider(QWidget *parent = nullptr);
    void setMaxValue(quint64 value);
    void setMinValue(quint64 value);
    void setValueRange(quint64 valueMin, quint64 valueMax);
    bool getEnterState();
    quint64 getValue();
public slots:
    void setValue(quint64 value);
protected:
    virtual void enterEvent(QEnterEvent *event) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:
    void valueChanged(qint64 value);
private:
    quint64 m_minValue{0};
    quint64 m_maxValue{100};
    quint64 m_curValue{50};
    quint64 m_pos {0};
    bool m_isSlideMe {false};
};

#endif // CSLIDER_H
