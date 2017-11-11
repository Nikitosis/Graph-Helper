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

void VisualGraph::init(QVector<QVector<int> > Vec)
{

}
