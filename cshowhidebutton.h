#ifndef CSHOWHIDEBUTTON_H
#define CSHOWHIDEBUTTON_H

#include "cbutton.h"

class CShowHideButton : public CButton
{
    Q_OBJECT
public:
    CShowHideButton(QWidget *parent = nullptr);
signals:
    void isNeedShow(bool isShowing);
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEnterEvent *event) Q_DECL_OVERRIDE;
private:
    bool m_isShowing {true};
};

#endif // CSHOWHIDEBUTTON_H
