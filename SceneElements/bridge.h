#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPolygon>
#include <qmath.h>

#include "myedge.h"

class Bridge : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum ConnectMode{StartToEnd,EndToStart,Both};

    explicit Bridge(int id,QObject *parent = nullptr);
    explicit Bridge(int id,MyEdge *start,MyEdge *end=nullptr,QObject *parent=nullptr);

    void setEndEdge(MyEdge *point);
    void changeConnectMode();
    void setConnectMode(ConnectMode mode);
    void setWeight(int weight);
    void setColor(QColor color);
    ConnectMode getConnectMode() const;
    MyEdge* getStartEdge() const;
    MyEdge* getEndEdge() const;
    QPointF getCenter() const;
    int getWeight() const;
    int getAngle() const;
    int getId() const;

    QRectF boundingRect() const;

signals:

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPolygon getTrianglePolygon(QPointF &from,QPointF &to,double radius,double side) const;
    void paintWeight(QPainter *painter);
    double len2(QPointF &a, QPointF &b) const;

private:
    int _weight;
    ConnectMode _connectMode;
    MyEdge *_startEdge;
    MyEdge *_endEdge;
    int _id;
    QColor _color;
};

#endif // BRIDGE_H
