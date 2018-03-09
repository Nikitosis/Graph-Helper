#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H
#include <QTabWidget>
#include <QTabBar>


class MyTabWidget:public QTabWidget
{
public:
    MyTabWidget(QWidget *parent);

    QTabBar *tabBar() const;
};

#endif // MYTABWIDGET_H
