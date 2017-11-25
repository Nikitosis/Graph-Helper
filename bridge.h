#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPolygon>

#include "myedge.h"

class Bridge : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum ConnectMode{StartToEnd,EndToStart,Both};

    explicit Bridge(QObject *parent = nullptr);
    explicit Bridge(MyEdge *start,MyEdge *end=nullptr,QObject *parent=nullptr);

    void setEndEdge(MyEdge *point);
    void changeConnectMode();
    void setWeight(int weight);
    int getConnectMode() const;
    MyEdge* getStartEdge() const;
    MyEdge* getEndEdge() const;
    QPointF getCenter() const;
    int getWeight() const;

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
    int weight;
    ConnectMode connectMode;
    MyEdge *startEdge;
    MyEdge *endEdge;
};

#endif // BRIDGE_H
