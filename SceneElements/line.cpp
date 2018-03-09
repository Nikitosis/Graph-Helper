#include "line.h"

Line::Line(QObject *parent) :
    QObject(parent),
    _startX(0),
    _startY(0),
    _endX(0),
    _endY(0)
{
        prepareGeometryChange();
}

Line::Line(int startX, int startY, int endX, int endY, QObject *parent):
    _startX(startX),
    _startY(startY),
    _endX(endX),
    _endY(endY),
    QObject(parent)
{
    prepareGeometryChange();
}

QRectF Line::boundingRect() const
{
    return QRectF(std::min(_startX,_endX)-10,std::min(_startY,_endY)-10,std::max(_startX,_endX)+5,std::max(_startY,_endY)+5).normalized();
}

void Line::setCoords(int x1, int y1, int x2, int y2)
{
    _startX=x1;
    _startY=y1;
    _endX=x2;
    _endY=y2;
    prepareGeometryChange();
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<<_startX<<" "<<_startY<<" "<<_endX<<" "<<_endY;
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(_startX,_startY,_endX,_endY);
}

