#ifndef CDOCKWIDGET_H
#define CDOCKWIDGET_H

#include <QDockWidget>

class CDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    CDockWidget(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
};

#endif // CDOCKWIDGET_H
