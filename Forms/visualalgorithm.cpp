#include "visualalgorithm.h"
#include "ui_visualalgorithm.h"

VisualAlgorithm::VisualAlgorithm(Graph *graph, int currentAlgo, QWidget *parent) :
    currentAlgo(currentAlgo),
    QDialog(parent),
    ui(new Ui::VisualAlgorithm)
{
    ui->setupUi(this);
    _graph=new Graph(graph,this);
    algoThread=new QThread;
    init();
    isExit=false;
    switch(currentAlgo)
    {
        case DFS_ALGORITHM:{algo=new DfsAlgorithm(&mtx,graph,isExit,&condit);break;}
        case BFS_ALGORITHM:{algo=new BfsAlgorithm(&mtx,graph,isExit,&condit);break;}
    }

    QObject::connect(algo,SIGNAL(changeBridgeColor(int,int,QColor)),
                     this,SLOT(changeBridgeColor(int,int,QColor)),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(changeEdgeColor(int,QColor)),
                     this,SLOT(changeEdgeColor(int,QColor)),Qt::QueuedConnection); //Qeued connections because it have to be executed in GUI thread

    QObject::connect(algo,SIGNAL(updateEditor(int)),
                     this,SLOT(updateEditor(int)),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(watchSaveState()),
                     ui->Watch,SLOT(saveState()),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(watchClear()),
                     ui->Watch,SLOT(clear()),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(watchAddTwoDArray(QVector<QVector<QString> >,QVector<QString>,QVector<QString>,QString)),
                     ui->Watch,SLOT(addTwoDArray(QVector<QVector<QString> >,QVector<QString>,QVector<QString>,QString)),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(watchAddOneDArray(QVector<QString>,QVector<QString>,QString)),
                     ui->Watch,SLOT(addOneDArray(QVector<QString>,QVector<QString>,QString)),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(watchResetState()),
                     ui->Watch,SLOT(resetState()),Qt::QueuedConnection);

    QObject::connect(algo,SIGNAL(handleSignals()),
                     this,SLOT(handleSignals()),Qt::DirectConnection); //this function have to be executed immedeately(calls in remote thread)

    QObject::connect(algoThread,SIGNAL(started()),algo,SLOT(runAlgo()));

    initAlgo();

}

void VisualAlgorithm::init()
{
    QSizePolicy policy=ui->Graph->sizePolicy();
    policy.setHorizontalStretch(3.93);
    ui->Graph->setSizePolicy(policy);

    policy=ui->Code->sizePolicy();
    policy.setHorizontalStretch(7);
    ui->Code->setSizePolicy(policy);
    ui->splitter_2->setStretchFactor(0,2);
    ui->splitter_2->setStretchFactor(1,1);

    ui->Watch->setColumnCount(2);
    QStringList list;
    list<<"Name"<<"Value";
    ui->Watch->setHeaderLabels(list);

    QVector<MyEdge*> Edges=_graph->getEdges();
    QVector<Bridge*> Bridges=_graph->getBridges();

    for(int i=0;i<Edges.size();i++)
    {
        ui->Graph->addElement(Edges[i]);
        Edges[i]->setParent(ui->Graph);
    }

    for(int i=0;i<Bridges.size();i++)
    {
        ui->Graph->addElement(Bridges[i]);
        Bridges[i]->setParent(ui->Graph);
    }
}

VisualAlgorithm::~VisualAlgorithm()
{
    delete ui;
}

void VisualAlgorithm::changeBridgeColor(int startEdgeId, int endEdgeId,QColor color)
{
    QVector<Bridge *> &Bridges=_graph->getBridges();
    for(int i=0;i<Bridges.size();i++)
        if((Bridges[i]->getStartEdge()->getId()==startEdgeId && Bridges[i]->getEndEdge()->getId()==endEdgeId)
        || (Bridges[i]->getStartEdge()->getId()==endEdgeId && Bridges[i]->getEndEdge()->getId()==startEdgeId))
        {
            Bridges[i]->setColor(color);
            return;
        }
    qDebug()<<"Cannot find Bridge by its Edges"<<endl;
}

void VisualAlgorithm::changeEdgeColor(int id, QColor color)
{
    QVector<MyEdge *>&Edges=_graph->getEdges();
    for(int i=0;i<Edges.size();i++)
        if(Edges[i]->getId()==id)
        {
            Edges[i]->setColor(color);
            return;
        }
    qDebug()<<"Cannot find Edge by its Id"<<endl;
}

void VisualAlgorithm::changeAllBridgesColor(QColor color)
{
    QVector<Bridge *> &Bridges=_graph->getBridges();
    for(int i=0;i<Bridges.size();i++)
        Bridges[i]->setColor(color);
}

void VisualAlgorithm::changeAllEdgesColor(QColor color)
{
    QVector<MyEdge *>&Edges=_graph->getEdges();
    for(int i=0;i<Edges.size();i++)
        Edges[i]->setColor(color);
}

void VisualAlgorithm::initAlgo()
{
    QFile file;
    switch(currentAlgo)
    {
        case DFS_ALGORITHM:{file.setFileName(":/Algorithms/Algorithms/DFS.txt");break;}
        case BFS_ALGORITHM:{file.setFileName(":/Algorithms/Algorithms/BFS.txt");break;}
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    ui->Code->document()->setPlainText(stream.readAll());

    QApplication::processEvents();
    changeAllBridgesColor(DEFAULT_BRIDGE_COLOR);
    changeAllEdgesColor(DEFAULT_BRIDGE_COLOR);



    int startEdge=-1;
    do
    {
    bool isOk=false;
    QString str= QInputDialog::getText(0,
                                       "First Edge",
                                       "First Edge:",
                                       QLineEdit::Normal,
                                       "",
                                       &isOk
                                       );
    if(!isOk)
        return;

    QVector<MyEdge *>Edges=_graph->getEdges();
    for(int i=0;i<Edges.size();i++)
        if(Edges[i]->getInfo()==str)
        {
            startEdge=i;
            break;
        }
    }while(startEdge==-1);

    isExit=false;
    algo->setStartEdge(startEdge);
    algo->moveToThread(algoThread);
    //Algorithm thread1;
    //thread1.run();
    algoThread->start();
    //future = QtConcurrent::run(algo,&Algorithm::runDFS,startEdge);  //Create thread with Algo function
}

void VisualAlgorithm::breakAlgo()
{
    isExit=true;
    condit.wakeAll();
    algoThread->quit();
    algoThread->wait();
}


void VisualAlgorithm::updateEditor(int codeLineIndex)
{
    qDebug()<<"Locked line";
    ui->Code->enableDebugMode(codeLineIndex);
    ui->Code->update();
}

void VisualAlgorithm::handleSignals()
{
    QApplication::processEvents();  //We handle all signals,which are still in our signal queue(from worker thread there are lots of emit UpdateDfs,but this thread hasn't handle them yet,and we don't need it)
}

void VisualAlgorithm::reject()
{
    breakAlgo();
    delete this;
}



void VisualAlgorithm::on_debugStep_clicked()
{
    if(isExit)
    {
        algoThread->quit();
        algoThread->wait();
        qDebug()<<"isrunning "<<algoThread->isRunning();
        condit.wakeAll();
        initAlgo();
    }
    else
    {
        condit.wakeAll();
    }
}

void VisualAlgorithm::on_debugBreak_clicked()
{
    breakAlgo();
    initAlgo();
}
