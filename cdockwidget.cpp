#include "cdockwidget.h"

CDockWidget::CDockWidget(QWidget *parent, Qt::WindowFlags flags) : QDockWidget{parent, flags}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
}
