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

   /* MyEdge *first=new MyEdge(500,500,20,"ada",1,this);
    MyEdge *second=new MyEdge(600,600,20,"kad",2,this);
    Bridge *bridge=new Bridge(first,second,this);
    ui->Graph->addElement(first);
    ui->Graph->addElement(second);
    ui->Graph->addElement(bridge);*/


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

void VisualAlgorithm::Algo()
{
    //dosmth

    QMutexLocker locker(&mtx);
    condit.wait(&mtx);
    qDebug()<<"Go!";
}

void VisualAlgorithm::on_pushButton_clicked()
{
    condit.wakeAll();
}
