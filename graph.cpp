#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent)
{
}

void Graph::addBridge(Bridge *bridge)
{
    _Bridges.push_back(bridge);

    int startNum=bridge->getStartEdge()->getId();
    int endNum=bridge->getEndEdge()->getId();

    _Matrix[startNum][endNum]=1;
}

bool cmp(MyEdge *first,MyEdge *second) //to compare Edges when sorting
{
    return first->getId()<second->getId();
}

void Graph::addEdge(MyEdge *edge)
{
    _Edges.push_back(edge);
    std::sort(_Edges.begin(),_Edges.end(),cmp);

    if(edge->getId()>=_Matrix.size())
    {
        _Matrix.push_back(QVector<int>(_Edges.size(),0));
        for(int i=0;i<_Matrix.size()-1;i++)//add 0 to other rows
            _Matrix[i].push_back(0);
    }
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
        _Matrix[endNum][startNum]=1;
    }
    if(bridge->getConnectMode()==Bridge::Both)
    {
        _Matrix[startNum][endNum]=1;
        _Matrix[endNum][startNum]=1;
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

int Graph::getFreeId() const
{
    QSet<int> set;
    for(int i=0;i<_Edges.size();i++)
        set.insert(_Edges[i]->getId());
                                        //get the id,which is first empty in sequence 1..infinity
    int num=0;
    while(set.find(num)!=set.end())
        num++;
    return num;
}

QVector<QVector<int> > Graph::getCorrectMatrix() const
{
    int amount=_Edges.size();
    QVector<QVector<int>> Vec;
    QSet<int> set;
    for(int i=0;i<_Edges.size();i++)
        set.insert(_Edges[i]->getId());

    for(int i=0;i<_Matrix.size();i++)
        if(set.find(i)!=set.end())
        {
            Vec.push_back({});
            for(int j=0;j<_Matrix.size();j++)
                if(set.find(j)!=set.end())
                    Vec[Vec.size()-1].push_back(_Matrix[i][j]);
        }
    return Vec;
}

QVector<MyEdge*> Graph::getEdges() const
{
    return _Edges;
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

    for(int i=0;i<_Matrix.size();i++)       //set to zero in Matrix
    {
        if(i==edge->getId())
        {
            for(int j=0;j<_Matrix[i].size();j++)
                _Matrix[i][j]=0;
        }
        _Matrix[i][edge->getId()]=0;
    }
                                             //delete edges and connected bridges
    for(int i=0;i<deleteBridge.size();i++)
        delete deleteBridge[i];
    for(int i=0;i<deleteEdge.size();i++)
        delete deleteEdge[i];
}

void Graph::deleteBridge(Bridge *bridge)
{
    QVector<Bridge*> deleteBridge;
    for(int i=0;i<_Bridges.size();i++)
    {
        if(_Bridges[i]->getStartEdge()->getId()==bridge->getStartEdge()->getId() &&
           _Bridges[i]->getEndEdge()->getId()==bridge->getEndEdge()->getId())
        {
            deleteBridge.push_back(_Bridges[i]);
            _Bridges.erase(_Bridges.begin()+i);
            i--;
        }
    }

    for(int i=0;i<deleteBridge.size();i++)
        delete deleteBridge[i];
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
