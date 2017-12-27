#include "bridge.h"

Bridge::Bridge(int id,QObject *parent) : QObject(parent),_startEdge(nullptr),_endEdge(nullptr),_id(id)
{
    this->setZValue(1);
    _connectMode=StartToEnd;
    _weight=1;
    _color=Qt::green;
}
Bridge::Bridge(int id,MyEdge *start, MyEdge *end, QObject *parent):Bridge(id,parent)
{
    _startEdge=start;
    _endEdge=end;
}


void Bridge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Bridge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
    QPen pen;
    pen.setWidth(4);
    pen.setColor(_color);
    painter->setPen(pen);
    painter->drawLine(_startEdge->getCordinates(),_endEdge->getCordinates());



    QPointF A=_startEdge->getCordinates();           //First Point
    QPointF B=_endEdge->getCordinates();             //Second Point
    const double radius=_startEdge->getRadius();

    if(len2(_startEdge->getCordinates(),_endEdge->getCordinates())>2*radius)      //If they are not intersected,we paint triangles
    {
        painter->setBrush(Qt::blue);
        if(_connectMode==StartToEnd)
            {
                QPolygon polygon=getTrianglePolygon(A,B,_endEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
            }
        if(_connectMode==EndToStart)
            {
                QPolygon polygon=getTrianglePolygon(B,A,_startEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
            }
        if(_connectMode==Both)
            {
                QPolygon polygon=getTrianglePolygon(A,B,_endEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
                polygon=getTrianglePolygon(B,A,_startEdge->getRadius(),radius);
                painter->drawPolygon(polygon);
            }
    }
    paintWeight(painter);
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

void Bridge::paintWeight(QPainter *painter)   //paint weight in center of the bridge
{
    QPen pen;
    QRectF rect;
    rect.setCoords(-30,-30,30,30);
    pen.setWidth(10);
    pen.setColor(Qt::black);
    painter->setPen(pen);

    painter->translate(getCenter());

    int angle=getAngle();
    painter->rotate(angle);
    painter->drawText(rect,Qt::AlignCenter,QString::number(_weight));

    painter->resetTransform();
}

void Bridge::setEndEdge(MyEdge *point)
{
   _endEdge=point;
}

void Bridge::changeConnectMode()
{
    if(_connectMode==StartToEnd)
        _connectMode=EndToStart;
    else
        if(_connectMode==EndToStart)
            _connectMode=Both;
    else
            _connectMode=StartToEnd;
    update();
}

void Bridge::setConnectMode(ConnectMode mode)
{
    _connectMode=mode;
}

void Bridge::setWeight(int weight)
{
    _weight=weight;
}

void Bridge::setColor(QColor color)
{
    _color=color;
}

Bridge::ConnectMode Bridge::getConnectMode() const
{
    return _connectMode;
}

MyEdge* Bridge::getStartEdge() const
{
    return _startEdge;
}

MyEdge* Bridge::getEndEdge() const
{
    return _endEdge;
}

QPointF Bridge::getCenter() const
{
    QPointF start=_startEdge->getCordinates();
    QPointF end=_endEdge->getCordinates();
    QPointF center=start+(end-start)/2;
    return center;
}

int Bridge::getWeight() const
{
    return _weight;
}

int Bridge::getAngle() const
{
    double tg=(double)(_endEdge->getCordinates().y()-_startEdge->getCordinates().y())/
            (double)(_endEdge->getCordinates().x()-_startEdge->getCordinates().x());
    const double PI=3.14159265358979;
    return atan(tg)/PI*180;
}

int Bridge::getId() const
{
    return _id;
}

QRectF Bridge::boundingRect() const
{
    //+-20 to not have any artifacts
    QPointF start=_startEdge->getCordinates();
    QPointF end=_endEdge->getCordinates();
    return QRectF(QPointF(std::min(start.x(),end.x())-20,std::min(start.y(),end.y())-20),
                  QPointF(std::max(start.x(),end.x())+20,std::max(start.y(),end.y())+20));
}
