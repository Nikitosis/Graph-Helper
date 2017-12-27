#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QThread>
#include <Forms/visualgraph.h>
#include <AppElements/visualgraphsceneview.h>
#include <Forms/visualalgorithm.h>

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

    void on_openDfs_clicked();

private:
    Ui::MainWindow *ui;
    VisualGraphSceneView::Mode _nowMode;
    VisualGraph *_visualGraphWindow;



    //enum Mode{Cursor,Bridge,Edge};
};

#endif // MAINWINDOW_H
