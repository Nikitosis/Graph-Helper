#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "mygraphicssceneview.h"
#include "visualgraph.h"

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



    void on_visualizeGraph_clicked();

private:
    Ui::MainWindow *ui;
    MyGraphicsSceneView::Mode nowMode;
    VisualGraph *visualGraphWindow;



    //enum Mode{Cursor,Bridge,Edge};
};

#endif // MAINWINDOW_H
