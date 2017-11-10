#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Button connections with lambdas


    connect(ui->cursorMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::CursorMode);});
    connect(ui->bridgeMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::BridgeMode);});
    connect(ui->edgeMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::EdgeMode);});

    //Initializing some variables and installation the scene
    ui->graphicsView->setMode(MyGraphicsSceneView::Mode::EdgeMode);


}

MainWindow::~MainWindow()
{
    delete ui;
}



