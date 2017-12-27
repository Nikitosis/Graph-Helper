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
    _color=QColor(68,182,254);
}

MyEdge::MyEdge(QPointF p, int radius, QString info,int id, QObject *parent):
    MyEdge(p.x(),p.y(),radius,info,id,parent)
{
}

MyEdge::MyEdge(MyEdge *edge, QObject *parent):
    MyEdge(edge->_x,edge->_y,edge->_radius,edge->_info,edge->_id,parent)
{
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

void MyEdge::setInfo(QString info)
{
    _info=info;
    update();
}

void MyEdge::setColor(QColor &color)
{
    _color=color;
}

QRectF MyEdge::boundingRect() const
{
    return QRectF(0,0,_radius*2+4,_radius*2+4);   //we added 4 to not have artifacts
}

void MyEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect=boundingRect();
    rect.setCoords(rect.x()+2,rect.y()+2,rect.width()-2,rect.height()-2);     //plus and minus 2 to avoid artifacts
    QPen pen;
    QBrush brush(Qt::white);
    pen.setWidth(4);
    pen.setColor(_color);
    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawEllipse(rect);
    pen.setColor(Qt::black);

    painter->setPen(pen);
    painter->setFont(getFont(painter));
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
    }
    return QGraphicsItem::itemChange(change,value);
}

QFont MyEdge::getFont(QPainter* painter)
{
    QFont font=painter->font();
    font.setPixelSize(15);
    int size=font.pixelSize();
    if(_info.length()>=4)
    {
        size-=4;
        font.setPixelSize(size);
    }
    if(_info.length()>=7)
    {
        size-=4;
        font.setPixelSize(size);
    }
    if(_info.length()>=10)
    {
        size-=2;
        font.setPixelSize(size);
    }
    return font;
}



