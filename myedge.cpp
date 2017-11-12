#include "myedge.h"
MyEdge::MyEdge(QObject *parent) : QObject(parent)
{
    this->setZValue(2);
    _id=0;
}

MyEdge::MyEdge(int x, int y, int radius,QString info,int id, QObject *parent):
    _x(x),
    _y(y),
    _radius(radius),
    _info(info),
    _id(id),
    QObject(parent)
{
    _xStart=x;
    _yStart=y;
    setPos(x,y);
    this->setZValue(2);
}

MyEdge::MyEdge(QPointF p, int radius, QString info,int id, QObject *parent):
    _x(p.x()),
    _y(p.y()),
    _radius(radius),
    _info(info),
    _id(id),
    QObject(parent)
{
    _xStart=_x;
    _yStart=_y;
    setPos(_x,_y);
    this->setZValue(2);
}

int MyEdge::getId() const
{
    return _id;
}


double MyEdge::getRadius() const
{
    return _radius;
}

QPointF MyEdge::getCordinates() const
{
    return QPointF(pos().x()+_radius,pos().y()+_radius);
}

QString MyEdge::getInfo() const
{
    return _info;
}

QRectF MyEdge::boundingRect() const
{
    return QRectF(0,0,_radius*2,_radius*2);
}

void MyEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect=boundingRect();
    QPen pen;
    QBrush brush(Qt::white);
    pen.setWidth(4);
    pen.setColor(QColor(68,182,254));
    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawEllipse(rect);
    pen.setColor(Qt::black);

    painter->setPen(pen);
    painter->drawText(rect,Qt::AlignCenter,_info);
}

void MyEdge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"press"<<_id;
    emit mousePressSignal(event);
}

QVariant MyEdge::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug()<<"Change";
    if(change==ItemPositionChange)
    {
        _x=pos().x();
        _y=pos().y();
        update();
        emit edgeMoved(this);
    }
    return QGraphicsItem::itemChange(change,value);
}



