#include "visualgraph.h"
#include "ui_visualgraph.h"

VisualGraph::VisualGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualGraph)
{
    ui->setupUi(this);
}

VisualGraph::~VisualGraph()
{
    delete ui;
}

void VisualGraph::init(QVector<QVector<int> > Vec,QVector<MyEdge*> Edges)
{
   initMatrix(Vec,Edges);
   initList(Vec,Edges);
   initBridge(Vec,Edges);
   initHelp();

}

void VisualGraph::initMatrix(QVector<QVector<int> > Vec, QVector<MyEdge *> Edges)
{
    QObject::connect(ui->MatrixEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),ui->MatrixInfo->verticalScrollBar(),SLOT(setValue(int)));
    QString str="";
    str+=QString::number(Edges.size())+"\n";
    for(int i=0;i<Vec.size();i++)
    {
        for(int j=0;j<Vec.size();j++)
            str+=QString::number(Vec[i][j])+" ";
        str+="\n";
    }
    ui->MatrixEdit->setText(str);

    str="\n";
    for(int i=0;i<Edges.size();i++)
         str+=Edges[i]->getInfo()+"\n";
    ui->MatrixInfo->setText(str);
}

void VisualGraph::initList(QVector<QVector<int> > Vec, QVector<MyEdge *> Edges)
{
    QObject::connect(ui->ListEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),ui->ListInfo->verticalScrollBar(),SLOT(setValue(int)));
    QString str=QString::number(Edges.size())+"\n";
    for(int i=0;i<Vec.size();i++)
    {
        for(int j=0;j<Vec.size();j++)
            if(Vec[i][j])
                str+=Edges[j]->getInfo()+" ";
        str+="\n";
    }
    ui->ListEdit->setText(str);

    str="\n";
    for(int i=0;i<Edges.size();i++)
         str+=Edges[i]->getInfo()+"\n";
    ui->ListInfo->setText(str);
}

void VisualGraph::initBridge(const QVector<QVector<int> > Vec, const QVector<MyEdge *> Edges)
{
    int bridgesAmount=0;
    for(int i=0;i<Vec.size();i++)
        for(int j=0;j<Vec.size();j++)
            if(Vec[i][j])
                bridgesAmount++;
    QString str=QString::number(Edges.size())+" "+QString::number(bridgesAmount)+"\n";
    for(int i=0;i<Vec.size();i++)
    {
        for(int j=0;j<Vec.size();j++)
            if(Vec[i][j])
                str+=Edges[i]->getInfo()+" "+Edges[j]->getInfo()+" "+QString::number(Vec[i][j])+"\n";

    }
    ui->BridgeEdit->setText(str);
}

void VisualGraph::initHelp()
{
    QFile file(QCoreApplication::applicationDirPath()+"/HelpText/HelpText1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    ui->Question_1->setToolTip(stream.readAll());
    stream.seek(0);

    file.setFileName(QCoreApplication::applicationDirPath()+"/HelpText/HelpText2.txt");
        file.open(QIODevice::ReadOnly | QIODevice::Text);

    ui->Question_2->setToolTip(stream.readAll());
    stream.seek(0);

    file.setFileName(QCoreApplication::applicationDirPath()+"/HelpText/HelpText3.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    ui->Question_3->setToolTip(stream.readAll());
    file.close();
}

