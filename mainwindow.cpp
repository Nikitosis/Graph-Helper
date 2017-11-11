#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    visualGraphWindow=new VisualGraph(this);
    //Button connections with lambdas


    connect(ui->cursorMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::CursorMode);});
    connect(ui->bridgeMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::BridgeMode);});
    connect(ui->edgeMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::EdgeMode);});
    connect(ui->bridgeDeleteMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::BridgeDeleteMode);});
    connect(ui->edgeDeleteMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(MyGraphicsSceneView::Mode::EdgeDeleteMode);});



    //Initializing some variables and installation the scene
    ui->graphicsView->setMode(MyGraphicsSceneView::Mode::EdgeMode);


}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_visualizeGraph_clicked()
{
    visualGraphWindow->init(ui->graphicsView->getCorrectMatrix());
    visualGraphWindow->show();
}
