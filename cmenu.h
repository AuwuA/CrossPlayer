#ifndef CMENU_H
#define CMENU_H

#include <QMenu>

class CMenu : public QMenu
{
    Q_OBJECT
public:
    CMenu(QWidget *parent = nullptr);
};

#endif // CMENU_H
