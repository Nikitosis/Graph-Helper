#include "mytabwidget.h"

MyTabWidget::MyTabWidget(QWidget *parent):QTabWidget(parent)
{
}

QTabBar *MyTabWidget::tabBar() const
{
    return QTabWidget::tabBar();
}
