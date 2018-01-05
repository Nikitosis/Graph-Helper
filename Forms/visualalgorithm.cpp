#include "visualalgorithm.h"
#include "ui_visualalgorithm.h"

VisualAlgorithm::VisualAlgorithm(Graph *graph,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualAlgorithm)
{
    ui->setupUi(this);
    _graph=new Graph(graph,this);
    init();

    QFuture<void> future = QtConcurrent::run(this,&VisualAlgorithm::Algo);  //Create thread with Algo function
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

    changeAllBridgesColor(DEFAULT_BRIDGE_COLOR);
    changeAllEdgesColor(DEFAULT_BRIDGE_COLOR);
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

void VisualAlgorithm::addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames,QVector<QVector<QString>> valueNames, QString mainName)
{
    QTreeWidgetItem *mainItem=new QTreeWidgetItem(ui->Watch);
    mainItem->setText(0,mainName);
    for(int i=0;i<arrayNames.size();i++)
    {
        QTreeWidgetItem *arrayItem=new QTreeWidgetItem(mainItem);
        arrayItem->setText(0,arrayNames[i]);

        for(int j=0;j<valueNames[i].size();j++)
        {
            QTreeWidgetItem *item=new QTreeWidgetItem(arrayItem);
            item->setText(0,valueNames[i][j]);
            item->setText(1,values[i][j]);
        }
    }
}

void VisualAlgorithm::changeBridgeColor(int startEdgeId, int endEdgeId,QColor color)
{
    QVector<Bridge *> &Bridges=_graph->getBridges();
    for(int i=0;i<Bridges.size();i++)
        if(Bridges[i]->getStartEdge()->getId()==startEdgeId && Bridges[i]->getEndEdge()->getId()==endEdgeId)
            Bridges[i]->setColor(color);
}

void VisualAlgorithm::changeEdgeColor(int id, QColor color)
{
    QVector<MyEdge *>&Edges=_graph->getEdges();
    for(int i=0;i<Edges.size();i++)
        if(Edges[i]->getId()==id)
            Edges[i]->setColor(color);
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

void VisualAlgorithm::DFS()
{

}

void VisualAlgorithm::Algo()
{
    //dosmth
    int startEdge=0;
    QVector<QVector<int>> &Matrix=_graph->getCorrectMatrix();
    QVector<bool> Visited(Matrix.size());
    QStack<int> Stack;
    QVector<QPair<int,int>> BridgesVec;
    Stack.push(startEdge);
    Visited[startEdge]=true;
    int n=Matrix.size();
    while(!Stack.empty())
    {
        changeEdgeColor(Stack.last(),ACTIVE_BRIDGE_COLOR);
        LockLine();
        for(int i=0;i<n;i++)
        {
            if(Matrix[Stack.last()][i]!=0 && !Visited[i])
            {
                Visited[i]=true;
                changeBridgeColor(Stack.last(),i,ACTIVE_BRIDGE_COLOR);
                changeEdgeColor(i,ACTIVE_BRIDGE_COLOR);
                changeEdgeColor(Stack.last(),PASSIVE_BRIDGE_COLOR);
                if(BridgesVec.size()>0)
                {
                    int first=BridgesVec[BridgesVec.size()-1].first;
                    int second=BridgesVec[BridgesVec.size()-1].second;
                    changeBridgeColor(first,second,PASSIVE_BRIDGE_COLOR);
                }
                BridgesVec.push_back({Stack.last(),i});
                Stack.push(i);
                i=-1;
                LockLine();
            }
        }
        changeEdgeColor(Stack.last(),PASSIVE_BRIDGE_COLOR);
        Stack.pop();
        if(BridgesVec.size()>0)
        {
            int first=BridgesVec[BridgesVec.size()-1].first;
            int second=BridgesVec[BridgesVec.size()-1].second;
            changeBridgeColor(first,second,PASSIVE_BRIDGE_COLOR);
            BridgesVec.pop_back();
        }
    }
    QMutexLocker locker(&mtx);
    condit.wait(&mtx);
    LockLine();
    qDebug()<<"Go!";
}

void VisualAlgorithm::LockLine()
{
    QMutexLocker locker(&mtx);
    condit.wait(&mtx);
}

void VisualAlgorithm::on_pushButton_clicked()
{
    condit.wakeAll();
}
