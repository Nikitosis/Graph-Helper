#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    visualGraphWindow=new VisualGraph(this);
    //Button connections with lambdas


    connect(ui->cursorMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(VisualGraphSceneView::Mode::CursorMode);});
    connect(ui->bridgeMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(VisualGraphSceneView::Mode::BridgeMode);});
    connect(ui->edgeMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(VisualGraphSceneView::Mode::EdgeMode);});
    connect(ui->bridgeDeleteMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(VisualGraphSceneView::Mode::BridgeDeleteMode);});
    connect(ui->edgeDeleteMode,&QPushButton::clicked,[=]{ui->graphicsView->setMode(VisualGraphSceneView::Mode::EdgeDeleteMode);});
    connect(ui->deleteAll,SIGNAL(clicked(bool)),ui->graphicsView,SLOT(deleteAll()));



    //Initializing some variables and installation the scene
    ui->graphicsView->setMode(VisualGraphSceneView::Mode::EdgeMode);

    VisualAlgorithm alg(ui->graphicsView->getGraph());
    alg.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_visualizeGraph_clicked()
{
    visualGraphWindow->init(ui->graphicsView->getCorrectMatrix(),ui->graphicsView->getEdges());
    visualGraphWindow->exec();
}
