#ifndef CPLAYBUTTON_H
#define CPLAYBUTTON_H

#include "cbutton.h"


class CPlayButton : public CButton
{
    Q_OBJECT
public:
    explicit CPlayButton(QWidget *parent = nullptr);
    void setPlayState(bool play);
signals:
    void playingState(bool isPlaying);
protected:
    virtual void enterEvent(QEnterEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
protected:
    bool m_isPlaying {};
};

#endif // CPLAYBUTTON_H
