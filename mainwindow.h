#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "mygraphicssceneview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:



private:
    Ui::MainWindow *ui;
    MyGraphicsSceneView::Mode nowMode;


    //enum Mode{Cursor,Bridge,Edge};
};

#endif // MAINWINDOW_H
