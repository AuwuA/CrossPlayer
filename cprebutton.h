#ifndef CPREBUTTON_H
#define CPREBUTTON_H

#include "cbutton.h"

class CPreButton : public CButton
{
    Q_OBJECT
public:
    explicit CPreButton(QWidget *parent = nullptr);
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

};

#endif // QPREBUTTON_H
