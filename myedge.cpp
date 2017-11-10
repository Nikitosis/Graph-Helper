#include "myedge.h"

MyEdge::MyEdge(QObject *parent) : QObject(parent)
{
    this->setZValue(2);

}

MyEdge::MyEdge(int x, int y, int radius,int num, QObject *parent):
    x(x),
    y(y),
    radius(radius),
    num(num),
    QObject(parent)
{
    xStart=x;
    yStart=y;
    setPos(x,y);
    this->setZValue(2);
}

MyEdge::MyEdge(QPointF p, int radius, int num, QObject *parent):
    QObject(parent),
    x(p.x()),
    y(p.y()),
    radius(radius),
    num(num)
{
    xStart=x;
    yStart=y;
    setPos(x,y);
    this->setZValue(2);
}

int MyEdge::getNum() const
{
    return num;
}

double MyEdge::getRadius() const
{
    return radius;
}

QPointF MyEdge::getCordinates() const
{
    return QPointF(pos().x()+radius,pos().y()+radius);
}

QRectF MyEdge::boundingRect() const
{
    return QRectF(0,0,radius*2,radius*2);
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
    painter->drawText(rect,Qt::AlignCenter,QString::number(num));
}

void MyEdge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"press"<<num;
    emit mousePressSignal(event);
}

QVariant MyEdge::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug()<<"Change";
    if(change==ItemPositionChange)
    {
        x=pos().x();
        y=pos().y();
        update();
        emit edgeMoved(this);
    }
    return QGraphicsItem::itemChange(change,value);
}



