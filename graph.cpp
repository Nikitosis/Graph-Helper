#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent)
{

}

void Graph::addBridge(Bridge *bridge)
{
    Bridges.push_back(bridge);

    int startNum=bridge->getStartEdge()->getNum()-1;
    int endNum=bridge->getEndEdge()->getNum()-1;

    Matrix[startNum][endNum]=1;
}

void Graph::addEdge(MyEdge *edge)
{
    Edges.push_back(edge);
    Matrix.push_back(QVector<int>(Edges.size()-1,0));
    for(int i=0;i<Matrix.size();i++)
        Matrix[i].push_back(0);
    //Matrix.push_back(QVector<int>({}));
}

int Graph::getEdgesAmount() const
{
    return Edges.size();
}

void Graph::changeConnectMode(Bridge *bridge)
{
    int startNum=bridge->getStartEdge()->getNum()-1;
    int endNum=bridge->getEndEdge()->getNum()-1;
    Matrix[startNum][endNum]=0;
    Matrix[endNum][startNum]=0;

    if(bridge->getConnectMode()==Bridge::StartToEnd)
    {
        Matrix[startNum][endNum]=1;
    }
    if(bridge->getConnectMode()==Bridge::EndToStart)
    {
        Matrix[startNum][endNum]=1;
    }
    if(bridge->getConnectMode()==Bridge::Both)
    {
        Matrix[startNum][endNum]=1;
        Matrix[startNum][endNum]=1;
    }
}

Bridge *Graph::findClosest(QPointF &point) const
{
    int minrast=100000;
    Bridge *minBridge=nullptr;
    for(int i=0;i<Bridges.size();i++)
    {
        if(minrast>getLen(Bridges[i],point))
        {
            minrast=getLen(Bridges[i],point);
            minBridge=Bridges[i];
        }
    }
    return minBridge;
}

double Graph::getLen(Bridge *bridge, QPointF &point) const
{
 QPointF Ap=bridge->getStartEdge()->getCordinates();
 QPointF Bp=bridge->getEndEdge()->getCordinates();

 //check if point is in the segment area(0<=angle<=90)
 QPointF BA=Ap-Bp;
 QPointF BC=point-Bp;
 double scal1=BA.x()*BC.x()+BA.y()*BC.y();
 QPointF AB=Bp-Ap;
 QPointF AC=point-Ap;
 double scal2=AB.x()*AC.x()+AB.y()*AC.y();
 if(scal1<0 || scal2<0) // if point isn't in the segment area,
     return 100;

 int A=Bp.y()-Ap.y();
 int B=Ap.x()-Bp.x();
 int C=Ap.x()*(Ap.y()-Bp.y())+Ap.y()*(Bp.x()-Ap.x());

 double rast=abs(A*point.x()+B*point.y()+C)/sqrt(A*A+B*B);
 return rast;
}

void Graph::setEdgeMovable(bool isMovable)
{
    for(int i=0;i<Edges.size();i++)
        if(isMovable)
            Edges[i]->setFlag(QGraphicsItem::ItemIsMovable);
    else
            Edges[i]->setFlag(QGraphicsItem::ItemIsMovable,false);
}

void Graph::updateBridges()
{
    for(int i=0;i<Bridges.size();i++)
    {
        Bridges[i]->update();
    }
}
