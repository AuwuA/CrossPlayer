#ifndef CMUTEBUTTON_H
#define CMUTEBUTTON_H

#include "cbutton.h"

class CMuteButton : public CButton
{
    Q_OBJECT
public:
    CMuteButton(QWidget *parent = nullptr);
signals:
    void isNeedMute(bool muteState);
public slots:
    void setMuteState(bool mute);
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
protected:
    bool m_isMute {false};
};

#endif // CMUTEBUTTON_H
