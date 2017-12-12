#include "line.h"

Line::Line(QObject *parent) :
    QObject(parent),
    startX(0),
    startY(0),
    endX(0),
    endY(0)
{
        prepareGeometryChange();
}

Line::Line(int startX, int startY, int endX, int endY, QObject *parent):
    startX(startX),
    startY(startY),
    endX(endX),
    endY(endY),
    QObject(parent)
{
    prepareGeometryChange();
}

QRectF Line::boundingRect() const
{
    return QRectF(std::min(startX,endX)-10,std::min(startY,endY)-10,std::max(startX,endX)+5,std::max(startY,endY)+5).normalized();
}

void Line::setCoords(int x1, int y1, int x2, int y2)
{
    startX=x1;
    startY=y1;
    endX=x2;
    endY=y2;
    prepareGeometryChange();
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<<startX<<" "<<startY<<" "<<endX<<" "<<endY;
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(startX,startY,endX,endY);
}

