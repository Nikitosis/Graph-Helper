#include "bridge.h"

Bridge::Bridge(QObject *parent) : QObject(parent),startEdge(nullptr),endEdge(nullptr)
{
    this->setZValue(1);
    connectMode=StartToEnd;
}
Bridge::Bridge(MyEdge *start, MyEdge *end, QObject *parent):QObject(parent),startEdge(start),endEdge(end)
{
    this->setZValue(1);
    connectMode=StartToEnd;
}


void Bridge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Bridge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(startEdge->getCordinates(),endEdge->getCordinates());


    QPointF A=startEdge->getCordinates();           //First Point
    QPointF B=endEdge->getCordinates();             //Second Point
    const double radius=startEdge->getRadius();

    if(len2(startEdge->getCordinates(),endEdge->getCordinates())>2*radius)      //If they are not intersected,we paint triangles
    {
        painter->setBrush(Qt::blue);
        if(connectMode==StartToEnd)
            {
                QPolygon polygon=getTrianglePolygon(A,B,endEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
            }
        if(connectMode==EndToStart)
            {
                QPolygon polygon=getTrianglePolygon(B,A,startEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
            }
        if(connectMode==Both)
            {
                QPolygon polygon=getTrianglePolygon(A,B,endEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
                polygon=getTrianglePolygon(B,A,startEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
            }
    }
}

double Bridge::len2(QPointF &a, QPointF &b) const           //length between 2 points
{
    return sqrt((a.x()-b.x())*(a.x()-b.x())+(a.y()-b.y())*(a.y()-b.y()));
}

QPolygon Bridge::getTrianglePolygon(QPointF &from, QPointF &to, double radius, double side) const
{
    //Some geometry calculations,which make triangle polygon
    QPointF A;
    A.setX(from.x());
    A.setY(from.y());

    QPointF B;
    B.setX(to.x());
    B.setY(to.y());
    double ABlen=len2(A,B);

    QPointF AB=B-A;

    double ALlen=ABlen-radius-side;
    double AClen=ABlen-radius;
    QPointF L=A+AB*(ALlen/ABlen);
    QPointF C=A+AB*(AClen/ABlen);

    QPointF LF=AB;
    double x=LF.x();
    double y=LF.y();
    LF.setX(y);
    LF.setY(-x);

    double LFlen=ABlen;
    QPointF Z=L+LF*(side/2/LFlen);
    QPointF X=L-LF*(side/2/LFlen);

    QPoint first;
    first.setX(Z.x());
    first.setY(Z.y());
    QPoint second;
    second.setX(C.x());
    second.setY(C.y());
    QPoint third;
    third.setX(X.x());
    third.setY(X.y());
    QPolygon polygon;
    polygon<<first<<second<<third;
    return polygon;

}

void Bridge::setEndEdge(MyEdge *point)
{
    endEdge=point;
}

void Bridge::changeConnectMode()
{
    if(connectMode==StartToEnd)
        connectMode=EndToStart;
    else
        if(connectMode==EndToStart)
            connectMode=Both;
    else
            connectMode=StartToEnd;
    update();
}

int Bridge::getConnectMode() const
{
    return connectMode;
}

MyEdge* Bridge::getStartEdge() const
{
    return startEdge;
}

MyEdge* Bridge::getEndEdge() const
{
    return endEdge;
}

QRectF Bridge::boundingRect() const
{
    //+-20 to not have any artifacts
    QPointF start=startEdge->getCordinates();
    QPointF end=endEdge->getCordinates();
    return QRectF(QPointF(std::min(start.x(),end.x())-20,std::min(start.y(),end.y())-20),
                  QPointF(std::max(start.x(),end.x())+20,std::max(start.y(),end.y())+20));
}
