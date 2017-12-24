#include "visualalgorithm.h"
#include "ui_visualalgorithm.h"

VisualAlgorithm::VisualAlgorithm(Graph *graph,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualAlgorithm)
{
    ui->setupUi(this);
    _graph=new Graph(graph,this);
    init();
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
