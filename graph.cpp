#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent)
{
    _edgesAmount=0;
}

void Graph::addBridge(Bridge *bridge)
{
    _Bridges.push_back(bridge);

    int startNum=bridge->getStartEdge()->getId();
    int endNum=bridge->getEndEdge()->getId();

    _Matrix[startNum][endNum]=1;
}

void Graph::addEdge(MyEdge *edge)
{
    _edgesAmount++;
    _Edges.push_back(edge);

    _Matrix.push_back(QVector<int>(_edgesAmount,0));
    for(int i=0;i<_Matrix.size()-1;i++)//add 0 to other rows
        _Matrix[i].push_back(0);
}

int Graph::getEdgesAmount() const
{
    return _edgesAmount;
}

void Graph::changeConnectMode(Bridge *bridge)
{
    int startNum=bridge->getStartEdge()->getId();
    int endNum=bridge->getEndEdge()->getId();
    _Matrix[startNum][endNum]=0;
    _Matrix[endNum][startNum]=0;

    if(bridge->getConnectMode()==Bridge::StartToEnd)
    {
        _Matrix[startNum][endNum]=1;
    }
    if(bridge->getConnectMode()==Bridge::EndToStart)
    {
        _Matrix[startNum][endNum]=1;
    }
    if(bridge->getConnectMode()==Bridge::Both)
    {
        _Matrix[startNum][endNum]=1;
        _Matrix[startNum][endNum]=1;
    }
}

Bridge *Graph::findClosest(QPointF &point) const
{
    int minrast=100000;
    Bridge *minBridge=nullptr;
    for(int i=0;i<_Bridges.size();i++)
    {
        if(minrast>getLen(_Bridges[i],point))
        {
            minrast=getLen(_Bridges[i],point);
            minBridge=_Bridges[i];
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

void Graph::deleteEdge(MyEdge *edge)
{
    QVector<Bridge*> deleteBridge;
    QVector<MyEdge*> deleteEdge;
    //find out,what edge is it and what bridges are being connected to it
    for(int i=0;i<_Bridges.size();i++)
    {
        if(_Bridges[i]->getStartEdge()->getId()==edge->getId() ||
           _Bridges[i]->getEndEdge()->getId()==edge->getId())
        {
            deleteBridge.push_back(_Bridges[i]);
            _Bridges.erase(_Bridges.begin()+i);
            i--;
        }
    }
    for(int i=0;i<_Edges.size();i++)
        if(_Edges[i]->getId()==edge->getId())
            {
                deleteEdge.push_back(_Edges[i]);
                _Edges.erase(_Edges.begin()+i);
                i--;
            }
    //delete edges and connected bridges
    for(int i=0;i<deleteBridge.size();i++)
        delete deleteBridge[i];
    for(int i=0;i<deleteEdge.size();i++)
        delete deleteEdge[i];
}

void Graph::setEdgeMovable(bool isMovable)
{
    for(int i=0;i<_Edges.size();i++)
        if(isMovable)
            _Edges[i]->setFlag(QGraphicsItem::ItemIsMovable);
    else
            _Edges[i]->setFlag(QGraphicsItem::ItemIsMovable,false);
}

void Graph::updateBridges()
{
    for(int i=0;i<_Bridges.size();i++)
    {
        _Bridges[i]->update();
    }
}
