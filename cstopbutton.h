#ifndef CSTOPBUTTON_H
#define CSTOPBUTTON_H

#include "cbutton.h"

class CStopButton : public CButton
{
    Q_OBJECT
public:
    explicit CStopButton(QWidget *parent = nullptr);
signals:
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:

};

#endif // CSTOPBUTTON_H
