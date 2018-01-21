#include "visualalgorithm.h"
#include "ui_visualalgorithm.h"

VisualAlgorithm::VisualAlgorithm(Graph *graph,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualAlgorithm)
{
    ui->setupUi(this);
    _graph=new Graph(graph,this);
    init();
    isExit=false;

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

void VisualAlgorithm::addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName)
{
    QTreeWidgetItem *mainItem=new QTreeWidgetItem(ui->Watch);
    mainItem->setText(0,mainName);
    for(int i=0;i<names.size();i++)
    {
        QTreeWidgetItem *item=new QTreeWidgetItem(mainItem);
        item->setText(0,names[i]);
        item->setText(1,values[i]);
    }
}

void VisualAlgorithm::addTwoDArray(QVector<QVector<QString>> &values, QVector<QString> &arrayNames,QVector<QString> valueNames, QString mainName)
{
    QTreeWidgetItem *mainItem=new QTreeWidgetItem(ui->Watch);
    mainItem->setText(0,mainName);
    for(int i=0;i<arrayNames.size();i++)
    {
        QTreeWidgetItem *arrayItem=new QTreeWidgetItem(mainItem);
        arrayItem->setText(0,arrayNames[i]);

        for(int j=0;j<valueNames.size();j++)
        {
            QTreeWidgetItem *item=new QTreeWidgetItem(arrayItem);
            item->setText(0,valueNames[j]);
            item->setText(1,values[i][j]);
        }
    }
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

void VisualAlgorithm::Dfs(int startEdge)
{

    mtx.lock();

    QVector<QVector<int>> &Matrix=_graph->getCorrectMatrix();
    QVector<MyEdge *> Edges=_graph->getEdges();
    QVector<bool> Visited(Matrix.size());
    QVector<int> Stack;
    QVector<QPair<int,int>> BridgesVec;

    if(Matrix.size()==0)
    {
        isExit=true;
        mtx.unlock();
        return;
    }

    updateDfs(Matrix,Visited,Stack);
    lockLine(4);

    Visited[startEdge]=true;

    updateDfs(Matrix,Visited,Stack);
    lockLine(5);

    Stack.push_back(startEdge);

    updateDfs(Matrix,Visited,Stack);
    lockLine(6);

    while(!Stack.empty())
    {
        changeEdgeColor(Edges[Stack.last()]->getId(),ACTIVE_BRIDGE_COLOR);
        updateDfs(Matrix,Visited,Stack);
        lockLine(8);
        for(int i=0;i<Matrix.size();i++)
        {
            lockLine(9);
            lockLine(10);
            if(Matrix[Stack.last()][i]!=0 && !Visited[i])
            {
                changeBridgeColor(Edges[Stack.last()]->getId(),Edges[i]->getId(),ACTIVE_BRIDGE_COLOR);
                changeEdgeColor(Edges[i]->getId(),ACTIVE_BRIDGE_COLOR);
                changeEdgeColor(Edges[Stack.last()]->getId(),PASSIVE_BRIDGE_COLOR);
                if(BridgesVec.size()>0)
                {
                    int first=BridgesVec[BridgesVec.size()-1].first;
                    int second=BridgesVec[BridgesVec.size()-1].second;
                    changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
                }
                BridgesVec.push_back({Stack.last(),i});

                lockLine(11);
                lockLine(12);

                Visited[i]=true;

                updateDfs(Matrix,Visited,Stack);
                lockLine(13);

                Stack.push_back(i);

                updateDfs(Matrix,Visited,Stack);
                lockLine(14);

                i=-1;

                updateDfs(Matrix,Visited,Stack);
                lockLine(15);
            }
            lockLine(16);
        }
        changeEdgeColor(Edges[Stack.last()]->getId(),PASSIVE_BRIDGE_COLOR);
        if(BridgesVec.size()>0)
        {
            int first=BridgesVec[BridgesVec.size()-1].first;
            int second=BridgesVec[BridgesVec.size()-1].second;
            changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
            BridgesVec.pop_back();
        }

        updateDfs(Matrix,Visited,Stack);
        lockLine(17);

        Stack.pop_back();

        updateDfs(Matrix,Visited,Stack);
        lockLine(18);
    }

    updateDfs(Matrix,Visited,Stack);
    lockLine(19);
    qDebug()<<"Go!";

    mtx.unlock();
}

void VisualAlgorithm::initDfs()
{
    QFile file(":/Algorithms/Algorithms/DFS.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    ui->Code->document()->setPlainText(stream.readAll());

    changeAllBridgesColor(DEFAULT_BRIDGE_COLOR);
    changeAllEdgesColor(DEFAULT_BRIDGE_COLOR);

    isExit=false;

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

    future = QtConcurrent::run(this,&VisualAlgorithm::Dfs,startEdge);  //Create thread with Algo function
}

void VisualAlgorithm::updateDfs(QVector<QVector<int> > &Matrix, QVector<bool> &Visited, QVector<int> &Stack)
{
    if(isExit)
        return;
    ui->Watch->clear();

    QVector<MyEdge *>Edges=_graph->getEdges();
    QVector<QString> Names(Edges.size());
    QVector<QVector<QString>> StringMatrix(Matrix.size());

    for(int i=0;i<Edges.size();i++)
        Names[i]=Edges[i]->getInfo();

    for(int i=0;i<Matrix.size();i++)
        for(int j=0;j<Matrix[i].size();j++)
            StringMatrix[i].push_back(QString::number(Matrix[i][j]));


    addTwoDArray(StringMatrix,Names,Names,"Matrix");

    QVector<QString> Values;
    for(int i=0;i<Visited.size();i++)
        Values.push_back(QString::number(Visited[i]));
    addOneDArray(Values,Names,"Visited");

    Values.clear();

    for(int i=0;i<Stack.size();i++)
        Values.push_back(Edges[Stack[i]]->getInfo());
    QVector<QString> Numbers;
    for(int i=0;i<Stack.size();i++)
        Numbers.push_back(QString::number(i+1));

    addOneDArray(Values,Numbers,"Stack");
}

void VisualAlgorithm::breakAlgo()
{
    isExit=true;
    condit.wakeAll();
    future.waitForFinished();  //to not leave working thread
}

void VisualAlgorithm::lockLine(int codeLineIndex)
{
    if(isExit)
        return;
    ui->Code->enableDebugMode(codeLineIndex);
    ui->Code->update();
    condit.wait(&mtx);
}

void VisualAlgorithm::reject()
{
    breakAlgo();
    delete this;
}



void VisualAlgorithm::on_debugStep_clicked()
{
    if(!future.isRunning())
        initDfs();
    condit.wakeAll();
}

void VisualAlgorithm::on_debugBreak_clicked()
{
    breakAlgo();
    initDfs();
}
