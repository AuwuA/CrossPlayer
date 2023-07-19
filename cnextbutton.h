#ifndef CNEXTBUTTON_H
#define CNEXTBUTTON_H

#include "cbutton.h"

class CNextButton : public CButton
{
    Q_OBJECT
public:
    explicit CNextButton(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

};

#endif // QNEXTBUTTON_H
